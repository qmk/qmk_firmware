# HD44780 LCD Driver {#hd44780-lcd-driver}

## Supported Hardware {#supported-hardware}

LCD modules using [HD44780U](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf) IC or equivalent, communicating in 4-bit mode.

|Module|Size          |Notes                            |
|------|--------------|---------------------------------|
|1602A |16x2, 5x8 dots|                                 |
|2004A |20x4, 5x8 dots|Untested, not currently supported|

To run these modules at 3.3V, an additional MAX660 voltage converter IC must be soldered on, along with two 10µF capacitors. See [this page](https://www.codrey.com/electronic-circuits/hack-your-16x2-lcd/) for more details.

## Usage {#usage}

Add the following to your `rules.mk`:

```make
HD44780_ENABLE = yes
```

## Basic Configuration {#basic-configuration}

Add the following to your `config.h`:

|Define                 |Default       |Description                                                                                          |
|-----------------------|--------------|-----------------------------------------------------------------------------------------------------|
|`HD44780_DATA_PINS`    |*Not defined* |(Required) An array of four GPIO pins connected to the display's D4-D7 pins, eg. `{ B1, B3, B2, B6 }`|
|`HD44780_RS_PIN`       |*Not defined* |(Required) The GPIO connected to the display's RS pin                                                |
|`HD44780_RW_PIN`       |*Not defined* |(Required) The GPIO connected to the display's RW pin                                                |
|`HD44780_E_PIN`        |*Not defined* |(Required) The GPIO connected to the display's E pin                                                 |
|`HD44780_DISPLAY_COLS` |`16`          |The number of visible characters on a single line of the display                                     |
|`HD44780_DISPLAY_LINES`|`2`           |The number of visible lines on the display                                                           |
|`HD44780_WRAP_LINES`   |*Not defined* |If defined, input characters will wrap to the next line                                              |

## Examples {#examples}

### Hello World {#example-hello-world}

Add the following to your `keymap.c`:

```c
void keyboard_post_init_user(void) {
    hd44780_init(true, true); // Show blinking cursor
    hd44780_puts_P(PSTR("Hello, world!\n"));
}
```

### Custom Character Definition {#example-custom-character}

Up to eight custom characters can be defined. This data is stored in the Character Generator RAM (CGRAM), and is not persistent across power cycles.

This example defines the QMK Psi as the first custom character. The first 16 positions in the character set are reserved for the eight custom characters duplicated.

```
Byte |      16 8 4 2 1
   1 | x x x ■ □ ■ □ ■
   2 | x x x ■ □ ■ □ ■
   3 | x x x ■ □ ■ □ ■
   4 | x x x □ ■ ■ ■ □
   5 | x x x □ □ ■ □ □
   6 | x x x □ □ ■ □ □
   7 | x x x □ □ ■ □ □
   8 | x x x □ □ □ □ □
```

```c
const uint8_t PROGMEM psi[8] = { 0x15, 0x15, 0x15, 0x0E, 0x04, 0x04, 0x04, 0x00 };

void keyboard_post_init_user(void) {
    hd44780_init(false, false);
    hd44780_define_char_P(0, psi);
    // Cursor is incremented while defining characters so must be reset
    hd44780_home();
    // 0x08 to avoid null terminator
    hd44780_puts_P(PSTR("\x08 QMK Firmware"));
}
```

## API {#api}

### `void hd44780_init(bool cursor, bool blink)` {#api-hd44780-init}

Initialize the display.

This function should be called only once, before any of the other functions can be called.

#### Arguments {#api-hd44780-init-arguments}

 - `bool cursor`  
   Whether to show the cursor.
 - `bool blink`  
   Whether to blink the cursor, if shown.

---

### `void hd44780_clear(void)` {#api-hd44780-clear}

Clear the display.

This function is called on init.

---

### `void hd44780_home(void)` {#api-hd44780-home}

Move the cursor to the home position.

This function is called on init.

---

### `void hd44780_on(bool cursor, bool blink)` {#api-hd44780-on}

Turn the display on, and/or set the cursor properties.

This function is called on init.

#### Arguments {#api-hd44780-on-arguments}

 - `bool cursor`  
   Whether to show the cursor.
 - `bool blink`  
   Whether to blink the cursor, if shown.

---

### `void hd44780_off(void)` {#api-hd44780-off}

Turn the display off.

---

### `void hd44780_set_cursor(uint8_t col, uint8_t line)` {#api-hd44780-set-cursor}

Move the cursor to the specified position on the display.

#### Arguments {#api-hd44780-set-cursor-arguments}

 - `uint8_t col`  
   The column number to move to, from 0 to 15 on 16x2 displays.
 - `bool line`  
   The line number to move to, either 0 or 1 on 16x2 displays.

---

### `void hd44780_putc(char c)` {#api-hd44780-putc}

Print a character to the display. The newline character `\n` will move the cursor to the start of the next line.

The exact character shown may depend on the ROM code of your particular display - refer to the datasheet for the full character set.

#### Arguments {#api-hd44780-putc-arguments}

 - `char c`  
   The character to print.

---

### `void hd44780_puts(const char *s)` {#api-hd44780-puts}

Print a string of characters to the display.

#### Arguments {#api-hd44780-puts-arguments}

 - `const char *s`  
   The string to print.

---

### `void hd44780_puts_P(const char *s)` {#api-hd44780-puts-p}

Print a string of characters from PROGMEM to the display.

On ARM devices, this function is simply an alias of `hd44780_puts()`.

#### Arguments {#api-hd44780-puts-p-arguments}

 - `const char *s`  
   The PROGMEM string to print (ie. `PSTR("Hello")`).

---

### `void hd44780_define_char(uint8_t index, uint8_t *data)` {#api-hd44780-define-char}

Define a custom character.

#### Arguments {#api-hd44780-define-char-arguments}

 - `uint8_t index`  
   The index of the custom character to define, from 0 to 7.
 - `uint8_t *data`  
   An array of 8 bytes containing the 5-bit row data of the character, where the first byte is the topmost row, and the least significant bit of each byte is the rightmost column.

---

### `void hd44780_define_char_P(uint8_t index, const uint8_t *data)` {#api-hd44780-define-char-p}

Define a custom character from PROGMEM.

On ARM devices, this function is simply an alias of `hd44780_define_char()`.

#### Arguments {#api-hd44780-define-char-p-arguments}

 - `uint8_t index`  
   The index of the custom character to define, from 0 to 7.
 - `const uint8_t *data`  
   A PROGMEM array of 8 bytes containing the 5-bit row data of the character, where the first byte is the topmost row, and the least significant bit of each byte is the rightmost column.

---

### `bool hd44780_busy(void)` {#api-hd44780-busy}

Indicates whether the display is currently processing, and cannot accept instructions.

#### Return Value {#api-hd44780-busy-arguments}

`true` if the display is busy.

---

### `void hd44780_write(uint8_t data, bool isData)` {#api-hd44780-write}

Write a byte to the display.

#### Arguments {#api-hd44780-write-arguments}

 - `uint8_t data`  
   The byte to send to the display.
 - `bool isData`  
   Whether the byte is an instruction or character data.

---

### `uint8_t hd44780_read(bool isData)` {#api-hd44780-read}

Read a byte from the display.

#### Arguments {#api-hd44780-read-arguments}

 - `bool isData`  
   Whether to read the current cursor position, or the character at the cursor.

#### Return Value {#api-hd44780-read-return}

If `isData` is `true`, the returned byte will be the character at the current DDRAM address. Otherwise, it will be the current DDRAM address and the busy flag.

---

### `void hd44780_command(uint8_t command)` {#api-hd44780-command}

Send a command to the display. Refer to the datasheet and `hd44780.h` for the valid commands and defines.

This function waits for the display to clear the busy flag before sending the command.

#### Arguments {#api-hd44780-command-arguments}

 - `uint8_t command`  
   The command to send.

---

### `void hd44780_data(uint8_t data)` {#api-hd44780-data}

Send a byte of data to the display.

This function waits for the display to clear the busy flag before sending the data.

#### Arguments {#api-hd44780-data-arguments}

 - `uint8_t data`  
   The byte of data to send.

---

### `void hd44780_set_cgram_address(uint8_t address)` {#api-hd44780-set-cgram-address}

Set the CGRAM address.

This function is used when defining custom characters.

#### Arguments {#api-hd44780-set-cgram-address-arguments}

 - `uint8_t address`  
   The CGRAM address to move to, from `0x00` to `0x3F`.

---

### `void hd44780_set_ddram_address(uint8_t address)` {#api-hd44780-set-ddram-address}

Set the DDRAM address.

This function is used when printing characters to the display, and setting the cursor.

#### Arguments {#api-hd44780-set-ddram-address-arguments}

 - `uint8_t address`  
   The DDRAM address to move to, from `0x00` to `0x7F`.
