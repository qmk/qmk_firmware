# Swap-Hands Action

The swap-hands action allows support for one-handed typing without requiring a separate layer. Set `SWAP_HANDS_ENABLE` in the Makefile and define a `hand_swap_config` entry in your keymap. Now whenever the `ACTION_SWAP_HANDS` command key is pressed the keyboard is mirrored. For instance, to type "Hello, World" on QWERTY you would type `^Ge^s^s^w^c W^wr^sd`

## Configuration

The configuration table is a simple 2-dimensional array to map from column/row to new column/row. Example `hand_swap_config` for Planck:

```C
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
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
|`SH_TT`    |Toggles with a tap; momentary when held.                                 |
