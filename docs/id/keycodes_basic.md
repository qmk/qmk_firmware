# Kode Tombol Dasar

Kode tombol dasar yang didasrkan pada [*HID Keyboard/Keypad Usage Page (0x07)*](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf) dengan pengecualian `KC_NO`, `KC_TRNS`, dan kode tombol pada rentang `0xA5-DF`. Lihat dibawah untuk detail lebih lanjut.

## Huruf dan Angka

|Tombol|Deskripsi  |
|------|-----------|
|`KC_A`|`a` dan `A`|
|`KC_B`|`b` dan `B`|
|`KC_C`|`c` dan `C`|
|`KC_D`|`d` dan `D`|
|`KC_E`|`e` dan `E`|
|`KC_F`|`f` dan `F`|
|`KC_G`|`g` dan `G`|
|`KC_H`|`h` dan `H`|
|`KC_I`|`i` dan `I`|
|`KC_J`|`j` dan `J`|
|`KC_K`|`k` dan `K`|
|`KC_L`|`l` dan `L`|
|`KC_M`|`m` dan `M`|
|`KC_N`|`n` dan `N`|
|`KC_O`|`o` dan `O`|
|`KC_P`|`p` dan `P`|
|`KC_Q`|`q` dan `Q`|
|`KC_R`|`r` dan `R`|
|`KC_S`|`s` dan `S`|
|`KC_T`|`t` dan `T`|
|`KC_U`|`u` dan `U`|
|`KC_V`|`v` dan `V`|
|`KC_W`|`w` dan `W`|
|`KC_X`|`x` dan `X`|
|`KC_Y`|`y` dan `Y`|
|`KC_Z`|`z` dan `Z`|
|`KC_1`|`1` dan `!`|
|`KC_2`|`2` dan `@`|
|`KC_3`|`3` dan `#`|
|`KC_4`|`4` dan `$`|
|`KC_5`|`5` dan `%`|
|`KC_6`|`6` dan `^`|
|`KC_7`|`7` dan `&`|
|`KC_8`|`8` dan `*`|
|`KC_9`|`9` dan `(`|
|`KC_0`|`0` dan `)`|

## Tombol F

|Tombol  |Deskripsi  |
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

## Tanda Baca

|Tombol           |Alias              |Deskripsi                                      |
|-----------------|-------------------|-----------------------------------------------|
|`KC_ENTER`       |`KC_ENT`           |Return (Enter)                                 |
|`KC_ESCAPE`      |`KC_ESC`           |Escape                                         |
|`KC_BSPACE`      |`KC_BSPC`          |Delete (Backspace)                             |
|`KC_TAB`         |                   |Tab                                            |
|`KC_SPACE`       |`KC_SPC`           |Spacebar                                       |
|`KC_MINUS`       |`KC_MINS`          |`-` dan `_`                                    |
|`KC_EQUAL`       |`KC_EQL`           |`=` dan `+`                                    |
|`KC_LBRACKET`    |`KC_LBRC`          |`[` dan `{`                                    |
|`KC_RBRACKET`    |`KC_RBRC`          |`]` dan `}`                                    |
|`KC_BSLASH`      |`KC_BSLS`          |`\` dan `\|`                                   |
|`KC_NONUS_HASH`  |`KC_NUHS`          |Non-US `#` dan `~`                             |
|`KC_SCOLON`      |`KC_SCLN`          |`;` dan `:`                                    |
|`KC_QUOTE`       |`KC_QUOT`          |`'` dan `"`                                    |
|`KC_GRAVE`       |`KC_GRV`, `KC_ZKHK`|<code>&#96;</code> dan `~`, JIS Zenkaku/Hankaku|
|`KC_COMMA`       |`KC_COMM`          |`,` dan `<`                                    |
|`KC_DOT`         |                   |`.` dan `>`                                    |
|`KC_SLASH`       |`KC_SLSH`          |`/` dan `?`                                    |
|`KC_NONUS_BSLASH`|`KC_NUBS`          |Non-US `\` dan `\|`                            |

## Lock Keys

|Tombol             |Alias               |Deskripsi                           |
|-------------------|--------------------|------------------------------------|
|`KC_CAPSLOCK`      |`KC_CLCK`, `KC_CAPS`|Caps Lock                           |
|`KC_SCROLLLOCK`    |`KC_SLCK`, `KC_BRMD`|Scroll Lock, Brightness Down (macOS)|
|`KC_NUMLOCK`       |`KC_NLCK`           |Keypad Num Lock dan Clear           |
|`KC_LOCKING_CAPS`  |`KC_LCAP`           |Locking Caps Lock                   |
|`KC_LOCKING_NUM`   |`KC_LNUM`           |Locking Num Lock                    |
|`KC_LOCKING_SCROLL`|`KC_LSCR`           |Locking Scroll Lock                 |

## *Modifier*

|Tombol     |Alias               |Deskripsi                           |
|-----------|--------------------|------------------------------------|
|`KC_LCTRL` |`KC_LCTL`           |*Control* Kiri                        |
|`KC_LSHIFT`|`KC_LSFT`           |*Shift* Kiri                          |
|`KC_LALT`  |`KC_LOPT`           |*Alt* Kiri (Option)                   |
|`KC_LGUI`  |`KC_LCMD`, `KC_LWIN`|*GUI* Kiri (Windows/Commdan/Meta key) |
|`KC_RCTRL` |`KC_RCTL`           |*Control* Kanan                       |
|`KC_RSHIFT`|`KC_RSFT`           |*Shift* Kanan                         |
|`KC_RALT`  |`KC_ROPT`, `KC_ALGR`|*Alt* Kanan (Option/AltGr)            |
|`KC_RGUI`  |`KC_RCMD`, `KC_RWIN`|*GUI* Kanan (Windows/Commdan/Meta key)|

## International

|Tombol    |Alias    |Deskripsi            |
|----------|---------|---------------------|
|`KC_INT1` |`KC_RO`  |JIS `\` dan `_`      |
|`KC_INT2` |`KC_KANA`|JIS Katakana/Hiragana|
|`KC_INT3` |`KC_JYEN`|JIS `¥` dan `\|`     |
|`KC_INT4` |`KC_HENK`|JIS Henkan           |
|`KC_INT5` |`KC_MHEN`|JIS Muhenkan         |
|`KC_INT6` |         |JIS Numpad `,`       |
|`KC_INT7` |         |International 7      |
|`KC_INT8` |         |International 8      |
|`KC_INT9` |         |International 9      |
|`KC_LANG1`|`KC_HAEN`|Hangul/English       |
|`KC_LANG2`|`KC_HANJ`|Hanja                |
|`KC_LANG3`|         |JIS Katakana         |
|`KC_LANG4`|         |JIS Hiragana         |
|`KC_LANG5`|         |JIS Zenkaku/Hankaku  |
|`KC_LANG6`|         |Language 6           |
|`KC_LANG7`|         |Language 7           |
|`KC_LANG8`|         |Language 8           |
|`KC_LANG9`|         |Language 9           |

## *Commands*

|Tombol            |Alias                         |Deskripsi                             |
|------------------|------------------------------|--------------------------------------|
|`KC_PSCREEN`      |`KC_PSCR`                     |Print Screen                          |
|`KC_PAUSE`        |`KC_PAUS`, `KC_BRK`, `KC_BRMU`|Pause, Brightness Up (macOS)          |
|`KC_INSERT`       |`KC_INS`                      |Insert                                |
|`KC_HOME`         |                              |Home                                  |
|`KC_PGUP`         |                              |Page Up                               |
|`KC_DELETE`       |`KC_DEL`                      |Forward Delete                        |
|`KC_END`          |                              |End                                   |
|`KC_PGDOWN`       |`KC_PGDN`                     |Page Down                             |
|`KC_RIGHT`        |`KC_RGHT`                     |Right Arrow                           |
|`KC_LEFT`         |                              |Left Arrow                            |
|`KC_DOWN`         |                              |Down Arrow                            |
|`KC_UP`           |                              |Up Arrow                              |
|`KC_APPLICATION`  |`KC_APP`                      |Application (Windows Context Menu Key)|
|`KC_POWER`        |                              |System Power                          |
|`KC_EXECUTE`      |`KC_EXEC`                     |Execute                               |
|`KC_HELP`         |                              |Help                                  |
|`KC_MENU`         |                              |Menu                                  |
|`KC_SELECT`       |`KC_SLCT`                     |Select                                |
|`KC_STOP`         |                              |Stop                                  |
|`KC_AGAIN`        |`KC_AGIN`                     |Again                                 |
|`KC_UNDO`         |                              |Undo                                  |
|`KC_CUT`          |                              |Cut                                   |
|`KC_COPY`         |                              |Copy                                  |
|`KC_PASTE`        |`KC_PSTE`                     |Paste                                 |
|`KC_FIND`         |                              |Find                                  |
|`KC__MUTE`        |                              |Mute                                  |
|`KC__VOLUP`       |                              |Volume Up                             |
|`KC__VOLDOWN`     |                              |Volume Down                           |
|`KC_ALT_ERASE`    |`KC_ERAS`                     |Alternate Erase                       |
|`KC_SYSREQ`       |                              |SysReq/Attention                      |
|`KC_CANCEL`       |                              |Cancel                                |
|`KC_CLEAR`        |`KC_CLR`                      |Clear                                 |
|`KC_PRIOR`        |                              |Prior                                 |
|`KC_RETURN`       |                              |Return                                |
|`KC_SEPARATOR`    |                              |Separator                             |
|`KC_OUT`          |                              |Out                                   |
|`KC_OPER`         |                              |Oper                                  |
|`KC_CLEAR_AGAIN`  |                              |Clear/Again                           |
|`KC_CRSEL`        |                              |CrSel/Props                           |
|`KC_EXSEL`        |                              |ExSel                                 |

## Tombol Media

Kode tombol berikut tidak terdapat pada laman penggunaan Keyboard/Keypad. Kode tombol `SYSTEM_` ditemukan pada laman Desktop Generik dan selainnya terdapat pada laman *Consumer*

?> Beberapa kode tombol ini mungkin berperilaku berbeda tergantung pada sistem operasi. Sebagai contoh, pada macOS, kode tombol `KC_MEDIA_FAST_FORWARD`, `KC_MEDIA_REWIND`, `KC_MEDIA_NEXT_TRACK`, dan `KC_MEDIA_PREV_TRACK` melewatkan yang diputar bila ditekan namun melewatkan seluruh daftar putar bila diketuk.

|Tombol                 |Alias    |Deskripsi          |
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

|Tombol             |Alias    |Deskripsi                     |
|-------------------|---------|------------------------------|
|`KC_KP_SLASH`      |`KC_PSLS`|Keypad `/`                    |
|`KC_KP_ASTERISK`   |`KC_PAST`|Keypad `*`                    |
|`KC_KP_MINUS`      |`KC_PMNS`|Keypad `-`                    |
|`KC_KP_PLUS`       |`KC_PPLS`|Keypad `+`                    |
|`KC_KP_ENTER`      |`KC_PENT`|Keypad Enter                  |
|`KC_KP_1`          |`KC_P1`  |Keypad `1` dan End            |
|`KC_KP_2`          |`KC_P2`  |Keypad `2` dan Down Arrow     |
|`KC_KP_3`          |`KC_P3`  |Keypad `3` dan Page Down      |
|`KC_KP_4`          |`KC_P4`  |Keypad `4` dan Left Arrow     |
|`KC_KP_5`          |`KC_P5`  |Keypad `5`                    |
|`KC_KP_6`          |`KC_P6`  |Keypad `6` dan Right Arrow    |
|`KC_KP_7`          |`KC_P7`  |Keypad `7` dan Home           |
|`KC_KP_8`          |`KC_P8`  |Keypad `8` dan Up Arrow       |
|`KC_KP_9`          |`KC_P9`  |Keypad `9` dan Page Up        |
|`KC_KP_0`          |`KC_P0`  |Keypad `0` dan Insert         |
|`KC_KP_DOT`        |`KC_PDOT`|Keypad `.` dan Delete         |
|`KC_KP_EQUAL`      |`KC_PEQL`|Keypad `=`                    |
|`KC_KP_COMMA`      |`KC_PCMM`|Keypad `,`                    |
|`KC_KP_EQUAL_AS400`|         |Keypad `=` on AS/400 keyboards|

## Tombol Khusus

Sebagai tambahan kode tombol berikut, kode tombol pada rentang `0xA5-DF` digunakan sebagai cadangan untuk penggunaan internal.

|Tombol          |Alias               |Deskripsi                              |
|----------------|--------------------|---------------------------------------|
|`KC_NO`         |`XXXXXXX`           |Ignore this key (NOOP)                 |
|`KC_TRANSPARENT`|`KC_TRNS`, `_______`|Use the next lowest non-transparent key|
