# OLED Driver

## OLED Supported Hardware

OLED modules using SSD1306 or SH1106 driver ICs, communicating over I2C.
Tested combinations:

| IC driver |   Size | Keyboard Platform | Notes                    |
|-----------|--------|-------------------|--------------------------|
| SSD1306   | 128x32 | AVR               | Primary support          |
| SSD1306   | 128x64 | AVR               | Verified working         |
| SSD1306   | 128x32 | ARM               |                          |
| SH1106    | 128x64 | AVR               | No rotation or scrolling |

Hardware configurations using ARM-based microcontrollers or different sizes of OLED modules may be compatible, but are untested.

!> Warning: This OLED Driver currently uses the new i2c_master driver from split common code. If your split keyboard uses i2c to communication between sides this driver could cause an address conflict (serial is fine). Please contact your keyboard vendor and ask them to migrate to the latest split common code to fix this. 

## Usage

To enable the OLED feature, there are three steps. First, when compiling your keyboard, you'll need to set `OLED_DRIVER_ENABLE=yes` in `rules.mk`, e.g.:

```
OLED_DRIVER_ENABLE = yes
```

This enables the feature and the `OLED_DRIVER_ENABLE` define. Then in your `keymap.c` file, you will need to implement the user task call, e.g:

```C++
#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer: "), false);
  switch (biton32(layer_state)) {
    case _QWERTY:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case _FN:
      oled_write_P(PSTR("FN\n"), false);
      break;
    case _ADJ:
      oled_write_P(PSTR("ADJ\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}
#endif
```

## Logo Example

In the default font, ranges in the font file are reserved for a QMK Logo. To Render this logo to the oled screen, use the following code example:

```C++
static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}
```

## Other Examples

In split keyboards, it is very common to have two OLED displays that each render different content and oriented flipped differently. You can do this by switching which content to render by using the return from `is_keyboard_master()` or `is_keyboard_left()` found in `split_util.h`, e.g:

```C++
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status();     // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    render_logo();       // Renders a statuc logo
    oled_scroll_left();  // Turns on scrolling
  }
}
#endif
```


 ## Basic Configuration

| Define                 | Default           | Description                                                                                                                |
|------------------------|-------------------|----------------------------------------------------------------------------------------------------------------------------|
| `OLED_DISPLAY_ADDRESS` | `0x3C`            | The i2c address of the OLED Display                                                                                        |
| `OLED_FONT_H`          | `"glcdfont.c"`    | The font code file to use for custom fonts                                                                                 |
| `OLED_FONT_START`      | `0`               | The starting characer index for custom fonts                                                                               |
| `OLED_FONT_END`        | `224`             | The ending characer index for custom fonts                                                                                 |
| `OLED_FONT_WIDTH`      | `6`               | The font width                                                                                                             |
| `OLED_FONT_HEIGHT`     | `8`               | The font height (untested)                                                                                                 |
| `OLED_DISABLE_TIMEOUT` | *Not defined*     | Disables the built in OLED timeout feature. Useful when implementing custom timeout rules.                                 |
| `OLED_IC`              | `OLED_IC_SSD1306` | Set to `OLED_IC_SH1106` if you're using the SH1106 OLED controller.                                                        |
| `OLED_COLUMN_OFFSET`   | `0`               | (SH1106 only.) Shift output to the right this many pixels.<br />Useful for 128x64 displays centered on a 132x64 SH1106 IC. |

 ## 128x64 & Custom sized OLED Displays

 The default display size for this feature is 128x32 and all necessary defines are precalculated with that in mind. We have added a define, `OLED_DISPLAY_128X64`, to switch all the values to be used in a 128x64 display, as well as added a custom define, `OLED_DISPLAY_CUSTOM`, that allows you to provide the necessary values to the driver.

|Define                 |Default        |Description                                                      |
|-----------------------|---------------|-----------------------------------------------------------------|
|`OLED_DISPLAY_128X64`  |*Not defined*  |Changes the display defines for use with 128x64 displays.        |
|`OLED_DISPLAY_CUSTOM`  |*Not defined*  |Changes the display defines for use with custom displays.<br />Requires user to implement the below defines. |
|`OLED_DISPLAY_WIDTH`   |`128`          |The width of the OLED display.                                   |
|`OLED_DISPLAY_HEIGHT`  |`32`           |The height of the OLED display.                                  |
|`OLED_MATRIX_SIZE`     |`512`          |The local buffer size to allocate.<br />`(OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)`. |
|`OLED_BLOCK_TYPE`      |`uint16_t`     |The unsigned integer type to use for dirty rendering. |
|`OLED_BLOCK_COUNT`     |`16`           |The number of blocks the display is divided into for dirty rendering.<br />`(sizeof(OLED_BLOCK_TYPE) * 8)`. |
|`OLED_BLOCK_SIZE`      |`32`           |The size of each block for dirty rendering<br />`(OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)`. |
|`OLED_COM_PINS`        |`COM_PINS_SEQ` |How the SSD1306 chip maps it's memory to display.<br />Options are `COM_PINS_SEQ`, `COM_PINS_ALT`, `COM_PINS_SEQ_LR`, & `COM_PINS_ALT_LR`. |
|`OLED_SOURCE_MAP`      |`{ 0, ... N }` |Precalculated source array to use for mapping source buffer to target OLED memory in 90 degree rendering.         |
|`OLED_TARGET_MAP`      |`{ 24, ... N }`|Precalculated target array to use for mapping source buffer to target OLED memory in 90 degree rendering.         |


### 90 Degree Rotation - Technical Mumbo Jumbo 

!> Rotation is unsupported on the SH1106.

```C
// OLED Rotation enum values are flags
typedef enum {
    OLED_ROTATION_0   = 0,
    OLED_ROTATION_90  = 1,
    OLED_ROTATION_180 = 2,
    OLED_ROTATION_270 = 3, // OLED_ROTATION_90 | OLED_ROTATION_180
} oled_rotation_t;
```

 OLED displays driven by SSD1306 drivers only natively support in hard ware 0 degree and 180 degree rendering. This feature is done in software and not free. Using this feature will increase the time to calculate what data to send over i2c to the OLED. If you are strapped for cycles, this can cause keycodes to not register. In testing however, the rendering time on an `atmega32u4` board only went from 2ms to 5ms and keycodes not registering was only noticed once we hit 15ms. 
 
 90 Degree Rotated Rendering is achieved by using bitwise operations to rotate each 8 block of memory and uses two precalculated arrays to remap buffer memory to OLED memory. The memory map defines are precalculated for remap performance and are calculated based on the OLED Height, Width, and Block Size. For example, in the 128x32 implementation with a `uint8_t` block type, we have a 64 byte block size. This gives us eight 8 byte blocks that need to be rotated and rendered. The OLED renders horizontally two 8 byte blocks before moving down a page, e.g:

|   |   |   |   |   |   |
|---|---|---|---|---|---|
| 0 | 1 |   |   |   |   |
| 2 | 3 |   |   |   |   |
| 4 | 5 |   |   |   |   |
| 6 | 7 |   |   |   |   |

However the local buffer is stored as if it was Height x Width display instead of Width x Height, e.g:

|   |   |   |   |   |   |
|---|---|---|---|---|---|
| 3 | 7 |   |   |   |   |
| 2 | 6 |   |   |   |   |
| 1 | 5 |   |   |   |   |
| 0 | 4 |   |   |   |   |

So those precalculated arrays just index the memory offsets in the order in which each one iterates its data.

## OLED API

```C++
// OLED Rotation enum values are flags
typedef enum {
    OLED_ROTATION_0   = 0,
    OLED_ROTATION_90  = 1,
    OLED_ROTATION_180 = 2,
    OLED_ROTATION_270 = 3, // OLED_ROTATION_90 | OLED_ROTATION_180
} oled_rotation_t;

// Initialize the OLED display, rotating the rendered output based on the define passed in.
// Returns true if the OLED was initialized successfully
bool oled_init(oled_rotation_t rotation);

// Called at the start of oled_init, weak function overridable by the user
// rotation - the value passed into oled_init
// Return new oled_rotation_t if you want to override default rotation
oled_rotation_t oled_init_user(oled_rotation_t rotation);

// Clears the display buffer, resets cursor position to 0, and sets the buffer to dirty for rendering
void oled_clear(void);

// Renders the dirty chunks of the buffer to OLED display
void oled_render(void);

// Moves cursor to character position indicated by column and line, wraps if out of bounds
// Max column denoted by 'oled_max_chars()' and max lines by 'oled_max_lines()' functions
void oled_set_cursor(uint8_t col, uint8_t line);

// Advances the cursor to the next page, writing ' ' if true
// Wraps to the begining when out of bounds
void oled_advance_page(bool clearPageRemainder);

// Moves the cursor forward 1 character length
// Advance page if there is not enough room for the next character
// Wraps to the begining when out of bounds
void oled_advance_char(void);

// Writes a single character to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Main handler that writes character data to the display buffer
void oled_write_char(const char data, bool invert);

// Writes a string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
void oled_write(const char *data, bool invert);

// Writes a string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Advances the cursor to the next page, wiring ' ' to the remainder of the current page
void oled_write_ln(const char *data, bool invert);

// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Remapped to call 'void oled_write(const char *data, bool invert);' on ARM
void oled_write_P(const char *data, bool invert);

// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Advances the cursor to the next page, wiring ' ' to the remainder of the current page
// Remapped to call 'void oled_write_ln(const char *data, bool invert);' on ARM
void oled_write_ln_P(const char *data, bool invert);

// Can be used to manually turn on the screen if it is off
// Returns true if the screen was on or turns on
bool oled_on(void);

// Can be used to manually turn off the screen if it is on
// Returns true if the screen was off or turns off
bool oled_off(void);

// Basically it's oled_render, but with timeout management and oled_task_user calling!
void oled_task(void);

// Called at the start of oled_task, weak function overridable by the user
void oled_task_user(void);

// Scrolls the entire display right
// Returns true if the screen was scrolling or starts scrolling
// NOTE: display contents cannot be changed while scrolling
bool oled_scroll_right(void);

// Scrolls the entire display left
// Returns true if the screen was scrolling or starts scrolling
// NOTE: display contents cannot be changed while scrolling
bool oled_scroll_left(void);

// Turns off display scrolling
// Returns true if the screen was not scrolling or stops scrolling
bool oled_scroll_off(void);

// Returns the maximum number of characters that will fit on a line
uint8_t oled_max_chars(void);

// Returns the maximum number of lines that will fit on the OLED
uint8_t oled_max_lines(void);
```

!> Scrolling and rotation are unsupported on the SH1106.

## SSD1306.h driver conversion guide

|Old API                    |Recommended New API                |
|---------------------------|-----------------------------------|
|`struct CharacterMatrix`   |*removed - delete all references*  |
|`iota_gfx_init`            |`oled_init`                        |
|`iota_gfx_on`              |`oled_on`                          |
|`iota_gfx_off`             |`oled_off`                         |
|`iota_gfx_flush`           |`oled_render`                      |
|`iota_gfx_write_char`      |`oled_write_char`                  |
|`iota_gfx_write`           |`oled_write`                       |
|`iota_gfx_write_P`         |`oled_write_P`                     |
|`iota_gfx_clear_screen`    |`oled_clear`                       |
|`matrix_clear`             |*removed - delete all references*  |
|`matrix_write_char_inner`  |`oled_write_char`                  |
|`matrix_write_char`        |`oled_write_char`                  |
|`matrix_write`             |`oled_write`                       |
|`matrix_write_ln`          |`oled_write_ln`                    |
|`matrix_write_P`           |`oled_write_P`                     |
|`matrix_write_ln_P`        |`oled_write_ln_P`                  |
|`matrix_render`            |`oled_render`                      |
|`iota_gfx_task`            |`oled_task`                        |
|`iota_gfx_task_user`       |`oled_task_user`                   |
