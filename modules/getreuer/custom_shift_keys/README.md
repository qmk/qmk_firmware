# Custom Shift Keys

<table>
<tr><td><b>Module</b></td><td><tt>getreuer/custom_shift_keys</tt></td></tr>
<tr><td><b>Version</b></td><td>2025-03-07</td></tr>
<tr><td><b>Maintainer</b></td><td>Pascal Getreuer (@getreuer)</td></tr>
<tr><td><b>License</b></td><td><a href="../LICENSE.txt">Apache 2.0</a></td></tr>
<tr><td><b>Documentation</b></td><td>
<a href="https://getreuer.info/posts/keyboards/custom-shift-keys">https://getreuer.info/posts/keyboards/custom-shift-keys</a>
</td></tr>
</table>

This is a community module adaptation of [Custom Shift
Keys](https://getreuer.info/posts/keyboards/custom-shift-keys), a light
alternative to QMK's [Key Overrides](https://docs.qmk.fm/features/key_overrides)
for customizing what keycode is produced when a key is shifted.

Add the following to your `keymap.json` to use Custom Shift Keys:

```json
{
    "modules": ["getreuer/custom_shift_keys"]
}
```

Then in your `keymap.c`, define how keys are shifted with the
`custom_shift_keys` array. Each row defines one key. The first keycode is the
keycode as it appears in your layout and determines what is typed normally. The
shifted_keycode is what you want the key to type when shifted. An example:

```c
const custom_shift_key_t custom_shift_keys[] = {
  {KC_DOT , KC_QUES},  // Shift . is ?
  {KC_COMM, KC_EXLM},  // Shift , is !
  {KC_MINS, KC_EQL },  // Shift - is =
  {KC_COLN, KC_SCLN},  // Shift : is ; 
};
```

For instance, the first row defines that when `KC_DOT` is pressed with Shift
held, keycode `KC_QUES` is sent.

See the [Custom Shift Keys
documentation](https://getreuer.info/posts/keyboards/custom-shift-keys) for
configuration options and further details.
