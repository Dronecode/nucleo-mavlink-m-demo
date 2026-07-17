#!/usr/bin/env bash
# Generate the pymavlink Python military dialect used by fake_pixhawk.py.
# Uses the mavlink submodule (with military.xml) from the PX4 worktree.
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"

# Point MAVROOT at a mavlink checkout that has military.xml in its
# message_definitions/v1.0/ dir. In a PX4 tree that is the mavlink submodule:
#   src/modules/mavlink/mavlink
# Default assumes PX4-Autopilot is a sibling of this repo; override as needed:
#   MAVROOT=/path/to/mavlink ./generate_dialect.sh
MAVROOT="${MAVROOT:-$HERE/../../PX4-Autopilot/src/modules/mavlink/mavlink}"
XML="$MAVROOT/message_definitions/v1.0/military.xml"

if [[ ! -f "$XML" ]]; then
	echo "military.xml not found at $XML" >&2
	echo "Set MAVROOT to a mavlink checkout that includes military.xml, e.g." >&2
	echo "  MAVROOT=/path/to/mavlink $0" >&2
	echo "See github.com/Dronecode/mavlink-military for military.xml." >&2
	exit 1
fi

PYTHONPATH="$MAVROOT" python3 "$MAVROOT/pymavlink/tools/mavgen.py" \
	--lang=Python --wire-protocol=2.0 \
	--output="$HERE/military_dialect" \
	"$XML"

echo "wrote $HERE/military_dialect.py"
