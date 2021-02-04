# Gambaran Umum Kode Tombol

Ketika mendefinisikan sebuah [tata letak](id/keymap.md), setiap tombol harus memiliki definisi tombol yang valid. Laman ini mendokumentasi simbol simbol yang berhubungan dengan kode tombol yang tersedia pada QMK.

Tabel ini hanya merupakan referensi saja. Tiap grup tombol juga tersambung pada laman yang mendokumentasikan fungsionalitas tombol tersebut secara lebih mendetail.

## Kode Tombol Dasar :id=basic-keycodes

Lihat juga: [Kode Tombol Dasar](id/keycodes_basic.md)

|Tombol                 |Alias                         |Deskripsi                                      |Windows      |macOS        |Linux<sup>1</sup>|
|-----------------------|------------------------------|-----------------------------------------------|-------------|-------------|-----------------|
|`KC_NO`                |`XXXXXXX`                     |Abaikan tombol ini (NOOP)                      |*N/A*        |*N/A*        |*N/A*            |
|`KC_TRANSPARENT`       |`KC_TRNS`, `_______`          |Gunakan tombol non-transparan selanjutnya      |*N/A*        |*N/A*        |*N/A*            |
|`KC_A`                 |                              |`a` dan `A`                                    |✔            |✔            |✔                |
|`KC_B`                 |                              |`b` dan `B`                                    |✔            |✔            |✔                |
|`KC_C`                 |                              |`c` dan `C`                                    |✔            |✔            |✔                |
|`KC_D`                 |                              |`d` dan `D`                                    |✔            |✔            |✔                |
|`KC_E`                 |                              |`e` dan `E`                                    |✔            |✔            |✔                |
|`KC_F`                 |                              |`f` dan `F`                                    |✔            |✔            |✔                |
|`KC_G`                 |                              |`g` dan `G`                                    |✔            |✔            |✔                |
|`KC_H`                 |                              |`h` dan `H`                                    |✔            |✔            |✔                |
|`KC_I`                 |                              |`i` dan `I`                                    |✔            |✔            |✔                |
|`KC_J`                 |                              |`j` dan `J`                                    |✔            |✔            |✔                |
|`KC_K`                 |                              |`k` dan `K`                                    |✔            |✔            |✔                |
|`KC_L`                 |                              |`l` dan `L`                                    |✔            |✔            |✔                |
|`KC_M`                 |                              |`m` dan `M`                                    |✔            |✔            |✔                |
|`KC_N`                 |                              |`n` dan `N`                                    |✔            |✔            |✔                |
|`KC_O`                 |                              |`o` dan `O`                                    |✔            |✔            |✔                |
|`KC_P`                 |                              |`p` dan `P`                                    |✔            |✔            |✔                |
|`KC_Q`                 |                              |`q` dan `Q`                                    |✔            |✔            |✔                |
|`KC_R`                 |                              |`r` dan `R`                                    |✔            |✔            |✔                |
|`KC_S`                 |                              |`s` dan `S`                                    |✔            |✔            |✔                |
|`KC_T`                 |                              |`t` dan `T`                                    |✔            |✔            |✔                |
|`KC_U`                 |                              |`u` dan `U`                                    |✔            |✔            |✔                |
|`KC_V`                 |                              |`v` dan `V`                                    |✔            |✔            |✔                |
|`KC_W`                 |                              |`w` dan `W`                                    |✔            |✔            |✔                |
|`KC_X`                 |                              |`x` dan `X`                                    |✔            |✔            |✔                |
|`KC_Y`                 |                              |`y` dan `Y`                                    |✔            |✔            |✔                |
|`KC_Z`                 |                              |`z` dan `Z`                                    |✔            |✔            |✔                |
|`KC_1`                 |                              |`1` dan `!`                                    |✔            |✔            |✔                |
|`KC_2`                 |                              |`2` dan `@`                                    |✔            |✔            |✔                |
|`KC_3`                 |                              |`3` dan `#`                                    |✔            |✔            |✔                |
|`KC_4`                 |                              |`4` dan `$`                                    |✔            |✔            |✔                |
|`KC_5`                 |                              |`5` dan `%`                                    |✔            |✔            |✔                |
|`KC_6`                 |                              |`6` dan `^`                                    |✔            |✔            |✔                |
|`KC_7`                 |                              |`7` dan `&`                                    |✔            |✔            |✔                |
|`KC_8`                 |                              |`8` dan `*`                                    |✔            |✔            |✔                |
|`KC_9`                 |                              |`9` dan `(`                                    |✔            |✔            |✔                |
|`KC_0`                 |                              |`0` dan `)`                                    |✔            |✔            |✔                |
|`KC_ENTER`             |`KC_ENT`                      |Return (Enter)                                 |✔            |✔            |✔                |
|`KC_ESCAPE`            |`KC_ESC`                      |Escape                                         |✔            |✔            |✔                |
|`KC_BSPACE`            |`KC_BSPC`                     |Delete (Backspace)                             |✔            |✔            |✔                |
|`KC_TAB`               |                              |Tab                                            |✔            |✔            |✔                |
|`KC_SPACE`             |`KC_SPC`                      |Spacebar                                       |✔            |✔            |✔                |
|`KC_MINUS`             |`KC_MINS`                     |`-` dan `_`                                    |✔            |✔            |✔                |
|`KC_EQUAL`             |`KC_EQL`                      |`=` dan `+`                                    |✔            |✔            |✔                |
|`KC_LBRACKET`          |`KC_LBRC`                     |`[` dan `{`                                    |✔            |✔            |✔                |
|`KC_RBRACKET`          |`KC_RBRC`                     |`]` dan `}`                                    |✔            |✔            |✔                |
|`KC_BSLASH`            |`KC_BSLS`                     |`\` dan `\|`                                   |✔            |✔            |✔                |
|`KC_NONUS_HASH`        |`KC_NUHS`                     |Non-US `#` dan `~`                             |✔            |✔            |✔                |
|`KC_SCOLON`            |`KC_SCLN`                     |`;` dan `:`                                    |✔            |✔            |✔                |
|`KC_QUOTE`             |`KC_QUOT`                     |`'` dan `"`                                    |✔            |✔            |✔                |
|`KC_GRAVE`             |`KC_GRV`, `KC_ZKHK`           |<code>&#96;</code> dan `~`, JIS Zenkaku/Hankaku|✔            |✔            |✔                |
|`KC_COMMA`             |`KC_COMM`                     |`,` dan `<`                                    |✔            |✔            |✔                |
|`KC_DOT`               |                              |`.` dan `>`                                    |✔            |✔            |✔                |
|`KC_SLASH`             |`KC_SLSH`                     |`/` dan `?`                                    |✔            |✔            |✔                |
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
|`KC_NUMLOCK`           |`KC_NLCK`                     |Keypad Num Lock dan Clear                      |✔            |✔            |✔                |
|`KC_KP_SLASH`          |`KC_PSLS`                     |Keypad `/`                                     |✔            |✔            |✔                |
|`KC_KP_ASTERISK`       |`KC_PAST`                     |Keypad `*`                                     |✔            |✔            |✔                |
|`KC_KP_MINUS`          |`KC_PMNS`                     |Keypad `-`                                     |✔            |✔            |✔                |
|`KC_KP_PLUS`           |`KC_PPLS`                     |Keypad `+`                                     |✔            |✔            |✔                |
|`KC_KP_ENTER`          |`KC_PENT`                     |Keypad Enter                                   |✔            |✔            |✔                |
|`KC_KP_1`              |`KC_P1`                       |Keypad `1` dan End                             |✔            |✔            |✔                |
|`KC_KP_2`              |`KC_P2`                       |Keypad `2` dan Down Arrow                      |✔            |✔            |✔                |
|`KC_KP_3`              |`KC_P3`                       |Keypad `3` dan Page Down                       |✔            |✔            |✔                |
|`KC_KP_4`              |`KC_P4`                       |Keypad `4` dan Left Arrow                      |✔            |✔            |✔                |
|`KC_KP_5`              |`KC_P5`                       |Keypad `5`                                     |✔            |✔            |✔                |
|`KC_KP_6`              |`KC_P6`                       |Keypad `6` dan Right Arrow                     |✔            |✔            |✔                |
|`KC_KP_7`              |`KC_P7`                       |Keypad `7` dan Home                            |✔            |✔            |✔                |
|`KC_KP_8`              |`KC_P8`                       |Keypad `8` dan Up Arrow                        |✔            |✔            |✔                |
|`KC_KP_9`              |`KC_P9`                       |Keypad `9` dan Page Up                         |✔            |✔            |✔                |
|`KC_KP_0`              |`KC_P0`                       |Keypad `0` dan Insert                          |✔            |✔            |✔                |
|`KC_KP_DOT`            |`KC_PDOT`                     |Keypad `.` dan Delete                          |✔            |✔            |✔                |
|`KC_NONUS_BSLASH`      |`KC_NUBS`                     |Non-US `\` dan `\|`                            |✔            |✔            |✔                |
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
|`KC_EXECUTE`           |`KC_EXEC`                     |Execute                                        |             |             |✔                |
|`KC_HELP`              |                              |Help                                           |             |             |✔                |
|`KC_MENU`              |                              |Menu                                           |             |             |✔                |
|`KC_SELECT`            |`KC_SLCT`                     |Select                                         |             |             |✔                |
|`KC_STOP`              |                              |Stop                                           |             |             |✔                |
|`KC_AGAIN`             |`KC_AGIN`                     |Again                                          |             |             |✔                |
|`KC_UNDO`              |                              |Undo                                           |             |             |✔                |
|`KC_CUT`               |                              |Cut                                            |             |             |✔                |
|`KC_COPY`              |                              |Copy                                           |             |             |✔                |
|`KC_PASTE`             |`KC_PSTE`                     |Paste                                          |             |             |✔                |
|`KC_FIND`              |                              |Find                                           |             |             |✔                |
|`KC__MUTE`             |                              |Mute                                           |             |✔            |✔                |
|`KC__VOLUP`            |                              |Volume Up                                      |             |✔            |✔                |
|`KC__VOLDOWN`          |                              |Volume Down                                    |             |✔            |✔                |
|`KC_LOCKING_CAPS`      |`KC_LCAP`                     |Locking Caps Lock                              |✔            |✔            |                 |
|`KC_LOCKING_NUM`       |`KC_LNUM`                     |Locking Num Lock                               |✔            |✔            |                 |
|`KC_LOCKING_SCROLL`    |`KC_LSCR`                     |Locking Scroll Lock                            |✔            |✔            |                 |
|`KC_KP_COMMA`          |`KC_PCMM`                     |Keypad `,`                                     |             |             |✔                |
|`KC_KP_EQUAL_AS400`    |                              |Keypad `=` on AS/400 keyboards                 |             |             |                 |
|`KC_INT1`              |`KC_RO`                       |JIS `\` dan `_`                                |✔            |             |✔                |
|`KC_INT2`              |`KC_KANA`                     |JIS Katakana/Hiragana                          |✔            |             |✔                |
|`KC_INT3`              |`KC_JYEN`                     |JIS `¥` dan `\|`                               |✔            |             |✔                |
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
|`KC_LCTRL`             |`KC_LCTL`                     |*Control* Kiri                                   |✔            |✔            |✔                |
|`KC_LSHIFT`            |`KC_LSFT`                     |*Shift* Kiri                                     |✔            |✔            |✔                |
|`KC_LALT`              |`KC_LOPT`                     |*Alt* Kiri (Option)                              |✔            |✔            |✔                |
|`KC_LGUI`              |`KC_LCMD`, `KC_LWIN`          |Left GUI (Windows/Commdan/Meta key)            |✔            |✔            |✔                |
|`KC_RCTRL`             |`KC_RCTL`                     |*Control* Kanan                                  |✔            |✔            |✔                |
|`KC_RSHIFT`            |`KC_RSFT`                     |*Shift* Kanan                                    |✔            |✔            |✔                |
|`KC_RALT`              |`KC_ROPT`, `KC_ALGR`          |*Alt* Kanan (Option/AltGr)                       |✔            |✔            |✔                |
|`KC_RGUI`              |`KC_RCMD`, `KC_RWIN`          |Right GUI (Windows/Commdan/Meta key)           |✔            |✔            |✔                |
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

<sup>1. Penggerak HID kernel Linux mengenali [hampir semua kode tombol](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-input.c), namun ikatan bawaan bergantung pada DE/WM.</sup><br/>
<sup>2. Diperlakukan sebagai F13-F15.</sup><br/>
<sup>3. Harus ditahan sekitar tiga detik dan akan menampilkan sebuah pilihan.</sup><br/>
<sup>4. Menahan *Shift+Option* memperkenankan pengendalian tingkat suara yang lebih terukur.</sup><br/>
<sup>5. Skips the entire track in iTunes saat diketuk, seeks within the current track saat ditahan.</sup><br/>
<sup>6. WMP tidak mengenali tombol putar ulang, namun dapat mengubah laju putar pada VLC.</sup>

## Kode Tombol Quantum :id=quantum-keycodes

Juga lihat: [Kode Tombol Quantum](id/quantum_keycodes.md#qmk-keycodes)

|Tombol        |Alias    |Deskripsi                                              |
|--------------|---------|-------------------------------------------------------|
|`RESET`       |         |Memindah papan ketik ke mode *bootloader* untuk *flash*|
|`DEBUG`       |         |Mengalihkan mode pengawakutuan                         |
|`EEPROM_RESET`|`EEP_RST`|Menginisialisasi ulang EEPROM papan ketik              |

## Tombol Audio :id=audio-keys

Lihat juga: [Audio](id/feature_audio.md)

|Tombol          |Alias    |Deskripsi                         |
|----------------|---------|----------------------------------|
|`AU_ON`         |         |Menyalakan fitur audio            |
|`AU_OFF`        |         |Mematikan fitur audio             |
|`AU_TOG`        |         |Memindah status audio             |
|`CLICKY_TOGGLE` |`CK_TOGG`|Memindah mode klik audio          |
|`CLICKY_UP`     |`CK_UP`  |Meningkatkan frekuensi klik       |
|`CLICKY_DOWN`   |`CK_DOWN`|Menurunkan frekuensi klik         |
|`CLICKY_RESET`  |`CK_RST` |Mengatur ulang frekuensi ke bawaan|
|`MU_ON`         |         |Menyalakan mode musik             |
|`MU_OFF`        |         |Mematikan mode musik              |
|`MU_TOG`        |         |Memindah mode musik               |
|`MU_MOD`        |         |Menggilir mode musik              |

## Cahaya Belakang :id=backlighting

Lihat juga: [Cahaya Belakang](id/feature_backlight.md)

|Tombol   |Deskripsi                                 |
|---------|------------------------------------------|
|`BL_TOGG`|Mengalihkan cahaya belakang               |
|`BL_STEP`|Menggilir tingkat keterangan cahaya       |
|`BL_ON`  |Mengatur cahaya ke tingkat paling terang  |
|`BL_OFF` |Mematikan cahaya belakang                 |
|`BL_INC` |Menaikkan tingkat terang cahaya belakang  |
|`BL_DEC` |Menurunkan tingkat terang cahaya belakang |
|`BL_BRTG`|Memindah backlight breathing                |

## Bootmagic :id=bootmagic

Lihat juga: [Bootmagic](id/feature_bootmagic.md)

|Tombol                            |Alias    |Deskripsi                                                                 |
|----------------------------------|---------|--------------------------------------------------------------------------|
|`MAGIC_SWAP_CONTROL_CAPSLOCK`     |`CL_SWAP`|Menukar Caps Lock dan *Control* Kiri                                        |
|`MAGIC_UNSWAP_CONTROL_CAPSLOCK`   |`CL_NORM`|Mengembalikan Caps Lock dan *Control* Kiri                                  |
|`MAGIC_CAPSLOCK_TO_CONTROL`       |`CL_CTRL`|Gunakan Caps Lock as Control                                              |
|`MAGIC_UNCAPSLOCK_TO_CONTROL`     |`CL_CAPS`|Berhenti menganggap Caps Lock as Control                                  |
|`MAGIC_SWAP_LCTL_LGUI`            |`LCG_SWP`|Menukar *Control* Kiri dan GUI                                              |
|`MAGIC_UNSWAP_LCTL_LGUI`          |`LCG_NRM`|Mengembalikan *Control* Kiri dan GUI                                        |
|`MAGIC_SWAP_RCTL_RGUI`            |`RCG_SWP`|Memindah *Control* Kanan dan GUI                                            |
|`MAGIC_UNSWAP_RCTL_RGUI`          |`RCG_NRM`|Mengembalikan *Control* Kanan dan GUI                                       |
|`MAGIC_SWAP_CTL_GUI`              |`CG_SWAP`|Memindah Control dan GUI on both sides                                    |
|`MAGIC_UNSWAP_CTL_GUI`            |`CG_NORM`|Mengembalikan Control dan GUI on both sides                               |
|`MAGIC_TOGGLE_CTL_GUI`            |`CG_TOGG`|Memindah Control dan GUI swap on both sides                               |
|`MAGIC_SWAP_LALT_LGUI`            |`LAG_SWP`|Memindah *Alt* Kiri dan GUI                                                 |
|`MAGIC_UNSWAP_LALT_LGUI`          |`LAG_NRM`|Mengembalikan *Alt* Kiri dan GUI                                            |
|`MAGIC_SWAP_RALT_RGUI`            |`RAG_SWP`|Memindah *Alt* Kanan dan GUI                                                |
|`MAGIC_UNSWAP_RALT_RGUI`          |`RAG_NRM`|Mengembalikan *Alt* Kanan dan GUI                                           |
|`MAGIC_SWAP_ALT_GUI`              |`AG_SWAP`|Memindah Alt dan GUI on both sides                                        |
|`MAGIC_UNSWAP_ALT_GUI`            |`AG_NORM`|Mengembalikan Alt dan GUI on both sides                                   |
|`MAGIC_TOGGLE_ALT_GUI`            |`AG_TOGG`|Memindah Alt dan GUI swap on both sides                                   |
|`MAGIC_NO_GUI`                    |`GUI_OFF`|Disable the GUI keys                                                      |
|`MAGIC_UNNO_GUI`                  |`GUI_ON` |Enable the GUI keys                                                       |
|`MAGIC_SWAP_GRAVE_ESC`            |`GE_SWAP`|Memindah <code>&#96;</code> dan Escape                                    |
|`MAGIC_UNSWAP_GRAVE_ESC`          |`GE_NORM`|Mengembalikan <code>&#96;</code> dan Escape                               |
|`MAGIC_SWAP_BACKSLASH_BACKSPACE`  |`BS_SWAP`|Memindah `\` dan Backspace                                                |
|`MAGIC_UNSWAP_BACKSLASH_BACKSPACE`|`BS_NORM`|Mengembalikan `\` dan Backspace                                           |
|`MAGIC_HOST_NKRO`                 |`NK_ON`  |Menyalakan fungsi N-key rollover                                          |
|`MAGIC_UNHOST_NKRO`               |`NK_OFF` |Mematikan N-key rollover                                                  |
|`MAGIC_TOGGLE_NKRO`               |`NK_TOGG`|Memindah N-key rollover                                                   |
|`MAGIC_EE_HANDS_LEFT`             |`EH_LEFT`|Mengatur *master* dari papan ketik belah pada tangan kiri (for `EE_HANDS`)|
|`MAGIC_EE_HANDS_RIGHT`            |`EH_RGHT`|Mengatur *master* dari papan ketik belah pda tangan kanan (for `EE_HANDS`)|

## Bluetooth :id=bluetooth

Lihat juga: [Bluetooth](id/feature_bluetooth.md)

|Tombol    |Deskripsi                                       |
|----------|------------------------------------------------|
|`OUT_AUTO`|Secara otomatis berpindah dari Bluetooth ke USB |
|`OUT_USB` |USB saja                                        |
|`OUT_BT`  |Bluetooth saja                                  |

## Makro Dinamis :id=dynamic-macros

Lihat juga: [Makro Dinamis](id/feature_dynamic_macros.md)

|Tombol           |Alias    |Deskripsi                                         |
|-----------------|---------|--------------------------------------------------|
|`DYN_REC_START1` |`DM_REC1`|Mulai rekam makro 1                               |
|`DYN_REC_START2` |`DM_REC2`|Mulai rekam makro 2                               |
|`DYN_MACRO_PLAY1`|`DM_PLY1`|Jalankan makro 1                                  |
|`DYN_MACRO_PLAY2`|`DM_PLY2`|Jalankan makro 2                                  |
|`DYN_REC_STOP`   |`DM_RSTP`|Selesai merekam makro yang saat ini.              |

## *Grave Escape* :id=grave-escape

Lihat juga: [*Grave Escape*](id/feature_grave_esc.md)

|Tombol     |Alias    |Deskripsi                                                          |
|-----------|---------|-------------------------------------------------------------------|
|`GRAVE_ESC`|`KC_GESC`|Escape saat ditekan, <code>&#96;</code> saat Shift atau GUI ditahan|

## Tombol Kunci :id=key-lock

Lihat juga: [Tombol Kunci](id/feature_key_lock.md)

|Tombol   |Deskripsi                                                         |
|---------|------------------------------------------------------------------|
|`KC_LOCK`|Tahan tombol yang akan diketuk sampai tombol tersebut diketuk lagi|

## Berpindah *Layer* :id=layer-switching

Lihat juga: [Berpindah *Layer*](id/feature_layers.md#switching-dan-toggling-layers)

|Tombol          |Deskripsi                                                                         |
|----------------|----------------------------------------------------------------------------------|
|`DF(layer)`     |Atur *layer* dasar (bawaan)                                                       |
|`MO(layer)`     |Nyalakan `layer` sementara saat ditekan (membutuhkan `KC_TRNS` pada *layer* tujuan)|
|`OSL(layer)`    |Nyalakan `layer` sementara sampai sebuah tombol ditekan. Lihat [*One Shot Key*](id/one_shot_keys.md) untuk detail|
|`LM(layer, mod)`|Nyalakan `layer` sementara (seperti MO) dengan `mod` juga diaktifkan. Dimana `mod` merupakan `mods_bit`. *Mods* dapat dilihat [disini](id/mod_tap.md)|
|`LT(layer, kc)` |Nyalakan `layer` bila ditahan, `kc` ketika diketuk                                |
|`TG(layer)`     |Mengaktifkan `layer` atau mematikannya                                            |
|`TO(layer)`     |Menyalakan `layer` dan mematikan *layer* lainnya kecuali *layer* bawaan           |
|`TT(layer)`     |Secara umum, berperilaku seperti MO kecuali diketuk beberapa kali, yang mengaktifkan `layer`|

## Leader Key :id=leader-key

Lihat juga: [Tombol *Leader*](id/feature_leader_key.md)

|Tombol   |Deskripsi               |
|---------|------------------------|
|`KC_LEAD`|Mulai urutan *leader*   |

## Tambol Tetikus :id=mouse-keys

Lihat juga: [Tambol Tetikus](id/feature_mouse_keys.md)

|Tombol          |Alias    |Deskripsi                   |
|----------------|---------|----------------------------|
|`KC_MS_UP`      |`KC_MS_U`|Kursor Tetikus Naik         |
|`KC_MS_DOWN`    |`KC_MS_D`|Kursor Tetikus Turun        |
|`KC_MS_LEFT`    |`KC_MS_L`|Kursor Tetikus Kiri         |
|`KC_MS_RIGHT`   |`KC_MS_R`|Kursor Tetikus Kanan        |
|`KC_MS_BTN1`    |`KC_BTN1`|Tombol Tetikus 1            |
|`KC_MS_BTN2`    |`KC_BTN2`|Tombol Tetikus 2            |
|`KC_MS_BTN3`    |`KC_BTN3`|Tombol Tetikus 3            |
|`KC_MS_BTN4`    |`KC_BTN4`|Tombol Tetikus 4            |
|`KC_MS_BTN5`    |`KC_BTN5`|Tombol Tetikus 5            |
|`KC_MS_WH_UP`   |`KC_WH_U`|Gelinding Tetikus Atas      |
|`KC_MS_WH_DOWN` |`KC_WH_D`|Gelinding Tetikus Bawah     |
|`KC_MS_WH_LEFT` |`KC_WH_L`|Gelinding Tetikus Kiri      |
|`KC_MS_WH_RIGHT`|`KC_WH_R`|Gelinding Tetikus Kanan     |
|`KC_MS_ACCEL0`  |`KC_ACL0`|Atur percepatan tetikus ke 0|
|`KC_MS_ACCEL1`  |`KC_ACL1`|Atur percepatan tetikus ke 1|
|`KC_MS_ACCEL2`  |`KC_ACL2`|Atur percepatan tetikus ke 2|

## *Modifier* :id=modifiers

Lihat juga: [Tombol *Modifier*](id/feature_advanced_keycodes.md#modifier-keys)

|Tombol    |Alias                          |Deskripsi                                             |
|----------|-------------------------------|------------------------------------------------------|
|`LCTL(kc)`|`C(kc)`                        |Tahan *Control* Kiri dan tekan `kc`                      |
|`LSFT(kc)`|`S(kc)`                        |Tahan *Shift* Kiri dan tekan `kc`                        |
|`LALT(kc)`|`A(kc)`, `LOPT(kc)`            |Tahan *Alt* Kiri dan tekan `kc`                          |
|`LGUI(kc)`|`G(kc)`, `LCMD(kc)`, `LWIN(kc)`|Tahan Left GUI dan tekan `kc`                          |
|`RCTL(kc)`|                               |Tahan *Control* Kanan dan tekan `kc`                     |
|`RSFT(kc)`|                               |Tahan *Shift* Kanan dan tekan `kc`                       |
|`RALT(kc)`|`ROPT(kc)`, `ALGR(kc)`         |Tahan *Alt* Kanan (AltGr) dan tekan `kc`                 |
|`RGUI(kc)`|`RCMD(kc)`, `LWIN(kc)`         |Tahan Right GUI dan tekan `kc`                         |
|`SGUI(kc)`|`SCMD(kc)`, `SWIN(kc)`         |Tahan *Shift* Kiri dan GUI dan tekan `kc`                |
|`LCA(kc)` |                               |Tahan *Control* Kiri dan Alt dan tekan `kc`              |
|`LSA(kc)` |                               |Tahan *Shift* Kiri dan *Alt* Kiri dan tekan `kc`           |
|`RSA(kc)` |`SAGR(kc)`                     |Tahan *Shift* Kanan dan *Alt* Kanan (AltGr) dan tekan `kc` |
|`RCS(kc)` |                               |Tahan *Control* Kanan dan *Shift* Kanan dan tekan `kc`     |
|`LCAG(kc)`|                               |Tahan *Control* Kiri, Alt dan GUI dan tekan `kc`         |
|`MEH(kc)` |                               |Tahan *Control* Kiri, Shift dan Alt dan tekan `kc`       |
|`HYPR(kc)`|                               |Tahan *Control* Kiri, Shift, Alt dan GUI dan tekan `kc`  |
|`KC_MEH`  |                               |*Control* Kiri, Shift dan Alt                           |
|`KC_HYPR` |                               |*Control* Kiri, Shift, Alt dan GUI                      |

## Tombol Tahan-aketuk :id=mod-tap-keys

Lihat juga: [Tahan-Ketuk](id/mod_tap.md)

|Tombol       |Alias                                                            |Deskripsi                                                     |
|-------------|-----------------------------------------------------------------|--------------------------------------------------------------|
|`MT(mod, kc)`|                                                                 |`mod` saat ditahan, `kc` saat diketuk                             |
|`LCTL_T(kc)` |`CTL_T(kc)`                                                      |*Control* Kiri saat ditahan, `kc` saat diketuk                      |
|`LSFT_T(kc)` |`SFT_T(kc)`                                                      |*Shift* Kiri saat ditahan, `kc` saat diketuk                        |
|`LALT_T(kc)` |`LOPT_T(kc)`, `ALT_T(kc)`, `OPT_T(kc)`                           |*Alt* Kiri saat ditahan, `kc` saat diketuk                          |
|`LGUI_T(kc)` |`LCMD_T(kc)`, `LWIN_T(kc)`, `GUI_T(kc)`, `CMD_T(kc)`, `WIN_T(kc)`|Left GUI saat ditahan, `kc` saat diketuk                          |
|`RCTL_T(kc)` |                                                                 |*Control* Kanan saat ditahan, `kc` saat diketuk                     |
|`RSFT_T(kc)` |                                                                 |*Shift* Kanan saat ditahan, `kc` saat diketuk                       |
|`RALT_T(kc)` |`ROPT_T(kc)`, `ALGR_T(kc)`                                       |*Alt* Kanan (AltGr) saat ditahan, `kc` saat diketuk                 |
|`RGUI_T(kc)` |`RCMD_T(kc)`, `RWIN_T(kc)`                                       |Right GUI saat ditahan, `kc` saat diketuk                         |
|`SGUI_T(kc)` |`SCMD_T(kc)`, `SWIN_T(kc)`                                       |*Shift* Kiri dan GUI saat ditahan, `kc` saat diketuk                |
|`LCA_T(kc)`  |                                                                 |*Control* Kiri dan Alt saat ditahan, `kc` saat diketuk              |
|`LSA_T(kc)`  |                                                                 |*Shift* Kiri dan *Alt* Kiri saat ditahan, `kc` saat diketuk           |
|`RSA_T(kc)`  |`SAGR_T(kc)`                                                     |*Shift* Kanan dan *Alt* Kanan (AltGr) saat ditahan, `kc` saat diketuk |
|`RCS_T(kc)`  |                                                                 |*Control* Kanan dan *Shift* Kanan saat ditahan, `kc` saat diketuk     |
|`LCAG_T(kc)` |                                                                 |*Control* Kiri, Alt dan GUI saat ditahan, `kc` saat diketuk         |
|`RCAG_T(kc)` |                                                                 |*Control* Kanan, Alt dan GUI saat ditahan, `kc` saat diketuk        |
|`C_S_T(kc)`  |                                                                 |*Control* Kiri dan Shift saat ditahan, `kc` saat diketuk            |
|`MEH_T(kc)`  |                                                                 |*Control* Kiri, Shift dan Alt saat ditahan, `kc` saat diketuk       |
|`HYPR_T(kc)` |`ALL_T(kc)`                                                      |*Control* Kiri, Shift, Alt dan GUI saat ditahan, `kc` saat diketuk - more info [here](https://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)|

## RGB Lighting :id=rgb-lighting

Lihat juga: [RGB Lighting](id/feature_rgblight.md)

|Tombol             |Alias     |Deskripsi                                                           |
|-------------------|----------|--------------------------------------------------------------------|
|`RGB_TOG`          |          |Memindah RGB lighting on or off                                       |
|`RGB_MODE_FORWARD` |`RGB_MOD` |Cycle through modes, reverse direction saat *Shift* ditahan           |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|Cycle through modes in reverse, forward direction saat *Shift* ditahan|
|`RGB_HUI`          |          |Meningkatkan hue, menurunkan hue saat *Shift* ditahan                       |
|`RGB_HUD`          |          |Menurunkan hue, meningkatkan hue saat *Shift* ditahan                       |
|`RGB_SAI`          |          |Meningkatkan saturasi, menurunkan saturasi saat *Shift* ditahan         |
|`RGB_SAD`          |          |Menurunkan saturasi, meningkatkan saturasi saat *Shift* ditahan         |
|`RGB_VAI`          |          |Meningkatkan nilai (brightness), menurunkan nilai saat *Shift* ditahan      |
|`RGB_VAD`          |          |Menurunkan nilai (brightness), meningkatkan nilai saat *Shift* ditahan      |
|`RGB_MODE_PLAIN`   |`RGB_M_P `|Mode statis                                          |
|`RGB_MODE_BREATHE` |`RGB_M_B` |Mode nafas                                            |
|`RGB_MODE_RAINBOW` |`RGB_M_R` |Mode animasi pelangi                                              |
|`RGB_MODE_SWIRL`   |`RGB_M_SW`|Mode animasi berputar                                                |
|`RGB_MODE_SNAKE`   |`RGB_M_SN`|Mode animasi ular                                                |
|`RGB_MODE_KNIGHT`  |`RGB_M_K` |Mode animasi "Knight Rider"                                        |
|`RGB_MODE_XMAS`    |`RGB_M_X` |Mode animasi pohon natal                                            |
|`RGB_MODE_GRADIENT`|`RGB_M_G` |Mode animasi gradien statis                                      |
|`RGB_MODE_RGBTEST` |`RGB_M_T` |Mode animasi tes RGB                                  |

## RGB Matrix Lighting :id=rgb-matrix-lighting

Lihat juga: [RGB Matrix Lighting](id/feature_rgb_matrix.md)

|Tombol             |Alias     |Deskripsi                                                                             |
|-------------------|----------|--------------------------------------------------------------------------------------|
|`RGB_TOG`          |          |Memindah RGB lighting on or off                                                         |
|`RGB_MODE_FORWARD` |`RGB_MOD` |Cycle through modes, reverse direction saat *Shift* ditahan                             |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|Cycle through modes in reverse, forward direction saat *Shift* ditahan                  |
|`RGB_HUI`          |          |Meningkatkan hue, menurunkan hue saat *Shift* ditahan                                         |
|`RGB_HUD`          |          |Menurunkan hue, meningkatkan hue saat *Shift* ditahan                                         |
|`RGB_SAI`          |          |Meningkatkan saturasi, menurunkan saturasi saat *Shift* ditahan                           |
|`RGB_SAD`          |          |Menurunkan saturasi, meningkatkan saturasi saat *Shift* ditahan                           |
|`RGB_VAI`          |          |Meningkatkan nilai (brightness), menurunkan nilai saat *Shift* ditahan                        |
|`RGB_VAD`          |          |Menurunkan nilai (brightness), meningkatkan nilai saat *Shift* ditahan                        |
|`RGB_SPI`          |          |Meningkatkan effect speed (belum mendukung eeprom), menurunkan speed saat *Shift* ditahan|
|`RGB_SPD`          |          |Menurunkan effect speed (belum mendukung eeprom), meningkatkan speed saat *Shift* ditahan|

## Printer Thermal :id=thermal-printer

Lihat juga: [Thermal Printer](id/feature_thermal_printer.md)

|Tombol     |Deskripsi                               |
|-----------|----------------------------------------|
|`PRINT_ON` |Mulai cetak apa yang diketik pengguna|
|`PRINT_OFF`|Berhenti cetak apa yang diketik pengguna|

## Simbol US ANSI Tergeser :id=us-ansi-shifted-symbols

Lihat juga: [Simbol US ANSI Tergeser](id/keycodes_us_ansi_shifted.md)

|Tombol                  |Alias              |Deskripsi  |
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

Lihat juga: [One Shot Keys](id/one_shot_keys.md)

|Tombol      |Deskripsi                         |
|------------|------------------------------------------------|
|`OSM(mod)`  |Tahan `mod` untuk satu penekanan tombol         |
|`OSL(layer)`|Berpindah ke `layer` untuk satu penekanan tombol|

## *Space Cadet* :id=space-cadet

Lihat juga: [*Space Cadet*](id/feature_space_cadet.md)

|Tombol     |Deskripsi                               |
|-----------|----------------------------------------|
|`KC_LCPO`  |*Control* Kiri saat ditahan, `(` saat diketuk |
|`KC_RCPC`  |*Control* Kanan saat ditahan, `)` saat diketuk|
|`KC_LSPO`  |*Shift* Kiri saat ditahan, `(` saat diketuk   |
|`KC_RSPC`  |*Shift* Kanan saat ditahan, `)` saat diketuk  |
|`KC_LAPO`  |*Alt* Kiri saat ditahan, `(` saat diketuk     |
|`KC_RAPC`  |*Alt* Kanan saat ditahan, `)` saat diketuk    |
|`KC_SFTENT`|*Shift* Kanan saat ditahan, Enter saat diketuk|

## Memindah Tangan :id=swap-hdans

Lihat juga: [Memindah Tangan](id/feature_swap_hands.md)

|Tombol     |Deskripsi                                                                |
|-----------|-------------------------------------------------------------------------|
|`SH_T(key)`|Sends `key` with a tap; momentary swap saat ditahan.                        |
|`SW_ON`    |Turns on swapping dan leaves it on.                                      |
|`SW_OFF`   |Turn off swapping dan leaves it off. Good for returning to a known state.|
|`SH_MON`   |Memindahs hdans when pressed, returns to normal when released (momentary).   |
|`SH_MOFF`  |Momentarily turns off swap.                                              |
|`SH_TG`    |Memindahs swap on dan off with every key press.                            |
|`SH_TT`    |Memindahs with a tap; momentary saat ditahan.                                 |
|`SH_OS`    |One shot swap hdans: toggle while pressed or until next key press.       |

## Dukungan Unicode :id=unicode-support

Lihat juga: [Dukungan Unicode](id/feature_unicode.md)

|Tombol                |Alias    |Deskripsi                                                       |
|----------------------|---------|----------------------------------------------------------------|
|`UC(c)`               |         |Kirim kode poin Unicode `c`                                     |
|`X(i)`                |         |Kirim kode poin Unicode pada indeks `i` di `unicode_map`           |
|`XP(i, j)`            |         |Kirim kode poin Unicode pada indeks `i`, atau `j` bila Shift/Caps menyala|
|`UNICODE_MODE_FORWARD`|`UC_MOD` |Cycle through selected input modes                              |
|`UNICODE_MODE_REVERSE`|`UC_RMOD`|Cycle through selected input modes in reverse                   |
|`UNICODE_MODE_MAC`    |`UC_M_MA`|Berpindah ke masukan macOS                                           |
|`UNICODE_MODE_LNX`    |`UC_M_LN`|Berpindah ke masukan Linux                                           |
|`UNICODE_MODE_WIN`    |`UC_M_WI`|Berpindah ke masukan Windows                                         |
|`UNICODE_MODE_BSD`    |`UC_M_BS`|Berpindah ke masukan BSD (tidak diimplementasikan)                           |
|`UNICODE_MODE_WINC`   |`UC_M_WC`|Berpindah ke masukan Windows menggunakan WinCompose                        |
