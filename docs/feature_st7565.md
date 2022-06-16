# ST7565 LCD Driver

## Supported Hardware

LCD modules using ST7565 driver IC, communicating over SPI.

|Module                        |IC     |Size  |Notes                                                     |
|------------------------------|-------|------|----------------------------------------------------------|
|Newhaven Display NHD-C12832A1Z|ST7565R|128x32|Used by Ergodox Infinity; primary consumer of this feature|
|Zolentech ZLE12864B           |ST7565P|128x64|Requires contrast adjustment                              |

## Usage

To enable the feature, there are three steps. First, when compiling your keyboard, you'll need to add the following to your `rules.mk`:

```make
ST7565_ENABLE = yes
```

Then in your `keymap.c` file, implement the ST7565 task call. This example assumes your keymap has three layers named `_QWERTY`, `_FN` and `_ADJ`:

```c
#ifdef ST7565_ENABLE
void st7565_task_user(void) {
    // Host Keyboard Layer Status
    st7565_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            st7565_write_P(PSTR("Default\n"), false);
            break;
        case _FN:
            st7565_write_P(PSTR("FN\n"), false);
            break;
        case _ADJ:
            st7565_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            st7565_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    st7565_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    st7565_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    st7565_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}
#endif
```

## Logo Example

In the default font, certain ranges of characters are reserved for a QMK logo. To render this logo to the screen, use the following code example:

```c
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    st7565_write_P(qmk_logo, false);
}
```

## Buffer Read Example
For some purposes, you may need to read the current state of the display buffer. The `st7565_read_raw` function can be used to safely read bytes from the buffer.

In this example, calling `fade_display` in the `st7565_task_user` function will slowly fade away whatever is on the screen by turning random pixels off over time.
```c
//Setup some mask which can be or'd with bytes to turn off pixels
const uint8_t single_bit_masks[8] = {127, 191, 223, 239, 247, 251, 253, 254};

static void fade_display(void) {
    //Define the reader structure
    display_buffer_reader_t reader;
    uint8_t buff_char;
    if (random() % 30 == 0) {
        srand(timer_read());
        // Fetch a pointer for the buffer byte at index 0. The return structure
        // will have the pointer and the number of bytes remaining from this
        // index position if we want to perform a sequential read by
        // incrementing the buffer pointer
        reader = st7565_read_raw(0);
        //Loop over the remaining buffer and erase pixels as we go
        for (uint16_t i = 0; i < reader.remaining_element_count; i++) {
            //Get the actual byte in the buffer by dereferencing the pointer
            buff_char = *reader.current_element;
            if (buff_char != 0) {
                st7565_write_raw_byte(buff_char & single_bit_masks[rand() % 8], i);
            }
            //increment the pointer to fetch a new byte during the next loop
            reader.current_element++;
        }
    }
}
```

## Other Examples

In split keyboards, it is very common to have two displays that each render different content and are oriented or flipped differently. You can do this by switching which content to render by using the return value from `is_keyboard_master()` or `is_keyboard_left()` found in `split_util.h`, e.g:

```c
#ifdef ST7565_ENABLE
display_rotation_t st7565_init_user(display_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return DISPLAY_ROTATION_180;  // flips the display 180 degrees if offhand
    }

    return rotation;
}

void st7565_task_user(void) {
    if (is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();  // Renders a static logo
    }
}
#endif
```

## Basic Configuration

|Define                  |Default       |Description                                                                                          |
|------------------------|--------------|-----------------------------------------------------------------------------------------------------|
|`ST7565_A0_PIN`         |*Not defined* |(Required) The GPIO connected to the display's A0 (data/command) pin                                 |
|`ST7565_RST_PIN`        |*Not defined* |(Required) The GPIO connected to the display's reset pin                                             |
|`ST7565_SS_PIN`         |*Not defined* |(Required) The GPIO connected to the display's slave select pin                                      |
|`ST7565_SPI_CLK_DIVISOR`|`4`           |The SPI clock divisor to use                                                                         |
|`ST7565_FONT_H`         |`"glcdfont.c"`|The font code file to use for custom fonts                                                           |
|`ST7565_FONT_START`     |`0`           |The starting character index for custom fonts                                                        |
|`ST7565_FONT_END`       |`223`         |The ending character index for custom fonts                                                          |
|`ST7565_FONT_WIDTH`     |`6`           |The font width                                                                                       |
|`ST7565_FONT_HEIGHT`    |`8`           |The font height (untested)                                                                           |
|`ST7565_TIMEOUT`        |`60000`       |Turns off the screen after 60000ms of keyboard inactivity. Helps reduce burn-in. Set to 0 to disable.|
|`ST7565_COLUMN_OFFSET`  |`0`           |Shift output to the right this many pixels.                                                          |
|`ST7565_CONTRAST`       |`32`          |The default contrast level of the display, from 0 to 255.                                            |
|`ST7565_UPDATE_INTERVAL`|`0`           |Set the time interval for updating the display in ms. This will improve the matrix scan rate.        |

## Custom sized displays

The default display size for this feature is 128x32 and all necessary defines are precalculated with that in mind.

|Define                 |Default   |Description                                                                                                |
|-----------------------|----------|-----------------------------------------------------------------------------------------------------------|
|`ST7565_DISPLAY_WIDTH` |`128`     |The width of the display.                                                                                  |
|`ST7565_DISPLAY_HEIGHT`|`32`      |The height of the display.                                                                                 |
|`ST7565_MATRIX_SIZE`   |`512`     |The local buffer size to allocate.<br>`(ST7565_DISPLAY_HEIGHT / 8 * ST7565_DISPLAY_WIDTH)`.                |
|`ST7565_BLOCK_TYPE`    |`uint16_t`|The unsigned integer type to use for dirty rendering.                                                      |
|`ST7565_BLOCK_COUNT`   |`16`      |The number of blocks the display is divided into for dirty rendering.<br>`(sizeof(ST7565_BLOCK_TYPE) * 8)`.|
|`ST7565_BLOCK_SIZE`    |`32`      |The size of each block for dirty rendering<br>`(ST7565_MATRIX_SIZE / ST7565_BLOCK_COUNT)`.                 |

## API

```c
// Rotation enum values are flags
typedef enum {
    DISPLAY_ROTATION_0,
    DISPLAY_ROTATION_180
} display_rotation_t;

// Initialize the display, rotating the rendered output based on the define passed in.
// Returns true if the was initialized successfully
bool st7565_init(display_rotation_t rotation);

// Called at the start of st7565_init, weak function overridable by the user
// rotation - the value passed into st7565_init
// Return new display_rotation_t if you want to override default rotation
display_rotation_t st7565_init_user(display_rotation_t rotation);

// Clears the display buffer, resets cursor position to 0, and sets the buffer to dirty for rendering
void st7565_clear(void);

// Renders the dirty chunks of the buffer to display
void st7565_render(void);

// Moves cursor to character position indicated by column and line, wraps if out of bounds
// Max column denoted by 'st7565_max_chars()' and max lines by 'st7565_max_lines()' functions
void st7565_set_cursor(uint8_t col, uint8_t line);

// Advances the cursor to the next page, writing ' ' if true
// Wraps to the begining when out of bounds
void st7565_advance_page(bool clearPageRemainder);

// Moves the cursor forward 1 character length
// Advance page if there is not enough room for the next character
// Wraps to the begining when out of bounds
void st7565_advance_char(void);

// Writes a single character to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Main handler that writes character data to the display buffer
void st7565_write_char(const char data, bool invert);

// Writes a string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
void st7565_write(const char *data, bool invert);

// Writes a string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Advances the cursor to the next page, wiring ' ' to the remainder of the current page
void st7565_write_ln(const char *data, bool invert);

// Pans the buffer to the right (or left by passing true) by moving contents of the buffer
// Useful for moving the screen in preparation for new drawing
void st7565_pan(bool left);

// Returns a pointer to the requested start index in the buffer plus remaining
// buffer length as struct
display_buffer_reader_t st7565_read_raw(uint16_t start_index);

// Writes a string to the buffer at current cursor position
void st7565_write_raw(const char *data, uint16_t size);

// Writes a single byte into the buffer at the specified index
void st7565_write_raw_byte(const char data, uint16_t index);

// Sets a specific pixel on or off
// Coordinates start at top-left and go right and down for positive x and y
void st7565_write_pixel(uint8_t x, uint8_t y, bool on);

// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Remapped to call 'void st7565_write(const char *data, bool invert);' on ARM
void st7565_write_P(const char *data, bool invert);

// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Advances the cursor to the next page, wiring ' ' to the remainder of the current page
// Remapped to call 'void st7565_write_ln(const char *data, bool invert);' on ARM
void st7565_write_ln_P(const char *data, bool invert);

// Writes a PROGMEM string to the buffer at current cursor position
void st7565_write_raw_P(const char *data, uint16_t size);

// Can be used to manually turn on the screen if it is off
// Returns true if the screen was on or turns on
bool st7565_on(void);

// Called when st7565_on() turns on the screen, weak function overridable by the user
// Not called if the screen is already on
void st7565_on_user(void);

// Can be used to manually turn off the screen if it is on
// Returns true if the screen was off or turns off
bool st7565_off(void);

// Called when st7565_off() turns off the screen, weak function overridable by the user
// Not called if the screen is already off
void st7565_off_user(void);

// Returns true if the screen is currently on, false if it is
// not
bool st7565_is_on(void);

// Basically it's st7565_render, but with timeout management and st7565_task_user calling!
void st7565_task(void);

// Called at the start of st7565_task, weak function overridable by the user
void st7565_task_user(void);

// Inverts the display
// Returns true if the screen was or is inverted
bool st7565_invert(bool invert);

// Returns the maximum number of characters that will fit on a line
uint8_t st7565_max_chars(void);

// Returns the maximum number of lines that will fit on the display
uint8_t st7565_max_lines(void);
```
