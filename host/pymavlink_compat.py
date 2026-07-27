#!/usr/bin/env python3
"""Work around a pymavlink bug that crashes recv_match() mid-session.

pymavlink <=2.4.49 has a latent crash in mavutil.add_message(). The function
stores "instance messages" (those whose dialect marks a field instance="true",
e.g. BATTERY_STATUS.id) in a per-instance dict hung off the cached message:

    if msg._instance_field is None or getattr(msg, msg._instance_field) is None:
        messages[mtype] = msg          # <-- stored plain, _instances stays None
        return
    ...
    messages[mtype]._instances[instance_value] = msg   # <-- None[...] -> TypeError

If the first copy of a type arrives with its instance field unset it is cached
by the first branch, leaving _instances as None. The next copy that *does* carry
an instance value falls through to the last line and raises

    TypeError: 'NoneType' object does not support item assignment

from inside recv_match(), which kills the caller. It shows up on connect-time
resync, when a partially-decoded frame lands before the steady stream, so it is
intermittent -- and it takes down Tools/mavlink_shell.py the same way.

apply() reinstalls add_message() with the missing "_instances is None" guard.
Everything else is byte-for-byte upstream behaviour. Safe to call more than
once, and a no-op on a pymavlink that has already fixed this.
"""
from __future__ import annotations

import copy

from pymavlink import mavutil

_applied = False


def _add_message(messages, mtype, msg):
    """Upstream mavutil.add_message() plus a guard for _instances being None."""
    if msg._instance_field is None or getattr(msg, msg._instance_field, None) is None:
        messages[mtype] = msg
        return

    instance_value = getattr(msg, msg._instance_field)
    # The added "or _instances is None": upstream only rebuilds the cache entry
    # when the type is absent, so a type first seen without an instance value
    # keeps _instances=None forever and the tail of this function explodes.
    if mtype not in messages or getattr(messages[mtype], "_instances", None) is None:
        messages[mtype] = copy.copy(msg)
        messages[mtype]._instances = {instance_value: msg}
        messages["%s[%s]" % (mtype, str(instance_value))] = copy.copy(msg)
        return

    messages[mtype]._instances[instance_value] = msg
    prev_instances = messages[mtype]._instances
    messages[mtype] = copy.copy(msg)
    messages[mtype]._instances = prev_instances
    messages["%s[%s]" % (mtype, str(instance_value))] = copy.copy(msg)


def apply() -> None:
    """Install the patched add_message(). Idempotent."""
    global _applied
    if _applied:
        return
    mavutil.add_message = _add_message
    _applied = True
