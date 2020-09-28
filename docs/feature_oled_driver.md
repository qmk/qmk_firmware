# OLED Driver

## Supported Hardware

OLED modules using SSD1306 or SH1106 driver ICs, communicating over I2C.
Tested combinations:

|IC       |Size  |Platform|Notes                   |
|---------|------|--------|------------------------|
|SSD1306  |128x32|AVR     |Primary support         |
|SSD1306  |128x64|AVR     |Verified working        |
|SSD1306  |128x32|Arm     |                        |
|SH1106   |128x64|AVR     |No rotation or scrolling|

Hardware configurations using Arm-based microcontrollers or different sizes of OLED modules may be compatible, but are untested.

!> Warning: This OLED driver currently uses the new i2c_master driver from Split Common code. If your split keyboard uses I2C to communicate between sides, this driver could cause an address conflict (serial is fine). Please contact your keyboard vendor and ask them to migrate to the latest Split Common code to fix this. In addition, the display timeout system to reduce OLED burn-in also uses Split Common to detect keypresses, so you will need to implement custom timeout logic for non-Split Common keyboards.

## Usage

To enable the OLED feature, there are three steps. First, when compiling your keyboard, you'll need to add the following to your `rules.mk`:

```make
OLED_DRIVER_ENABLE = yes
```

Then in your `keymap.c` file, implement the OLED task call. This example assumes your keymap has three layers named `_QWERTY`, `_FN` and `_ADJ`:

```c
#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
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
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}
#endif
```

## Logo Example

In the default font, certain ranges of characters are reserved for a QMK logo. To render this logo to the OLED screen, use the following code example:

```c
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}
```

## Buffer Read Example
For some purposes, you may need to read the current state of the OLED display
buffer. The `oled_read_raw` function can be used to safely read bytes from the
buffer.

In this example, calling `fade_display` in the `oled_task_user` function will
slowly fade away whatever is on the screen by turning random pixels black over
time.
```c
//Setup some mask which can be or'd with bytes to turn off pixels
const uint8_t single_bit_masks[8] = {127, 191, 223, 239, 247, 251, 253, 254};

static void fade_display(void) {
    //Define the reader structure
    oled_buffer_reader_t reader;
    uint8_t buff_char;
    if (random() % 30 == 0) {
        srand(timer_read());
        // Fetch a pointer for the buffer byte at index 0. The return structure
        // will have the pointer and the number of bytes remaining from this
        // index position if we want to perform a sequential read by
        // incrementing the buffer pointer
        reader = oled_read_raw(0);
        //Loop over the remaining buffer and erase pixels as we go
        for (uint16_t i = 0; i < reader.remaining_element_count; i++) {
            //Get the actual byte in the buffer by dereferencing the pointer
            buff_char = *reader.current_element;
            if (buff_char != 0) {
                oled_write_raw_byte(buff_char & single_bit_masks[rand() % 8], i);
            }
            //increment the pointer to fetch a new byte during the next loop
            reader.current_element++;
        }
    }
}
```

## Other Examples

In split keyboards, it is very common to have two OLED displays that each render different content and are oriented or flipped differently. You can do this by switching which content to render by using the return value from `is_keyboard_master()` or `is_keyboard_left()` found in `split_util.h`, e.g:

```c
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }

    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();  // Renders a static logo
        oled_scroll_left();  // Turns on scrolling
    }
}
#endif
```

## Basic Configuration

|Define                     |Default          |Description                                                                                                               |
|---------------------------|-----------------|--------------------------------------------------------------------------------------------------------------------------|
|`OLED_DISPLAY_ADDRESS`     |`0x3C`           |The i2c address of the OLED Display                                                                                       |
|`OLED_FONT_H`              |`"glcdfont.c"`   |The font code file to use for custom fonts                                                                                |
|`OLED_FONT_START`          |`0`              |The starting characer index for custom fonts                                                                              |
|`OLED_FONT_END`            |`223`            |The ending characer index for custom fonts                                                                                |
|`OLED_FONT_WIDTH`          |`6`              |The font width                                                                                                            |
|`OLED_FONT_HEIGHT`         |`8`              |The font height (untested)                                                                                                |
|`OLED_TIMEOUT`             |`60000`          |Turns off the OLED screen after 60000ms of keyboard inactivity. Helps reduce OLED Burn-in. Set to 0 to disable.           |
|`OLED_SCROLL_TIMEOUT`      |`0`              |Scrolls the OLED screen after 0ms of OLED inactivity. Helps reduce OLED Burn-in. Set to 0 to disable.                     |
|`OLED_SCROLL_TIMEOUT_RIGHT`|*Not defined*    |Scroll timeout direction is right when defined, left when undefined.                                                      |
|`OLED_IC`                  |`OLED_IC_SSD1306`|Set to `OLED_IC_SH1106` if you're using the SH1106 OLED controller.                                                       |
|`OLED_COLUMN_OFFSET`       |`0`              |(SH1106 only.) Shift output to the right this many pixels.<br />Useful for 128x64 displays centered on a 132x64 SH1106 IC.|

 ## 128x64 & Custom sized OLED Displays

 The default display size for this feature is 128x32 and all necessary defines are precalculated with that in mind. We have added a define, `OLED_DISPLAY_128X64`, to switch all the values to be used in a 128x64 display, as well as added a custom define, `OLED_DISPLAY_CUSTOM`, that allows you to provide the necessary values to the driver.

|Define               |Default        |Description                                                                                                                             |
|---------------------|---------------|----------------------------------------------------------------------------------------------------------------------------------------|
|`OLED_DISPLAY_128X64`|*Not defined*  |Changes the display defines for use with 128x64 displays.                                                                               |
|`OLED_DISPLAY_CUSTOM`|*Not defined*  |Changes the display defines for use with custom displays.<br>Requires user to implement the below defines.                              |
|`OLED_DISPLAY_WIDTH` |`128`          |The width of the OLED display.                                                                                                          |
|`OLED_DISPLAY_HEIGHT`|`32`           |The height of the OLED display.                                                                                                         |
|`OLED_MATRIX_SIZE`   |`512`          |The local buffer size to allocate.<br>`(OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)`.                                                 |
|`OLED_BLOCK_TYPE`    |`uint16_t`     |The unsigned integer type to use for dirty rendering.                                                                                   |
|`OLED_BLOCK_COUNT`   |`16`           |The number of blocks the display is divided into for dirty rendering.<br>`(sizeof(OLED_BLOCK_TYPE) * 8)`.                               |
|`OLED_BLOCK_SIZE`    |`32`           |The size of each block for dirty rendering<br>`(OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)`.                                                  |
|`OLED_COM_PINS`      |`COM_PINS_SEQ` |How the SSD1306 chip maps it's memory to display.<br>Options are `COM_PINS_SEQ`, `COM_PINS_ALT`, `COM_PINS_SEQ_LR`, & `COM_PINS_ALT_LR`.|
|`OLED_SOURCE_MAP`    |`{ 0, ... N }` |Precalculated source array to use for mapping source buffer to target OLED memory in 90 degree rendering.                               |
|`OLED_TARGET_MAP`    |`{ 24, ... N }`|Precalculated target array to use for mapping source buffer to target OLED memory in 90 degree rendering.                               |


### 90 Degree Rotation - Technical Mumbo Jumbo

!> Rotation is unsupported on the SH1106.

```c
// OLED Rotation enum values are flags
typedef enum {
    OLED_ROTATION_0   = 0,
    OLED_ROTATION_90  = 1,
    OLED_ROTATION_180 = 2,
    OLED_ROTATION_270 = 3, // OLED_ROTATION_90 | OLED_ROTATION_180
} oled_rotation_t;
```

OLED displays driven by SSD1306 drivers only natively support in hardware 0 degree and 180 degree rendering. This feature is done in software and not free. Using this feature will increase the time to calculate what data to send over i2c to the OLED. If you are strapped for cycles, this can cause keycodes to not register. In testing however, the rendering time on an ATmega32U4 board only went from 2ms to 5ms and keycodes not registering was only noticed once we hit 15ms.

90 degree rotation is achieved by using bitwise operations to rotate each 8 block of memory and uses two precalculated arrays to remap buffer memory to OLED memory. The memory map defines are precalculated for remap performance and are calculated based on the display height, width, and block size. For example, in the 128x32 implementation with a `uint8_t` block type, we have a 64 byte block size. This gives us eight 8 byte blocks that need to be rotated and rendered. The OLED renders horizontally two 8 byte blocks before moving down a page, e.g:

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

```c
// OLED rotation enum values are flags
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

// Pans the buffer to the right (or left by passing true) by moving contents of the buffer
// Useful for moving the screen in preparation for new drawing 
// oled_scroll_left or oled_scroll_right should be preferred for all cases of moving a static
// image such as a logo or to avoid burn-in as it's much, much less cpu intensive
void oled_pan(bool left);

// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Remapped to call 'void oled_write(const char *data, bool invert);' on ARM
void oled_write_P(const char *data, bool invert);

// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Advances the cursor to the next page, wiring ' ' to the remainder of the current page
// Remapped to call 'void oled_write_ln(const char *data, bool invert);' on ARM
void oled_write_ln_P(const char *data, bool invert);

// Returns a pointer to the requested start index in the buffer plus remaining
// buffer length as struct
oled_buffer_reader_t oled_read_raw(uint16_t start_index);

// Writes a string to the buffer at current cursor position
void oled_write_raw(const char *data, uint16_t size);

// Writes a single byte into the buffer at the specified index
void oled_write_raw_byte(const char data, uint16_t index);

// Writes a PROGMEM string to the buffer at current cursor position
void oled_write_raw_P(const char *data, uint16_t size);

// Sets a specific pixel on or off
// Coordinates start at top-left and go right and down for positive x and y
void oled_write_pixel(uint8_t x, uint8_t y, bool on);

// Can be used to manually turn on the screen if it is off
// Returns true if the screen was on or turns on
bool oled_on(void);

// Can be used to manually turn off the screen if it is on
// Returns true if the screen was off or turns off
bool oled_off(void);

// Returns true if the oled is currently on, false if it is
// not
bool is_oled_on(void);

// Basically it's oled_render, but with timeout management and oled_task_user calling!
void oled_task(void);

// Called at the start of oled_task, weak function overridable by the user
void oled_task_user(void);

// Set the specific 8 lines rows of the screen to scroll.
// 0 is the default for start, and 7 for end, which is the entire
// height of the screen.  For 128x32 screens, rows 4-7 are not used.
void oled_scroll_set_area(uint8_t start_line, uint8_t end_line);

// Sets scroll speed, 0-7, fastest to slowest. Default is three.
// Does not take effect until scrolling is either started or restarted
// the ssd1306 supports 8 speeds with the delay
// listed below betwen each frame of the scrolling effect
// 0=2, 1=3, 2=4, 3=5, 4=25, 5=64, 6=128, 7=256
void oled_scroll_set_speed(uint8_t speed);

// Begin scrolling the entire display right
// Returns true if the screen was scrolling or starts scrolling
// NOTE: display contents cannot be changed while scrolling
bool oled_scroll_right(void);

// Begin scrolling the entire display left
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

## SSD1306.h Driver Conversion Guide

|Old API                  |Recommended New API              |
|-------------------------|---------------------------------|
|`struct CharacterMatrix` |*removed - delete all references*|
|`iota_gfx_init`          |`oled_init`                      |
|`iota_gfx_on`            |`oled_on`                        |
|`iota_gfx_off`           |`oled_off`                       |
|`iota_gfx_flush`         |`oled_render`                    |
|`iota_gfx_write_char`    |`oled_write_char`                |
|`iota_gfx_write`         |`oled_write`                     |
|`iota_gfx_write_P`       |`oled_write_P`                   |
|`iota_gfx_clear_screen`  |`oled_clear`                     |
|`matrix_clear`           |*removed - delete all references*|
|`matrix_write_char_inner`|`oled_write_char`                |
|`matrix_write_char`      |`oled_write_char`                |
|`matrix_write`           |`oled_write`                     |
|`matrix_write_ln`        |`oled_write_ln`                  |
|`matrix_write_P`         |`oled_write_P`                   |
|`matrix_write_ln_P`      |`oled_write_ln_P`                |
|`matrix_render`          |`oled_render`                    |
|`iota_gfx_task`          |`oled_task`                      |
|`iota_gfx_task_user`     |`oled_task_user`                 |
