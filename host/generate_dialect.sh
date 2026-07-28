#!/usr/bin/env bash
# Generate host/military_dialect.py, the pymavlink MAVLink-M dialect that every
# host script imports. It is ~2 MB of generated code and git-ignored, so a fresh
# clone must run this once before anything else works.
#
# You need exactly one input: military.xml, from
# https://github.com/Dronecode/mavlink-military
#
# You do NOT need a PX4 or mavlink checkout. military.xml includes common.xml,
# which includes standard.xml and minimal.xml, and `pip install -r
# requirements.txt` already ships those three plus the generator.
#
# Usage:
#   ./generate_dialect.sh /path/to/military.xml     # explicit, always wins
#   MILITARY_XML=/path/to/military.xml ./generate_dialect.sh
#   MAVROOT=/path/to/mavlink ./generate_dialect.sh  # use a mavlink checkout
#   ./generate_dialect.sh                           # search the usual places
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"

# One cleanup for both temporaries; WORKDIR is only created if we have to stage
# the included dialects.
WORKDIR=""
MAVGEN_LOG="$(mktemp)"
cleanup() {
	rm -f "$MAVGEN_LOG"
	[[ -n "$WORKDIR" ]] && rm -rf "$WORKDIR"
	return 0
}
trap cleanup EXIT

# --------------------------------------------------------------------------- #
# 1. Find military.xml
# --------------------------------------------------------------------------- #
XML=""
CANDIDATES=()
if [[ $# -ge 1 ]]; then
	XML="$1"
	[[ -f "$XML" ]] || { echo "not a file: $XML" >&2; exit 1; }
elif [[ -n "${MILITARY_XML:-}" ]]; then
	XML="$MILITARY_XML"
	[[ -f "$XML" ]] || { echo "MILITARY_XML is not a file: $XML" >&2; exit 1; }
else
	# Nothing explicit, so try the usual spots, nearest first. A MAVROOT-style
	# mavlink checkout still works but is no longer required or assumed.
	CANDIDATES=(
		"$HERE/military.xml"
		"$HERE/../military.xml"
		"$HERE/../../mavlink-military/military.xml"
		"$HERE/../../../mavlink-military/military.xml"
	)
	[[ -n "${MAVROOT:-}" ]] && CANDIDATES=(
		"$MAVROOT/message_definitions/v1.0/military.xml" "${CANDIDATES[@]}")
	for c in "${CANDIDATES[@]}"; do
		if [[ -f "$c" ]]; then XML="$c"; break; fi
	done
fi

if [[ -z "$XML" ]]; then
	{
		echo "military.xml not found."
		echo
		echo "Pass it explicitly:"
		echo "    ./generate_dialect.sh /path/to/military.xml"
		echo
		echo "Or clone it beside this repo and re-run with no arguments:"
		echo "    git clone https://github.com/Dronecode/mavlink-military"
		echo "    ./generate_dialect.sh"
		echo
		echo "Searched:"
		printf '    %s\n' "${CANDIDATES[@]}"
	} >&2
	exit 1
fi

XML="$(cd "$(dirname "$XML")" && pwd)/$(basename "$XML")"   # absolutise
echo "military.xml: $XML"

# --------------------------------------------------------------------------- #
# 2. Make sure the <include>d dialects sit beside military.xml
# --------------------------------------------------------------------------- #
# mavgen resolves <include> relative to the including file's directory. Inside a
# mavlink checkout common.xml is already a sibling. A bare military.xml from the
# mavlink-military repo has no siblings, so stage a temp dir with both.
XMLDIR="$(dirname "$XML")"
if [[ -f "$XMLDIR/common.xml" ]]; then
	BUILD_XML="$XML"
else
	WORKDIR="$(mktemp -d)"   # cleaned up by the EXIT trap at the top
	cp "$XML" "$WORKDIR/"
	SRC="$(MAVROOT="${MAVROOT:-}" MAVLINK_DEFS="${MAVLINK_DEFS:-}" \
		python3 - "$HERE" <<-'PY'
	import os, sys
	need = ("common.xml", "standard.xml", "minimal.xml")
	here = sys.argv[1]

	cands = []
	# Explicit override always wins.
	if os.environ.get("MAVLINK_DEFS"):
	    cands.append(os.environ["MAVLINK_DEFS"])
	if os.environ.get("MAVROOT"):
	    cands.append(os.path.join(os.environ["MAVROOT"],
	                              "message_definitions", "v1.0"))
	# The pip wheel ships them inside the package.
	try:
	    import pymavlink
	    cands.append(os.path.join(os.path.dirname(pymavlink.__file__),
	                              "message_definitions", "v1.0"))
	except ImportError:
	    pass
	# Distro packages (Debian/Ubuntu python3-pymavlink, ROS) split data files
	# out of the module tree, so check the usual share/ locations too.
	for base in (sys.prefix, "/usr", "/usr/local", os.path.expanduser("~/.local")):
	    for proj in ("pymavlink", "mavlink"):
	        cands.append(os.path.join(base, "share", proj,
	                                  "message_definitions", "v1.0"))
	# A mavlink checkout sitting beside this repo.
	for rel in ("../../mavlink", "../../../mavlink"):
	    cands.append(os.path.join(here, rel, "message_definitions", "v1.0"))

	for d in cands:
	    if all(os.path.exists(os.path.join(d, f)) for f in need):
	        print(os.path.abspath(d))
	        break
	else:
	    sys.stderr.write(
	        "could not find common.xml/standard.xml/minimal.xml, which "
	        "military.xml includes.\n\nSearched:\n"
	        + "".join("    %s\n" % os.path.abspath(d) for d in cands)
	        + "\nFix any one of these:\n"
	          "  * reinstall pymavlink from pip, which bundles them:\n"
	          "        python3 -m pip install --upgrade --force-reinstall pymavlink\n"
	          "    (Ubuntu's apt python3-pymavlink strips these data files)\n"
	          "  * point at a mavlink checkout:\n"
	          "        git clone https://github.com/mavlink/mavlink\n"
	          "        MAVLINK_DEFS=mavlink/message_definitions/v1.0 ./generate_dialect.sh\n"
	          "  * or put military.xml in a directory that already has common.xml\n")
	    sys.exit(1)
	PY
	)"
	for f in common.xml standard.xml minimal.xml; do cp "$SRC/$f" "$WORKDIR/"; done
	BUILD_XML="$WORKDIR/$(basename "$XML")"
	echo "includes:     $SRC"
fi

# --------------------------------------------------------------------------- #
# 3. Find a mavgen, preferring one that matches where the includes came from
# --------------------------------------------------------------------------- #
# Version skew is the trap here. mavgen validates the XML against the
# mavschema.xsd shipped alongside *it*, so an old pip mavgen fed a recent
# common.xml fails with a wall of
#   SCHEMAV_ELEMENT_CONTENT: Element 'superseded': This element is not expected
# because <superseded> was added to common.xml after that schema was cut. So if
# the definitions came out of a checkout that carries its own mavgen, use that
# one: a matched pair validates cleanly.
MAVGEN=""
if [[ -n "${SRC:-}" ]]; then
	# $SRC is <root>/message_definitions/v1.0, so <root> is two levels up.
	SRC_ROOT="$(cd "$SRC/../.." && pwd)"
	for c in "$SRC_ROOT/pymavlink/tools/mavgen.py" "$SRC_ROOT/tools/mavgen.py"; do
		[[ -f "$c" ]] && { MAVGEN="$c"; break; }
	done
fi
if [[ -z "$MAVGEN" && -n "${MAVROOT:-}" && -f "$MAVROOT/pymavlink/tools/mavgen.py" ]]; then
	MAVGEN="$MAVROOT/pymavlink/tools/mavgen.py"
fi
if [[ -z "$MAVGEN" ]]; then
	# `which` alone is not enough: `pip install --user` puts it in ~/.local/bin,
	# which is frequently not on PATH on Ubuntu.
	MAVGEN="$(python3 - <<-'PY'
	import os, shutil, sysconfig
	p = shutil.which("mavgen.py")
	if not p:
	    for d in (sysconfig.get_path("scripts"),
	              os.path.expanduser("~/.local/bin"), "/usr/local/bin"):
	        c = os.path.join(d, "mavgen.py")
	        if os.path.exists(c):
	            p = c
	            break
	print(p or "")
	PY
	)"
fi

if [[ -z "$MAVGEN" ]]; then
	echo "mavgen.py not found. Install the host deps first:" >&2
	echo "    python3 -m pip install -r $HERE/requirements.txt" >&2
	exit 1
fi
echo "mavgen:       $MAVGEN"

# --------------------------------------------------------------------------- #
# 4. Generate, then prove the 53000 block actually made it in
# --------------------------------------------------------------------------- #
# Try with validation on. If it fails only because this mavgen's mavschema.xsd
# predates an element in the XML (the <superseded> case above), retry without
# validation rather than dead-ending: these XMLs come from upstream, and the
# real correctness check is the MAVLink-M message count below, which is far more
# meaningful than XSD conformance.
if ! python3 "$MAVGEN" --lang=Python --wire-protocol=2.0 \
		--output="$HERE/military_dialect" "$BUILD_XML" 2>"$MAVGEN_LOG"; then
	if grep -q "SCHEMAV\|SCHEMASV\|not expected" "$MAVGEN_LOG"; then
		echo
		echo "note: XML validation failed, which almost always means this mavgen's"
		echo "      schema is older than these XML definitions. Retrying without"
		echo "      validation. To silence this, match the versions:"
		echo "          python3 -m pip install --upgrade pymavlink"
		echo
		python3 "$MAVGEN" --lang=Python --wire-protocol=2.0 --no-validate \
			--output="$HERE/military_dialect" "$BUILD_XML"
	else
		cat "$MAVGEN_LOG" >&2
		echo "mavgen failed, and not because of XML validation." >&2
		exit 1
	fi
fi

# Without this check a wrong or stale XML yields a common-only dialect that
# imports fine and then mysteriously drops every ESAD message at runtime.
python3 - "$HERE" <<-'PY'
import sys
sys.path.insert(0, sys.argv[1])
import military_dialect as m
n = sum(1 for i in m.mavlink_map if 53000 <= i < 54000)
if n == 0:
    sys.exit("FAIL: generated dialect has no MAVLink-M (53000-block) messages. "
             "Wrong military.xml?")
print("wrote %s/military_dialect.py (%d MAVLink-M messages, wire protocol %s)"
      % (sys.argv[1], n, m.WIRE_PROTOCOL_VERSION))
PY
