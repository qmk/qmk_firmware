# Quantum Painter LVGL Integration :id=lvgl

LVGL (Light and Versatile Graphics Library) is an open-source graphics library providing everything you need to create an embedded GUI for your board with easy-to-use graphical elements.

LVGL integrates with [Quantum Painter's](quantum_painter.md) API and drivers to render to the display, the hardware supported by Quantum Painter is also supported by LVGL.

?> Keep in mind that enabling the LVGL integration has a big impact in firmware size, it is recommeded to use a supported MCU with >256 kB of flash space.

To learn more about LVGL and how to use it please take a look at their [official documentation](https://docs.lvgl.io/8.2/intro/)

## Enabling LVGL :id=lvgl-enabling
To enable LVGL to be built into your firmware, add the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS = ......
QUANTUM_PAINTER_LVGL_INTEGRATION = yes
```
To configure the Quantum Painter Display Drivers please read the [Quantum Painter Display Drivers](quantum_painter.md#quantum-painter-drivers) section.

## Quantum Painter LVGL API :id=lvgl-api

### Quantum Painter LVGL Attach :id=lvgl-api-init

```c
bool qp_lvgl_attach(painter_device_t device);
```

The `qp_lvgl_attach` function is used to set up LVGL with the supplied display, and requires an already configured display.

```c
static painter_device_t display;
void keyboard_post_init_kb(void) {
    display = qp_make_.......;         // Create the display
    qp_init(display, QP_ROTATION_0);   // Initialise the display
    
    if (qp_lvgl_attach(display)) {     // Attach LVGL to the display
        ...Your code to draw           // Run LVGL specific code to draw
    }
}
```
To init. the display please read the [Display Initialisation](quantum_painter.md#quantum-painter-api-init) section.

!> Attaching LVGL to a display means LVGL subsequently "owns" the display. Using standard Quantum Painter drawing operations with the display after LVGL attachment will likely result in display artifacts.
### Quantum Painter LVGL Detach :id=lvgl-api-init

```c
void qp_lvgl_detach()
```

The `qp_lvgl_detach` function stops the internal LVGL ticks and releases resources related to it.

## Enabling/Disabling LVGL features :id=lvgl-configuring

You can overwrite LVGL specific features in your `lv_conf.h` file.
