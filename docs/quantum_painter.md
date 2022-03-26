# Quantum Painter :id=quantum-painter

Quantum Painter is the standardised API for graphical displays. It currently includes support for basic drawing primitives, as well as custom images, animations, and fonts.

Due to the complexity, there is no support for Quantum Painter on AVR-based boards.

To enable overall Quantum Painter to be built into your firmware, add the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS = ......
```

You will also likely need to select an appropriate driver in `rules.mk`, which is listed below.

!> Quantum Painter is not currently integrated with system-level operations such as disabling displays after a configurable timeout, or when the keyboard goes into suspend. Users will need to handle this manually a the current time.

The QMK CLI can be used to convert from normal images such as PNG files or animated GIFs, as well as fonts from TTF files.

Hardware supported:

| Display Panel | Panel Type         | Size             | Comms Transport | Driver                                  |
|---------------|--------------------|------------------|-----------------|-----------------------------------------|
| GC9A01        | RGB LCD (circular) | 240x240          | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS = gc9a01_spi`  |
| ILI9163       | RGB LCD            | 128x128          | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS = ili9163_spi` |
| ILI9341       | RGB LCD            | 240x320          | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS = ili9341_spi` |
| SSD1351       | RGB OLED           | 128x128          | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS = ssd1351_spi` |
| ST7789        | RGB LCD            | 240x320, 240x240 | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS = st7789_spi`  |

## Quantum Painter Configuration :id=quantum-painter-config

| Option                                  | Default | Purpose                                                                                                                                     |
|-----------------------------------------|---------|---------------------------------------------------------------------------------------------------------------------------------------------|
| `QUANTUM_PAINTER_NUM_IMAGES`            | `8`     | The maximum number of images/animations that can be loaded at any one time.                                                                 |
| `QUANTUM_PAINTER_NUM_FONTS`             | `4`     | The maximum number of fonts that can be loaded at any one time.                                                                             |
| `QUANTUM_PAINTER_CONCURRENT_ANIMATIONS` | `4`     | The maximum number of animations that can be executed at the same time.                                                                     |
| `QUANTUM_PAINTER_LOAD_FONTS_TO_RAM`     | `FALSE` | Whether or not fonts should be loaded to RAM. Relevant for fonts stored in off-chip persistent storage, such as external flash.             |
| `QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE`   | `32`    | The limit of the amount of pixel data that can be transmitted in one transaction to the display. Higher values require more RAM on the MCU. |
| `QUANTUM_PAINTER_SUPPORTS_256_PALETTE`  | `FALSE` | If 256-color palettes are supported. Requires significantly more RAM on the MCU.                                                            |

Drivers have their own set of configurable options, and are described in their respective sections.

## Quantum Painter CLI Commands :id=quantum-painter-cli

!! TBD !!

## Quantum Painter Drawing API :id=quantum-painter-api

All APIs require a `painter_device_t` object as their first parameter -- this object comes from the specific device initialisation, and instructions on creating it can be found in each driver's respective section.

To use any of the APIs, you need to include `qp.h`:
```c
#include <qp.h>
```

### General Notes :id=quantum-painter-api-general

The coordinate system used in Quantum Painter generally accepts `left`, `top`, `right`, and `bottom` instead of x/y/width/height, and each coordinate is inclusive of where pixels should be drawn. This is required as some datatypes used by display panels have a maximum value of `255` -- for any value or geometry extent that matches `256`, this would be represented as a `0`, instead.

?> Drawing a horizontal line 8 pixels long, starting from 4 pixels inside the left side of the display, will need `left=4`, `right=11`.

All color data matches the standard QMK HSV triplet definitions:

* Hue is of the range `0...255` and is internally mapped to 0...360 degrees.
* Saturation is of the range `0...255` and is internally mapped to 0...100% saturation.
* Value is of the range `0...255` and is internally mapped to 0...100% brightness.

?> Colors used in Quantum Painter are not subject to the RGB lighting CIE curve, if it is enabled.

### Device Control :id=quantum-painter-api-device-control

#### Display Initialisation :id=quantum-painter-api-init

```c
bool qp_init(painter_device_t device, painter_rotation_t rotation);
```

The `qp_init` function is used to initialise a display device after it has been created. This accepts a rotation parameter (`QP_ROTATION_0`, `QP_ROTATION_90`, `QP_ROTATION_180`, `QP_ROTATION_270`), which makes sure that the orientation of what's drawn on the display is correct.

#### Display Power :id=quantum-painter-api-power

```c
bool qp_power(painter_device_t device, bool power_on);
```

The `qp_power` function instructs the display whether or not the display panel should be on or off.

!> If there is a separate backlight controlled through the normal QMK backlight API, this is not controlled by the `qp_power` function and needs to be manually handled elsewhere.

#### Display Clear :id=quantum-painter-api-clear

```c
bool qp_clear(painter_device_t device);
```

The `qp_clear` function clears the display's screen.

#### Display Flush :id=quantum-painter-api-flush

```c
bool qp_flush(painter_device_t device);
```

The `qp_flush` function ensures that all drawing operations are "pushed" to the display. This should be done as the last operation whenever a sequence of draws occur, and guarantees that any changes are applied.

!> Some display panels may seem to work even without a call to `qp_flush` -- this may be because the driver cannot queue drawing operations and needs to display them immediately when invoked. In general, calling `qp_flush` at the end is still considered "best practice".

### Drawing Primitives :id=quantum-painter-api-primitives

#### Set Pixel :id=quantum-painter-api-setpixel

```c
bool qp_setpixel(painter_device_t device, uint16_t x, uint16_t y, uint8_t hue, uint8_t sat, uint8_t val);
```

The `qp_setpixel` can be used to set a specific pixel on the screen to the supplied color.

?> Using `qp_setpixel` for large amounts of drawing operations is inefficient and should be avoided unless they cannot be achieved with other drawing APIs.

#### Draw Line :id=quantum-painter-api-line

```c
bool qp_line(painter_device_t device, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t hue, uint8_t sat, uint8_t val);
```

The `qp_line` can be used to draw lines on the screen with the supplied color.

#### Draw Rect :id=quantum-painter-api-rect

```c
bool qp_rect(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint8_t hue, uint8_t sat, uint8_t val, bool filled);
```

The `qp_rect` can be used to draw rectangles on the screen with the supplied color, with or without a background fill. If not filled, any pixels inside the rectangle will be left as-is.

#### Draw Circle :id=quantum-painter-api-circle

```c
bool qp_circle(painter_device_t device, uint16_t x, uint16_t y, uint16_t radius, uint8_t hue, uint8_t sat, uint8_t val, bool filled);
```

The `qp_circle` can be used to draw circles on the screen with the supplied color, with or without a background fill. If not filled, any pixels inside the circle will be left as-is.

#### Draw Ellipse :id=quantum-painter-api-ellipse

```c
bool qp_ellipse(painter_device_t device, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint8_t hue, uint8_t sat, uint8_t val, bool filled);
```

The `qp_ellipse` can be used to draw ellipses on the screen with the supplied color, with or without a background fill. If not filled, any pixels inside the ellipses will be left as-is.

### Image Functions :id=quantum-painter-api-images

#### Load Image :id=quantum-painter-api-load-image

```c
painter_image_handle_t qp_load_image_mem(const void *buffer);
```

The `qp_load_image_mem` function loads a QGF image from memory or flash.

`qp_load_image_mem` returns a handle to the loaded image, which can then be used to draw to the screen using `qp_drawimage`, `qp_drawimage_recolor`, `qp_animate`, or `qp_animate_recolor`. If an image is no longer required, it can be unloaded by calling `qp_close_image` below. 

See the [CLI Commands](quantum_painter.md?id=quantum-painter-cli) for instructions on how to convert images to [QGF](quantum_painter_qgf.md).

?> The total number of images available to load at any one time is controlled by the configurable option `QUANTUM_PAINTER_NUM_IMAGES` in the table above. If more images are required, the number should be increased in `config.h`.

Image information is available through accessing the handle:

```c
// Draw an image on the bottom-right of the 240x320 display
painter_device_t display = .......;
painter_image_handle_t image = qp_load_image_mem(gfx_my_image);
qp_drawimage(display, (239 - image->width), (319 - image->height), image); // also `image->frame_count` for animations
```

#### Unload Image :id=quantum-painter-api-close-image

```c
bool qp_close_image(painter_image_handle_t image);
```

The `qp_close_image` function releases resources related to the loading of the supplied image.

#### Draw image :id=quantum-painter-api-draw-image

```c
bool qp_drawimage(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image);
bool qp_drawimage_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);
```

The `qp_drawimage` and `qp_drawimage_recolor` functions draw the supplied image to the screen at the supplied location, with the latter function allowing for monochrome-based images to be recolored.

#### Animate Image :id=quantum-painter-api-animate-image

```c
deferred_token qp_animate(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image);
deferred_token qp_animate_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);
```

The `qp_animate` and `qp_animate_recolor` functions draw the supplied image to the screen at the supplied location, with the latter function allowing for monochrome-based animations to be recolored. They also set up internal timing such that each frame is rendered at the correct time as per the animated image.

Once an image has been set to animate, it will loop indefinitely until stopped, with no user intervention required.

Both functions return a `deferred_token`, which can then be used to stop the animation, using `qp_stop_animation` below.

#### Stop Animation :id=quantum-painter-api-stop-animation

```c
void qp_stop_animation(deferred_token anim_token);
```

The `qp_stop_animation` function stops the previously-started animation.

### Font Functions :id=quantum-painter-api-fonts

#### Load Font :id=quantum-painter-api-load-font

```c
painter_font_handle_t qp_load_font_mem(const void *buffer);
```

The `qp_load_font_mem` function loads a QFF font from memory or flash.

`qp_load_font_mem` returns a handle to the loaded font, which can then be measured using `qp_textwidth`, or drawn to the screen using `qp_drawtext`, or `qp_drawtext_recolor`. If a font is no longer required, it can be unloaded by calling `qp_close_font` below. 

See the [CLI Commands](quantum_painter.md?id=quantum-painter-cli) for instructions on how to convert TTF fonts to [QFF](quantum_painter_qff.md).

?> The total number of fonts available to load at any one time is controlled by the configurable option `QUANTUM_PAINTER_NUM_FONTS` in the table above. If more fonts are required, the number should be increased in `config.h`.

Font information is available through accessing the handle:

```c
// Draw text on the bottom-right of the 240x320 display
painter_device_t display = .......;
painter_font_handle_t font = qp_load_font_mem(font_opensans);
const char *text = "blah";
int16_t width = qp_textwidth(font, text);
qp_drawtext(display, (239 - width), (319 - font->line_height), font, text);
```

#### Unload Font :id=quantum-painter-api-close-font

```c
bool qp_close_font(painter_font_handle_t font);
```

The `qp_close_font` function releases resources related to the loading of the supplied font.

#### Measure Text :id=quantum-painter-api-textwidth

```c
int16_t qp_textwidth(painter_font_handle_t font, const char *str);
```

The `qp_textwidth` function allows measurement of how many pixels wide the supplied string would result in, for the given font.

#### Draw Text :id=quantum-painter-api-drawtext

```c
int16_t qp_drawtext(painter_device_t device, uint16_t x, uint16_t y, painter_font_handle_t font, const char *str);
int16_t qp_drawtext_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_font_handle_t font, const char *str, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);
```

The `qp_drawtext` and `qp_drawtext_recolor` functions draw the supplied string to the screen at the given location using the font supplied, with the latter function allowing for monochrome-based fonts to be recolored.

### Advanced Functions :id=quantum-painter-api-advanced

#### Get Geometry :id=quantum-painter-api-get-geometry

```c
void qp_get_geometry(painter_device_t device, uint16_t *width, uint16_t *height, painter_rotation_t *rotation, uint16_t *offset_x, uint16_t *offset_y);
```

The `qp_get_geometry` function allows external code to retrieve the current width, height, rotation, and drawing offsets.

#### Set Viewport Offsets :id=quantum-painter-api-set-viewport

```c
void qp_set_viewport_offsets(painter_device_t device, uint16_t offset_x, uint16_t offset_y);
```

The `qp_set_viewport_offsets` function can be used to offset all subsequent drawing operations. For example, if a display controller is internally 240x320, but the display panel is 240x240 and has a Y offset of 80 pixels, you could invoke `qp_set_viewport_offsets(display, 0, 80);` and the drawing positioning would be corrected.

#### Set Viewport :id=quantum-painter-api-viewport

```c
bool qp_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
```

The `qp_viewport` function controls where raw pixel data is written to.

#### Stream Pixel Data :id=quantum-painter-api-pixdata

```c
bool qp_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count);
```

The `qp_pixdata` function allows raw pixel data to be streamed to the display. It requires a native pixel count rather than the number of bytes to transfer, to ensure display panel data alignment is respected. E.g. for display panels using RGB565 internal format, sending 10 pixels will result in 20 bytes of transfer.

!> Under normal circumstances, users will not need to manually call either `qp_viewport` or `qp_pixdata`. These allow for writing of raw pixel information, in the display panel's native format, to the area defined by the viewport.

## Quantum Painter Display Drivers :id=quantum-painter-drivers

### Common: Standard TFT (SPI + D/C + RST)

Most TFT display panels use a 5-pin interface -- SPI SCK, SPI MOSI, SPI CS, D/C, and RST pins.

For these displays, QMK's `spi_master` must already be correctly configured for the platform you're building for.

The pin assignments for SPI CS, D/C, and RST are specified during device construction.

### GC9A01 :id=qp-driver-gc9a01

Enabling support for the GC9A01 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS = gc9a01_spi
```

Creating a GC9A01 device in firmware can then be done with the following API:

```c
painter_device_t qp_gc9a01_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
```

The device handle returned from the `qp_gc9a01_make_spi_device` function can be used to perform all other drawing operations.

The maximum number of displays can be configured by changing the following in your `config.h` (default is 1):

```c
// 3 displays:
#define GC9A01_NUM_DEVICES 3
```

### ILI9163 :id=qp-driver-ili9163

Enabling support for the ILI9163 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS = ili9163_spi
```

Creating a ILI9163 device in firmware can then be done with the following API:

```c
painter_device_t qp_ili9163_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
```

The device handle returned from the `qp_ili9163_make_spi_device` function can be used to perform all other drawing operations.

The maximum number of displays can be configured by changing the following in your `config.h` (default is 1):

```c
// 3 displays:
#define ILI9163_NUM_DEVICES 3
```

### ILI9341 :id=qp-driver-ili9341

Enabling support for the ILI9341 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS = ili9341_spi
```

Creating a ILI9341 device in firmware can then be done with the following API:

```c
painter_device_t qp_ili9341_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
```

The device handle returned from the `qp_ili9341_make_spi_device` function can be used to perform all other drawing operations.

The maximum number of displays can be configured by changing the following in your `config.h` (default is 1):

```c
// 3 displays:
#define ILI9341_NUM_DEVICES 3
```

### SSD1351 :id=qp-driver-ssd1351

Enabling support for the SSD1351 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS = ssd1351_spi
```

Creating a SSD1351 device in firmware can then be done with the following API:

```c
painter_device_t qp_ssd1351_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
```

The device handle returned from the `qp_ssd1351_make_spi_device` function can be used to perform all other drawing operations.

The maximum number of displays can be configured by changing the following in your `config.h` (default is 1):

```c
// 3 displays:
#define SSD1351_NUM_DEVICES 3
```

### ST7789 :id=qp-driver-st7789

Enabling support for the ST7789 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS = st7789_spi
```

Creating a ST7789 device in firmware can then be done with the following API:

```c
painter_device_t qp_st7789_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
```

The device handle returned from the `qp_st7789_make_spi_device` function can be used to perform all other drawing operations.

The maximum number of displays can be configured by changing the following in your `config.h` (default is 1):

```c
// 3 displays:
#define ST7789_NUM_DEVICES 3
```

!> Some ST7789 devices are known to have different drawing offsets -- despite being a 240x320 pixel display controller internally, some display panels are only 240x240, or smaller. These may require an offset to be applied; see `qp_set_viewport_offsets` above for information on how to override the offsets if they aren't correctly rendered.