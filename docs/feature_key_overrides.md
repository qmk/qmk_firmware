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

When the necessary keys are pressed (`shift` + `backspace`), the override is 'activated' and the replacement key is registered in the keyboard report (`delete`), while the trigger key (`backspace`) is removed from the keyboard report. The trigger modifiers may also be removed from the keyboard report upon activation of an override. In this example, the `shift` key has to be removed from the keyboard report.

The override is 'deactivated' when one of the trigger keys (`shift` or `backspace`) is lifted, another non-modifier key is pressed down, or a negative modifier is pressed down. When an override deactivates, the replacement key (`delete`) is removed from the keyboard report, while the modifiers that are still held down and we previously removed from the keyboard report are re-added to the keyboard report. Optionally, the trigger key (`backspace`) may also be re-added to the keyboard report if it is still held down (controlled with the option `ko_option_reregister_trigger_on_deactivation`).


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

### Reference for `ko_option_t `


## Advanced Examples
### Modifiers as Layer Keys

**This is an advanced example**. It exemplifies how creative you can get with key overrides. Do you really need a dedicated key to toggle your fn layer? With key overrides perhaps not. This example shows how you can configure to use `rCtrl` + `rAlt` (right control and right alt) to access a momentary layer like an fn layer. By this you completely eliminate the need to use a dedicated layer key.

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

key_override_t fn_override = {
	// Trigger when rctl and ralt are down
	.trigger_modifiers                   = MOD_BIT(KC_RCTL) | MOD_BIT(KC_RALT),
	.one_mod                             = false,                                
	.layers                              = ~0,
	// When activated, remove the trigger modifiers from the keyboard report                     
	.suppressed_mods                     = MOD_BIT(KC_RCTL) | MOD_BIT(KC_RALT),  
	// Configuration for how many other keys may be down
	.allows_other_keys_down_at_trigger   = false,                                
	.allows_other_keys_down_while_active = true,                                 
	.reregister_trigger_after_completion = false,                                
	.trigger_only_on_trigger_down        = true,                                 
	.negative_modifier_mask              = 0,       
	// Perform a custom action that activates the fn layer                             
	.custom_action                       = momentary_layer,  
	// Pass the index of your fn layer as context                    
	.context                             = (void *)LAYER_FN, 
	// KC_NO as trigger means only the modifiers and no normal key needs to be pressed                    
	.trigger                             = KC_NO,   
	// We are performing a custom action, so no replacement key needs to be registered                             
	.replacement                         = KC_NO, 
	// The override is always enabled                               
	.enabled                             = NULL};
```

## Keycodes 

You can enable, disable and toggle the Key Override feature on the fly.

|Keycode   |Description                      |Function Equivalent|
|----------|---------------------------------|--------|
|`KEY_OVERRIDE_ON`  |Turns on Key Override feature           | `key_override_on(void)`|
|`KEY_OVERRIDE_OFF` |Turns off Key Override feature          |`key_override_off(void)`|
|`KEY_OVERRIDE_TOGGLE` |Toggles Key Override feature on and off |`key_override_toggle(void)`|