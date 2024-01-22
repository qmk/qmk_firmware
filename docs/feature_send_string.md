# Send String :id=send-string

The Send String API is part of QMK's macro system. It allows for sequences of keystrokes to be sent automatically.

The full ASCII character set is supported, along with all of the keycodes in the Basic Keycode range (as these are the only ones that will actually be sent to the host).

?> Unicode characters are **not** supported with this API -- see the [Unicode](feature_unicode.md) feature instead.

## Usage :id=usage

Send String is enabled by default, so there is usually no need for any special setup. However, if it is disabled, add the following to your `rules.mk`:

```make
SEND_STRING_ENABLE = yes
```

## Basic Configuration :id=basic-configuration

Add the following to your `config.h`:

|Define           |Default         |Description                                                                                                 |
|-----------------|----------------|------------------------------------------------------------------------------------------------------------|
|`SENDSTRING_BELL`|*Not defined*   |If the [Audio](feature_audio.md) feature is enabled, the `\a` character (ASCII `BEL`) will beep the speaker.|
|`BELL_SOUND`     |`TERMINAL_SOUND`|The song to play when the `\a` character is encountered. By default, this is an eighth note of C5.          |

## Keycodes :id=keycodes

The Send String functions accept C string literals, but specific keycodes can be injected with the below macros. All of the keycodes in the [Basic Keycode range](keycodes_basic.md) are supported (as these are the only ones that will actually be sent to the host), but with an `X_` prefix instead of `KC_`.

|Macro         |Description                                                        |
|--------------|-------------------------------------------------------------------|
|`SS_TAP(x)`   |Send a keydown, then keyup, event for the given Send String keycode|
|`SS_DOWN(x)`  |Send a keydown event for the given Send String keycode             |
|`SS_UP(x)`    |Send a keyup event for the given Send String keycode               |
|`SS_DELAY(ms)`|Wait for `ms` milliseconds                                         |

The following characters are also mapped to their respective keycodes for convenience:

|Character|Hex   |ASCII|Keycode       |
|---------|------|-----|--------------|
|`\b`     |`\x08`|`BS` |`KC_BACKSPACE`|
|`\e`     |`\x09`|`ESC`|`KC_ESCAPE`   |
|`\n`     |`\x0A`|`LF` |`KC_ENTER`    |
|`\t`     |`\x1B`|`TAB`|`KC_TAB`      |
|         |`\x7F`|`DEL`|`KC_DELETE`   |

### Language Support :id=language-support

By default, Send String assumes your OS keyboard layout is set to US ANSI. If you are using a different keyboard layout, you can [override the lookup tables used to convert ASCII characters to keystrokes](reference_keymap_extras.md#sendstring-support).

## Examples :id=examples

### Hello World :id=example-hello-world

A simple custom keycode which types out "Hello, world!" and the Enter key when pressed.

Add the following to your `keymap.c`:

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SS_HELLO:
            if (record->event.pressed) {
                SEND_STRING("Hello, world!\n");
            }
            return false;
    }

    return true;
}
```

### Keycode Injection :id=example-keycode-injection

This example types out opening and closing curly braces, then taps the left arrow key to move the cursor between the two.

```c
SEND_STRING("{}" SS_TAP(X_LEFT));
```

This example types Ctrl+A, then Ctrl+C, without releasing Ctrl.

```c
SEND_STRING(SS_LCTL("ac"));
```

## API :id=api

### `void send_string(const char *string)` :id=api-send-string

Type out a string of ASCII characters.

This function simply calls `send_string_with_delay(string, 0)`.

#### Arguments :id=api-send-string-arguments

 - `const char *string`  
   The string to type out.

---

### `void send_string_with_delay(const char *string, uint8_t interval)` :id=api-send-string-with-delay

Type out a string of ASCII characters, with a delay between each character.

#### Arguments :id=api-send-string-with-delay-arguments

 - `const char *string`  
   The string to type out.
 - `uint8_t interval`  
   The amount of time, in milliseconds, to wait before typing the next character.

---

### `void send_string_P(const char *string)` :id=api-send-string-p

Type out a PROGMEM string of ASCII characters.

On ARM devices, this function is simply an alias for `send_string_with_delay(string, 0)`.

#### Arguments :id=api-send-string-p-arguments

 - `const char *string`  
   The string to type out.

---

### `void send_string_with_delay_P(const char *string, uint8_t interval)` :id=api-send-string-with-delay-p

Type out a PROGMEM string of ASCII characters, with a delay between each character.

On ARM devices, this function is simply an alias for `send_string_with_delay(string, interval)`.

#### Arguments :id=api-send-string-with-delay-p-arguments

 - `const char *string`  
   The string to type out.
 - `uint8_t interval`  
   The amount of time, in milliseconds, to wait before typing the next character.

---

### `void send_char(char ascii_code)` :id=api-send-char

Type out an ASCII character.

#### Arguments :id=api-send-char-arguments

 - `char ascii_code`  
   The character to type.

---

### `void send_dword(uint32_t number)` :id=api-send-dword

Type out an eight digit (unsigned 32-bit) hexadecimal value.

The format is `[0-9a-f]{8}`, eg. `00000000` through `ffffffff`.

#### Arguments :id=api-send-dword-arguments

 - `uint32_t number`  
   The value to type, from 0 to 4,294,967,295.

---

### `void send_word(uint16_t number)` :id=api-send-word

Type out a four digit (unsigned 16-bit) hexadecimal value.

The format is `[0-9a-f]{4}`, eg. `0000` through `ffff`.

#### Arguments :id=api-send-word-arguments

 - `uint16_t number`  
   The value to type, from 0 to 65,535.

---

### `void send_byte(uint8_t number)` :id=api-send-bytes

Type out a two digit (8-bit) hexadecimal value.

The format is `[0-9a-f]{2}`, eg. `00` through `ff`.

#### Arguments :id=api-send-byte-arguments

 - `uint8_t number`  
   The value to type, from 0 to 255.

---

### `void send_nibble(uint8_t number)` :id=api-send-nibble

Type out a single hexadecimal digit.

The format is `[0-9a-f]{1}`, eg. `0` through `f`.

#### Arguments :id=api-send-nibble-arguments

 - `uint8_t number`  
   The value to type, from 0 to 15.

---

### `void tap_random_base64(void)` :id=api-tap-random-base64

Type a pseudorandom character from the set `A-Z`, `a-z`, `0-9`, `+` and `/`.

---

### `SEND_STRING(string)` :id=api-send-string-macro

Shortcut macro for `send_string_with_delay_P(PSTR(string), 0)`.

On ARM devices, this define evaluates to `send_string_with_delay(string, 0)`.

---

### `SEND_STRING_DELAY(string, interval)` :id=api-send-string-delay-macro

Shortcut macro for `send_string_with_delay_P(PSTR(string), interval)`.

On ARM devices, this define evaluates to `send_string_with_delay(string, interval)`.
