# Keycodes Overview

When defining a [keymap](keymap) each key needs a valid key definition. This page documents the symbols that correspond to keycodes that are available to you in QMK.

This is a reference only. Each group of keys links to the page documenting their functionality in more detail.

## Basic Keycodes {#basic-keycodes}

See also: [Basic Keycodes](keycodes_basic)

|Key                     |Aliases                        |Description                            |Windows      |macOS        |Linux<sup>1</sup>|
|------------------------|-------------------------------|---------------------------------------|-------------|-------------|-----------------|
|`KC_NO`                 |`XXXXXXX`                      |Ignore this key (NOOP)                 |*N/A*        |*N/A*        |*N/A*            |
|`KC_TRANSPARENT`        |`KC_TRNS`, `_______`           |Use the next lowest non-transparent key|*N/A*        |*N/A*        |*N/A*            |
|`KC_A`                  |                               |`a` and `A`                            |✔            |✔            |✔                |
|`KC_B`                  |                               |`b` and `B`                            |✔            |✔            |✔                |
|`KC_C`                  |                               |`c` and `C`                            |✔            |✔            |✔                |
|`KC_D`                  |                               |`d` and `D`                            |✔            |✔            |✔                |
|`KC_E`                  |                               |`e` and `E`                            |✔            |✔            |✔                |
|`KC_F`                  |                               |`f` and `F`                            |✔            |✔            |✔                |
|`KC_G`                  |                               |`g` and `G`                            |✔            |✔            |✔                |
|`KC_H`                  |                               |`h` and `H`                            |✔            |✔            |✔                |
|`KC_I`                  |                               |`i` and `I`                            |✔            |✔            |✔                |
|`KC_J`                  |                               |`j` and `J`                            |✔            |✔            |✔                |
|`KC_K`                  |                               |`k` and `K`                            |✔            |✔            |✔                |
|`KC_L`                  |                               |`l` and `L`                            |✔            |✔            |✔                |
|`KC_M`                  |                               |`m` and `M`                            |✔            |✔            |✔                |
|`KC_N`                  |                               |`n` and `N`                            |✔            |✔            |✔                |
|`KC_O`                  |                               |`o` and `O`                            |✔            |✔            |✔                |
|`KC_P`                  |                               |`p` and `P`                            |✔            |✔            |✔                |
|`KC_Q`                  |                               |`q` and `Q`                            |✔            |✔            |✔                |
|`KC_R`                  |                               |`r` and `R`                            |✔            |✔            |✔                |
|`KC_S`                  |                               |`s` and `S`                            |✔            |✔            |✔                |
|`KC_T`                  |                               |`t` and `T`                            |✔            |✔            |✔                |
|`KC_U`                  |                               |`u` and `U`                            |✔            |✔            |✔                |
|`KC_V`                  |                               |`v` and `V`                            |✔            |✔            |✔                |
|`KC_W`                  |                               |`w` and `W`                            |✔            |✔            |✔                |
|`KC_X`                  |                               |`x` and `X`                            |✔            |✔            |✔                |
|`KC_Y`                  |                               |`y` and `Y`                            |✔            |✔            |✔                |
|`KC_Z`                  |                               |`z` and `Z`                            |✔            |✔            |✔                |
|`KC_1`                  |                               |`1` and `!`                            |✔            |✔            |✔                |
|`KC_2`                  |                               |`2` and `@`                            |✔            |✔            |✔                |
|`KC_3`                  |                               |`3` and `#`                            |✔            |✔            |✔                |
|`KC_4`                  |                               |`4` and `$`                            |✔            |✔            |✔                |
|`KC_5`                  |                               |`5` and `%`                            |✔            |✔            |✔                |
|`KC_6`                  |                               |`6` and `^`                            |✔            |✔            |✔                |
|`KC_7`                  |                               |`7` and `&`                            |✔            |✔            |✔                |
|`KC_8`                  |                               |`8` and `*`                            |✔            |✔            |✔                |
|`KC_9`                  |                               |`9` and `(`                            |✔            |✔            |✔                |
|`KC_0`                  |                               |`0` and `)`                            |✔            |✔            |✔                |
|`KC_ENTER`              |`KC_ENT`                       |Return (Enter)                         |✔            |✔            |✔                |
|`KC_ESCAPE`             |`KC_ESC`                       |Escape                                 |✔            |✔            |✔                |
|`KC_BACKSPACE`          |`KC_BSPC`                      |Delete (Backspace)                     |✔            |✔            |✔                |
|`KC_TAB`                |                               |Tab                                    |✔            |✔            |✔                |
|`KC_SPACE`              |`KC_SPC`                       |Spacebar                               |✔            |✔            |✔                |
|`KC_MINUS`              |`KC_MINS`                      |`-` and `_`                            |✔            |✔            |✔                |
|`KC_EQUAL`              |`KC_EQL`                       |`=` and `+`                            |✔            |✔            |✔                |
|`KC_LEFT_BRACKET`       |`KC_LBRC`                      |`[` and `{`                            |✔            |✔            |✔                |
|`KC_RIGHT_BRACKET`      |`KC_RBRC`                      |`]` and `}`                            |✔            |✔            |✔                |
|`KC_BACKSLASH`          |`KC_BSLS`                      |`\` and `\|`                           |✔            |✔            |✔                |
|`KC_NONUS_HASH`         |`KC_NUHS`                      |Non-US `#` and `~`                     |✔            |✔            |✔                |
|`KC_SEMICOLON`          |`KC_SCLN`                      |`;` and `:`                            |✔            |✔            |✔                |
|`KC_QUOTE`              |`KC_QUOT`                      |`'` and `"`                            |✔            |✔            |✔                |
|`KC_GRAVE`              |`KC_GRV`                       |<code>&#96;</code> and `~`             |✔            |✔            |✔                |
|`KC_COMMA`              |`KC_COMM`                      |`,` and `<`                            |✔            |✔            |✔                |
|`KC_DOT`                |                               |`.` and `>`                            |✔            |✔            |✔                |
|`KC_SLASH`              |`KC_SLSH`                      |`/` and `?`                            |✔            |✔            |✔                |
|`KC_CAPS_LOCK`          |`KC_CAPS`                      |Caps Lock                              |✔            |✔            |✔                |
|`KC_F1`                 |                               |F1                                     |✔            |✔            |✔                |
|`KC_F2`                 |                               |F2                                     |✔            |✔            |✔                |
|`KC_F3`                 |                               |F3                                     |✔            |✔            |✔                |
|`KC_F4`                 |                               |F4                                     |✔            |✔            |✔                |
|`KC_F5`                 |                               |F5                                     |✔            |✔            |✔                |
|`KC_F6`                 |                               |F6                                     |✔            |✔            |✔                |
|`KC_F7`                 |                               |F7                                     |✔            |✔            |✔                |
|`KC_F8`                 |                               |F8                                     |✔            |✔            |✔                |
|`KC_F9`                 |                               |F9                                     |✔            |✔            |✔                |
|`KC_F10`                |                               |F10                                    |✔            |✔            |✔                |
|`KC_F11`                |                               |F11                                    |✔            |✔            |✔                |
|`KC_F12`                |                               |F12                                    |✔            |✔            |✔                |
|`KC_PRINT_SCREEN`       |`KC_PSCR`                      |Print Screen                           |✔            |✔<sup>2</sup>|✔                |
|`KC_SCROLL_LOCK`        |`KC_SCRL`, `KC_BRMD`           |Scroll Lock, Brightness Down (macOS)   |✔            |✔<sup>2</sup>|✔                |
|`KC_PAUSE`              |`KC_PAUS`, `KC_BRK`, `KC_BRMU` |Pause, Brightness Up (macOS)           |✔            |✔<sup>2</sup>|✔                |
|`KC_INSERT`             |`KC_INS`                       |Insert                                 |✔            |             |✔                |
|`KC_HOME`               |                               |Home                                   |✔            |✔            |✔                |
|`KC_PAGE_UP`            |`KC_PGUP`                      |Page Up                                |✔            |✔            |✔                |
|`KC_DELETE`             |`KC_DEL`                       |Forward Delete                         |✔            |✔            |✔                |
|`KC_END`                |                               |End                                    |✔            |✔            |✔                |
|`KC_PAGE_DOWN`          |`KC_PGDN`                      |Page Down                              |✔            |✔            |✔                |
|`KC_RIGHT`              |`KC_RGHT`                      |Right Arrow                            |✔            |✔            |✔                |
|`KC_LEFT`               |                               |Left Arrow                             |✔            |✔            |✔                |
|`KC_DOWN`               |                               |Down Arrow                             |✔            |✔            |✔                |
|`KC_UP`                 |                               |Up Arrow                               |✔            |✔            |✔                |
|`KC_NUM_LOCK`           |`KC_NUM`                       |Keypad Num Lock and Clear              |✔            |✔            |✔                |
|`KC_KP_SLASH`           |`KC_PSLS`                      |Keypad `/`                             |✔            |✔            |✔                |
|`KC_KP_ASTERISK`        |`KC_PAST`                      |Keypad `*`                             |✔            |✔            |✔                |
|`KC_KP_MINUS`           |`KC_PMNS`                      |Keypad `-`                             |✔            |✔            |✔                |
|`KC_KP_PLUS`            |`KC_PPLS`                      |Keypad `+`                             |✔            |✔            |✔                |
|`KC_KP_ENTER`           |`KC_PENT`                      |Keypad Enter                           |✔            |✔            |✔                |
|`KC_KP_1`               |`KC_P1`                        |Keypad `1` and End                     |✔            |✔            |✔                |
|`KC_KP_2`               |`KC_P2`                        |Keypad `2` and Down Arrow              |✔            |✔            |✔                |
|`KC_KP_3`               |`KC_P3`                        |Keypad `3` and Page Down               |✔            |✔            |✔                |
|`KC_KP_4`               |`KC_P4`                        |Keypad `4` and Left Arrow              |✔            |✔            |✔                |
|`KC_KP_5`               |`KC_P5`                        |Keypad `5`                             |✔            |✔            |✔                |
|`KC_KP_6`               |`KC_P6`                        |Keypad `6` and Right Arrow             |✔            |✔            |✔                |
|`KC_KP_7`               |`KC_P7`                        |Keypad `7` and Home                    |✔            |✔            |✔                |
|`KC_KP_8`               |`KC_P8`                        |Keypad `8` and Up Arrow                |✔            |✔            |✔                |
|`KC_KP_9`               |`KC_P9`                        |Keypad `9` and Page Up                 |✔            |✔            |✔                |
|`KC_KP_0`               |`KC_P0`                        |Keypad `0` and Insert                  |✔            |✔            |✔                |
|`KC_KP_DOT`             |`KC_PDOT`                      |Keypad `.` and Delete                  |✔            |✔            |✔                |
|`KC_NONUS_BACKSLASH`    |`KC_NUBS`                      |Non-US `\` and `\|`                    |✔            |✔            |✔                |
|`KC_APPLICATION`        |`KC_APP`                       |Application (Windows Context Menu Key) |✔            |             |✔                |
|`KC_KB_POWER`           |                               |System Power                           |             |✔<sup>3</sup>|✔                |
|`KC_KP_EQUAL`           |`KC_PEQL`                      |Keypad `=`                             |✔            |✔            |✔                |
|`KC_F13`                |                               |F13                                    |✔            |✔            |✔                |
|`KC_F14`                |                               |F14                                    |✔            |✔            |✔                |
|`KC_F15`                |                               |F15                                    |✔            |✔            |✔                |
|`KC_F16`                |                               |F16                                    |✔            |✔            |✔                |
|`KC_F17`                |                               |F17                                    |✔            |✔            |✔                |
|`KC_F18`                |                               |F18                                    |✔            |✔            |✔                |
|`KC_F19`                |                               |F19                                    |✔            |✔            |✔                |
|`KC_F20`                |                               |F20                                    |✔            |             |✔                |
|`KC_F21`                |                               |F21                                    |✔            |             |✔                |
|`KC_F22`                |                               |F22                                    |✔            |             |✔                |
|`KC_F23`                |                               |F23                                    |✔            |             |✔                |
|`KC_F24`                |                               |F24                                    |✔            |             |✔                |
|`KC_EXECUTE`            |`KC_EXEC`                      |Execute                                |             |             |✔                |
|`KC_HELP`               |                               |Help                                   |             |             |✔                |
|`KC_MENU`               |                               |Menu                                   |             |             |✔                |
|`KC_SELECT`             |`KC_SLCT`                      |Select                                 |             |             |✔                |
|`KC_STOP`               |                               |Stop                                   |             |             |✔                |
|`KC_AGAIN`              |`KC_AGIN`                      |Again                                  |             |             |✔                |
|`KC_UNDO`               |                               |Undo                                   |             |             |✔                |
|`KC_CUT`                |                               |Cut                                    |             |             |✔                |
|`KC_COPY`               |                               |Copy                                   |             |             |✔                |
|`KC_PASTE`              |`KC_PSTE`                      |Paste                                  |             |             |✔                |
|`KC_FIND`               |                               |Find                                   |             |             |✔                |
|`KC_KB_MUTE`            |                               |Mute                                   |             |✔            |✔                |
|`KC_KB_VOLUME_UP`       |                               |Volume Up                              |             |✔            |✔                |
|`KC_KB_VOLUME_DOWN`     |                               |Volume Down                            |             |✔            |✔                |
|`KC_LOCKING_CAPS_LOCK`  |`KC_LCAP`                      |Locking Caps Lock                      |✔            |✔            |                 |
|`KC_LOCKING_NUM_LOCK`   |`KC_LNUM`                      |Locking Num Lock                       |✔            |✔            |                 |
|`KC_LOCKING_SCROLL_LOCK`|`KC_LSCR`                      |Locking Scroll Lock                    |✔            |✔            |                 |
|`KC_KP_COMMA`           |`KC_PCMM`                      |Keypad `,`                             |             |             |✔                |
|`KC_KP_EQUAL_AS400`     |                               |Keypad `=` on AS/400 keyboards         |             |             |                 |
|`KC_INTERNATIONAL_1`    |`KC_INT1`                      |International 1                        |✔            |             |✔                |
|`KC_INTERNATIONAL_2`    |`KC_INT2`                      |International 2                        |✔            |             |✔                |
|`KC_INTERNATIONAL_3`    |`KC_INT3`                      |International 3                        |✔            |             |✔                |
|`KC_INTERNATIONAL_4`    |`KC_INT4`                      |International 4                        |✔            |             |✔                |
|`KC_INTERNATIONAL_5`    |`KC_INT5`                      |International 5                        |✔            |             |✔                |
|`KC_INTERNATIONAL_6`    |`KC_INT6`                      |International 6                        |             |             |✔                |
|`KC_INTERNATIONAL_7`    |`KC_INT7`                      |International 7                        |             |             |                 |
|`KC_INTERNATIONAL_8`    |`KC_INT8`                      |International 8                        |             |             |                 |
|`KC_INTERNATIONAL_9`    |`KC_INT9`                      |International 9                        |             |             |                 |
|`KC_LANGUAGE_1`         |`KC_LNG1`                      |Language 1                             |             |             |✔                |
|`KC_LANGUAGE_2`         |`KC_LNG2`                      |Language 2                             |             |             |✔                |
|`KC_LANGUAGE_3`         |`KC_LNG3`                      |Language 3                             |             |             |✔                |
|`KC_LANGUAGE_4`         |`KC_LNG4`                      |Language 4                             |             |             |✔                |
|`KC_LANGUAGE_5`         |`KC_LNG5`                      |Language 5                             |             |             |✔                |
|`KC_LANGUAGE_6`         |`KC_LNG6`                      |Language 6                             |             |             |                 |
|`KC_LANGUAGE_7`         |`KC_LNG7`                      |Language 7                             |             |             |                 |
|`KC_LANGUAGE_8`         |`KC_LNG8`                      |Language 8                             |             |             |                 |
|`KC_LANGUAGE_9`         |`KC_LNG9`                      |Language 9                             |             |             |                 |
|`KC_ALTERNATE_ERASE`    |`KC_ERAS`                      |Alternate Erase                        |             |             |                 |
|`KC_SYSTEM_REQUEST`     |`KC_SYRQ`                      |SysReq/Attention                       |             |             |                 |
|`KC_CANCEL`             |`KC_CNCL`                      |Cancel                                 |             |             |                 |
|`KC_CLEAR`              |`KC_CLR`                       |Clear                                  |             |             |✔                |
|`KC_PRIOR`              |`KC_PRIR`                      |Prior                                  |             |             |                 |
|`KC_RETURN`             |`KC_RETN`                      |Return                                 |             |             |                 |
|`KC_SEPARATOR`          |`KC_SEPR`                      |Separator                              |             |             |                 |
|`KC_OUT`                |                               |Out                                    |             |             |                 |
|`KC_OPER`               |                               |Oper                                   |             |             |                 |
|`KC_CLEAR_AGAIN`        |`KC_CLAG`                      |Clear/Again                            |             |             |                 |
|`KC_CRSEL`              |`KC_CRSL`                      |CrSel/Props                            |             |             |                 |
|`KC_EXSEL`              |`KC_EXSL`                      |ExSel                                  |             |             |                 |
|`KC_LEFT_CTRL`          |`KC_LCTL`                      |Left Control                           |✔            |✔            |✔                |
|`KC_LEFT_SHIFT`         |`KC_LSFT`                      |Left Shift                             |✔            |✔            |✔                |
|`KC_LEFT_ALT`           |`KC_LALT`, `KC_LOPT`           |Left Alt (Option)                      |✔            |✔            |✔                |
|`KC_LEFT_GUI`           |`KC_LGUI`, `KC_LCMD`, `KC_LWIN`|Left GUI (Windows/Command/Meta key)    |✔            |✔            |✔                |
|`KC_RIGHT_CTRL`         |`KC_RCTL`                      |Right Control                          |✔            |✔            |✔                |
|`KC_RIGHT_SHIFT`        |`KC_RSFT`                      |Right Shift                            |✔            |✔            |✔                |
|`KC_RIGHT_ALT`          |`KC_RALT`, `KC_ROPT`, `KC_ALGR`|Right Alt (Option/AltGr)               |✔            |✔            |✔                |
|`KC_RIGHT_GUI`          |`KC_RGUI`, `KC_RCMD`, `KC_RWIN`|Right GUI (Windows/Command/Meta key)   |✔            |✔            |✔                |
|`KC_SYSTEM_POWER`       |`KC_PWR`                       |System Power Down                      |✔            |✔<sup>3</sup>|✔                |
|`KC_SYSTEM_SLEEP`       |`KC_SLEP`                      |System Sleep                           |✔            |✔<sup>3</sup>|✔                |
|`KC_SYSTEM_WAKE`        |`KC_WAKE`                      |System Wake                            |             |✔<sup>3</sup>|✔                |
|`KC_AUDIO_MUTE`         |`KC_MUTE`                      |Mute                                   |✔            |✔            |✔                |
|`KC_AUDIO_VOL_UP`       |`KC_VOLU`                      |Volume Up                              |✔            |✔<sup>4</sup>|✔                |
|`KC_AUDIO_VOL_DOWN`     |`KC_VOLD`                      |Volume Down                            |✔            |✔<sup>4</sup>|✔                |
|`KC_MEDIA_NEXT_TRACK`   |`KC_MNXT`                      |Next Track                             |✔            |✔<sup>5</sup>|✔                |
|`KC_MEDIA_PREV_TRACK`   |`KC_MPRV`                      |Previous Track                         |✔            |✔<sup>5</sup>|✔                |
|`KC_MEDIA_STOP`         |`KC_MSTP`                      |Stop Track                             |✔            |             |✔                |
|`KC_MEDIA_PLAY_PAUSE`   |`KC_MPLY`                      |Play/Pause Track                       |✔            |✔            |✔                |
|`KC_MEDIA_SELECT`       |`KC_MSEL`                      |Launch Media Player                    |✔            |             |✔                |
|`KC_MEDIA_EJECT`        |`KC_EJCT`                      |Eject                                  |             |✔            |✔                |
|`KC_MAIL`               |                               |Launch Mail                            |✔            |             |✔                |
|`KC_CALCULATOR`         |`KC_CALC`                      |Launch Calculator                      |✔            |             |✔                |
|`KC_MY_COMPUTER`        |`KC_MYCM`                      |Launch My Computer                     |✔            |             |✔                |
|`KC_WWW_SEARCH`         |`KC_WSCH`                      |Browser Search                         |✔            |             |✔                |
|`KC_WWW_HOME`           |`KC_WHOM`                      |Browser Home                           |✔            |             |✔                |
|`KC_WWW_BACK`           |`KC_WBAK`                      |Browser Back                           |✔            |             |✔                |
|`KC_WWW_FORWARD`        |`KC_WFWD`                      |Browser Forward                        |✔            |             |✔                |
|`KC_WWW_STOP`           |`KC_WSTP`                      |Browser Stop                           |✔            |             |✔                |
|`KC_WWW_REFRESH`        |`KC_WREF`                      |Browser Refresh                        |✔            |             |✔                |
|`KC_WWW_FAVORITES`      |`KC_WFAV`                      |Browser Favorites                      |✔            |             |✔                |
|`KC_MEDIA_FAST_FORWARD` |`KC_MFFD`                      |Next Track                             |✔            |✔<sup>5</sup>|✔                |
|`KC_MEDIA_REWIND`       |`KC_MRWD`                      |Previous Track                         |✔<sup>6</sup>|✔<sup>5</sup>|✔                |
|`KC_BRIGHTNESS_UP`      |`KC_BRIU`                      |Brightness Up                          |✔            |✔            |✔                |
|`KC_BRIGHTNESS_DOWN`    |`KC_BRID`                      |Brightness Down                        |✔            |✔            |✔                |
|`KC_CONTROL_PANEL`      |`KC_CPNL`                      |Open Control Panel                     |✔            |             |                 |
|`KC_ASSISTANT`          |`KC_ASST`                      |Launch Context-Aware Assistant         |✔            |             |                 |
|`KC_MISSION_CONTROL`    |`KC_MCTL`                      |Open Mission Control                   |             |✔            |                 |
|`KC_LAUNCHPAD`          |`KC_LPAD`                      |Open Launchpad                         |             |✔            |                 |

<sup>1. The Linux kernel HID driver recognizes [nearly all keycodes](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-input.c), but the default bindings depend on the DE/WM.</sup><br/>
<sup>2. Treated as F13-F15.</sup><br/>
<sup>3. Must be held for about three seconds, and will display a prompt instead.</sup><br/>
<sup>4. Holding Shift+Option allows for finer control of volume level.</sup><br/>
<sup>5. Skips the entire track in iTunes when tapped, seeks within the current track when held.</sup><br/>
<sup>6. WMP does not recognize the Rewind key, but both alter playback speed in VLC.</sup>

## Quantum Keycodes {#quantum-keycodes}

See also: [Quantum Keycodes](quantum_keycodes#qmk-keycodes)

|Key              |Aliases  |Description                                                                                                                                      |
|-----------------|---------|-------------------------------------------------------------------------------------------------------------------------------------------------|
|`QK_BOOTLOADER`  |`QK_BOOT`|Put the keyboard into bootloader mode for flashing                                                                                               |
|`QK_DEBUG_TOGGLE`|`DB_TOGG`|Toggle debug mode                                                                                                                                |
|`QK_CLEAR_EEPROM`|`EE_CLR` |Reinitializes the keyboard's EEPROM (persistent memory)                                                                                          |
|`QK_MAKE`        |         |Sends `qmk compile -kb (keyboard) -km (keymap)`, or `qmk flash` if shift is held. Puts keyboard into bootloader mode if shift & control are held |
|`QK_REBOOT`      |`QK_RBT` |Resets the keyboard. Does not load the bootloader                                                                                                |

## Audio Keys {#audio-keys}

See also: [Audio](features/audio)

|Key                      |Aliases  |Description                                |
|-------------------------|---------|-------------------------------------------|
|`QK_AUDIO_ON`            |`AU_ON`  |Turns on Audio Feature                     |
|`QK_AUDIO_OFF`           |`AU_OFF` |Turns off Audio Feature                    |
|`QK_AUDIO_TOGGLE`        |`AU_TOGG`|Toggles Audio state                        |
|`QK_AUDIO_CLICKY_TOGGLE` |`CK_TOGG`|Toggles Audio clicky mode                  |
|`QK_AUDIO_CLICKY_ON`     |`CK_ON`  |Turns on Audio clicky mode                 |
|`QK_AUDIO_CLICKY_OFF`    |`CK_OFF` |Turns on Audio clicky mode                 |
|`QK_AUDIO_CLICKY_UP`     |`CK_UP`  |Increases frequency of the clicks          |
|`QK_AUDIO_CLICKY_DOWN`   |`CK_DOWN`|Decreases frequency of the clicks          |
|`QK_AUDIO_CLICKY_RESET`  |`CK_RST` |Resets frequency to default                |
|`QK_MUSIC_ON`            |`MU_ON`  |Turns on Music Mode                        |
|`QK_MUSIC_OFF`           |`MU_OFF` |Turns off Music Mode                       |
|`QK_MUSIC_TOGGLE`        |`MU_TOGG`|Toggles Music Mode                         |
|`QK_MUSIC_MODE_NEXT`     |`MU_NEXT`|Cycles through the music modes             |
|`QK_AUDIO_VOICE_NEXT`    |`AU_NEXT`|Cycles through the audio voices            |
|`QK_AUDIO_VOICE_PREVIOUS`|`AU_PREV`|Cycles through the audio voices in reverse |

## Auto Shift {#auto-shift}

See also: [Auto Shift](features/auto_shift)

|Key                   |Aliases  |Description                                 |
|----------------------|---------|--------------------------------------------|
|`QK_AUTO_SHIFT_DOWN`  |`AS_DOWN`|Lower the Auto Shift timeout variable (down)|
|`QK_AUTO_SHIFT_UP`    |`AS_UP`  |Raise the Auto Shift timeout variable (up)  |
|`QK_AUTO_SHIFT_REPORT`|`AS_RPT` |Report your current Auto Shift timeout value|
|`QK_AUTO_SHIFT_ON`    |`AS_ON`  |Turns on the Auto Shift Function            |
|`QK_AUTO_SHIFT_OFF`   |`AS_OFF` |Turns off the Auto Shift Function           |
|`QK_AUTO_SHIFT_TOGGLE`|`AS_TOGG`|Toggles the state of the Auto Shift feature |

## Autocorrect {#autocorrect}

See also: [Autocorrect](features/autocorrect)

|Key                    |Aliases  |Description                                   |
|-----------------------|---------|----------------------------------------------|
|`QK_AUTOCORRECT_ON`    |`AC_ON`  |Turns on the Autocorrect feature.             |
|`QK_AUTOCORRECT_OFF`   |`AC_OFF` |Turns off the Autocorrect feature.            |
|`QK_AUTOCORRECT_TOGGLE`|`AC_TOGG`|Toggles the status of the Autocorrect feature.|

## Backlighting {#backlighting}

See also: [Backlighting](features/backlight)

| Key                             | Aliases   | Description                         |
|---------------------------------|-----------|-------------------------------------|
| `QK_BACKLIGHT_TOGGLE`           | `BL_TOGG` | Turn the backlight on or off        |
| `QK_BACKLIGHT_STEP`             | `BL_STEP` | Cycle through backlight levels      |
| `QK_BACKLIGHT_ON`               | `BL_ON`   | Set the backlight to max brightness |
| `QK_BACKLIGHT_OFF`              | `BL_OFF`  | Turn the backlight off              |
| `QK_BACKLIGHT_UP`               | `BL_UP`   | Increase the backlight level        |
| `QK_BACKLIGHT_DOWN`             | `BL_DOWN` | Decrease the backlight level        |
| `QK_BACKLIGHT_TOGGLE_BREATHING` | `BL_BRTG` | Toggle backlight breathing          |

## Bluetooth {#bluetooth}

See also: [Bluetooth](features/bluetooth)

|Key                  |Aliases  |Description                                   |
|---------------------|---------|----------------------------------------------|
|`QK_OUTPUT_AUTO`     |`OU_AUTO`|Automatically switch between USB and Bluetooth|
|`QK_OUTPUT_USB`      |`OU_USB` |USB only                                      |
|`QK_OUTPUT_BLUETOOTH`|`OU_BT`  |Bluetooth only                                |

## Caps Word {#caps-word}

See also: [Caps Word](features/caps_word)

|Key                  |Aliases  |Description                   |
|---------------------|---------|------------------------------|
|`QK_CAPS_WORD_TOGGLE`|`CW_TOGG`|Toggles Caps Word             |

## Dynamic Macros {#dynamic-macros}

See also: [Dynamic Macros](features/dynamic_macros)

|Key                              |Aliases  |Description                                       |
|---------------------------------|---------|--------------------------------------------------|
|`QK_DYNAMIC_MACRO_RECORD_START_1`|`DM_REC1`|Start recording Macro 1                           |
|`QK_DYNAMIC_MACRO_RECORD_START_2`|`DM_REC2`|Start recording Macro 2                           |
|`QK_DYNAMIC_MACRO_PLAY_1`        |`DM_PLY1`|Replay Macro 1                                    |
|`QK_DYNAMIC_MACRO_PLAY_2`        |`DM_PLY2`|Replay Macro 2                                    |
|`QK_DYNAMIC_MACRO_RECORD_STOP`   |`DM_RSTP`|Finish the macro that is currently being recorded.|

## Grave Escape {#grave-escape}

See also: [Grave Escape](features/grave_esc)

|Key              |Aliases  |Description                                                       |
|-----------------|---------|------------------------------------------------------------------|
|`QK_GRAVE_ESCAPE`|`QK_GESC`|Escape when pressed, <code>&#96;</code> when Shift or GUI are held|

## Joystick {#joystick}

See also: [Joystick](features/joystick)

|Key                    |Aliases|Description|
|-----------------------|-------|-----------|
|`QK_JOYSTICK_BUTTON_0` |`JS_0` |Button 0   |
|`QK_JOYSTICK_BUTTON_1` |`JS_1` |Button 1   |
|`QK_JOYSTICK_BUTTON_2` |`JS_2` |Button 2   |
|`QK_JOYSTICK_BUTTON_3` |`JS_3` |Button 3   |
|`QK_JOYSTICK_BUTTON_4` |`JS_4` |Button 4   |
|`QK_JOYSTICK_BUTTON_5` |`JS_5` |Button 5   |
|`QK_JOYSTICK_BUTTON_6` |`JS_6` |Button 6   |
|`QK_JOYSTICK_BUTTON_7` |`JS_7` |Button 7   |
|`QK_JOYSTICK_BUTTON_8` |`JS_8` |Button 8   |
|`QK_JOYSTICK_BUTTON_9` |`JS_9` |Button 9   |
|`QK_JOYSTICK_BUTTON_10`|`JS_10`|Button 10  |
|`QK_JOYSTICK_BUTTON_11`|`JS_11`|Button 11  |
|`QK_JOYSTICK_BUTTON_12`|`JS_12`|Button 12  |
|`QK_JOYSTICK_BUTTON_13`|`JS_13`|Button 13  |
|`QK_JOYSTICK_BUTTON_14`|`JS_14`|Button 14  |
|`QK_JOYSTICK_BUTTON_15`|`JS_15`|Button 15  |
|`QK_JOYSTICK_BUTTON_16`|`JS_16`|Button 16  |
|`QK_JOYSTICK_BUTTON_17`|`JS_17`|Button 17  |
|`QK_JOYSTICK_BUTTON_18`|`JS_18`|Button 18  |
|`QK_JOYSTICK_BUTTON_19`|`JS_19`|Button 19  |
|`QK_JOYSTICK_BUTTON_20`|`JS_20`|Button 20  |
|`QK_JOYSTICK_BUTTON_21`|`JS_21`|Button 21  |
|`QK_JOYSTICK_BUTTON_22`|`JS_22`|Button 22  |
|`QK_JOYSTICK_BUTTON_23`|`JS_23`|Button 23  |
|`QK_JOYSTICK_BUTTON_24`|`JS_24`|Button 24  |
|`QK_JOYSTICK_BUTTON_25`|`JS_25`|Button 25  |
|`QK_JOYSTICK_BUTTON_26`|`JS_26`|Button 26  |
|`QK_JOYSTICK_BUTTON_27`|`JS_27`|Button 27  |
|`QK_JOYSTICK_BUTTON_28`|`JS_28`|Button 28  |
|`QK_JOYSTICK_BUTTON_29`|`JS_29`|Button 29  |
|`QK_JOYSTICK_BUTTON_30`|`JS_30`|Button 30  |
|`QK_JOYSTICK_BUTTON_31`|`JS_31`|Button 31  |

## Key Lock {#key-lock}

See also: [Key Lock](features/key_lock)

|Key      |Description                                                   |
|---------|--------------------------------------------------------------|
|`QK_LOCK`|Hold down the next key pressed, until the key is pressed again|

## Layer Switching {#layer-switching}

See also: [Layer Switching](feature_layers#switching-and-toggling-layers)

|Key             |Description                                                                       |
|----------------|----------------------------------------------------------------------------------|
|`DF(layer)`     |Set the base (default) layer                                                      |
|`MO(layer)`     |Momentarily turn on `layer` when pressed (requires `KC_TRNS` on destination layer)|
|`OSL(layer)`    |Momentarily activates `layer` until a key is pressed. See [One Shot Keys](one_shot_keys) for details. |
|`LM(layer, mod)`|Momentarily turn on `layer` (like MO) with `mod` active as well.  Where `mod` is a mods_bit.  Mods can be viewed [here](mod_tap).  Example Implementation: `LM(LAYER_1, MOD_LALT)`|
|`LT(layer, kc)` |Turn on `layer` when held, `kc` when tapped                                       |
|`TG(layer)`     |Toggle `layer` on or off                                                          |
|`TO(layer)`     |Turns on `layer` and turns off all other layers, except the default layer |
|`TT(layer)`     |Normally acts like MO unless it's tapped multiple times, which toggles `layer` on |

## Leader Key {#leader-key}

See also: [Leader Key](features/leader_key)

|Key      |Description             |
|---------|------------------------|
|`QK_LEAD`|Begins a leader sequence|

## LED Matrix {#led-matrix}

See also: [LED Matrix](features/led_matrix)

|Key                            |Aliases  |Description                        |
|-------------------------------|---------|-----------------------------------|
|`QK_LED_MATRIX_ON`             |`LM_ON`  |Turn on LED Matrix                 |
|`QK_LED_MATRIX_OFF`            |`LM_OFF` |Turn off LED Matrix                |
|`QK_LED_MATRIX_TOGGLE`         |`LM_TOGG`|Toggle LED Matrix on or off        |
|`QK_LED_MATRIX_MODE_NEXT`      |`LM_NEXT`|Cycle through animations           |
|`QK_LED_MATRIX_MODE_PREVIOUS`  |`LM_PREV`|Cycle through animations in reverse|
|`QK_LED_MATRIX_BRIGHTNESS_UP`  |`LM_BRIU`|Increase the brightness level      |
|`QK_LED_MATRIX_BRIGHTNESS_DOWN`|`LM_BRID`|Decrease the brightness level      |
|`QK_LED_MATRIX_SPEED_UP`       |`LM_SPDU`|Increase the animation speed       |
|`QK_LED_MATRIX_SPEED_DOWN`     |`LM_SPDD`|Decrease the animation speed       |

## Magic Keycodes {#magic-keycodes}

See also: [Magic Keycodes](keycodes_magic)

|Key                                  |Aliases  |Description                                                               |
|-------------------------------------|---------|--------------------------------------------------------------------------|
|`QK_MAGIC_SWAP_CONTROL_CAPS_LOCK`    |`CL_SWAP`|Swap Caps Lock and Left Control                                           |
|`QK_MAGIC_UNSWAP_CONTROL_CAPS_LOCK`  |`CL_NORM`|Unswap Caps Lock and Left Control                                         |
|`QK_MAGIC_TOGGLE_CONTROL_CAPS_LOCK`  |`CL_TOGG`|Toggle Caps Lock and Left Control swap                                    |
|`QK_MAGIC_CAPS_LOCK_AS_CONTROL_ON`   |`CL_CTRL`|Treat Caps Lock as Control                                                |
|`QK_MAGIC_CAPS_LOCK_AS_CONTROL_OFF`  |`CL_CAPS`|Stop treating Caps Lock as Control                                        |
|`QK_MAGIC_SWAP_ESCAPE_CAPS_LOCK`     |`EC_SWAP`|Swap Caps Lock and Escape                                                 |
|`QK_MAGIC_UNSWAP_ESCAPE_CAPS_LOCK`   |`EC_NORM`|Unswap Caps Lock and Escape                                               |
|`QK_MAGIC_TOGGLE_ESCAPE_CAPS_LOCK`   |`EC_TOGG`|Toggle Caps Lock and Escape swap                                          |
|`QK_MAGIC_SWAP_LCTL_LGUI`            |`CG_LSWP`|Swap Left Control and GUI                                                 |
|`QK_MAGIC_UNSWAP_LCTL_LGUI`          |`CG_LNRM`|Unswap Left Control and GUI                                               |
|`QK_MAGIC_SWAP_RCTL_RGUI`            |`CG_RSWP`|Swap Right Control and GUI                                                |
|`QK_MAGIC_UNSWAP_RCTL_RGUI`          |`CG_RNRM`|Unswap Right Control and GUI                                              |
|`QK_MAGIC_SWAP_CTL_GUI`              |`CG_SWAP`|Swap Control and GUI on both sides                                        |
|`QK_MAGIC_UNSWAP_CTL_GUI`            |`CG_NORM`|Unswap Control and GUI on both sides                                      |
|`QK_MAGIC_TOGGLE_CTL_GUI`            |`CG_TOGG`|Toggle Control and GUI swap on both sides                                 |
|`QK_MAGIC_SWAP_LALT_LGUI`            |`AG_LSWP`|Swap Left Alt and GUI                                                     |
|`QK_MAGIC_UNSWAP_LALT_LGUI`          |`AG_LNRM`|Unswap Left Alt and GUI                                                   |
|`QK_MAGIC_SWAP_RALT_RGUI`            |`AG_RSWP`|Swap Right Alt and GUI                                                    |
|`QK_MAGIC_UNSWAP_RALT_RGUI`          |`AG_RNRM`|Unswap Right Alt and GUI                                                  |
|`QK_MAGIC_SWAP_ALT_GUI`              |`AG_SWAP`|Swap Alt and GUI on both sides                                            |
|`QK_MAGIC_UNSWAP_ALT_GUI`            |`AG_NORM`|Unswap Alt and GUI on both sides                                          |
|`QK_MAGIC_TOGGLE_ALT_GUI`            |`AG_TOGG`|Toggle Alt and GUI swap on both sides                                     |
|`QK_MAGIC_GUI_OFF`                   |`GU_OFF` |Disable the GUI keys                                                      |
|`QK_MAGIC_GUI_ON`                    |`GU_ON`  |Enable the GUI keys                                                       |
|`QK_MAGIC_TOGGLE_GUI`                |`GU_TOGG`|Toggles the status of the GUI keys                                        |
|`QK_MAGIC_SWAP_GRAVE_ESC`            |`GE_SWAP`|Swap <code>&#96;</code> and Escape                                        |
|`QK_MAGIC_UNSWAP_GRAVE_ESC`          |`GE_NORM`|Unswap <code>&#96;</code> and Escape                                      |
|`QK_MAGIC_SWAP_BACKSLASH_BACKSPACE`  |`BS_SWAP`|Swap `\` and Backspace                                                    |
|`QK_MAGIC_UNSWAP_BACKSLASH_BACKSPACE`|`BS_NORM`|Unswap `\` and Backspace                                                  |
|`QK_MAGIC_TOGGLE_BACKSLASH_BACKSPACE`|`BS_TOGG`|Toggle `\` and Backspace swap state                                       |
|`QK_MAGIC_NKRO_ON`                   |`NK_ON`  |Enable N-key rollover                                                     |
|`QK_MAGIC_NKRO_OFF`                  |`NK_OFF` |Disable N-key rollover                                                    |
|`QK_MAGIC_TOGGLE_NKRO`               |`NK_TOGG`|Toggle N-key rollover                                                     |
|`QK_MAGIC_EE_HANDS_LEFT`             |`EH_LEFT`|Set the master half of a split keyboard as the left hand (for `EE_HANDS`) |
|`QK_MAGIC_EE_HANDS_RIGHT`            |`EH_RGHT`|Set the master half of a split keyboard as the right hand (for `EE_HANDS`)|

## MIDI {#midi}

See also: [MIDI](features/midi)

|Key                            |Aliases           |Description                      |
|-------------------------------|------------------|---------------------------------|
|`QK_MIDI_ON`                   |`MI_ON`           |Turn MIDI on                     |
|`QK_MIDI_OFF`                  |`MI_OFF`          |Turn MIDI off                    |
|`QK_MIDI_TOGGLE`               |`MI_TOGG`         |Toggle MIDI enabled              |
|`QK_MIDI_NOTE_C_0`             |`MI_C`            |C octave 0                       |
|`QK_MIDI_NOTE_C_SHARP_0`       |`MI_Cs`, `MI_Db`  |C♯/D♭ octave 0                   |
|`QK_MIDI_NOTE_D_0`             |`MI_D`            |D octave 0                       |
|`QK_MIDI_NOTE_D_SHARP_0`       |`MI_Ds`, `MI_Eb`  |D♯/E♭ octave 0                   |
|`QK_MIDI_NOTE_E_0`             |`MI_E`            |E octave 0                       |
|`QK_MIDI_NOTE_F_0`             |`MI_F`            |F octave 0                       |
|`QK_MIDI_NOTE_F_SHARP_0`       |`MI_Fs`, `MI_Gb`  |F♯/G♭ octave 0                   |
|`QK_MIDI_NOTE_G_0`             |`MI_G`            |G octave 0                       |
|`QK_MIDI_NOTE_G_SHARP_0`       |`MI_Gs`, `MI_Ab`  |G♯/A♭ octave 0                   |
|`QK_MIDI_NOTE_A_0`             |`MI_A`            |A octave 0                       |
|`QK_MIDI_NOTE_A_SHARP_0`       |`MI_As`, `MI_Bb`  |A♯/B♭ octave 0                   |
|`QK_MIDI_NOTE_B_0`             |`MI_B`            |B octave 0                       |
|`QK_MIDI_NOTE_C_1`             |`MI_C1`           |C octave 1                       |
|`QK_MIDI_NOTE_C_SHARP_1`       |`MI_Cs1`, `MI_Db1`|C♯/D♭ octave 1                   |
|`QK_MIDI_NOTE_D_1`             |`MI_D1`           |D octave 1                       |
|`QK_MIDI_NOTE_D_SHARP_1`       |`MI_Ds1`, `MI_Eb1`|D♯/E♭ octave 1                   |
|`QK_MIDI_NOTE_E_1`             |`MI_E1`           |E octave 1                       |
|`QK_MIDI_NOTE_F_1`             |`MI_F1`           |F octave 1                       |
|`QK_MIDI_NOTE_F_SHARP_1`       |`MI_Fs1`, `MI_Gb1`|F♯/G♭ octave 1                   |
|`QK_MIDI_NOTE_G_1`             |`MI_G1`           |G octave 1                       |
|`QK_MIDI_NOTE_G_SHARP_1`       |`MI_Gs1`, `MI_Ab1`|G♯/A♭ octave 1                   |
|`QK_MIDI_NOTE_A_1`             |`MI_A1`           |A octave 1                       |
|`QK_MIDI_NOTE_A_SHARP_1`       |`MI_As1`, `MI_Bb1`|A♯/B♭ octave 1                   |
|`QK_MIDI_NOTE_B_1`             |`MI_B1`           |B octave 1                       |
|`QK_MIDI_NOTE_C_2`             |`MI_C2`           |C octave 2                       |
|`QK_MIDI_NOTE_C_SHARP_2`       |`MI_Cs2`, `MI_Db2`|C♯/D♭ octave 2                   |
|`QK_MIDI_NOTE_D_2`             |`MI_D2`           |D octave 2                       |
|`QK_MIDI_NOTE_D_SHARP_2`       |`MI_Ds2`, `MI_Eb2`|D♯/E♭ octave 2                   |
|`QK_MIDI_NOTE_E_2`             |`MI_E2`           |E octave 2                       |
|`QK_MIDI_NOTE_F_2`             |`MI_F2`           |F octave 2                       |
|`QK_MIDI_NOTE_F_SHARP_2`       |`MI_Fs2`, `MI_Gb2`|F♯/G♭ octave 2                   |
|`QK_MIDI_NOTE_G_2`             |`MI_G2`           |G octave 2                       |
|`QK_MIDI_NOTE_G_SHARP_2`       |`MI_Gs2`, `MI_Ab2`|G♯/A♭ octave 2                   |
|`QK_MIDI_NOTE_A_2`             |`MI_A2`           |A octave 2                       |
|`QK_MIDI_NOTE_A_SHARP_2`       |`MI_As2`, `MI_Bb2`|A♯/B♭ octave 2                   |
|`QK_MIDI_NOTE_B_2`             |`MI_B2`           |B octave 2                       |
|`QK_MIDI_NOTE_C_3`             |`MI_C3`           |C octave 3                       |
|`QK_MIDI_NOTE_C_SHARP_3`       |`MI_Cs3`, `MI_Db3`|C♯/D♭ octave 3                   |
|`QK_MIDI_NOTE_D_3`             |`MI_D3`           |D octave 3                       |
|`QK_MIDI_NOTE_D_SHARP_3`       |`MI_Ds3`, `MI_Eb3`|D♯/E♭ octave 3                   |
|`QK_MIDI_NOTE_E_3`             |`MI_E3`           |E octave 3                       |
|`QK_MIDI_NOTE_F_3`             |`MI_F3`           |F octave 3                       |
|`QK_MIDI_NOTE_F_SHARP_3`       |`MI_Fs3`, `MI_Gb3`|F♯/G♭ octave 3                   |
|`QK_MIDI_NOTE_G_3`             |`MI_G3`           |G octave 3                       |
|`QK_MIDI_NOTE_G_SHARP_3`       |`MI_Gs3`, `MI_Ab3`|G♯/A♭ octave 3                   |
|`QK_MIDI_NOTE_A_3`             |`MI_A3`           |A octave 3                       |
|`QK_MIDI_NOTE_A_SHARP_3`       |`MI_As3`, `MI_Bb3`|A♯/B♭ octave 3                   |
|`QK_MIDI_NOTE_B_3`             |`MI_B3`           |B octave 3                       |
|`QK_MIDI_NOTE_C_4`             |`MI_C4`           |C octave 4                       |
|`QK_MIDI_NOTE_C_SHARP_4`       |`MI_Cs4`, `MI_Db4`|C♯/D♭ octave 4                   |
|`QK_MIDI_NOTE_D_4`             |`MI_D4`           |D octave 4                       |
|`QK_MIDI_NOTE_D_SHARP_4`       |`MI_Ds4`, `MI_Eb4`|D♯/E♭ octave 4                   |
|`QK_MIDI_NOTE_E_4`             |`MI_E4`           |E octave 4                       |
|`QK_MIDI_NOTE_F_4`             |`MI_F4`           |F octave 4                       |
|`QK_MIDI_NOTE_F_SHARP_4`       |`MI_Fs4`, `MI_Gb4`|F♯/G♭ octave 4                   |
|`QK_MIDI_NOTE_G_4`             |`MI_G4`           |G octave 4                       |
|`QK_MIDI_NOTE_G_SHARP_4`       |`MI_Gs4`, `MI_Ab4`|G♯/A♭ octave 4                   |
|`QK_MIDI_NOTE_A_4`             |`MI_A4`           |A octave 4                       |
|`QK_MIDI_NOTE_A_SHARP_4`       |`MI_As4`, `MI_Bb4`|A♯/B♭ octave 4                   |
|`QK_MIDI_NOTE_B_4`             |`MI_B4`           |B octave 4                       |
|`QK_MIDI_NOTE_C_5`             |`MI_C5`           |C octave 5                       |
|`QK_MIDI_NOTE_C_SHARP_5`       |`MI_Cs5`, `MI_Db5`|C♯/D♭ octave 5                   |
|`QK_MIDI_NOTE_D_5`             |`MI_D5`           |D octave 5                       |
|`QK_MIDI_NOTE_D_SHARP_5`       |`MI_Ds5`, `MI_Eb5`|D♯/E♭ octave 5                   |
|`QK_MIDI_NOTE_E_5`             |`MI_E5`           |E octave 5                       |
|`QK_MIDI_NOTE_F_5`             |`MI_F5`           |F octave 5                       |
|`QK_MIDI_NOTE_F_SHARP_5`       |`MI_Fs5`, `MI_Gb5`|F♯/G♭ octave 5                   |
|`QK_MIDI_NOTE_G_5`             |`MI_G5`           |G octave 5                       |
|`QK_MIDI_NOTE_G_SHARP_5`       |`MI_Gs5`, `MI_Ab5`|G♯/A♭ octave 5                   |
|`QK_MIDI_NOTE_A_5`             |`MI_A5`           |A octave 5                       |
|`QK_MIDI_NOTE_A_SHARP_5`       |`MI_As5`, `MI_Bb5`|A♯/B♭ octave 5                   |
|`QK_MIDI_NOTE_B_5`             |`MI_B5`           |B octave 5                       |
|`QK_MIDI_OCTAVE_N2`            |`MI_OCN2`         |Set octave to -2                 |
|`QK_MIDI_OCTAVE_N1`            |`MI_OCN1`         |Set octave to -1                 |
|`QK_MIDI_OCTAVE_0`             |`MI_OC0`          |Set octave to 0                  |
|`QK_MIDI_OCTAVE_1`             |`MI_OC1`          |Set octave to 1                  |
|`QK_MIDI_OCTAVE_2`             |`MI_OC2`          |Set octave to 2                  |
|`QK_MIDI_OCTAVE_3`             |`MI_OC3`          |Set octave to 3                  |
|`QK_MIDI_OCTAVE_4`             |`MI_OC4`          |Set octave to 4                  |
|`QK_MIDI_OCTAVE_5`             |`MI_OC5`          |Set octave to 5                  |
|`QK_MIDI_OCTAVE_6`             |`MI_OC6`          |Set octave to 6                  |
|`QK_MIDI_OCTAVE_7`             |`MI_OC7`          |Set octave to 7                  |
|`QK_MIDI_OCTAVE_DOWN`          |`MI_OCTD`         |Move down an octave              |
|`QK_MIDI_OCTAVE_UP`            |`MI_OCTU`         |Move up an octave                |
|`QK_MIDI_TRANSPOSE_N6`         |`MI_TRN6`         |Set transposition to -6 semitones|
|`QK_MIDI_TRANSPOSE_N5`         |`MI_TRN5`         |Set transposition to -5 semitones|
|`QK_MIDI_TRANSPOSE_N4`         |`MI_TRN4`         |Set transposition to -4 semitones|
|`QK_MIDI_TRANSPOSE_N3`         |`MI_TRN3`         |Set transposition to -3 semitones|
|`QK_MIDI_TRANSPOSE_N2`         |`MI_TRN2`         |Set transposition to -2 semitones|
|`QK_MIDI_TRANSPOSE_N1`         |`MI_TRN1`         |Set transposition to -1 semitone |
|`QK_MIDI_TRANSPOSE_0`          |`MI_TR0`          |No transposition                 |
|`QK_MIDI_TRANSPOSE_1`          |`MI_TR1`          |Set transposition to +1 semitone |
|`QK_MIDI_TRANSPOSE_2`          |`MI_TR2`          |Set transposition to +2 semitones|
|`QK_MIDI_TRANSPOSE_3`          |`MI_TR3`          |Set transposition to +3 semitones|
|`QK_MIDI_TRANSPOSE_4`          |`MI_TR4`          |Set transposition to +4 semitones|
|`QK_MIDI_TRANSPOSE_5`          |`MI_TR5`          |Set transposition to +5 semitones|
|`QK_MIDI_TRANSPOSE_6`          |`MI_TR6`          |Set transposition to +6 semitones|
|`QK_MIDI_TRANSPOSE_DOWN`       |`MI_TRSD`         |Decrease transposition           |
|`QK_MIDI_TRANSPOSE_UP`         |`MI_TRSU`         |Increase transposition           |
|`QK_MIDI_VELOCITY_0`           |`MI_VL0`          |Set velocity to 0                |
|`QK_MIDI_VELOCITY_1`           |`MI_VL1`          |Set velocity to 12               |
|`QK_MIDI_VELOCITY_2`           |`MI_VL2`          |Set velocity to 25               |
|`QK_MIDI_VELOCITY_3`           |`MI_VL3`          |Set velocity to 38               |
|`QK_MIDI_VELOCITY_4`           |`MI_VL4`          |Set velocity to 51               |
|`QK_MIDI_VELOCITY_5`           |`MI_VL5`          |Set velocity to 64               |
|`QK_MIDI_VELOCITY_6`           |`MI_VL6`          |Set velocity to 76               |
|`QK_MIDI_VELOCITY_7`           |`MI_VL7`          |Set velocity to 89               |
|`QK_MIDI_VELOCITY_8`           |`MI_VL8`          |Set velocity to 102              |
|`QK_MIDI_VELOCITY_9`           |`MI_VL9`          |Set velocity to 114              |
|`QK_MIDI_VELOCITY_10`          |`MI_VL10`         |Set velocity to 127              |
|`QK_MIDI_VELOCITY_DOWN`        |`MI_VELD`         |Decrease velocity                |
|`QK_MIDI_VELOCITY_UP`          |`MI_VELU`         |Increase velocity                |
|`QK_MIDI_CHANNEL_1`            |`MI_CH1`          |Set channel to 1                 |
|`QK_MIDI_CHANNEL_2`            |`MI_CH2`          |Set channel to 2                 |
|`QK_MIDI_CHANNEL_3`            |`MI_CH3`          |Set channel to 3                 |
|`QK_MIDI_CHANNEL_4`            |`MI_CH4`          |Set channel to 4                 |
|`QK_MIDI_CHANNEL_5`            |`MI_CH5`          |Set channel to 5                 |
|`QK_MIDI_CHANNEL_6`            |`MI_CH6`          |Set channel to 6                 |
|`QK_MIDI_CHANNEL_7`            |`MI_CH7`          |Set channel to 7                 |
|`QK_MIDI_CHANNEL_8`            |`MI_CH8`          |Set channel to 8                 |
|`QK_MIDI_CHANNEL_9`            |`MI_CH9`          |Set channel to 9                 |
|`QK_MIDI_CHANNEL_10`           |`MI_CH10`         |Set channel to 10                |
|`QK_MIDI_CHANNEL_11`           |`MI_CH11`         |Set channel to 11                |
|`QK_MIDI_CHANNEL_12`           |`MI_CH12`         |Set channel to 12                |
|`QK_MIDI_CHANNEL_13`           |`MI_CH13`         |Set channel to 13                |
|`QK_MIDI_CHANNEL_14`           |`MI_CH14`         |Set channel to 14                |
|`QK_MIDI_CHANNEL_15`           |`MI_CH15`         |Set channel to 15                |
|`QK_MIDI_CHANNEL_16`           |`MI_CH16`         |Set channel to 16                |
|`QK_MIDI_CHANNEL_DOWN`         |`MI_CHND`         |Decrease channel                 |
|`QK_MIDI_CHANNEL_UP`           |`MI_CHNU`         |Increase channel                 |
|`QK_MIDI_ALL_NOTES_OFF`        |`MI_AOFF`         |Stop all notes                   |
|`QK_MIDI_SUSTAIN`              |`MI_SUST`         |Sustain                          |
|`QK_MIDI_PORTAMENTO`           |`MI_PORT`         |Portmento                        |
|`QK_MIDI_SOSTENUTO`            |`MI_SOST`         |Sostenuto                        |
|`QK_MIDI_SOFT`                 |`MI_SOFT`         |Soft Pedal                       |
|`QK_MIDI_LEGATO`               |`MI_LEG`          |Legato                           |
|`QK_MIDI_MODULATION`           |`MI_MOD`          |Modulation                       |
|`QK_MIDI_MODULATION_SPEED_DOWN`|`MI_MODD`         |Decrease modulation speed        |
|`QK_MIDI_MODULATION_SPEED_UP`  |`MI_MODU`         |Increase modulation speed        |
|`QK_MIDI_PITCH_BEND_DOWN`      |`MI_BNDD`         |Bend pitch down                  |
|`QK_MIDI_PITCH_BEND_UP`        |`MI_BNDU`         |Bend pitch up                    |

## Mouse Keys {#mouse-keys}

See also: [Mouse Keys](features/mouse_keys)

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

## Modifiers {#modifiers}

See also: [Modifier Keys](feature_advanced_keycodes#modifier-keys)

|Key       |Aliases                           |Description                                           |
|----------|----------------------------------|------------------------------------------------------|
|`LCTL(kc)`|`C(kc)`                           |Hold Left Control and press `kc`                      |
|`LSFT(kc)`|`S(kc)`                           |Hold Left Shift and press `kc`                        |
|`LALT(kc)`|`A(kc)`, `LOPT(kc)`               |Hold Left Alt and press `kc`                          |
|`LGUI(kc)`|`G(kc)`, `LCMD(kc)`, `LWIN(kc)`   |Hold Left GUI and press `kc`                          |
|`RCTL(kc)`|                                  |Hold Right Control and press `kc`                     |
|`RSFT(kc)`|                                  |Hold Right Shift and press `kc`                       |
|`RALT(kc)`|`ROPT(kc)`, `ALGR(kc)`            |Hold Right Alt (AltGr) and press `kc`                 |
|`RGUI(kc)`|`RCMD(kc)`, `RWIN(kc)`            |Hold Right GUI and press `kc`                         |
|`LSG(kc)` |`SGUI(kc)`, `SCMD(kc)`, `SWIN(kc)`|Hold Left Shift and Left GUI and press `kc`           |
|`LAG(kc)` |                                  |Hold Left Alt and Left GUI and press `kc`             |
|`RSG(kc)` |                                  |Hold Right Shift and Right GUI and press `kc`         |
|`RAG(kc)` |                                  |Hold Right Alt and Right GUI and press `kc`           |
|`LCA(kc)` |                                  |Hold Left Control and Alt and press `kc`              |
|`LSA(kc)` |                                  |Hold Left Shift and Left Alt and press `kc`           |
|`RSA(kc)` |`SAGR(kc)`                        |Hold Right Shift and Right Alt (AltGr) and press `kc` |
|`RCS(kc)` |                                  |Hold Right Control and Right Shift and press `kc`     |
|`LCAG(kc)`|                                  |Hold Left Control, Alt and GUI and press `kc`         |
|`MEH(kc)` |                                  |Hold Left Control, Shift and Alt and press `kc`       |
|`HYPR(kc)`|                                  |Hold Left Control, Shift, Alt and GUI and press `kc`  |
|`KC_MEH`  |                                  |Left Control, Shift and Alt                           |
|`KC_HYPR` |                                  |Left Control, Shift, Alt and GUI                      |

## Mod-Tap Keys {#mod-tap-keys}

See also: [Mod-Tap](mod_tap)

|Key          |Aliases                                                          |Description                                                   |
|-------------|-----------------------------------------------------------------|--------------------------------------------------------------|
|`MT(mod, kc)`|                                                                 |`mod` when held, `kc` when tapped                             |
|`LCTL_T(kc)` |`CTL_T(kc)`                                                      |Left Control when held, `kc` when tapped                      |
|`LSFT_T(kc)` |`SFT_T(kc)`                                                      |Left Shift when held, `kc` when tapped                        |
|`LALT_T(kc)` |`LOPT_T(kc)`, `ALT_T(kc)`, `OPT_T(kc)`                           |Left Alt when held, `kc` when tapped                          |
|`LGUI_T(kc)` |`LCMD_T(kc)`, `LWIN_T(kc)`, `GUI_T(kc)`, `CMD_T(kc)`, `WIN_T(kc)`|Left GUI when held, `kc` when tapped                          |
|`RCTL_T(kc)` |                                                                 |Right Control when held, `kc` when tapped                     |
|`RSFT_T(kc)` |                                                                 |Right Shift when held, `kc` when tapped                       |
|`RALT_T(kc)` |`ROPT_T(kc)`, `ALGR_T(kc)`                                       |Right Alt (AltGr) when held, `kc` when tapped                 |
|`RGUI_T(kc)` |`RCMD_T(kc)`, `RWIN_T(kc)`                                       |Right GUI when held, `kc` when tapped                         |
|`LSG_T(kc)`  |`SGUI_T(kc)`, `SCMD_T(kc)`, `SWIN_T(kc)`                         |Left Shift and GUI when held, `kc` when tapped                |
|`LAG_T(kc)`  |                                                                 |Left Alt and GUI when held, `kc` when tapped                  |
|`RSG_T(kc)`  |                                                                 |Right Shift and GUI when held, `kc` when tapped               |
|`RAG_T(kc)`  |                                                                 |Right Alt and GUI when held, `kc` when tapped                 |
|`LCA_T(kc)`  |                                                                 |Left Control and Alt when held, `kc` when tapped              |
|`LSA_T(kc)`  |                                                                 |Left Shift and Left Alt when held, `kc` when tapped           |
|`RSA_T(kc)`  |`SAGR_T(kc)`                                                     |Right Shift and Right Alt (AltGr) when held, `kc` when tapped |
|`RCS_T(kc)`  |                                                                 |Right Control and Right Shift when held, `kc` when tapped     |
|`LCAG_T(kc)` |                                                                 |Left Control, Alt and GUI when held, `kc` when tapped         |
|`RCAG_T(kc)` |                                                                 |Right Control, Alt and GUI when held, `kc` when tapped        |
|`C_S_T(kc)`  |                                                                 |Left Control and Shift when held, `kc` when tapped            |
|`MEH_T(kc)`  |                                                                 |Left Control, Shift and Alt when held, `kc` when tapped       |
|`HYPR_T(kc)` |`ALL_T(kc)`                                                      |Left Control, Shift, Alt and GUI when held, `kc` when tapped - more info [here](https://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)|

## Tapping Term Keys {#tapping-term-keys}

See also: [Dynamic Tapping Term](tap_hold#dynamic-tapping-term)

| Key                           | Aliases | Description                                                                               |
|-------------------------------|---------|-------------------------------------------------------------------------------------------|
|`QK_DYNAMIC_TAPPING_TERM_PRINT`|`DT_PRNT`| Types the current tapping term, in milliseconds                                           |
|`QK_DYNAMIC_TAPPING_TERM_UP`   |`DT_UP`  | Increases the current tapping term by `DYNAMIC_TAPPING_TERM_INCREMENT`ms (5ms by default) |
|`QK_DYNAMIC_TAPPING_TERM_DOWN` |`DT_DOWN`| Decreases the current tapping term by `DYNAMIC_TAPPING_TERM_INCREMENT`ms (5ms by default) |

## RGB Lighting {#rgb-lighting}

See also: [RGB Lighting](features/rgblight)

|Key                           |Aliases   |Description                                                          |
|------------------------------|----------|---------------------------------------------------------------------|
|`QK_UNDERGLOW_TOGGLE`         |`UG_TOGG` |Toggle RGB lighting on or off                                        |
|`QK_UNDERGLOW_MODE_NEXT`      |`UG_NEXT` |Cycle through modes, reverse direction when Shift is held            |
|`QK_UNDERGLOW_MODE_PREVIOUS`  |`UG_PREV` |Cycle through modes in reverse, forward direction when Shift is held |
|`QK_UNDERGLOW_HUE_UP`         |`UG_HUEU` |Increase hue, decrease hue when Shift is held                        |
|`QK_UNDERGLOW_HUE_DOWN`       |`UG_HUED` |Decrease hue, increase hue when Shift is held                        |
|`QK_UNDERGLOW_SATURATION_UP`  |`UG_SATU` |Increase saturation, decrease saturation when Shift is held          |
|`QK_UNDERGLOW_SATURATION_DOWN`|`UG_SATD` |Decrease saturation, increase saturation when Shift is held          |
|`QK_UNDERGLOW_VALUE_UP`       |`UG_VALU` |Increase value (brightness), decrease value when Shift is held       |
|`QK_UNDERGLOW_VALUE_DOWN`     |`UG_VALD` |Decrease value (brightness), increase value when Shift is held       |
|`QK_UNDERGLOW_SPEED_UP`       |`UG_SPDU` |Increase effect speed (brightness), decrease speed when Shift is held|
|`QK_UNDERGLOW_SPEED_DOWN`     |`UG_SPDD` |Decrease effect speed (brightness), increase speed when Shift is held|
|`RGB_MODE_PLAIN`              |`RGB_M_P `|Static (no animation) mode (deprecated)                              |
|`RGB_MODE_BREATHE`            |`RGB_M_B` |Breathing animation mode (deprecated)                                |
|`RGB_MODE_RAINBOW`            |`RGB_M_R` |Rainbow animation mode (deprecated)                                  |
|`RGB_MODE_SWIRL`              |`RGB_M_SW`|Swirl animation mode (deprecated)                                    |
|`RGB_MODE_SNAKE`              |`RGB_M_SN`|Snake animation mode (deprecated)                                    |
|`RGB_MODE_KNIGHT`             |`RGB_M_K` |"Knight Rider" animation mode (deprecated)                           |
|`RGB_MODE_XMAS`               |`RGB_M_X` |Christmas animation mode (deprecated)                                |
|`RGB_MODE_GRADIENT`           |`RGB_M_G` |Static gradient animation mode (deprecated)                          |
|`RGB_MODE_RGBTEST`            |`RGB_M_T` |Red, Green, Blue test animation mode (deprecated)                    |
|`RGB_MODE_TWINKLE`            |`RGB_M_TW`|Twinkle animation mode (deprecated)                                  |

## RGB Matrix Lighting {#rgb-matrix-lighting}

See also: [RGB Matrix Lighting](features/rgb_matrix)

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

## US ANSI Shifted Symbols {#us-ansi-shifted-symbols}

See also: [US ANSI Shifted Symbols](keycodes_us_ansi_shifted)

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

## One Shot Keys {#one-shot-keys}

See also: [One Shot Keys](one_shot_keys)

|Key                 |Aliases  |Description                       |
|--------------------|---------|----------------------------------|
|`OSM(mod)`          |         |Hold `mod` for one keypress       |
|`OSL(layer)`        |         |Switch to `layer` for one keypress|
|`QK_ONE_SHOT_TOGGLE`|`OS_TOGG`|Toggles One Shot keys status      |
|`QK_ONE_SHOT_ON`    |`OS_ON`  |Turns One Shot keys on            |
|`QK_ONE_SHOT_OFF`   |`OS_OFF` |Turns One Shot keys off           |

## Programmable Button Support {#programmable-button}

See also: [Programmable Button](features/programmable_button)

|Key                        |Aliases|Description           |
|---------------------------|-------|----------------------|
|`QK_PROGRAMMABLE_BUTTON_1` |`PB_1` |Programmable button 1 |
|`QK_PROGRAMMABLE_BUTTON_2` |`PB_2` |Programmable button 2 |
|`QK_PROGRAMMABLE_BUTTON_3` |`PB_3` |Programmable button 3 |
|`QK_PROGRAMMABLE_BUTTON_4` |`PB_4` |Programmable button 4 |
|`QK_PROGRAMMABLE_BUTTON_5` |`PB_5` |Programmable button 5 |
|`QK_PROGRAMMABLE_BUTTON_6` |`PB_6` |Programmable button 6 |
|`QK_PROGRAMMABLE_BUTTON_7` |`PB_7` |Programmable button 7 |
|`QK_PROGRAMMABLE_BUTTON_8` |`PB_8` |Programmable button 8 |
|`QK_PROGRAMMABLE_BUTTON_9` |`PB_9` |Programmable button 9 |
|`QK_PROGRAMMABLE_BUTTON_10`|`PB_10`|Programmable button 10|
|`QK_PROGRAMMABLE_BUTTON_11`|`PB_11`|Programmable button 11|
|`QK_PROGRAMMABLE_BUTTON_12`|`PB_12`|Programmable button 12|
|`QK_PROGRAMMABLE_BUTTON_13`|`PB_13`|Programmable button 13|
|`QK_PROGRAMMABLE_BUTTON_14`|`PB_14`|Programmable button 14|
|`QK_PROGRAMMABLE_BUTTON_15`|`PB_15`|Programmable button 15|
|`QK_PROGRAMMABLE_BUTTON_16`|`PB_16`|Programmable button 16|
|`QK_PROGRAMMABLE_BUTTON_17`|`PB_17`|Programmable button 17|
|`QK_PROGRAMMABLE_BUTTON_18`|`PB_18`|Programmable button 18|
|`QK_PROGRAMMABLE_BUTTON_19`|`PB_19`|Programmable button 19|
|`QK_PROGRAMMABLE_BUTTON_20`|`PB_20`|Programmable button 20|
|`QK_PROGRAMMABLE_BUTTON_21`|`PB_21`|Programmable button 21|
|`QK_PROGRAMMABLE_BUTTON_22`|`PB_22`|Programmable button 22|
|`QK_PROGRAMMABLE_BUTTON_23`|`PB_23`|Programmable button 23|
|`QK_PROGRAMMABLE_BUTTON_24`|`PB_24`|Programmable button 24|
|`QK_PROGRAMMABLE_BUTTON_25`|`PB_25`|Programmable button 25|
|`QK_PROGRAMMABLE_BUTTON_26`|`PB_26`|Programmable button 26|
|`QK_PROGRAMMABLE_BUTTON_27`|`PB_27`|Programmable button 27|
|`QK_PROGRAMMABLE_BUTTON_28`|`PB_28`|Programmable button 28|
|`QK_PROGRAMMABLE_BUTTON_29`|`PB_29`|Programmable button 29|
|`QK_PROGRAMMABLE_BUTTON_30`|`PB_30`|Programmable button 30|
|`QK_PROGRAMMABLE_BUTTON_31`|`PB_31`|Programmable button 31|
|`QK_PROGRAMMABLE_BUTTON_32`|`PB_32`|Programmable button 32|

## Repeat Key {#repeat-key}

See also: [Repeat Key](features/repeat_key)

|Keycode                |Aliases  |Description                          |
|-----------------------|---------|-------------------------------------|
|`QK_REPEAT_KEY`        |`QK_REP` |Repeat the last pressed key          |
|`QK_ALT_REPEAT_KEY`    |`QK_AREP`|Perform alternate of the last key    |

## Space Cadet {#space-cadet}

See also: [Space Cadet](features/space_cadet)

|Key                                           |Aliases  |Description                             |
|----------------------------------------------|---------|----------------------------------------|
|`QK_SPACE_CADET_LEFT_CTRL_PARENTHESIS_OPEN`   |`SC_LCPO`|Left Control when held, `(` when tapped |
|`QK_SPACE_CADET_RIGHT_CTRL_PARENTHESIS_CLOSE` |`SC_RCPC`|Right Control when held, `)` when tapped|
|`QK_SPACE_CADET_LEFT_SHIFT_PARENTHESIS_OPEN`  |`SC_LSPO`|Left Shift when held, `(` when tapped   |
|`QK_SPACE_CADET_RIGHT_SHIFT_PARENTHESIS_CLOSE`|`SC_RSPC`|Right Shift when held, `)` when tapped  |
|`QK_SPACE_CADET_LEFT_ALT_PARENTHESIS_OPEN`    |`SC_LAPO`|Left Alt when held, `(` when tapped     |
|`QK_SPACE_CADET_RIGHT_ALT_PARENTHESIS_CLOSE`  |`SC_RAPC`|Right Alt when held, `)` when tapped    |
|`QK_SPACE_CADET_RIGHT_SHIFT_ENTER`            |`SC_SENT`|Right Shift when held, Enter when tapped|

## Swap Hands {#swap-hands}

See also: [Swap Hands](features/swap_hands)

|Key                          |Aliases  |Description                                         |
|-----------------------------|---------|----------------------------------------------------|
|`SH_T(kc)`                   |         |Momentary swap when held, `kc` when tapped          |
|`QK_SWAP_HANDS_ON`           |`SH_ON`  |Turn on hand swap                                   |
|`QK_SWAP_HANDS_OFF`          |`SH_OFF` |Turn off hand swap                                  |
|`QK_SWAP_HANDS_MOMENTARY_ON` |`SH_MON` |Turn on hand swap while held                        |
|`QK_SWAP_HANDS_MOMENTARY_OFF`|`SH_MOFF`|Turn off hand swap while held                       |
|`QK_SWAP_HANDS_TOGGLE`       |`SH_TOGG`|Toggle hand swap                                    |
|`QK_SWAP_HANDS_TAP_TOGGLE`   |`SH_TT`  |Momentary swap when held, toggle when tapped        |
|`QK_SWAP_HANDS_ONE_SHOT`     |`SH_OS`  |Turn on hand swap while held or until next key press|

## Unicode Support {#unicode-support}

See also: [Unicode Support](features/unicode)

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
