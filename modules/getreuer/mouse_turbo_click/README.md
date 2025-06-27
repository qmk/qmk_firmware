# Mouse Turbo Click

<table>
<tr><td><b>Module</b></td><td><tt>getreuer/mouse_turbo_click</tt></td></tr>
<tr><td><b>Version</b></td><td>2025-03-07</td></tr>
<tr><td><b>Maintainer</b></td><td>Pascal Getreuer (@getreuer)</td></tr>
<tr><td><b>License</b></td><td><a href="../LICENSE.txt">Apache 2.0</a></td></tr>
<tr><td><b>Documentation</b></td><td>
<a href="https://getreuer.info/posts/keyboards/mouse-turbo-click">https://getreuer.info/posts/keyboards/mouse-turbo-click</a>
</td></tr>
</table>

This is a community module adaptation of [Mouse Turbo
Click](https://getreuer.info/posts/keyboards/mouse-turbo-click) to click the
mouse rapidly.

Add the following to your `keymap.json`:

```json
{
    "modules": ["getreuer/mouse_turbo_click"]
}
```

Then use the keycode `TURBO` somewhere in your layout. This key clicks the mouse
rapidly, implemented using mouse keys and a periodic callback function:

* Pressing and holding the Turbo Click button sends rapid mouse clicks,
  about 12 clicks per second.

* Quickly double tapping the Turbo Click button "locks" it. Rapid mouse
  clicks are sent until the Turbo Click button is tapped again.

Optionally, the click rate and keycode can be customized. See the [Mouse Turbo
Click documentation](https://getreuer.info/posts/keyboards/mouse-turbo-click)
for details.

