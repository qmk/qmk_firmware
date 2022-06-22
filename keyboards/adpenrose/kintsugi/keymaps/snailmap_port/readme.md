# SnailMap-ported keymap for the Kintsugi

## Features

- Keyboard matrix that highlights whichever key is currently pressed.
- Little cute snail icon that changes acording to the current WPM.
- Counters for current and max WPM values.
- Active layer name.
- Mini WPM graph.

## How to customize

The `OLED configuration variables` can be used to easily customize the display:

```
oled_horizontal     - Horizontal or vertical orientation
graph_direction     - Graph movement direction
graph_refresh       - Frequency of graph lines
graph_top_wpm       - WPM required to reach the top of the graph
icon_med_wpm        - WPM required to display the medium snail
icon_fast_wpm       - WPM required to display the fast snail
MA_LAYER_NAME       - Layer 0 display name
L1_LAYER_NAME       - Layer 1 display name
L2_LAYER_NAME       - Layer 2 display name
L3_LAYER_NAME       - Layer 3 display name
```

___

###### *This keymap is an adaptation designed to work with the Kintsugi keyboard. The original SnailMap keymap was created by [dogspace](https://github.com/dogspace) for the Nibble keyboard, and you can check it [here](https://github.com/qmk/qmk_firmware/tree/master/keyboards/nullbitsco/nibble/keymaps/snailmap).*