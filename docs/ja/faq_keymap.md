# キーマップの FAQ

<!---
  original document: d598f01cb:docs/faq_keymap.md
  git diff d598f01cb HEAD docs/faq_keymap.md | cat
-->

このページは人々がキーマップについてしばしば持つ疑問について説明します。まだ読んだことが無い場合には、[キーマップの概要](ja/keymap.md)を最初に読むべきです。

## どのキーコードを使えますか？
あなたが利用可能なキーコードのインデックスについては、[キーコード](ja/keycodes.md)を見てください。利用可能な場合、これらをより広範なドキュメントにリンクします。

キーコードは実際には [common/keycode.h](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/keycode.h) で定義されています。

## デフォルトのキーコードとは何か？

世界中で使用されている ANSI、ISO および JIS の3つの標準キーボードがあります。北米では主に ANSI が使われ、ヨーロッパおよびアフリカでは主に ISO が使われ、日本では JIS が使われます。言及されていない地域では、ANSI あるいは ISO が使われています。これらのレイアウトに対応するキーコードは以下の通りです:

<!-- Source for this image: http://www.keyboard-layout-editor.com/#/gists/bf431647d1001cff5eff20ae55621e9a -->
![キーボードのレイアウトイメージ](https://i.imgur.com/5wsh5wM.png)

## 一部のキーが交換されているか、または動作しない

QMK は2つの機能、ブートマジックとコマンドを持ち、これによりその場でキーボードの動作を変更することができます。これには Ctrl/Caps の交換、Gui の無効化、Alt/GUI の交換、Backspace/Backslash の交換、全てのキーの無効化およびその他の動作の変更が含まれますが、これらに限定されません。

迅速な解決策として、キーボードを接続している時に `Space`+`Backspace` を押してみてください。これはキーボードに保存されている設定をリセットし、これらのキーを通常の操作に戻します。うまく行かない場合は、以下を見てください:

* [ブートマジック](ja/feature_bootmagic.md)
* [コマンド](ja/feature_command.md)

## メニューキーが動作しない

ほとんどの最近のキーボードにある、`KC_RGUI` と `KC_RCTL` の間にあるキーは、実際には `KC_APP` と呼ばれます。これは、そのキーが発明された時に、関連する標準にすでに `MENU` という名前のキーが存在していたため、MS はそれを `APP` キーと呼ぶことを選択したたためです。

## `KC_SYSREQ` が動作しません。
`KC_SYSREQ` の代わりに、Print Screen(`KC_PSCREEN` あるいは `KC_PSCR`) のキーコードを使ってください。'Alt + Print Screen' のキーの組み合わせは、'System request' と認識されます。

[issue #168](https://github.com/tmk/tmk_keyboard/issues/168) と以下を見てください
* http://en.wikipedia.org/wiki/Magic_SysRq_key
* http://en.wikipedia.org/wiki/System_request

## 電源キーが動作しません

やや紛らわしいことに、QMK には2つの "Power" キーコードがあります: キーボード/キーパッド HID 使用法ページでは `KC_POWER`、コンシューマ ページでは `KC_SYSTEM_POWER` (あるいは `KC_PWR`)。

前者は macOS でのみ認識されますが、後者 `KC_SLEP` および `KC_WAKE` は3つの主要なオペレーティングシステム全てでサポートされるため、これらを使うことをお勧めします。Windows ではこれらのキーはすぐに有効になりますが、macOS ではそれらはダイアログが表示されるまで押し続ける必要があります。

## ワンショットモディファイア
私の個人的な問題を解決します。'The' ではなく 'the' あるいは 'THe' を間違って取得することがありました。ワンショットシフトはこれを軽減します。
https://github.com/tmk/tmk_keyboard/issues/67

## モディファイヤ/レイヤスタック
修飾キーあるいはレイヤは、レイヤの切り替えが適切に設定されていない場合、スタックするかもしれません。
修飾キーおよびレイヤ切り替えの場合、修飾キーの登録を解除するか、リリースイベント時に前のレイヤに戻るために、目的のレイヤの同じ位置に `KC_TRANS` を配置する必要があります。

* https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#31-momentary-switching
* http://geekhack.org/index.php?topic=57008.msg1492604#msg1492604
* https://github.com/tmk/tmk_keyboard/issues/248


## メカニカルロックスイッチのサポート

この機能は [Alps](http://deskthority.net/wiki/Alps_SKCL_Lock) のような*メカニカルロックスイッチ*用です。以下を `config.h` に追加することで有効にすることができます:

```
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
```

この機能を有効にした後で、キーマップでキーコード `KC_LCAP`、`KC_LNUM` および `KC_LSCR` を代わりに使います。

古いビンテージメカニカルキーボードにはロックスイッチが付いている場合がありますが、最新のものにはありません。***ほとんどの場合この機能は必要なく、単にキーコード `KC_CAPS`、`KC_NLCK` および `KC_SLCK`*** を使います。

## Cédille 'Ç' のような ASCII 以外の特別文字の入力
これらの機能を全てのシステムで入力するための汎用的な方法はありません。 OS またはレイアウトに固有の方法で、**MACRO** を定義しなければなりません。

**MACRO** コードの例についてはこの投稿を見てください。

http://deskthority.net/workshop-f7/tmk-keyboard-firmware-collection-t4478-120.html#p195620

**Windows** では、`AltGr` キーあるいは **Alt コード** を使うことができます。
* http://en.wikipedia.org/wiki/AltGr_key
* http://en.wikipedia.org/wiki/Alt_code

**Mac** では、OS が `Option` キーの組み合わせを定義します。
* http://en.wikipedia.org/wiki/Option_key#Alternative_keyboard_input

**Xorg** では、代わりに `compose` キーを使うことができます。
* http://en.wikipedia.org/wiki/Compose_key

**Unicode** 入力については、これをみてください。
* http://en.wikipedia.org/wiki/Unicode_input

## macOS での `Fn` キー

ほとんどの Fn キーと異なり、Apple のキーボードのキーには実際には独自のキーコードがあります... 基本的な 6KRO HID レポートの6番目のキーコードの代わりになります -- つまり、Apple キーボードは実際には 5KRO のみです。

QMK にこのキーを送信させることは技術的に可能です。ただし、そうするには Fn キーの状態を追加するためにレポート形式の修正を必要とします。 
さらに悪いことに、キーボードの VID と PID が実際の Apple のキーボードのものと一致しない限り、認識されません。公式の QMK がこの機能をサポートする法的な問題は、それが起こりそうもないということを意味します。

詳細については、[この問題](https://github.com/qmk/qmk_firmware/issues/2179)を見てください。

## Mac OSX でサポートされるキーは？
このソースコードから、どのキーコードが OSX でサポートされるかを知ることができます。

`usb_2_adb_keymap` 配列は、キーボード/キーパッドページの使用法を ADB スキャンコード(OSX 内部キーコード)にマップします。

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/Cosmo_USB2ADB.c

`IOHIDConsumer::dispatchConsumerEvent` はコンシューマページの使用法を処理します。

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/IOHIDConsumer.cpp


## Mac OSX での JIS キー
`無変換(Muhenkan)`, `変換(Henkan)`, `ひらがな(hiragana)` のような日本語 JIS キーボード固有のキーは OSX では認識されません。**Seil** を使ってこれらのキーを使うことができます。以下のオプションを試してください。

* PC キーボードで NFER キーを有効にする
* PC キーボードで XFER キーを有効にする
* PC キーボードで KATAKANA キーを有効にする

https://pqrs.org/osx/karabiner/seil.html


## RN-42 Bluetooth が Karabiner で動作しない
Karabiner - Mac OSX 上のキーマッピングツール - デフォルトで RN-42 モジュールからの入力を無視します。Karabiner をキーボードで動作させるにはこのオプションを有効にする必要があります。
https://github.com/tekezo/Karabiner/issues/403#issuecomment-102559237

この問題の詳細についてはこれらを見てください。
https://github.com/tmk/tmk_keyboard/issues/213
https://github.com/tekezo/Karabiner/issues/403


## 単一のキーでの Esc と<code>&#96;</code>

[Grave Escape](ja/feature_grave_esc.md) 機能を見てください。

## デュアルロールの右修飾キーの矢印
キーがタップされた時に右の修飾キーが矢印キーになり、キーが押し続けられた時に修飾キーが引き続き使用されます。TMK では、デュアルロール機能は **TAP** と呼ばれます。
```
#include "keymap_common.h"


/* TMK のデュアルロール機能を備えた右修飾キーの矢印キー
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

デュアルロールキー: https://en.wikipedia.org/wiki/Modifier_key#Dual-role_keys


## Mac OSX での Eject
`KC_EJCT` キーコードは OSX で動作します。https://github.com/tmk/tmk_keyboard/issues/250
Windows 10 はコードを無視し、Linux/Xorg は認識しますが、デフォルトではマッピングがありません。

実際の Apple キーボードにある Eject キーコードは実際には分かりません。HHKB は Mac モードでは Eject キー (`Fn+f`) に `F20` を使いますが、これはおそらく Apple の Eject キーコードと同じではありません。


## `action_util.c` の `weak_mods` と `real_mods` は何か
___TO BE IMPROVED___

real_mods は実際/物理的な修飾キーの状態を保持することを目的にしていますが、weak_mods は実際の修飾キーの状態に影響しない仮想あるいは一時的なモディファイアの状態を保持します。

物理的な左シフトキーを押しながら ACTION_MODS_KEY を入力するとします (LSHIFT, KC_A)

weak_mods では、
* (1) 左シフトキーを押し続ける: real_mods |= MOD_BIT(LSHIFT)
* (2) ACTION_MODS_KEY(LSHIFT, KC_A) を押す: weak_mods |= MOD_BIT(LSHIFT)
* (3) ACTION_MODS_KEY を放す(LSHIFT, KC_A): weak_mods &= ~MOD_BIT(LSHIFT)
real_mods はモディファイアの状態を維持します。

weak mods 無しでは、
* (1) 左シフトキーを押し続ける: real_mods |= MOD_BIT(LSHIFT)
* (2) ACTION_MODS_KEY を押す (LSHIFT, KC_A): real_mods |= MOD_BIT(LSHIFT)
* (3) ACTION_MODS_KEY を放す(LSHIFT, KC_A): real_mods &= ~MOD_BIT(LSHIFT)
ここで、real_mods は 'physical left shift' の状態を失います。

キーボードレポートが送信される時、weak_mods は real_mods と OR されます。
https://github.com/tmk/tmk_core/blob/master/common/action_util.c#L57
