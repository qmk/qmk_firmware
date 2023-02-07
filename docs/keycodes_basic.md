# Basic Keycodes

The basic set of keycodes are based on the [HID Keyboard/Keypad Usage Page (0x07)](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf) with the exception of `KC_NO`, `KC_TRNS` and keycodes in the `0xA5-DF` range. See below for more details.

## Letters and Numbers

|Key   |Description|
|------|-----------|
|`KC_A`|`a` and `A`|
|`KC_B`|`b` and `B`|
|`KC_C`|`c` and `C`|
|`KC_D`|`d` and `D`|
|`KC_E`|`e` and `E`|
|`KC_F`|`f` and `F`|
|`KC_G`|`g` and `G`|
|`KC_H`|`h` and `H`|
|`KC_I`|`i` and `I`|
|`KC_J`|`j` and `J`|
|`KC_K`|`k` and `K`|
|`KC_L`|`l` and `L`|
|`KC_M`|`m` and `M`|
|`KC_N`|`n` and `N`|
|`KC_O`|`o` and `O`|
|`KC_P`|`p` and `P`|
|`KC_Q`|`q` and `Q`|
|`KC_R`|`r` and `R`|
|`KC_S`|`s` and `S`|
|`KC_T`|`t` and `T`|
|`KC_U`|`u` and `U`|
|`KC_V`|`v` and `V`|
|`KC_W`|`w` and `W`|
|`KC_X`|`x` and `X`|
|`KC_Y`|`y` and `Y`|
|`KC_Z`|`z` and `Z`|
|`KC_1`|`1` and `!`|
|`KC_2`|`2` and `@`|
|`KC_3`|`3` and `#`|
|`KC_4`|`4` and `$`|
|`KC_5`|`5` and `%`|
|`KC_6`|`6` and `^`|
|`KC_7`|`7` and `&`|
|`KC_8`|`8` and `*`|
|`KC_9`|`9` and `(`|
|`KC_0`|`0` and `)`|

## F Keys

|Key     |Description|
|--------|-----------|
|`KC_F1` |F1         |
|`KC_F2` |F2         |
|`KC_F3` |F3         |
|`KC_F4` |F4         |
|`KC_F5` |F5         |
|`KC_F6` |F6         |
|`KC_F7` |F7         |
|`KC_F8` |F8         |
|`KC_F9` |F9         |
|`KC_F10`|F10        |
|`KC_F11`|F11        |
|`KC_F12`|F12        |
|`KC_F13`|F13        |
|`KC_F14`|F14        |
|`KC_F15`|F15        |
|`KC_F16`|F16        |
|`KC_F17`|F17        |
|`KC_F18`|F18        |
|`KC_F19`|F19        |
|`KC_F20`|F20        |
|`KC_F21`|F21        |
|`KC_F22`|F22        |
|`KC_F23`|F23        |
|`KC_F24`|F24        |

## Punctuation

|Key                 |Aliases  |Description               |
|--------------------|---------|--------------------------|
|`KC_ENTER`          |`KC_ENT` |Return (Enter)            |
|`KC_ESCAPE`         |`KC_ESC` |Escape                    |
|`KC_BACKSPACE`      |`KC_BSPC`|Delete (Backspace)        |
|`KC_TAB`            |         |Tab                       |
|`KC_SPACE`          |`KC_SPC` |Spacebar                  |
|`KC_MINUS`          |`KC_MINS`|`-` and `_`               |
|`KC_EQUAL`          |`KC_EQL` |`=` and `+`               |
|`KC_LEFT_BRACKET`   |`KC_LBRC`|`[` and `{`               |
|`KC_RIGHT_BRACKET`  |`KC_RBRC`|`]` and `}`               |
|`KC_BACKSLASH`      |`KC_BSLS`|`\` and `\|`              |
|`KC_NONUS_HASH`     |`KC_NUHS`|Non-US `#` and `~`        |
|`KC_SEMICOLON`      |`KC_SCLN`|`;` and `:`               |
|`KC_QUOTE`          |`KC_QUOT`|`'` and `"`               |
|`KC_GRAVE`          |`KC_GRV` |<code>&#96;</code> and `~`|
|`KC_COMMA`          |`KC_COMM`|`,` and `<`               |
|`KC_DOT`            |         |`.` and `>`               |
|`KC_SLASH`          |`KC_SLSH`|`/` and `?`               |
|`KC_NONUS_BACKSLASH`|`KC_NUBS`|Non-US `\` and `\|`       |

## Lock Keys

|Key                     |Aliases             |Description                         |
|------------------------|--------------------|------------------------------------|
|`KC_CAPS_LOCK`          |`KC_CAPS`           |Caps Lock                           |
|`KC_SCROLL_LOCK`        |`KC_SCRL`, `KC_BRMD`|Scroll Lock, Brightness Down (macOS)|
|`KC_NUM_LOCK`           |`KC_NUM`            |Keypad Num Lock and Clear           |
|`KC_LOCKING_CAPS_LOCK`  |`KC_LCAP`           |Locking Caps Lock                   |
|`KC_LOCKING_NUM_LOCK`   |`KC_LNUM`           |Locking Num Lock                    |
|`KC_LOCKING_SCROLL_LOCK`|`KC_LSCR`           |Locking Scroll Lock                 |

## Modifiers

|Key             |Aliases                        |Description                         |
|----------------|-------------------------------|------------------------------------|
|`KC_LEFT_CTRL`  |`KC_LCTL`                      |Left Control                        |
|`KC_LEFT_SHIFT` |`KC_LSFT`                      |Left Shift                          |
|`KC_LEFT_ALT`   |`KC_LALT`, `KC_LOPT`           |Left Alt (Option)                   |
|`KC_LEFT_GUI`   |`KC_LGUI`, `KC_LCMD`, `KC_LWIN`|Left GUI (Windows/Command/Meta key) |
|`KC_RIGHT_CTRL` |`KC_RCTL`                      |Right Control                       |
|`KC_RIGHT_SHIFT`|`KC_RSFT`                      |Right Shift                         |
|`KC_RIGHT_ALT`  |`KC_RALT`, `KC_ROPT`, `KC_ALGR`|Right Alt (Option/AltGr)            |
|`KC_RIGHT_GUI`  |`KC_RGUI`, `KC_RCMD`, `KC_RWIN`|Right GUI (Windows/Command/Meta key)|

## International

|Key                 |Aliases  |Description          |
|--------------------|---------|---------------------|
|`KC_INTERNATIONAL_1`|`KC_INT1`|JIS `\` and `_`      |
|`KC_INTERNATIONAL_2`|`KC_INT2`|JIS Katakana/Hiragana|
|`KC_INTERNATIONAL_3`|`KC_INT3`|JIS `¥` and `\|`     |
|`KC_INTERNATIONAL_4`|`KC_INT4`|JIS Henkan           |
|`KC_INTERNATIONAL_5`|`KC_INT5`|JIS Muhenkan         |
|`KC_INTERNATIONAL_6`|`KC_INT6`|JIS Numpad `,`       |
|`KC_INTERNATIONAL_7`|`KC_INT7`|International 7      |
|`KC_INTERNATIONAL_8`|`KC_INT8`|International 8      |
|`KC_INTERNATIONAL_9`|`KC_INT9`|International 9      |
|`KC_LANGUAGE_1`     |`KC_LNG1`|Hangul/English       |
|`KC_LANGUAGE_2`     |`KC_LNG2`|Hanja                |
|`KC_LANGUAGE_3`     |`KC_LNG3`|JIS Katakana         |
|`KC_LANGUAGE_4`     |`KC_LNG4`|JIS Hiragana         |
|`KC_LANGUAGE_5`     |`KC_LNG5`|JIS Zenkaku/Hankaku  |
|`KC_LANGUAGE_6`     |`KC_LNG6`|Language 6           |
|`KC_LANGUAGE_7`     |`KC_LNG7`|Language 7           |
|`KC_LANGUAGE_8`     |`KC_LNG8`|Language 8           |
|`KC_LANGUAGE_9`     |`KC_LNG9`|Language 9           |

## Commands

|Key                 |Aliases                       |Description                           |
|--------------------|------------------------------|--------------------------------------|
|`KC_PRINT_SCREEN`   |`KC_PSCR`                     |Print Screen                          |
|`KC_PAUSE`          |`KC_PAUS`, `KC_BRK`, `KC_BRMU`|Pause, Brightness Up (macOS)          |
|`KC_INSERT`         |`KC_INS`                      |Insert                                |
|`KC_HOME`           |                              |Home                                  |
|`KC_PAGE_UP`        |`KC_PGUP`                     |Page Up                               |
|`KC_DELETE`         |`KC_DEL`                      |Forward Delete                        |
|`KC_END`            |                              |End                                   |
|`KC_PAGE_DOWN`      |`KC_PGDN`                     |Page Down                             |
|`KC_RIGHT`          |`KC_RGHT`                     |Right Arrow                           |
|`KC_LEFT`           |                              |Left Arrow                            |
|`KC_DOWN`           |                              |Down Arrow                            |
|`KC_UP`             |                              |Up Arrow                              |
|`KC_APPLICATION`    |`KC_APP`                      |Application (Windows Context Menu Key)|
|`KC_KB_POWER`       |                              |System Power                          |
|`KC_EXECUTE`        |`KC_EXEC`                     |Execute                               |
|`KC_HELP`           |                              |Help                                  |
|`KC_MENU`           |                              |Menu                                  |
|`KC_SELECT`         |`KC_SLCT`                     |Select                                |
|`KC_STOP`           |                              |Stop                                  |
|`KC_AGAIN`          |`KC_AGIN`                     |Again                                 |
|`KC_UNDO`           |                              |Undo                                  |
|`KC_CUT`            |                              |Cut                                   |
|`KC_COPY`           |                              |Copy                                  |
|`KC_PASTE`          |`KC_PSTE`                     |Paste                                 |
|`KC_FIND`           |                              |Find                                  |
|`KC_KB_MUTE`        |                              |Mute                                  |
|`KC_KB_VOLUME_UP`   |                              |Volume Up                             |
|`KC_KB_VOLUME_DOWN` |                              |Volume Down                           |
|`KC_ALTERNATE_ERASE`|`KC_ERAS`                     |Alternate Erase                       |
|`KC_SYSTEM_REQUEST` |`KC_SYRQ`                     |SysReq/Attention                      |
|`KC_CANCEL`         |`KC_CNCL`                     |Cancel                                |
|`KC_CLEAR`          |`KC_CLR`                      |Clear                                 |
|`KC_PRIOR`          |`KC_PRIR`                     |Prior                                 |
|`KC_RETURN`         |`KC_RETN`                     |Return                                |
|`KC_SEPARATOR`      |`KC_SEPR`                     |Separator                             |
|`KC_OUT`            |                              |Out                                   |
|`KC_OPER`           |                              |Oper                                  |
|`KC_CLEAR_AGAIN`    |`KC_CLAG`                     |Clear/Again                           |
|`KC_CRSEL`          |`KC_CRSL`                     |CrSel/Props                           |
|`KC_EXSEL`          |`KC_EXSL`                     |ExSel                                 |

## Media Keys

These keycodes are not part of the Keyboard/Keypad usage page. The `SYSTEM_` keycodes are found in the Generic Desktop page, and the rest are located in the Consumer page.

?> Some of these keycodes may behave differently depending on the OS. For example, on macOS, the keycodes `KC_MEDIA_FAST_FORWARD`, `KC_MEDIA_REWIND`, `KC_MEDIA_NEXT_TRACK` and `KC_MEDIA_PREV_TRACK` skip within the current track when held, but skip the entire track when tapped.

|Key                    |Aliases  |Description        |
|-----------------------|---------|-------------------|
|`KC_SYSTEM_POWER`      |`KC_PWR` |System Power Down  |
|`KC_SYSTEM_SLEEP`      |`KC_SLEP`|System Sleep       |
|`KC_SYSTEM_WAKE`       |`KC_WAKE`|System Wake        |
|`KC_AUDIO_MUTE`        |`KC_MUTE`|Mute               |
|`KC_AUDIO_VOL_UP`      |`KC_VOLU`|Volume Up          |
|`KC_AUDIO_VOL_DOWN`    |`KC_VOLD`|Volume Down        |
|`KC_MEDIA_NEXT_TRACK`  |`KC_MNXT`|Next Track         |
|`KC_MEDIA_PREV_TRACK`  |`KC_MPRV`|Previous Track     |
|`KC_MEDIA_STOP`        |`KC_MSTP`|Stop Track         |
|`KC_MEDIA_PLAY_PAUSE`  |`KC_MPLY`|Play/Pause Track   |
|`KC_MEDIA_SELECT`      |`KC_MSEL`|Launch Media Player|
|`KC_MEDIA_EJECT`       |`KC_EJCT`|Eject              |
|`KC_MAIL`              |         |Launch Mail        |
|`KC_CALCULATOR`        |`KC_CALC`|Launch Calculator  |
|`KC_MY_COMPUTER`       |`KC_MYCM`|Launch My Computer |
|`KC_WWW_SEARCH`        |`KC_WSCH`|Browser Search     |
|`KC_WWW_HOME`          |`KC_WHOM`|Browser Home       |
|`KC_WWW_BACK`          |`KC_WBAK`|Browser Back       |
|`KC_WWW_FORWARD`       |`KC_WFWD`|Browser Forward    |
|`KC_WWW_STOP`          |`KC_WSTP`|Browser Stop       |
|`KC_WWW_REFRESH`       |`KC_WREF`|Browser Refresh    |
|`KC_WWW_FAVORITES`     |`KC_WFAV`|Browser Favorites  |
|`KC_MEDIA_FAST_FORWARD`|`KC_MFFD`|Next Track         |
|`KC_MEDIA_REWIND`      |`KC_MRWD`|Previous Track     |
|`KC_BRIGHTNESS_UP`     |`KC_BRIU`|Brightness Up      |
|`KC_BRIGHTNESS_DOWN`   |`KC_BRID`|Brightness Down    |
|`KC_CONTROL_PANEL`     |`KC_CPNL`|Open Control Panel |
|`KC_ASSISTANT`         |`KC_ASST`|Launch Assistant   |

## Number Pad

|Key                |Aliases  |Description                   |
|-------------------|---------|------------------------------|
|`KC_KP_SLASH`      |`KC_PSLS`|Keypad `/`                    |
|`KC_KP_ASTERISK`   |`KC_PAST`|Keypad `*`                    |
|`KC_KP_MINUS`      |`KC_PMNS`|Keypad `-`                    |
|`KC_KP_PLUS`       |`KC_PPLS`|Keypad `+`                    |
|`KC_KP_ENTER`      |`KC_PENT`|Keypad Enter                  |
|`KC_KP_1`          |`KC_P1`  |Keypad `1` and End            |
|`KC_KP_2`          |`KC_P2`  |Keypad `2` and Down Arrow     |
|`KC_KP_3`          |`KC_P3`  |Keypad `3` and Page Down      |
|`KC_KP_4`          |`KC_P4`  |Keypad `4` and Left Arrow     |
|`KC_KP_5`          |`KC_P5`  |Keypad `5`                    |
|`KC_KP_6`          |`KC_P6`  |Keypad `6` and Right Arrow    |
|`KC_KP_7`          |`KC_P7`  |Keypad `7` and Home           |
|`KC_KP_8`          |`KC_P8`  |Keypad `8` and Up Arrow       |
|`KC_KP_9`          |`KC_P9`  |Keypad `9` and Page Up        |
|`KC_KP_0`          |`KC_P0`  |Keypad `0` and Insert         |
|`KC_KP_DOT`        |`KC_PDOT`|Keypad `.` and Delete         |
|`KC_KP_EQUAL`      |`KC_PEQL`|Keypad `=`                    |
|`KC_KP_COMMA`      |`KC_PCMM`|Keypad `,`                    |
|`KC_KP_EQUAL_AS400`|         |Keypad `=` on AS/400 keyboards|

## Special Keys

In addition to these, keycodes in the range of `0xA5-DF` are reserved for internal use.

|Key             |Aliases             |Description                            |
|----------------|--------------------|---------------------------------------|
|`KC_NO`         |`XXXXXXX`           |Ignore this key (NOOP)                 |
|`KC_TRANSPARENT`|`KC_TRNS`, `_______`|Use the next lowest non-transparent key|
