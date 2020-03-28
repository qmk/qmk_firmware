# Layers :id=layers

One of the most powerful and well used features of QMK Firmware is the ability to use layers.  For most people, this amounts to a function key that allows for different keys, much like what you would see on a laptop or tablet keyboard. 

For a detailed explanation of how the layer stack works, checkout [Keymap Overview](keymap.md#keymap-and-layers).

## Switching and Toggling Layers :id=switching-and-toggling-layers

These functions allow you to activate layers in various ways. Note that layers are not generally independent layouts -- multiple layers can be activated at once, and it's typical for layers to use `KC_TRNS` to allow keypresses to pass through to lower layers. When using momentary layer switching with MO(), LM(), TT(), or LT(), make sure to leave the key on the above layers transparent or it may not work as intended.

* `DF(layer)` - switches the default layer. The default layer is the always-active base layer that other layers stack on top of. See below for more about the default layer. This might be used to switch from QWERTY to Dvorak layout. (Note that this is a temporary switch that only persists until the keyboard loses power. To modify the default layer in a persistent way requires deeper customization, such as calling the `set_single_persistent_default_layer` function inside of [process_record_user](custom_quantum_functions.md#programming-the-behavior-of-any-keycode).)
* `MO(layer)` - momentarily activates *layer*. As soon as you let go of the key, the layer is deactivated. 
* `LM(layer, mod)` - Momentarily activates *layer* (like `MO`), but with modifier(s) *mod* active. Only supports layers 0-15 and the left modifiers: `MOD_LCTL`, `MOD_LSFT`, `MOD_LALT`, `MOD_LGUI` (note the use of `MOD_` constants instead of `KC_`). These modifiers can be combined using bitwise OR, e.g. `LM(_RAISE, MOD_LCTL | MOD_LALT)`.
* `LT(layer, kc)` - momentarily activates *layer* when held, and sends *kc* when tapped. Only supports layers 0-15.
* `OSL(layer)` - momentarily activates *layer* until the next key is pressed. See [One Shot Keys](one_shot_keys.md) for details and additional functionality.
* `TG(layer)` - toggles *layer*, activating it if it's inactive and vice versa
* `TO(layer)` - activates *layer* and de-activates all other layers (except your default layer). This function is special, because instead of just adding/removing one layer to your active layer stack, it will completely replace your current active layers, uniquely allowing you to replace higher layers with a lower one. This is activated on keydown (as soon as the key is pressed).
* `TT(layer)` - Layer Tap-Toggle. If you hold the key down, *layer* is activated, and then is de-activated when you let go (like `MO`). If you repeatedly tap it, the layer will be toggled on or off (like `TG`). It needs 5 taps by default, but you can change this by defining `TAPPING_TOGGLE` -- for example, `#define TAPPING_TOGGLE 2` to toggle on just two taps.

### Caveats :id=caveats

Currently, `LT()` and `MT()` are limited to the [Basic Keycode set](keycodes_basic.md), meaning you can't use keycodes like `LCTL()`, `KC_TILD`, or anything greater than `0xFF`. Specifically, dual function keys like `LT` and `MT` use a 16 bit keycode. 4 bits are used for the function identifier, the next 12 are divided into the parameters. Layer Tap uses 4 bits for the layer (and is why it's limited to layers 0-16, actually), while Mod Tap does the same, 4 bits for the identifier, 4 bits for which mods are used, and all of them use 8 bits for the keycode. Because of this, the keycode used is limited to `0xFF` (0-255), which are the basic keycodes only. 

Expanding this would be complicated, at best. Moving to a 32-bit keycode would solve a lot of this, but would double the amount of space that the keymap matrix uses. And it could potentially cause issues, too. If you need to apply modifiers to your tapped keycode, [Tap Dance](feature_tap_dance.md#example-5-using-tap-dance-for-advanced-mod-tap-and-layer-tap-keys) can be used to accomplish this.

Additionally, if at least one right-handed modifier is specified in a Mod Tap or Layer Tap, it will cause all modifiers specified to become right-handed, so it is not possible to mix and match the two.

## Working with Layers :id=working-with-layers

Care must be taken when switching layers, it's possible to lock yourself into a layer with no way to deactivate that layer (without unplugging your keyboard.) We've created some guidelines to help users avoid the most common problems.

### Beginners :id=beginners

If you are just getting started with QMK you will want to keep everything simple. Follow these guidelines when setting up your layers:

* Setup layer 0 as your default, "base" layer. This is your normal typing layer, and could be whatever layout you want (qwerty, dvorak, colemak, etc.). It's important to set this as the lowest layer since it will typically have most or all of the keyboard's keys defined, so would block other layers from having any effect if it were above them (i.e., had a higher layer number). 
* Arrange your layers in a "tree" layout, with layer 0 as the root. Do not try to enter the same layer from more than one other layer.
* In a layer's keymap, only reference higher-numbered layers. Because layers are processed from the highest-numbered (topmost) active layer down, modifying the state of lower layers can be tricky and error-prone.

### Intermediate Users :id=intermediate-users

Sometimes you need more than one base layer. For example, if you want to switch between QWERTY and Dvorak, switch between layouts for different countries, or switch your layout for different videogames. Your base layers should always be the lowest numbered layers. When you have multiple base layers you should always treat them as mutually exclusive. When one base layer is on the others are off.

### Advanced Users :id=advanced-users

Once you have a good feel for how layers work and what you can do, you can get more creative. The rules listed in the beginner section will help you be successful by avoiding some of the tricker details but they can be constraining, especially for ultra-compact keyboard users. Understanding how layers work will allow you to use them in more advanced ways.

Layers stack on top of each other in numerical order. When determining what a keypress does, QMK scans the layers from the top down, stopping when it reaches the first active layer that is not set to `KC_TRNS`. As a result if you activate a layer that is numerically lower than your current layer, and your current layer (or another layer that is active and higher than your target layer) has something other than `KC_TRNS`, that is the key that will be sent, not the key on the layer you just activated. This is the cause of most people's "why doesn't my layer get switched" problem.

Sometimes, you might want to switch between layers in a macro or as part of a tap dance routine. `layer_on` activates a layer, and `layer_off` deactivates it. More layer-related functions can be found in [action_layer.h](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/action_layer.h).

## Functions :id=functions

There are a number of functions (and variables) related to how you can use or manipulate the layers.

|Function                                      |Description                                                                                              |
|----------------------------------------------|---------------------------------------------------------------------------------------------------------|
| `layer_state_set(layer_mask)`                | Directly sets the layer state (recommended, do not use unless you know what you are doing).             |
| `layer_clear()`                              | Clears all layers (turns them all off).                                                                 |
| `layer_move(layer)`                          | Turns specified layer on, and all other layers off.                                                     |
| `layer_on(layer)`                            | Turns specified layer on, leaves all other layers in existing state.                                    |
| `layer_off(layer)`                           | Turns specified layer off, leaves all other layers in existing state.                                   |
| `layer_invert(layer)`                        | Interverts/toggles the state of the specified layer                                                     |
| `layer_or(layer_mask)`                       | Turns on layers based on matching bits between specifed layer and existing layer state.                 |
| `layer_and(layer_mask)`                      | Turns on layers based on matching enabled bits between specifed layer and existing layer state.         |
| `layer_xor(layer_mask)`                      | Turns on layers based on non-matching bits between specifed layer and existing layer state.             |
| `layer_debug(layer_mask)`                    | Prints out the current bit mask and highest active layer to debugger console.                           |
| `default_layer_set(layer_mask)`              | Directly sets the default layer state (recommended, do not use unless you know what you are doing).     |
| `default_layer_or(layer_mask)`               | Turns on layers based on matching bits between specifed layer and existing default layer state.         |
| `default_layer_and(layer_mask)`              | Turns on layers based on matching enabled bits between specifed layer and existing default layer state. |
| `default_layer_xor(layer_mask)`              | Turns on layers based on non-matching bits between specifed layer and existing default layer state.     |
| `default_layer_debug(layer_mask)`            | Prints out the current bit mask and highest active default layer to debugger console.                   |
| [`set_single_persistent_default_layer(layer)`](ref_functions.md#setting-the-persistent-default-layer) | Sets the default layer and writes it to persistent memory (EEPROM).  |
| [`update_tri_layer(x, y, z)`](ref_functions.md#update_tri_layerx-y-z) | Checks if layers `x` and `y` are both on, and sets `z` based on that (on if both on, otherwise off). |
| [`update_tri_layer_state(state, x, y, z)`](ref_functions.md#update_tri_layer_statestate-x-y-z) | Does the same as `update_tri_layer(x, y, z)`, but from `layer_state_set_*` functions. |

In addition to the functions that you can call, there are a number of callback functions that get called every time the layer changes. This passes the layer state to the function, where it can be read or modified.

|Callback                                             |Description                                                                             |
|-----------------------------------------------------|----------------------------------------------------------------------------------------|
| `layer_state_set_kb(layer_state_t state)`           | Callback for layer functions, for keyboard.                                            |
| `layer_state_set_user(layer_state_t state)`         | Callback for layer functions, for users.                                               |
| `default_layer_state_set_kb(layer_state_t state)`   | Callback for default layer functions, for keyboard. Called on keyboard initialization. |
| `default_layer_state_set_user(layer_state_t state)` | Callback for default layer functions, for users. Called on keyboard initialization.    |

?> For additional details on how you can use these callbacks, check out the [Layer Change Code](custom_quantum_functions.md#layer-change-code) document.

It is also possible to check the state of a particular layer using the following functions and macros.

|Function/macro                             |Description                                                                                                           |
|-------------------------------------------|----------------------------------------------------------------------------------------------------------------------|
| `layer_state_cmp(cmp_layer_state, layer)` | Checks `cmp_layer_state` to see if the specified `layer` is enabled. This is meant for use with the layer callbacks. |
| `layer_state_is(layer)`                   | Checks if the specified `layer` is currently enabled globally.                                                       |
| `IS_LAYER_ON(layer)`                      | Checks if the specified `layer` is currently enabled globally (convenience for `layer_state_is`).                    |
| `IS_LAYER_OFF(layer)`                     | Checks if the specified `layer` is currently disabled globally (convenience for `!layer_state_is`).                  |
| `IS_LAYER_ON_STATE(state, layer)`         | Checks if the specified `layer` is enabled in `state` (convenience for `layer_state_cmp`). Used in layer callbacks.  |
| `IS_LAYER_OFF_STATE(state, layer)`        | Checks if the specified `layer` is disabled in `state` (convenience for `!layer_state_cmp`). Used in layer callbacks.|
