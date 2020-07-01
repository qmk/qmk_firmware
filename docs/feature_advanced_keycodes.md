# Modifier Keys :id=modifier-keys

These allow you to combine a modifier with a keycode. When pressed, the keydown event for the modifier, then `kc` will be sent. On release, the keyup event for `kc`, then the modifier will be sent.

|Key       |Aliases                        |Description                                         |
|----------|-------------------------------|----------------------------------------------------|
|`LCTL(kc)`|`C(kc)`                        |Hold Left Control and press `kc`                    |
|`LSFT(kc)`|`S(kc)`                        |Hold Left Shift and press `kc`                      |
|`LALT(kc)`|`A(kc)`, `LOPT(kc)`            |Hold Left Alt and press `kc`                        |
|`LGUI(kc)`|`G(kc)`, `LCMD(kc)`, `LWIN(kc)`|Hold Left GUI and press `kc`                        |
|`RCTL(kc)`|                               |Hold Right Control and press `kc`                   |
|`RSFT(kc)`|                               |Hold Right Shift and press `kc`                     |
|`RALT(kc)`|`ROPT(kc)`, `ALGR(kc)`         |Hold Right Alt and press `kc`                       |
|`RGUI(kc)`|`RCMD(kc)`, `LWIN(kc)`         |Hold Right GUI and press `kc`                       |
|`SGUI(kc)`|`SCMD(kc)`, `SWIN(kc)`         |Hold Left Shift and GUI and press `kc`              |
|`LCA(kc)` |                               |Hold Left Control and Alt and press `kc`            |
|`LCAG(kc)`|                               |Hold Left Control, Alt and GUI and press `kc`       |
|`MEH(kc)` |                               |Hold Left Control, Shift and Alt and press `kc`     |
|`HYPR(kc)`|                               |Hold Left Control, Shift, Alt and GUI and press `kc`|

You can also chain them, for example `LCTL(LALT(KC_DEL))` or `C(A(KC_DEL))` makes a key that sends Control+Alt+Delete with a single keypress.

# Legacy Content :id=legacy-content

This page used to encompass a large set of features. We have moved many sections that used to be part of this page to their own pages. Everything below this point is simply a redirect so that people following old links on the web find what they're looking for.

## Layers :id=switching-and-toggling-layers

* [Layers](feature_layers.md)

## Mod-Tap :id=mod-tap

* [Mod-Tap](mod_tap.md)

## One Shot Keys :id=one-shot-keys

* [One Shot Keys](one_shot_keys.md)

## Tap-Hold Configuration Options :id=tap-hold-configuration-options

* [Tap-Hold Configuration Options](tap_hold.md)
