# Mod-Tap

The Mod-Tap key `MT(mod, kc)` acts like a modifier when held, and a regular keycode when tapped. In other words, you can have a key that sends Escape when you tap it, but functions as a Control or Shift key when you hold it down.

The modifiers this keycode and `OSM()` accept are prefixed with `MOD_`, not `KC_`:

|Modifier  |Description                             |
|----------|----------------------------------------|
|`MOD_LCTL`|Left Control                            |
|`MOD_LSFT`|Left Shift                              |
|`MOD_LALT`|Left Alt                                |
|`MOD_LGUI`|Left GUI (Windows/Command/Meta key)     |
|`MOD_RCTL`|Right Control                           |
|`MOD_RSFT`|Right Shift                             |
|`MOD_RALT`|Right Alt (AltGr)                       |
|`MOD_RGUI`|Right GUI (Windows/Command/Meta key)    |
|`MOD_HYPR`|Hyper (Left Control, Shift, Alt and GUI)|
|`MOD_MEH` |Meh (Left Control, Shift, and Alt)      |

You can combine these by ORing them together like so:

```c
MT(MOD_LCTL | MOD_LSFT, KC_ESC)
```

This key would activate Left Control and Left Shift when held, and send Escape when tapped.

For convenience, QMK includes some Mod-Tap shortcuts to make common combinations more compact in your keymap:

|Key         |Aliases                                                          |Description                                                   |
|------------|-----------------------------------------------------------------|--------------------------------------------------------------|
|`LCTL_T(kc)`|`CTL_T(kc)`                                                      |Left Control when held, `kc` when tapped                      |
|`LSFT_T(kc)`|`SFT_T(kc)`                                                      |Left Shift when held, `kc` when tapped                        |
|`LALT_T(kc)`|`LOPT_T(kc)`, `ALT_T(kc)`, `OPT_T(kc)`                           |Left Alt when held, `kc` when tapped                          |
|`LGUI_T(kc)`|`LCMD_T(kc)`, `LWIN_T(kc)`, `GUI_T(kc)`, `CMD_T(kc)`, `WIN_T(kc)`|Left GUI when held, `kc` when tapped                          |
|`RCTL_T(kc)`|                                                                 |Right Control when held, `kc` when tapped                     |
|`RSFT_T(kc)`|                                                                 |Right Shift when held, `kc` when tapped                       |
|`RALT_T(kc)`|`ROPT_T(kc)`, `ALGR_T(kc)`                                       |Right Alt when held, `kc` when tapped                         |
|`RGUI_T(kc)`|`RCMD_T(kc)`, `RWIN_T(kc)`                                       |Right GUI when held, `kc` when tapped                         |
|`LSG_T(kc)` |`SGUI_T(kc)`, `SCMD_T(kc)`, `SWIN_T(kc)`                         |Left Shift and GUI when held, `kc` when tapped                |
|`LAG_T(kc)` |                                                                 |Left Alt and GUI when held, `kc` when tapped                  |
|`RSG_T(kc)` |                                                                 |Right Shift and GUI when held, `kc` when tapped               |
|`RAG_T(kc)` |                                                                 |Right Alt and GUI when held, `kc` when tapped                 |
|`LCA_T(kc)` |                                                                 |Left Control and Alt when held, `kc` when tapped              |
|`LSA_T(kc)` |                                                                 |Left Shift and Alt when held, `kc` when tapped                |
|`RSA_T(kc)` |`SAGR_T(kc)`                                                     |Right Shift and Right Alt (AltGr) when held, `kc` when tapped |
|`RCS_T(kc)` |                                                                 |Right Control and Right Shift when held, `kc` when tapped     |
|`LCAG_T(kc)`|                                                                 |Left Control, Alt and GUI when held, `kc` when tapped         |
|`RCAG_T(kc)`|                                                                 |Right Control, Alt and GUI when held, `kc` when tapped        |
|`C_S_T(kc)` |                                                                 |Left Control and Shift when held, `kc` when tapped            |
|`MEH_T(kc)` |                                                                 |Left Control, Shift and Alt when held, `kc` when tapped       |
|`HYPR_T(kc)`|`ALL_T(kc)`                                                      |Left Control, Shift, Alt and GUI when held, `kc` when tapped - more info [here](https://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)|

## Caveats

Currently, the `kc` argument of `MT()` is limited to the [Basic Keycode set](keycodes_basic.md), meaning you can't use keycodes like `LCTL()`, `KC_TILD`, or anything greater than `0xFF`. This is because QMK uses 16-bit keycodes, of which 3 bits are used for the function identifier, 1 bit for selecting right or left mods, and 4 bits to tell which mods are used, leaving only 8 bits for the keycode. Additionally, if at least one right-handed modifier is specified in a Mod-Tap, it will cause all modifiers specified to become right-handed, so it is not possible to mix and match the two - for example, Left Control and Right Shift would become Right Control and Right Shift.

Expanding this would be complicated, at best. Moving to a 32-bit keycode would solve a lot of this, but would double the amount of space that the keymap matrix uses. And it could potentially cause issues, too. If you need to apply modifiers to your tapped keycode, [Tap Dance](feature_tap_dance.md#example-5-using-tap-dance-for-advanced-mod-tap-and-layer-tap-keys) can be used to accomplish this.

You may also run into issues when using Remote Desktop Connection on Windows. Because these keycodes send key events faster than a human, Remote Desktop could miss them.
To fix this, open Remote Desktop Connection, click on "Show Options", open the the "Local Resources" tab, and in the keyboard section, change the drop down to "On this Computer". This will fix the issue, and allow the characters to work correctly.
It can also be mitigated by increasing [`TAP_CODE_DELAY`](config_options.md#behaviors-that-can-be-configured).

## Other Resources

See the [Tap-Hold Configuration Options](tap_hold.md) for additional flags that tweak Mod-Tap behavior.
