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
# 2. Find a mavgen
# --------------------------------------------------------------------------- #
# Prefer a mavlink checkout's copy when MAVROOT points at one, else the mavgen.py
# that pip installs. `which` alone is not enough: `pip install --user` puts it in
# ~/.local/bin, which is often not on PATH on Ubuntu.
if [[ -n "${MAVROOT:-}" && -f "$MAVROOT/pymavlink/tools/mavgen.py" ]]; then
	MAVGEN="$MAVROOT/pymavlink/tools/mavgen.py"
else
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
# 3. Make sure the <include>d dialects sit beside military.xml
# --------------------------------------------------------------------------- #
# mavgen resolves <include> relative to the including file's directory. Inside a
# mavlink checkout common.xml is already a sibling. A bare military.xml from the
# mavlink-military repo has no siblings, so stage a temp dir with both.
XMLDIR="$(dirname "$XML")"
if [[ -f "$XMLDIR/common.xml" ]]; then
	BUILD_XML="$XML"
else
	WORKDIR="$(mktemp -d)"
	trap 'rm -rf "$WORKDIR"' EXIT
	cp "$XML" "$WORKDIR/"
	python3 - "$WORKDIR" <<-'PY'
	import os, shutil, sys
	import pymavlink
	src = os.path.join(os.path.dirname(pymavlink.__file__),
	                   "message_definitions", "v1.0")
	need = ("common.xml", "standard.xml", "minimal.xml")
	missing = [f for f in need if not os.path.exists(os.path.join(src, f))]
	if missing:
	    sys.exit("installed pymavlink is missing bundled definitions: %s"
	             % ", ".join(missing))
	for f in need:
	    shutil.copy(os.path.join(src, f), sys.argv[1])
	PY
	BUILD_XML="$WORKDIR/$(basename "$XML")"
	echo "includes:     staged from the installed pymavlink"
fi

# --------------------------------------------------------------------------- #
# 4. Generate, then prove the 53000 block actually made it in
# --------------------------------------------------------------------------- #
python3 "$MAVGEN" --lang=Python --wire-protocol=2.0 \
	--output="$HERE/military_dialect" "$BUILD_XML"

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
