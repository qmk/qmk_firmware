# Charybdis (6x4, 5x3 "Nano")

An ergonomic keyboard with integrated trackball.

Engineered to be a full mouse replacement solution with high-quality,
custom-developed components.

There are 6x4 and 5x3 "Nano" versions.

-   Keyboard Maintainer: [Bastard Keyboards](https://github.com/Bastardkb)
-   Hardware Supported: elite-C V4
-   Hardware Availability: [Bastard Keyboards](https://bastardkb.com)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for more information.

Brand new to QMK? Start with the [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Check out the [keyboard build guides](https://docs.bastardkb.com) for the
Charybdis and other ergonomic keyboards.

## Building the firmware

### Charybdis (4x6)

The `default` keymap is inspired from the original [Dactyl
Manuform](../../handwired/dactyl_manuform) layout.

```shell
qmk compile -kb bastardkb/charybdis/4x6 -km default
```

Check out the `stock` layout if you're looking for Via/Vial support:

```shell
qmk compile -kb bastardkb/charybdis/4x6 -km stock
```

### Charybdis (3x5)

The `default` keymap is inspired from the original [Dactyl
Manuform](../../handwired/dactyl_manuform) layout.

```shell
qmk compile -kb bastardkb/charybdis/3x5 -km default
```

Check out the `stock` layout if you're looking for Via/Vial support:

```shell
qmk compile -kb bastardkb/charybdis/3x5 -km stock
```

## Customizing the firmware

### Dynamic DPI scaling

The pointer's DPI can be changed at runtime.

By default, the DPI is set to `400`. The Charybdis supports up to 16 different
DPI values. By default, it cycles between `400` and `3400`, with a step of
`200` (_ie._ `400`, `600`, `800`, …, `3400`).

Calling `charybdis_cycle_pointer_default_dpi(bool forward)` will cycle forward
or backward the possible values.

Use `charybdis_cycle_pointer_default_dpi_noeeprom(bool forward)` to change the
DPI value without persisting the change to EEPROM (_ie._ resetting the board
will revert to the last saved value).

`charybdis_get_pointer_default_dpi()` returns the current DPI value.

This behavior can be further customized with the following defines:

```c
#define CHARYBDIS_MINIMUM_DEFAULT_DPI 400
#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 200
```

### Drag-scroll

Drag-scroll enables scrolling with the trackball. When drag-scroll is enabled,
the trackball's `x` and `y` movements are converted into `h` (horizontal) and
`v` (vertical) movement, effectively sending scroll instructions to the host
system.

Call `charybdis_set_pointer_dragscroll_enabled(bool enable)` to enable/disable
drag-scroll.

`charybdis_get_pointer_dragscroll_enabled()` returns whether sniping mode is
currently enabled.

To invert the horizontal scrolling direction, define
`CHARYBDIS_DRAGSCROLL_REVERSE_X`:

```c
#define CHARYBDIS_DRAGSCROLL_REVERSE_X
```

To invert the vertical scrolling direction (_ie._ mimic macOS "natural" scroll
direction), define `CHARYBDIS_DRAGSCROLL_REVERSE_Y`:

```c
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y
```

This only affects the vertical scroll direction.

### Sniping mode

Sniping mode slows down the pointer for more precise gestures. It is useful
when combined with a higher default DPI.

Call `charybdis_set_pointer_sniping_enabled(bool enable)` to enable/disable
sniping mode.

`charybdis_get_pointer_sniping_enabled()` returns whether sniping mode is
currently enabled.

Like the default pointer's DPI, the sniper mode DPI can be changed at runtime.

By default, sniping mode lowers the DPI to `200`. This can be changed at
runtime: the Charybdis supports up to 4 different DPI values for sniping mode.
By default, it cycles between `200`, `300`, `400` and `500`.

Calling `charybdis_cycle_pointer_sniping_dpi(bool forward)` will cycle forward
or backward the possible values.

Use `charybdis_cycle_pointer_sniping_dpi_noeeprom(bool forward)` to change the
sniping mode DPI value without persisting the change to EEPROM (_ie._ resetting
the board will revert to the last saved value).

`charybdis_get_pointer_sniping_dpi()` returns the current sniping mode DPI
value.

This behavior can be further customized with the following defines:

```c
#define CHARYBDIS_MINIMUM_SNIPING_DPI 200
#define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 100
```

### Acceleration

By default, the pointer's movements are linear. To enable acceleration, add the
following define:

```c
#define CHARYBDIS_POINTER_ACCELERATION_ENABLE
```

The acceleration factor can be further tune _via_ the
`CHARYBDIS_POINTER_ACCELERATION_FACTOR`:

```c
#define CHARYBDIS_POINTER_ACCELERATION_FACTOR 24
```
