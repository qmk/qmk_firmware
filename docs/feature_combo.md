# Combos

The Combo feature is a chording type solution for adding custom actions. It lets you hit multiple keys at once and produce a different effect. For instance, hitting `A` and `B` within the combo term would hit `ESC` instead, or have it perform even more complex tasks.

To enable this feature, you need to add `COMBO_ENABLE = yes` to your `rules.mk`.

Then, in your `keymap.c` file, you'll need to define a sequence of keys, terminated with `COMBO_END`, and a structure to list the combination of keys, and its resulting action.

```c
const uint16_t PROGMEM test_combo1[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM test_combo2[] = {KC_C, KC_D, COMBO_END};
combo_t key_combos[] = {
    COMBO(test_combo1, KC_ESC),
    COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
};
```

This will send "Escape" if you hit the A and B keys, and Ctrl+Z when you hit the C and D keys.

## Mod-Tap Support
[Mod-Tap](mod_tap.md) feature is also supported together with combos. You will need to use the full Mod-Tap keycode in the combo definition, e.g.:

```c
const uint16_t PROGMEM test_combo1[] = {LSFT_T(KC_A), LT(1, KC_B), COMBO_END};
```

## Overlapping Combos
It is possible to overlap combos. Before, with the example below both combos would activate when all three keys were pressed. Now only the three key combo will activate.

```c
const uint16_t PROGMEM test_combo1[] = {LSFT_T(KC_A), LT(1, KC_B), COMBO_END};
const uint16_t PROGMEM test_combo2[] = {LSFT_T(KC_A), LT(1, KC_B), KC_C, COMBO_END};
combo_t key_combos[] = {
    COMBO(test_combo1, KC_ESC)
    COMBO(test_combo2, KC_TAB)
};
```

## Examples

A long list of combos can be defined in an `enum` list:

```c
enum combos {
  AB_ESC,
  JK_TAB,
  QW_SFT,
  SD_LAYER
};

const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};

combo_t key_combos[] = {
  [AB_ESC] = COMBO(ab_combo, KC_ESC),
  [JK_TAB] = COMBO(jk_combo, KC_TAB),
  [QW_SFT] = COMBO(qw_combo, KC_LSFT),
  [SD_LAYER] = COMBO(sd_combo, MO(_LAYER)),
};
```

For a more complicated implementation, you can use the `process_combo_event` function to add custom handling.

```c
enum combo_events {
  EM_EMAIL,
  BSPC_LSFT_CLEAR,
};

const uint16_t PROGMEM email_combo[] = {KC_E, KC_M, COMBO_END};
const uint16_t PROGMEM clear_line_combo[] = {KC_BSPC, KC_LSFT, COMBO_END};

combo_t key_combos[] = {
  [EM_EMAIL] = COMBO_ACTION(email_combo),
  [BSPC_LSFT_CLEAR] = COMBO_ACTION(clear_line_combo),
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case EM_EMAIL:
      if (pressed) {
        SEND_STRING("john.doe@example.com");
      }
      break;
    case BSPC_LSFT_CLEAR:
      if (pressed) {
        tap_code16(KC_END);
        tap_code16(S(KC_HOME));
        tap_code16(KC_BSPC);
      }
      break;
  }
}
```

This will send "john.doe@example.com" if you chord E and M together, and clear the current line with Backspace and Left-Shift. You could change this to do stuff like play sounds or change settings.

It is worth noting that `COMBO_ACTION`s are not needed anymore. As of [PR#8591](https://github.com/qmk/qmk_firmware/pull/8591/), it is possible to run your own custom keycodes from combos. Just define the custom keycode, program its functionality in `process_record_user`, and define a combo with `COMBO(<key_array>, <your_custom_keycode>)`. See the first example in [Macros](feature_macros.md).

## Keycodes
You can enable, disable and toggle the Combo feature on the fly. This is useful if you need to disable them temporarily, such as for a game. The following keycodes are available for use in your `keymap.c`

|Keycode          |Aliases  |Description                     |
|-----------------|---------|--------------------------------|
|`QK_COMBO_ON`    |`CM_ON`  |Turns on Combo feature          |
|`QK_COMBO_OFF`   |`CM_OFF` |Turns off Combo feature         |
|`QK_COMBO_TOGGLE`|`CM_TOGG`|Toggles Combo feature on and off|

## Advanced Configuration
These configuration settings can be set in your `config.h` file.

### Combo Term
By default, the timeout for the Combos to be recognized is set to 50ms. This can be changed if accidental combo misfires are happening or if you're having difficulties pressing keys at the same time. For instance, `#define COMBO_TERM 40` would set the timeout period for combos to 40ms.

### Buffer and state sizes
If you're using long combos, or you have a lot of overlapping combos, you may run into issues with this, as the buffers may not be large enough to accommodate what you're doing. In this case, you can configure the sizes of the buffers used. Be aware, larger combo sizes and larger buffers will increase memory usage!

To configure the amount of keys a combo can be composed of, change the following:

| Keys | Define to be set                  |
|------|-----------------------------------|
| 6    | `#define EXTRA_SHORT_COMBOS`      |
| 8    | QMK Default                       |
| 16   | `#define EXTRA_LONG_COMBOS`       |
| 32   | `#define EXTRA_EXTRA_LONG_COMBOS` |

Defining `EXTRA_SHORT_COMBOS` combines a combo's internal state into just one byte. This can, in some cases, save some memory. If it doesn't, no point using it. If you do, you also have to make sure you don't define combos with more than 6 keys.

Processing combos has two buffers, one for the key presses, another for the combos being activated. Use the following options to configure the sizes of these buffers:

| Define                              | Default                                              |
|-------------------------------------|------------------------------------------------------|
| `#define COMBO_KEY_BUFFER_LENGTH 8` | 8 (the key amount `(EXTRA_)EXTRA_LONG_COMBOS` gives) |
| `#define COMBO_BUFFER_LENGTH 4`     | 4                                                    |

### Modifier Combos
If a combo resolves to a Modifier, the window for processing the combo can be extended independently from normal combos. By default, this is disabled but can be enabled with `#define COMBO_MUST_HOLD_MODS`, and the time window can be configured with `#define COMBO_HOLD_TERM 150` (default: `TAPPING_TERM`). With `COMBO_MUST_HOLD_MODS`, you cannot tap the combo any more which makes the combo less prone to misfires.

### Strict key press order
By defining `COMBO_MUST_PRESS_IN_ORDER` combos only activate when the keys are pressed in the same order as they are defined in the key array.

### Per Combo Timing, Holding, Tapping and Key Press Order
For each combo, it is possible to configure the time window it has to pressed in, if it needs to be held down, if it needs to be tapped, or if its keys need to be pressed in order.

For example, tap-only combos are useful if any (or all) of the underlying keys are mod-tap or layer-tap keys. When you tap the combo, you get the combo result. When you press the combo and hold it down, the combo doesn't activate. Instead the keys are processed separately as if the combo wasn't even there.

In order to use these features, the following configuration options and functions need to be defined. Coming up with useful timings and configuration is left as an exercise for the reader.

| Config Flag                 | Function                                                  | Description                                                                                            |
|-----------------------------|-----------------------------------------------------------|--------------------------------------------------------------------------------------------------------|
| `COMBO_TERM_PER_COMBO`      | uint16_t get_combo_term(uint16_t index, combo_t \*combo)  | Optional per-combo timeout window. (default: `COMBO_TERM`)                                             |
| `COMBO_MUST_HOLD_PER_COMBO` | bool get_combo_must_hold(uint16_t index, combo_t \*combo) | Controls if a given combo should fire immediately on tap or if it needs to be held. (default: `false`) |
| `COMBO_MUST_TAP_PER_COMBO`  | bool get_combo_must_tap(uint16_t index, combo_t \*combo)  | Controls if a given combo should fire only if tapped within `COMBO_HOLD_TERM`. (default: `false`)      |
| `COMBO_MUST_PRESS_IN_ORDER_PER_COMBO` | bool get_combo_must_press_in_order(uint16_t index, combo_t \*combo) | Controls if a given combo should fire only if its keys are pressed in order. (default: `true`) |

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
    if (combo->keys[0] == KC_ENT) { // if first key in the array is Enter
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

bool get_combo_must_press_in_order(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        /* List combos here that you want to only activate if their keys
         * are pressed in the same order as they are defined in the combo's key
         * array. */
        case COMBO_NAME_HERE:
            return true;
        default:
            return false;
    }
}
```

### Generic hook to (dis)allow a combo activation

By defining `COMBO_SHOULD_TRIGGER` and its companying function `bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record)` you can block or allow combos to activate on the conditions of your choice.
For example, you could disallow some combos on the base layer and allow them on another. Or disable combos on the home row when a timer is running.

Examples:
```c
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    /* Disable combo `SOME_COMBO` on layer `_LAYER_A` */
    switch (combo_index) {
        case SOME_COMBO:
            if (layer_state_is(_LAYER_A)) {
                return false;
            }
    }

    return true;
}
```

### Combo timer

Normally, the timer is started on the first key press and then reset on every subsequent key press within the `COMBO_TERM`.
Inputting combos is relaxed like this, but also slightly more prone to accidental misfires.

The next two options alter the behaviour of the timer.

#### `#define COMBO_STRICT_TIMER`

With `COMBO_STRICT_TIMER`, the timer is started only on the first key press.
Inputting combos is now less relaxed; you need to make sure the full chord is pressed within the `COMBO_TERM`.
Misfires are less common but if you type multiple combos fast, there is a
chance that the latter ones might not activate properly.

#### `#define COMBO_NO_TIMER`

By defining `COMBO_NO_TIMER`, the timer is disabled completely and combos are activated on the first key release.
This also disables the "must hold" functionalities as they just wouldn't work at all.

### Customizable key releases

By defining `COMBO_PROCESS_KEY_RELEASE` and implementing the function `bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode)`, you can run your custom code on each key release after a combo was activated. For example you could change the RGB colors, activate haptics, or alter the modifiers.

You can also release a combo early by returning `true` from the function.

Here's an example where a combo resolves to two modifiers, and on key releases the modifiers are unregistered one by one, depending on which key was released.

```c
enum combos {
  AB_MODS
};

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
### Layer independent combos

If you, for example, use multiple base layers for different key layouts, one for QWERTY, and another one for Colemak, you might want your combos to work from the same key positions on all layers. Defining the same combos again for another layout is redundant and takes more memory. The solution is to just check the keycodes from one layer.

With `#define COMBO_ONLY_FROM_LAYER 0` in config.h, the combos' keys are always checked from layer `0`, even if other layers are active.

#### Combo reference layers by layer.

If not using `COMBO_ONLY_FROM_LAYER` it is possible to specify a
combo reference layer for any layer using the `combo_ref_from_layer` hook. 
The combo macros automatically create this function from the `COMBO_REF_LAYER()`
entries given.

This function returns the assigned reference layer for the current layer.
if there is no match, it returns the  default reference layer if set, 
or the current layer otherwise. A default layer can be set with
`DEFAULT_REF_LAYER(_MY_COMBO_REF_LAYER)`

If not set, the default reference layer selection from the automatically generated 
`combo-ref-from-layer()` will be the current layer.

The following `combo_ref_from_layer` function 
will give a reference layer of _QWERTY for the _DVORAK layer and
will give the _NAV layer as a reference to it's self. All other layers
will have the default for their combo reference layer. If the default
is not set, all other layers will reference themselves.

    ```c
    #define COMBO_REF_DEFAULT _MY_COMBO_LAYER
    ...

    uint8_t combo_ref_from_layer(uint8_t layer){
        switch (get_highest_layer(layer_state)){
            case _DVORAK: return _QWERTY;
            case _NAV: return _NAV;
            default: return _MY_COMBO_LAYER;
        }
        return layer;  // important if default is not in case.
    }

    ```
    
    The equivalent definition using the combo macros is this: 

    ```c
    COMBO_REF_LAYER(_DVORAK, _QWERTY)
    COMBO_REF_LAYER(_NAV, _NAV)
    DEFAULT_REF_LAYER(_MY_COMBO_LAYER).
    ```
    

## User callbacks

In addition to the keycodes, there are a few functions that you can use to set the status, or check it:

|Function   |Description                                                         |
|-----------|--------------------------------------------------------------------|
| `combo_enable()`     | Enables the combo feature                               |
| `combo_disable()`    | Disables the combo feature, and clears the combo buffer |
| `combo_toggle()`     | Toggles the state of the combo feature                  |
| `is_combo_enabled()` | Returns the status of the combo feature state (true or false) |


## Dictionary Management

Having 3 places to update when adding new combos or altering old ones does become cumbersome when you have a lot of combos. We can alleviate this with some magic! ... If you consider C macros magic.
First, you need to add `VPATH += keyboards/gboards` to your `rules.mk`. Next, include the file `g/keymap_combo.h` in your `keymap.c`.

!> This functionality uses the same `process_combo_event` function as `COMBO_ACTION` macros do, so you cannot use the function yourself in your keymap. Instead, you have to define the `case`s of the `switch` statement by themselves within `inject.h`, which `g/keymap_combo.h` will then include into the function.

Then, write your combos in `combos.def` file in the following manner:

```c
// Alternate reference layers by layer
//               Layer     Reference layer
COMBO_REF_LAYER(_DVORAK, _QWERTY)  // reference the qwerty layer for dvorak.
COMBO_REF_LAYER(_NAV, _NAV) // explicit reference to self instead of the default.

//   name     result    chord keys
COMB(AB_ESC,   KC_ESC,   KC_A, KC_B)
COMB(JK_TAB,   KC_TAB,   KC_J, KC_K)
COMB(JKL_SPC,  KC_SPC,   KC_J, KC_K, KC_L)
COMB(BSSL_CLR, KC_NO,    KC_BSPC, KC_LSFT) // using KC_NO as the resulting keycode is the same as COMBO_ACTION before.
COMB(QW_UNDO,  C(KC_Z),  KC_Q, KC_W)
SUBS(TH_THE,   "the",    KC_T, KC_H) // SUBS uses SEND_STRING to output the given string.
...
```

For small to huge ready made dictionaries of combos, you can check out http://combos.gboards.ca/.
