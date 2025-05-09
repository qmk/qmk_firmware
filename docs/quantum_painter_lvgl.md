# Quantum Painter LVGL Integration {#lvgl}

LVGL (Light and Versatile Graphics Library) is an open-source graphics library providing everything you need to create an embedded GUI for your board with easy-to-use graphical elements.

LVGL integrates with [Quantum Painter's](quantum_painter) API and drivers to render to the display, the hardware supported by Quantum Painter is also supported by LVGL.

::: tip
Keep in mind that enabling the LVGL integration has a big impact in firmware size, it is recommeded to use a supported MCU with >256 kB of flash space.
:::

To learn more about LVGL and how to use it please take a look at their [official documentation](https://docs.lvgl.io/8.2/intro/)

## Enabling LVGL {#lvgl-enabling}
To enable LVGL to be built into your firmware, add the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS = ......
QUANTUM_PAINTER_LVGL_INTEGRATION = yes
```
To configure the Quantum Painter Display Drivers please read the [Quantum Painter Display Drivers](quantum_painter#quantum-painter-drivers) section.

## Quantum Painter LVGL API {#lvgl-api}

### Quantum Painter LVGL Attach {#lvgl-api-init}

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
To init. the display please read the [Display Initialisation](quantum_painter#quantum-painter-api-init) section.

::: warning
Attaching LVGL to a display means LVGL subsequently "owns" the display. Using standard Quantum Painter drawing operations with the display after LVGL attachment will likely result in display artifacts.
:::

### Quantum Painter LVGL Detach {#lvgl-api-detach}

```c
void qp_lvgl_detach(void)
```

The `qp_lvgl_detach` function stops the internal LVGL ticks and releases resources related to it.

## Enabling/Disabling LVGL features {#lvgl-configuring}

You can overwrite LVGL specific features in your `lv_conf.h` file.

## Changing the LVGL task frequency

When LVGL is running, your keyboard's responsiveness may decrease, causing missing keystrokes or encoder rotations, especially during the animation of dynamically-generated content. This occurs because LVGL operates as a scheduled task with a default task rate of five milliseconds. While a fast task rate is advantageous when LVGL is responsible for detecting and processing inputs, it can lead to excessive recalculations of displayed content, which may slow down QMK's matrix scanning. If you rely on QMK instead of LVGL for processing inputs, it can be beneficial to increase the time between calls to the LVGL task handler to better match your preferred display update rate. To do this, add this to your `config.h`:

```c
#define QP_LVGL_TASK_PERIOD 40
```
