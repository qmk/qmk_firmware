# Combos

The Combo feature is a chording type solution for adding custom actions.  It lets you hit multiple keys at once and produce a different effect.  For instance, hitting `A` and `S` within the tapping term would hit `ESC` instead, or have it perform even more complex tasks.

To enable this feature, you need to add `COMBO_ENABLE = yes` to your `rules.mk`.

Additionally, in your `config.h`, you'll need to specify the number of combos that you'll be using, by adding `#define COMBO_COUNT 1` (replacing 1 with the number that you're using).
<!-- At this time, this is necessary -->


Then, your `keymap.c` file, you'll need to define a sequence of keys, terminated with `COMBO_END`, and a structure to list the combination of keys, and it's resulting action.

```c
const uint16_t PROGMEM test_combo[] = {KC_A, KC_B, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {COMBO(test_combo, KC_ESC)};
```

This will send "Escape" if you hit the A and B keys.

!> This method only supports [basic keycodes](keycodes_basic.md). See the examples for more control.

## Examples

If you want to add a list, then you'd use something like this:

```c
enum combos {
  AB_ESC,
  JK_TAB
};

const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [AB_ESC] = COMBO(ab_combo, KC_ESC),
  [JK_TAB] = COMBO(jk_combo, KC_TAB)
};
```

For a more complicated implementation, you can use the `process_combo_event` function to add custom handling.

```c
enum combo_events {
  ZC_COPY,
  XV_PASTE
};

const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [ZC_COPY] = COMBO_ACTION(copy_combo),
  [XV_PASTE] = COMBO_ACTION(paste_combo),
};

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case ZC_COPY:
      if (pressed) {
        tap_code16(LCTL(KC_C));
      }
      break;
    case XV_PASTE:
      if (pressed) {
        tap_code16(LCTL(KC_V));
      }
      break;
  }
}
```

This will send Ctrl+C if you hit Z and C, and Ctrl+V if you hit X and V.  But you could change this to do stuff like change layers, play sounds, or change settings.

# Advanced Configuration
These configuration settings can be set in your keymaps `config.h`. 

#### Keycodes 
You can enable, disable and toggle the Combo feature on the fly.  This is useful if you need to disable them temporarily, such as for a game. The following keycodes are avalible for use in your `keymap.c`

|Keycode   |Description                      |
|----------|---------------------------------|
|`CMB_ON`  |Turns on Combo feature           |
|`CMB_OFF` |Turns off Combo feature          |
|`CMB_TOG` |Toggles Combo feature on and off |

#### Combo Term
By default, the timeout for the Combos to be recognized is set to the same value as `TAPPING_TERM` (default: 200ms). This can be changed if accidental combo misfires are happening. For instance `#define COMBO_TERM 50` would set the time out period for combos to 50ms.

#### Long Combos
If you're using long combos or longer combos, you may run into issues with this, as the structure may not be large enough to accommodate what you're doing. In this case, you can configure the size of the data structure used. Be aware, larger combo sizes will increase memory usage!

| Keys | Define to be set     |
|------|----------------------|
| 8    | QMK Default          |
| 16   | `#define EXTRA_LONG_COMBOS`  |
| 32   | `#define EXTRA_EXTRA_LONG_COMBOS`|

#### Permissive Hold
Similar to Tap-Hold configuration, Combos can be setup to behave similarly. Add `#define COMBO_PERMISSIVE_HOLD` to your `config.h` to enable. This feature is extremely useful for fast typists!

#### Mod Term
If a combo contains a Modifer, the window for processing a combo can be extended. This is useful for keymaps with a shortend `COMBO_TERM` or that use a Combo for a modifer key. By default it is disabled but can be enabled with `#define COMBO_MUST_HOLD_MODS`, the time window can be configured with `#define COMBO_MOD_TERM 50` (default: `TAPPING_TERM`

#### Per Combo Timing
Instead of using a blanket `COMBO_TERM` window for every combo, per-combo timings can be generated. In order to use this feature the following config options and functions can be defined. Coming up with useful timings and configuration is left as an excercise for the reader.

| Config Flag | Function | Description |
|-------------|----------|-------------|
| `COMBO_MUST_HOLD_PER_KEY` | bool get_combo_must_hold(uint16_t index, combo_t \*combo) | Controls if a given combo window should be extended by `get_combo_term()` (default: False) |
| `COMBO_TERM_PER_COMBO` | uint16_t get_combo_term(uint16_t index, combo_t \*combo) | Optional per-combo timeout window for primary combos. (default: COMBO_TERM) |

#### Variable Length Combos
If `COMBO_VARIABLE_LEN` is defined allows the user to pragmatically declare the size of the Combo data structure and avoid updating COMBO_COUNT. Instead a variable is exported called COMBO_LEN and is usually set with something similar to the following in `keymap.c`: `int COMBO_LEN = sizeof(key_combos) / sizeof(key_combos[0]);`

#### User callbacks

In addition to the keycodes, there are a few functions that you can use to set the status, or check it:

|Function   |Description                                                         |
|-----------|--------------------------------------------------------------------|
| `combo_enable()`     | Enables the combo feature                               |
| `combo_disable()`    | Disables the combo feature, and clears the combo buffer |
| `combo_toggle()`     | Toggles the state of the combo feature                  |
| `is_combo_enabled()` | Returns the status of the combo feature state (true or false) |

#### Hooks
The following functions can be defined and will hook the processing of the Combo feature

|Function   |Description                                                         |
|-----------|--------------------------------------------------------------------|
| void process_combo_event(uint16_t combo_index, bool pressed) | User hook called on every combo key |


#### Dictionary Management
Combos can be augmented by the [Combo Engine](http://combos.gboards.ca/) to allow for easier configuration and multifile dictionaries. When a large number of Combos are present, these decorators allow for simpler management and definition of Combos. With single line combo definitions and various helpers consider using this when over 20 combos are present on a keyboard. Under the hood, the Combo Feature is used and all the above configuration will work with it.
