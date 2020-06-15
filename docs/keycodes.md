# Keycodes Overview

When defining a [keymap](keymap.md) each key needs a valid key definition. This page documents the symbols that correspond to keycodes that are available to you in QMK.

This is a reference only. Each group of keys links to the page documenting their functionality in more detail.

## Basic Keycodes :id=basic-keycodes

See also: [Basic Keycodes](keycodes_basic.md)

|Key                    |Aliases                       |Description                                    |Windows      |macOS        |Linux<sup>1</sup>|
|-----------------------|------------------------------|-----------------------------------------------|-------------|-------------|-----------------|
|`KC_NO`                |`XXXXXXX`                     |Ignore this key (NOOP)                         |*N/A*        |*N/A*        |*N/A*            |
|`KC_TRANSPARENT`       |`KC_TRNS`, `_______`          |Use the next lowest non-transparent key        |*N/A*        |*N/A*        |*N/A*            |
|`KC_A`                 |                              |`a` and `A`                                    |✔            |✔            |✔                |
|`KC_B`                 |                              |`b` and `B`                                    |✔            |✔            |✔                |
|`KC_C`                 |                              |`c` and `C`                                    |✔            |✔            |✔                |
|`KC_D`                 |                              |`d` and `D`                                    |✔            |✔            |✔                |
|`KC_E`                 |                              |`e` and `E`                                    |✔            |✔            |✔                |
|`KC_F`                 |                              |`f` and `F`                                    |✔            |✔            |✔                |
|`KC_G`                 |                              |`g` and `G`                                    |✔            |✔            |✔                |
|`KC_H`                 |                              |`h` and `H`                                    |✔            |✔            |✔                |
|`KC_I`                 |                              |`i` and `I`                                    |✔            |✔            |✔                |
|`KC_J`                 |                              |`j` and `J`                                    |✔            |✔            |✔                |
|`KC_K`                 |                              |`k` and `K`                                    |✔            |✔            |✔                |
|`KC_L`                 |                              |`l` and `L`                                    |✔            |✔            |✔                |
|`KC_M`                 |                              |`m` and `M`                                    |✔            |✔            |✔                |
|`KC_N`                 |                              |`n` and `N`                                    |✔            |✔            |✔                |
|`KC_O`                 |                              |`o` and `O`                                    |✔            |✔            |✔                |
|`KC_P`                 |                              |`p` and `P`                                    |✔            |✔            |✔                |
|`KC_Q`                 |                              |`q` and `Q`                                    |✔            |✔            |✔                |
|`KC_R`                 |                              |`r` and `R`                                    |✔            |✔            |✔                |
|`KC_S`                 |                              |`s` and `S`                                    |✔            |✔            |✔                |
|`KC_T`                 |                              |`t` and `T`                                    |✔            |✔            |✔                |
|`KC_U`                 |                              |`u` and `U`                                    |✔            |✔            |✔                |
|`KC_V`                 |                              |`v` and `V`                                    |✔            |✔            |✔                |
|`KC_W`                 |                              |`w` and `W`                                    |✔            |✔            |✔                |
|`KC_X`                 |                              |`x` and `X`                                    |✔            |✔            |✔                |
|`KC_Y`                 |                              |`y` and `Y`                                    |✔            |✔            |✔                |
|`KC_Z`                 |                              |`z` and `Z`                                    |✔            |✔            |✔                |
|`KC_1`                 |                              |`1` and `!`                                    |✔            |✔            |✔                |
|`KC_2`                 |                              |`2` and `@`                                    |✔            |✔            |✔                |
|`KC_3`                 |                              |`3` and `#`                                    |✔            |✔            |✔                |
|`KC_4`                 |                              |`4` and `$`                                    |✔            |✔            |✔                |
|`KC_5`                 |                              |`5` and `%`                                    |✔            |✔            |✔                |
|`KC_6`                 |                              |`6` and `^`                                    |✔            |✔            |✔                |
|`KC_7`                 |                              |`7` and `&`                                    |✔            |✔            |✔                |
|`KC_8`                 |                              |`8` and `*`                                    |✔            |✔            |✔                |
|`KC_9`                 |                              |`9` and `(`                                    |✔            |✔            |✔                |
|`KC_0`                 |                              |`0` and `)`                                    |✔            |✔            |✔                |
|`KC_ENTER`             |`KC_ENT`                      |Return (Enter)                                 |✔            |✔            |✔                |
|`KC_ESCAPE`            |`KC_ESC`                      |Escape                                         |✔            |✔            |✔                |
|`KC_BSPACE`            |`KC_BSPC`                     |Delete (Backspace)                             |✔            |✔            |✔                |
|`KC_TAB`               |                              |Tab                                            |✔            |✔            |✔                |
|`KC_SPACE`             |`KC_SPC`                      |Spacebar                                       |✔            |✔            |✔                |
|`KC_MINUS`             |`KC_MINS`                     |`-` and `_`                                    |✔            |✔            |✔                |
|`KC_EQUAL`             |`KC_EQL`                      |`=` and `+`                                    |✔            |✔            |✔                |
|`KC_LBRACKET`          |`KC_LBRC`                     |`[` and `{`                                    |✔            |✔            |✔                |
|`KC_RBRACKET`          |`KC_RBRC`                     |`]` and `}`                                    |✔            |✔            |✔                |
|`KC_BSLASH`            |`KC_BSLS`                     |`\` and `\|`                                   |✔            |✔            |✔                |
|`KC_NONUS_HASH`        |`KC_NUHS`                     |Non-US `#` and `~`                             |✔            |✔            |✔                |
|`KC_SCOLON`            |`KC_SCLN`                     |`;` and `:`                                    |✔            |✔            |✔                |
|`KC_QUOTE`             |`KC_QUOT`                     |`'` and `"`                                    |✔            |✔            |✔                |
|`KC_GRAVE`             |`KC_GRV`, `KC_ZKHK`           |<code>&#96;</code> and `~`, JIS Zenkaku/Hankaku|✔            |✔            |✔                |
|`KC_COMMA`             |`KC_COMM`                     |`,` and `<`                                    |✔            |✔            |✔                |
|`KC_DOT`               |                              |`.` and `>`                                    |✔            |✔            |✔                |
|`KC_SLASH`             |`KC_SLSH`                     |`/` and `?`                                    |✔            |✔            |✔                |
|`KC_CAPSLOCK`          |`KC_CLCK`, `KC_CAPS`          |Caps Lock                                      |✔            |✔            |✔                |
|`KC_F1`                |                              |F1                                             |✔            |✔            |✔                |
|`KC_F2`                |                              |F2                                             |✔            |✔            |✔                |
|`KC_F3`                |                              |F3                                             |✔            |✔            |✔                |
|`KC_F4`                |                              |F4                                             |✔            |✔            |✔                |
|`KC_F5`                |                              |F5                                             |✔            |✔            |✔                |
|`KC_F6`                |                              |F6                                             |✔            |✔            |✔                |
|`KC_F7`                |                              |F7                                             |✔            |✔            |✔                |
|`KC_F8`                |                              |F8                                             |✔            |✔            |✔                |
|`KC_F9`                |                              |F9                                             |✔            |✔            |✔                |
|`KC_F10`               |                              |F10                                            |✔            |✔            |✔                |
|`KC_F11`               |                              |F11                                            |✔            |✔            |✔                |
|`KC_F12`               |                              |F12                                            |✔            |✔            |✔                |
|`KC_PSCREEN`           |`KC_PSCR`                     |Print Screen                                   |✔            |✔<sup>2</sup>|✔                |
|`KC_SCROLLLOCK`        |`KC_SLCK`, `KC_BRMD`          |Scroll Lock, Brightness Down (macOS)           |✔            |✔<sup>2</sup>|✔                |
|`KC_PAUSE`             |`KC_PAUS`, `KC_BRK`, `KC_BRMU`|Pause, Brightness Up (macOS)                   |✔            |✔<sup>2</sup>|✔                |
|`KC_INSERT`            |`KC_INS`                      |Insert                                         |✔            |             |✔                |
|`KC_HOME`              |                              |Home                                           |✔            |✔            |✔                |
|`KC_PGUP`              |                              |Page Up                                        |✔            |✔            |✔                |
|`KC_DELETE`            |`KC_DEL`                      |Forward Delete                                 |✔            |✔            |✔                |
|`KC_END`               |                              |End                                            |✔            |✔            |✔                |
|`KC_PGDOWN`            |`KC_PGDN`                     |Page Down                                      |✔            |✔            |✔                |
|`KC_RIGHT`             |`KC_RGHT`                     |Right Arrow                                    |✔            |✔            |✔                |
|`KC_LEFT`              |                              |Left Arrow                                     |✔            |✔            |✔                |
|`KC_DOWN`              |                              |Down Arrow                                     |✔            |✔            |✔                |
|`KC_UP`                |                              |Up Arrow                                       |✔            |✔            |✔                |
|`KC_NUMLOCK`           |`KC_NLCK`                     |Keypad Num Lock and Clear                      |✔            |✔            |✔                |
|`KC_KP_SLASH`          |`KC_PSLS`                     |Keypad `/`                                     |✔            |✔            |✔                |
|`KC_KP_ASTERISK`       |`KC_PAST`                     |Keypad `*`                                     |✔            |✔            |✔                |
|`KC_KP_MINUS`          |`KC_PMNS`                     |Keypad `-`                                     |✔            |✔            |✔                |
|`KC_KP_PLUS`           |`KC_PPLS`                     |Keypad `+`                                     |✔            |✔            |✔                |
|`KC_KP_ENTER`          |`KC_PENT`                     |Keypad Enter                                   |✔            |✔            |✔                |
|`KC_KP_1`              |`KC_P1`                       |Keypad `1` and End                             |✔            |✔            |✔                |
|`KC_KP_2`              |`KC_P2`                       |Keypad `2` and Down Arrow                      |✔            |✔            |✔                |
|`KC_KP_3`              |`KC_P3`                       |Keypad `3` and Page Down                       |✔            |✔            |✔                |
|`KC_KP_4`              |`KC_P4`                       |Keypad `4` and Left Arrow                      |✔            |✔            |✔                |
|`KC_KP_5`              |`KC_P5`                       |Keypad `5`                                     |✔            |✔            |✔                |
|`KC_KP_6`              |`KC_P6`                       |Keypad `6` and Right Arrow                     |✔            |✔            |✔                |
|`KC_KP_7`              |`KC_P7`                       |Keypad `7` and Home                            |✔            |✔            |✔                |
|`KC_KP_8`              |`KC_P8`                       |Keypad `8` and Up Arrow                        |✔            |✔            |✔                |
|`KC_KP_9`              |`KC_P9`                       |Keypad `9` and Page Up                         |✔            |✔            |✔                |
|`KC_KP_0`              |`KC_P0`                       |Keypad `0` and Insert                          |✔            |✔            |✔                |
|`KC_KP_DOT`            |`KC_PDOT`                     |Keypad `.` and Delete                          |✔            |✔            |✔                |
|`KC_NONUS_BSLASH`      |`KC_NUBS`                     |Non-US `\` and `\|`                            |✔            |✔            |✔                |
|`KC_APPLICATION`       |`KC_APP`                      |Application (Windows Context Menu Key)         |✔            |             |✔                |
|`KC_POWER`             |                              |System Power                                   |             |✔<sup>3</sup>|✔                |
|`KC_KP_EQUAL`          |`KC_PEQL`                     |Keypad `=`                                     |✔            |✔            |✔                |
|`KC_F13`               |                              |F13                                            |✔            |✔            |✔                |
|`KC_F14`               |                              |F14                                            |✔            |✔            |✔                |
|`KC_F15`               |                              |F15                                            |✔            |✔            |✔                |
|`KC_F16`               |                              |F16                                            |✔            |✔            |✔                |
|`KC_F17`               |                              |F17                                            |✔            |✔            |✔                |
|`KC_F18`               |                              |F18                                            |✔            |✔            |✔                |
|`KC_F19`               |                              |F19                                            |✔            |✔            |✔                |
|`KC_F20`               |                              |F20                                            |✔            |             |✔                |
|`KC_F21`               |                              |F21                                            |✔            |             |✔                |
|`KC_F22`               |                              |F22                                            |✔            |             |✔                |
|`KC_F23`               |                              |F23                                            |✔            |             |✔                |
|`KC_F24`               |                              |F24                                            |✔            |             |✔                |
|`KC_EXECUTE`           |`KC_EXEC`                     |Execute                                        |            |             |✔                |
|`KC_HELP`              |                              |Help                                           |            |             |✔                |
|`KC_MENU`              |                              |Menu                                           |            |             |✔                |
|`KC_SELECT`            |`KC_SLCT`                     |Select                                         |            |             |✔                |
|`KC_STOP`              |                              |Stop                                           |            |             |✔                |
|`KC_AGAIN`             |`KC_AGIN`                     |Again                                          |            |             |✔                |
|`KC_UNDO`              |                              |Undo                                           |            |             |✔                |
|`KC_CUT`               |                              |Cut                                            |            |             |✔                |
|`KC_COPY`              |                              |Copy                                           |            |             |✔                |
|`KC_PASTE`             |`KC_PSTE`                     |Paste                                          |            |             |✔                |
|`KC_FIND`              |                              |Find                                           |            |             |✔                |
|`KC__MUTE`             |                              |Mute                                           |             |✔            |✔                |
|`KC__VOLUP`            |                              |Volume Up                                      |             |✔            |✔                |
|`KC__VOLDOWN`          |                              |Volume Down                                    |             |✔            |✔                |
|`KC_LOCKING_CAPS`      |`KC_LCAP`                     |Locking Caps Lock                              |✔            |✔            |                 |
|`KC_LOCKING_NUM`       |`KC_LNUM`                     |Locking Num Lock                               |✔            |✔            |                 |
|`KC_LOCKING_SCROLL`    |`KC_LSCR`                     |Locking Scroll Lock                            |✔            |✔            |                 |
|`KC_KP_COMMA`          |`KC_PCMM`                     |Keypad `,`                                     |             |             |✔                |
|`KC_KP_EQUAL_AS400`    |                              |Keypad `=` on AS/400 keyboards                 |             |             |                 |
|`KC_INT1`              |`KC_RO`                       |JIS `\` and `_`                                |✔            |             |✔                |
|`KC_INT2`              |`KC_KANA`                     |JIS Katakana/Hiragana                          |✔            |             |✔                |
|`KC_INT3`              |`KC_JYEN`                     |JIS `¥` and `\|`                               |✔            |             |✔                |
|`KC_INT4`              |`KC_HENK`                     |JIS Henkan                                     |✔            |             |✔                |
|`KC_INT5`              |`KC_MHEN`                     |JIS Muhenkan                                   |✔            |             |✔                |
|`KC_INT6`              |                              |JIS Numpad `,`                                 |             |             |✔                |
|`KC_INT7`              |                              |International 7                                |             |             |                 |
|`KC_INT8`              |                              |International 8                                |             |             |                 |
|`KC_INT9`              |                              |International 9                                |             |             |                 |
|`KC_LANG1`             |`KC_HAEN`                     |Hangul/English                                 |             |             |✔                |
|`KC_LANG2`             |`KC_HANJ`                     |Hanja                                          |             |             |✔                |
|`KC_LANG3`             |                              |JIS Katakana                                   |             |             |✔                |
|`KC_LANG4`             |                              |JIS Hiragana                                   |             |             |✔                |
|`KC_LANG5`             |                              |JIS Zenkaku/Hankaku                            |             |             |✔                |
|`KC_LANG6`             |                              |Language 6                                     |             |             |                 |
|`KC_LANG7`             |                              |Language 7                                     |             |             |                 |
|`KC_LANG8`             |                              |Language 8                                     |             |             |                 |
|`KC_LANG9`             |                              |Language 9                                     |             |             |                 |
|`KC_ALT_ERASE`         |`KC_ERAS`                     |Alternate Erase                                |             |             |                 |
|`KC_SYSREQ`            |                              |SysReq/Attention                               |             |             |                 |
|`KC_CANCEL`            |                              |Cancel                                         |             |             |                 |
|`KC_CLEAR`             |`KC_CLR`                      |Clear                                          |             |             |✔                |
|`KC_PRIOR`             |                              |Prior                                          |             |             |                 |
|`KC_RETURN`            |                              |Return                                         |             |             |                 |
|`KC_SEPARATOR`         |                              |Separator                                      |             |             |                 |
|`KC_OUT`               |                              |Out                                            |             |             |                 |
|`KC_OPER`              |                              |Oper                                           |             |             |                 |
|`KC_CLEAR_AGAIN`       |                              |Clear/Again                                    |             |             |                 |
|`KC_CRSEL`             |                              |CrSel/Props                                    |             |             |                 |
|`KC_EXSEL`             |                              |ExSel                                          |             |             |                 |
|`KC_LCTRL`             |`KC_LCTL`                     |Left Control                                   |✔            |✔            |✔                |
|`KC_LSHIFT`            |`KC_LSFT`                     |Left Shift                                     |✔            |✔            |✔                |
|`KC_LALT`              |`KC_LOPT`                     |Left Alt (Option)                              |✔            |✔            |✔                |
|`KC_LGUI`              |`KC_LCMD`, `KC_LWIN`          |Left GUI (Windows/Command/Meta key)            |✔            |✔            |✔                |
|`KC_RCTRL`             |`KC_RCTL`                     |Right Control                                  |✔            |✔            |✔                |
|`KC_RSHIFT`            |`KC_RSFT`                     |Right Shift                                    |✔            |✔            |✔                |
|`KC_RALT`              |`KC_ROPT`, `KC_ALGR`          |Right Alt (Option/AltGr)                       |✔            |✔            |✔                |
|`KC_RGUI`              |`KC_RCMD`, `KC_RWIN`          |Right GUI (Windows/Command/Meta key)           |✔            |✔            |✔                |
|`KC_SYSTEM_POWER`      |`KC_PWR`                      |System Power Down                              |✔            |✔<sup>3</sup>|✔                |
|`KC_SYSTEM_SLEEP`      |`KC_SLEP`                     |System Sleep                                   |✔            |✔<sup>3</sup>|✔                |
|`KC_SYSTEM_WAKE`       |`KC_WAKE`                     |System Wake                                    |             |✔<sup>3</sup>|✔                |
|`KC_AUDIO_MUTE`        |`KC_MUTE`                     |Mute                                           |✔            |✔            |✔                |
|`KC_AUDIO_VOL_UP`      |`KC_VOLU`                     |Volume Up                                      |✔            |✔<sup>4</sup>|✔                |
|`KC_AUDIO_VOL_DOWN`    |`KC_VOLD`                     |Volume Down                                    |✔            |✔<sup>4</sup>|✔                |
|`KC_MEDIA_NEXT_TRACK`  |`KC_MNXT`                     |Next Track                                     |✔            |✔<sup>5</sup>|✔                |
|`KC_MEDIA_PREV_TRACK`  |`KC_MPRV`                     |Previous Track                                 |✔            |✔<sup>5</sup>|✔                |
|`KC_MEDIA_STOP`        |`KC_MSTP`                     |Stop Track                                     |✔            |             |✔                |
|`KC_MEDIA_PLAY_PAUSE`  |`KC_MPLY`                     |Play/Pause Track                               |✔            |✔            |✔                |
|`KC_MEDIA_SELECT`      |`KC_MSEL`                     |Launch Media Player                            |✔            |             |✔                |
|`KC_MEDIA_EJECT`       |`KC_EJCT`                     |Eject                                          |             |✔            |✔                |
|`KC_MAIL`              |                              |Launch Mail                                    |✔            |             |✔                |
|`KC_CALCULATOR`        |`KC_CALC`                     |Launch Calculator                              |✔            |             |✔                |
|`KC_MY_COMPUTER`       |`KC_MYCM`                     |Launch My Computer                             |✔            |             |✔                |
|`KC_WWW_SEARCH`        |`KC_WSCH`                     |Browser Search                                 |✔            |             |✔                |
|`KC_WWW_HOME`          |`KC_WHOM`                     |Browser Home                                   |✔            |             |✔                |
|`KC_WWW_BACK`          |`KC_WBAK`                     |Browser Back                                   |✔            |             |✔                |
|`KC_WWW_FORWARD`       |`KC_WFWD`                     |Browser Forward                                |✔            |             |✔                |
|`KC_WWW_STOP`          |`KC_WSTP`                     |Browser Stop                                   |✔            |             |✔                |
|`KC_WWW_REFRESH`       |`KC_WREF`                     |Browser Refresh                                |✔            |             |✔                |
|`KC_WWW_FAVORITES`     |`KC_WFAV`                     |Browser Favorites                              |✔            |             |✔                |
|`KC_MEDIA_FAST_FORWARD`|`KC_MFFD`                     |Next Track                                     |✔            |✔<sup>5</sup>|✔                |
|`KC_MEDIA_REWIND`      |`KC_MRWD`                     |Previous Track                                 |✔<sup>6</sup>|✔<sup>5</sup>|✔                |
|`KC_BRIGHTNESS_UP`     |`KC_BRIU`                     |Brightness Up                                  |✔            |✔            |✔                |
|`KC_BRIGHTNESS_DOWN`   |`KC_BRID`                     |Brightness Down                                |✔            |✔            |✔                |

<sup>1. The Linux kernel HID driver recognizes [nearly all keycodes](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-input.c), but the default bindings depend on the DE/WM.</sup><br/>
<sup>2. Treated as F13-F15.</sup><br/>
<sup>3. Must be held for about three seconds, and will display a prompt instead.</sup><br/>
<sup>4. Holding Shift+Option allows for finer control of volume level.</sup><br/>
<sup>5. Skips the entire track in iTunes when tapped, seeks within the current track when held.</sup><br/>
<sup>6. WMP does not recognize the Rewind key, but both alter playback speed in VLC.</sup>

## Quantum Keycodes :id=quantum-keycodes

See also: [Quantum Keycodes](quantum_keycodes.md#qmk-keycodes)

|Key           |Aliases  |Description                                            |
|--------------|---------|-------------------------------------------------------|
|`RESET`       |         |Put the keyboard into bootloader mode for flashing     |
|`DEBUG`       |         |Toggle debug mode                                      |
|`EEPROM_RESET`|`EEP_RST`|Reinitializes the keyboard's EEPROM (persistent memory)|

## Audio Keys :id=audio-keys

See also: [Audio](feature_audio.md)

|Key             |Aliases  |Description                       |
|----------------|---------|----------------------------------|
|`AU_ON`         |         |Turns on Audio Feature            |
|`AU_OFF`        |         |Turns off Audio Feature           |
|`AU_TOG`        |         |Toggles Audio state               |
|`CLICKY_TOGGLE` |`CK_TOGG`|Toggles Audio clicky mode         |
|`CLICKY_UP`     |`CK_UP`  |Increases frequency of the clicks |
|`CLICKY_DOWN`   |`CK_DOWN`|Decreases frequency of the clicks |
|`CLICKY_RESET`  |`CK_RST` |Resets frequency to default       |
|`MU_ON`         |         |Turns on Music Mode               |
|`MU_OFF`        |         |Turns off Music Mode              |
|`MU_TOG`        |         |Toggles Music Mode                |
|`MU_MOD`        |         |Cycles through the music modes    |

## Backlighting :id=backlighting

See also: [Backlighting](feature_backlight.md)

|Key      |Description                               |
|---------|------------------------------------------|
|`BL_TOGG`|Turn the backlight on or off              |
|`BL_STEP`|Cycle through backlight levels            |
|`BL_ON`  |Set the backlight to max brightness       |
|`BL_OFF` |Turn the backlight off                    |
|`BL_INC` |Increase the backlight level              |
|`BL_DEC` |Decrease the backlight level              |
|`BL_BRTG`|Toggle backlight breathing                |

## Bootmagic :id=bootmagic

See also: [Bootmagic](feature_bootmagic.md)

|Key                               |Aliases  |Description                                                               |
|----------------------------------|---------|--------------------------------------------------------------------------|
|`MAGIC_SWAP_CONTROL_CAPSLOCK`     |`CL_SWAP`|Swap Caps Lock and Left Control                                           |
|`MAGIC_UNSWAP_CONTROL_CAPSLOCK`   |`CL_NORM`|Unswap Caps Lock and Left Control                                         |
|`MAGIC_CAPSLOCK_TO_CONTROL`       |`CL_CTRL`|Treat Caps Lock as Control                                                |
|`MAGIC_UNCAPSLOCK_TO_CONTROL`     |`CL_CAPS`|Stop treating Caps Lock as Control                                        |
|`MAGIC_SWAP_LCTL_LGUI`            |`LCG_SWP`|Swap Left Control and GUI                                                 |
|`MAGIC_UNSWAP_LCTL_LGUI`          |`LCG_NRM`|Unswap Left Control and GUI                                               |
|`MAGIC_SWAP_RCTL_RGUI`            |`RCG_SWP`|Swap Right Control and GUI                                                |
|`MAGIC_UNSWAP_RCTL_RGUI`          |`RCG_NRM`|Unswap Right Control and GUI                                              |
|`MAGIC_SWAP_CTL_GUI`              |`CG_SWAP`|Swap Control and GUI on both sides                                        |
|`MAGIC_UNSWAP_CTL_GUI`            |`CG_NORM`|Unswap Control and GUI on both sides                                      |
|`MAGIC_TOGGLE_CTL_GUI`            |`CG_TOGG`|Toggle Control and GUI swap on both sides                                 |
|`MAGIC_SWAP_LALT_LGUI`            |`LAG_SWP`|Swap Left Alt and GUI                                                     |
|`MAGIC_UNSWAP_LALT_LGUI`          |`LAG_NRM`|Unswap Left Alt and GUI                                                   |
|`MAGIC_SWAP_RALT_RGUI`            |`RAG_SWP`|Swap Right Alt and GUI                                                    |
|`MAGIC_UNSWAP_RALT_RGUI`          |`RAG_NRM`|Unswap Right Alt and GUI                                                  |
|`MAGIC_SWAP_ALT_GUI`              |`AG_SWAP`|Swap Alt and GUI on both sides                                            |
|`MAGIC_UNSWAP_ALT_GUI`            |`AG_NORM`|Unswap Alt and GUI on both sides                                          |
|`MAGIC_TOGGLE_ALT_GUI`            |`AG_TOGG`|Toggle Alt and GUI swap on both sides                                     |
|`MAGIC_NO_GUI`                    |`GUI_OFF`|Disable the GUI keys                                                      |
|`MAGIC_UNNO_GUI`                  |`GUI_ON` |Enable the GUI keys                                                       |
|`MAGIC_SWAP_GRAVE_ESC`            |`GE_SWAP`|Swap <code>&#96;</code> and Escape                                        |
|`MAGIC_UNSWAP_GRAVE_ESC`          |`GE_NORM`|Unswap <code>&#96;</code> and Escape                                      |
|`MAGIC_SWAP_BACKSLASH_BACKSPACE`  |`BS_SWAP`|Swap `\` and Backspace                                                    |
|`MAGIC_UNSWAP_BACKSLASH_BACKSPACE`|`BS_NORM`|Unswap `\` and Backspace                                                  |
|`MAGIC_HOST_NKRO`                 |`NK_ON`  |Enable N-key rollover                                                     |
|`MAGIC_UNHOST_NKRO`               |`NK_OFF` |Disable N-key rollover                                                    |
|`MAGIC_TOGGLE_NKRO`               |`NK_TOGG`|Toggle N-key rollover                                                     |
|`MAGIC_EE_HANDS_LEFT`             |`EH_LEFT`|Set the master half of a split keyboard as the left hand (for `EE_HANDS`) |
|`MAGIC_EE_HANDS_RIGHT`            |`EH_RGHT`|Set the master half of a split keyboard as the right hand (for `EE_HANDS`)|

## Bluetooth :id=bluetooth

See also: [Bluetooth](feature_bluetooth.md)

|Key       |Description                                   |
|----------|----------------------------------------------|
|`OUT_AUTO`|Automatically switch between USB and Bluetooth|
|`OUT_USB` |USB only                                      |
|`OUT_BT`  |Bluetooth only                                |

## Dynamic Macros :id=dynamic-macros

See also: [Dynamic Macros](feature_dynamic_macros.md)

|Key              |Aliases  |Description                                       |
|-----------------|---------|--------------------------------------------------|
|`DYN_REC_START1` |`DM_REC1`|Start recording Macro 1                           |
|`DYN_REC_START2` |`DM_REC2`|Start recording Macro 2                           |
|`DYN_MACRO_PLAY1`|`DM_PLY1`|Replay Macro 1                                    |
|`DYN_MACRO_PLAY2`|`DM_PLY2`|Replay Macro 2                                    |
|`DYN_REC_STOP`   |`DM_RSTP`|Finish the macro that is currently being recorded.|

## Grave Escape :id=grave-escape

See also: [Grave Escape](feature_grave_esc.md)

|Key        |Aliases  |Description                                                       |
|-----------|---------|------------------------------------------------------------------|
|`GRAVE_ESC`|`KC_GESC`|Escape when pressed, <code>&#96;</code> when Shift or GUI are held|

## Key Lock :id=key-lock

See also: [Key Lock](feature_key_lock.md)

|Key      |Description                                                   |
|---------|--------------------------------------------------------------|
|`KC_LOCK`|Hold down the next key pressed, until the key is pressed again|

## Layer Switching :id=layer-switching

See also: [Layer Switching](feature_layers.md#switching-and-toggling-layers)

|Key             |Description                                                                       |
|----------------|----------------------------------------------------------------------------------|
|`DF(layer)`     |Set the base (default) layer                                                      |
|`MO(layer)`     |Momentarily turn on `layer` when pressed (requires `KC_TRNS` on destination layer)|
|`OSL(layer)`    |Momentarily activates `layer` until a key is pressed. See [One Shot Keys](one_shot_keys.md) for details. |
|`LM(layer, mod)`|Momentarily turn on `layer` (like MO) with `mod` active as well.  Where `mod` is a mods_bit.  Mods can be viewed [here](mod_tap.md).  Example Implementation: `LM(LAYER_1, MOD_LALT)`|
|`LT(layer, kc)` |Turn on `layer` when held, `kc` when tapped                                       |
|`TG(layer)`     |Toggle `layer` on or off                                                          |
|`TO(layer)`     |Turns on `layer` and turns off all other layers, except the default layer |
|`TT(layer)`     |Normally acts like MO unless it's tapped multiple times, which toggles `layer` on |

## Leader Key :id=leader-key

See also: [Leader Key](feature_leader_key.md)

|Key      |Description             |
|---------|------------------------|
|`KC_LEAD`|Begins a leader sequence|

## Mouse Keys :id=mouse-keys

See also: [Mouse Keys](feature_mouse_keys.md)

|Key             |Aliases  |Description                |
|----------------|---------|---------------------------|
|`KC_MS_UP`      |`KC_MS_U`|Mouse Cursor Up            |
|`KC_MS_DOWN`    |`KC_MS_D`|Mouse Cursor Down          |
|`KC_MS_LEFT`    |`KC_MS_L`|Mouse Cursor Left          |
|`KC_MS_RIGHT`   |`KC_MS_R`|Mouse Cursor Right         |
|`KC_MS_BTN1`    |`KC_BTN1`|Mouse Button 1             |
|`KC_MS_BTN2`    |`KC_BTN2`|Mouse Button 2             |
|`KC_MS_BTN3`    |`KC_BTN3`|Mouse Button 3             |
|`KC_MS_BTN4`    |`KC_BTN4`|Mouse Button 4             |
|`KC_MS_BTN5`    |`KC_BTN5`|Mouse Button 5             |
|`KC_MS_WH_UP`   |`KC_WH_U`|Mouse Wheel Up             |
|`KC_MS_WH_DOWN` |`KC_WH_D`|Mouse Wheel Down           |
|`KC_MS_WH_LEFT` |`KC_WH_L`|Mouse Wheel Left           |
|`KC_MS_WH_RIGHT`|`KC_WH_R`|Mouse Wheel Right          |
|`KC_MS_ACCEL0`  |`KC_ACL0`|Set mouse acceleration to 0|
|`KC_MS_ACCEL1`  |`KC_ACL1`|Set mouse acceleration to 1|
|`KC_MS_ACCEL2`  |`KC_ACL2`|Set mouse acceleration to 2|

## Modifiers :id=modifiers

See also: [Modifier Keys](feature_advanced_keycodes.md#modifier-keys)

|Key       |Aliases                        |Description                                         |
|----------|-------------------------------|----------------------------------------------------|
|`LCTL(kc)`|`C(kc)`                        |Hold Left Control and press `kc`                    |
|`LSFT(kc)`|`S(kc)`                        |Hold Left Shift and press `kc`                      |
|`LALT(kc)`|`A(kc)`, `LOPT(kc)`            |Hold Left Alt and press `kc`                        |
|`LGUI(kc)`|`G(kc)`, `LCMD(kc)`, `LWIN(kc)`|Hold Left GUI and press `kc`                        |
|`RCTL(kc)`|                               |Hold Right Control and press `kc`                   |
|`RSFT(kc)`|                               |Hold Right Shift and press `kc`                     |
|`RALT(kc)`|`ROPT(kc)`, `ALGR(kc)`         |Hold Right Alt and press `kc`                       |
|`RGUI(kc)`|`RCMD(kc)`, `LWIN(kc)`         |Hold Right GUI and press `kc`                       |
|`SGUI(kc)`|`SCMD(kc)`, `SWIN(kc)`         |Hold Left Shift and GUI and press `kc`              |
|`LCA(kc)` |                               |Hold Left Control and Alt and press `kc`            |
|`LCAG(kc)`|                               |Hold Left Control, Alt and GUI and press `kc`       |
|`MEH(kc)` |                               |Hold Left Control, Shift and Alt and press `kc`     |
|`HYPR(kc)`|                               |Hold Left Control, Shift, Alt and GUI and press `kc`|
|`KC_MEH`  |                               |Left Control, Shift and Alt                         |
|`KC_HYPR` |                               |Left Control, Shift, Alt and GUI                    |

## Mod-Tap Keys :id=mod-tap-keys

See also: [Mod-Tap](mod_tap.md)

|Key          |Aliases                                                          |Description                                            |
|-------------|-----------------------------------------------------------------|-------------------------------------------------------|
|`MT(mod, kc)`|                                                                 |`mod` when held, `kc` when tapped                      |
|`LCTL_T(kc)` |`CTL_T(kc)`                                                      |Left Control when held, `kc` when tapped               |
|`LSFT_T(kc)` |`SFT_T(kc)`                                                      |Left Shift when held, `kc` when tapped                 |
|`LALT_T(kc)` |`LOPT_T(kc)`, `ALT_T(kc)`, `OPT_T(kc)`                           |Left Alt when held, `kc` when tapped                   |
|`LGUI_T(kc)` |`LCMD_T(kc)`, `LWIN_T(kc)`, `GUI_T(kc)`, `CMD_T(kc)`, `WIN_T(kc)`|Left GUI when held, `kc` when tapped                   |
|`RCTL_T(kc)` |                                                                 |Right Control when held, `kc` when tapped              |
|`RSFT_T(kc)` |                                                                 |Right Shift when held, `kc` when tapped                |
|`RALT_T(kc)` |`ROPT_T(kc)`, `ALGR_T(kc)`                                       |Right Alt when held, `kc` when tapped                  |
|`RGUI_T(kc)` |`RCMD_T(kc)`, `RWIN_T(kc)`                                       |Right GUI when held, `kc` when tapped                  |
|`SGUI_T(kc)` |`SCMD_T(kc)`, `SWIN_T(kc)`                                       |Left Shift and GUI when held, `kc` when tapped         |
|`LCA_T(kc)`  |                                                                 |Left Control and Alt when held, `kc` when tapped       |
|`LCAG_T(kc)` |                                                                 |Left Control, Alt and GUI when held, `kc` when tapped  |
|`RCAG_T(kc)` |                                                                 |Right Control, Alt and GUI when held, `kc` when tapped |
|`C_S_T(kc)`  |                                                                 |Left Control and Shift when held, `kc` when tapped     |
|`MEH_T(kc)`  |                                                                 |Left Control, Shift and Alt when held, `kc` when tapped|
|`HYPR_T(kc)` |`ALL_T(kc)`                                                      |Left Control, Shift, Alt and GUI when held, `kc` when tapped - more info [here](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)|

## RGB Lighting :id=rgb-lighting

See also: [RGB Lighting](feature_rgblight.md)

|Key                |Aliases   |Description                                                         |
|-------------------|----------|--------------------------------------------------------------------|
|`RGB_TOG`          |          |Toggle RGB lighting on or off                                       |
|`RGB_MODE_FORWARD` |`RGB_MOD` |Cycle through modes, reverse direction when Shift is held           |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|Cycle through modes in reverse, forward direction when Shift is held|
|`RGB_HUI`          |          |Increase hue, decrease hue when Shift is held                       |
|`RGB_HUD`          |          |Decrease hue, increase hue when Shift is held                       |
|`RGB_SAI`          |          |Increase saturation, decrease saturation when Shift is held         |
|`RGB_SAD`          |          |Decrease saturation, increase saturation when Shift is held         |
|`RGB_VAI`          |          |Increase value (brightness), decrease value when Shift is held      |
|`RGB_VAD`          |          |Decrease value (brightness), increase value when Shift is held      |
|`RGB_MODE_PLAIN`   |`RGB_M_P `|Static (no animation) mode                                          |
|`RGB_MODE_BREATHE` |`RGB_M_B` |Breathing animation mode                                            |
|`RGB_MODE_RAINBOW` |`RGB_M_R` |Rainbow animation mode                                              |
|`RGB_MODE_SWIRL`   |`RGB_M_SW`|Swirl animation mode                                                |
|`RGB_MODE_SNAKE`   |`RGB_M_SN`|Snake animation mode                                                |
|`RGB_MODE_KNIGHT`  |`RGB_M_K` |"Knight Rider" animation mode                                       |
|`RGB_MODE_XMAS`    |`RGB_M_X` |Christmas animation mode                                            |
|`RGB_MODE_GRADIENT`|`RGB_M_G` |Static gradient animation mode                                      |
|`RGB_MODE_RGBTEST` |`RGB_M_T` |Red,Green,Blue test animation mode                                  |

## RGB Matrix Lighting :id=rgb-matrix-lighting

See also: [RGB Matrix Lighting](feature_rgb_matrix.md)

|Key                |Aliases   |Description                                                                           |
|-------------------|----------|--------------------------------------------------------------------------------------|
|`RGB_TOG`          |          |Toggle RGB lighting on or off                                                         |
|`RGB_MODE_FORWARD` |`RGB_MOD` |Cycle through modes, reverse direction when Shift is held                             |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|Cycle through modes in reverse, forward direction when Shift is held                  |
|`RGB_HUI`          |          |Increase hue, decrease hue when Shift is held                                         |
|`RGB_HUD`          |          |Decrease hue, increase hue when Shift is held                                         |
|`RGB_SAI`          |          |Increase saturation, decrease saturation when Shift is held                           |
|`RGB_SAD`          |          |Decrease saturation, increase saturation when Shift is held                           |
|`RGB_VAI`          |          |Increase value (brightness), decrease value when Shift is held                        |
|`RGB_VAD`          |          |Decrease value (brightness), increase value when Shift is held                        |
|`RGB_SPI`          |          |Increase effect speed (does not support eeprom yet), decrease speed when Shift is held|
|`RGB_SPD`          |          |Decrease effect speed (does not support eeprom yet), increase speed when Shift is held|

## Thermal Printer :id=thermal-printer

See also: [Thermal Printer](feature_thermal_printer.md)

|Key        |Description                             |
|-----------|----------------------------------------|
|`PRINT_ON` |Start printing everything the user types|
|`PRINT_OFF`|Stop printing everything the user types |

## US ANSI Shifted Symbols :id=us-ansi-shifted-symbols

See also: [US ANSI Shifted Symbols](keycodes_us_ansi_shifted.md)

|Key                     |Aliases            |Description|
|------------------------|-------------------|-----------|
|`KC_TILDE`              |`KC_TILD`          |`~`        |
|`KC_EXCLAIM`            |`KC_EXLM`          |`!`        |
|`KC_AT`                 |                   |`@`        |
|`KC_HASH`               |                   |`#`        |
|`KC_DOLLAR`             |`KC_DLR`           |`$`        |
|`KC_PERCENT`            |`KC_PERC`          |`%`        |
|`KC_CIRCUMFLEX`         |`KC_CIRC`          |`^`        |
|`KC_AMPERSAND`          |`KC_AMPR`          |`&`        |
|`KC_ASTERISK`           |`KC_ASTR`          |`*`        |
|`KC_LEFT_PAREN`         |`KC_LPRN`          |`(`        |
|`KC_RIGHT_PAREN`        |`KC_RPRN`          |`)`        |
|`KC_UNDERSCORE`         |`KC_UNDS`          |`_`        |
|`KC_PLUS`               |                   |`+`        |
|`KC_LEFT_CURLY_BRACE`   |`KC_LCBR`          |`{`        |
|`KC_RIGHT_CURLY_BRACE`  |`KC_RCBR`          |`}`        |
|`KC_PIPE`               |                   |`\|`       |
|`KC_COLON`              |`KC_COLN`          |`:`        |
|`KC_DOUBLE_QUOTE`       |`KC_DQUO`, `KC_DQT`|`"`        |
|`KC_LEFT_ANGLE_BRACKET` |`KC_LABK`, `KC_LT` |`<`        |
|`KC_RIGHT_ANGLE_BRACKET`|`KC_RABK`, `KC_GT` |`>`        |
|`KC_QUESTION`           |`KC_QUES`          |`?`        |

## One Shot Keys :id=one-shot-keys

See also: [One Shot Keys](one_shot_keys.md)

|Key         |Description                       |
|------------|----------------------------------|
|`OSM(mod)`  |Hold `mod` for one keypress       |
|`OSL(layer)`|Switch to `layer` for one keypress|

## Space Cadet :id=space-cadet

See also: [Space Cadet](feature_space_cadet.md)

|Key        |Description                             |
|-----------|----------------------------------------|
|`KC_LCPO`  |Left Control when held, `(` when tapped |
|`KC_RCPC`  |Right Control when held, `)` when tapped|
|`KC_LSPO`  |Left Shift when held, `(` when tapped   |
|`KC_RSPC`  |Right Shift when held, `)` when tapped  |
|`KC_LAPO`  |Left Alt when held, `(` when tapped     |
|`KC_RAPC`  |Right Alt when held, `)` when tapped    |
|`KC_SFTENT`|Right Shift when held, Enter when tapped|

## Swap Hands :id=swap-hands

See also: [Swap Hands](feature_swap_hands.md)

|Key        |Description                                                              |
|-----------|-------------------------------------------------------------------------|
|`SH_T(key)`|Sends `key` with a tap; momentary swap when held.                        |
|`SW_ON`    |Turns on swapping and leaves it on.                                      |
|`SW_OFF`   |Turn off swapping and leaves it off. Good for returning to a known state.|
|`SH_MON`   |Swaps hands when pressed, returns to normal when released (momentary).   |
|`SH_MOFF`  |Momentarily turns off swap.                                              |
|`SH_TG`    |Toggles swap on and off with every key press.                            |
|`SH_TT`    |Toggles with a tap; momentary when held.                                 |
|`SH_OS`    |One shot swap hands: toggle while pressed or until next key press.       |

## Unicode Support :id=unicode-support

See also: [Unicode Support](feature_unicode.md)

|Key                   |Aliases  |Description                                                     |
|----------------------|---------|----------------------------------------------------------------|
|`UC(c)`               |         |Send Unicode code point `c`                                     |
|`X(i)`                |         |Send Unicode code point at index `i` in `unicode_map`           |
|`XP(i, j)`            |         |Send Unicode code point at index `i`, or `j` if Shift/Caps is on|
|`UNICODE_MODE_FORWARD`|`UC_MOD` |Cycle through selected input modes                              |
|`UNICODE_MODE_REVERSE`|`UC_RMOD`|Cycle through selected input modes in reverse                   |
|`UNICODE_MODE_MAC`    |`UC_M_MA`|Switch to macOS input                                           |
|`UNICODE_MODE_LNX`    |`UC_M_LN`|Switch to Linux input                                           |
|`UNICODE_MODE_WIN`    |`UC_M_WI`|Switch to Windows input                                         |
|`UNICODE_MODE_BSD`    |`UC_M_BS`|Switch to BSD input (not implemented)                           |
|`UNICODE_MODE_WINC`   |`UC_M_WC`|Switch to Windows input using WinCompose                        |
