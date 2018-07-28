# Advanced Keycodes

Your keymap can include keycodes that are more advanced than normal, for example shifted keys. This page documents the functions that are available to you.

### Assigning Custom Names

People often define custom names using `#define`. For example:

```c
#define FN_CAPS LT(_FL, KC_CAPSLOCK)
#define ALT_TAB LALT(KC_TAB)
```

This will allow you to use `FN_CAPS` and `ALT_TAB` in your `KEYMAP()`, keeping it more readable.

### Limits of These Aliases

Currently, the keycodes able to used with these functions are limited to the [Basic Keycodes](keycodes_basic.md), meaning you can't use keycodes like `KC_TILD`, or anything greater than 0xFF. For a full list of the keycodes able to be used see [Basic Keycodes](keycodes_basic.md).

# Switching and Toggling Layers

These functions allow you to activate layers in various ways. Note that layers are not generally independent layouts -- multiple layers can be activated at once, and it's typical for layers to use `KC_TRNS` to allow keypresses to pass through to lower layers. For a detailed explanation of layers, see [Keymap Overview](keymap.md#keymap-and-layers)

* `DF(layer)` - switches the default layer. The default layer is the always-active base layer that other layers stack on top of. See below for more about the default layer. This might be used to switch from QWERTY to Dvorak layout. (Note that this is a temporary switch that only persists until the keyboard loses power. To modify the default layer in a persistent way requires deeper customization, such as calling the `set_single_persistent_default_layer` function inside of [process_record_user](custom_quantum_functions.md#programming-the-behavior-of-any-keycode).)
* `MO(layer)` - momentarily activates *layer*. As soon as you let go of the key, the layer is deactivated. 
* `LM(layer, mod)` - Momentarily activates *layer* (like `MO`), but with modifier(s) *mod* active. Only supports layers 0-15 and the left modifiers.
* `LT(layer, kc)` - momentarily activates *layer* when held, and sends *kc* when tapped.
* `TG(layer)` - toggles *layer*, activating it if it's inactive and vice versa
* `TO(layer)` - activates *layer* and de-activates all other layers (except your default layer). This function is special, because instead of just adding/removing one layer to your active layer stack, it will completely replace your current active layers, uniquely allowing you to replace higher layers with a lower one. This is activated on keydown (as soon as the key is pressed).
* `TT(layer)` - Layer Tap-Toggle. If you hold the key down, *layer* is activated, and then is de-activated when you let go (like `MO`). If you repeatedly tap it, the layer will be toggled on or off (like `TG`). It needs 5 taps by default, but you can change this by defining `TAPPING_TOGGLE` -- for example, `#define TAPPING_TOGGLE 2` to toggle on just two taps.

# Working with Layers

Care must be taken when switching layers, it's possible to lock yourself into a layer with no way to deactivate that layer (without unplugging your keyboard.) We've created some guidelines to help users avoid the most common problems.

### Beginners

If you are just getting started with QMK you will want to keep everything simple. Follow these guidelines when setting up your layers:

* Setup layer 0 as your default, "base" layer. This is your normal typing layer, and could be whatever layout you want (qwerty, dvorak, colemak, etc.). It's important to set this as the lowest layer since it will typically have most or all of the keyboard's keys defined, so would block other layers from having any effect if it were above them (i.e., had a higher layer number). 
* Arrange your layers in a "tree" layout, with layer 0 as the root. Do not try to enter the same layer from more than one other layer.
* In a layer's keymap, only reference higher-numbered layers. Because layers are processed from the highest-numbered (topmost) active layer down, modifying the state of lower layers can be tricky and error-prone.

### Intermediate Users

Sometimes you need more than one base layer. For example, if you want to switch between QWERTY and Dvorak, switch between layouts for different countries, or switch your layout for different videogames. Your base layers should always be the lowest numbered layers. When you have multiple base layers you should always treat them as mutually exclusive. When one base layer is on the others are off.

### Advanced Users

Once you have a good feel for how layers work and what you can do, you can get more creative. The rules listed in the beginner section will help you be successful by avoiding some of the tricker details but they can be constraining, especially for ultra-compact keyboard users. Understanding how layers work will allow you to use them in more advanced ways.

Layers stack on top of each other in numerical order. When determining what a keypress does, QMK scans the layers from the top down, stopping when it reaches the first active layer that is not set to `KC_TRNS`. As a result if you activate a layer that is numerically lower than your current layer, and your current layer (or another layer that is active and higher than your target layer) has something other than `KC_TRNS`, that is the key that will be sent, not the key on the layer you just activated. This is the cause of most people's "why doesn't my layer get switched" problem.

Sometimes, you might want to switch between layers in a macro or as part of a tap dance routine. `layer_on` activates a layer, and `layer_off` deactivates it. More layer-related functions can be found in [action_layer.h](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/action_layer.h).

# Modifier Keys

These functions allow you to combine a mod with a keycode. When pressed the keydown for the mod will be sent first, and then *kc* will be sent. When released the keyup for *kc* will be sent and then the mod will be sent.

* `LSFT(kc)` or `S(kc)` - applies left Shift to *kc* (keycode)
* `RSFT(kc)` - applies right Shift to *kc*
* `LCTL(kc)` - applies left Control to *kc*
* `RCTL(kc)` - applies right Control to *kc*
* `LALT(kc)` - applies left Alt to *kc*
* `RALT(kc)` - applies right Alt to *kc*
* `LGUI(kc)` - applies left GUI (command/win) to *kc*
* `RGUI(kc)` - applies right GUI (command/win) to *kc*
* `HYPR(kc)` - applies Hyper (all modifiers) to *kc*
* `MEH(kc)`  - applies Meh (all modifiers except Win/Cmd) to *kc*
* `LCAG(kc)` - applies CtrlAltGui to *kc*

You can also chain these, like this:

    LALT(LCTL(KC_DEL)) -- this makes a key that sends Alt, Control, and Delete in a single keypress.

# Shifted Keycodes

The following shortcuts automatically add `LSFT()` to keycodes to get commonly used symbols.

|Key                     |Aliases           |Description        |
|------------------------|------------------|-------------------|
|`KC_TILDE`              |`KC_TILD`         |`~`                |
|`KC_EXCLAIM`            |`KC_EXLM`         |`!`                |
|`KC_AT`                 |                  |`@`                |
|`KC_HASH`               |                  |`#`                |
|`KC_DOLLAR`             |`KC_DLR`          |`$`                |
|`KC_PERCENT`            |`KC_PERC`         |`%`                |
|`KC_CIRCUMFLEX`         |`KC_CIRC`         |`^`                |
|`KC_AMPERSAND`          |`KC_AMPR`         |`&`                |
|`KC_ASTERISK`           |`KC_ASTR`         |`*`                |
|`KC_LEFT_PAREN`         |`KC_LPRN`         |`(`                |
|`KC_RIGHT_PAREN`        |`KC_RPRN`         |`)`                |
|`KC_UNDERSCORE`         |`KC_UNDS`         |`_`                |
|`KC_PLUS`               |                  |`+`                |
|`KC_LEFT_CURLY_BRACE`   |`KC_LCBR`         |`{`                |
|`KC_RIGHT_CURLY_BRACE`  |`KC_RCBR`         |`}`                |
|`KC_PIPE`               |                  |<code>&#124;</code>|
|`KC_COLON`              |`KC_COLN`         |`:`                |
|`KC_DOUBLE_QUOTE`       |`KC_DQT`/`KC_DQUO`|`"`                |
|`KC_LEFT_ANGLE_BRACKET` |`KC_LT`/`KC_LABK` |`<`                |
|`KC_RIGHT_ANGLE_BRACKET`|`KC_GT`/`KC_RABK` |`>`                |
|`KC_QUESTION`           |`KC_QUES`         |`?`                |

# Mod Tap

`MT(mod, kc)` - is *mod* (modifier key - MOD_LCTL, MOD_LSFT) when held, and *kc* when tapped. In other words, you can have a key that sends Esc (or the letter O or whatever) when you tap it, but works as a Control key or a Shift key when you hold it down.

These are the values you can use for the `mod` in `MT()` and `OSM()`:

  * MOD_LCTL
  * MOD_LSFT
  * MOD_LALT
  * MOD_LGUI
  * MOD_RCTL
  * MOD_RSFT
  * MOD_RALT
  * MOD_RGUI
  * MOD_HYPR
  * MOD_MEH

These can also be combined like `MOD_LCTL | MOD_LSFT` e.g. `MT(MOD_LCTL | MOD_LSFT, KC_ESC)` which would activate Control and Shift when held, and send Escape when tapped.

We've added shortcuts to make common modifier/tap (mod-tap) mappings more compact:

  * `CTL_T(kc)` - is LCTL when held and *kc* when tapped
  * `SFT_T(kc)` - is LSFT when held and *kc* when tapped
  * `ALT_T(kc)` - is LALT when held and *kc* when tapped
  * `ALGR_T(kc)` - is AltGr when held and *kc* when tapped
  * `GUI_T(kc)` - is LGUI when held and *kc* when tapped
  * `ALL_T(kc)` - is Hyper (all mods) when held and *kc* when tapped. To read more about what you can do with a Hyper key, see [this blog post by Brett Terpstra](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)
  * `LCAG_T(kc)` - is CtrlAltGui when held and *kc* when tapped
  * `MEH_T(kc)` - is like Hyper, but not as cool -- does not include the Cmd/Win key, so just sends Alt+Ctrl+Shift.

?> Due to the way that keycodes are structured, any modifiers specified as part of `kc`, such as `LCTL()` or `KC_LPRN`, will only activate when held instead of tapped.

?> Additionally, if there is at least one right-handed modifier, any other modifiers in a chain of functions will turn into their right-handed equivalents, so it is not possible to "mix and match" the two.

# One Shot Keys

One shot keys are keys that remain active until the next key is pressed, and then are released. This allows you to type keyboard combinations without pressing more than one key at a time. These keys are usually called "Sticky keys" or "Dead keys".

For example, if you define a key as `OSM(MOD_LSFT)`, you can type a capital A character by first pressing and releasing shift, and then pressing and releasing A. Your computer will see the shift key being held the moment shift is pressed, and it will see the shift key being released immediately after A is released.

One shot keys also work as normal modifiers. If you hold down a one shot key and type other keys, your one shot will be released immediately after you let go of the key.

You can control the behavior of one shot keys by defining these in `config.h`:

```c
#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped this number of times again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */
```

* `OSM(mod)` - Momentarily hold down *mod*. You must use the `MOD_*` keycodes as shown in [Mod Tap](#mod-tap), not the `KC_*` codes.
* `OSL(layer)` - momentary switch to *layer*.

Sometimes, you want to activate a one-shot layer as part of a macro or tap dance routine. To do this, you need to call `set_oneshot_layer(LAYER, ONESHOT_START)` on key down, and `set_oneshot_layer(ONESHOT_PRESSED)` on key up. If you want to cancel the oneshot, call `reset_oneshot_layer()`. For more complicated actions, take a look at the oneshot implementation in [`process_record`](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/action.c#L429).

If you're having issues with OSM translating over Remote Desktop Connection, this can be fixed by opening the settings, going to the "Local Resources" tap, and in the keyboard section, change the drop down to "On this Computer".  This will fix the issue and allow OSM to function properly over Remote Desktop.

# Permissive Hold

As of [PR#1359](https://github.com/qmk/qmk_firmware/pull/1359/), there is a new `config.h` option:

```
#define PERMISSIVE_HOLD
```

This makes it easier for fast typists to use dual-function keys. Without this, if you let go of a held key inside the tapping term, it won't register.

Example: (Tapping Term = 200ms)

- SHFT_T(KC_A) Down
- KC_X Down
- KC_X Up
- SHFT_T(KC_A) Up

With defaults, if above is typed within tapping term, this will emit `ax`. With permissive hold, if above is typed within tapping term, this will emit `X` (so, Shift+X).

# Mod tap interrupt

When a dual role key used for a modifier is quickly followed by another keys, it is interpreted as held even before the tapping term elapsed.  This is a problem if a key is used for example inside a rolling combo because the second key will be pressed before the first key is released.

For example, when trying to type the rolling combo "zx" and z being configured to send Ctrl when hold, z rapidly followed by x actually sends Ctrl-x. That's bad.

You can disable this behavior by defining `IGNORE_MOD_TAP_INTERRUPT` in `config.h`.

Note that this only concerns modifiers and not layer switching keys.

# Hold after tap

When the user holds a key after tap, this repeats the tapped key rather to hold a modifier key.  This allows to use auto repeat for the tapped key.  If you prefer to hold a modifier instead, define `TAPPING_FORCE_HOLD` in `config.h`.

Example:

- SHFT_T(KC_A) Down
- SHFT_T(KC_A) Up
- SHFT_T(KC_A) Down
- wait more than tapping term...
- SHFT_T(KC_A) Up

With default settings, `a` will be sent on the first release, then `a` will be sent on the second press allowing the computer to trigger its auto repeat function.

With `TAPPING_FORCE_HOLD`, the second press will be interpreted as a Shift, allowing to use it as a modifier shortly after having used it as a tap.

!> `TAPPING_FORCE_HOLD` will break anything that uses tapping toggles (Such as the `TT` layer keycode, and the One Shot Tapping Toggle).

# Retro Tapping

When you hold a dual function key, and haven't pressed anything when you release the key, normally nothing happens.  However, if you enable this, if you release the key without pressing another key, it will send the original key, even if it is outside of the tapping term. 

For instance, if you're using `LT(2, KC_SPACE)`, if you hold the key, don't hit anything else and then release it, normally, nothing happens. But with `RETRO_TAPPING` defined in your `config.h`, it will send `KC_SPACE`. 
