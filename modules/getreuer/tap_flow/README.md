# Tap Flow

<table>
<tr><td><b>Module</b></td><td><tt>getreuer/tap_flow</tt></td></tr>
<tr><td><b>Version</b></td><td>2025-04-08</td></tr>
<tr><td><b>Maintainer</b></td><td>Pascal Getreuer (@getreuer)</td></tr>
<tr><td><b>License</b></td><td><a href="../LICENSE.txt">Apache 2.0</a></td></tr>
<tr><td><b>Documentation</b></td><td>
<a href="https://getreuer.info/posts/keyboards/tap-flow">https://getreuer.info/posts/keyboards/tap-flow</a>
</td></tr>
</table>

This module is an implementation of "global quick tap" (GQT), aka "require
prior idle," for tap-hold keys. It is particularly useful for home row mods to
avoid accidental mod triggers in fast typing. Tap Flow is the predecessor of QMK
core feature [Flow Tap](https://docs.qmk.fm/tap_hold#flow-tap).

To use this module, add the following to your `keymap.json`:

```json
{
    "modules": ["getreuer/tap_flow"]
}
```

Tap Flow's term can be tuned on the fly with the following keycodes:

| Keycode           | Alias     | Description                       |
|-------------------|-----------|-----------------------------------|
| `TAP_FLOW_PRINT`  | `TFLOW_P` | Type the current value.           |
| `TAP_FLOW_UP`     | `TFLOW_U` | Increase by 5&nbsp;ms.            |
| `TAP_FLOW_DOWN`   | `TFLOW_D` | Decrease by 5&nbsp;ms.            |

Tap Flow's default behavior is:

* Filtering is done only when a tap-hold press is within `TAP_FLOW_TERM` of the
  previous key event, which defaults to 150&nbsp;ms. Use `TFLOW_U` / `TFLOW_D`
  to tune, then define `TAP_FLOW_TERM` in your `config.h` to set the value
  printed by `TFLOW_P`.

* Filtering is done only when both the tap-hold key and the previous key are
  among <kbd>Space</kbd>, letters <kbd>A</kbd>&ndash;<kbd>Z</kbd>, and
  punctuations <kbd>,</kbd> <kbd>.</kbd> <kbd>;</kbd> <kbd>/</kbd>.

Define the `is_tap_flow_key()` or `get_tap_flow_term()` callbacks to customize.

Tap Flow modifies the tap-hold decision such that when a tap-hold key is pressed
within a short timeout of the preceding key, the tapping function is used. The
assumption is that during fast typing, only the tap function of tap-hold keys is
desired (though perhaps with an exception for Shift or AltGr, noted below),
whereas the hold functions (mods and layers) are used in isolation, or at least
with a brief pause preceding the tap-hold key press.

Optionally, the feature can be customized with the `is_tap_flow_key()` and
`get_tap_flow_term()` callbacks. In this way, exceptions may be made for Shift
and AltGr (or whatever you wish) to use a shorter time or to disable filtering
for those keys entirely.

For full documentation, see
<https://getreuer.info/posts/keyboards/tap-flow>
