# キーマップのFAQ

このページは人々がキーマップについてしばしば持つ質問についてカバーします。まだ持っていない場合は、[キーマップの概要](keymap.md)を最初に読むべきです。

## どのキーコードを使えますか？
あなたが利用可能なキーコードのインデックスについては、[キーコード](keycodes.md)を見てください。利用可能な場合、これらをより広範なドキュメントにリンクします。

キーコードは実際には[common/keycode.h](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/keycode.h)で定義されています。

## デフォルトのキーコードとは何か？

世界中で使用されている ANSI, ISO および JIS.の3つの標準キーボードがあります。北米では主にANSIが使われ、ヨーロッパおよびアフリカでは主にISOが使われ、日本ではJISが使われます。言及されていない地域では、ANSIあるいはISOが使われています。これらのレイアウトに対応するキーコードは以下の通りです:

<!-- Source for this image: http://www.keyboard-layout-editor.com/#/gists/bf431647d1001cff5eff20ae55621e9a -->
![キーボードのレイアウト イメージ](https://i.imgur.com/5wsh5wM.png)

## 一部のキーが好感されているか動作しない

QMKは2つの機能、ブートマジックとコマンドを持ち、これによりその場でキーボードの動作を変更することができます。これには Ctrl/Capsの交換、Guiの無効か、Alt/GUIの交換、Backspace/Backslashの交換、全てのキーの無効化 およびその他の動作の変更が含まれますが、これらに限定されません。

高速な解決策として、キーボードを接続している時に`Space`+`Backspace` を押してみてください。これはキーボードに保存されている設定をリセットされ、これらのキーを通常の操作に戻します。うまく行かない場合は、以下を見てください:

* [ブートマジック](feature_bootmagic.md)
* [コマンド](feature_command.md)

## メニュー キーが動作しない

`KC_RGUI` と `KC_RCTL` の間にあるほとんどの最新のキーボードで見つかるキーは、実際には`KC_APP`と呼ばれます。これは、そのキーが発明された時に、関連する標準にすでに`MENU`という名前のキーが存在していたため、MSはそれを `APP` キーと呼ぶことを選択したたためです。

## `KC_SYSREQ` が動作しません。
`KC_SYSREQ`の代わりに、Print Screen(`KC_PSCREEN` あるいは `KC_PSCR`) のキーコードを使ってください。'Alt + Print Screen' のキーの組み合わせは、'System request'と認識されます。

[issue #168](https://github.com/tmk/tmk_keyboard/issues/168) と以下を見てください
* http://en.wikipedia.org/wiki/Magic_SysRq_key
* http://en.wikipedia.org/wiki/System_request

## 電源キーが動作しません

やや紛らわしいことに、QMKには2つの"Power" キーコードがあります: キーボード/キーパッド HID使用ページでは`KC_POWER`、コンシューマ ページでは`KC_SYSTEM_POWER` (あるいは `KC_PWR`)。

前者はmacOSでのみ認識されますが、後者 `KC_SLEP` および `KC_WAKE` は3つの主要なオペレーティング システム全てでサポートされるため、代わりにこれらを使うことをお勧めします。Windowsでは、これらのキーはすぐに有効になりますが、macOSではそれらはダイアログが表示されるまで押し続ける必要があります。

## ワンショット修飾子
私の個人的な問題を解決します。'The'.ではなく 'the' あるいは 'THe' を間違って取得することがありました。ワンショットSihiftはこれを軽減します。
https://github.com/tmk/tmk_keyboard/issues/67

## モディファイヤ/レイヤ スタック
モディファイヤ キーあるいはレイヤは、レイヤの切り替えが適切に設定されていない場合、スタックするかもしれません。
モディファイヤ キーおよびレイヤ切り替えの場合、モディファイヤ キーの登録を解除するか、リリースイベント時に前のレイヤに戻るために、目的のレイヤの同じ位置に`KC_TRANS`を配置する必要があります。

* https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#31-momentary-switching
* http://geekhack.org/index.php?topic=57008.msg1492604#msg1492604
* https://github.com/tmk/tmk_keyboard/issues/248


## メカニカル ロック スイッチのサポート

この機能は[this Alps one](http://deskthority.net/wiki/Alps_SKCL_Lock)のような*メカニカル ロック スイッチ*用です。これを`config.h`に追加することで有効にすることができます:

```
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
```

この機能を有効にした後で、キーマップでキーコード `KC_LCAP`, `KC_LNUM` および `KC_LSCR` を代わりに使います。

古いビンテージ メカニカル キーボードにはロック スイッチが付いている場合がありますが、最新のものにはありません。***ほとんどの場合この機能は必要なく、単にキーコード `KC_CAPS`, `KC_NLCK` および `KC_SLCK`.***を使います。

## Cédille 'Ç'のようなASCII以外の特別文字を入力してください。 
これらの機能を全てのシステムで入力するための汎用的な方法はありません。 OSまたはレイアウトに固有の方法で、**MACRO**を定義しなければなりません。

**MACRO** コードの例についてはこの投稿を見てください。

http://deskthority.net/workshop-f7/tmk-keyboard-firmware-collection-t4478-120.html#p195620

**Windows**では、`AltGr`キーあるいは**Altコード**を使うことができます。
* http://en.wikipedia.org/wiki/AltGr_key
* http://en.wikipedia.org/wiki/Alt_code

**Mac**では、OSが`Option`キーの組み合わせを定義します。
* http://en.wikipedia.org/wiki/Option_key#Alternative_keyboard_input

**Xorg**では、代わりに`compose`キーを使うことができます。
* http://en.wikipedia.org/wiki/Compose_key

**Unicode** 入力については、これをみてください。
* http://en.wikipedia.org/wiki/Unicode_input

## macOSでの`Fn`キー

ほとんどの Fn キーと異なり、Appleのキーボードのキーには実際には独自のキーコードがあります... 基本的な 6KRO HID レポートの6番目のキーコードの代わりになります -- つまり、Appleキーボードは実際には 5KRO のみです。

QMKにこのキーを送信させることは技術的に可能です。ただし、そうするには Fn キーの状態を追加するためにレポート形式の修正を必要とします。 
さらに悪いことに、キーボードのVIDとPIDが実際のAppleのキーボードのものと一致しない限り、認識されません。公式のQMKがこの機能をサポートする法的な問題は、それが起こりそうもないという意味を作成するかもしれません。

詳細については、[この問題](https://github.com/qmk/qmk_firmware/issues/2179)を見てください。


## Mac OSXでのメディア コントロールキー
#### KC_MNXT と KC_MPRV はMacでは動作しません。
`KC_MNXT` と `KC_MPRV`の代わりに、`KC_MFFD`(`KC_MEDIA_FAST_FORWARD`) および `KC_MRWD`(`KC_MEDIA_REWIND`) を使ってください。
https://github.com/tmk/tmk_keyboard/issues/195 を見てください


## Mac OSXでサポートされるキーは？
このソースコードから、どのキーコードがOSXでサポートされるかを知ることができます。

`usb_2_adb_keymap` 配列は、キーボード/キーパッド ページの使用法をADBスキャンコード(OSX内部キーコード)にマップします。

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/Cosmo_USB2ADB.c

`IOHIDConsumer::dispatchConsumerEvent`はコンシューマページの使用を処理します。

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/IOHIDConsumer.cpp


## Mac OSXでのJISキー
`無変換(Muhenkan)`, `変換(Henkan)`, `ひらがな(hiragana)` のような日本語JISキーボード固有のキーはOSXでは認識されません。**Seil**を使ってこれらのキーを使うことができます。以下のオプションを試してください。

* PCキーボードで NFER キーを有効にする
* PCキーボードで XFER キーを有効にする
* PCキーボードで KATAKANA キーを有効にする

https://pqrs.org/osx/karabiner/seil.html


## RN-42 Bluetooth が Karabiner で動作しない
Karabiner - Mac OSX上のキーマッピング ツール - デフォルトでRN-42モジュールからの入力を無視します。Karabinerをキーボードで動作させるにはこのオプションを有効にする必要があります。
https://github.com/tekezo/Karabiner/issues/403#issuecomment-102559237

この問題の詳細についてはこれらを見てください。
https://github.com/tmk/tmk_keyboard/issues/213
https://github.com/tekezo/Karabiner/issues/403


## 単一のキーでの Esc と<code>&#96;</code>

[Grave Escape](feature_grave_esc.md) 機能を見てください。

## デュアル ロールの右修飾キーの矢印
キーがタップされた時に右の修飾キーが矢印キーになり、キーが保持された時に修飾キーが引き続き使用されます。TMKでは、デュアル-ロール機能は**TAP**と呼ばれます。
```
#include "keymap_common.h"


/* TMKのデュアルロール機能を備えた右修飾キーの矢印キー
 *
 *  https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#213-modifier-with-tap-keydual-role
 *  https://en.wikipedia.org/wiki/Modifier_key#Dual-role_keys
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    [0] = LAYOUT( \
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, NUHS,BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT,  \
        LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,FN0, ESC, \
        FN4, LGUI,LALT,          SPC,                     APP, FN2, FN1, FN3),
    [1] = LAYOUT( \
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,\
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN5, TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,FN7, FN6, FN8),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_UP),
    [1] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_DOWN),
    [2] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_LEFT),
    [3] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_RIGHT),
    [4] = ACTION_LAYER_MOMENTARY(1),
    [5] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_PGUP),
    [6] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_PGDN),
    [7] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_HOME),
    [8] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_END),
};
```

デュアル-ロール キー: https://en.wikipedia.org/wiki/Modifier_key#Dual-role_keys


## Mac OSXでのEject
`KC_EJCT` キーコードはOSXで動作します。https://github.com/tmk/tmk_keyboard/issues/250
Windows 10 はコードを無視し、Linux/Xorg は認識しますが、デフォルトではマッピングがありません。

実際のAppleキーボードにあるEjectキーコードは実際には分かりません。HHKBはMacモードではEjectキー (`Fn+f`) に`F20`を使いますが、これはおそらくAppleのEjectキーコードと同じではありません。


## `action_util.c`の`weak_mods` と `real_mods` は何か
___TO BE IMPROVED___

real_modsは実際/物理的な修飾キーの状態を保持することを目的にしていますが、weak_modsは実際の修飾キーの状態に影響しない仮想あるいは一時的な修飾子の状態を保持します。

物理的な左シフトキーを押しながらACTION_MODS_KEYを入力するとします (LSHIFT, KC_A)

weak_modsでは、
* (1) 左シフトキーを押し続ける: real_mods |= MOD_BIT(LSHIFT)
* (2) ACTION_MODS_KEY(LSHIFT, KC_A) を押す: weak_mods |= MOD_BIT(LSHIFT)
* (3) ACTION_MODS_KEY を放す(LSHIFT, KC_A): weak_mods &= ~MOD_BIT(LSHIFT)
real_mods は修飾子の状態を維持します。

weak mods無しでは、
* (1) 左シフトキーを押し続ける: real_mods |= MOD_BIT(LSHIFT)
* (2) ACTION_MODS_KEY を押す (LSHIFT, KC_A): real_mods |= MOD_BIT(LSHIFT)
* (3) ACTION_MODS_KEY を放す(LSHIFT, KC_A): real_mods &= ~MOD_BIT(LSHIFT)
ここで、real_modsは 'physical left shift' の状態を失います。

キーボード レポートが送信される時、weak_mods は real_mods とORされます。
https://github.com/tmk/tmk_core/blob/master/common/action_util.c#L57
