# Unicode Support

There are three Unicode keymap definition methods available in QMK:

## `UNICODE_ENABLE`

Supports Unicode up to `0x7FFF`. This covers characters for most modern languages, as well as symbols, but it doesn't cover emoji. The keycode function is `UC(c)` in the keymap file, where _c_ is the code point's number (preferably hexadecimal, up to 4 digits long). For example: `UC(0x45B)`, `UC(0x30C4)`.

## `UNICODEMAP_ENABLE`

Supports Unicode up to `0x10FFFF` (all possible code points). You need to maintain a separate mapping table `const uint32_t PROGMEM unicode_map[] = {...}` in your keymap file. The keycode function is `X(i)`, where _i_ is an array index into the mapping table. The table may contain at most 1024 entries.

You may want to have an enum to make referencing easier. So, you could add something like this to your keymap file:

```c
enum unicode_names {
  BANG,
  IRONY,
  SNEK,
};

const uint32_t PROGMEM unicode_map[] = {
  [BANG]  = 0x203D,  // ‽
  [IRONY] = 0x2E2E,  // ⸮
  [SNEK]  = 0x1F40D, // 🐍
};
```

Then you can use `X(BANG)` etc. in your keymap.

## `UCIS_ENABLE`

Supports Unicode up to `0x10FFFF` (all possible code points). As with `UNICODEMAP`, you need to maintain a mapping table in your keymap file. However, there are no built-in keycodes for this feature — you will have to add a keycode or function that calls `qk_ucis_start()`. Once this function's been called, you can type the corresponding mnemonic for your character, then hit Space or Enter to complete it, or Esc to cancel. If the mnemonic matches an entry in your table, the typed text will automatically be erased and the corresponding Unicode character inserted.

For instance, you would define a table like this in your keymap file:

```c
const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
  UCIS_SYM("poop", 0x1F4A9), // 💩
  UCIS_SYM("rofl", 0x1F923), // 🤣
  UCIS_SYM("kiss", 0x1F619)  // 😙
);
```

You call `qk_ucis_start()`, then type "rofl" and hit Enter. QMK should erase the "rofl" text and input the laughing emoji.

### Customization

There are several functions that you can define in your keymap to customize the functionality of this feature.

* `void qk_ucis_start_user(void)` – This runs when you call the "start" function, and can be used to provide feedback. By default, it types out a keyboard emoji.
* `void qk_ucis_success(uint8_t symbol_index)` – This runs when the input has matched something and has completed. By default, it doesn't do anything.
* `void qk_ucis_symbol_fallback (void)` – This runs when the input doesn't match anything. By default, it falls back to trying that input as a Unicode code.

You can find the default implementations of these functions in [`process_ucis.c`](https://github.com/qmk/qmk_firmware/blob/master/quantum/process_keycode/process_ucis.c).

## Input Modes

Unicode input in QMK works by inputting a sequence of characters to the OS, sort of like a macro. Unfortunately, the way this is done differs for each platform. Specifically, each platform requires a different combination of keys to trigger Unicode input. Therefore, a corresponding input mode has to be set in QMK.

The following input modes are available:

* **`UC_OSX`**: Mac OS X built-in Unicode hex input. Supports code points up to `0xFFFF` (`0x10FFFF` with `UNICODEMAP`).

  To enable, go to _System Preferences > Keyboard > Input Sources_, add _Unicode Hex Input_ to the list (it's under _Other_), then activate it from the input dropdown in the Menu Bar.
  By default, this mode uses the left Option key (`KC_LALT`), but this can be changed by defining [`UNICODE_OSX_KEY`](#input-key-configuration) with another keycode.

* **`UC_LNX`**: Linux built-in IBus Unicode input. Supports code points up to `0x10FFFF` (all possible code points).

  Enabled by default and works almost anywhere on IBus-enabled distros. Without IBus, this mode works under GTK apps, but rarely anywhere else.

* **`UC_WIN`**: _(not recommended)_ Windows built-in hex numpad Unicode input. Supports code points up to `0xFFFF`.

  To enable, create a registry key under `HKEY_CURRENT_USER\Control Panel\Input Method\EnableHexNumpad` of type `REG_SZ` called `EnableHexNumpad` and set its value to `1`. This can be done from the Command Prompt by running `reg add "HKCU\Control Panel\Input Method" -v EnableHexNumpad -t REG_SZ -d 1` with administrator privileges. Afterwards, reboot.
  This mode is not recommended because of reliability and compatibility issues; use the `UC_WINC` mode instead.

* **`UC_BSD`**: _(non implemented)_ Unicode input under BSD. Not implemented at this time. If you're a BSD user and want to help add support for it, please [open an issue on GitHub](https://github.com/qmk/qmk_firmware/issues).

* **`UC_WINC`**: Windows Unicode input using [WinCompose](https://github.com/samhocevar/wincompose). As of v0.8.2, supports code points up to `0xFFFFF` (all currently assigned code points).

  To enable, install the [latest release](https://github.com/samhocevar/wincompose/releases/latest). Once installed, WinCompose will automatically run on startup. Works reliably under all version of Windows supported by the app.
  By default, this mode uses the right Alt key (`KC_RALT`), but this can be changed in the WinCompose settings and by defining [`UNICODE_WINC_KEY`](#input-key-configuration) with another keycode.

### Switching Input Modes

There are two ways to set the input mode for Unicode: by keycode or by function. Keep in mind that both methods write to persistent storage (EEPROM), and are loaded each time the keyboard starts. So once you've set it the first time, you don't need to set it again unless you want to change it, or you've reset the EEPROM settings.

You can switch the input mode at any time by using one of the following keycodes. The easiest way is to add the ones you use to your keymap.

|Keycode                |Alias    |Input mode   |Description                              |
|-----------------------|---------|-------------|-----------------------------------------|
|`UNICODE_MODE_FORWARD` |`UC_MOD` |             |Cycles forwards through the available modes. [(Disabled by default)](#input-method-cycling)|
|`UNICODE_MODE_REVERSE` |`UC_RMOD`|             |Cycles forwards through the available modes. [(Disabled by default)](#input-method-cycling)|
|`UNICODE_MODE_OSX`     |`UC_M_OS`|`UC_OSX`     |Switch to Mac OS X input.                |
|`UNICODE_MODE_LNX`     |`UC_M_LN`|`UC_LNX`     |Switch to Linux input.                   |
|`UNICODE_MODE_WIN`     |`UC_M_WI`|`UC_WIN`     |Switch to Windows input.                 |
|`UNICODE_MODE_BSD`     |`UC_M_BS`|`UC_BSD`     |Switch to BSD input (not implemented).   |
|`UNICODE_MODE_WINC`    |`UC_M_WC`|`UC_WINC`    |Switch to Windows input using WinCompose.|

You can also switch the input mode by calling `set_unicode_input_mode(x)` in your code, where _x_ is one of the above input mode constants (e.g. `UC_LNX`). Since the function only needs to be called once, it's recommended that you do it in `eeconfig_init_user` (or a similar function). For example:

```c
void eeconfig_init_user(void) {
  set_unicode_input_mode(UC_LNX);
}
```

### Audio Feedback

If you have the [Audio feature](feature_audio.md) enabled on the board, you can set melodies to be played when you press the above keys. That way you can have some audio feedback when switching input modes.

For instance, you can add these definitions to your `config.h` file:

```c
#define UNICODE_SONG_OSX  COIN_SOUND
#define UNICODE_SONG_LNX  UNICODE_LINUX
#define UNICODE_SONG_BSD  MARIO_GAMEOVER
#define UNICODE_SONG_WIN  UNICODE_WINDOWS
#define UNICODE_SONG_WINC UNICODE_WINDOWS
```

### Additional Customization

Because Unicode is such a large and variable feature, there are a number of options that you can customize to work better on your system. 

#### Start and Finish input functions

The functions for starting and finishing Unicode input on your platform can be overridden locally. Possible uses include customizing input mode behavior if you don't use the default keys, or adding extra visual/audio feedback to Unicode input.

* `void unicode_input_start(void)` – This sends the initial sequence that tells your platform to enter Unicode input mode. For example, it presses Ctrl+Shift+U on Linux and holds the Option key on Mac.
* `void unicode_input_finish(void)` – This is called to exit Unicode input mode, for example by pressing Space or releasing the Option key.

You can find the default implementations of these functions in [`process_unicode_common.c`](https://github.com/qmk/qmk_firmware/blob/master/quantum/process_keycode/process_unicode_common.c).


#### Input Key Configuration

Additionally, you can customize the keys used to trigger the unicode input for macOS and WinCompose by adding defines to your `config.h`

```c
#define UNICODE_OSX_KEY  KC_LALT
#define UNICODE_WINC_KEY KC_RALT
```

#### Input Method Cycling

Also, you can choose which input methods are availble for cycling through.  By default, this is disabled. But if you want to enabled it, then limiting it to just those modes makes sense.  Note that `UNICODE_SELECTED_MODES` define is comma delimited.

```c
#define UNICODE_SELECTED_MODES UC_OSX, UC_LNX, UC_WIN, UC_BSD, UC_WINC
```

## `send_unicode_hex_string`

To type multiple characters for things like (ノಠ痊ಠ)ノ彡┻━┻, you can use `send_unicode_hex_string()` much like `SEND_STRING()` except you would use hex values separate by spaces.
For example, the table flip seen above would be `send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B")`

There are many ways to get a hex code, but an easy one is [this site](https://r12a.github.io/app-conversion/). Just make sure to convert to hexadecimal, and that is your string.

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

For instance, typing "`a" will result in à.

You can find details on how to enable this [here](https://support.microsoft.com/en-us/help/17424/windows-change-keyboard-layout).
