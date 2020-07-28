# Основные коды клавиш

Основной набор кодов клавиш основан на документе [HID Keyboard/Keypad Usage Page (0x07)](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf), за исключением `KC_NO`, `KC_TRNS` и сканкодов диапазона `0xA5-DF`. Подробности см. далее.

## Буквы и цифры

|Код   |Описание|
|------|-----------|
|`KC_A`|`a` и `A`|
|`KC_B`|`b` и `B`|
|`KC_C`|`c` и `C`|
|`KC_D`|`d` и `D`|
|`KC_E`|`e` и `E`|
|`KC_F`|`f` и `F`|
|`KC_G`|`g` и `G`|
|`KC_H`|`h` и `H`|
|`KC_I`|`i` и `I`|
|`KC_J`|`j` и `J`|
|`KC_K`|`k` и `K`|
|`KC_L`|`l` и `L`|
|`KC_M`|`m` и `M`|
|`KC_N`|`n` и `N`|
|`KC_O`|`o` и `O`|
|`KC_P`|`p` и `P`|
|`KC_Q`|`q` и `Q`|
|`KC_R`|`r` и `R`|
|`KC_S`|`s` и `S`|
|`KC_T`|`t` и `T`|
|`KC_U`|`u` и `U`|
|`KC_V`|`v` и `V`|
|`KC_W`|`w` и `W`|
|`KC_X`|`x` и `X`|
|`KC_Y`|`y` и `Y`|
|`KC_Z`|`z` и `Z`|
|`KC_1`|`1` и `!`|
|`KC_2`|`2` и `@`|
|`KC_3`|`3` и `#`|
|`KC_4`|`4` и `$`|
|`KC_5`|`5` и `%`|
|`KC_6`|`6` и `^`|
|`KC_7`|`7` и `&`|
|`KC_8`|`8` и `*`|
|`KC_9`|`9` и `(`|
|`KC_0`|`0` и `)`|

## F-ряд

|Код     |Описание|
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

## Пунктуация

|Код              |Синонимы           |Описание                                    |
|-----------------|-------------------|-----------------------------------------------|
|`KC_ENTER`       |`KC_ENT`           |Return (Enter)                                 |
|`KC_ESCAPE`      |`KC_ESC`           |Escape                                         |
|`KC_BSPACE`      |`KC_BSPC`          |Delete (Backspace)                             |
|`KC_TAB`         |                   |Tab                                            |
|`KC_SPACE`       |`KC_SPC`           |Пробел                                       |
|`KC_MINUS`       |`KC_MINS`          |`-` и `_`                                    |
|`KC_EQUAL`       |`KC_EQL`           |`=` и `+`                                    |
|`KC_LBRACKET`    |`KC_LBRC`          |`[` и `{`                                    |
|`KC_RBRACKET`    |`KC_RBRC`          |`]` и `}`                                    |
|`KC_BSLASH`      |`KC_BSLS`          |`\` и `\|`                                   |
|`KC_NONUS_HASH`  |`KC_NUHS`          |Non-US `#` и `~`                             |
|`KC_SCOLON`      |`KC_SCLN`          |`;` и `:`                                    |
|`KC_QUOTE`       |`KC_QUOT`          |`'` и `"`                                    |
|`KC_GRAVE`       |`KC_GRV`, `KC_ZKHK`|<code>&#96;</code> и `~`, JIS Zenkaku/Hankaku|
|`KC_COMMA`       |`KC_COMM`          |`,` и `<`                                    |
|`KC_DOT`         |                   |`.` и `>`                                    |
|`KC_SLASH`       |`KC_SLSH`          |`/` и `?`                                    |
|`KC_NONUS_BSLASH`|`KC_NUBS`          |Non-US `\` и `\|`                            |

## Lock-клавиши

|Код                |Синонимы            |Описание                            |
|-------------------|--------------------|------------------------------------|
|`KC_CAPSLOCK`      |`KC_CLCK`, `KC_CAPS`|Caps Lock                           |
|`KC_SCROLLLOCK`    |`KC_SLCK`, `KC_BRMD`|Scroll Lock, уменьшение яркости (macOS)|
|`KC_NUMLOCK`       |`KC_NLCK`           |Num Lock и Clear                    |
|`KC_LOCKING_CAPS`  |`KC_LCAP`           |Переключающийся Caps Lock                   |
|`KC_LOCKING_NUM`   |`KC_LNUM`           |Переключающийся Num Lock                    |
|`KC_LOCKING_SCROLL`|`KC_LSCR`           |Переключающийся Scroll Lock                 |

## Модификаторы

|Код        |Синонимы            |Описание                            |
|-----------|--------------------|------------------------------------|
|`KC_LCTRL` |`KC_LCTL`           |Левый Control                        |
|`KC_LSHIFT`|`KC_LSFT`           |Левый Shift                          |
|`KC_LALT`  |`KC_LOPT`           |Левый Alt (Option)                   |
|`KC_LGUI`  |`KC_LCMD`, `KC_LWIN`|Левый GUI (Windows/Command/Meta key) |
|`KC_RCTRL` |`KC_RCTL`           |Правый Control                       |
|`KC_RSHIFT`|`KC_RSFT`           |Правый Shift                         |
|`KC_RALT`  |`KC_ROPT`, `KC_ALGR`|Правый Alt (Option/AltGr)            |
|`KC_RGUI`  |`KC_RCMD`, `KC_RWIN`|Правый GUI (Windows/Command/Meta key)|

## Прочие языковые раскладки

|Код       |Синонимы |Описание             |
|----------|---------|---------------------|
|`KC_INT1` |`KC_RO`  |JIS `\` и `_`        |
|`KC_INT2` |`KC_KANA`|JIS Катакана/Хирагана|
|`KC_INT3` |`KC_JYEN`|JIS `¥` и `\|`       |
|`KC_INT4` |`KC_HENK`|JIS Henkan           |
|`KC_INT5` |`KC_MHEN`|JIS Muhenkan         |
|`KC_INT6` |         |JIS Numpad `,`       |
|`KC_INT7` |         |International 7      |
|`KC_INT8` |         |International 8      |
|`KC_INT9` |         |International 9      |
|`KC_LANG1`|`KC_HAEN`|Хангыль/Английский   |
|`KC_LANG2`|`KC_HANJ`|Ханча                |
|`KC_LANG3`|         |JIS Катакана         |
|`KC_LANG4`|         |JIS Хирагана         |
|`KC_LANG5`|         |JIS Zenkaku/Hankaku  |
|`KC_LANG6`|         |Language 6           |
|`KC_LANG7`|         |Language 7           |
|`KC_LANG8`|         |Language 8           |
|`KC_LANG9`|         |Language 9           |

## Команды

|Код               |Синонимы                      |Описание                      |
|------------------|------------------------------|------------------------------|
|`KC_PSCREEN`      |`KC_PSCR`                     |Print Screen                  |
|`KC_PAUSE`        |`KC_PAUS`, `KC_BRK`, `KC_BRMU`|Pause, увеличение яркости (macOS)  |
|`KC_INSERT`       |`KC_INS`                      |Insert                        |
|`KC_HOME`         |                              |Home                          |
|`KC_PGUP`         |                              |Page Up                       |
|`KC_DELETE`       |`KC_DEL`                      |Forward Delete                |
|`KC_END`          |                              |End                           |
|`KC_PGDOWN`       |`KC_PGDN`                     |Page Down                     |
|`KC_RIGHT`        |`KC_RGHT`                     |стрелка вправо                |
|`KC_LEFT`         |                              |стрелка влево                 |
|`KC_DOWN`         |                              |стрелка вниз                  |
|`KC_UP`           |                              |стрелка вверх                 |
|`KC_APPLICATION`  |`KC_APP`                      |Application (клавиша меню Windows)|
|`KC_POWER`        |                              |System Power (macOS/Linux)    |
|`KC_EXECUTE`      |`KC_EXEC`                     |Execute                       |
|`KC_HELP`         |                              |Help                          |
|`KC_MENU`         |                              |Menu                          |
|`KC_SELECT`       |`KC_SLCT`                     |Select                        |
|`KC_STOP`         |                              |Stop                          |
|`KC_AGAIN`        |`KC_AGIN`                     |Again                         |
|`KC_UNDO`         |                              |Undo                          |
|`KC_CUT`          |                              |Cut                           |
|`KC_COPY`         |                              |Copy                          |
|`KC_PASTE`        |`KC_PSTE`                     |Paste                         |
|`KC_FIND`         |                              |Find                          |
|`KC__MUTE`        |                              |Mute (macOS)                  |
|`KC__VOLUP`       |                              |Volume Up (macOS)             |
|`KC__VOLDOWN`     |                              |Volume Down (macOS)           |
|`KC_ALT_ERASE`    |`KC_ERAS`                     |Alternate Erase               |
|`KC_SYSREQ`       |                              |SysReq/Attention              |
|`KC_CANCEL`       |                              |Cancel                        |
|`KC_CLEAR`        |`KC_CLR`                      |Clear                         |
|`KC_PRIOR`        |                              |Prior                         |
|`KC_RETURN`       |                              |Return                        |
|`KC_SEPARATOR`    |                              |Separator                     |
|`KC_OUT`          |                              |Out                           |
|`KC_OPER`         |                              |Oper                          |
|`KC_CLEAR_AGAIN`  |                              |Clear/Again                   |
|`KC_CRSEL`        |                              |CrSel/Props                   |
|`KC_EXSEL`        |                              |ExSel                         |

## Медиа-клавиши

Эти коды клавиш не являются частью спецификации «Keyboard/Keypad usage». Коды `SYSTEM_` описаны на странице «Generic Desktop», и остальные — на странице «Consumer».

?> Поведение некоторых из этих кодов может отличаться в зависимости от ОС. Например, в macOS коды `KC_MEDIA_FAST_FORWARD`, `KC_MEDIA_REWIND`, `KC_MEDIA_NEXT_TRACK` и `KC_MEDIA_PREV_TRACK` включают перемотку в пределах текущего трека при удержании и переключают на другой трек при одиночном нажатии.

|Key                    |Aliases  |Description                  |
|-----------------------|---------|-----------------------------|
|`KC_SYSTEM_POWER`      |`KC_PWR` |System Power Down            |
|`KC_SYSTEM_SLEEP`      |`KC_SLEP`|System Sleep                 |
|`KC_SYSTEM_WAKE`       |`KC_WAKE`|System Wake                  |
|`KC_AUDIO_MUTE`        |`KC_MUTE`|Mute                         |
|`KC_AUDIO_VOL_UP`      |`KC_VOLU`|Volume Up                    |
|`KC_AUDIO_VOL_DOWN`    |`KC_VOLD`|Volume Down                  |
|`KC_MEDIA_NEXT_TRACK`  |`KC_MNXT`|Next Track                   |
|`KC_MEDIA_PREV_TRACK`  |`KC_MPRV`|Previous Track               |
|`KC_MEDIA_STOP`        |`KC_MSTP`|Stop Track (Windows)         |
|`KC_MEDIA_PLAY_PAUSE`  |`KC_MPLY`|Play/Pause Track             |
|`KC_MEDIA_SELECT`      |`KC_MSEL`|Launch Media Player (Windows)|
|`KC_MEDIA_EJECT`       |`KC_EJCT`|Eject (macOS)                |
|`KC_MAIL`              |         |Launch Mail (Windows)        |
|`KC_CALCULATOR`        |`KC_CALC`|Launch Calculator (Windows)  |
|`KC_MY_COMPUTER`       |`KC_MYCM`|Launch My Computer (Windows) |
|`KC_WWW_SEARCH`        |`KC_WSCH`|Browser Search (Windows)     |
|`KC_WWW_HOME`          |`KC_WHOM`|Browser Home (Windows)       |
|`KC_WWW_BACK`          |`KC_WBAK`|Browser Back (Windows)       |
|`KC_WWW_FORWARD`       |`KC_WFWD`|Browser Forward (Windows)    |
|`KC_WWW_STOP`          |`KC_WSTP`|Browser Stop (Windows)       |
|`KC_WWW_REFRESH`       |`KC_WREF`|Browser Refresh (Windows)    |
|`KC_WWW_FAVORITES`     |`KC_WFAV`|Browser Favorites (Windows)  |
|`KC_MEDIA_FAST_FORWARD`|`KC_MFFD`|Next Track (macOS)           |
|`KC_MEDIA_REWIND`      |`KC_MRWD`|Previous Track (macOS)       |
|`KC_BRIGHTNESS_UP`     |`KC_BRIU`|Brightness Up                |
|`KC_BRIGHTNESS_DOWN`   |`KC_BRID`|Brightness Down              |

## Нампад

|Код                |Синонимы |Описание                      |
|-------------------|---------|------------------------------|
|`KC_KP_SLASH`      |`KC_PSLS`|Нампад `/`                    |
|`KC_KP_ASTERISK`   |`KC_PAST`|Нампад `*`                    |
|`KC_KP_MINUS`      |`KC_PMNS`|Нампад `-`                    |
|`KC_KP_PLUS`       |`KC_PPLS`|Нампад `+`                    |
|`KC_KP_ENTER`      |`KC_PENT`|Нампад Enter                  |
|`KC_KP_1`          |`KC_P1`  |Нампад `1` и End              |
|`KC_KP_2`          |`KC_P2`  |Нампад `2` и стрелка вниз     |
|`KC_KP_3`          |`KC_P3`  |Нампад `3` и Page Down        |
|`KC_KP_4`          |`KC_P4`  |Нампад `4` и стрелка влево    |
|`KC_KP_5`          |`KC_P5`  |Нампад `5`                    |
|`KC_KP_6`          |`KC_P6`  |Нампад `6` и стрелка вправо   |
|`KC_KP_7`          |`KC_P7`  |Нампад `7` и Home             |
|`KC_KP_8`          |`KC_P8`  |Нампад `8` и стрелка вверх    |
|`KC_KP_9`          |`KC_P9`  |Нампад `9` и Page Up          |
|`KC_KP_0`          |`KC_P0`  |Нампад `0` и Insert           |
|`KC_KP_DOT`        |`KC_PDOT`|Нампад `.` и Delete           |
|`KC_KP_EQUAL`      |`KC_PEQL`|Нампад `=`                    |
|`KC_KP_COMMA`      |`KC_PCMM`|Нампад `,`                    |
|`KC_KP_EQUAL_AS400`|         |Нампад `=` для AS/400         |

## Специальные клавиши

В дополнение к нижеперечисленным коды диапазона `0xA5-DF` зарезервированы для внутреннего использования в TMK/QMK.

|Код             |Синонимы            |Описание                               |
|----------------|--------------------|---------------------------------------|
|`KC_NO`         |`XXXXXXX`           |Игнорировать эту клавишу (NOOP)        |
|`KC_TRANSPARENT`|`KC_TRNS`, `_______`|Использовать значение непрозрачной клавиши на слое ниже|
