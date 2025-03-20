# Keycode String

<table>
<tr><td><b>Module</b></td><td><tt>getreuer/keycode_string</tt></td></tr>
<tr><td><b>Version</b></td><td>2025-03-07</td></tr>
<tr><td><b>Maintainer</b></td><td>Pascal Getreuer (@getreuer)</td></tr>
<tr><td><b>License</b></td><td><a href="../LICENSE.txt">Apache 2.0</a></td></tr>
<tr><td><b>Documentation</b></td><td>
<a href="https://getreuer.info/posts/keyboards/keycode-string">https://getreuer.info/posts/keyboards/keycode-string</a>
</td></tr>
</table>

This is a community module adaptation of [Keycode
String](https://getreuer.info/posts/keyboards/keycode-string), a utility to
convert QMK keycodes to human-readable strings. It's much nicer to read names
like "`LT(2,KC_D)`" than numerical codes like "`0x4207`."

Add the following to your `keymap.json`:

```json
{
    "modules": ["getreuer/keycode_string"]
}
```

Then use `get_keycode_string(keycode)` like:

```c
dprintf("kc=%s\n", get_keycode_string(keycode));
```

Many common QMK keycodes are understood out of the box by
`get_keycode_string()`, but not all. Optionally, use `KEYCODE_STRING_NAMES_USER`
in keymap.c to define names for additional keycodes or override how any keycode
is formatted.

See the [Keycode String
documentation](https://getreuer.info/posts/keyboards/keycode-string) for further
details.

