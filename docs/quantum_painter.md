# Quantum Painter {#quantum-painter}

Quantum Painter is the standardised API for graphical displays. It currently includes support for basic drawing primitives, as well as custom images, animations, and fonts.

Due to the complexity, there is no support for Quantum Painter on AVR-based boards.

To enable overall Quantum Painter to be built into your firmware, add the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += ......
```

You will also likely need to select an appropriate driver in `rules.mk`, which is listed below.

::: warning
Quantum Painter is not currently integrated with system-level operations such as when the keyboard goes into suspend. Users will need to handle this manually at the current time.
:::

The QMK CLI can be used to convert from normal images such as PNG files or animated GIFs, as well as fonts from TTF files.

Supported devices:

| Display Panel  | Panel Type         | Size             | Comms Transport | Driver                                   |
|----------------|--------------------|------------------|-----------------|------------------------------------------|
| GC9A01         | RGB LCD (circular) | 240x240          | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS += gc9a01_spi`  |
| ILI9163        | RGB LCD            | 128x128          | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS += ili9163_spi` |
| ILI9341        | RGB LCD            | 240x320          | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS += ili9341_spi` |
| ILI9486        | RGB LCD            | 320x480          | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS += ili9486_spi` |
| ILI9488        | RGB LCD            | 320x480          | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS += ili9488_spi` |
| SSD1351        | RGB OLED           | 128x128          | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS += ssd1351_spi` |
| ST7735         | RGB LCD            | 132x162, 80x160  | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS += st7735_spi`  |
| ST7789         | RGB LCD            | 240x320, 240x240 | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS += st7789_spi`  |
| SH1106 (SPI)   | Monochrome OLED    | 128x64           | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS += sh1106_spi`  |
| SH1106 (I2C)   | Monochrome OLED    | 128x64           | I2C             | `QUANTUM_PAINTER_DRIVERS += sh1106_i2c`  |
| SSD1306 (SPI)  | Monochrome OLED    | 128x64           | SPI + D/C + RST | `QUANTUM_PAINTER_DRIVERS += sh1106_spi`  |
| SSD1306 (I2C)  | Monochrome OLED    | 128x32           | I2C             | `QUANTUM_PAINTER_DRIVERS += sh1106_i2c`  |
| Surface        | Virtual            | User-defined     | None            | `QUANTUM_PAINTER_DRIVERS += surface`     |

## Quantum Painter Configuration {#quantum-painter-config}

| Option                                            | Default | Purpose                                                                                                                                                                                      |
|---------------------------------------------------|---------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `QUANTUM_PAINTER_DISPLAY_TIMEOUT`                 | `30000` | This controls the amount of time (in milliseconds) that all displays will remain on after the last user input. If set to `0`, the display will remain on indefinitely.                       |
| `QUANTUM_PAINTER_TASK_THROTTLE`                   | `1`     | This controls the amount of time (in milliseconds) that the Quantum Painter internal task will wait between each execution. Affects animations, display timeout, and LVGL timing if enabled. |
| `QUANTUM_PAINTER_NUM_IMAGES`                      | `8`     | The maximum number of images/animations that can be loaded at any one time.                                                                                                                  |
| `QUANTUM_PAINTER_NUM_FONTS`                       | `4`     | The maximum number of fonts that can be loaded at any one time.                                                                                                                              |
| `QUANTUM_PAINTER_CONCURRENT_ANIMATIONS`           | `4`     | The maximum number of animations that can be executed at the same time.                                                                                                                      |
| `QUANTUM_PAINTER_LOAD_FONTS_TO_RAM`               | `FALSE` | Whether or not fonts should be loaded to RAM. Relevant for fonts stored in off-chip persistent storage, such as external flash.                                                              |
| `QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE`             | `1024`  | The limit of the amount of pixel data that can be transmitted in one transaction to the display. Higher values require more RAM on the MCU.                                                  |
| `QUANTUM_PAINTER_SUPPORTS_256_PALETTE`            | `FALSE` | If 256-color palettes are supported. Requires significantly more RAM on the MCU.                                                                                                             |
| `QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS`          | `FALSE` | If native color range is supported. Requires significantly more RAM on the MCU.                                                                                                              |
| `QUANTUM_PAINTER_DEBUG`                           | _unset_ | Prints out significant amounts of debugging information to CONSOLE output. Significant performance degradation, use only for debugging.                                                      |
| `QUANTUM_PAINTER_DEBUG_ENABLE_FLUSH_TASK_OUTPUT`  | _unset_ | By default, debug output is disabled while the internal task is flushing the display(s). If you want to keep it enabled, add this to your `config.h`. Note: Console will get clogged.        |


Drivers have their own set of configurable options, and are described in their respective sections.

## Quantum Painter CLI Commands {#quantum-painter-cli}

:::::tabs

==== `qmk painter-convert-graphics`

This command converts images to a format usable by QMK, i.e. the QGF File Format.

**Usage**:

```
usage: qmk painter-convert-graphics [-h] [-w] [-d] [-r] -f FORMAT [-o OUTPUT] -i INPUT [-v]

options:
  -h, --help            show this help message and exit
  -w, --raw             Writes out the QGF file as raw data instead of c/h combo.
  -d, --no-deltas       Disables the use of delta frames when encoding animations.
  -r, --no-rle          Disables the use of RLE when encoding images.
  -f FORMAT, --format FORMAT
                        Output format, valid types: rgb888, rgb565, pal256, pal16, pal4, pal2, mono256, mono16, mono4, mono2
  -o OUTPUT, --output OUTPUT
                        Specify output directory. Defaults to same directory as input.
  -i INPUT, --input INPUT
                        Specify input graphic file.
  -v, --verbose         Turns on verbose output.
```

The `INPUT` argument can be any image file loadable by Python's Pillow module. Common formats include PNG, or Animated GIF.

The `OUTPUT` argument needs to be a directory, and will default to the same directory as the input argument.

The `FORMAT` argument can be any of the following:

| Format    | Meaning                                                                                   |
|-----------|-------------------------------------------------------------------------------------------|
| `rgb888`  | 16,777,216 colors in 8-8-8 RGB format (requires `QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS`) |
| `rgb565`  | 65,536 colors in 5-6-5 RGB format (requires `QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS`)     |
| `pal256`  | 256-color palette (requires `QUANTUM_PAINTER_SUPPORTS_256_PALETTE`)                       |
| `pal16`   | 16-color palette                                                                          |
| `pal4`    | 4-color palette                                                                           |
| `pal2`    | 2-color palette                                                                           |
| `mono256` | 256-shade grayscale (requires `QUANTUM_PAINTER_SUPPORTS_256_PALETTE`)                     |
| `mono16`  | 16-shade grayscale                                                                        |
| `mono4`   | 4-shade grayscale                                                                         |
| `mono2`   | 2-shade grayscale                                                                         |

**Examples**:

```
$ cd /home/qmk/qmk_firmware/keyboards/my_keeb
$ qmk painter-convert-graphics -f mono16 -i my_image.gif -o ./generated/
Writing /home/qmk/qmk_firmware/keyboards/my_keeb/generated/my_image.qgf.h...
Writing /home/qmk/qmk_firmware/keyboards/my_keeb/generated/my_image.qgf.c...
```

==== `qmk painter-make-font-image`

This command converts a TTF font to an intermediate format for editing, before converting to the QFF File Format.

**Usage**:

```
usage: qmk painter-make-font-image [-h] [-a] [-u UNICODE_GLYPHS] [-n] [-s SIZE] -o OUTPUT -f FONT

optional arguments:
  -h, --help            show this help message and exit
  -a, --no-aa           Disable anti-aliasing on fonts.
  -u UNICODE_GLYPHS, --unicode-glyphs UNICODE_GLYPHS
                        Also generate the specified unicode glyphs.
  -n, --no-ascii        Disables output of the full ASCII character set (0x20..0x7E), exporting only the glyphs specified.
  -s SIZE, --size SIZE  Specify font size. Default 12.
  -o OUTPUT, --output OUTPUT
                        Specify output image path.
  -f FONT, --font FONT  Specify input font file.
```

The `FONT` argument is generally a TrueType Font file (TTF).

The `OUTPUT` argument is the output image to generate, generally something like `my_font.png`.

The `UNICODE_GLYPHS` argument allows for specifying extra unicode glyphs to generate, and accepts a string.

**Examples**:

```
$ qmk painter-make-font-image --font NotoSans-ExtraCondensedBold.ttf --size 11 -o noto11.png --unicode-glyphs "ĄȽɂɻɣɈʣ"
```

==== `qmk painter-convert-font-image`

This command converts an intermediate font image to the QFF File Format.

This command expects an image that conforms to the following format:

* Top-left pixel (at `0,0`) is the "delimiter" color:
    * Each glyph in the font starts when a pixel of this color is found on the first row
    * The first row is discarded when converting to the QFF format
* The number of delimited glyphs must match the supplied arguments to the command:
    * The full ASCII set `0x20..0x7E` (if `--no-ascii` was not specified)
    * The corresponding number of unicode glyphs if any were specified with `--unicode-glyphs`
* The order of the glyphs matches the ASCII set, if any, followed by the Unicode glyph set, if any.

**Usage**:

```
usage: qmk painter-convert-font-image [-h] [-w] [-r] -f FORMAT [-u UNICODE_GLYPHS] [-n] [-o OUTPUT] [-i INPUT]

options:
  -h, --help            show this help message and exit
  -w, --raw             Writes out the QFF file as raw data instead of c/h combo.
  -r, --no-rle          Disable the use of RLE to minimise converted image size.
  -f FORMAT, --format FORMAT
                        Output format, valid types: rgb565, pal256, pal16, pal4, pal2, mono256, mono16, mono4, mono2
  -u UNICODE_GLYPHS, --unicode-glyphs UNICODE_GLYPHS
                        Also generate the specified unicode glyphs.
  -n, --no-ascii        Disables output of the full ASCII character set (0x20..0x7E), exporting only the glyphs specified.
  -o OUTPUT, --output OUTPUT
                        Specify output directory. Defaults to same directory as input.
  -i INPUT, --input INPUT
                        Specify input graphic file.
```

The same arguments for `--no-ascii` and `--unicode-glyphs` need to be specified, as per `qmk painter-make-font-image`.

**Examples**:

```
$ cd /home/qmk/qmk_firmware/keyboards/my_keeb
$ qmk painter-convert-font-image --input noto11.png -f mono4 --unicode-glyphs "ĄȽɂɻɣɈʣ"
Writing /home/qmk/qmk_firmware/keyboards/my_keeb/generated/noto11.qff.h...
Writing /home/qmk/qmk_firmware/keyboards/my_keeb/generated/noto11.qff.c...
```

:::::

## Quantum Painter Display Drivers {#quantum-painter-drivers}

::::::tabs

===== LCD

Most TFT display panels use a 5-pin interface -- SPI SCK, SPI MOSI, SPI CS, D/C, and RST pins.

For these displays, QMK's `spi_master` must already be correctly configured for the platform you're building for.

The pin assignments for SPI CS, D/C, and RST are specified during device construction.

:::::tabs

==== GC9A01

Enabling support for the GC9A01 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += gc9a01_spi
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

Native color format rgb565 is compatible with GC9A01

==== ILI9163

Enabling support for the ILI9163 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += ili9163_spi
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

Native color format rgb565 is compatible with ILI9163

==== ILI9341

Enabling support for the ILI9341 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += ili9341_spi
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

Native color format rgb565 is compatible with ILI9341

==== ILI9486

Enabling support for the ILI9486 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += ili9486_spi
```

Creating a ILI9486 device in firmware can then be done with the following API:

```c
painter_device_t qp_ili9486_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
```

There's another variant for this [Waveshare module](https://www.waveshare.com/wiki/3.5inch_TFT_Touch_Shield), because it has a quirky SPI->Parallel converter. You can create it with:

```c
painter_device_t qp_ili9486_make_spi_waveshare_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
```

The device handle returned from these functions can be used to perform all other drawing operations.

The maximum number of displays can be configured by changing the following in your `config.h` (default is 1):

```c
// 3 displays:
#define ILI9486_NUM_DEVICES 3
```

Native color format rgb888 is compatible with ILI9486
Native color format rgb565 is compatible with ILI9486 Waveshare

==== ILI9488

Enabling support for the ILI9488 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += ili9488_spi
```

Creating a ILI9488 device in firmware can then be done with the following API:

```c
painter_device_t qp_ili9488_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
```

The device handle returned from the `qp_ili9488_make_spi_device` function can be used to perform all other drawing operations.

The maximum number of displays can be configured by changing the following in your `config.h` (default is 1):

```c
// 3 displays:
#define ILI9488_NUM_DEVICES 3
```

Native color format rgb888 is compatible with ILI9488

==== ST7735

Enabling support for the ST7735 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += st7735_spi
```

Creating a ST7735 device in firmware can then be done with the following API:

```c
painter_device_t qp_st7735_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
```

The device handle returned from the `qp_st7735_make_spi_device` function can be used to perform all other drawing operations.

The maximum number of displays can be configured by changing the following in your `config.h` (default is 1):

```c
// 3 displays:
#define ST7735_NUM_DEVICES 3
```

Native color format rgb565 is compatible with ST7735

::: warning
Some ST7735 devices are known to have different drawing offsets -- despite being a 132x162 pixel display controller internally, some display panels are only 80x160, or smaller. These may require an offset to be applied; see `qp_set_viewport_offsets` above for information on how to override the offsets if they aren't correctly rendered.
:::

==== ST7789

Enabling support for the ST7789 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += st7789_spi
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

Native color format rgb565 is compatible with ST7789

::: warning
Some ST7789 devices are known to have different drawing offsets -- despite being a 240x320 pixel display controller internally, some display panels are only 240x240, or smaller. These may require an offset to be applied; see `qp_set_viewport_offsets` above for information on how to override the offsets if they aren't correctly rendered.
:::

:::::

===== OLED

OLED displays tend to use 5-pin SPI when at larger resolutions, or when using color -- SPI SCK, SPI MOSI, SPI CS, D/C, and RST pins. Smaller OLEDs may use I2C instead.

When using these displays, either `spi_master` or `i2c_master` must already be correctly configured for both the platform and panel you're building for.

For SPI, the pin assignments for SPI CS, D/C, and RST are specified during device construction -- for I2C the panel's address is specified instead.

:::::tabs

==== SSD1351

Enabling support for the SSD1351 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += ssd1351_spi
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

Native color format rgb565 is compatible with SSD1351

==== SH1106

Enabling support for the SH1106 in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
# For SPI:
QUANTUM_PAINTER_DRIVERS += sh1106_spi
# For I2C:
QUANTUM_PAINTER_DRIVERS += sh1106_i2c
```

Creating a SH1106 device in firmware can then be done with the following APIs:

```c
// SPI-based SH1106:
painter_device_t qp_sh1106_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
// I2C-based SH1106:
painter_device_t qp_sh1106_make_i2c_device(uint16_t panel_width, uint16_t panel_height, uint8_t i2c_address);
```

The device handle returned from the `qp_sh1106_make_???_device` function can be used to perform all other drawing operations.

The maximum number of displays of each type can be configured by changing the following in your `config.h` (default is 1):

```c
// 3 SPI displays:
#define SH1106_NUM_SPI_DEVICES 3
// 3 I2C displays:
#define SH1106_NUM_I2C_DEVICES 3
```

Native color format mono2 is compatible with SH1106

==== SSD1306

SSD1306 and SH1106 are almost entirely identical, to the point of being indisinguishable by Quantum Painter. Enable SH1106 support in Quantum Painter and create SH1106 devices in firmware to perform drawing operations on SSD1306 displays.

:::::

===== Surface

Quantum Painter has a surface driver which is able to target a buffer in RAM. In general, surfaces keep track of the "dirty" region -- the area that has been drawn to since the last flush -- so that when transferring to the display they can transfer the minimal amount of data to achieve the end result.

::: warning
These generally require significant amounts of RAM, so at large sizes and/or higher bit depths, they may not be usable on all MCUs.
:::

Enabling support for surfaces in Quantum Painter is done by adding the following to `rules.mk`:

```make
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += surface
```

Creating a surface in firmware can then be done with the following APIs:

```c
// 16bpp RGB565 surface:
painter_device_t qp_make_rgb565_surface(uint16_t panel_width, uint16_t panel_height, void *buffer);
// 1bpp monochrome surface:
painter_device_t qp_make_mono1bpp_surface(uint16_t panel_width, uint16_t panel_height, void *buffer);
```

The `buffer` is a user-supplied area of memory, which can be statically allocated using `SURFACE_REQUIRED_BUFFER_BYTE_SIZE`:

```c
// Buffer required for a 240x80 16bpp surface:
uint8_t framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(240, 80, 16)];
```

The device handle returned from the `qp_make_?????_surface` function can be used to perform all other drawing operations.

Example:

```c
static painter_device_t my_surface;
static uint8_t my_framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(240, 80, 16)]; // Allocate a buffer for a 16bpp 240x80 RGB565 display
void keyboard_post_init_kb(void) {
    my_surface = qp_rgb565_make_surface(240, 80, my_framebuffer);
    qp_init(my_surface, QP_ROTATION_0);
    keyboard_post_init_user();
}
```

The maximum number of surfaces can be configured by changing the following in your `config.h` (default is 1):

```c
// 3 surfaces:
#define SURFACE_NUM_DEVICES 3
```

To transfer the contents of the surface to another display of the same pixel format, the following API can be invoked:

```c
bool qp_surface_draw(painter_device_t surface, painter_device_t display, uint16_t x, uint16_t y, bool entire_surface);
```

The `surface` is the surface to copy out from. The `display` is the target display to draw into. `x` and `y` are the target location to draw the surface pixel data. Under normal circumstances, the location should be consistent, as the dirty region is calculated with respect to the `x` and `y` coordinates -- changing those will result in partial, overlapping draws. `entire_surface` whether the entire surface should be drawn, instead of just the dirty region.

::: warning
The surface and display panel must have the same native pixel format.
:::

::: tip
Calling `qp_flush()` on the surface resets its dirty region. Copying the surface contents to the display also automatically resets the dirty region.
:::

::::::

## Quantum Painter Drawing API {#quantum-painter-api}

All APIs require a `painter_device_t` object as their first parameter -- this object comes from the specific device initialisation, and instructions on creating it can be found in each driver's respective section.

To use any of the APIs, you need to include `qp.h`:
```c
#include <qp.h>
```

::::::tabs

===== General Notes

The coordinate system used in Quantum Painter generally accepts `left`, `top`, `right`, and `bottom` instead of x/y/width/height, and each coordinate is inclusive of where pixels should be drawn. This is required as some datatypes used by display panels have a maximum value of `255` -- for any value or geometry extent that matches `256`, this would be represented as a `0`, instead.

::: tip
Drawing a horizontal line 8 pixels long, starting from 4 pixels inside the left side of the display, will need `left=4`, `right=11`.
:::

All color data matches the standard QMK HSV triplet definitions:

* Hue is of the range `0...255` and is internally mapped to 0...360 degrees.
* Saturation is of the range `0...255` and is internally mapped to 0...100% saturation.
* Value is of the range `0...255` and is internally mapped to 0...100% brightness.

::: tip
Colors used in Quantum Painter are not subject to the RGB lighting CIE curve, if it is enabled.
:::

===== Device Control

:::::tabs

==== Display Initialisation

```c
bool qp_init(painter_device_t device, painter_rotation_t rotation);
```

The `qp_init` function is used to initialise a display device after it has been created. This accepts a rotation parameter (`QP_ROTATION_0`, `QP_ROTATION_90`, `QP_ROTATION_180`, `QP_ROTATION_270`), which makes sure that the orientation of what's drawn on the display is correct.

```c
static painter_device_t display;
void keyboard_post_init_kb(void) {
    display = qp_make_.......;         // Create the display
    qp_init(display, QP_ROTATION_0);   // Initialise the display
}
```

==== Display Power

```c
bool qp_power(painter_device_t device, bool power_on);
```

The `qp_power` function instructs the display whether or not the display panel should be on or off.

::: warning
If there is a separate backlight controlled through the normal QMK backlight API, this is not controlled by the `qp_power` function and needs to be manually handled elsewhere.
:::

```c
static uint8_t last_backlight = 255;
void suspend_power_down_user(void) {
    if (last_backlight == 255) {
        last_backlight = get_backlight_level();
    }
    backlight_set(0);
    rgb_matrix_set_suspend_state(true);
    qp_power(display, false);
}

void suspend_wakeup_init_user(void) {
    qp_power(display, true);
    rgb_matrix_set_suspend_state(false);
    if (last_backlight != 255) {
        backlight_set(last_backlight);
    }
    last_backlight = 255;
}
```

==== Display Clear

```c
bool qp_clear(painter_device_t device);
```

The `qp_clear` function clears the display's screen.

==== Display Flush

```c
bool qp_flush(painter_device_t device);
```

The `qp_flush` function ensures that all drawing operations are "pushed" to the display. This should be done as the last operation whenever a sequence of draws occur, and guarantees that any changes are applied.

::: warning
Some display panels may seem to work even without a call to `qp_flush` -- this may be because the driver cannot queue drawing operations and needs to display them immediately when invoked. In general, calling `qp_flush` at the end is still considered "best practice".
:::

```c
void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        // Draw a rect based off the current RGB color
        qp_rect(display, 0, 7, 0, 239, rgb_matrix_get_hue(), 255, 255);
        qp_flush(display);
    }
}
```

:::::

===== Drawing Primitives

:::::tabs

==== Set Pixel

```c
bool qp_setpixel(painter_device_t device, uint16_t x, uint16_t y, uint8_t hue, uint8_t sat, uint8_t val);
```

The `qp_setpixel` can be used to set a specific pixel on the screen to the supplied color.

::: tip
Using `qp_setpixel` for large amounts of drawing operations is inefficient and should be avoided unless they cannot be achieved with other drawing APIs.
:::

```c
void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        // Draw a 240px high vertical rainbow line on X=0:
        for (int i = 0; i < 239; ++i) {
            qp_setpixel(display, 0, i, i, 255, 255);
        }
        qp_flush(display);
    }
}
```

==== Draw Line

```c
bool qp_line(painter_device_t device, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t hue, uint8_t sat, uint8_t val);
```

The `qp_line` can be used to draw lines on the screen with the supplied color.

```c
void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        // Draw 8px-wide rainbow down the left side of the display
        for (int i = 0; i < 239; ++i) {
            qp_line(display, 0, i, 7, i, i, 255, 255);
        }
        qp_flush(display);
    }
}
```

==== Draw Rect

```c
bool qp_rect(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint8_t hue, uint8_t sat, uint8_t val, bool filled);
```

The `qp_rect` can be used to draw rectangles on the screen with the supplied color, with or without a background fill. If not filled, any pixels inside the rectangle will be left as-is.

```c
void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        // Draw 8px-wide rainbow filled rectangles down the left side of the display
        for (int i = 0; i < 239; i+=8) {
            qp_rect(display, 0, i, 7, i+7, i, 255, 255, true);
        }
        qp_flush(display);
    }
}
```

==== Draw Circle

```c
bool qp_circle(painter_device_t device, uint16_t x, uint16_t y, uint16_t radius, uint8_t hue, uint8_t sat, uint8_t val, bool filled);
```

The `qp_circle` can be used to draw circles on the screen with the supplied color, with or without a background fill. If not filled, any pixels inside the circle will be left as-is.

```c
void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        // Draw r=4 filled circles down the left side of the display
        for (int i = 0; i < 239; i+=8) {
            qp_circle(display, 4, 4+i, 4, i, 255, 255, true);
        }
        qp_flush(display);
    }
}
```

==== Draw Ellipse

```c
bool qp_ellipse(painter_device_t device, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint8_t hue, uint8_t sat, uint8_t val, bool filled);
```

The `qp_ellipse` can be used to draw ellipses on the screen with the supplied color, with or without a background fill. If not filled, any pixels inside the ellipses will be left as-is.

```c
void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        // Draw 16x8 filled ellipses down the left side of the display
        for (int i = 0; i < 239; i+=8) {
            qp_ellipse(display, 8, 4+i, 16, 8, i, 255, 255, true);
        }
        qp_flush(display);
    }
}
```

:::::

===== Image Functions

Making an image available for use requires compiling it into your firmware. To do so, assuming you've created `my_image.qgf.c` and `my_image.qgf.h` as per the CLI examples above, you'd add the following to your `rules.mk`:

```make
SRC += my_image.qgf.c
```

...and in your `keymap.c`, you'd add to the top of the file:
```c
#include "my_image.qgf.h"
```

:::::tabs

==== Load Image

```c
painter_image_handle_t qp_load_image_mem(const void *buffer);
```

The `qp_load_image_mem` function loads a QGF image from memory or flash.

`qp_load_image_mem` returns a handle to the loaded image, which can then be used to draw to the screen using `qp_drawimage`, `qp_drawimage_recolor`, `qp_animate`, or `qp_animate_recolor`. If an image is no longer required, it can be unloaded by calling `qp_close_image` below.

See the [CLI Commands](quantum_painter#quantum-painter-cli) for instructions on how to convert images to [QGF](quantum_painter_qgf).

::: tip
The total number of images available to load at any one time is controlled by the configurable option `QUANTUM_PAINTER_NUM_IMAGES` in the table above. If more images are required, the number should be increased in `config.h`.
:::

Image information is available through accessing the handle:

| Property    | Accessor             |
|-------------|----------------------|
| Width       | `image->width`       |
| Height      | `image->height`      |
| Frame Count | `image->frame_count` |

==== Unload Image

```c
bool qp_close_image(painter_image_handle_t image);
```

The `qp_close_image` function releases resources related to the loading of the supplied image.

==== Draw image

```c
bool qp_drawimage(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image);
bool qp_drawimage_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);
```

The `qp_drawimage` and `qp_drawimage_recolor` functions draw the supplied image to the screen at the supplied location, with the latter function allowing for monochrome-based images to be recolored.

```c
// Draw an image on the bottom-right of the 240x320 display on initialisation
static painter_image_handle_t my_image;
void keyboard_post_init_kb(void) {
    my_image = qp_load_image_mem(gfx_my_image);
    if (my_image != NULL) {
        qp_drawimage(display, (239 - my_image->width), (319 - my_image->height), my_image);
    }
}
```

==== Animate Image

```c
deferred_token qp_animate(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image);
deferred_token qp_animate_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_image_handle_t image, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);
```

The `qp_animate` and `qp_animate_recolor` functions draw the supplied image to the screen at the supplied location, with the latter function allowing for monochrome-based animations to be recolored. They also set up internal timing such that each frame is rendered at the correct time as per the animated image.

Once an image has been set to animate, it will loop indefinitely until stopped, with no user intervention required.

Both functions return a `deferred_token`, which can then be used to stop the animation, using `qp_stop_animation` below.

```c
// Animate an image on the bottom-right of the 240x320 display on initialisation
static painter_image_handle_t my_image;
static deferred_token my_anim;
void keyboard_post_init_kb(void) {
    my_image = qp_load_image_mem(gfx_my_image);
    if (my_image != NULL) {
        my_anim = qp_animate(display, (239 - my_image->width), (319 - my_image->height), my_image);
    }
}
```

==== Stop Animation

```c
void qp_stop_animation(deferred_token anim_token);
```

The `qp_stop_animation` function stops the previously-started animation.
```c
void housekeeping_task_user(void) {
    if (some_random_stop_reason) {
        qp_stop_animation(my_anim);
    }
}
```

:::::

===== Font Functions

Making a font available for use requires compiling it into your firmware. To do so, assuming you've created `my_font.qff.c` and `my_font.qff.h` as per the CLI examples above, you'd add the following to your `rules.mk`:

```make
SRC += noto11.qff.c
```

...and in your `keymap.c`, you'd add to the top of the file:
```c
#include "noto11.qff.h"
```

:::::tabs

==== Load Font

```c
painter_font_handle_t qp_load_font_mem(const void *buffer);
```

The `qp_load_font_mem` function loads a QFF font from memory or flash.

`qp_load_font_mem` returns a handle to the loaded font, which can then be measured using `qp_textwidth`, or drawn to the screen using `qp_drawtext`, or `qp_drawtext_recolor`. If a font is no longer required, it can be unloaded by calling `qp_close_font` below.

See the [CLI Commands](quantum_painter#quantum-painter-cli) for instructions on how to convert TTF fonts to [QFF](quantum_painter_qff).

::: tip
The total number of fonts available to load at any one time is controlled by the configurable option `QUANTUM_PAINTER_NUM_FONTS` in the table above. If more fonts are required, the number should be increased in `config.h`.
:::

Font information is available through accessing the handle:

| Property    | Accessor             |
|-------------|----------------------|
| Line Height | `image->line_height` |

==== Unload Font

```c
bool qp_close_font(painter_font_handle_t font);
```

The `qp_close_font` function releases resources related to the loading of the supplied font.

==== Measure Text

```c
int16_t qp_textwidth(painter_font_handle_t font, const char *str);
```

The `qp_textwidth` function allows measurement of how many pixels wide the supplied string would result in, for the given font.

==== Draw Text

```c
int16_t qp_drawtext(painter_device_t device, uint16_t x, uint16_t y, painter_font_handle_t font, const char *str);
int16_t qp_drawtext_recolor(painter_device_t device, uint16_t x, uint16_t y, painter_font_handle_t font, const char *str, uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);
```

The `qp_drawtext` and `qp_drawtext_recolor` functions draw the supplied string to the screen at the given location using the font supplied, with the latter function allowing for monochrome-based fonts to be recolored.

```c
// Draw a text message on the bottom-right of the 240x320 display on initialisation
static painter_font_handle_t my_font;
void keyboard_post_init_kb(void) {
    my_font = qp_load_font_mem(font_noto11);
    if (my_font != NULL) {
        static const char *text = "Hello from QMK!";
        int16_t width = qp_textwidth(my_font, text);
        qp_drawtext(display, (239 - width), (319 - my_font->line_height), my_font, text);
    }
}
```

:::::

===== Advanced Functions

:::::tabs

==== Getters

These functions allow external code to retrieve the current width, height, rotation, and drawing offsets.

::::tabs

=== Width

```c
uint16_t qp_get_width(painter_device_t device);
```

=== Height

```c
uint16_t qp_get_height(painter_device_t device);
```

=== Rotation

```c
painter_rotation_t qp_get_rotation(painter_device_t device);
```

=== Offset X

```c
uint16_t qp_get_offset_x(painter_device_t device);
```

=== Offset Y

```c
uint16_t qp_get_offset_y(painter_device_t device);
```

=== Everything

Convenience function to call all the previous ones at once.
Note: You can pass `NULL` for the values you are not interested in.

```c
void qp_get_geometry(painter_device_t device, uint16_t *width, uint16_t *height, painter_rotation_t *rotation, uint16_t *offset_x, uint16_t *offset_y);
```

::::

==== Set Viewport Offsets

```c
void qp_set_viewport_offsets(painter_device_t device, uint16_t offset_x, uint16_t offset_y);
```

The `qp_set_viewport_offsets` function can be used to offset all subsequent drawing operations. For example, if a display controller is internally 240x320, but the display panel is 240x240 and has a Y offset of 80 pixels, you could invoke `qp_set_viewport_offsets(display, 0, 80);` and the drawing positioning would be corrected.

==== Set Viewport

```c
bool qp_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
```

The `qp_viewport` function controls where raw pixel data is written to.

==== Stream Pixel Data

```c
bool qp_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count);
```

The `qp_pixdata` function allows raw pixel data to be streamed to the display. It requires a native pixel count rather than the number of bytes to transfer, to ensure display panel data alignment is respected. E.g. for display panels using RGB565 internal format, sending 10 pixels will result in 20 bytes of transfer.

::: warning
Under normal circumstances, users will not need to manually call either `qp_viewport` or `qp_pixdata`. These allow for writing of raw pixel information, in the display panel's native format, to the area defined by the viewport.
:::

:::::

::::::
