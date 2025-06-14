# Key Overrides {#key-overrides}

Key overrides allow you to override modifier-key combinations to send a different modifier-key combination or perform completely custom actions. Don't want `shift` + `1` to type `!` on your computer? Use a key override to make your keyboard type something different when you press `shift` + `1`. The general behavior is like this: If `modifiers w` + `key x` are pressed, replace these keys with `modifiers y` + `key z` in the keyboard report.

You can use key overrides in a similar way to momentary layer/fn keys to activate custom keycodes/shortcuts, with a number of benefits: You completely keep the original use of the modifier keys, while being able to save space by removing fn keys from your keyboard. You can also easily configure _combinations of modifiers_ to trigger different actions than individual modifiers, and much more. The possibilities are quite vast and this documentation contains a few examples for inspiration throughout.

##### A few more examples to get started: You could use key overrides to...
- Send `brightness up/down` when pressing `ctrl` + `volume up/down`.
- Send `delete` when pressing `shift` + `backspace`.
- Create custom shortcuts or change existing ones: E.g. Send `ctrl`+`shift`+`z` when `ctrl`+`y` is pressed.
- Run custom code when `ctrl` + `alt` + `esc` is pressed.

## Setup {#setup}

To enable this feature, you need to add `KEY_OVERRIDE_ENABLE = yes` to your `rules.mk`.

Then, in your `keymap.c` file, you'll need to define the array `key_overrides`, which defines all key overrides to be used. Each override is a value of type `key_override_t`. The array `key_overrides`contains pointers to `key_override_t` values (`const key_override_t **`).

## Creating Key Overrides {#creating-key-overrides}

The `key_override_t` struct has many options that allow you to precisely tune your overrides. The full reference is shown below. Instead of manually creating a `key_override_t` value, it is recommended to use these dedicated initializers:

#### `ko_make_basic(modifiers, key, replacement)`
Returns a `key_override_t`, which sends `replacement` (can be a key-modifier combination), when `key` and `modifiers` are all pressed down. This override still activates if any additional modifiers not specified in `modifiers` are also pressed down. See `ko_make_with_layers_and_negmods` to customize this behavior.

#### `ko_make_with_layers(modifiers, key, replacement, layers)`
Additionally takes a bitmask `layers` that defines on which layers the override is used.

#### `ko_make_with_layers_and_negmods(modifiers, key, replacement, layers, negative_mods)`
Additionally takes a bitmask `negative_mods` that defines which modifiers may not be pressed for this override to activate.

#### `ko_make_with_layers_negmods_and_options(modifiers, key, replacement, layers, negative_mods, options)`
Additionally takes a bitmask `options` that specifies additional options. See `ko_option_t` for available options.

For more customization possibilities, you may directly create a `key_override_t`, which allows you to customize even more behavior. Read further below for details and examples.

## Simple Example {#simple-example}

This shows how the mentioned example of sending `delete` when `shift` + `backspace` are pressed is realized:

```c
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&delete_key_override
};
```

## Intermediate Difficulty Examples {#intermediate-difficulty-examples}

### Media Controls & Screen Brightness {#media-controls-amp-screen-brightness}

In this example a single key is configured to control media, volume and screen brightness by using key overrides.

- The key is set to send `play/pause` in the keymap.

The following key overrides will be configured:

- `Ctrl` + `play/pause` will send `next track`.
- `Ctrl` + `Shift` + `play/pause` will send `previous track`. 
- `Alt` + `play/pause` will send `volume up`. 
- `Alt` + `Shift` + `play/pause` will send `volume down`.
- `Ctrl` + `Alt` + `play/pause` will send `brightness up`.
- `Ctrl` + `Alt` + `Shift` + `play/pause` will send `brightness down`.


```c
const key_override_t next_track_override = 
	ko_make_with_layers_negmods_and_options(
   		MOD_MASK_CTRL,       // Trigger modifiers: ctrl
    	KC_MPLY,             // Trigger key: play/pause
    	KC_MNXT,             // Replacement key
    	~0,                  // Activate on all layers
    	MOD_MASK_SA,         // Do not activate when shift or alt are pressed
    	ko_option_no_reregister_trigger); // Specifies that the play key is not registered again after lifting ctrl
    
const key_override_t prev_track_override = ko_make_with_layers_negmods_and_options(MOD_MASK_CS, KC_MPLY,
											KC_MPRV, ~0, MOD_MASK_ALT, ko_option_no_reregister_trigger);

const key_override_t vol_up_override = ko_make_with_layers_negmods_and_options(MOD_MASK_ALT, KC_MPLY,
											KC_VOLU, ~0, MOD_MASK_CS, ko_option_no_reregister_trigger);

const key_override_t vol_down_override = ko_make_with_layers_negmods_and_options(MOD_MASK_SA, KC_MPLY,
											KC_VOLD, ~0, MOD_MASK_CTRL, ko_option_no_reregister_trigger);

const key_override_t brightness_up_override = ko_make_with_layers_negmods_and_options(MOD_MASK_CA, KC_MPLY,
											KC_BRIU, ~0, MOD_MASK_SHIFT, ko_option_no_reregister_trigger);

const key_override_t brightness_down_override = ko_make_basic(MOD_MASK_CSA, KC_MPLY, KC_BRID);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&next_track_override,
	&prev_track_override,
	&vol_up_override,
	&vol_down_override,
	&brightness_up_override,
	&brightness_down_override
};
```

### Flexible macOS-friendly Grave Escape {#flexible-macos-friendly-grave-escape}
The [Grave Escape feature](grave_esc) is limited in its configurability and has [bugs when used on macOS](grave_esc#caveats). Key overrides can be used to achieve a similar functionality as Grave Escape, but with more customization and without bugs on macOS.

```c
// Shift + esc = ~
const key_override_t tilde_esc_override = ko_make_basic(MOD_MASK_SHIFT, KC_ESC, S(KC_GRV));

// GUI + esc = `
const key_override_t grave_esc_override = ko_make_basic(MOD_MASK_GUI, KC_ESC, KC_GRV);

const key_override_t *key_overrides[] = {
	&tilde_esc_override,
	&grave_esc_override
};
```

In addition to not encountering unexpected bugs on macOS, you can also change the behavior as you wish. Instead setting `GUI` + `ESC` = `` ` `` you may change it to an arbitrary other modifier, for example `Ctrl` + `ESC` = `` ` ``.

## Advanced Examples {#advanced-examples}
### Modifiers as Layer Keys {#modifiers-as-layer-keys}

Do you really need a dedicated key to toggle your fn layer? With key overrides, perhaps not. This example shows how you can configure to use `rGUI` + `rAlt` (right GUI and right alt) to access a momentary layer like an fn layer. With this you completely eliminate the need to use a dedicated layer key. Of course the choice of modifier keys can be changed as needed, `rGUI` + `rAlt` is just an example here. 

```c
// This is called when the override activates and deactivates. Enable the fn layer on activation and disable on deactivation
bool momentary_layer(bool key_down, void *layer) {
    if (key_down) {
        layer_on((uint8_t)(uintptr_t)layer);
    } else {
        layer_off((uint8_t)(uintptr_t)layer);
    }

    return false;
}

const key_override_t fn_override = {.trigger_mods          = MOD_BIT(KC_RGUI) | MOD_BIT(KC_RALT),                       //
                                   .layers                 = ~(1 << LAYER_FN),                                          //
                                   .suppressed_mods        = MOD_BIT(KC_RGUI) | MOD_BIT(KC_RALT),                       //
                                   .options                = ko_option_no_unregister_on_other_key_down,                 //
                                   .negative_mod_mask      = (uint8_t) ~(MOD_BIT(KC_RGUI) | MOD_BIT(KC_RALT)),          //
                                   .custom_action          = momentary_layer,                                           //
                                   .context                = (void *)LAYER_FN,                                          //
                                   .trigger                = KC_NO,                                                     //
                                   .replacement            = KC_NO,                                                     //
                                   .enabled                = NULL};
```

## Keycodes {#keycodes}

|Keycode                 |Aliases  |Description           |
|------------------------|---------|----------------------|
|`QK_KEY_OVERRIDE_TOGGLE`|`KO_TOGG`|Toggle key overrides  |
|`QK_KEY_OVERRIDE_ON`    |`KO_ON`  |Turn on key overrides |
|`QK_KEY_OVERRIDE_OFF`   |`KO_OFF` |Turn off key overrides|

## Reference for `key_override_t` {#reference-for-key_override_t}

Advanced users may need more customization than what is offered by the simple `ko_make` initializers. For this, directly create a `key_override_t` value and set all members. Below is a reference for all members of `key_override_t`.

| Member                                                 | Description                                                                                                                                                                                                                                                                                                                                                                                                                                        |
|--------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `uint16_t trigger`                                     | The non-modifier keycode that triggers the override. This keycode, and the necessary modifiers (`trigger_mods`) must be pressed to activate this override. Set this to the keycode of the key that should activate the override. Set to `KC_NO` to require only the necessary modifiers to be pressed and no non-modifier.                                                                                                                                                                                                                                                                                                                                |
| `uint8_t trigger_mods`                            | Which mods need to be down for activation. If both sides of a modifier are set (e.g. left ctrl and right ctrl) then only one is required to be pressed (e.g. left ctrl suffices). Use the `MOD_MASK_XXX` and `MOD_BIT()` macros for this.                                                                                                                                                                                                                                                                            |
| `layer_state_t layers`                                 | This is a BITMASK (!), defining which layers this override applies to. To use this override on layer i set the ith bit `(1 << i)`.                                                                                                                                                                                                                                                                                                                   |
| `uint8_t negative_mod_mask`                       | Which modifiers cannot be down. It must hold that `(active_modifiers & negative_mod_mask) == 0`, otherwise the key override will not be activated. An active override will be deactivated once this is no longer true.                                                                                                                                                                                                                                                                                                     |
| `uint8_t suppressed_mods`                              | Modifiers to 'suppress' while the override is active. To suppress a modifier means that even though the modifier key is held down, the host OS sees the modifier as not pressed. Can be used to suppress the trigger modifiers, as a trivial example.                                                                                                                                                                                                                                                                                                                                            |
| `uint16_t replacement`                                 | The complex keycode to send as replacement when this override is triggered. This can be a simple keycode, a key-modifier combination (e.g. `C(KC_A)`), or `KC_NO` (to register no replacement keycode). Use in combination with suppressed_mods to get the correct modifiers to be sent.                                                                                                                                                                                                                 |
| `ko_option_t options`             | Options controlling the behavior of the override, such as what actions are allowed to activate the override.                                                                                                                                                                                                                                                                                                                |
| `bool (*custom_action)(bool activated, void *context)` | If not NULL, this function will be called right before the replacement key is registered, along with the provided context and a flag indicating whether the override was activated or deactivated. This function allows you to run some custom actions for specific key overrides. If you return `false`, the replacement key is not registered/unregistered as it would normally. Return `true` to register and unregister the override normally. |
| `void *context`                                        | A context that will be passed to the custom action function.                                                                                                                                                                                                                                                                                                                                                                        |
| `bool *enabled`                                        | If this points to false this override will not be used. Set to NULL to always have this override enabled.                                                                                                                                                                                                                                                                                                                                          |

## Reference for `ko_option_t` {#reference-for-ko_option_t}

Bitfield with various options controlling the behavior of a key override.

| Value                                    | Description                                                                                                                                                                                                            |
|------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `ko_option_activation_trigger_down`      | Allow activating when the trigger key is pressed down.                                                                                                                                                                 |
| `ko_option_activation_required_mod_down` | Allow activating when a necessary modifier is pressed down.                                                                                                                                                                                     |
| `ko_option_activation_negative_mod_up`   | Allow activating when a negative modifier is released.                                                                                                                                                                 |
| `ko_option_one_mod`                      | If set, any of the modifiers in `trigger_mods` will be enough to activate the override (logical OR of modifiers). If not set, all the modifiers in `trigger_mods` have to be pressed (logical AND of modifiers). |
| `ko_option_no_unregister_on_other_key_down`    |  If set, the override will not deactivate when another key is pressed down. Use only if you really know you need this.                                                                                                                          |
| `ko_option_no_reregister_trigger`        | If set, the trigger key will never be registered again after the override is deactivated.                                                                                                                              |
| `ko_options_default`                     | The default options used by the `ko_make_xxx` functions                                                                                                                                                                  |

## For Advanced Users: Inner Workings {#for-advanced-users-inner-workings}

This section explains how a key override works in detail, explaining where each member of `key_override_t` comes into play. Understanding this is essential to be able to take full advantage of all the options offered by key overrides.

#### Activation {#activation}

When the necessary keys are pressed (`trigger_mods` + `trigger`), the override is 'activated' and the replacement key is registered in the keyboard report (`replacement`), while the `trigger` key is removed from the keyboard report. The trigger modifiers may also be removed from the keyboard report upon activation of an override (`suppressed_mods`). The override will not activate if any of the `negative_modifiers` are pressed.

Overrides can activate in three different cases:

1. The trigger key is pressed down and necessary modifiers are already down.
2. A necessary modifier is pressed down, while the trigger key and other necessary modifiers are already down.
3. A negative modifier is released, while all necessary modifiers and the trigger key are already down.

Use the `option` member to customize which of these events are allowed to activate your overrides (default: all three).

In any case, a key override can only activate if the `trigger` key is the _last_ non-modifier key that was pressed down. This emulates the behavior of how standard OSes (macOS, Windows, Linux) handle normal key input (to understand: Hold down `a`, then also hold down `b`, then hold down `shift`; `B` will be typed but not `A`).

#### Deactivation {#deactivation}

An override is 'deactivated' when one of the trigger keys (`trigger_mods`, `trigger`) is lifted, another non-modifier key is pressed down, or one of the `negative_modifiers` is pressed down. When an override deactivates, the `replacement` key is removed from the keyboard report, while the `suppressed_mods` that are still held down are re-added to the keyboard report. By default, the `trigger` key is re-added to the keyboard report if it is still held down and no other non-modifier key has been pressed since. This again emulates the behavior of how standard OSes handle normal key input (To understand: hold down `a`, then also hold down `b`, then also `shift`, then release `b`; `A` will not be typed even though you are holding the `a` and `shift` keys). Use the `option` field `ko_option_no_reregister_trigger` to prevent re-registering the trigger key in all cases.

#### Key Repeat Delay {#key-repeat-delay}

A third way in which standard OS-handling of modifier-key input is emulated in key overrides is with a ['key repeat delay'](https://www.dummies.com/computers/pcs/set-your-keyboards-repeat-delay-and-repeat-rate/). To explain what this is, let's look at how normal keyboard input is handled by mainstream OSes again: If you hold down `a`, followed by `shift`, you will see the letter `a` is first typed, then for a short moment nothing is typed and then repeating `A`s are typed. Take note that, although shift is pressed down just after `a` is pressed, it takes a moment until `A` is typed. This is caused by the aforementioned key repeat delay, and it is a feature that prevents unwanted repeated characters from being typed.

This applies equally to releasing a modifier: When you hold `shift`, then press `a`, the letter `A` is typed. Now if you release `shift` first, followed by `a` shortly after, you will not see the letter `a` being typed, even though for a short moment of time you were just holding down the key `a`. This is because no modified characters are typed until the key repeat delay has passed.

 This exact behavior is implemented in key overrides as well: If a key override for `shift` + `a` = `b` exists, and `a` is pressed and held, followed by `shift`, you will not immediately see the letter `b` being typed. Instead, this event is deferred for a short moment, until the key repeat delay has passed, measured from the moment when the trigger key (`a`) was pressed down.

The duration of the key repeat delay is controlled with the `KEY_OVERRIDE_REPEAT_DELAY` macro. Define this value in your `config.h` file to change it. It is 500ms by default.


## Difference to Combos {#difference-to-combos}

Note that key overrides are very different from [combos](combo). Combos require that you press down several keys almost _at the same time_ and can work with any combination of non-modifier keys. Key overrides work like keyboard shortcuts (e.g. `ctrl` + `z`): They take combinations of _multiple_ modifiers and _one_ non-modifier key to then perform some custom action. Key overrides are implemented with much care to behave just like normal keyboard shortcuts would in regards to the order of pressed keys, timing, and interaction with other pressed keys. There are a number of optional settings that can be used to really fine-tune the behavior of each key override as well. Using key overrides also does not delay key input for regular key presses, which inherently happens in combos and may be undesirable.

## Solution to the problem of flashing modifiers {#neutralize-flashing-modifiers}

If the programs you use bind an action to taps of modifier keys (e.g. tapping left GUI to bring up the applications menu or tapping left Alt to focus the menu bar), you may find that using key overrides with suppressed mods falsely triggers those actions. To counteract this, you can define a `DUMMY_MOD_NEUTRALIZER_KEYCODE` in `config.h` that will get sent in between the register and unregister events of a suppressed modifier. That way, the programs on your computer will no longer interpret the mod suppression induced by key overrides as a lone tap of a modifier key and will thus not falsely trigger the undesired action.

Naturally, for this technique to be effective, you must choose a `DUMMY_MOD_NEUTRALIZER_KEYCODE` for which no keyboard shortcuts are bound to. Recommended values are: `KC_RIGHT_CTRL` or `KC_F18`. 
Please note that `DUMMY_MOD_NEUTRALIZER_KEYCODE` must be a basic, unmodified, HID keycode so values like `KC_NO`, `KC_TRANSPARENT` or `KC_PIPE` aka `S(KC_BACKSLASH)` are not permitted.

By default, only left Alt and left GUI are neutralized. If you want to change the list of applicable modifier masks, use the following in your `config.h`:

```c
#define MODS_TO_NEUTRALIZE { <mod_mask_1>, <mod_mask_2>, ... }
```

Examples:

```c
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_RIGHT_CTRL

// Neutralize left alt and left GUI (Default value)
#define MODS_TO_NEUTRALIZE { MOD_BIT(KC_LEFT_ALT), MOD_BIT(KC_LEFT_GUI) }

// Neutralize left alt, left GUI, right GUI and left Control+Shift
#define MODS_TO_NEUTRALIZE { MOD_BIT(KC_LEFT_ALT), MOD_BIT(KC_LEFT_GUI), MOD_BIT(KC_RIGHT_GUI), MOD_BIT(KC_LEFT_CTRL)|MOD_BIT(KC_LEFT_SHIFT) }
```

::: warning
Do not use `MOD_xxx` constants like `MOD_LSFT` or `MOD_RALT`, since they're 5-bit packed bit-arrays while `MODS_TO_NEUTRALIZE` expects a list of 8-bit packed bit-arrays. Use `MOD_BIT(<kc>)` or `MOD_MASK_xxx` instead.
:::
