# Advanced Keycodes

Your keymap can include keycodes that are more advanced than normal, for example keys that switch layers or send modifiers when held, but send regular keycodes when tapped. This page documents the functions that are available to you.

## Assigning Custom Names

People often define custom names using `#define`. For example:

```c
#define FN_CAPS LT(_FL, KC_CAPSLOCK)
#define ALT_TAB LALT(KC_TAB)
```

This will allow you to use `FN_CAPS` and `ALT_TAB` in your `KEYMAP()`, keeping it more readable.

## Caveats

Currently, `LT()` and `MT()` are limited to the [Basic Keycode set](keycodes_basic.md), meaning you can't use keycodes like `LCTL()`, `KC_TILD`, or anything greater than `0xFF`. Modifiers specified as part of a Layer Tap or Mod Tap's keycode will be ignored.

Additionally, if at least one right-handed modifier is specified in a Mod Tap or Layer Tap, it will cause all modifiers specified to become right-handed, so it is not possible to mix and match the two.

# Switching and Toggling Layers

These functions allow you to activate layers in various ways. Note that layers are not generally independent layouts -- multiple layers can be activated at once, and it's typical for layers to use `KC_TRNS` to allow keypresses to pass through to lower layers. For a detailed explanation of layers, see [Keymap Overview](keymap.md#keymap-and-layers)

* `DF(layer)` - switches the default layer. The default layer is the always-active base layer that other layers stack on top of. See below for more about the default layer. This might be used to switch from QWERTY to Dvorak layout. (Note that this is a temporary switch that only persists until the keyboard loses power. To modify the default layer in a persistent way requires deeper customization, such as calling the `set_single_persistent_default_layer` function inside of [process_record_user](custom_quantum_functions.md#programming-the-behavior-of-any-keycode).)
* `MO(layer)` - momentarily activates *layer*. As soon as you let go of the key, the layer is deactivated. 
* `LM(layer, mod)` - Momentarily activates *layer* (like `MO`), but with modifier(s) *mod* active. Only supports layers 0-15 and the left modifiers.
* `LT(layer, kc)` - momentarily activates *layer* when held, and sends *kc* when tapped. Only supports layers 0-15.
* `OSL(layer)` - momentarily activates *layer* until the next key is pressed. See [One Shot Keys](#one-shot-keys) for details and additional functionality.
* `TG(layer)` - toggles *layer*, activating it if it's inactive and vice versa
* `TO(layer)` - activates *layer* and de-activates all other layers (except your default layer). This function is special, because instead of just adding/removing one layer to your active layer stack, it will completely replace your current active layers, uniquely allowing you to replace higher layers with a lower one. This is activated on keydown (as soon as the key is pressed).
* `TT(layer)` - Layer Tap-Toggle. If you hold the key down, *layer* is activated, and then is de-activated when you let go (like `MO`). If you repeatedly tap it, the layer will be toggled on or off (like `TG`). It needs 5 taps by default, but you can change this by defining `TAPPING_TOGGLE` -- for example, `#define TAPPING_TOGGLE 2` to toggle on just two taps.

# Working with Layers

Care must be taken when switching layers, it's possible to lock yourself into a layer with no way to deactivate that layer (without unplugging your keyboard.) We've created some guidelines to help users avoid the most common problems.

## Beginners

If you are just getting started with QMK you will want to keep everything simple. Follow these guidelines when setting up your layers:

* Setup layer 0 as your default, "base" layer. This is your normal typing layer, and could be whatever layout you want (qwerty, dvorak, colemak, etc.). It's important to set this as the lowest layer since it will typically have most or all of the keyboard's keys defined, so would block other layers from having any effect if it were above them (i.e., had a higher layer number). 
* Arrange your layers in a "tree" layout, with layer 0 as the root. Do not try to enter the same layer from more than one other layer.
* In a layer's keymap, only reference higher-numbered layers. Because layers are processed from the highest-numbered (topmost) active layer down, modifying the state of lower layers can be tricky and error-prone.

## Intermediate Users

Sometimes you need more than one base layer. For example, if you want to switch between QWERTY and Dvorak, switch between layouts for different countries, or switch your layout for different videogames. Your base layers should always be the lowest numbered layers. When you have multiple base layers you should always treat them as mutually exclusive. When one base layer is on the others are off.

## Advanced Users

Once you have a good feel for how layers work and what you can do, you can get more creative. The rules listed in the beginner section will help you be successful by avoiding some of the tricker details but they can be constraining, especially for ultra-compact keyboard users. Understanding how layers work will allow you to use them in more advanced ways.

Layers stack on top of each other in numerical order. When determining what a keypress does, QMK scans the layers from the top down, stopping when it reaches the first active layer that is not set to `KC_TRNS`. As a result if you activate a layer that is numerically lower than your current layer, and your current layer (or another layer that is active and higher than your target layer) has something other than `KC_TRNS`, that is the key that will be sent, not the key on the layer you just activated. This is the cause of most people's "why doesn't my layer get switched" problem.

Sometimes, you might want to switch between layers in a macro or as part of a tap dance routine. `layer_on` activates a layer, and `layer_off` deactivates it. More layer-related functions can be found in [action_layer.h](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/action_layer.h).

# Modifier Keys

These allow you to combine a modifier with a keycode. When pressed, the keydown event for the modifier, then `kc` will be sent. On release, the keyup event for `kc`, then the modifier will be sent.

|Key       |Aliases               |Description                                         |
|----------|----------------------|----------------------------------------------------|
|`LCTL(kc)`|                      |Hold Left Control and press `kc`                    |
|`LSFT(kc)`|`S(kc)`               |Hold Left Shift and press `kc`                      |
|`LALT(kc)`|                      |Hold Left Alt and press `kc`                        |
|`LGUI(kc)`|`LCMD(kc)`, `LWIN(kc)`|Hold Left GUI and press `kc`                        |
|`RCTL(kc)`|                      |Hold Right Control and press `kc`                   |
|`RSFT(kc)`|                      |Hold Right Shift and press `kc`                     |
|`RALT(kc)`|`ALGR(kc)`            |Hold Right Alt and press `kc`                       |
|`RGUI(kc)`|`RCMD(kc)`, `LWIN(kc)`|Hold Right GUI and press `kc`                       |
|`HYPR(kc)`|                      |Hold Left Control, Shift, Alt and GUI and press `kc`|
|`MEH(kc)` |                      |Hold Left Control, Shift and Alt and press `kc`     |
|`LCAG(kc)`|                      |Hold Left Control, Alt and GUI and press `kc`       |
|`SGUI(kc)`|`SCMD(kc)`, `SWIN(kc)`|Hold Left Shift and GUI and press `kc`              |
|`LCA(kc)` |                      |Hold Left Control and Alt and press `kc`            |

You can also chain them, for example `LCTL(LALT(KC_DEL))` makes a key that sends Control+Alt+Delete with a single keypress.

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

|Key         |Aliases                                |Description                                            |
|------------|---------------------------------------|-------------------------------------------------------|
|`LCTL_T(kc)`|`CTL_T(kc)`                            |Left Control when held, `kc` when tapped               |
|`RCTL_T(kc)`|                                       |Right Control when held, `kc` when tapped              |
|`LSFT_T(kc)`|`SFT_T(kc)`                            |Left Shift when held, `kc` when tapped                 |
|`RSFT_T(kc)`|                                       |Right Shift when held, `kc` when tapped                |
|`LALT_T(kc)`|`ALT_T(kc)`                            |Left Alt when held, `kc` when tapped                   |
|`RALT_T(kc)`|`ALGR_T(kc)`                           |Right Alt when held, `kc` when tapped                  |
|`LGUI_T(kc)`|`LCMD_T(kc)`, `RWIN_T(kc)`, `GUI_T(kc)`|Left GUI when held, `kc` when tapped                   |
|`RGUI_T(kc)`|`RCMD_T(kc)`, `RWIN_T(kc)`             |Right GUI when held, `kc` when tapped                  |
|`C_S_T(kc)` |                                       |Left Control and Shift when held, `kc` when tapped     |
|`MEH_T(kc)` |                                       |Left Control, Shift and Alt when held, `kc` when tapped|
|`LCAG_T(kc)`|                                       |Left Control, Alt and GUI when held, `kc` when tapped  |
|`RCAG_T(kc)`|                                       |Right Control, Alt and GUI when held, `kc` when tapped |
|`ALL_T(kc)` |                                       |Left Control, Shift, Alt and GUI when held, `kc` when tapped - more info [here](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)|
|`SGUI_T(kc)`|`SCMD_T(kc)`, `SWIN_T(kc)`             |Left Shift and GUI when held, `kc` when tapped         |
|`LCA_T(kc)` |                                       |Left Control and Alt when held, `kc` when tapped       |

## Caveats

Unfortunately, these keycodes cannot be used in Mod-Taps or Layer-Taps, since any modifiers specified in the keycode are ignored.

Additionally, you may run into issues when using Remote Desktop Connection on Windows. Because these codes send shift very fast, Remote Desktop may miss the codes.

To fix this, open Remote Desktop Connection, click on "Show Options", open the the "Local Resources" tab. In the keyboard section, change the drop down to "On this Computer". This will fix the issue, and allow the characters to work correctly.

# One Shot Keys

One shot keys are keys that remain active until the next key is pressed, and then are released. This allows you to type keyboard combinations without pressing more than one key at a time. These keys are usually called "Sticky keys" or "Dead keys".

For example, if you define a key as `OSM(MOD_LSFT)`, you can type a capital A character by first pressing and releasing shift, and then pressing and releasing A. Your computer will see the shift key being held the moment shift is pressed, and it will see the shift key being released immediately after A is released.

One shot keys also work as normal modifiers. If you hold down a one shot key and type other keys, your one shot will be released immediately after you let go of the key.

Additionally, hitting keys five times in a short period will lock that key. This applies for both One Shot Modifiers and One Shot Layers, and is controlled by the `ONESHOT_TAP_TOGGLE` define.

You can control the behavior of one shot keys by defining these in `config.h`:

```c
#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped this number of times again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */
```

* `OSM(mod)` - Momentarily hold down *mod*. You must use the `MOD_*` keycodes as shown in [Mod Tap](#mod-tap), not the `KC_*` codes.
* `OSL(layer)` - momentary switch to *layer*.

Sometimes, you want to activate a one-shot key as part of a macro or tap dance routine.  

For one shot layers, you need to call `set_oneshot_layer(LAYER, ONESHOT_START)` on key down, and `set_oneshot_layer(ONESHOT_PRESSED)` on key up. If you want to cancel the oneshot, call `reset_oneshot_layer()`.

For one shot mods, you need to call `set_oneshot_mods(MOD)` to set it, or `clear_oneshot_mods()` to cancel it.

!> If you're having issues with OSM translating over Remote Desktop Connection, this can be fixed by opening the settings, going to the "Local Resources" tap, and in the keyboard section, change the drop down to "On this Computer".  This will fix the issue and allow OSM to function properly over Remote Desktop.

# Tap-Hold Configuration Options

While Tap-Hold options are fantastic, they are not without their issues.  We have tried to configure them with reasonal defaults, but that may still cause issues for some people. 

These options let you modify the behavior of the Tap-Hold keys.

## Permissive Hold

As of [PR#1359](https://github.com/qmk/qmk_firmware/pull/1359/), there is a new `config.h` option:

```c
#define PERMISSIVE_HOLD
```

This makes tap and hold keys (like Mod Tap) work better for fast typist, or for high `TAPPING_TERM` settings. 

If you press a Mod Tap key, tap another key (press and release) and then release the Mod Tap key, all within the tapping term, it will output the "tapping" function for both keys.

For Instance:

- `SHFT_T(KC_A)` Down
- `KC_X` Down
- `KC_X` Up
- `SHFT_T(KC_A)` Up

Normally, if you do all this within the `TAPPING_TERM` (default: 200ms) this will be registered as `ax` by the firmware and host system. With permissive hold enabled, this modifies how this is handled by considering the Mod Tap keys as a Mod if another key is tapped, and would registered as `X` (`SHIFT`+`x`). 

?> If you have `Ignore Mod Tap Interrupt` enabled, as well, this will modify how both work. The regular key has the modifier added if the first key is released first or if both keys are held longer than the `TAPPING_TERM`.

## Ignore Mod Tap Interrupt

To enable this setting, add this to your `config.h`:

```c
#define IGNORE_MOD_TAP_INTERRUPT
```

Similar to Permissive Hold, this alters how the firmware processes input for fast typist. If you press a Mod Tap key, press another key, release the Mod Tap key, and then release the normal key, it would normally output the "tapping" function for both keys. This may not be desirable for rolling combo keys. 

Setting `Ignore Mod Tap Interrupt` requires  holding both keys for the `TAPPING_TERM` to trigger the hold function (the mod).

For Instance:

- `SHFT_T(KC_A)` Down
- `KC_X` Down
- `SHFT_T(KC_A)` Up
- `KC_X` Up

Normally, this would send `X` (`SHIFT`+`x`). With `Ignore Mod Tap Interrupt` enabled, holding both keys are required for the `TAPPING_TERM` to register the hold action. A quick tap will output `ax` in this case, while a hold on both will still output `X`  (`SHIFT`+`x`).


?> __Note__: This only concerns modifiers and not layer switching keys.

?> If you have `Permissive Hold` enabled, as well, this will modify how both work. The regular key has the modifier added if the first key is released first or if both keys are held longer than the `TAPPING_TERM`.

## Tapping Force Hold

To enable `tapping force hold`, add the following to your `config.h`: 

```c
#define TAPPING_FORCE_HOLD
```

When the user holds a key after tap, this repeats the tapped key rather to hold a modifier key.  This allows to use auto repeat for the tapped key.  

Example:

- SHFT_T(KC_A) Down
- SHFT_T(KC_A) Up
- SHFT_T(KC_A) Down
- wait more than tapping term...
- SHFT_T(KC_A) Up

With default settings, `a` will be sent on the first release, then `a` will be sent on the second press allowing the computer to trigger its auto repeat function.

With `TAPPING_FORCE_HOLD`, the second press will be interpreted as a Shift, allowing to use it as a modifier shortly after having used it as a tap.

!> `TAPPING_FORCE_HOLD` will break anything that uses tapping toggles (Such as the `TT` layer keycode, and the One Shot Tapping Toggle).

## Retro Tapping

To enable `retro tapping`, add the following to your `config.h`: 

```c
#define RETRO_TAPPING
```

Holding and releasing a dual function key without pressing another key will result in nothing happening. With retro tapping enabled, releasing the key without pressing another will send the original keycode even if it is outside the tapping term.

For instance, holding and releasing `LT(2, KC_SPACE)` without hitting another key will result in nothing happening. With this enabled, it will send `KC_SPACE` instead.
