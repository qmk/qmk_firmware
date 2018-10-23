# Unicode Support

There are three Unicode keymap definition method available in QMK:

## UNICODE_ENABLE

Supports Unicode input up to 0xFFFF. The keycode function is `UC(n)` in keymap file, where *n* is a 4 digit hexadecimal.

## UNICODEMAP_ENABLE

Supports Unicode up to 0xFFFFFFFF. You need to maintain a separate mapping table `const uint32_t PROGMEM unicode_map[] = {...}` in your keymap file. The keycode function is `X(n)` where *n* is the array index of the mapping table.

And you may want to have an enum to make reference easier.  So you'd want to add something like this to your keymap:

```c
enum unicode_name {
  BANG, // ‽
  IRONY, // ⸮
  SNEK // snke 🐍
};

const uint32_t PROGMEM unicode_map[] = {
  [BANG]      = 0x0203D, // ‽
  [IRONY]     = 0x02E2E, // ⸮
  [SNEK]      = 0x1F40D // snke 🐍
}:
```

Make sure that the order for both matches.

## UCIS_ENABLE

Supports Unicode up to 0xFFFFFFFF. As with `UNICODE_MAP`, you may want to main a mapping table in your keymap file.  However, there is no keycodes for this feature, you will have to add a keycode or function to call `qk_ucis_start()`. Once you've run that, you can just type the text for your unicode, and then hit space or enter to complete it, or ESC to cancel it. And if it matches an entry in your table, it will automatically "backspace" the trigger word (from your table) and then will input the unicode sequence.

For instance, you would need to have a table like this in your keymap:

```c
const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE
(
 UCIS_SYM("poop", 0x1f4a9),
 UCIS_SYM("rofl", 0x1f923),
 UCIS_SYM("kiss", 0x1f619)
);
```

You run the function, and then type "rofl" and hit enter, it should backspace remove "rofl" and input the `0x1f923` unicode.

### Customization

There are several functions that you can add to your keymap to customize the functionality of this feature.

* `void qk_ucis_start_user(void)` - This runs when you run the "start" function, and can be used to provide feedback. By default, it types out a keyboard emoji.
* `void qk_ucis_success(uint8_t symbol_index)` - This runs when the unicode input has matched something, and has completed. Default doesn't do anything.
* `void qk_ucis_symbol_fallback (void)` - This runs if the input text doesn't match anything.  The default function falls back to trying that input as a unicode code.

The default code for these are:

```c
void qk_ucis_start_user(void) { // outputs keyboard emoji
  unicode_input_start();
  register_hex(0x2328);
  unicode_input_finish();
}

void qk_ucis_success(uint8_t symbol_index) {
}

void qk_ucis_symbol_fallback (void) { // falls back to manual unicode entry
  for (uint8_t i = 0; i < qk_ucis_state.count - 1; i++) {
    uint8_t code = qk_ucis_state.codes[i];
    register_code(code);
    unregister_code(code);
    wait_ms(UNICODE_TYPE_DELAY);
  }
}
```

## Input Modes

Unicode input in QMK works by inputting a sequence of characters to the OS, sort of like a macro. Unfortunately, the way this is done differs for each OS, so a corresponding input mode has to be set.

The following input modes are available:

* **`UC_OSX`**: Mac OS X built-in Unicode hex input. Works up to 0xFFFF. To enable, go to _System Preferences > Keyboard > Input Sources_, add _Unicode Hex Input_ to the list (it's under _Other_), then activate it from the input dropdown in the Menu Bar. By default, this mode uses the left Option key (`KC_LALT`), but this can be changed by defining `UNICODE_OSX_KEY` with another keycode.
* **`UC_LNX`**: Linux built-in IBus Unicode input. Works up to 0xFFFFF. Enabled by default and works almost anywhere on IBus-enabled distros. Without IBus, this mode works under GTK apps, but rarely anywhere else.
* **`UC_WIN`**: _(not recommended)_ Windows built-in Unicode hex numpad input. To enable, create a registry key under `HKEY_CURRENT_USER\Control Panel\Input Method\EnableHexNumpad` of type `REG_SZ` called `EnableHexNumpad`, set its value to `1`, and reboot. This mode is not recommended because of reliability and compatibility issue; use the `UC_WINC` mode instead.
* **`UC_WINC`**: Windows Unicode input using [WinCompose](https://github.com/samhocevar/wincompose). Works reliably under all version of Windows supported by the app. To enable, install [WinCompose](https://github.com/samhocevar/wincompose/releases/latest) (it will run automatically on startup). By default, this mode uses the right Alt key (`KC_RALT`), but this can be changed in the WinCompose settings and by defining `UNICODE_WINC_KEY` with another keycode.

At some point you need to call `set_unicode_input_mode(X)` in your code to set the appropriate mode. Since the setting is stored in EEPROM, this only needs to be called once, so it's recommended that you do it in `matrix_init_user` (or a similar function). For example:

```c
void matrix_init_user(void) {
  set_unicode_input_mode(UC_LNX);
}
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
