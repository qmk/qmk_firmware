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
void qp_lvgl_detach(void)
```

The `qp_lvgl_detach` function stops the internal LVGL ticks and releases resources related to it.

## Enabling/Disabling LVGL features :id=lvgl-configuring

You can overwrite LVGL specific features in your `lv_conf.h` file.

## Changing the LVGL task frequency

When LVGL is running, your keyboard's responsiveness may decrease, causing missing keystrokes or encoder rotations, especially during the animation of dynamically-generated content. This occurs because LVGL operates as a scheduled task with a default task rate of five milliseconds. While a fast task rate is advantageous when LVGL is responsible for detecting and processing inputs, it can lead to excessive recalculations of displayed content, which may slow down QMK's matrix scanning. If you rely on QMK instead of LVGL for processing inputs, it can be beneficial to increase the time between calls to the LVGL task handler to better match your preferred display update rate. To do this, add this to your `config.h`:

```c
#define QP_LVGL_TASK_PERIOD 40
```

## Adding Custom Fonts with LVGL :id=lvgl-fonts

[LVGL Custom Fonts Documentation](https://docs.lvgl.io/master/overview/font.html#add-a-new-font)

If you are using LVGL in your project, you want to avoid using Quantum Painter drawing operations for custom fonts. To add custom fonts to LVGL you can follow these steps:


1. Use the [LVGL Online Font Converter](https://lvgl.io/tools/fontconverter) or [LVGL Offline Font Converter](https://github.com/lvgl/lv_font_conv) to convert a .ttf or .woff font to a C file that you can include in your project.
> A good naming convention for your font is `my_font_name_12` to indicate the font name and size when referencing it in your code.

!> **Note:** You will need to generate a new C file for each font size you want to use in your project. In order to reduce your firmware size, it is highly recommended to specify the exact set of characters you will use.

2. Create a new folder in `/keyboards/<keyboard>/fonts` and copy your generated C font files to the folder. You can also place it in your root keyboard folder if you want to share the font with multiple keyboards.

3. Open the .c font file and modify the include `lvgl.h` to point to the `lvgl.h` file in the firmware. If you selected the option to use a fallback font, you may also need to include it.
```c
...
//#include "lvgl/lvgl.h" // replace this
#include "../../lvgl.h" // pointing to qmk firmware lvgl.h
...
```
Alternatively, you can define `#define LV_LVGL_H_INCLUDE_SIMPLE` in your `config.h` file file

4. Include the .c font file in your `rules.mk`:
```
SRC += fonts/my_font_name_12.c \
       fonts/my_font_name_14.c
```

5. To use the font in your code:
```c
LV_FONT_DECLARE(my_font_name_12);
lv_obj_set_style_text_font(text_label, &my_font_name_12, LV_PART_MAIN);
```
