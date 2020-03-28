# Unicode Support

Unicode characters can be input straight from your keyboard! There are some limitations, however.

QMK has three different methods for enabling Unicode input and defining keycodes:

## Basic Unicode

This method supports Unicode code points up to `0x7FFF`. This covers characters for most modern languages, as well as symbols, but it doesn't cover emoji.

Add the following to your `rules.mk`:

```make
UNICODE_ENABLE = yes
```

Then add `UC(c)` keycodes to your keymap, where _c_ is the code point (preferably in hexadecimal, up to 4 digits long). For example: `UC(0x45B)`, `UC(0x30C4)`.

## Unicode Map

This method supports all possible code points (up to `0x10FFFF`); however, you need to maintain a separate mapping table in your keymap file, which may contain at most 16384 entries.

Add the following to your `rules.mk`:

```make
UNICODEMAP_ENABLE = yes
```

Then add `X(i)` keycodes to your keymap, where _i_ is an array index into the mapping table:

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

### Lower and Upper Case

Characters often come in lower and upper case pairs, such as å and Å. To make inputting these characters easier, you can use `XP(i, j)` in your keymap, where _i_ and _j_ are the mapping table indices of the lower and upper case character, respectively. If you're holding down Shift or have Caps Lock turned on when you press the key, the second (upper case) character will be inserted; otherwise, the first (lower case) version will appear.

This is most useful when creating a keymap for an international layout with special characters. Instead of having to put the lower and upper case versions of a character on separate keys, you can have them both on the same key by using `XP()`. This helps blend Unicode keys in with regular alphas.

Due to keycode size constraints, _i_ and _j_ can each only refer to one of the first 128 characters in your `unicode_map`. In other words, 0 ≤ _i_ ≤ 127 and 0 ≤ _j_ ≤ 127. This is enough for most use cases, but if you'd like to customize the index calculation, you can override the [`unicodemap_index()`](https://github.com/qmk/qmk_firmware/blob/71f640d47ee12c862c798e1f56392853c7b1c1a8/quantum/process_keycode/process_unicodemap.c#L40) function. This also allows you to, say, check Ctrl instead of Shift/Caps.

## UCIS

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

### Customization

There are several functions that you can define in your keymap to customize the functionality of this feature.

* `void qk_ucis_start_user(void)` – This runs when you call the "start" function, and can be used to provide feedback. By default, it types out a keyboard emoji.
* `void qk_ucis_success(uint8_t symbol_index)` – This runs when the input has matched something and has completed. By default, it doesn't do anything.
* `void qk_ucis_symbol_fallback (void)` – This runs when the input doesn't match anything. By default, it falls back to trying that input as a Unicode code.

You can find the default implementations of these functions in [`process_ucis.c`](https://github.com/qmk/qmk_firmware/blob/master/quantum/process_keycode/process_ucis.c).

## Input Modes

Unicode input in QMK works by inputting a sequence of characters to the OS, sort of like a macro. Unfortunately, the way this is done differs for each platform. Specifically, each platform requires a different combination of keys to trigger Unicode input. Therefore, a corresponding input mode has to be set in QMK.

The following input modes are available:

* **`UC_MAC`**: macOS built-in Unicode hex input. Supports code points up to `0xFFFF` (`0x10FFFF` with Unicode Map).

  To enable, go to _System Preferences > Keyboard > Input Sources_, add _Unicode Hex Input_ to the list (it's under _Other_), then activate it from the input dropdown in the Menu Bar.
  By default, this mode uses the left Option key (`KC_LALT`) for Unicode input, but this can be changed by defining [`UNICODE_KEY_MAC`](#input-key-configuration) with another keycode.

  !> Using the _Unicode Hex Input_ input source may disable some Option based shortcuts, such as Option + Left Arrow and Option + Right Arrow.

  !> `UC_OSX` is a deprecated alias of `UC_MAC` that will be removed in a future version of QMK.

* **`UC_LNX`**: Linux built-in IBus Unicode input. Supports code points up to `0x10FFFF` (all possible code points).

  Enabled by default and works almost anywhere on IBus-enabled distros. Without IBus, this mode works under GTK apps, but rarely anywhere else.
  By default, this mode uses Ctrl+Shift+U (`LCTL(LSFT(KC_U))`) to start Unicode input, but this can be changed by defining [`UNICODE_KEY_LNX`](#input-key-configuration) with another keycode. This might be required for IBus versions ≥1.5.15, where Ctrl+Shift+U behavior is consolidated into Ctrl+Shift+E.

* **`UC_WIN`**: _(not recommended)_ Windows built-in hex numpad Unicode input. Supports code points up to `0xFFFF`.

  To enable, create a registry key under `HKEY_CURRENT_USER\Control Panel\Input Method\EnableHexNumpad` of type `REG_SZ` called `EnableHexNumpad` and set its value to `1`. This can be done from the Command Prompt by running `reg add "HKCU\Control Panel\Input Method" -v EnableHexNumpad -t REG_SZ -d 1` with administrator privileges. Reboot afterwards.
  This mode is not recommended because of reliability and compatibility issues; use the `UC_WINC` mode instead.

* **`UC_BSD`**: _(non implemented)_ Unicode input under BSD. Not implemented at this time. If you're a BSD user and want to help add support for it, please [open an issue on GitHub](https://github.com/qmk/qmk_firmware/issues).

* **`UC_WINC`**: Windows Unicode input using [WinCompose](https://github.com/samhocevar/wincompose). As of v0.9.0, supports code points up to `0x10FFFF` (all possible code points).

  To enable, install the [latest release](https://github.com/samhocevar/wincompose/releases/latest). Once installed, WinCompose will automatically run on startup. Works reliably under all version of Windows supported by the app.
  By default, this mode uses right Alt (`KC_RALT`) as the Compose key, but this can be changed in the WinCompose settings and by defining [`UNICODE_KEY_WINC`](#input-key-configuration) with another keycode.

### Switching Input Modes

There are two ways to set the input mode for Unicode: by keycode or by function. Keep in mind that both methods write to persistent storage (EEPROM), and are loaded each time the keyboard starts. So once you've set it the first time, you don't need to set it again unless you want to change it, or you've reset the EEPROM settings.

You can switch the input mode at any time by using one of the following keycodes. The easiest way is to add the ones you use to your keymap.

|Keycode               |Alias    |Input Mode  |Description                                                   |
|----------------------|---------|------------|--------------------------------------------------------------|
|`UNICODE_MODE_FORWARD`|`UC_MOD` |Next in list|[Cycle](#input-mode-cycling) through selected modes           |
|`UNICODE_MODE_REVERSE`|`UC_RMOD`|Prev in list|[Cycle](#input-mode-cycling) through selected modes in reverse|
|`UNICODE_MODE_MAC`    |`UC_M_MA`|`UC_MAC`    |Switch to macOS input                                         |
|`UNICODE_MODE_LNX`    |`UC_M_LN`|`UC_LNX`    |Switch to Linux input                                         |
|`UNICODE_MODE_WIN`    |`UC_M_WI`|`UC_WIN`    |Switch to Windows input                                       |
|`UNICODE_MODE_BSD`    |`UC_M_BS`|`UC_BSD`    |Switch to BSD input (not implemented)                         |
|`UNICODE_MODE_WINC`   |`UC_M_WC`|`UC_WINC`   |Switch to Windows input using WinCompose                      |

You can also switch the input mode by calling `set_unicode_input_mode(x)` in your code, where _x_ is one of the above input mode constants (e.g. `UC_LNX`). Since the function only needs to be called once, it's recommended that you do it in `eeconfig_init_user()` (or a similar function). For example:

```c
void eeconfig_init_user(void) {
    set_unicode_input_mode(UC_LNX);
}
```

### Audio Feedback

If you have the [Audio feature](feature_audio.md) enabled on the board, you can set melodies to be played when you press the above keys. That way you can have some audio feedback when switching input modes.

For instance, you can add these definitions to your `config.h` file:

```c
#define UNICODE_SONG_MAC  COIN_SOUND
#define UNICODE_SONG_LNX  UNICODE_LINUX
#define UNICODE_SONG_BSD  MARIO_GAMEOVER
#define UNICODE_SONG_WIN  UNICODE_WINDOWS
#define UNICODE_SONG_WINC UNICODE_WINDOWS
```

### Additional Customization

Because Unicode is a large and versatile feature, there are a number of options you can customize to make it work better on your system.

#### Start and Finish Input Functions

The functions for starting and finishing Unicode input on your platform can be overridden locally. Possible uses include customizing input mode behavior if you don't use the default keys, or adding extra visual/audio feedback to Unicode input.

* `void unicode_input_start(void)` – This sends the initial sequence that tells your platform to enter Unicode input mode. For example, it presses Ctrl+Shift+U on Linux and holds the Option key on macOS.
* `void unicode_input_finish(void)` – This is called to exit Unicode input mode, for example by pressing Space or releasing the Option key.

You can find the default implementations of these functions in [`process_unicode_common.c`](https://github.com/qmk/qmk_firmware/blob/master/quantum/process_keycode/process_unicode_common.c).

#### Input Key Configuration

You can customize the keys used to trigger Unicode input for macOS, Linux and WinCompose by adding corresponding defines to your `config.h`. The default values match the platforms' default settings, so you shouldn't need to change this unless Unicode input isn't working, or you want to use a different key (e.g. in order to free up left or right Alt).

|Define            |Type      |Default           |Example                                    |
|------------------|----------|------------------|-------------------------------------------|
|`UNICODE_KEY_MAC` |`uint8_t` |`KC_LALT`         |`#define UNICODE_KEY_MAC  KC_RALT`         |
|`UNICODE_KEY_LNX` |`uint16_t`|`LCTL(LSFT(KC_U))`|`#define UNICODE_KEY_LNX  LCTL(LSFT(KC_E))`|
|`UNICODE_KEY_WINC`|`uint8_t` |`KC_RALT`         |`#define UNICODE_KEY_WINC KC_RGUI`         |

#### Input Mode Cycling

You can choose which input modes are available for cycling through. By default, this is disabled. If you want to enable it, limiting it to just the modes you use makes sense. Note that the values in the list are comma-delimited.

```c
#define UNICODE_SELECTED_MODES UC_MAC, UC_LNX, UC_WIN, UC_WINC
```

You can cycle through the selected modes by using the `UC_MOD`/`UC_RMOD` keycodes, or by calling `cycle_unicode_input_mode(offset)` in your code (`offset` is how many modes to move forward by, so +1 corresponds to `UC_MOD`).

By default, when the keyboard boots, it will initialize the input mode to the last one you used. You can disable this and make it start with the first mode in the list every time by adding the following to your `config.h`:

```c
#define UNICODE_CYCLE_PERSIST false
```

!> Using `UNICODE_SELECTED_MODES` means you don't have to initially set the input mode in `matrix_init_user()` (or a similar function); the Unicode system will do that for you on startup. This has the added benefit of avoiding unnecessary writes to EEPROM.

## `send_unicode_string()`

This function is much like `send_string()` but allows you to input UTF-8 characters directly, and supports all code points (provided the selected input method also supports it). Make sure your `keymap.c` is formatted in UTF-8 encoding.

```c
send_unicode_string("(ノಠ痊ಠ)ノ彡┻━┻");
```

## `send_unicode_hex_string()`

Similar to `send_unicode_string()`, but the characters are represented by their code point values in ASCII, separated by spaces. For example, the table flip above would be achieved with:

```c
send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
```

An easy way to convert your Unicode string to this format is by using [this site](https://r12a.github.io/app-conversion/), and taking the result in the "Hex/UTF-32" section.

## Additional Language Support

In `quantum/keymap_extras/`, you'll see various language files - these work the same way as the alternative layout ones do. Most are defined by their two letter country/language code followed by an underscore and a 4-letter abbreviation of its name. `FR_UGRV` which will result in a `ù` when using a software-implemented AZERTY layout. It's currently difficult to send such characters in just the firmware.

## International Characters on Windows

### AutoHotkey allows Windows users to create custom hotkeys among others.

The method does not require Unicode support in the keyboard itself but depends instead of [AutoHotkey](https://autohotkey.com) running in the background.

First you need to select a modifier combination that is not in use by any of your programs.
CtrlAltWin is not used very widely and should therefore be perfect for this.
There is a macro defined for a mod-tab combo `LCAG_T`.
Add this mod-tab combo to a key on your keyboard, e.g.: `LCAG_T(KC_TAB)`.
This makes the key behave like a tab key if pressed and released immediately but changes it to the modifier if used with another key.

In the default script of AutoHotkey you can define custom hotkeys.

    <^<!<#a::Send, ä
    <^<!<#<+a::Send, Ä

The hotkeys above are for the combination CtrlAltGui and CtrlAltGuiShift plus the letter a.
AutoHotkey inserts the Text right of `Send, ` when this combination is pressed.

### US International

If you enable the US International layout on the system, it will use punctuation to accent the characters.

For instance, typing "\`a" will result in à.

You can find details on how to enable this [here](https://support.microsoft.com/en-us/help/17424/windows-change-keyboard-layout).
