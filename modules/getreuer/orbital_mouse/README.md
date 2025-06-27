# Orbital Mouse

<table>
<tr><td><b>Module</b></td><td><tt>getreuer/orbital_mouse</tt></td></tr>
<tr><td><b>Version</b></td><td>2025-03-07</td></tr>
<tr><td><b>Maintainer</b></td><td>Pascal Getreuer (@getreuer)</td></tr>
<tr><td><b>License</b></td><td><a href="../LICENSE.txt">Apache 2.0</a></td></tr>
<tr><td><b>Documentation</b></td><td>
<a href="https://getreuer.info/posts/keyboards/orbital-mouse">https://getreuer.info/posts/keyboards/orbital-mouse</a>
</td></tr>
</table>

This is a community module adaptation of [Orbital
Mouse](https://getreuer.info/posts/keyboards/orbital-mouse) for a polar approach
to mouse control. Orbital Mouse replaces QMK Mouse Keys. The pointer moves
according to a heading direction. Two keys move forward and backward along that
direction while another two keys steer.

Add the following to your `keymap.json`:

```json
{
    "modules": ["getreuer/orbital_mouse"]
}
```

Then use the "`OM_*`" Orbital Mouse keycodes in your layout. 

| Keycode     | Aliases     | Description                                    |
|-------------|-------------|------------------------------------------------|
| `OM_U`      | `MS_UP`     | Move forward.                                  |
| `OM_D`      | `MS_DOWN`   | Move backward.                                 |
| `OM_L`      | `MS_LEFT`   | Steer left (counter-clockwise).                |
| `OM_R`      | `MS_RGHT`   | Steer right (clockwise).                       |
| `OM_BTN`*n* | `MS_BTN`*n* | Press mouse button *n*, for *n* = 1, ..., 8.   |
| `OM_W_U`    | `MS_WHLU`   | Mouse wheel up.                                |
| `OM_W_D`    | `MS_WHLD`   | Mouse wheel down.                              |
| `OM_W_L`    | `MS_WHLL`   | Mouse wheel left.                              |
| `OM_W_R`    | `MS_WHLR`   | Mouse wheel right.                             |
| `OM_SLOW`   |             | Slow mode. Movement is slower while held.      |
| `OM_SEL`*n* |             | Select mouse button *n*, for *n* = 1, ..., 8.  |
| `OM_BTNS`   |             | Press the selected mouse button.               |
| `OM_DBLS`   |             | Double click the selected mouse button.        |
| `OM_HLDS`   |             | Hold the selected mouse button.                |
| `OM_RELS`   |             | Release the selected mouse button.             |

A suggested right-handed layout for Orbital Mouse control is

    OM_W_U , OM_BTNS, OM_U   , OM_DBLS, _______,
    OM_W_D , OM_L   , OM_D   , OM_R   , OM_SLOW,
    OM_RELS, OM_HLDS, OM_SEL1, OM_SEL2, OM_SEL3,

Optionally, there are config options to customize Sentence Case. See the
[Orbital Mouse
documentation](https://getreuer.info/posts/keyboards/orbital-mouse) for details.

