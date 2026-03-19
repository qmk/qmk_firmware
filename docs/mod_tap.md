# Mod-Tap

The Mod-Tap key `MT(mod, kc)` acts like a modifier when held, and a regular keycode when tapped. In other words, you can have a key that sends Escape when you tap it, but functions as a Control or Shift key when you hold it down.

The modifiers (`mod`) argument to the `MT()` macro are prefixed with `MOD_`, not `KC_`:

|Modifier  |Description                             |
|----------|----------------------------------------|
|`MOD_LCTL`|Left Control                            |
|`MOD_LSFT`|Left Shift                              |
|`MOD_LALT`|Left Alt                                |
|`MOD_LGUI`|Left GUI (Windows/Command/Super key)    |
|`MOD_RCTL`|Right Control                           |
|`MOD_RSFT`|Right Shift                             |
|`MOD_RALT`|Right Alt (AltGr)                       |
|`MOD_RGUI`|Right GUI (Windows/Command/Super key)   |
|`MOD_HYPR`|Hyper (Left Control, Shift, Alt and GUI)|
|`MOD_MEH` |Meh (Left Control, Shift, and Alt)      |

You can combine these by ORing them together like so:

```c
MT(MOD_LCTL | MOD_LSFT, KC_ESC)
```

This key would activate Left Control and Left Shift when held, and send Escape when tapped.

For convenience, QMK includes some Mod-Tap shortcuts to make common combinations more compact in your keymap:

|Key         |Aliases                                                          |Description                                                                            |
|------------|-----------------------------------------------------------------|---------------------------------------------------------------------------------------|
|`LCTL_T(kc)`|`CTL_T(kc)`                                                      |Left Control when held, `kc` when tapped                                               |
|`LSFT_T(kc)`|`SFT_T(kc)`                                                      |Left Shift when held, `kc` when tapped                                                 |
|`LALT_T(kc)`|`ALT_T(kc)`, `LOPT_T(kc)`, `OPT_T(kc)`                           |Left Alt when held, `kc` when tapped                                                   |
|`LGUI_T(kc)`|`GUI_T(kc)`, `LCMD_T(kc)`, `LWIN_T(kc)`, `CMD_T(kc)`, `WIN_T(kc)`|Left GUI when held, `kc` when tapped                                                   |
|`LCS_T(kc)` |                                                                 |Left Control and Left Shift when held, `kc` when tapped                                |
|`LCA_T(kc)` |                                                                 |Left Control and Left Alt when held, `kc` when tapped                                  |
|`LCG_T(kc)` |                                                                 |Left Control and Left GUI when held, `kc` when tapped                                  |
|`LSA_T(kc)` |                                                                 |Left Shift and Left Alt when held, `kc` when tapped                                    |
|`LSG_T(kc)` |                                                                 |Left Shift and Left GUI when held, `kc` when tapped                                    |
|`LAG_T(kc)` |                                                                 |Left Alt and Left GUI when held, `kc` when tapped                                      |
|`LCSG_T(kc)`|                                                                 |Left Control, Left Shift and Left GUI when held, `kc` when tapped                      |
|`LCAG_T(kc)`|                                                                 |Left Control, Left Alt and Left GUI when held, `kc` when tapped                        |
|`LSAG_T(kc)`|                                                                 |Left Shift, Left Alt and Left GUI when held, `kc` when tapped                          |
|`RCTL_T(kc)`|                                                                 |Right Control when held, `kc` when tapped                                              |
|`RSFT_T(kc)`|                                                                 |Right Shift when held, `kc` when tapped                                                |
|`RALT_T(kc)`|`ROPT_T(kc)`, `ALGR_T(kc)`                                       |Right Alt when held, `kc` when tapped                                                  |
|`RGUI_T(kc)`|`RCMD_T(kc)`, `RWIN_T(kc)`                                       |Right GUI when held, `kc` when tapped                                                  |
|`RCS_T(kc)` |                                                                 |Right Control and Right Shift when held, `kc` when tapped                              |
|`RCA_T(kc)` |                                                                 |Right Control and Right Alt when held, `kc` when tapped                                |
|`RCG_T(kc)` |                                                                 |Right Control and Right GUI when held, `kc` when tapped                                |
|`RSA_T(kc)` |                                                                 |Right Shift and Right Alt when held, `kc` when tapped                                  |
|`RSG_T(kc)` |                                                                 |Right Shift and Right GUI when held, `kc` when tapped                                  |
|`RAG_T(kc)` |                                                                 |Right Alt and Right GUI when held, `kc` when tapped                                    |
|`RCSG_T(kc)`|                                                                 |Right Control, Right Shift and Right GUI when held, `kc` when tapped                   |
|`RCAG_T(kc)`|                                                                 |Right Control, Right Alt and Right GUI when held, `kc` when tapped                     |
|`RSAG_T(kc)`|                                                                 |Right Shift, Right Alt and Right GUI when held, `kc` when tapped                       |
|`MEH_T(kc)` |                                                                 |Left Control, Left Shift and Left Alt when held, `kc` when tapped                      |
|`HYPR_T(kc)`|                                                                 |Left Control, Left Shift, Left Alt and Left GUI when held, `kc` when tapped<sup>1</sup>|

<sup>1. More information on the Hyper key can be found on [this blog post by Brett Terpstra](https://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/).</sup>

## Caveats

Currently, the `kc` argument of `MT()` is limited to the [Basic Keycode set](keycodes_basic), meaning you can't use keycodes like `LCTL()`, `KC_TILD`, or anything greater than `0xFF`. This is because QMK uses 16-bit keycodes, of which 3 bits are used for the function identifier, 1 bit for selecting right or left mods, and 4 bits to tell which mods are used, leaving only 8 bits for the keycode. Additionally, if at least one right-handed modifier is specified in a Mod-Tap, it will cause all modifiers specified to become right-handed, so it is not possible to mix and match the two - for example, Left Control and Right Shift would become Right Control and Right Shift.

Expanding this would be complicated, at best. Moving to a 32-bit keycode would solve a lot of this, but would double the amount of space that the keymap matrix uses. And it could potentially cause issues, too. If you need to apply modifiers to your tapped keycode, [Tap Dance](features/tap_dance#example-5-using-tap-dance-for-advanced-mod-tap-and-layer-tap-keys) can be used to accomplish this.

You may also run into issues when using Remote Desktop Connection on Windows. Because these keycodes send key events faster than a human, Remote Desktop could miss them.
To fix this, open Remote Desktop Connection, click on "Show Options", open the "Local Resources" tab, and in the keyboard section, change the drop down to "On this Computer". This will fix the issue, and allow the characters to work correctly.
It can also be mitigated by increasing [`TAP_CODE_DELAY`](config_options#behaviors-that-can-be-configured).

## Intercepting Mod-Taps

### Changing tap function

The basic keycode limitation with Mod-Tap can be worked around by intercepting it in `process_record_user`. For example, shifted keycode `KC_DQUO` cannot be used with `MT()` because it is a 16-bit keycode alias of `LSFT(KC_QUOT)`. Modifiers on `KC_DQUO` will be masked by `MT()`. But the following custom code can be used to intercept the "tap" function to manually send `KC_DQUO`:

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_DQUO):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_DQUO); // Send KC_DQUO on tap
                return false;        // Return false to ignore further processing of key
            }
            break;
    }
    return true;
}
```

### Changing hold function

Likewise, similar custom code can also be used to intercept the hold function to send custom user key code. The following example uses `LT(0, kc)` (layer-tap key with no practical use because layer 0 is always active) to add cut, copy and paste function to X,C and V keys when they are held down:

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(0,KC_X):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(C(KC_X)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_C):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(C(KC_C)); // Intercept hold function to send Ctrl-C
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_V):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-V
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
    }
    return true;
}
```

### Changing both tap and hold

This last example implements custom tap and hold function with `LT(0,KC_NO)` to create a single copy-on-tap, paste-on-hold key:

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(0,KC_NO):
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_C)); // Intercept tap function to send Ctrl-C
            } else if (record->event.pressed) {
                tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-V
            }
            return false;
    }
    return true;
}
```

## Other Resources

See the [Tap-Hold Configuration Options](tap_hold) for additional flags that tweak Mod-Tap behavior.
