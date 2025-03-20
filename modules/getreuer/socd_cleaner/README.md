# SOCD Cleaner

<table>
<tr><td><b>Module</b></td><td><tt>getreuer/socd_cleaner</tt></td></tr>
<tr><td><b>Version</b></td><td>2025-03-07</td></tr>
<tr><td><b>Maintainer</b></td><td>Pascal Getreuer (@getreuer)</td></tr>
<tr><td><b>License</b></td><td><a href="../LICENSE.txt">Apache 2.0</a></td></tr>
<tr><td><b>Documentation</b></td><td>
<a href="https://getreuer.info/posts/keyboards/socd-cleaner">https://getreuer.info/posts/keyboards/socd-cleaner</a>
</td></tr>
</table>

This is a community module adaptation of [SOCD Cleaner
Case](https://getreuer.info/posts/keyboards/socd-cleaner) for Simultaneous
Opposing Cardinal Directions (SOCD) filtering. What this mouthful of a name
means is that when two keys of opposing direction are held at the same time, a
rule is applied to decide which key is sent to the computer. Such filtering is
popular for fast inputs on the WASD keys in gaming. 

**Caution: Check game rules before using.** Notably, [Counter-Strike does not
allow SOCD
filtering](https://store.steampowered.com/news/app/730/view/6500469346429600836).
It is your responsibility to disable SOCD Cleaner where it is prohibited.

## Add SOCD to your keymap

Add the following to your `keymap.json`:

```json
{
  "modules": ["getreuer/socd_cleaner"]
}
```

Then in your `keymap.c`, add:

```c
socd_cleaner_t socd_opposing_pairs[] = {
  {{KC_W, KC_S}, SOCD_CLEANER_LAST},
  {{KC_A, KC_D}, SOCD_CLEANER_LAST},
};
```

These lines specify that SOCD filtering is to be performed on the WASD keys
(referred to by keycodes `KC_W`, `KC_A`, `KC_S`, `KC_D`) with last input
priority resolution (`SOCD_CLEANER_LAST`). If you want to do something else,
this is where to change that.

Resolution strategies:

* `SOCD_CLEANER_LAST`: (Recommended) Last input priority with reactivation. The
  last key pressed wins. If the last key is released while the opposing key is
  still held, the opposing key is reactivated. Rapid alternating inputs can be
  made. Repeatedly tapping the `D` key while `A` is held sends `ADADADAD`.

* `SOCD_CLEANER_NEUTRAL`: Neutral resolution. When both keys are pressed, they
  cancel and neither is sent.

* `SOCD_CLEANER_0_WINS`: Key 0 always wins, the first key listed in defining the
  opposing pair.

* `SOCD_CLEANER_1_WINS`: Key 1 always wins, the second key listed.

* `SOCD_CLEANER_OFF`: SOCD filtering is disabled for this key pair.

SOCD Cleaner is enabled by default. Optionally, use these keycodes to enable and
disable SOCD Cleaner globally for all opposing pairs:

| Keycode   | Description               |
|-----------|---------------------------|
| `SOCDON`  | Turn SOCD Cleaner on.     |
| `SOCDOFF` | Turn SOCD Cleaner off.    |
| `SOCDTOG` | Toggle SOCD Cleaner.      |


See the [SOCD Cleaner
documentation](https://getreuer.info/posts/keyboards/socd-cleaner) for further
explanation and details.

