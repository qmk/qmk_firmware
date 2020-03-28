# Combos

The Combo feature is a chording type solution for adding custom actions. It lets you hit multiple keys at once and produce a different effect. For instance, hitting `A` and `S` within the tapping term would hit `ESC` instead, or have it perform even more complex tasks.

To enable this feature, you need to add `COMBO_ENABLE = yes` to your `rules.mk`.

Additionally, in your `config.h`, you'll need to specify the number of combos that you'll be using, by adding `#define COMBO_COUNT 1` (replacing 1 with the number that you're using). It is also possible to not define this and instead set the variable `COMBO_LEN` yourself. There's a trick where we don't need to think about this variable at all. More on this later.


Then, in your `keymap.c` file, you'll need to define a sequence of keys, terminated with `COMBO_END`, and a structure to list the combination of keys, and its resulting action.

```c
const uint16_t PROGMEM test_combo[] = {KC_A, KC_B, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {COMBO(test_combo, KC_ESC)};
```

This will send "Escape" if you hit the A and B keys.

As of [PR#8591](https://github.com/qmk/qmk_firmware/pull/8591/), it is possible to fire combos from ModTap keys and LayerTap keys. So in the above example you could have keys `LSFT_T(KC_A)` and `LT(_LAYER, KC_B)` and it would work. So Home Row Mods and Home Row Combos at same time is now a thing!

It is also now possible to overlap combos. Before, with the example below both combos would activate when all three keys were pressed. Now only the three key combo will activate.

```c
const uint16_t PROGMEM test_combo1[] = {LSFT_T(KC_A), LT(_LAYER, KC_B), COMBO_END};
const uint16_t PROGMEM test_combo2[] = {LSFT_T(KC_A), LT(_LAYER, KC_B), KC_C, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(test_combo1, KC_ESC)
    COMBO(test_combo2, KC_TAB)
};
```

Executing more complex keycodes like ModTaps and LayerTaps is now also possible.

## Examples

If you want to add a list, then you'd use something like this:

```c
enum combos {
  AB_ESC,
  JK_TAB,
  QW_SFT,
  SD_LAYER,
};

const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [AB_ESC] = COMBO(ab_combo, KC_ESC),
  [JK_TAB] = COMBO(jk_combo, KC_TAB),
  [QW_SFT] = COMBO(qw_combo, KC_LSFT)
  [SD_LAYER] = COMBO(layer_combo, MO(_LAYER)),
};
```

For a more complicated implementation, you can use the `process_combo_event` function to add custom handling.
Additionally, this example shows how you can leave `COMBO_COUNT` undefined.

```c
enum combo_events {
  ZC_COPY,
  XV_PASTE,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};

combo_t key_combos[] = {
  [ZC_COPY] = COMBO_ACTION(copy_combo),
  [XV_PASTE] = COMBO_ACTION(paste_combo),
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
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

This will send Ctrl+C if you hit Z and C, and Ctrl+V if you hit X and V. But you could change this to do stuff like play sounds or change settings.

## Keycodes
You can enable, disable and toggle the Combo feature on the fly. This is useful if you need to disable them temporarily, such as for a game. The following keycodes are available for use in your `keymap.c`

|Keycode   |Description                      |
|----------|---------------------------------|
|`CMB_ON`  |Turns on Combo feature           |
|`CMB_OFF` |Turns off Combo feature          |
|`CMB_TOG` |Toggles Combo feature on and off |

# Advanced Configuration
These configuration settings can be set in your `config.h` file.

## Combo Term
By default, the timeout for the Combos to be recognized is set to 50ms. This can be changed if accidental combo misfires are happening or if you're having difficulties pressing keys at the same time. For instance, `#define COMBO_TERM 40` would set the timeout period for combos to 40ms.

## Long Combos
If you're using long combos, or you have a lot of overlapping combos, you may run into issues with this, as the buffers may not be large enough to accommodate what you're doing. In this case, you can configure the sizes of the buffers used. Be aware, larger combo sizes and larger buffers will increase memory usage!

To configure the amount of keys a combo can be composed of, change the following:

| Keys | Define to be set     |
|------|----------------------|
| 8    | QMK Default          |
| 16   | `#define EXTRA_LONG_COMBOS`  |
| 32   | `#define EXTRA_EXTRA_LONG_COMBOS`|

Processing combos has two buffers, one for the key presses, another for the combos being activated. Use the following options to configure the sizes of these buffers:

| Define                              | Default                                              |
| `#define COMBO_KEY_BUFFER_LENGTH 8` | 8 (the key amount `(EXTRA_)EXTRA_LONG_COMBOS` gives) |
| `#define COMBO_BUFFER_LENGTH 4`     | 4                                                    |

## Modifier Combos
If a combo resolves to a Modifier, the window for processing the combo can be extended independently from normal combos. By default, this is disabled but can be enabled with `#define COMBO_MUST_HOLD_MODS`, and the time window can be configured with `#define COMBO_HOLD_TERM 150` (default: `TAPPING_TERM`). With `COMBO_MUST_HOLD_MODS`, you cannot tap the combo any more which makes the combo less prone to misfires.

## Per Combo Timing, Holding and Tapping
For each combo, it is possible to configure the time window it has to pressed in, if it needs to be held down, or if it needs to be tapped.

For example, tap-only combos are useful if any (or all) of the underlying keys is a Mod-Tap or a Layer-Tap key. When you tap the combo, you get the combo result. When you press the combo and hold it down, the combo doesn't actually activate. Instead the keys are processed separately as if the combo wasn't even there.

In order to use these features, the following configuration options and functions need to be defined. Coming up with useful timings and configuration is left as an exercise for the reader.

| Config Flag                 | Function                                                  | Description                                                                                            |
|-----------------------------|-----------------------------------------------------------|--------------------------------------------------------------------------------------------------------|
| `COMBO_TERM_PER_COMBO`      | uint16_t get_combo_term(uint16_t index, combo_t \*combo)  | Optional per-combo timeout window. (default: `COMBO_TERM`)                                             |
| `COMBO_MUST_HOLD_PER_COMBO` | bool get_combo_must_hold(uint16_t index, combo_t \*combo) | Controls if a given combo should fire immediately on tap or if it needs to be held. (default: `false`) |
| `COMBO_MUST_TAP_PER_COMBO`  | bool get_combo_must_tap(uint16_t index, combo_t \*combo)  | Controls if a given combo should fire only if tapped within `COMBO_HOLD_TERM`. (default: `false`)      |

Examples:
```c
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    // decide by combo->keycode
    switch (combo->keycode) {
        case KC_X:
            return 50;
    }

    // or with combo index, i.e. its name from enum.
    switch (index) {
        case COMBO_NAME_HERE:
            return 9001;
    }

    // And if you're feeling adventurous, you can even decide by the keys in the chord,
    // i.e. the exact array of keys you defined for the combo.
    // This can be useful if your combos have a common key and you want to apply the
    // same combo term for all of them.
    if (combo->keys[0] == KC_ENTER) { // if first key in the array is KC_ENTER
        return 150;
    }

    return COMBO_TERM;
}

bool get_combo_must_hold(uint16_t index, combo_t *combo) {
    // Same as above, decide by keycode, the combo index, or by the keys in the chord.

    if (KEYCODE_IS_MOD(combo->keycode) || 
        (combo->keycode >= QK_MOMENTARY && combo->keycode <= QK_MOMENTARY_MAX) // MO(kc) keycodes
        ) {
        return true;
    }

    switch (index) {
        case COMBO_NAME_HERE:
            return true;
    }

    return false;
}

bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    // If you want all combos to be tap-only, just uncomment the next line
    // return true

    // If you want *all* combos, that have Mod-Tap/Layer-Tap/Momentary keys in its chord, to be tap-only, this is for you:
    uint16_t key;
    uint8_t idx = 0;
    while ((key = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
        switch (key) {
            case QK_MOD_TAP...QK_MOD_TAP_MAX:
            case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
            case QK_MOMENTARY...QK_MOMENTARY_MAX:
                return true;
        }
        idx += 1;
    }
    return false;

}
```

## Variable Length Combos
If you leave `COMBO_COUNT` undefined in `config.h`, it allows you to programmatically declare the size of the Combo data structure and avoid updating `COMBO_COUNT`. Instead a variable called `COMBO_LEN` has to be set. It can be set with something similar to the following in `keymap.c`: `uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(key_combos[0]);` or by adding `COMBO_LENGTH` as the *last* entry in the combo enum and then `uint16_t COMBO_LEN = COMBO_LENGTH;` as such:
```c
enum myCombos {
    ...,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
```
Regardless of the method used to declare `COMBO_LEN`, this also requires to convert the `combo_t key_combos[COMBO_COUNT] = {...};` line to `combo_t key_combos[] = {...};`.


## Combo timer

Normally, the timer is started on the first key press and then reset on every subsequent key press within the `COMBO_TERM`.
Inputting combos is relaxed like this, but also slightly more prone to accidental misfires.

The next two options alter the behaviour of the timer.

### `#define COMBO_STRICT_TIMER`

With `COMBO_STRICT_TIMER`, the timer is started only on the first key press.
Inputting combos is now less relaxed; you need to make sure the full chord is pressed within the `COMBO_TERM`.
Misfires are less common but if you type multiple combos fast, there is a
chance that the latter ones might not activate properly.

### `#define COMBO_NO_TIMER`

By defining `COMBO_NO_TIMER`, the timer is disabled completely and combos are activated on the first key release.
This also disables the "must hold" functionalities as they just wouldn't work at all.

## Customizable key releases

By defining `COMBO_PROCESS_KEY_RELEASE` and implementing the function `bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode)`, you can run your custom code on each key release after a combo was activated. For example you could change the RGB colors, activate haptics, or alter the modifiers.

You can also release a combo early by returning `true` from the function.

Here's an example where a combo resolves to two modifiers, and on key releases the modifiers are unregistered one by one, depending on which key was released.

```c
enum combos {
  AB_MODS,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};

combo_t key_combos[] = {
  [AB_MODS] = COMBO(ab_combo, LCTL(KC_LSFT)),
};

bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    switch (combo_index) {
        case AB_MODS:
            switch(keycode) {
                case KC_A:
                    unregister_mods(MOD_MASK_CTRL);
                    break;
                case KC_B:
                    unregister_mods(MOD_MASK_SHIFT);
                    break;
            }
            return false; // do not release combo
    }
    return false;
}
```
## User callbacks

In addition to the keycodes, there are a few functions that you can use to set the status, or check it:

|Function   |Description                                                         |
|-----------|--------------------------------------------------------------------|
| `combo_enable()`     | Enables the combo feature                               |
| `combo_disable()`    | Disables the combo feature, and clears the combo buffer |
| `combo_toggle()`     | Toggles the state of the combo feature                  |
| `is_combo_enabled()` | Returns the status of the combo feature state (true or false) |


# Dictionary Management

Having 3 places to update when adding new combos or altering old ones does become cumbersome when you have a lot of combos. We can alleviate this with some magic! ... If you consider C macros magic.
First, you need to add `VPATH += keyboards/gboards` to your `rules.mk`. Next, include the file `g/keymap_combo.h` in your `keymap.c`.

Then, write your combos in `combos.def` file in the following manner:

```c
//   name     result    chord keys
COMB(AB_ESC,  KC_ESC,   KC_A, KC_B)
COMB(JK_TAB,  KC_TAB,   KC_J, KC_K)
COMB(JKL_SPC, KC_SPC,   KC_J, KC_K, KC_L)
COMB(ZC_COPY, KC_NO,    KC_Z, KC_C) // using KC_NO as the resulting keycode is the same as COMBO_ACTION before.
...
```

Now, you can update only one place to add or alter combos. You don't even need to remember to update the `COMBO_COUNT` or the `COMBO_LEN` variables at all. Everything is taken care of. Magic!

For small to huge ready made dictionaries of combos, you can check out http://combos.gboards.ca/.
