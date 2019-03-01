# OLED

## OLED Supported Hardware

128x32 OLED modules using SSD1306 driver IC over I2C. Supported on both AVR and ARM based keyboards. Possible but untested hardware includes other sized OLED modules using SSD1306 over I2C, such as 128x64. 

## Usage

To enable the OLED feature, there are three steps. First, when compiling your keyboard, you'll need to set `OLED_ENABLE=yes` in `rules.mk`, e.g.:

```
BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
STENO_ENABLE = no
EXTRAKEY_ENABLE = yes
OLED_ENABLE = yes
```

This enables the feature and the `OLED_ENABLE` define. Then in your `keymap.c` file, you will need to implement the initialization and task calls, e.g:

```C++
void matrix_init_user(void) {
#ifdef OLED_ENABLE
  oled_init(false);   // turns on the display
#endif
}

void matrix_scan_user(void) {
#ifdef OLED_ENABLE
  oled_task();
#endif
}
```

Then finally implement the user task call and send your data to the OLED to render, e.g:
```C++
#ifdef OLED_ENABLE
void oled_task_user(void) {
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
    oled_write_P(PSTR("Undefined\n"), false);
  }

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}
#endif
```


## Other Examples

In split keyboards, it is very common to have two OLED displays that each render different content. You can do this by switching which content to render by using the return from `is_keyboard_master()` or `is_keyboard_left()` found in `split_util.h`, e.g:

```C++
#ifdef OLED_ENABLE
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

|Define                 |Default        |Description                                     |
|-----------------------|---------------|------------------------------------------------|
|`SSD1306_ADDRESS`      |`0x3C`         |The i2c address of the OLED Display             |
|`OLED_FONT_H`          |`"glcdfont.c"` |The font code file to use for custom fonts      |
|`OLED_FONT_START`      |`0`            |The starting characer index for custom fonts    |
|`OLED_FONT_END`        |`224`          |The ending characer index for custom fonts      |
|`OLED_FONT_WIDTH`      |`6`            |The font width                                  |
|`OLED_FONT_HEIGHT`     |`8`            |The font height (untested)                      |


 ## 128x64 & Custom sized OLED Displays

 The default display size for this feature is 128x32 and all necessary defines are precalculated with that in mind. We have added a define, `OLED_DISPLAY_128X64`, to switch all the values to be used in a 128x64 display, as well as added a custom define, `OLED_DISPLAY_CUSTOM`, that allows you to provide the necessary values to the driver.

|Define                 |Default        |Description                                                      |
|-----------------------|---------------|-----------------------------------------------------------------|
|`OLED_DISPLAY_128X64`  |*Not defined*  |Changes the display defines for use with 128x64 displays.        |
|`OLED_DISPLAY_CUSTOM`  |*Not defined*  |Changes the display defines for use with custom displays.<br />Requires user to implement the below defines. |
|`OLED_DISPLAY_WIDTH`   |`128`          |The width of the OLED display.                                   |
|`OLED_DISPLAY_HEIGHT`  |`32`           |The height of the OLED display.                                  |
|`OLED_MATRIX_SIZE`     |`512`          |The local buffer size to allocate.<br />`(OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)`|
|`OLED_BLOCK_TYPE`      |`uint8_t`      |The unsigned integer type to use for dirty rendering.|
|`OLED_BLOCK_COUNT`     |`8`            |The number of blocks the display is divided into for dirty rendering.<br />`(sizeof(OLED_BLOCK_TYPE) * 8)`|
|`OLED_BLOCK_SIZE`      |`64`           |The size of each block for dirty rendering<br />`(OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)`|


 ## 90 Degree Rotated Rendering

 OLED displays driven by SSD1306 drivers only natively support in hard ware 0 degree and 180 degree rendering. By enabling the `OLED_ROTATE90` define, this handles rotating the display buffer in the software driver 90 degrees so we can effectivly get 90 and 270 degree rendering. This is useful if you have mounted the OLED display vertically long ways. 
 
 **NOTE:** This is done in software and not free. Enabling this will increase the firmware size as well as the time to calculate what data to send over i2c to the OLED. If you are strapped for cycles, this can cause keycodes to not register. In testing however, the rendering time on an `atmega32u4` board only went from 2ms to 5ms and keycodes not registering was only noticed once we hit 15ms.

 
|Define                 |Default        |Description                                     |
|-----------------------|---------------|------------------------------------------------|
|`OLED_ROTATE90`        |*Not defined*  |When defined, rotates the rendered output 90 degrees. **NOTE:** increases firmware size and is slower to render.  |
|`OLED_SOURCE_MAP`      |`{ 0, ... N }` |Precalculated source array to use for mapping source buffer to target oled memory in 90 degree rendering.         |
|`OLED_TARGET_MAP`      |`{ 48, ... N }`|Precalculated target array to use for mapping source buffer to target oled memory in 90 degree rendering.         |

### Technical Mumbo Jumbo 

90 Degree Rotated Rendering is achieved by using bitwise operations to rotate each 8 block of memory and uses two precalculated arrays to remap buffer memory to OLED memory. The memory map defines are precalculated for remap performance and are calculated based on the OLED Height, Width, and Block Size. For example, in the default 128x32 implementation we have a 64 byte block size. This gives us eight 8 byte blocks that need to be rotated and rendered. The OLED renders horizontally two 8 byte blocks before moving down a page, e.g:

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
// Initialize the oled display, rotating the rendered output 180 degrees if true.
// Returns true if the OLED was initialized successfully
bool oled_init(bool flip180);

// Clears the display buffer, resets cursor position to 0, and sets the buffer to dirty for rendering
void oled_clear(void);

// Renders the dirty chunks of the buffer to oled display
void oled_render(void);

// Moves cursor to character position indicated by column and line, wraps if out of bounds
// Max column denoted by 'OLED_MAX_CHARS' define and max lines by 'OLED_MAX_LINES' define
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
```
