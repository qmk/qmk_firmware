# Unicode Support

There are three Unicode keymap definition method available in QMK:

## UNICODE_ENABLE

Supports Unicode input up to 0xFFFF. The keycode function is `UC(n)` in
keymap file, where *n* is a 4 digit hexadecimal.

## UNICODEMAP_ENABLE

Supports Unicode up to 0xFFFFFFFF. You need to maintain a separate mapping
table `const uint32_t PROGMEM unicode_map[] = {...}` in your keymap file.
The keycode function is `X(n)` where *n* is the array index of the mapping
table.

## UCIS_ENABLE

TBD

Unicode input in QMK works by inputing a sequence of characters to the OS,
sort of like macro. Unfortunately, each OS has different ideas on how Unicode is inputted.

This is the current list of Unicode input method in QMK:

* UC_OSX: MacOS Unicode Hex Input support. Works only up to 0xFFFF. Disabled by default. To enable: go to System Preferences -> Keyboard -> Input Sources, and enable Unicode Hex.
* UC_OSX_RALT: Same as UC_OSX, but sends the Right Alt key for unicode input
* UC_LNX: Unicode input method under Linux. Works up to 0xFFFFF. Should work almost anywhere on ibus enabled distros. Without ibus, this works under GTK apps, but rarely anywhere else.
* UC_WIN: (not recommended) Windows built-in Unicode input. To enable: create registry key under `HKEY_CURRENT_USER\Control Panel\Input Method\EnableHexNumpad` of type `REG_SZ` called `EnableHexNumpad`, set its value to 1, and reboot. This method is not recommended because of reliability and compatibility issue, use WinCompose method below instead.
* UC_WINC: Windows Unicode input using WinCompose. Requires [WinCompose](https://github.com/samhocevar/wincompose). Works reliably under many (all?) variations of Windows.

# Additional Language Support

In `quantum/keymap_extras/`, you'll see various language files - these work the same way as the alternative layout ones do. Most are defined by their two letter country/language code followed by an underscore and a 4-letter abbreviation of its name. `FR_UGRV` which will result in a `ù` when using a software-implemented AZERTY layout. It's currently difficult to send such characters in just the firmware.

# International Characters on Windows

[AutoHotkey](https://autohotkey.com) allows Windows users to create custom hotkeys among others.

The method does not require Unicode support in the keyboard itself but depends instead of AutoHotkey running in the background.

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
