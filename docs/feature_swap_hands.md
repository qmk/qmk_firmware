# Swap-Hands Action

The swap-hands action allows support for one-handed typing without requiring a separate layer. Set `SWAP_HANDS_ENABLE` in the Makefile and define a `hand_swap_config` entry in your keymap. Now whenever the `ACTION_SWAP_HANDS` command key is pressed the keyboard is mirrored. For instance, to type "Hello, World" on QWERTY you would type `^Ge^s^s^w^c W^wr^sd`

## Configuration

The configuration table is a simple 2-dimensional array to map from column/row to new column/row. Example `hand_swap_config` for Planck:

```c
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{11, 0}, {10, 0}, {9, 0}, {8, 0}, {7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
  {{11, 1}, {10, 1}, {9, 1}, {8, 1}, {7, 1}, {6, 1}, {5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
  {{11, 2}, {10, 2}, {9, 2}, {8, 2}, {7, 2}, {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
  {{11, 3}, {10, 3}, {9, 3}, {8, 3}, {7, 3}, {6, 3}, {5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
};
```

Note that the array indices are reversed same as the matrix and the values are of type `keypos_t` which is `{col, row}` and all values are zero-based. In the example above, `hand_swap_config[2][4]` (third row, fifth column) would return `{7, 2}` (third row, eighth column). Yes, this is confusing.

## Swap Keycodes

|Key                          |Aliases  |Description                                         |
|-----------------------------|---------|----------------------------------------------------|
|`SH_T(kc)`                   |         |Momentary swap when held, `kc` when tapped          |
|`QK_SWAP_HANDS_ON`           |`SH_ON`  |Turn on hand swap                                   |
|`QK_SWAP_HANDS_OFF`          |`SH_OFF` |Turn off hand swap                                  |
|`QK_SWAP_HANDS_MOMENTARY_ON` |`SH_MON` |Turn on hand swap while held                        |
|`QK_SWAP_HANDS_MOMENTARY_OFF`|`SH_MOFF`|Turn off hand swap while held                       |
|`QK_SWAP_HANDS_TOGGLE`       |`SH_TOGG`|Toggle hand swap                                    |
|`QK_SWAP_HANDS_TAP_TOGGLE`   |`SH_TT`  |Momentary swap when held, toggle when tapped        |
|`QK_SWAP_HANDS_ONE_SHOT`     |`SH_OS`  |Turn on hand swap while held or until next key press|

`SH_TT` swap-hands tap-toggle key is similar to [layer tap-toggle](feature_layers.md?id=switching-and-toggling-layers). Tapping repeatedly (5 taps by default) will toggle swap-hands on or off, like `SH_TOGG`. Tap-toggle count can be changed by defining a value for `TAPPING_TOGGLE`.

## Encoder Mapping

When using an encoder mapping, it's also able to handle swapping encoders between sides, too.

Encoder indexes are defined as left-to-right, and the extent of the array needs to match the number of encoders on the keyboard.

As an example, if a split keyboard has a single encoder per side, you can swap the order by using the following code in your keymap:
```c
#if defined(SWAP_HANDS_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = { 1, 0 };
#endif
```

### Functions :id=functions

User callback functions to manipulate Swap-Hands:

| Function              | Description                                 |
|-----------------------|---------------------------------------------|
| `swap_hands_on()`     | Turns Swap-Hands on.                        |
| `swap_hands_off()`    | Turns Swap-Hands off.                       |
| `swap_hands_toggle()` | Toggles Swap-Hands.                         |
| `is_swap_hands_on()`  | Returns true if Swap-Hands is currently on. |
