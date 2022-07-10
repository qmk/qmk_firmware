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

|Key        |Description                                                              |
|-----------|-------------------------------------------------------------------------|
|`SH_T(key)`|Sends `key` with a tap; momentary swap when held.                        |
|`SH_ON`    |Turns on swapping and leaves it on.                                      |
|`SH_OFF`   |Turn off swapping and leaves it off. Good for returning to a known state.|
|`SH_MON`   |Swaps hands when pressed, returns to normal when released (momentary).   |
|`SH_MOFF`  |Momentarily turns off swap.                                              |
|`SH_TG`    |Toggles swap on and off with every key press.                            |
|`SH_TT`    |Momentary swap when held, toggles with repeated taps (see below).        |
|`SH_OS`    |One shot swap hands: toggles while pressed or until next key press.      |

`SH_TT` swap-hands tap-toggle key is similar to [layer tap-toggle](feature_layers.md?id=switching-and-toggling-layers). Tapping repeatedly (5 taps by default) will toggle swap-hands on or off, like `SH_TG`. Tap-toggle count can be changed by defining a value for `TAPPING_TOGGLE`.

## Encoder Mapping

When using an encoder mapping, it's also able to handle swapping encoders between sides, too.

Encoder indexes are defined as left-to-right, and the extent of the array needs to match the number of encoders on the keyboard.

As an example, if a split keyboard has a single encoder per side, you can swap the order by using the following code in your keymap:
```c
#if defined(SWAP_HANDS_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = { 1, 0 };
#endif
```
