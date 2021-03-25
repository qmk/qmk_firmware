# Combos

The Combo feature lets you customize key presses that are produced when multiple keys are hit at once. For instance, hitting `A` and `S` within the combo term would hit `ESC` instead, or have it perform even more complex tasks.

To enable this feature:

0. Instead of defining layer names, custom keycodes and other "keymap items" in the `keymap.c`, define them in `keymap.h` and `#include` it in `keymap.c`
1. Add `COMBO_ENABLE = yes` to your `rules.mk`
2. Add `SRC += combos.cpp` to your `rules.mk`
3. Define the combos in `combos.cpp` (next to `keymap.c`), following the example below

```cpp
#include "make_combos.hpp"

extern "C" {
#include QMK_KEYBOARD_H
#include "keymap.h"
}

enum combo_keys {
    LTOP1, LTOP2, LTOP3, LTOP4, LTOP5, RTOP1, RTOP2, RTOP3, RTOP4, RTOP5,
    LBOT1, LBOT2, LBOT3, LBOT4, LBOT5, RBOT1, RBOT2, RBOT3, RBOT4, RBOT5,
};

static constexpr auto combos_data_instance PROGMEM = make_combos_data(
    combo_layer<NAV>({
        {KC_TAB, {LTOP1, LBOT1}},
        {KC_HOME, {LTOP2, RTOP2}},
    }),
    combo_layer<SYM>({
        {KC_MINS, {LTOP1, LBOT1}},
    })
);

extern "C" constexpr auto combos PROGMEM = make_combos(LAYOUT_yourkeeb(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    LTOP1, LTOP2, LTOP3, LTOP4, LTOP5, RTOP1, RTOP2, RTOP3, RTOP4, RTOP5,
    LBOT1, LBOT2, LBOT3, LBOT4, LBOT5, RBOT1, RBOT2, RBOT3, RBOT4, RBOT5,
), combos_data_instance);
```

Let's look at each of its parts:

- Each physical key, which can participate in a combo on some layer, is given a name using `combo_keys` enum
- They are then placed in the keymap using `make_combos`. Non-combo keys are marked as such using `KC_NO`
- Combos are defined using `make_combos_data`, which takes a list of layers. Each layer begins with a layer id (from `keymap.h`), followed by a list of combos, which are active on that layer
- Each combo starts with its `uint16_t` keycode, followed by an array of combo keys that make up the combo. Full range of keycodes is supported, including layer tap, mod tap, tap dance and custom keys

## Combo feature toggle
Sometimes it's useful to disable combos temporarily, such as for a game. For that purpose, special keycodes are available for use in your keymap. It's also possible to toggle combos from user code using functions:

|Keycode   |Function call        |Description                                |
|---------:|--------------------:|:------------------------------------------|
|`CMB_ON`  |`combo_enable()`     |Turns on Combo feature                     |
|`CMB_OFF` |`combo_disable()`    |Turns off Combo feature                    |
|`CMB_TOG` |`combo_toggle()`     |Toggles Combo feature on and off           |
|N/A       |`is_combo_enabled()` |Returns `true` if Combo feature is enabled |

## Limitations

The maximum number of combo keys is defined by `COMBO_KEY_COUNT` (default: 32). If your keyboard contains a lot of keys and you want all of them to be combo-capable, you may need to increase the limit.

If you need to press a lot of keys at the same time, you may need to increase `COMBO_BUFFER_SIZE` (default: 8).

## Combo term
By default, the timeout for the combos to be recognized is set to 50ms. This can be changed if accidental combo misfires are happening or if you're having difficulties pressing keys at the same time. For instance, add `#define COMBO_TERM 100` to your `config.h` to set the timeout period for combos to 100ms.

#### Per combo timing
You can customize combo term per combo by adding `combo_term` to the combo definition:

```cpp
{KC_TAB, {LTOP1, LBOT1}, combo_term{200}},
```

#### Delaying non-combo keys
By default, `COMBO_TERM` is imposed on keys that participate in some combo on the current layer. This creates inconsistency between the delay for combo keys and non-combo keys.

You can force combo term on non-combo keys by implementing `uint16_t key_combo_term(uint16_t keycode, const keyrecord_t *record)` function in `keymap.c` (default: returns 0). For example, you can `return COMBO_TERM`, or depend on the currently active layer or on the keycode.

## Urgent combos
Normally, combos are only fired when their combo term passes. You can mark some combos as "urgent" to make them fire immediately by adding `combo_urgent` to the combo definition:

```cpp
{KC_LSFT, {LTOP1, LBOT1}, combo_urgent{}}
```

Urgency is most useful for layer tap, mod tap and other modifiers.

Caveats:

- Combos with nested key lists will break: the smaller combo will trigger immediately
- Urgent combos and other keys and combos may be reordered, e.g. if pressing a normal combo, then, within combo term, an urgent combo, the urgent combo will take effect before the normal one

## All-layer combos

You can put `ALL_LAYER_COMBOS` instead of the layer id for the first combo layer. In that case its combos will be active on all layers.

## Custom combo actions

#### Sending a string

Instead of emitting a keycode, a combo can emit a string using `SEND_STRING`:

```cpp
{"Hello world!"_pgm, {LTOP1, LBOT1}}
```

#### Calling a function

A combo can call a function with signature `void(bool enabled)`:

```cpp
{foo, {LTOP1, LBOT1}}
```

> WARNING: Combo actions defined in this way bypass any preprocessing by such QMK layers as Key Locking and WPM counting. It's instead recommended to assign the combo a custom keycode and then handle it in `combo_action_user`.
