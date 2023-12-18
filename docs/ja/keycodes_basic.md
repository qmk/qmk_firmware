# 基本的なキーコード

<!---
  original document: 0.11.25:docs/keycodes_basic.md
  git diff 0.11.25 HEAD -- docs/keycodes_basic.md | cat
-->

基本的なキーコードのセットは、`KC_NO`、`KC_TRNS` と `0xA5-DF` の範囲のキーコードを除いて、[HID Keyboard/Keypad Usage Page (0x07)](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf) に基づいています。

## 文字と数字

|キー  |説明      |
|------|----------|
|`KC_A`|`a` と `A`|
|`KC_B`|`b` と `B`|
|`KC_C`|`c` と `C`|
|`KC_D`|`d` と `D`|
|`KC_E`|`e` と `E`|
|`KC_F`|`f` と `F`|
|`KC_G`|`g` と `G`|
|`KC_H`|`h` と `H`|
|`KC_I`|`i` と `I`|
|`KC_J`|`j` と `J`|
|`KC_K`|`k` と `K`|
|`KC_L`|`l` と `L`|
|`KC_M`|`m` と `M`|
|`KC_N`|`n` と `N`|
|`KC_O`|`o` と `O`|
|`KC_P`|`p` と `P`|
|`KC_Q`|`q` と `Q`|
|`KC_R`|`r` と `R`|
|`KC_S`|`s` と `S`|
|`KC_T`|`t` と `T`|
|`KC_U`|`u` と `U`|
|`KC_V`|`v` と `V`|
|`KC_W`|`w` と `W`|
|`KC_X`|`x` と `X`|
|`KC_Y`|`y` と `Y`|
|`KC_Z`|`z` と `Z`|
|`KC_1`|`1` と `!`|
|`KC_2`|`2` と `@`|
|`KC_3`|`3` と `#`|
|`KC_4`|`4` と `$`|
|`KC_5`|`5` と `%`|
|`KC_6`|`6` と `^`|
|`KC_7`|`7` と `&`|
|`KC_8`|`8` と `*`|
|`KC_9`|`9` と `(`|
|`KC_0`|`0` と `)`|

## ファンクションキー

|キー    |説明 |
|--------|-----|
|`KC_F1` |F1   |
|`KC_F2` |F2   |
|`KC_F3` |F3   |
|`KC_F4` |F4   |
|`KC_F5` |F5   |
|`KC_F6` |F6   |
|`KC_F7` |F7   |
|`KC_F8` |F8   |
|`KC_F9` |F9   |
|`KC_F10`|F10  |
|`KC_F11`|F11  |
|`KC_F12`|F12  |
|`KC_F13`|F13  |
|`KC_F14`|F14  |
|`KC_F15`|F15  |
|`KC_F16`|F16  |
|`KC_F17`|F17  |
|`KC_F18`|F18  |
|`KC_F19`|F19  |
|`KC_F20`|F20  |
|`KC_F21`|F21  |
|`KC_F22`|F22  |
|`KC_F23`|F23  |
|`KC_F24`|F24  |

##  パンクチュエーション

|キー             |エイリアス         |説明                                          |
|-----------------|-------------------|----------------------------------------------|
|`KC_ENTER`       |`KC_ENT`           |Return (Enter)                                |
|`KC_ESCAPE`      |`KC_ESC`           |Escape                                        |
|`KC_BSPACE`      |`KC_BSPC`          |Delete (Backspace)                            |
|`KC_TAB`         |                   |Tab                                           |
|`KC_SPACE`       |`KC_SPC`           |Spacebar                                      |
|`KC_MINUS`       |`KC_MINS`          |`-` と `_`                                    |
|`KC_EQUAL`       |`KC_EQL`           |`=` と `+`                                    |
|`KC_LBRACKET`    |`KC_LBRC`          |`[` と `{`                                    |
|`KC_RBRACKET`    |`KC_RBRC`          |`]` と `}`                                    |
|`KC_BSLASH`      |`KC_BSLS`          |`\` と `\|`                                   |
|`KC_NONUS_HASH`  |`KC_NUHS`          |Non-US `#` と `~`                             |
|`KC_SCOLON`      |`KC_SCLN`          |`;` と `:`                                    |
|`KC_QUOTE`       |`KC_QUOT`          |`'` と `"`                                    |
|`KC_GRAVE`       |`KC_GRV`, `KC_ZKHK`|<code>&#96;</code> と `~`, JIS 全角/半角      |
|`KC_COMMA`       |`KC_COMM`          |`,` と `<`                                    |
|`KC_DOT`         |                   |`.` と `>`                                    |
|`KC_SLASH`       |`KC_SLSH`          |`/` と `?`                                    |
|`KC_NONUS_BSLASH`|`KC_NUBS`          |Non-US `\` と `\|`                            |

## ロックキー

|キー               |エイリアス          |説明                                   |
|-------------------|--------------------|---------------------------------------|
|`KC_CAPSLOCK`      |`KC_CLCK`, `KC_CAPS`|Caps Lock                              |
|`KC_SCROLLLOCK`    |`KC_SCRL`, `KC_BRMD`|Scroll Lock, 画面の明るさダウン (macOS)|
|`KC_NUMLOCK`       |`KC_NUM`           |テンキー Num Lock と Clear             |
|`KC_LOCKING_CAPS`  |`KC_LCAP`           |Caps Lock のロック                     |
|`KC_LOCKING_NUM`   |`KC_LNUM`           |Num Lock のロック                      |
|`KC_LOCKING_SCROLL`|`KC_LSCR`           |Scroll Lock のロック                   |

## 修飾キー

|キー       |エイリアス          |説明                             |
|-----------|--------------------|---------------------------------|
|`KC_LCTRL` |`KC_LCTL`           |左 Control                       |
|`KC_LSHIFT`|`KC_LSFT`           |左 Shift                         |
|`KC_LALT`  |`KC_LOPT`           |左 Alt (Option)                  |
|`KC_LGUI`  |`KC_LCMD`, `KC_LWIN`|左 GUI (Windows/Command/Meta キー)|
|`KC_RCTRL` |`KC_RCTL`           |右 Control                       |
|`KC_RSHIFT`|`KC_RSFT`           |右 Shift                         |
|`KC_RALT`  |`KC_ROPT`, `KC_ALGR`|右 Alt (Option/AltGr)            |
|`KC_RGUI`  |`KC_RCMD`, `KC_RWIN`|右 GUI (Windows/Command/Meta キー)|

## 国際化対応キー

|キー      |エイリアス|説明                 |
|----------|----------|---------------------|
|`KC_INT1` |`KC_RO`   |JIS `\` と ` _`      |
|`KC_INT2` |`KC_KANA` |JIS カタカナ/ひらがな|
|`KC_INT3` |`KC_JYEN` |JIS `¥` と `\ |`     |
|`KC_INT4` |`KC_HENK` |JIS 変換             |
|`KC_INT5` |`KC_MHEN` |JIS 無変換           |
|`KC_INT6` |          |JIS テンキー `,`     |
|`KC_INT7` |          |International 7      |
|`KC_INT8` |          |International 8      |
|`KC_INT9` |          |International 9      |
|`KC_LANG1`|`KC_HAEN` |ハングル/英語        |
|`KC_LANG2`|`KC_HANJ` |韓文漢字             |
|`KC_LANG3`|          |JIS カタカナ         |
|`KC_LANG4`|          |JIS ひらがな         |
|`KC_LANG5`|          |JIS 全角/半角        |
|`KC_LANG6`|          |Language 6           |
|`KC_LANG7`|          |Language 7           |
|`KC_LANG8`|          |Language 8           |
|`KC_LANG9`|          |Language 9           |

## コマンドキー

|キー              |エイリアス                    |説明                                                   |
|------------------|------------------------------|-------------------------------------------------------|
|`KC_PSCREEN`      |`KC_PSCR`                     |Print Screen                                           |
|`KC_PAUSE`        |`KC_PAUS`, `KC_BRK`, `KC_BRMU`|Pause, 画面の明るさアップ (macOS)                      |
|`KC_INSERT`       |`KC_INS`                      |Insert                                                 |
|`KC_HOME`         |                              |Home                                                   |
|`KC_PGUP`         |                              |Page Up                                                |
|`KC_DELETE`       |`KC_DEL`                      |Forward Delete                                         |
|`KC_END`          |                              |End                                                    |
|`KC_PGDOWN`       |`KC_PGDN`                     |Page Down                                              |
|`KC_RIGHT`        |`KC_RGHT`                     |右矢印                                                 |
|`KC_LEFT`         |                              |左矢印                                                 |
|`KC_DOWN`         |                              |下矢印                                                 |
|`KC_UP`           |                              |上矢印                                                 |
|`KC_APPLICATION`  |`KC_APP`                      |アプリケーションキー (Windows コンテキストメニューキー)|
|`KC_POWER`        |                              |システム電源                                           |
|`KC_EXECUTE`      |`KC_EXEC`                     |Execute                                                |
|`KC_HELP`         |                              |Help                                                   |
|`KC_MENU`         |                              |Menu                                                   |
|`KC_SELECT`       |`KC_SLCT`                     |Select                                                 |
|`KC_STOP`         |                              |Stop                                                   |
|`KC_AGAIN`        |`KC_AGIN`                     |Again                                                  |
|`KC_UNDO`         |                              |アンドゥ                                               |
|`KC_CUT`          |                              |カット                                                 |
|`KC_COPY`         |                              |コピー                                                 |
|`KC_PASTE`        |`KC_PSTE`                     |ペースト                                               |
|`KC_FIND`         |                              |検索                                                   |
|`KC__MUTE`        |                              |ミュート                                               |
|`KC__VOLUP`       |                              |音量アップ                                             |
|`KC__VOLDOWN`     |                              |音量ダウン                                             |
|`KC_ALT_ERASE`    |`KC_ERAS`                     |Alternate Erase                                        |
|`KC_SYSREQ`       |                              |SysReq/Attention                                       |
|`KC_CANCEL`       |                              |Cancel                                                 |
|`KC_CLEAR`        |`KC_CLR`                      |Clear                                                  |
|`KC_PRIOR`        |                              |Prior                                                  |
|`KC_RETURN`       |                              |Return                                                 |
|`KC_SEPARATOR`    |                              |Separator                                              |
|`KC_OUT`          |                              |Out                                                    |
|`KC_OPER`         |                              |Oper                                                   |
|`KC_CLEAR_AGAIN`  |                              |Clear/Again                                            |
|`KC_CRSEL`        |                              |CrSel/Props                                            |
|`KC_EXSEL`        |                              |ExSel                                                  |

## メディアキー

これらのキーコードは、HID Keyboard/Keypad usage ページにはありません。`SYSTEM_` キーコードは、Generic Desktop ページで見つかります。また、その他は Consumer ページにあります。

?> これらのキーコードのいくつかは、OS によって異なる動作をする可能性があります。例として、macOS では `KC_MEDIA_FAST_FORWARD`、`KC_MEDIA_REWIND`、`KC_MEDIA_NEXT_TRACK`、`KC_MEDIA_PREV_TRACK` は、押している間は現在の曲の中でスキップしますが、タップした時は曲全体をスキップします。

|キー                   |エイリアス |説明                  |
|-----------------------|-----------|----------------------|
|`KC_SYSTEM_POWER`      |`KC_PWR`   |システム電源オフ      |
|`KC_SYSTEM_SLEEP`      |`KC_SLEP`  |システムスリープ      |
|`KC_SYSTEM_WAKE`       |`KC_WAKE`  |システムスリープ解除  |
|`KC_AUDIO_MUTE`        |`KC_MUTE`  |ミュート              |
|`KC_AUDIO_VOL_UP`      |`KC_VOLU`  |音量アップ            |
|`KC_AUDIO_VOL_DOWN`    |`KC_VOLD`  |音量ダウン            |
|`KC_MEDIA_NEXT_TRACK`  |`KC_MNXT`  |次の曲へ              |
|`KC_MEDIA_PREV_TRACK`  |`KC_MPRV`  |前の曲へ              |
|`KC_MEDIA_STOP`        |`KC_MSTP`  |再生停止              |
|`KC_MEDIA_PLAY_PAUSE`  |`KC_MPLY`  |再生/一時停止         |
|`KC_MEDIA_SELECT`      |`KC_MSEL`  |Media Player 起動     |
|`KC_MEDIA_EJECT`       |`KC_EJCT`  |イジェクト            |
|`KC_MAIL`              |           |メール起動            |
|`KC_CALCULATOR`        |`KC_CALC`  |電卓起動              |
|`KC_MY_COMPUTER`       |`KC_MYCM`  |マイコンピュータを開く|
|`KC_WWW_SEARCH`        |`KC_WSCH`  |ブラウザ検索          |
|`KC_WWW_HOME`          |`KC_WHOM`  |ブラウザホーム画面    |
|`KC_WWW_BACK`          |`KC_WBAK`  |ブラウザ戻る          |
|`KC_WWW_FORWARD`       |`KC_WFWD`  |ブラウザ進む          |
|`KC_WWW_STOP`          |`KC_WSTP`  |ブラウザ読み込み中止  |
|`KC_WWW_REFRESH`       |`KC_WREF`  |ブラウザ再読み込み    |
|`KC_WWW_FAVORITES`     |`KC_WFAV`  |ブラウザお気に入り    |
|`KC_MEDIA_FAST_FORWARD`|`KC_MFFD`  |次の曲へ              |
|`KC_MEDIA_REWIND`      |`KC_MRWD`  |前の曲へ              |
|`KC_BRIGHTNESS_UP`     |`KC_BRIU`  |画面の明るさアップ    |
|`KC_BRIGHTNESS_DOWN`   |`KC_BRID`  |画面の明るさダウン    |

## テンキー

|キー               |エイリアス |説明                           |
|-------------------|-----------|-------------------------------|
|`KC_KP_SLASH`      |`KC_PSLS`  |テンキー `/`                   |
|`KC_KP_ASTERISK`   |`KC_PAST`  |テンキー `*`                   |
|`KC_KP_MINUS`      |`KC_PMNS`  |テンキー `-`                   |
|`KC_KP_PLUS`       |`KC_PPLS`  |テンキー `+`                   |
|`KC_KP_ENTER`      |`KC_PENT`  |テンキー Enter                 |
|`KC_KP_1`          |`KC_P1`    |テンキー `1` と End            |
|`KC_KP_2`          |`KC_P2`    |テンキー `2` と 下矢印         |
|`KC_KP_3`          |`KC_P3`    |テンキー `3` と Page Down      |
|`KC_KP_4`          |`KC_P4`    |テンキー `4` と 左矢印         |
|`KC_KP_5`          |`KC_P5`    |テンキー `5`                   |
|`KC_KP_6`          |`KC_P6`    |テンキー `6` と 右矢印         |
|`KC_KP_7`          |`KC_P7`    |テンキー `7` と Home           |
|`KC_KP_8`          |`KC_P8`    |テンキー `8` と 上矢印         |
|`KC_KP_9`          |`KC_P9`    |テンキー `9` と Page Up        |
|`KC_KP_0`          |`KC_P0`    |テンキー `0` と Insert         |
|`KC_KP_DOT`        |`KC_PDOT`  |テンキー `.` と Delete         |
|`KC_KP_EQUAL`      |`KC_PEQL`  |テンキー `=`                   |
|`KC_KP_COMMA`      |`KC_PCMM`  |テンキー `,`                   |
|`KC_KP_EQUAL_AS400`|           |AS/400 キーボードのテンキー `=`|

## 特別なキー

これらのキーコードに加えて、`0xA5-DF` の範囲のキーコードは、内部処理のために予約されています。

|キー            |エイリアス          |説明                               |
|----------------|--------------------|-----------------------------------|
|`KC_NO`         |`XXXXXXX`           |このキーを無視します (NOOP)        |
|`KC_TRANSPARENT`|`KC_TRNS`, `_______`|次に低いレイヤーの非透過キーを使う |
