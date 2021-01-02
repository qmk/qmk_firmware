# Key Overrides

With key overrides you can define custom actions for arbitrary modifier + key combinations: If `modifiers w` + `key x` are pressed, replace these keys with `modifiers y` + `key z` in the keyboard report. At the core, key overrides give you the power of layers without having to use dedicated layer keys, allowing you to use modifier keys instead (and combinations thereof).

For example, you may configure a key override to send the `delete` key when `shift` + `backspace` are pressed together, or that your volume keys become screen brightness keys when holding `ctrl`. The possibilities are quite vast and this documentation contains a few examples for inspiration.

## Setup

To enable this feature, you need to add `KEY_OVERRIDE_ENABLE = yes` to your `rules.mk`.

Then, in your `keymap.c` file, you'll need to define the array `key_overrides`, which defines all available overrides.  Each override is a value of type `key_override_t`. The array `key_overrides` is `NULL`-terminated and contains pointers to `key_override_t` values.

## Creating Key Overrides

The `key_override_t` struct has many options that allow you to precicely tune your overrides. The full reference is shown below. However, `key_override_t` is quite complex, and to make things simpler, it is suggested to use one of the following three simplified initializers to create key overrides:

#### `ko_make_basic(modifiers, key, replacement)`
Sends `replacement` (can be a key-modifer combination), when `key` is pressed while `modifiers` are pressed down.

#### `ko_make_with_layers(modifiers, key, replacement, layers)`
Additionally takes a bitmask `layers` that defines on which layers the override is used.

#### `ko_make_with_layers_and_negmods(modifiers, key, replacement, layers, negative_mods)`
Additionally takes a bitmask `negative_mods` that defines which modifiers may not be pressed for this override to activate.

#### `ko_make_with_layers_negmods_and_options(modifiers, key, replacement, layers, negative_mods, options)`
Additionally takes a bitmask `options` that specifies additional options. See `ko_option_t` for available options.

## Simple Example

This shows how the mentioned example of sending `delete` when `shift` + `backspace` are pressed is realized:

```c
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPACE, KC_DELETE);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&delete_key_override,
	NULL // Null terminate the array of overrides!
};
```

## Intermediate Difficulty Examples

### Media Controls & Screen Brightness

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
const key_override_t next_track_override = ko_make_with_layers_and_negmods(
    MOD_MASK_CTRL,       // Trigger modifiers: ctrl
    KC_MEDIA_PLAY_PAUSE, // Trigger key: play/pause
    KC_MEDIA_NEXT_TRACK, // Replacement key
    ~0,                  // Activate on all layers
    MOD_MASK_SA);        // Do not activate when shift or alt are pressed
    
const key_override_t prev_track_override = ko_make_with_layers_and_negmods(MOD_MASK_CS, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_PREV_TRACK, ~0, MOD_MASK_ALT);

const key_override_t vol_up_override = ko_make_with_layers_and_negmods(MOD_MASK_ALT, KC_MEDIA_PLAY_PAUSE, KC_AUDIO_VOL_UP, ~0, MOD_MASK_CS);

const key_override_t vol_down_override = ko_make_with_layers_and_negmods(MOD_MASK_SA, KC_MEDIA_PLAY_PAUSE, KC_AUDIO_VOL_DOWN, ~0, MOD_MASK_CTRL);

const key_override_t brightness_up_override = ko_make_with_layers_and_negmods(MOD_MASK_CA, KC_MEDIA_PLAY_PAUSE, KC_BRIGHTNESS_UP, ~0, MOD_MASK_SHIFT);

const key_override_t brightness_down_override = ko_make_basic(MOD_MASK_CSA, KC_MEDIA_PLAY_PAUSE, KC_BRIGHTNESS_DOWN);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&next_track_override,
	&prev_track_override,
	&vol_up_override,
	&vol_down_override,
	&brightness_up_override,
	&brightness_down_override,
	NULL
};
```

### Flexible macOS-friendly Grave Escape
The [Grave Escape feature](https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_grave_esc) is limited in its configurability and has [bugs when used on macOS](https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_grave_esc#caveats). Key overrides can be used to achieve a similar functionality as Grave Escape, but with more customization and without bugs on macOS.

```c
// Shift + esc = ~
const key_override_t tilde_esc_override = ko_make_basic(MOD_MASK_SHIFT, KC_ESC, S(KC_GRAVE));

// GUI + esc = `
const key_override_t grave_esc_override = ko_make_basic(MOD_MASK_GUI, KC_ESC, KC_GRAVE);

const key_override_t **key_overrides = (const key_override_t *[]){
	&tilde_esc_override,
	&grave_esc_override,
	NULL
};
```

In addition to not encountering unexpected bugs on macOS, you can also change the behavior as you wish. Instead setting `GUI` + `ESC` = `` ` `` you may change it to an arbitrary other modifier, for example `Ctrl` + `ESC` = `` ` ``.

## Inner Workings

Continuing with the example of `shift` + `backspace` = `delete`, this section explains how a key override works in detail. Understanding this is essential to be able to take full advantage of all the options offered by key overrides.

#### Activation

When the necessary keys are pressed (`shift` + `backspace`), the override is 'activated' and the replacement key is registered in the keyboard report (`delete`), while the trigger key (`backspace`) is removed from the keyboard report. The trigger modifiers may also be removed from the keyboard report upon activation of an override. In this example, the `shift` key has to be removed from the keyboard report.

Overrides can activate in three different cases:

1. The trigger key is pressed down and necessary modifiers are already down.
2. A necessary modifier is pressed down, while the trigger key and other necessary modifiers are already down.
3. A negative modifier is released, while all necessary modifiers and the trigger key are already down.

Use the `option` member to customize which of these events are allowed to activate your overrides (default: all three).

In any case, a key override can only activate if the trigger key is the _last_ non-modifier key that was pressed down. This emulates the behavior of how standard OSes (macOS, Windows, Linux) handle normal key input (hold down `a`, then also hold down `b`, then hold down `shift`; `B` will be typed but not `A`).

#### Deactivation

An override is 'deactivated' when one of the trigger keys (`shift` or `backspace`) is lifted, another non-modifier key is pressed down, or a negative modifier is pressed down. When an override deactivates, the replacement key (`delete`) is removed from the keyboard report, while the modifiers that are still held down and we previously removed from the keyboard report are re-added to the keyboard report. By default, the trigger key (`backspace`) is re-added to the keyboard report if it is still held down and no other non-modifier key has been pressed since. This again emulates the behavior of how standard OSes handle normal key input (hold down `a`, then also hold down `b` and `shift`, then release `b`; `A` will not be typed even though you are holding the `a` and `shift` keys). Use the option `ko_option_no_reregister_trigger` to prevent re-registering the trigger key in all cases.

#### Key Repeat Interval

A third way in which standard OS-handling of modded (shifted/alted/...) keys is emulated in key overrides is with a 'key repeat interval'. To explain what this is, let's look at how normal keyboard input is handled by mainstream OSes again: If you hold down `a`, followed by `shift`, you will see the letter `a` is first typed, then for a short moment nothing is typed and then repeating `A`s are typed. Take note that, although shift is pressed down just after `a` is pressed, it takes a moment until `A` is typed. This is caused by the aforementioned key repeat interval, and it is a feature that prevents unwanted repeated characters from being typed.

This applies equally to releasing a modifier: When you hold `shift`, then press `a`, the letter `A` is typed. Now if you release `shift` first, followed by `a` shortly after, you will not see the letter `a` being typed even though for a short moment of time you were just holding down the key `a`. This exact behavior is implemented in key overrides as well: If a key override for `shift` + `a` = `b` is active, and `a` is held down, followed by `shift`, you will not immediately see the letter `b` being typed. Instead, this event is deferred for a short moment, just like in the key repeat interval for normal, non overridden keys. The override key (`b`) will not be typed until the key repeat interval has passed, measured from the moment when the trigger key was pressed down.

The duration of the key repeat interval is controlled with the `TAPPING_TERM` macro. Define this value in your `config.h` file to change it. It is 250ms by default.

## Reference for `key_override_t`

Advanced users may need more customization than what is offered by the simple `ko_make` initializers. For this, directly create a `key_override_t` value and set all members. Below is a reference for all members of `key_override_t`.

| Member                                                 | Description                                                                                                                                                                                                                                                                                                                                                                                                                                        |
|--------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `uint16_t trigger`                                     | The basic keycode that triggers the override. This keycode MUST exclude modifiers. It can also be a custom keycode. A key override can only activate when the trigger key is the last non-modifier key that was pressed down. This emulates the standard behavior of how OSes handle keyboard input. Moreover, wWhen an override is active and another non-modifier key is pressed down, the modifier is always deactivated, again emulating the behavior of OS keyboard handling.                                                                                                                                                                                                                                                                                                                                |
| `uint8_t trigger_modifiers`                            | Which mods need to be down for activation. If both sides of mod are set (e.g. left ctrl and right ctrl) then only one is required to trigger (e.g. left ctrl suffices).                                                                                                                                                                                                                                                                            |
| `layer_state_t layers`                                 | This is a BITMASK (!), defining which layers this override applies to. To use this override on layer i set the ith bit (1 << i).                                                                                                                                                                                                                                                                                                                   |
| `uint8_t negative_modifier_mask`                       | Which keys cannot be down: get_mods() & negative_modifier_mask must be 0. Can be used to disallow specific modifiers for fine-grained control.                                                                                                                                                                                                                                                                                                     |
| `uint8_t suppressed_mods`                              | Modifiers to suppress when active. Can be used to suppress the trigger modifiers, as a trivial example.                                                                                                                                                                                                                                                                                                                                            |
| `uint16_t replacement`                                 | The complex keycode to send as replacement when this override is triggered. This may be a custom keycode or a key-modifier combination. Use in combination with suppressed_mods to get the correct modifiers to be sent if needed.                                                                                                                                                                                                                 |
| `ko_option_t options`             | Options controlling the behavior of the override, such as what actions are allowed to activate the override.                                                                                                                                                                                                                                                                                                                |
| `bool (*custom_action)(bool activated, void *context)` | If not NULL, this function will be called right before the replacement key is registered, along with the provided context and a flag indicating whether the override was activated or deactivated. This function allows you to run some custom actions for specific key overrides. If you return `false`, the replacement key is not registered/unregistered as it would normally. Return `true` to register and unregister the override normally. |
| `void *context`                                        | A context that will be passed to the custom action function if that is set.                                                                                                                                                                                                                                                                                                                                                                        |
| `bool *enabled`                                        | If this points to false this override will not be used. Set to NULL to always have this override enabled.                                                                                                                                                                                                                                                                                                                                          |

### Reference for `ko_option_t`

Bitfield with various options controlling the behavior of a key override.

| Value                                    | Description                                                                                                                                                                                                            |
|------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `ko_option_activation_trigger_down`      | Allow activating when the trigger key is pressed down.                                                                                                                                                                 |
| `ko_option_activation_required_mod_down` | Allow activating when a necessary modifier is pressed down.                                                                                                                                                                                     |
| `ko_option_activation_negative_mod_up`   | Allow activating when a negative modifier is released.                                                                                                                                                                 |
| `ko_option_one_mod`                      | If set, any of the modifiers in `trigger_modifiers` will be enough to activate the override (logical OR of modifiers). If not set, all the modifiers in `trigger_modifiers` have to be pressed (logical AND of modifiers). |
| `ko_option_exclusive_key_on_activate`    |  If set, the override can only activate if no non-modifier key except the trigger key is down.                                                                                                                         |
| `ko_option_no_reregister_trigger`        | If set, the trigger key will never be registered again after the override is deactivated.                                                                                                                              |
| `ko_options_default`                     | The default options used by the `ko_make_xxx` functions                                                                                                                                                                  |

## Advanced Examples
### Modifiers as Layer Keys

_Do you really need a dedicated key to toggle your fn layer? With key overrides, perhaps not._ This example shows how you can configure to use `rGUI` + `rAlt` (right GUI and right alt) to access a momentary layer like an fn layer. With this you completely eliminate the need to use a dedicated layer key. Of course the choice of modifier keys can be changed as needed, `rGUI` + `rAlt` is just an example here. 

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

const key_override_t fn_override = {.trigger_modifiers      = MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL),                       //
                                   .layers                 = ~(1 << LAYER_FN),                                          //
                                   .suppressed_mods        = MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL),                       //
                                   .options                = ko_options_default | ko_option_exclusive_key_on_activate,  //
                                   .negative_modifier_mask = (uint8_t) ~(MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL)),          //
                                   .custom_action          = momentary_layer,                                           //
                                   .context                = (void *)LAYER_FN,                                          //
                                   .trigger                = KC_NO,                                                     //
                                   .replacement            = KC_NO,                                                     //
                                   .enabled                = NULL};
```

## Keycodes 

You can enable, disable and toggle the Key Override feature on the fly.

|Keycode   |Description                      |Function Equivalent|
|----------|---------------------------------|--------|
|`KEY_OVERRIDE_ON`  |Turns on Key Override feature           | `key_override_on(void)`|
|`KEY_OVERRIDE_OFF` |Turns off Key Override feature          |`key_override_off(void)`|
|`KEY_OVERRIDE_TOGGLE` |Toggles Key Override feature on and off |`key_override_toggle(void)`|