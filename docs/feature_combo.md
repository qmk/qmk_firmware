# Combos

The Combo feature lets you customize key presses that are produced when multiple keys are hit at once. For instance, hitting `A` and `S` within the combo term would hit `ESC` instead, or have it perform even more complex tasks.

To enable this feature, add `COMBO_ENABLE = yes` to your `rules.mk`. Then in your `keymap.c` file, define the combos. Their structure is easier to explain with an example:

```c
enum combos {
    AB_COPY,
    CD_PASTE,
};

const uint16_t PROGMEM a_b_combo[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM c_d_combo[] = {KC_C, KC_D, COMBO_END};

combo_t key_combos[] = {
    [AB_COPY]  = COMBO(a_b_combo, LCTL(KC_C)),
    [CD_PASTE] = COMBO(c_d_combo, LCTL(KC_V)),
};

const uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(*key_combos);
```

Let's look at each of its parts:

- The enum with combo names is technically not required, but is useful to refer to combos from the customization points
- For each combo, we define an array of the keycodes it consists of, terminated with `COMBO_END`
- The mapping between input key sequences and resulting keycodes is then established by `key_combos` array
- `COMBO_LEN` must contain the length of `key_combos` array

The full range of source and target keycodes is supported, including layer-tap and mod-tap.

## Combo feature toggle
Sometimes it's useful to disable combos temporarily, such as for a game. For that purpose, special keycodes are available for use in your keymap. It's also possible to toggle combos from user code using functions:

|Keycode   |Function call        |Description                                |
|---------:|--------------------:|:------------------------------------------|
|`CMB_ON`  |`combo_enable()`     |Turns on Combo feature                     |
|`CMB_OFF` |`combo_disable()`    |Turns off Combo feature                    |
|`CMB_TOG` |`combo_toggle()`     |Toggles Combo feature on and off           |
|N/A       |`is_combo_enabled()` |Returns `true` if Combo feature is enabled |

## Combo term
By default, the timeout for the combos to be recognized is set to 50ms. This can be changed if accidental combo misfires are happening or if you're having difficulties pressing keys at the same time. For instance, add `#define COMBO_TERM 100` to your `config.h` to set the timeout period for combos to 100ms.

#### Per combo timing
To customize combo term per combo, implement `get_combo_term` function in `keymap.c`. Example:
```c
uint16_t get_combo_term(uint16_t combo_index) {
    // decide by combo index, i.e. its name from the enum
    switch (index) {
        case COMBO_NAME_HERE:
            return 9001;
    }

    // ...or by the output keycode
    switch (combo->keycode) {
        case KC_X:
            return 50;
    }

    return COMBO_TERM;
}
```

#### Per key timing
To customize combo term per key, implement `uint16_t key_combo_term(uint16_t keycode, const keyrecord_t *record)` function in `keymap.c`. This way you can even force non-combo'd keys to de delayed. By default, key combo term is 0 for all keys.

Combo term for a given key is computed as a maximum of its key combo term and combo terms of all combos the key is a part of.

## Urgent combos
Normally, combos are only fired when their combo term passes. You can mark some combos as "urgent" to make them fire as soon as they are fully pressed, similarly to `PERMISSIVE_HOLD`.

To customize urgency, implement `bool is_combo_urgent(uint16_t combo_index)` in `keymap.c`.

Urgency can have multiple effects:
 
- Combos will feel "snappier", they will fire at the same time a normal key would fire
- Combos with nested key lists will break, because the smaller combo will trigger immediately
- Urgent combos and other combos may be reordered, because the urgent combo isn't delayed in the same way other combos and keys are. This is usually surprising, but can be desirable e.g. for layer-switching combos

## Long combos
If you're using long combos, you may run into the limit on the maximum number of keys per combo. You can increase the limit by adding `#define MAX_COMBO_LENGTH 16` to `config.h`. Possible values: 8 (default), 16, 32.

## Dictionary Management
When a large number of combos are present, duplicating code in 3 places can become tedious.

This is issue is solved by the [Combo Engine](http://combos.gboards.ca/), which allows to eliminate duplication. Under the hood, the Combo Feature is used and the above configuration will work with it.

## Deprecated features

#### Setting the number of combos via `COMBO_COUNT`

This macro is deprecated in favor of `COMBO_LEN` constant.

#### Custom combo handling via `process_combo_event`

For custom handling of combos, you could use `COMBO_ACTION` (instead of `COMBO`) inside `key_combos`, together with `process_combo_event` function.

This method is deprecated in favor of processing combo results in `process_record_user`. You may also need to create custom keycodes.
