# Modifier Keys :id=modifier-keys

These allow you to combine a modifier with a keycode. When pressed, the keydown event for the modifier, then `kc` will be sent. On release, the keyup event for `kc`, then the modifier will be sent.

|Key       |Aliases                        |Description                                           |
|----------|-------------------------------|------------------------------------------------------|
|`LCTL(kc)`|`C(kc)`                        |Hold Left Control and press `kc`                      |
|`LSFT(kc)`|`S(kc)`                        |Hold Left Shift and press `kc`                        |
|`LALT(kc)`|`A(kc)`, `LOPT(kc)`            |Hold Left Alt and press `kc`                          |
|`LGUI(kc)`|`G(kc)`, `LCMD(kc)`, `LWIN(kc)`|Hold Left GUI and press `kc`                          |
|`RCTL(kc)`|                               |Hold Right Control and press `kc`                     |
|`RSFT(kc)`|                               |Hold Right Shift and press `kc`                       |
|`RALT(kc)`|`ROPT(kc)`, `ALGR(kc)`         |Hold Right Alt and press `kc`                         |
|`RGUI(kc)`|`RCMD(kc)`, `LWIN(kc)`         |Hold Right GUI and press `kc`                         |
|`SGUI(kc)`|`SCMD(kc)`, `SWIN(kc)`         |Hold Left Shift and GUI and press `kc`                |
|`LCA(kc)` |                               |Hold Left Control and Alt and press `kc`              |
|`LSA(kc)` |                               |Hold Left Shift and Left Alt and press `kc`           |
|`RSA(kc)` |`SAGR(kc)`                     |Hold Right Shift and Right Alt (AltGr) and press `kc` |
|`RCS(kc)` |                               |Hold Right Control and Right Shift and press `kc`     |
|`LCAG(kc)`|                               |Hold Left Control, Alt and GUI and press `kc`         |
|`MEH(kc)` |                               |Hold Left Control, Shift and Alt and press `kc`       |
|`HYPR(kc)`|                               |Hold Left Control, Shift, Alt and GUI and press `kc`  |

You can also chain them, for example `LCTL(LALT(KC_DEL))` or `C(A(KC_DEL))` makes a key that sends Control+Alt+Delete with a single keypress.

# Checking Modifier State :id=checking-modifier-state

The current modifier state can mainly be accessed with two functions: `get_mods()` for normal modifiers and modtaps and `get_oneshot_mods()` for one-shot modifiers (unless they're held, in which case they act like normal modifier keys).

The presence of one or more specific modifiers in the current modifier state can be detected by ANDing the modifier state with a mod mask corresponding to the set of modifiers you want to match for. The reason why bitwise operators are used is that the modifier state is stored as a single byte in the format (GASC)<sub>R</sub>(GASC)<sub>L</sub>.

Thus, to give an example, `01000010` would be the internal representation of LShift+RAlt.
For more information on bitwise operators in C, click [here](https://en.wikipedia.org/wiki/Bitwise_operations_in_C) to open the Wikipedia page on the topic.

In practice, this means that you can check whether a given modifier is active with `get_mods() & MOD_BIT(KC_<modifier>)` (see the [list of modifier keycodes](keycodes_basic.md#modifiers)) or with `get_mods() & MOD_MASK_<modifier>` if the difference between left and right hand modifiers is not important and you want to match both. Same thing can be done for one-shot modifiers if you replace `get_mods()` with `get_oneshot_mods()`.

To check that *only* a specific set of mods is active at a time, AND the modifier state and your desired mod mask as explained above and compare the result to the mod mask itself: `get_mods() & <mod mask> == <mod mask>`.

For example, let's say you want to trigger a piece of custom code if one-shot left control and one-shot left shift are on but every other one-shot mods are off. To do so, you can compose the desired mod mask by combining the mod bits for left control and shift with `(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT))` and then plug it in: `get_oneshot_mods & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT)) == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT))`. Using `MOD_MASK_CS` instead for the mod bitmask would have forced you to press four modifier keys (both versions of control and shift) to fulfill the condition.

The full list of mod masks is as follows:

| Mod Mask Name      | Matching Modifiers                             |
|--------------------|------------------------------------------------|
| `MOD_MASK_CTRL`    | LCTRL       , RCTRL                            |
| `MOD_MASK_SHIFT`   | LSHIFT      , RSHIFT                           |
| `MOD_MASK_ALT`     | LALT        , RALT                             |
| `MOD_MASK_GUI`     | LGUI        , RGUI                             |
| `MOD_MASK_CS`      | CTRL        , SHIFT                            |
| `MOD_MASK_CA`      | (L/R)CTRL   , (L/R)ALT                         |
| `MOD_MASK_CG`      | (L/R)CTRL   , (L/R)GUI                         |
| `MOD_MASK_SA`      | (L/R)SHIFT  , (L/R)ALT                         |
| `MOD_MASK_SG`      | (L/R)SHIFT  , (L/R)GUI                         |
| `MOD_MASK_AG`      | (L/R)ALT    , (L/R)GUI                         |
| `MOD_MASK_CSA`     | (L/R)CTRL   , (L/R)SHIFT , (L/R)ALT            |
| `MOD_MASK_CSG`     | (L/R)CTRL   , (L/R)SHIFT , (L/R)GUI            |
| `MOD_MASK_CAG`     | (L/R)CTRL   , (L/R)ALT   , (L/R)GUI            |
| `MOD_MASK_SAG`     | (L/R)SHIFT  , (L/R)ALT   , (L/R)GUI            |
| `MOD_MASK_CSAG`    | (L/R)CTRL   , (L/R)SHIFT , (L/R)ALT , (L/R)GUI |

Aside from accessing the currently active modifiers using `get_mods()`, there exists some other functions you can use to modify the modifier state, where the `mods` argument refers to the modifiers bitmask.

* `add_mods(mods)`: Enable `mods` without affecting any other modifiers
* `register_mods(mods)`: Like `add_mods` but send a keyboard report immediately.
* `del_mods(mods)`: Disable `mods` without affecting any other modifiers
* `unregister_mods(mods)`: Like `del_mods` but send a keyboard report immediately.
* `set_mods(mods)`: Overwrite current modifier state with `mods`
* `clear_mods()`: Reset the modifier state by disabling all modifiers

Similarly, in addition to `get_oneshot_mods()`, there also exists these functions for one-shot mods:

* `add_oneshot_mods(mods)`: Enable `mods` without affecting any other one-shot modifiers
* `del_oneshot_mods(mods)`: Disable `mods` without affecting any other one-shot modifiers
* `set_oneshot_mods(mods)`: Overwrite current one-shot modifier state with `mods`
* `clear_oneshot_mods()`: Reset the one-shot modifier state by disabling all one-shot modifiers

## Examples :id=examples

The following examples use [advanced macro functions](feature_macros.md#advanced-macro-functions) which you can read more about in the [documentation page on macros](feature_macros.md).

### Alt + Escape for Alt + Tab :id=alt-escape-for-alt-tab

Simple example where chording Left Alt with `KC_ESC` makes it behave like `KC_TAB` for alt-tabbing between applications. This example strictly checks if only Left Alt is active, meaning you can't do Alt+Shift+Esc to switch between applications in reverse order. Also keep in mind that this removes the ability to trigger the actual Alt+Escape keyboard shortcut, though it keeps the ability to do AltGr+Escape.

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

    case KC_ESC:
        // Detect the activation of only Left Alt
        if ((get_mods() & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
            if (record->event.pressed) {
                // No need to register KC_LALT because it's already active.
                // The Alt modifier will apply on this KC_TAB.
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            // Do not let QMK process the keycode further
            return false;
        }
        // Else, let QMK process the KC_ESC keycode as usual
        return true;

    }
    return true;
};
```

### Shift + Backspace for Delete :id=shift-backspace-for-delete

Advanced example where the original behaviour of shift is cancelled when chorded with `KC_BSPC` and is instead fully replaced by `KC_DEL`. Two main variables are created to make this work well: `mod_state` and `delkey_registered`. The first one stores the modifier state and is used to restore it after registering `KC_DEL`. The second variable is a boolean variable (true or false) which keeps track of the status of `KC_DEL` to manage the release of the whole Backspace/Delete key correctly.

As opposed to the previous example, this doesn't use strict modifier checking. Pressing `KC_BSPC` while one or two shifts are active is enough to trigger this custom code, regardless of the state of other modifiers. That approach offers some perks: Ctrl+Shift+Backspace lets us delete the next word (Ctrl+Delete) and Ctrl+Alt+Shift+Backspace lets us execute the Ctrl+Alt+Del keyboard shortcut.

```c
// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {

    case KC_BSPC:
        {
        // Initialize a boolean variable that keeps track
        // of the delete key status: registered or not?
        static bool delkey_registered;
        if (record->event.pressed) {
            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_DEL keycode
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                // Update the boolean variable to reflect the status of KC_DEL
                delkey_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Backspace/Delete key.
                set_mods(mod_state);
                return false;
            }
        } else { // on release of KC_BSPC
            // In case KC_DEL is still being sent even after the release of KC_BSPC
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        // Let QMK process the KC_BSPC keycode as usual outside of shift
        return true;
    }

    }
    return true;
};
```

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
