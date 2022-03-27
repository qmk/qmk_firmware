# Basic Keycodes

The basic set of keycodes are based on the [HID Keyboard/Keypad Usage Page (0x07)](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf) with the exception of `KC_NO`, `KC_TRNS` and keycodes in the `0xA5-DF` range. See below for more details.

## Letters and Numbers

[keycodes_letters_and_numbers.md](./keycodes_letters_and_numbers.md ':include')

## F Keys

[keycodes_f_keys.md](./keycodes_f_keys.md ':include')

## Punctuation

[keycodes_punctuation.md](./keycodes_punctuation.md ':include')

## Lock Keys

[keycodes_lock_keys.md](./keycodes_lock_keys.md ':include')

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

[keycodes_international.md](./keycodes_international.md ':include')

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
