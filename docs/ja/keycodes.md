# キーコードの概要

<!---
  original document: 0.11.64:docs/keycodes.md
  git diff 0.11.64 HEAD -- docs/keycodes.md | cat
-->

[キーマップ](ja/keymap.md) を定義するときは、それぞれのキーに有効な定義が必要です。このページは、QMK で使えるキーコードに相当するシンボルについて記述しています。

このページは参照のみです。それぞれのキーの種類毎のリンク先のページに、それぞれのキーの機能についてもっと詳細に記載しています。

## 基本的なキーコード :id=basic-keycodes

[基本的なキーコード](ja/keycodes_basic.md) も見てください。

?> 訳注: 以下の説明は、OS のキーボード配列の設定が「US」の場合のものです。OS のキーボード配列の設定が「JIS」の場合、一部のキーは下の表と異なる文字が入力されます。例えば、`KC_LBRC` は、OS のキーボード配列の設定が US であれば「`[` または `{`」が入力されますが、JIS の場合「`@` または <code>&#96;</code>」が入力されます。
?> これは、OS がキーボードから送信されたキーコードを解釈する際に、キーボード配列の設定によって対応する文字を変えるためです。もし、OS のキーボード配列の設定を JIS にする場合、`#include "keymap_jp.h"` を `keymap.c` に追加すると`JP_AT` のような JIS キーボードのキーキャップに対応したキーを指定できます。

|キー                   |エイリアス                    |説明                                     |Windows      |macOS        |Linux<sup>1</sup>|
|-----------------------|------------------------------|-----------------------------------------|-------------|-------------|-----------------|
|`KC_NO`                |`XXXXXXX`                     |このキーを無視します (何もしません) 。   |*N/A*        |*N/A*        |*N/A*            |
|`KC_TRANSPARENT`       |`KC_TRNS`, `_______`          | 次に低いレイヤーの非透過キーを使う      |*N/A*        |*N/A*        |*N/A*            |
|`KC_A`                 |                              |`a` と `A`                               |✔           |✔            |✔                |
|`KC_B`                 |                              |`b` と `B`                               |✔           |✔            |✔                |
|`KC_C`                 |                              |`c` と `C`                               |✔           |✔            |✔                |
|`KC_D`                 |                              |`d` と `D`                               |✔           |✔            |✔                |
|`KC_E`                 |                              |`e` と `E`                               |✔           |✔            |✔                |
|`KC_F`                 |                              |`f` と `F`                               |✔           |✔            |✔                |
|`KC_G`                 |                              |`g` と `G`                               |✔           |✔            |✔                |
|`KC_H`                 |                              |`h` と `H`                               |✔           |✔            |✔                |
|`KC_I`                 |                              |`i` と `I`                               |✔           |✔            |✔                |
|`KC_J`                 |                              |`j` と `J`                               |✔           |✔            |✔                |
|`KC_K`                 |                              |`k` と `K`                               |✔           |✔            |✔                |
|`KC_L`                 |                              |`l` と `L`                               |✔           |✔            |✔                |
|`KC_M`                 |                              |`m` と `M`                               |✔           |✔            |✔                |
|`KC_N`                 |                              |`n` と `N`                               |✔           |✔            |✔                |
|`KC_O`                 |                              |`o` と `O`                               |✔           |✔            |✔                |
|`KC_P`                 |                              |`p` と `P`                               |✔           |✔            |✔                |
|`KC_Q`                 |                              |`q` と `Q`                               |✔           |✔            |✔                |
|`KC_R`                 |                              |`r` と `R`                               |✔           |✔            |✔                |
|`KC_S`                 |                              |`s` と `S`                               |✔           |✔            |✔                |
|`KC_T`                 |                              |`t` と `T`                               |✔           |✔            |✔                |
|`KC_U`                 |                              |`u` と `U`                               |✔           |✔            |✔                |
|`KC_V`                 |                              |`v` と `V`                               |✔           |✔            |✔                |
|`KC_W`                 |                              |`w` と `W`                               |✔           |✔            |✔                |
|`KC_X`                 |                              |`x` と `X`                               |✔           |✔            |✔                |
|`KC_Y`                 |                              |`y` と `Y`                               |✔           |✔            |✔                |
|`KC_Z`                 |                              |`z` と `Z`                               |✔           |✔            |✔                |
|`KC_1`                 |                              |`1` と `!`                               |✔           |✔            |✔                |
|`KC_2`                 |                              |`2` と `@`                               |✔           |✔            |✔                |
|`KC_3`                 |                              |`3` と `#`                               |✔           |✔            |✔                |
|`KC_4`                 |                              |`4` と `$`                               |✔           |✔            |✔                |
|`KC_5`                 |                              |`5` と `%`                               |✔           |✔            |✔                |
|`KC_6`                 |                              |`6` と `^`                               |✔           |✔            |✔                |
|`KC_7`                 |                              |`7` と `&`                               |✔           |✔            |✔                |
|`KC_8`                 |                              |`8` と `*`                               |✔           |✔            |✔                |
|`KC_9`                 |                              |`9` と `(`                               |✔           |✔            |✔                |
|`KC_0`                 |                              |`0` と `)`                               |✔           |✔            |✔                |
|`KC_ENTER`             |`KC_ENT`                      |Return (Enter)                           |✔           |✔            |✔                |
|`KC_ESCAPE`            |`KC_ESC`                      |Escape                                   |✔           |✔            |✔                |
|`KC_BSPACE`            |`KC_BSPC`                     |Delete (Backspace)                       |✔           |✔            |✔                |
|`KC_TAB`               |                              |Tab                                      |✔           |✔            |✔                |
|`KC_SPACE`             |`KC_SPC`                      |Spacebar                                 |✔           |✔            |✔                |
|`KC_MINUS`             |`KC_MINS`                     |`-` と `_`                               |✔           |✔            |✔                |
|`KC_EQUAL`             |`KC_EQL`                      |`=` と `+`                               |✔           |✔            |✔                |
|`KC_LBRACKET`          |`KC_LBRC`                     |`[` と `{`                               |✔           |✔            |✔                |
|`KC_RBRACKET`          |`KC_RBRC`                     |`]` と `}`                               |✔           |✔            |✔                |
|`KC_BSLASH`            |`KC_BSLS`                     |`\` と `\|`                              |✔           |✔            |✔                |
|`KC_NONUS_HASH`        |`KC_NUHS`                     |Non-US `#` と `~`                       |✔           |✔            |✔                |
|`KC_SCOLON`            |`KC_SCLN`                     |`;` と `:`                               |✔           |✔            |✔                |
|`KC_QUOTE`             |`KC_QUOT`                     |`'` と `"`                               |✔           |✔            |✔                |
|`KC_GRAVE`             |`KC_GRV`, `KC_ZKHK`           |<code>&#96;</code> と `~`, JIS 全角/半角 |✔           |✔            |✔                |
|`KC_COMMA`             |`KC_COMM`                     |`,` と `<`                               |✔           |✔            |✔                |
|`KC_DOT`               |                              |`.` と `>`                               |✔           |✔            |✔                |
|`KC_SLASH`             |`KC_SLSH`                     |`/` と `?`                               |✔           |✔            |✔                |
|`KC_CAPSLOCK`          |`KC_CLCK`, `KC_CAPS`          |Caps Lock                                |✔           |✔            |✔                |
|`KC_F1`                |                              |F1                                       |✔           |✔            |✔                |
|`KC_F2`                |                              |F2                                       |✔           |✔            |✔                |
|`KC_F3`                |                              |F3                                       |✔           |✔            |✔                |
|`KC_F4`                |                              |F4                                       |✔           |✔            |✔                |
|`KC_F5`                |                              |F5                                       |✔           |✔            |✔                |
|`KC_F6`                |                              |F6                                       |✔           |✔            |✔                |
|`KC_F7`                |                              |F7                                       |✔           |✔            |✔                |
|`KC_F8`                |                              |F8                                       |✔           |✔            |✔                |
|`KC_F9`                |                              |F9                                       |✔           |✔            |✔                |
|`KC_F10`               |                              |F10                                      |✔           |✔            |✔                |
|`KC_F11`               |                              |F11                                      |✔           |✔            |✔                |
|`KC_F12`               |                              |F12                                      |✔           |✔            |✔                |
|`KC_PSCREEN`           |`KC_PSCR`                     |Print Screen                             |✔           |✔<sup>2</sup>|✔                |
|`KC_SCROLLLOCK`        |`KC_SLCK`, `KC_BRMD`          |Scroll Lock, 画面の明るさダウン (macOS)  |✔           |✔<sup>2</sup>|✔                |
|`KC_PAUSE`             |`KC_PAUS`, `KC_BRK`, `KC_BRMU`|Pause, 画面の明るさアップ (macOS)        |✔           |✔<sup>2</sup>|✔                |
|`KC_INSERT`            |`KC_INS`                      |Insert                                   |✔           |             |✔                |
|`KC_HOME`              |                              |Home                                     |✔           |✔            |✔                |
|`KC_PGUP`              |                              |Page Up                                  |✔           |✔            |✔                |
|`KC_DELETE`            |`KC_DEL`                      |Forward Delete                           |✔           |✔            |✔                |
|`KC_END`               |                              |End                                      |✔           |✔            |✔                |
|`KC_PGDOWN`            |`KC_PGDN`                     |Page Down                                |✔           |✔            |✔                |
|`KC_RIGHT`             |`KC_RGHT`                     |右矢印                                   |✔           |✔            |✔                |
|`KC_LEFT`              |                              |左矢印                                   |✔           |✔            |✔                |
|`KC_DOWN`              |                              |下矢印                                   |✔           |✔            |✔                |
|`KC_UP`                |                              |上矢印                                   |✔           |✔            |✔                |
|`KC_NUMLOCK`           |`KC_NLCK`                     |テンキー Num Lock と Clear              |✔           |✔            |✔                |
|`KC_KP_SLASH`          |`KC_PSLS`                     |テンキー `/`                             |✔           |✔            |✔                |
|`KC_KP_ASTERISK`       |`KC_PAST`                     |テンキー `*`                             |✔           |✔            |✔                |
|`KC_KP_MINUS`          |`KC_PMNS`                     |テンキー `-`                             |✔           |✔            |✔                |
|`KC_KP_PLUS`           |`KC_PPLS`                     |テンキー `+`                             |✔           |✔            |✔                |
|`KC_KP_ENTER`          |`KC_PENT`                     |テンキー Enter                           |✔           |✔            |✔                |
|`KC_KP_1`              |`KC_P1`                       |テンキー `1` と End                      |✔           |✔            |✔                |
|`KC_KP_2`              |`KC_P2`                       |テンキー `2` と下矢印               |✔           |✔            |✔                |
|`KC_KP_3`              |`KC_P3`                       |テンキー `3` と Page Down                |✔           |✔            |✔                |
|`KC_KP_4`              |`KC_P4`                       |テンキー `4` と左矢印               |✔           |✔            |✔                |
|`KC_KP_5`              |`KC_P5`                       |テンキー `5`                             |✔           |✔            |✔                |
|`KC_KP_6`              |`KC_P6`                       |テンキー `6` と右矢印              |✔           |✔            |✔                |
|`KC_KP_7`              |`KC_P7`                       |テンキー `7` と Home                     |✔           |✔            |✔                |
|`KC_KP_8`              |`KC_P8`                       |テンキー `8` と上矢印                 |✔           |✔            |✔                |
|`KC_KP_9`              |`KC_P9`                       |テンキー `9` と Page Up                  |✔           |✔            |✔                |
|`KC_KP_0`              |`KC_P0`                       |テンキー `0` と Insert                   |✔           |✔            |✔                |
|`KC_KP_DOT`            |`KC_PDOT`                     |テンキー `.` と Delete                   |✔           |✔            |✔                |
|`KC_NONUS_BSLASH`      |`KC_NUBS`                     |Non-US `\` と `\|`                       |✔           |✔            |✔                |
|`KC_APPLICATION`       |`KC_APP`                      |アプリケーションキー (Windows コンテキストメニューキー)  |✔            |             |✔                |
|`KC_POWER`             |                              |システム電源                             |             |✔<sup>3</sup>|✔                |
|`KC_KP_EQUAL`          |`KC_PEQL`                     |テンキー `=`                             |✔           |✔            |✔                |
|`KC_F13`               |                              |F13                                      |✔           |✔            |✔                |
|`KC_F14`               |                              |F14                                      |✔           |✔            |✔                |
|`KC_F15`               |                              |F15                                      |✔           |✔            |✔                |
|`KC_F16`               |                              |F16                                      |✔           |✔            |✔                |
|`KC_F17`               |                              |F17                                      |✔           |✔            |✔                |
|`KC_F18`               |                              |F18                                      |✔           |✔            |✔                |
|`KC_F19`               |                              |F19                                      |✔           |✔            |✔                |
|`KC_F20`               |                              |F20                                      |✔           |             |✔                |
|`KC_F21`               |                              |F21                                      |✔           |             |✔                |
|`KC_F22`               |                              |F22                                      |✔           |             |✔                |
|`KC_F23`               |                              |F23                                      |✔           |             |✔                |
|`KC_F24`               |                              |F24                                      |✔           |             |✔                |
|`KC_EXECUTE`           |`KC_EXEC`                     |Execute                                  |             |             |✔                |
|`KC_HELP`              |                              |Help                                     |             |             |✔                |
|`KC_MENU`              |                              |Menu                                     |             |             |✔                |
|`KC_SELECT`            |`KC_SLCT`                     |Select                                   |             |             |✔                |
|`KC_STOP`              |                              |Stop                                     |             |             |✔                |
|`KC_AGAIN`             |`KC_AGIN`                     |Again                                    |             |             |✔                |
|`KC_UNDO`              |                              |アンドゥ                                 |             |             |✔                |
|`KC_CUT`               |                              |カット                                   |             |             |✔                |
|`KC_COPY`              |                              |コピー                                   |             |             |✔                |
|`KC_PASTE`             |`KC_PSTE`                     |ペースト                                 |             |             |✔                |
|`KC_FIND`              |                              |検索                                     |             |             |✔                |
|`KC__MUTE`             |                              |ミュート                                 |             |✔            |✔                |
|`KC__VOLUP`            |                              |音量アップ                               |             |✔            |✔                |
|`KC__VOLDOWN`          |                              |音量ダウン                               |             |✔            |✔                |
|`KC_LOCKING_CAPS`      |`KC_LCAP`                     |Caps Lock のロック                        |✔           |✔            |                 |
|`KC_LOCKING_NUM`       |`KC_LNUM`                     |Num Lock のロック                         |✔           |✔            |                 |
|`KC_LOCKING_SCROLL`    |`KC_LSCR`                     |Scroll Lock のロック                      |✔           |✔            |                 |
|`KC_KP_COMMA`          |`KC_PCMM`                     |テンキー `,`                             |             |             |✔                |
|`KC_KP_EQUAL_AS400`    |                              |AS/400 キーボードのテンキー `=`          |             |             |                 |
|`KC_INT1`              |`KC_RO`                       |JIS `\` と `_`                           |✔           |             |✔                |
|`KC_INT2`              |`KC_KANA`                     |JIS カタカナ/ひらがな                            |✔           |             |✔                |
|`KC_INT3`              |`KC_JYEN`                     |JIS `¥` と `\|`                          |✔           |             |✔                |
|`KC_INT4`              |`KC_HENK`                     |JIS 変換                                 |✔           |             |✔                |
|`KC_INT5`              |`KC_MHEN`                     |JIS 無変換                               |✔           |             |✔                |
|`KC_INT6`              |                              |JIS テンキー `,`                         |             |             |✔                |
|`KC_INT7`              |                              |International 7                          |             |             |                 |
|`KC_INT8`              |                              |International 8                          |             |             |                 |
|`KC_INT9`              |                              |International 9                          |             |             |                 |
|`KC_LANG1`             |`KC_HAEN`                     |ハングル/英語                            |             |             |✔                |
|`KC_LANG2`             |`KC_HANJ`                     |韓文漢字                                 |             |             |✔                |
|`KC_LANG3`             |                              |JIS カタカナ                             |             |             |✔                |
|`KC_LANG4`             |                              |JIS ひらがな                             |             |             |✔                |
|`KC_LANG5`             |                              |JIS 全角/半角                            |             |             |✔                |
|`KC_LANG6`             |                              |Language 6                               |             |             |                 |
|`KC_LANG7`             |                              |Language 7                               |             |             |                 |
|`KC_LANG8`             |                              |Language 8                               |             |             |                 |
|`KC_LANG9`             |                              |Language 9                               |             |             |                 |
|`KC_ALT_ERASE`         |`KC_ERAS`                     |Alternate Erase                          |             |             |                 |
|`KC_SYSREQ`            |                              |SysReq/Attention                         |             |             |                 |
|`KC_CANCEL`            |                              |Cancel                                   |             |             |                 |
|`KC_CLEAR`             |`KC_CLR`                      |Clear                                    |             |             |✔                |
|`KC_PRIOR`             |                              |Prior                                    |             |             |                 |
|`KC_RETURN`            |                              |Return                                   |             |             |                 |
|`KC_SEPARATOR`         |                              |Separator                                |             |             |                 |
|`KC_OUT`               |                              |Out                                      |             |             |                 |
|`KC_OPER`              |                              |Oper                                     |             |             |                 |
|`KC_CLEAR_AGAIN`       |                              |Clear/Again                              |             |             |                 |
|`KC_CRSEL`             |                              |CrSel/Props                              |             |             |                 |
|`KC_EXSEL`             |                              |ExSel                                    |             |             |                 |
|`KC_LCTRL`             |`KC_LCTL`                     |左 Control                               |✔           |✔            |✔                |
|`KC_LSHIFT`            |`KC_LSFT`                     |左 Shift                                 |✔           |✔            |✔                |
|`KC_LALT`              |`KC_LOPT`                     |左 Alt (Option)                          |✔           |✔            |✔                |
|`KC_LGUI`              |`KC_LCMD`, `KC_LWIN`          |左 GUI (Windows/Command/Meta key)        |✔           |✔            |✔                |
|`KC_RCTRL`             |`KC_RCTL`                     |右 Control                               |✔           |✔            |✔                |
|`KC_RSHIFT`            |`KC_RSFT`                     |右 Shift                                 |✔           |✔            |✔                |
|`KC_RALT`              |`KC_ROPT`, `KC_ALGR`          |右 Alt (Option/AltGr)                    |✔           |✔            |✔                |
|`KC_RGUI`              |`KC_RCMD`, `KC_RWIN`          |右 GUI (Windows/Command/Meta key)        |✔           |✔            |✔                |
|`KC_SYSTEM_POWER`      |`KC_PWR`                      |システム電源オフ                         |✔           |✔<sup>3</sup>|✔                |
|`KC_SYSTEM_SLEEP`      |`KC_SLEP`                     |システムスリープ                         |✔           |✔<sup>3</sup>|✔                |
|`KC_SYSTEM_WAKE`       |`KC_WAKE`                     |システムスリープ解除                     |             |✔<sup>3</sup>|✔                |
|`KC_AUDIO_MUTE`        |`KC_MUTE`                     |ミュート                                 |✔           |✔            |✔                |
|`KC_AUDIO_VOL_UP`      |`KC_VOLU`                     |音量アップ                               |✔           |✔<sup>4</sup>|✔                |
|`KC_AUDIO_VOL_DOWN`    |`KC_VOLD`                     |音量ダウン                               |✔           |✔<sup>4</sup>|✔                |
|`KC_MEDIA_NEXT_TRACK`  |`KC_MNXT`                     |次の曲へ                                 |✔           |✔<sup>5</sup>|✔                |
|`KC_MEDIA_PREV_TRACK`  |`KC_MPRV`                     |前の曲へ                                 |✔           |✔<sup>5</sup>|✔                |
|`KC_MEDIA_STOP`        |`KC_MSTP`                     |再生停止                                 |✔           |             |✔                |
|`KC_MEDIA_PLAY_PAUSE`  |`KC_MPLY`                     |再生/一時停止                            |✔           |✔            |✔                |
|`KC_MEDIA_SELECT`      |`KC_MSEL`                     |Media Player 起動                        |✔           |             |✔                |
|`KC_MEDIA_EJECT`       |`KC_EJCT`                     |イジェクト                               |             |✔            |✔                |
|`KC_MAIL`              |                              |メール起動                               |✔           |             |✔                |
|`KC_CALCULATOR`        |`KC_CALC`                     |電卓起動                                 |✔           |             |✔                |
|`KC_MY_COMPUTER`       |`KC_MYCM`                     |マイコンピュータを開く                   |✔           |             |✔                |
|`KC_WWW_SEARCH`        |`KC_WSCH`                     |ブラウザ検索                             |✔           |             |✔                |
|`KC_WWW_HOME`          |`KC_WHOM`                     |ブラウザホーム画面                       |✔           |             |✔                |
|`KC_WWW_BACK`          |`KC_WBAK`                     |ブラウザ戻る                             |✔           |             |✔                |
|`KC_WWW_FORWARD`       |`KC_WFWD`                     |ブラウザ進む                             |✔           |             |✔                |
|`KC_WWW_STOP`          |`KC_WSTP`                     |ブラウザ読み込み中止                     |✔           |             |✔                |
|`KC_WWW_REFRESH`       |`KC_WREF`                     |ブラウザ再読み込み                       |✔           |             |✔                |
|`KC_WWW_FAVORITES`     |`KC_WFAV`                     |ブラウザお気に入り                       |✔           |             |✔                |
|`KC_MEDIA_FAST_FORWARD`|`KC_MFFD`                     |次の曲へ                                 |✔           |✔<sup>5</sup>|✔                |
|`KC_MEDIA_REWIND`      |`KC_MRWD`                     |前の曲へ                                 |✔<sup>6</sup>|✔<sup>5</sup>|✔                |
|`KC_BRIGHTNESS_UP`     |`KC_BRIU`                     |画面の明るさアップ                       |✔            |✔            |✔                |
|`KC_BRIGHTNESS_DOWN`   |`KC_BRID`                     |画面の明るさダウン                       |✔            |✔            |✔                |

<sup>1. Linux カーネル HID ドライバは [ほぼ全てのキーコード](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-input.c) を識別しますが、デフォルトの関連付けは デスクトップ環境/ウィンドウマネージャによって決まります。</sup><br/>
<sup>2. F13-F15 として取り扱われます。</sup><br/>
<sup>3. 約3秒間押していると、プロンプトが表示されます。</sup><br/>
<sup>4. Shift と Option を押していると、ボリュームレベルの細かいコントロールが可能になります。</sup><br/>
<sup>5. iTunes では、タップすると1曲全体がスキップされます。押していると曲の中で早送り/巻き戻しになります。</sup><br/>
<sup>6. Windows Media Player は巻き戻しキーを識別しませんが、VLC では早送り/巻き戻しキーで再生速度が変更されます。</sup>

## Quantum キーコード :id=quantum-keycodes

[Quantum キーコード](ja/quantum_keycodes.md#qmk-keycodes) も見てください。

|キー          |エイリアス |説明                                                     |
|--------------|-----------|---------------------------------------------------------|
|`RESET`       |           |ファームウエア書き込みのためにキーボードをブートローダーモードにします |
|`DEBUG`       |           |デバッグモードを切り替えます                             |
|`EEPROM_RESET`|`EEP_RST`  |キーボードの EEPROM (不揮発メモリ) を再初期化します      |

## オーディオキー :id=audio-keys

[オーディオ](ja/feature_audio.md) も見てください。

|キー            |エイリアス  |説明                                   |
|----------------|------------|---------------------------------------|
|`AU_ON`         |            |オーディオモードオン                   |
|`AU_OFF`        |            |オーディオモードオフ                   |
|`AU_TOG`        |            |オーディオモードを切り替えます         |
|`CLICKY_TOGGLE` |`CK_TOGG`   |オーディオクリックモードを切り替えます |
|`CLICKY_UP`     |`CK_UP`     |クリック音の周波数を増やします         |
|`CLICKY_DOWN`   |`CK_DOWN`   |クリック音の周波数を減らします         |  
|`CLICKY_RESET`  |`CK_RST`    |周波数をデフォルトに再設定します       |
|`MU_ON`         |            |音楽モードをオンにします               |
|`MU_OFF`        |            |音楽モードをオフにします               |
|`MU_TOG`        |            |音楽モードを切り替えます               |
|`MU_MOD`        |            |音楽モードを循環します                 |

## バックライト :id=backlighting

[バックライト](ja/feature_backlight.md) も見てください。

|キー     |説明                                 |
|---------|-------------------------------------|
|`BL_TOGG`|バックライトをオンあるいはオフにする |
|`BL_STEP`|バックライトレベルを循環する         |
|`BL_ON`  |バックライトを最大輝度にセットする   |
|`BL_OFF` |バックライトをオフにする             |
|`BL_INC` |バックライトのレベルを上げる         |
|`BL_DEC` |バックライトのレベルを下げる         |
|`BL_BRTG`|バックライトの明滅動作を切り替える   |

## ブートマジック :id=bootmagic

[ブートマジック](ja/feature_bootmagic.md) も見てください。

| キー                               | エイリアス| 説明                                                  |
|------------------------------------|-----------|-------------------------------------------------------|
| `MAGIC_SWAP_CONTROL_CAPSLOCK`      | `CL_SWAP` | Caps Lock と左 Control の入れ替え                     |
| `MAGIC_UNSWAP_CONTROL_CAPSLOCK`    | `CL_NORM` | Caps Lock と左 Control の入れ替えの解除               |
| `MAGIC_CAPSLOCK_TO_CONTROL`        | `CL_CTRL` | Caps Lock を Control として扱う                       |
| `MAGIC_UNCAPSLOCK_TO_CONTROL`      | `CL_CAPS` | Caps Lock を Control として扱うことを止める           |
| `MAGIC_SWAP_LCTL_LGUI`             | `LCG_SWP` | 左 Control と GUI の入れ替え                          |
| `MAGIC_UNSWAP_LCTL_LGUI`           | `LCG_NRM` | 左 Control と GUI の入れ替えを解除                    |
| `MAGIC_SWAP_RCTL_RGUI`             | `RCG_SWP` | 右 Control と GUI の入れ替え                          |
| `MAGIC_UNSWAP_RCTL_RGUI`           | `RCG_NRM` | 右 Control と GUI の入れ替えを解除                    |
| `MAGIC_SWAP_CTL_GUI`               | `CG_SWAP` | 両側の Control と GUI の入れ替え                      |
| `MAGIC_UNSWAP_CTL_GUI`             | `CG_NORM` | 両側の Control と GUI の入れ替えを解除                |
| `MAGIC_TOGGLE_CTL_GUI`             | `CG_TOGG` | 両側の Control と GUI の入れ替えの切り替え            |
| `MAGIC_SWAP_LALT_LGUI`             | `LAG_SWP` | 左 Alt と GUI の入れ替え                              |
| `MAGIC_UNSWAP_LALT_LGUI`           | `LAG_NRM` | 左 Alt と GUI の入れ替えを解除                        |
| `MAGIC_SWAP_RALT_RGUI`             | `RAG_SWP` | 右 Alt と GUI の入れ替え                              |
| `MAGIC_UNSWAP_RALT_RGUI`           | `RAG_NRM` | 右 Alt と GUI の入れ替えを解除                        |
| `MAGIC_SWAP_ALT_GUI`               | `AG_SWAP` | 両側の Alt と GUI の入れ替え                          |
| `MAGIC_UNSWAP_ALT_GUI`             | `AG_NORM` | 両側の Alt と GUI の入れ替えを解除                    |
| `MAGIC_TOGGLE_ALT_GUI`             | `AG_TOGG` | 両側の Alt と GUI の入れ替えの切り替え                |
| `MAGIC_NO_GUI`                     | `GUI_OFF` | GUI キーを無効にする                                  |
| `MAGIC_UNNO_GUI`                   | `GUI_ON`  | GUI キーを有効にする                                  |
| `MAGIC_SWAP_GRAVE_ESC`             | `GE_SWAP` | <code>&#96;</code> とエスケープの入れ替え             |
| `MAGIC_UNSWAP_GRAVE_ESC`           | `GE_NORM` | <code>&#96;</code> とエスケープの入れ替えを解除       |
| `MAGIC_SWAP_BACKSLASH_BACKSPACE`   | `BS_SWAP` | `\` と Backspace を入れ替え                           |
| `MAGIC_UNSWAP_BACKSLASH_BACKSPACE` | `BS_NORM` | `\` と Backspace の入れ替えを解除する                 |
| `MAGIC_HOST_NKRO`                  | `NK_ON`   | N キーロールオーバーを有効にする                      |
| `MAGIC_UNHOST_NKRO`                | `NK_OFF`  | N キーロールオーバーを無効にする                      |
| `MAGIC_TOGGLE_NKRO`                | `NK_TOGG` | N キーロールオーバーの有効・無効を切り替え            |
| `MAGIC_EE_HANDS_LEFT`              | `EH_LEFT` | 分割キーボードのマスター側を左手に設定(`EE_HANDS` 用) |
| `MAGIC_EE_HANDS_RIGHT`             | `EH_RGHT` | 分割キーボードのマスター側を右手に設定(`EE_HANDS` 用) |

## Bluetooth :id=bluetooth

[Bluetooth](ja/feature_bluetooth.md) も見てください。


|キー      |説明                                  |
|----------|--------------------------------------|
|`OUT_AUTO`|USB と Bluetooth を自動的に切り替える |
|`OUT_USB` |USB のみ                              |
|`OUT_BT`  |Bluetooth のみ                        |

## 動的マクロ :id=dynamic-macros

[動的マクロ](ja/feature_dynamic_macros.md) も見てください。 

|キー             |エイリアス  |説明                              |
|-----------------|---------|-------------------------------------|
|`DYN_REC_START1` |`DM_REC1`|マクロ 1 の記録を開始します          |
|`DYN_REC_START2` |`DM_REC2`|マクロ 2 の記録を開始します          |
|`DYN_MACRO_PLAY1`|`DM_PLY1`|マクロ 1 を再生します                |
|`DYN_MACRO_PLAY2`|`DM_PLY2`|マクロ 2 を再生します                |
|`DYN_REC_STOP`   |`DM_RSTP`|現在記録中のマクロの記録を終了します |

## グレイブエスケープ :id=grave-escape

[グレイブエスケープ](ja/feature_grave_esc.md) も見てください。

|キー       |エイリアス  |説明                                                       |
|-----------|---------|------------------------------------------------------------------|
|`GRAVE_ESC`|`KC_GESC`|押された場合に Escape。Shift あるいは GUI が押されたままの場合は <code>&#96;</code>|

## キーロック :id=key-lock

[キーロック](ja/feature_key_lock.md) も見てください。

|キー     |説明                                              |
|---------|--------------------------------------------------|
|`KC_LOCK`|キーが再び押されるまで次のキーを押したままにします |

## レイヤー切り替え :id=layer-switching

[レイヤー切り替え](ja/feature_layers.md#switching-and-toggling-layers) も見てください。

|キー            |説明                                                                                                                                  |
|----------------|--------------------------------------------------------------------------------------------------------------------------------------|
|`DF(layer)`     |指定されたレイヤーを基本 (デフォルト) レイヤーに設定する |
|`MO(layer)`     |キーを押したら一時的に `layer` を切り替える。(切り替え先のレイヤーには `KC_TRNS` が必要です) |
|`OSL(layer)`    |次のキーが押されるまで、一時的にレイヤーをアクティブにします。詳細は [ワンショットキー](ja/one_shot_keys.md) のとおり。 |
|`LM(layer, mod)`|`mod` がアクティブな状態で (MO のように) 一時的にレイヤーをアクティブにします。ここでは、`mod` は mods_bit のことです。Mod については [こちら](ja/mod_tap.md) で見ることができます。実装例: `LM(LAYER_1, MOD_LALT)` |
|`LT(layer, kc)` |押していると `layer` をオンにし、タップすると `kc` になります。 |
|`TG(layer)`     |`layer` のオン・オフを切り替え |
|`TO(layer)`     |`layer` をオンにして、デフォルトレイヤーを除く他のレイヤーをオフにします。 |
|`TT(layer)`     |複数回タップしない限り `MO` のように動作し、複数回タップすると `layer` をオンにトグルします。 |

## リーダーキー :id=leader-key

[リーダーキー](ja/feature_leader_key.md) も見てください。

|キー     |説明                           |
|---------|-------------------------------|
|`KC_LEAD`|リーダーキーのシーケンスを開始 |

## マウスキー :id=mouse-keys

[マウスキー](ja/feature_mouse_keys.md) も見てください。

|キー            |エイリアス  |説明                  |
|----------------|---------|-------------------------|
|`KC_MS_UP`      |`KC_MS_U`|マウスカーソルを上に移動 |
|`KC_MS_DOWN`    |`KC_MS_D`|マウスカーソルを下に移動 |
|`KC_MS_LEFT`    |`KC_MS_L`|マウスカーソルを左に移動 |
|`KC_MS_RIGHT`   |`KC_MS_R`|マウスカーソルを右に移動 |
|`KC_MS_BTN1`    |`KC_BTN1`|ボタン1を押す            |
|`KC_MS_BTN2`    |`KC_BTN2`|ボタン2を押す            |
|`KC_MS_BTN3`    |`KC_BTN3`|ボタン3を押す            |
|`KC_MS_BTN4`    |`KC_BTN4`|ボタン4を押す            |
|`KC_MS_BTN5`    |`KC_BTN5`|ボタン5を押す            |
|`KC_MS_WH_UP`   |`KC_WH_U`|ホイールを向こう側に回転 |
|`KC_MS_WH_DOWN` |`KC_WH_D`|ホイールを手前側に回転   |
|`KC_MS_WH_LEFT` |`KC_WH_L`|ホイールを左に倒す       |
|`KC_MS_WH_RIGHT`|`KC_WH_R`|ホイールを右に倒す       |
|`KC_MS_ACCEL0`  |`KC_ACL0`|速度を0に設定            |
|`KC_MS_ACCEL1`  |`KC_ACL1`|速度を1に設定            |
|`KC_MS_ACCEL2`  |`KC_ACL2`|速度を2に設定            |

## 修飾キー :id=modifiers

[修飾キー](ja/feature_advanced_keycodes.md#modifier-keys) も見てください。

| キー       | エイリアス                      | 説明                                                          |
|------------|---------------------------------|---------------------------------------------------------------|
| `LCTL(kc)` | `C(kc)`                         | 左 Control を押しながら `kc` を押します。                     |
| `LSFT(kc)` | `S(kc)`                         | 左 Shift を押しながら `kc` を押します。                       |
| `LALT(kc)` | `A(kc)`, `LOPT(kc)`             | 左 Alt を押しながら `kc`を押します。                          |
| `LGUI(kc)` | `G(kc)`, `LCMD(kc)`, `LWIN(kc)` | 左 GUI を押しながら `kc` を押します。                         |
| `RCTL(kc)` |                                 | 右 Control を押しながら `kc` を押します。                     |
| `RSFT(kc)` |                                 | 右 Shift を押しながら `kc` を押します。                       |
| `RALT(kc)` | `ROPT(kc)`, `ALGR(kc)`          | 右 Alt (AltGr) を押しながら `kc` を押します。                 |
| `RGUI(kc)` | `RCMD(kc)`, `LWIN(kc)`          | 右 GUI を押しながら `kc` を押します。                         |
| `SGUI(kc)` | `SCMD(kc)`, `SWIN(kc)`          | 左 Shift と GUI を押しながら `kc` を押します。                |
| `LCA(kc)`  |                                 | 左 Control と Alt を押しながら `kc` を押します。              |
| `LSA(kc)`  |                                 | 左 Shift と Alt を押しながら `kc` を押します。                |
| `RSA(kc)`  |`SAGR(kc)`                       | 右 Shift と Alt (AltGr)  を押しながら `kc` を押します。       |
| `RCS(kc)`  |                                 | 右 Control と Shift を押しながら `kc` を押します。            |
| `LCAG(kc)` |                                 | 左 Control、Alt、GUI を押しながら `kc` を押します。           |
| `MEH(kc)`  |                                 | 左 Control、Shift、Alt を押しながら `kc` を押します。         |
| `HYPR(kc)` |                                 | 左 Control、Shift、Alt、GUI を押しながら `kc` を押します。    |
| `KC_MEH`   |                                 | 左 Control、Shift、Alt                                        |
| `KC_HYPR`  |                                 | 左 Control、Shift、Alt、GUI                                   |


## モッドタップキー :id=mod-tap-keys

[モッドタップキー](ja/mod_tap.md) も見てください。

|キー          |エイリアス                                                         | 説明                                                                   |
|--------------|-------------------------------------------------------------------|------------------------------------------------------------------------|
| `MT(mod, kc)`|                                                                   |押したままの場合は `mod` 、タップした場合は `kc`                        |
| `LCTL_T(kc)` | `CTL_T(kc)`                                                       | 押したままの場合は左 Control、タップした場合は `kc`                    |
| `LSFT_T(kc)` | `SFT_T(kc)`                                                       | 押したままの場合は左 Shift、タップした場合は `kc`                      |
| `LALT_T(kc)` | `LOPT_T(kc)`, `ALT_T(kc)`, `OPT_T(kc)`                            | 押したままの場合は左 Alt、タップした場合は `kc`                        |
| `LGUI_T(kc)` | `LCMD_T(kc)`, `LWIN_T(kc)`, `GUI_T(kc)`, `CMD_T(kc)`, `WIN_T(kc)` | 押したままの場合は左 GUI、タップした場合は `kc`                        |
| `RCTL_T(kc)` |                                                                   | 押したままの場合は右 Control、タップした場合は `kc`                    |
| `RSFT_T(kc)` |                                                                   | 押したままの場合は右 Shift、タップした場合は `kc`                      |
| `RALT_T(kc)` | `ROPT_T(kc)`, `ALGR_T(kc)`                                        | 押したままの場合は右 Alt (AltGr) 、タップした場合は `kc`               |
| `RGUI_T(kc)` | `RCMD_T(kc)`, `RWIN_T(kc)`                                        | 押したままの場合は右 GUI、タップした場合は `kc`                        |
| `SGUI_T(kc)` | `SCMD_T(kc)`, `SWIN_T(kc)`                                        | 押したままの場合は左 Shift と GUI、タップした場合は `kc`               |
| `LCA_T(kc)`  |                                                                   | 押したままの場合は左 Control と Alt、タップした場合は `kc`             |
| `LSA_T(kc)`  |                                                                   | 押したままの場合は左 Shift と Alt、タップした場合は `kc`               |
| `RSA_T(kc)`  |`SAGR_T(kc)`                                                       | 押したままの場合は右 Shift と Alt (AltGr) 、タップした場合は `kc`      |
| `RCS_T(kc)`  |                                                                   | 押したままの場合は右 Control と Shift、タップした場合は `kc`           | 
| `LCAG_T(kc)` |                                                                   | 押したままの場合は左 Control、Alt、GUI、タップした場合は `kc`          |
| `RCAG_T(kc)` |                                                                   | 押したままの場合は右 Control、Alt、GUI、タップした場合は `kc`          |
| `C_S_T(kc)`  |                                                                   | 押したままの場合は左 Control と Shift、タップした場合は `kc`           |
| `MEH_T(kc)`  |                                                                   | 押したままの場合は左 Control、Shift、Alt、タップした場合は `kc`        |
| `HYPR_T(kc)` | `ALL_T(kc)`                                                       | 押したままの場合は左 Control、Shift、Alt、GUI、タップした場合は `kc` - より詳しくは[ここ](https://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)を見てください |

## RGB ライト :id=rgb-lighting

[RGB ライト](ja/feature_rgblight.md) も見てください。

|キー               |エイリアス|説明                                                                 |
|-------------------|----------|---------------------------------------------------------------------|
|`RGB_TOG`          |          |RGB ライトのオン・オフを切り替え                                     |
|`RGB_MODE_FORWARD` |`RGB_MOD` |RGB モードを順送りで変更し、Shift を押していると逆順で変更します。   |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|RGB モードを逆順で変更し、Shift を押していると順送りで変更します。   |
|`RGB_HUI`          |          |色相 (HUE) を増加させ、Shift を押していると減少させます。            |
|`RGB_HUD`          |          |色相 (HUE) を減少させ、Shift を押していると増加させます。            |
|`RGB_SAI`          |          |彩度 (SAT) を増加させ、Shift を押していると減少させます。            |
|`RGB_SAD`          |          |彩度 (SAT) を減少させ、Shift を押していると増加させます。            |
|`RGB_VAI`          |          |明度 (VAL/brightness) を増加させ、Shift を押していると減少させます。 |
|`RGB_VAD`          |          |明度 (VAL/brightness) を減少させ、Shift を押していると増加させます。 |
|`RGB_MODE_PLAIN`   |`RGB_M_P `|静止(動き無し) モードに固定します                                    |
|`RGB_MODE_BREATHE` |`RGB_M_B` |明滅アニメーションモード                                             |
|`RGB_MODE_RAINBOW` |`RGB_M_R` |レインボーアニメーションモード                                       |
|`RGB_MODE_SWIRL`   |`RGB_M_SW`|渦巻アニメーションモード                                             |
|`RGB_MODE_SNAKE`   |`RGB_M_SN`|スネークアニメーションモード                                         |
|`RGB_MODE_KNIGHT`  |`RGB_M_K` |「ナイトライダー」アニメーションモード                               |
|`RGB_MODE_XMAS`    |`RGB_M_X` |クリスマスアニメーションモード                                       |
|`RGB_MODE_GRADIENT`|`RGB_M_G` |固定階調アニメーションモード                                         |
|`RGB_MODE_RGBTEST` |`RGB_M_T` |赤、緑、青のテストアニメーションモード                               |

## RGB マトリックスライト :id=rgb-matrix-lighting

[RGB マトリックスライト](ja/feature_rgb_matrix.md) も見てください。

|キー               |エイリアス|説明                                                                                                    |
|-------------------|----------|--------------------------------------------------------------------------------------------------------|
|`RGB_TOG`          |          |RGB ライトのオン・オフを切り替え                                                                        |
|`RGB_MODE_FORWARD` |`RGB_MOD` |RGB モードを順送りで変更し、Shift を押していると逆順で変更します。                                      |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|RGB モードを逆順で変更し、Shift を押していると順送りで変更します。                                      |
|`RGB_HUI`          |          |色相 (HUE) を増加させ、Shift を押していると減少させます。                                               |
|`RGB_HUD`          |          |色相 (HUE) を減少させ、Shift を押していると増加させます。                                               |
|`RGB_SAI`          |          |彩度 (SAT) を増加させ、Shift を押していると減少させます。                                               |
|`RGB_SAD`          |          |彩度 (SAT) を減少させ、Shift を押していると増加させます。                                               |
|`RGB_VAI`          |          |明度 (VAL/brightness) を増加させ、Shift を押していると減少させます。                                    |
|`RGB_VAD`          |          |明度 (VAL/brightness) を減少させ、Shift を押していると増加させます。                                    |
|`RGB_SPI`          |          |エフェクトのスピード (EEPROM はまだサポートしていません) を増加させ、Shift を押していると減少させます。 |
|`RGB_SPD`          |          |エフェクトのスピード (EEPROM はまだサポートしていません) を減少させ、Shift を押していると増加させます。 |

## 感熱式プリンタ :id=thermal-printer

[感熱式プリンタ](ja/feature_thermal_printer.md) も見てください。

|キー       |説明                             |
|-----------|---------------------------------|
|`PRINT_ON` |ユーザが入力した全ての印刷を開始 |
|`PRINT_OFF`|ユーザが入力した全ての印刷を停止 |

## US ANSI シフト済シンボル :id=us-ansi-shifted-symbols

[US ANSI シフト済シンボル](ja/keycodes_us_ansi_shifted.md) も見てください。

|キー                    |エイリアス            |説明|
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

## ワンショットキー :id=one-shot-keys

[ワンショットキー](ja/one_shot_keys.md) も見てください。

|キー        |説明                            |
|------------|--------------------------------|
|`OSM(mod)`  | 次のキーが押されるまで、`mod` を押したままにします |
|`OSL(layer)`| 次のキーが押されるまで、一時的にレイヤーをアクティブにします |

## Space Cadet :id=space-cadet

[Space Cadet](ja/feature_space_cadet.md) も見てください。

|キー       |説明                                       |
|-----------|-------------------------------------------|
|`KC_LCPO`  |押したままの場合は左 Control、タップした場合は `(` |
|`KC_RCPC`  |押したままの場合は右 Control、タップした場合は `)` |
|`KC_LSPO`  |押したままの場合は左 Shift、タップした場合は `(`、 |
|`KC_RSPC`  |押したままの場合は右 Shift、タップした場合は `)`、 |
|`KC_LAPO`  |押したままの場合は左 Alt、タップした場合は `(`、   |
|`KC_RAPC`  |押したままの場合は右 Alt、タップした場合は `)`、   |
|`KC_SFTENT`|押したままの場合は右 Shift、タップした場合は Enter |

## スワップハンド :id=swap-hands

[スワップハンド](ja/feature_swap_hands.md) も見てください。

|キー         |説明                                                                              |
|-------------|----------------------------------------------------------------------------------|
| `SH_T(key)` | タップで `key` を送信する。押している時に一時的に入れ替え。                      |
| `SH_ON`     | 入れ替えをオンにして、そのままにする。                                           |
| `SH_OFF`    | 入れ替えをオフにして、そのままにする。既知の状態に戻るのに適しています。         |
| `SH_MON`    | 押すとスワップハンドし、放すと通常に戻る (一時的)。                              |
| `SH_MOFF`   | 一時的に入れ替えをオフする。                                                     |
| `SH_TG`     | キーを押すたびにオンとオフを切り替える。                               |
| `SH_TT`     | タップで切り替える。押している時に一時的に切り替える。                               |
| `SH_OS`     | ワンショットスワップハンド: 押している時あるいは次のキーを押すまで切り替える。 |

## ユニコードサポート :id=unicode-support

[ユニコードサポート](ja/feature_unicode.md) も見てください。

|キー                  |エイリアス |説明                                                                  |
|----------------------|-----------|----------------------------------------------------------------------|
|`UC(c)`               |           |コードポイント `c` のユニコードを送信                                 |
|`X(i)`                |           |`unicode_map` のインデックス `i` のユニコードを送信                   |
|`XP(i, j)`            |           |Shift/Capsが有効なら、インデックス `i` または `j` のユニコードを送信  |
|`UNICODE_MODE_FORWARD`|`UC_MOD`   |ユニコード入力方式を順送りで選択                                      |
|`UNICODE_MODE_REVERSE`|`UC_RMOD`  |ユニコード入力方式を逆順で選択                                        |
|`UNICODE_MODE_OSX`    |`UC_M_OS`  |ユニコード入力方式を macOS 方式に切り替え                             |
|`UNICODE_MODE_LNX`    |`UC_M_LN`  |ユニコード入力方式を Linux 方式に切り替え                             |
|`UNICODE_MODE_WIN`    |`UC_M_WI`  |ユニコード入力方式を Windows 方式に切り替え                           |
|`UNICODE_MODE_BSD`    |`UC_M_BS`  |ユニコード入力方式を BSD 方式に切り替え (実装されていません)          |
|`UNICODE_MODE_WINC`   |`UC_M_WC`  |ユニコード入力方式を WinCompose を使う Windows 方式に切り替え         |
