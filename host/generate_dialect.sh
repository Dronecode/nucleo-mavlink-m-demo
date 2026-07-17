#!/usr/bin/env bash
# Generate the pymavlink Python military dialect used by fake_pixhawk.py.
# Uses the mavlink submodule (with military.xml) from the PX4 worktree.
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"

# Point this at the mavlink checkout that has military.xml in message_definitions.
MAVROOT="${MAVROOT:-/Users/rroche/Work/Dronecode/PX4-Autopilot/.claude/worktrees/wobbly-growing-rain/src/modules/mavlink/mavlink}"
XML="$MAVROOT/message_definitions/v1.0/military.xml"

if [[ ! -f "$XML" ]]; then
	echo "military.xml not found at $XML" >&2
	echo "Set MAVROOT to a mavlink checkout that includes military.xml." >&2
	exit 1
fi

PYTHONPATH="$MAVROOT" python3 "$MAVROOT/pymavlink/tools/mavgen.py" \
	--lang=Python --wire-protocol=2.0 \
	--output="$HERE/military_dialect" \
	"$XML"

echo "wrote $HERE/military_dialect.py"
