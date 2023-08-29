# Unicode :id=unicode

With a little help from your OS, practically any Unicode character can be input using your keyboard.

## Caveats :id=caveats

There are some limitations to this feature. Because there is no "standard" method of Unicode input across all operating systems, each of them require their own setup process on both the host *and* in the firmware, which may involve installation of additional software. This also means Unicode input will not "just work" when the keyboard is plugged into another device.

## Usage :id=usage

The core Unicode API can be used purely programmatically. However, there are also additional subsystems which build on top of it and come with keycodes to make things easier. See below for more details.

Add the following to your keymap's `rules.mk`:

```make
UNICODE_COMMON = yes
```

## Basic Configuration :id=basic-configuration

Add the following to your `config.h`:

|Define                  |Default           |Description                                                                     |
|------------------------|------------------|--------------------------------------------------------------------------------|
|`UNICODE_KEY_MAC`       |`KC_LEFT_ALT`     |The key to hold when beginning a Unicode sequence with the macOS input mode     |
|`UNICODE_KEY_LNX`       |`LCTL(LSFT(KC_U))`|The key to tap when beginning a Unicode sequence with the Linux input mode      |
|`UNICODE_KEY_WINC`      |`KC_RIGHT_ALT`    |The key to hold when beginning a Unicode sequence with the WinCompose input mode|
|`UNICODE_SELECTED_MODES`|`-1`              |A comma separated list of input modes for cycling through                       |
|`UNICODE_CYCLE_PERSIST` |`true`            |Whether to persist the current Unicode input mode to EEPROM                     |
|`UNICODE_TYPE_DELAY`    |`10`              |The amount of time to wait, in milliseconds, between Unicode sequence keystrokes|

### Audio Feedback :id=audio-feedback

If you have the [Audio](feature_audio.md) feature enabled on your board, you can configure it to play sounds when the input mode is changed.

Add the following to your `config.h`:

|Define             |Default|Description                                                |
|-------------------|-------|-----------------------------------------------------------|
|`UNICODE_SONG_MAC` |*n/a*  |The song to play when the macOS input mode is selected     |
|`UNICODE_SONG_LNX` |*n/a*  |The song to play when the Linux input mode is selected     |
|`UNICODE_SONG_BSD` |*n/a*  |The song to play when the BSD input mode is selected       |
|`UNICODE_SONG_WIN` |*n/a*  |The song to play when the Windows input mode is selected   |
|`UNICODE_SONG_WINC`|*n/a*  |The song to play when the WinCompose input mode is selected|

## Input Subsystems :id=input-subsystems

Each of these subsystems have their own pros and cons in terms of flexibility and ease of use. Choose the one that best fits your needs.

<!-- tabs:start -->

### ** Basic **

This is the easiest to use, albeit somewhat limited. It supports code points up to `U+7FFF`, which covers characters for most modern languages (including East Asian), as well as many symbols, but does not include emoji.

To enable Basic Unicode, add the following to your `rules.mk`:

```make
UNICODE_ENABLE = yes
```

You can then add `UC(c)` keycodes to your keymap, where *c* is the code point of the desired character (in hexadecimal - the `U+` prefix will not work). For example, `UC(0x40B)` will output [Ћ](https://unicode-table.com/en/040B/), and `UC(0x30C4)` will output [ツ](https://unicode-table.com/en/30C4).

### ** Unicode Map **

Unicode Map supports all possible code points (up to `U+10FFFF`). Here, the code points are stored in a separate mapping table (which may contain at most 16,384 entries), instead of directly in the keymap.

To enable Unicode Map, add the following to your `rules.mk`:

```make
UNICODEMAP_ENABLE = yes
```

Then, you will need to create a mapping table in your `keymap.c`, and (optionally) an enum for naming the array indices, like so:

```c
enum unicode_names {
    BANG,
    IRONY,
    SNEK
};

const uint32_t PROGMEM unicode_map[] = {
    [BANG]  = 0x203D,  // ‽
    [IRONY] = 0x2E2E,  // ⸮
    [SNEK]  = 0x1F40D, // 🐍
};
```

Finally, add `UM(i)` keycodes to your keymap, where *i* is an index into the `unicode_map[]` array. If you defined the enum above, you can use those names instead, for example `UM(BANG)` or `UM(SNEK)`.

#### Lower and Upper Case Pairs :id=unicodemap-pairs

Some writing systems have lowercase and uppercase variants of each character, such as å and Å. To make inputting these characters easier, you can use the `UP(i, j)` keycode in your keymap, where *i* and *j* are the mapping table indices of the lowercase and uppercase characters, respectively. If you're holding down Shift or have Caps Lock turned on when you press the key, the uppercase character will be inserted; otherwise, the lowercase character will be inserted.

```c
const uint32_t PROGMEM unicode_map[] = {
    [AE_LOWER] = 0x00E6,  // æ
    [AE_UPPER] = 0x00C6,  // Æ
};
```

This is most useful when creating a keymap for an international layout with special characters. Instead of having to put the lower and upper case versions of a character on separate keys, you can have them both on the same key. This helps blend Unicode keys in with regular keycodes.

Due to keycode size constraints, *i* and *j* can each only refer to one of the first 128 characters in your `unicode_map`. In other words, 0 ≤ *i* ≤ 127 and 0 ≤ *j* ≤ 127.

### ** UCIS **

As with Unicode Map, the UCIS method also supports all possible code points, and requires the use of a mapping table. However, it works much differently - Unicode characters are input by replacing a typed mnemonic.

To enable UCIS, add the following to your keymap's `rules.mk`:

```make
UCIS_ENABLE = yes
```

Then, create a mapping table in your `keymap.c`:

```c
const ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("poop", 0x1F4A9),                // 💩
    UCIS_SYM("rofl", 0x1F923),                // 🤣
    UCIS_SYM("ukr", 0x1F1FA, 0x1F1E6),        // 🇺🇦
    UCIS_SYM("look", 0x0CA0, 0x005F, 0x0CA0)  // ಠ_ಠ
);
```

By default, each table entry may be up to three code points long. This can be changed by adding `#define UCIS_MAX_CODE_POINTS n` to your keymap's `config.h`.

To invoke UCIS input, the `ucis_start()` function must first be called (for example, in a custom "Unicode" keycode). Then, type the mnemonic for the mapping table entry (such as "rofl"), and hit Space or Enter. The "rofl" text will be backspaced and the emoji inserted.

<!-- tabs:end -->

## Input Modes :id=input-modes

Unicode input works by typing a sequence of characters, similar to a macro. However, since this sequence depends on your OS, you will need to prepare both your host machine and QMK to recognise and send the correct Unicode input sequences respectively.

To set the list of enabled input modes, add the `UNICODE_SELECTED_MODES` define to your keymap's `config.h`, for example:

```c
#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX
// or
#define UNICODE_SELECTED_MODES UNICODE_MODE_MAC, UNICODE_MODE_WINCOMPOSE
```

These modes can then be cycled through using the `UC_NEXT` and `UC_PREV` keycodes. You can also switch to any input mode, even if it is not specified in `UNICODE_SELECTED_MODES`, using their respective keycodes.

If your keyboard has working EEPROM, it will remember the last used input mode and continue using it on the next power up. This can be disabled by defining `UNICODE_CYCLE_PERSIST` to `false`.

<!-- tabs:start -->

### ** macOS **

**Mode Name:** `UNICODE_MODE_MAC`

macOS has built-in support for Unicode input as its own input source. It supports all possible code points by way of surrogate pairs for code points above `U+FFFF`.

To enable, go to **System Preferences → Keyboard → Input Sources**, then add Unicode Hex Input to the list (under Other), and activate it from the input dropdown in the menu bar. Note that this may disable some Option-based shortcuts such as Option+Left and Option+Right.

### ** Linux (IBus) **

**Mode Name:** `UNICODE_MODE_LINUX`

For Linux distros with IBus, Unicode input is enabled by default, supports all possible code points, and works almost anywhere. Without IBus, it works under GTK apps, but rarely anywhere else.

Users who would like support in non-GTK apps without IBus may need to resort to a more indirect method, such as creating a custom keyboard layout.

### ** Windows (WinCompose) **

**Mode Name:** `UNICODE_MODE_WINCOMPOSE`

This mode requires a third-party tool called [WinCompose](https://github.com/samhocevar/wincompose). It supports all possible code points, and is the recommended input mode for Windows.

To enable, install the [latest release from GitHub](https://github.com/samhocevar/wincompose/releases/latest). Once installed, it will automatically run on startup. This works reliably under all versions of Windows supported by WinCompose.

### ** Windows (HexNumpad) **

**Mode Name:** `UNICODE_MODE_WINDOWS`

!> This input mode is *not* the "Alt code" system. Alt codes are not Unicode; they instead follow [the Windows-1252 character set](https://en.wikipedia.org/wiki/Alt_code).

This is Windows' built-in hex numpad Unicode input mode. It only supports code points up to `U+FFFF`, and is not recommended due to reliability and compatibility issues.

To enable, run the following as an administrator, then reboot:

```
reg add "HKCU\Control Panel\Input Method" -v EnableHexNumpad -t REG_SZ -d 1
```

### ** Emacs **

**Mode Name:** `UNICODE_MODE_EMACS`

Emacs supports code point input with the `insert-char` command.

### ** BSD **

**Mode Name:** `UNICODE_MODE_BSD`

Not currently implemented. If you're a BSD user and want to contribute support for this input mode, please [feel free](contributing.md)!

<!-- tabs:end -->

## Keycodes :id=keycodes

|Key                         |Aliases  |Description                                                     |
|----------------------------|---------|----------------------------------------------------------------|
|`UC(c)`                     |         |Send Unicode code point `c`, up to `0x7FFF`                     |
|`UM(i)`                     |         |Send Unicode code point at index `i` in `unicode_map`           |
|`UP(i, j)`                  |         |Send Unicode code point at index `i`, or `j` if Shift/Caps is on|
|`QK_UNICODE_MODE_NEXT`      |`UC_NEXT`|Cycle through selected input modes                              |
|`QK_UNICODE_MODE_PREVIOUS`  |`UC_PREV`|Cycle through selected input modes in reverse                   |
|`QK_UNICODE_MODE_MACOS`     |`UC_MAC` |Switch to macOS input                                           |
|`QK_UNICODE_MODE_LINUX`     |`UC_LINX`|Switch to Linux input                                           |
|`QK_UNICODE_MODE_WINDOWS`   |`UC_WIN` |Switch to Windows input                                         |
|`QK_UNICODE_MODE_BSD`       |`UC_BSD` |Switch to BSD input (not implemented)                           |
|`QK_UNICODE_MODE_WINCOMPOSE`|`UC_WINC`|Switch to Windows input using WinCompose                        |
|`QK_UNICODE_MODE_EMACS`     |`UC_EMAC`|Switch to emacs (`C-x-8 RET`)                                   |

## API :id=api

### `uint8_t get_unicode_input_mode(void)` :id=api-get-unicode-input-mode

Get the current Unicode input mode.

#### Return Value :id=api-get-unicode-input-mode-return-value

The currently active Unicode input mode.

---

### `void set_unicode_input_mode(uint8_t mode)` :id=api-set-unicode-input-mode

Set the Unicode input mode.

#### Arguments :id=api-set-unicode-input-mode-arguments

 - `uint8_t mode`  
   The input mode to set.

---

### `void unicode_input_mode_step(void)` : id=api-unicode-input-mode-step

Change to the next Unicode input mode.

---

### `void unicode_input_mode_step_reverse(void)` : id=api-unicode-input-mode-step-reverse

Change to the previous Unicode input mode.

---

### `void unicode_input_mode_set_user(uint8_t input_mode)` :id=api-unicode-input-mode-set-user

User-level callback, invoked when the input mode is changed.

#### Arguments :id=api-unicode-input-mode-set-user-arguments

 - `uint8_t input_mode`  
   The new input mode.

---

### `void unicode_input_mode_set_kb(uint8_t input_mode)` :id=api-unicode-input-mode-set-kb

Keyboard-level callback, invoked when the input mode is changed.

#### Arguments :id=api-unicode-input-mode-set-kb-arguments

 - `uint8_t input_mode`  
   The new input mode.

---

### `void unicode_input_start(void)` :id=api-unicode-input-start

Begin the Unicode input sequence. The exact behavior depends on the currently selected input mode:

 - **macOS**: Hold `UNICODE_KEY_MAC`
 - **Linux**: Tap `UNICODE_KEY_LNX`
 - **WinCompose**: Tap `UNICODE_KEY_WINC`, then U
 - **HexNumpad**: Hold Left Alt, then tap Numpad +
 - **Emacs**: Tap Ctrl+X, then 8, then Enter

This function is weakly defined, and can be overridden in user code.

---

### `void unicode_input_finish(void)` :id=api-unicode-input-finish

Complete the Unicode input sequence. The exact behavior depends on the currently selected input mode:

 - **macOS**: Release `UNICODE_KEY_MAC`
 - **Linux**: Tap Space
 - **WinCompose**: Tap Enter
 - **HexNumpad**: Release Left Alt
 - **Emacs**: Tap Enter

This function is weakly defined, and can be overridden in user code.

---

### `void unicode_input_cancel(void)` :id=api-unicode-input-cancel

Cancel the Unicode input sequence. The exact behavior depends on the currently selected input mode:

 - **macOS**: Release `UNICODE_KEY_MAC`
 - **Linux**: Tap Escape
 - **WinCompose**: Tap Escape
 - **HexNumpad**: Release Left Alt
 - **Emacs**: Tap Ctrl+G

This function is weakly defined, and can be overridden in user code.

---

### `void register_unicode(uint32_t code_point)` :id=api-register-unicode

Input a single Unicode character. A surrogate pair will be sent if required by the input mode.

#### Arguments :id=api-register-unicode-arguments

 - `uint32_t code_point`  
   The code point of the character to send.

---

### `void send_unicode_string(const char *str)` :id=api-send-unicode-string

Send a string containing Unicode characters.

#### Arguments :id=api-send-unicode-string-arguments

 - `const char *str`  
   The string to send.

---

### `uint8_t unicodemap_index(uint16_t keycode)` :id=api-unicodemap-index

Get the index into the `unicode_map` array for the given keycode, respecting shift state for pair keycodes.

#### Arguments :id=api-unicodemap-index-arguments

 - `uint16_t keycode`  
   The Unicode Map keycode to get the index of.

#### Return Value :id=api-unicodemap-index-return-value

An index into the `unicode_map` array.

---

### `uint32_t unicodemap_get_code_point(uint8_t index)` :id=api-unicodemap-get-code-point

Get the code point for the given index in the `unicode_map` array.

#### Arguments :id=unicodemap-get-code-point-arguments

 - `uint8_t index`  
   The index into  the `unicode_map` array.

#### Return Value :id=unicodemap-get-code-point-return-value

A Unicode code point value.

---

### `void register_unicodemap(uint8_t index)` :id=api-register-unicodemap

Send the code point for the given index in the `unicode_map` array.

#### Arguments :id=api-register-unicodemap-arguments

 - `uint8_t index`  
   The index into the `unicode_map` array.

---

### `void ucis_start(void)` :id=api-ucis-start

Begin the input sequence.

---

### `bool ucis_active(void)` :id=api-ucis-active

Whether UCIS is currently active.

#### Return Value :id=api-ucis-active-return-value

`true` if UCIS is active.

---

### `uint8_t ucis_count(void)` :id=api-ucis-count

Get the number of characters in the input sequence buffer.

#### Return Value :id=api-ucis-count-return-value

The current input sequence buffer length.

---

### `bool ucis_add(uint16_t keycode)` :id=api-ucis-add

Add the given keycode to the input sequence buffer.

#### Arguments :id=api-ucis-add-arguments

 - `uint16_t keycode`  
   The keycode to add. Must be between `KC_A` and `KC_Z`, or `KC_1` and `KC_0`.

#### Return Value :id=api-ucis-add-return-value

`true` if the keycode was added.

---

### `bool ucis_remove_last(void)` :id=api-ucis-remove-last

Remove the last character from the input sequence buffer.

#### Return Value :id=api-ucis-remove-last

`true` if the sequence was not empty.

---

### `void ucis_finish(void)` :id=api-ucis-finish

Mark the input sequence as complete, and attempt to match.

---

### `void ucis_cancel(void)` :id=api-ucis-cancel

Cancel the input sequence.

---

### `void register_ucis(void)` :id=api-register-ucis

Send the code point(s) for the given UCIS index.

#### Arguments :id=api-register-ucis-arguments

 - `uint8_t index`  
   The index into the UCIS symbol table.
