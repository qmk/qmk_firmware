# Tri Layers {#tri-layers}

This enables support for the OLKB style "Tri Layer" keycodes.  These function similar to the `MO` (momentary) function key, but if both the "Lower" and "Upper" keys are pressed, it activates a third "Adjust" layer.  To enable this functionality, add this line to your `rules.mk`:

```make
TRI_LAYER_ENABLE = yes
```

Note that the "upper", "lower" and "adjust" names don't have a particular significance, they are just used to identify and clarify the behavior. Layers are processed from highest numeric value to lowest, however the values are not required to be consecutive.

For a detailed explanation of how the layer stack works, check out [Keymap Overview](../keymap#keymap-and-layers).

## Keycodes {#keycodes}

| Keycode              | Alias     | Description                                                                                             |
|----------------------|-----------|---------------------------------------------------------------------------------------------------------|
| `QK_TRI_LAYER_LOWER` | `TL_LOWR` | Momentarily enables the "lower" layer. Enables the "adjust" layer if the "upper" layer is also enabled. |
| `QK_TRI_LAYER_UPPER` | `TL_UPPR` | Momentarily enables the "upper" layer. Enables the "adjust" layer if the "lower" layer is also enabled. |

## Configuration

To change the default values for the layers, you can change these defines, in your `config.h`

| Config name              | Default | Description                              |
|--------------------------|---------|------------------------------------------|
| `TRI_LAYER_LOWER_LAYER`  | `1`     | Sets the default for the "lower" layer.  |
| `TRI_LAYER_UPPER_LAYER`  | `2`     | Sets the default for the "upper" layer.  |
| `TRI_LAYER_ADJUST_LAYER` | `3`     | Sets the default for the "adjust" layer. |

Eg, if you wanted to set the "Adjust" layer to be layer 5, you'd add this to your `config.h`: 

```c
#define TRI_LAYER_ADJUST_LAYER 5
```

## Functions

| Function name                                |  Description                                    |
|----------------------------------------------|-------------------------------------------------|
| `set_tri_layer_lower_layer(layer)`           | Changes the "lower" layer*.                     |
| `set_tri_layer_upper_layer(layer)`           | Changes the "upper" layer*.                     |
| `set_tri_layer_adjust_layer(layer)`          | Changes the "adjust" layer*.                    |
| `set_tri_layer_layers(lower, upper, adjust)` | Sets the "lower", "upper" and "adjust" layers*. |
| `get_tri_layer_lower_layer()`                | Gets the current "lower" layer.                 |
| `get_tri_layer_upper_layer()`                | Gets the current "upper" layer.                 |
| `get_tri_layer_adjust_layer()`               | Gets the current "adjust" layer.                |

::: warning
Note: these settings are not persistent, and will be reset to the default on power loss or power cycling of the controller.
:::
