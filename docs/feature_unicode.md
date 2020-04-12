# Unicode Support

Unicode characters can be input straight from your keyboard! There are some limitations, however.

In order to enable Unicode support on your keyboard, you will need to do the following:

1. Choose one of three supported Unicode implementations: [Basic](#basic-unicode), [Unicode Map](#unicode-map), [UCIS](#ucis).
2. Find which [input mode](#input-modes) is the best match for your operating system and setup.
3. [Set](#setting-the-input-mode) the appropriate input mode (or modes) in your configuration.
4. Add Unicode keycodes to your keymap.


## 1. Methods :id=methods

QMK supports three different methods for enabling Unicode input and adding Unicode characters to your keymap. Each has its pros and cons in terms of flexibility and ease of use. Choose the one that best fits your use case.

The Basic method should be enough for most users. However, if you need a wider range of supported characters (including emoji, rare symbols etc.), you should use Unicode Map.

<br>

### 1.1. Basic Unicode :id=basic-unicode

The easiest to use method, albeit somewhat limited. It stores Unicode characters as keycodes in the keymap itself, so it only supports code points up to `0x7FFF`. This covers characters for most modern languages (including East Asian), as well as symbols, but it doesn't cover emoji.

Add the following to your `rules.mk`:

```make
UNICODE_ENABLE = yes
```

Then add `UC(c)` keycodes to your keymap, where _c_ is the code point of the desired character (preferably in hexadecimal, up to 4 digits long). For example, `UC(0x40B)` will output [Ћ](https://unicode-table.com/en/040B/), and `UC(0x30C4)` will output [ツ](https://unicode-table.com/en/30C4).

<br>

### 1.2. Unicode Map :id=unicode-map

In addition to standard character ranges, this method also covers emoji, ancient scripts, rare symbols etc. In fact, all possible code points (up to `0x10FFFF`) are supported. Here, Unicode characters are stored in a separate mapping table. You need to maintain a `unicode_map` array in your keymap file, which may contain at most 16384 entries.

Add the following to your `rules.mk`:

```make
UNICODEMAP_ENABLE = yes
```

Then add `X(i)` keycodes to your keymap, where _i_ is the desired character's index in the mapping table. This can be a numeric value, but it's recommended to keep the indices in an enum and access them by name.

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

Then you can use `X(BANG)`, `X(SNEK)` etc. in your keymap.

#### Lower and Upper Case

Characters often come in lower and upper case pairs, such as å and Å. To make inputting these characters easier, you can use `XP(i, j)` in your keymap, where _i_ and _j_ are the mapping table indices of the lower and upper case character, respectively. If you're holding down Shift or have Caps Lock turned on when you press the key, the second (upper case) character will be inserted; otherwise, the first (lower case) version will appear.

This is most useful when creating a keymap for an international layout with special characters. Instead of having to put the lower and upper case versions of a character on separate keys, you can have them both on the same key by using `XP()`. This helps blend Unicode keys in with regular alphas.

Due to keycode size constraints, _i_ and _j_ can each only refer to one of the first 128 characters in your `unicode_map`. In other words, 0 ≤ _i_ ≤ 127 and 0 ≤ _j_ ≤ 127. This is enough for most use cases, but if you'd like to customize the index calculation, you can override the [`unicodemap_index()`](https://github.com/qmk/qmk_firmware/blob/71f640d47ee12c862c798e1f56392853c7b1c1a8/quantum/process_keycode/process_unicodemap.c#L36) function. This also allows you to, say, check Ctrl instead of Shift/Caps.

<br>

### 1.3. UCIS :id=ucis

This method also supports all possible code points. As with the Unicode Map method, you need to maintain a mapping table in your keymap file. However, there are no built-in keycodes for this feature — you have to create a custom keycode or function that invokes this functionality.

Add the following to your `rules.mk`:

```make
UCIS_ENABLE = yes
```

Then define a table like this in your keymap file:

```c
const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("poop", 0x1F4A9), // 💩
    UCIS_SYM("rofl", 0x1F923), // 🤣
    UCIS_SYM("kiss", 0x1F619)  // 😙
);
```

To use it, call `qk_ucis_start()`. Then, type the mnemonic for the character (such as "rofl"), and hit Space or Enter. QMK should erase the "rofl" text and insert the laughing emoji.

#### Customization

There are several functions that you can define in your keymap to customize the functionality of this feature.

* `void qk_ucis_start_user(void)` – This runs when you call the "start" function, and can be used to provide feedback. By default, it types out a keyboard emoji.
* `void qk_ucis_success(uint8_t symbol_index)` – This runs when the input has matched something and has completed. By default, it doesn't do anything.
* `void qk_ucis_symbol_fallback (void)` – This runs when the input doesn't match anything. By default, it falls back to trying that input as a Unicode code.

You can find the default implementations of these functions in [`process_ucis.c`](https://github.com/qmk/qmk_firmware/blob/master/quantum/process_keycode/process_ucis.c).


## 2. Input Modes :id=input-modes

Unicode input in QMK works by inputting a sequence of characters to the OS, sort of like a macro. Unfortunately, the way this is done differs for each platform. Specifically, each platform requires a different combination of keys to trigger Unicode input. Therefore, a corresponding input mode has to be set in QMK.

The following input modes are available:

* **`UC_MAC`**: macOS built-in Unicode hex input. Supports code points up to `0xFFFF` (`0x10FFFF` with Unicode Map).

  To enable, go to _System Preferences > Keyboard > Input Sources_, add _Unicode Hex Input_ to the list (it's under _Other_), then activate it from the input dropdown in the Menu Bar.
  By default, this mode uses the left Option key (`KC_LALT`) for Unicode input, but this can be changed by defining [`UNICODE_KEY_MAC`](#input-key-configuration) with another keycode.

  !> Using the _Unicode Hex Input_ input source may disable some Option-based shortcuts, such as Option+Left and Option+Right.

  !> `UC_OSX` is a deprecated alias of `UC_MAC` that will be removed in future versions of QMK. All new keymaps should use `UC_MAC`.

* **`UC_LNX`**: Linux built-in IBus Unicode input. Supports code points up to `0x10FFFF` (all possible code points).

  Enabled by default and works almost anywhere on IBus-enabled distros. Without IBus, this mode works under GTK apps, but rarely anywhere else.
  By default, this mode uses Ctrl+Shift+U (`LCTL(LSFT(KC_U))`) to start Unicode input, but this can be changed by defining [`UNICODE_KEY_LNX`](#input-key-configuration) with another keycode. This might be required for IBus versions ≥1.5.15, where Ctrl+Shift+U behavior is consolidated into Ctrl+Shift+E.

* **`UC_WIN`**: _(not recommended)_ Windows built-in hex numpad Unicode input. Supports code points up to `0xFFFF`.

  To enable, create a registry key under `HKEY_CURRENT_USER\Control Panel\Input Method` of type `REG_SZ` called `EnableHexNumpad` and set its value to `1`. This can be done from the Command Prompt by running `reg add "HKCU\Control Panel\Input Method" -v EnableHexNumpad -t REG_SZ -d 1` with administrator privileges. Reboot afterwards.
  This mode is not recommended because of reliability and compatibility issues; use the `UC_WINC` mode instead.

* **`UC_BSD`**: _(non implemented)_ Unicode input under BSD. Not implemented at this time. If you're a BSD user and want to help add support for it, please [open an issue on GitHub](https://github.com/qmk/qmk_firmware/issues).

* **`UC_WINC`**: Windows Unicode input using [WinCompose](https://github.com/samhocevar/wincompose). As of v0.9.0, supports code points up to `0x10FFFF` (all possible code points).

  To enable, install the [latest release](https://github.com/samhocevar/wincompose/releases/latest). Once installed, WinCompose will automatically run on startup. Works reliably under all version of Windows supported by the app.
  By default, this mode uses right Alt (`KC_RALT`) as the Compose key, but this can be changed in the WinCompose settings and by defining [`UNICODE_KEY_WINC`](#input-key-configuration) with another keycode.


## 3. Setting the Input Mode :id=setting-the-input-mode

To set your desired input mode, add the following define to your `config.h`:

```c
#define UNICODE_SELECTED_MODES UC_LNX
```

This example sets the board's default input mode to `UC_LNX`. You can replace this with `UC_MAC` or any of the other modes listed [above](#input-modes). The board will automatically use the selected mode on startup, unless you manually switch to another mode (see [below](#keycodes)).

You can also select multiple input modes, which allows you to easily cycle through them using the `UC_MOD`/`UC_RMOD` keycodes.

```c
#define UNICODE_SELECTED_MODES UC_MAC, UC_LNX, UC_WINC
```

Note that the values are separated by commas. The board will remember the last used input mode and will continue using it on next power-up. You can disable this and force it to always start with the first mode in the list by adding `#define UNICODE_CYCLE_PERSIST false` to your `config.h`.

#### Keycodes

You can switch the input mode at any time by using the following keycodes. Adding these to your keymap allows you to quickly switch to a specific input mode, including modes not listed in `UNICODE_SELECTED_MODES`.

|Keycode               |Alias    |Input Mode  |Description                                                                  |
|----------------------|---------|------------|-----------------------------------------------------------------------------|
|`UNICODE_MODE_FORWARD`|`UC_MOD` |Next in list|Cycle through selected modes, reverse direction when Shift is held           |
|`UNICODE_MODE_REVERSE`|`UC_RMOD`|Prev in list|Cycle through selected modes in reverse, forward direction when Shift is held|
|`UNICODE_MODE_MAC`    |`UC_M_MA`|`UC_MAC`    |Switch to macOS input                                                        |
|`UNICODE_MODE_LNX`    |`UC_M_LN`|`UC_LNX`    |Switch to Linux input                                                        |
|`UNICODE_MODE_WIN`    |`UC_M_WI`|`UC_WIN`    |Switch to Windows input                                                      |
|`UNICODE_MODE_BSD`    |`UC_M_BS`|`UC_BSD`    |Switch to BSD input _(not implemented)_                                      |
|`UNICODE_MODE_WINC`   |`UC_M_WC`|`UC_WINC`   |Switch to Windows input using WinCompose                                     |

You can also switch the input mode by calling `set_unicode_input_mode(x)` in your code, where _x_ is one of the above input mode constants (e.g. `UC_LNX`).

?> Using `UNICODE_SELECTED_MODES` is preferred to calling `set_unicode_input_mode()` in `matrix_init_user()` or similar functions, since it's better integrated into the Unicode system and has the added benefit of avoiding unnecessary writes to EEPROM.

#### Audio Feedback

If you have the [Audio feature](feature_audio.md) enabled on the board, you can set melodies to be played when you press the above keys. That way you can have some audio feedback when switching input modes.

For instance, you can add these definitions to your `config.h` file:

```c
#define UNICODE_SONG_MAC  AUDIO_ON_SOUND
#define UNICODE_SONG_LNX  UNICODE_LINUX
#define UNICODE_SONG_BSD  TERMINAL_SOUND
#define UNICODE_SONG_WIN  UNICODE_WINDOWS
#define UNICODE_SONG_WINC UNICODE_WINDOWS
```


## Additional Customization

Because Unicode is a large and versatile feature, there are a number of options you can customize to make it work better on your system.

### Start and Finish Input Functions

The functions for starting and finishing Unicode input on your platform can be overridden locally. Possible uses include customizing input mode behavior if you don't use the default keys, or adding extra visual/audio feedback to Unicode input.

* `void unicode_input_start(void)` – This sends the initial sequence that tells your platform to enter Unicode input mode. For example, it holds the left Alt key followed by Num+ on Windows, and presses the `UNICODE_KEY_LNX` combination (default: Ctrl+Shift+U) on Linux.
* `void unicode_input_finish(void)` – This is called to exit Unicode input mode, for example by pressing Space or releasing the Alt key.

You can find the default implementations of these functions in [`process_unicode_common.c`](https://github.com/qmk/qmk_firmware/blob/master/quantum/process_keycode/process_unicode_common.c).

### Input Key Configuration

You can customize the keys used to trigger Unicode input for macOS, Linux and WinCompose by adding corresponding defines to your `config.h`. The default values match the platforms' default settings, so you shouldn't need to change this unless Unicode input isn't working, or you want to use a different key (e.g. in order to free up left or right Alt).

|Define            |Type      |Default           |Example                                    |
|------------------|----------|------------------|-------------------------------------------|
|`UNICODE_KEY_MAC` |`uint8_t` |`KC_LALT`         |`#define UNICODE_KEY_MAC  KC_RALT`         |
|`UNICODE_KEY_LNX` |`uint16_t`|`LCTL(LSFT(KC_U))`|`#define UNICODE_KEY_LNX  LCTL(LSFT(KC_E))`|
|`UNICODE_KEY_WINC`|`uint8_t` |`KC_RALT`         |`#define UNICODE_KEY_WINC KC_RGUI`         |


## Sending Unicode Strings

QMK provides several functions that allow you to send Unicode input to the host programmatically:

### `send_unicode_string()`

This function is much like `send_string()`, but it allows you to input UTF-8 characters directly. It supports all code points, provided the selected input mode also supports it. Make sure your `keymap.c` file is formatted using UTF-8 encoding.

```c
send_unicode_string("(ノಠ痊ಠ)ノ彡┻━┻");
```

Example uses include sending Unicode strings when a key is pressed, as described in [Macros](feature_macros.md).

### `send_unicode_hex_string()`

Similar to `send_unicode_string()`, but the characters are represented by their Unicode code points, written in hexadecimal and separated by spaces. For example, the table flip above would be achieved with:

```c
send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
```

An easy way to convert your Unicode string to this format is to use [this site](https://r12a.github.io/app-conversion/) and take the result in the "Hex/UTF-32" section.


## Additional Language Support

In `quantum/keymap_extras`, you'll see various language files — these work the same way as the ones for alternative layouts such as Colemak or BÉPO. When you include one of these language headers, you gain access to keycodes specific to that language / national layout. Such keycodes are defined by a 2-letter country/language code, followed by an underscore and a 4-letter abbreviation of the character to which the key corresponds. For example, including `keymap_french.h` and using `FR_UGRV` in your keymap will output `ù` when typed on a system with a native French AZERTY layout.

If the primary system layout you use on your machine is different from US ANSI, using these language-specific keycodes can help your QMK keymaps better match what will actually be output on the screen. However, keep in mind that these keycodes are just aliases for the corresponding default US keycodes under the hood, and that the HID protocol used by keyboards is itself inherently based on US ANSI.


## International Characters on Windows

### AutoHotkey

The method does not require Unicode support in the keyboard itself but instead depends on [AutoHotkey](https://autohotkey.com) running in the background.

First you need to select a modifier combination that is not in use by any of your programs.
Ctrl+Alt+Win is not used very widely and should therefore be perfect for this.
There is a macro defined for a mod-tab combo `LCAG_T`.
Add this mod-tab combo to a key on your keyboard, e.g.: `LCAG_T(KC_TAB)`.
This makes the key behave like a tab key if pressed and released immediately but changes it to the modifier if used with another key.

In the default script of AutoHotkey you can define custom hotkeys.

    <^<!<#a::Send, ä
    <^<!<#<+a::Send, Ä

The hotkeys above are for the combination CtrlAltGui and CtrlAltGuiShift plus the letter a.
AutoHotkey inserts the Text right of `Send, ` when this combination is pressed.

### US International

If you enable the US International layout on the system, it will use punctuation to accent the characters. For instance, typing "\`a" will result in à.
You can find details on how to enable this [here](https://support.microsoft.com/en-us/help/17424/windows-change-keyboard-layout).
