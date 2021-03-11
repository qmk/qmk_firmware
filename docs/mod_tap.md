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
|`SGUI_T(kc)`|`SCMD_T(kc)`, `SWIN_T(kc)`                                       |Left Shift and GUI when held, `kc` when tapped                |
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

Unfortunately, these keycodes cannot be used in Mod-Taps or Layer-Taps, since any modifiers specified in the keycode are ignored.

Additionally, you may run into issues when using Remote Desktop Connection on Windows. Because these codes send shift very fast, Remote Desktop may miss the codes.

To fix this, open Remote Desktop Connection, click on "Show Options", open the the "Local Resources" tab. In the keyboard section, change the drop down to "On this Computer". This will fix the issue, and allow the characters to work correctly.

## Other Resources

See the [Tap-Hold Configuration Options](tap_hold.md) for additional flags that tweak Mod-Tap behavior.
