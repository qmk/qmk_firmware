# Dilemma `via` keymap

The Dilemma `via` keymap is based on a QWERTY layout with [home row mods](https://precondition.github.io/home-row-mods) and [Miryoku-inspired layers](https://github.com/manna-harbour/miryoku), and some features and changes specific to the Dilemma.

This layout also supports VIA.

## Customizing the keymap

### Dynamic DPI scaling

Use the following keycodes to change the default DPI:

-   `POINTER_DEFAULT_DPI_FORWARD`: increases the DPI; decreases when shifted;
-   `POINTER_DEFAULT_DPI_REVERSE`: decreases the DPI; increases when shifted.

There's a maximum of 16 possible values for the sniping mode DPI. See the [Dilemma documentation](../../README.md) for more information.

Use the following keycodes to change the sniping mode DPI:

-   `POINTER_SNIPING_DPI_FORWARD`: increases the DPI; decreases when shifted;
-   `POINTER_SNIPING_DPI_REVERSE`: decreases the DPI; increases when shifted.

There's a maximum of 4 possible values for the sniping mode DPI. See the [Dilemma documentation](../../README.md) for more information.

### Drag-scroll

Use the `DRAGSCROLL_MODE` keycode to enable drag-scroll on hold. Use the `DRAGSCROLL_TOGGLE` keycode to enable/disable drag-scroll on key press.

### Circular scroll

By default, the firmware is configured to enable the circular scroll feature on Cirque trackpad.

To disable this, add the following to your keymap:

```c
#undef POINTING_DEVICE_GESTURES_SCROLL_ENABLE
```

### Sniping

Use the `SNIPING_MODE` keycode to enable sniping mode on hold. Use the `SNIPING_TOGGLE` keycode to enable/disable sniping mode on key press.

Change the value of `DILEMMA_AUTO_SNIPING_ON_LAYER` to automatically enable sniping mode on layer change. By default, sniping mode is enabled on the pointer layer:

```c
#define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER
```

### Auto pointer layer

The pointer layer can be automatically enabled when moving the trackball. To enable or disable this behavior, add or remove the following define:

```c
#define DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE
```

By default, the layer is turned off 1 second after the last registered trackball movement:

```c
#define DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
```

The trigger sensibility can also be tuned. The lower the value, the more sensible the trigger:

```c
#define DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
```
