# キーマップの FAQ

<!---
  original document: 0.13.15:docs/faq_keymap.md
  git diff 0.13.15 HEAD -- docs/faq_keymap.md | cat
-->

このページは人々がキーマップについてしばしば持つ疑問について説明します。まだ読んだことが無い場合には、[キーマップの概要](ja/keymap.md)を最初に読むべきです。

## どのキーコードを使えますか？
あなたが利用可能なキーコードのインデックスについては、[キーコード](ja/keycodes.md)を見てください。より広範なドキュメントがある場合は、そこからリンクしてあります。

キーコードは実際には [common/keycode.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/keycode.h) で定義されています。

## デフォルトのキーコードとは何か？

世界中で使用されている ANSI、ISO および JIS の3つの標準キーボードがあります。北米では主に ANSI が使われ、ヨーロッパおよびアフリカでは主に ISO が使われ、日本では JIS が使われます。言及されていない地域では、ANSI あるいは ISO が使われています。これらのレイアウトに対応するキーコードは以下の通りです:

<!-- Source for this image: https://www.keyboard-layout-editor.com/#/gists/bf431647d1001cff5eff20ae55621e9a -->
![キーボードのレイアウトイメージ](https://i.imgur.com/5wsh5wM.png)

## 複雑なキーコードのカスタム名を作成する方法はありますか？

時には、読みやすくするために、一部のキーコードにカスタム名を定義すると役に立ちます。人々は、しばしば `#define` を使ってカスタム名を定義します。例えば:

```c
#define FN_CAPS LT(_FL, KC_CAPSLOCK)
#define ALT_TAB LALT(KC_TAB)
```

これにより、キーマップで `FN_CAPS` と `ALT_TAB` を使えるようになり、読みやすくなります。

## 一部のキーが入れ替わっているか、または動作しない

QMK には2つの機能、ブートマジックとコマンドがあり、これによりその場でキーボードの動作を変更することができます。これには Ctrl/Caps の交換、Gui の無効化、Alt/Gui の交換、Backspace/Backslash の交換、全てのキーの無効化およびその他の動作の変更が含まれますが、これらに限定されません。

迅速な解決策として、キーボードを接続している時に `Space`+`Backspace` を押してみてください。これはキーボードに保存されている設定をリセットし、これらのキーを通常の操作に戻します。うまく行かない場合は、以下を見てください:

* [ブートマジック](ja/feature_bootmagic.md)
* [コマンド](ja/feature_command.md)

## メニューキーが動作しない

ほとんどの最近のキーボードにある、`KC_RGUI` と `KC_RCTL` の間にあるキーは、実際には `KC_APP` と呼ばれます。これは、そのキーが発明された時に、関連する標準にすでに `MENU` という名前のキーが存在していたため、MS はそれを `APP` キーと呼ぶことを選択したためです。

## `KC_SYSREQ` が動作しません
`KC_SYSREQ` の代わりに、Print Screen(`KC_PSCREEN` あるいは `KC_PSCR`) のキーコードを使ってください。'Alt + Print Screen' のキーの組み合わせは、'システムリクエスト' と認識されます。

[issue #168](https://github.com/tmk/tmk_keyboard/issues/168) と以下を見てください
* https://en.wikipedia.org/wiki/Magic_SysRq_key
* https://en.wikipedia.org/wiki/System_request

## 電源キーが動作しません

やや紛らわしいことに、QMK には2つの "Power" キーコードがあります: キーボード/キーパッド HID usage page では `KC_POWER`、Consumer page では `KC_SYSTEM_POWER` (あるいは `KC_PWR`)。

前者は macOS でのみ認識されますが、後者 `KC_SLEP` および `KC_WAKE` は3つの主要なオペレーティングシステム全てでサポートされるため、これらを使うことをお勧めします。Windows ではこれらのキーはすぐに機能しますが、macOS ではそれらはダイアログが表示されるまで押し続ける必要があります。

## ワンショットモディファイア
私の個人的な 'the' の問題を解決します。'The' ではなく 'the' あるいは 'THe' を間違って入力することがありました。ワンショットシフトはこれを軽減します。
https://github.com/tmk/tmk_keyboard/issues/67

## モディファイヤ/レイヤスタック
修飾キーあるいはレイヤは、レイヤの切り替えが適切に設定されていない場合、スタックするかもしれません。
修飾キーおよびレイヤ切り替えの場合、リリースイベント時に修飾キーの登録を解除する、もしくは前のレイヤに戻るために、目的のレイヤの同じ位置に `KC_TRANS` を配置する必要があります。

* https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#31-momentary-switching
* https://geekhack.org/index.php?topic=57008.msg1492604#msg1492604
* https://github.com/tmk/tmk_keyboard/issues/248


## メカニカルロックスイッチのサポート

この機能は [Alps](https://deskthority.net/wiki/Alps_SKCL_Lock) のような*メカニカルロックスイッチ*用です。以下を `config.h` に追加することで有効にすることができます:

```
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
```

この機能を有効にした後で、キーマップでキーコード `KC_LCAP`、`KC_LNUM` および `KC_LSCR` を使います。

古いビンテージメカニカルキーボードにはロックスイッチが付いている場合がありますが、最新のものにはありません。***ほとんどの場合この機能は必要なく、単にキーコード `KC_CAPS`、`KC_NLCK` および `KC_SLCK`*** を使います。

## セディーユ 'Ç' のような ASCII 以外の特別文字の入力

[ユニコード](ja/feature_unicode.md) 機能を見てください。

## macOS での `Fn` キー

ほとんどの Fn キーと異なり、Apple のキーボードの Fn キーには実際には独自のキーコードのようなものがあります。基本的な 6KRO HID レポートの6番目のキーコードの代わりになります -- つまり、Apple キーボードは実際には 5KRO のみです。

QMK にこのキーを送信させることは技術的に可能です。ただし、そうするには Fn キーの状態を追加するためにレポート形式の修正を必要とします。 
さらに悪いことに、キーボードの VID と PID が実際の Apple のキーボードのものと一致しない限り、認識されません。公式の QMK がこの機能をサポートすることで法的な問題が起きるため、サポートされることはないでしょう。

詳細については、[この issue](https://github.com/qmk/qmk_firmware/issues/2179) を見てください。

## Mac OSX でサポートされるキーは？
このソースコードから、どのキーコードが OSX でサポートされるかを知ることができます。

`usb_2_adb_keymap` 配列は、キーボード/キーパッドページの Page usages を ADB スキャンコード(OSX 内部キーコード)にマップします。

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/Cosmo_USB2ADB.c

`IOHIDConsumer::dispatchConsumerEvent` は Consumer page usages を処理します。

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/IOHIDConsumer.cpp


## Mac OSX での JIS キー
`無変換(Muhenkan)`, `変換(Henkan)`, `ひらがな(hiragana)` のような日本語 JIS キーボード固有のキーは OSX では認識されません。**Seil** を使ってこれらのキーを使うことができます。以下のオプションを試してください。

* PC キーボードで NFER キーを有効にする
* PC キーボードで XFER キーを有効にする
* PC キーボードで KATAKANA キーを有効にする

https://pqrs.org/osx/karabiner/seil.html


## RN-42 Bluetooth が Karabiner で動作しない
Karabiner - Mac OSX 上のキーマッピングツール - は、デフォルトでは RN-42 モジュールからの入力を無視します。Karabiner をキーボードで動作させるにはこのオプションを有効にする必要があります。
https://github.com/tekezo/Karabiner/issues/403#issuecomment-102559237

この問題の詳細についてはこれらを見てください。
https://github.com/tmk/tmk_keyboard/issues/213
https://github.com/tekezo/Karabiner/issues/403


## 単一のキーでの Esc と<code>&#96;</code>

[Grave Escape](ja/feature_grave_esc.md) 機能を見てください。

## Mac OSX での Eject
`KC_EJCT` キーコードは OSX で動作します。https://github.com/tmk/tmk_keyboard/issues/250
Windows 10 はコードを無視し、Linux/Xorg は認識しますが、デフォルトではマッピングがありません。

実際の Apple キーボードにある Eject キーコードは実際には分かりません。HHKB は Mac モードでは Eject キー (`Fn+f`) に `F20` を使いますが、これはおそらく Apple の Eject キーコードと同じではありません。


## `action_util.c` の `weak_mods` と `real_mods` は何か
___改善されるべきです___

real_mods は実際の物理的な修飾キーの状態を保持することを目的にしていますが、weak_mods は実際の修飾キーの状態に影響しない仮想あるいは一時的なモディファイアの状態を保持します。

物理的な左シフトキーを押しながら ACTION_MODS_KEY(LSHIFT, KC_A) を入力するとします

weak_mods では、
* (1) 左シフトキーを押し続ける: real_mods |= MOD_BIT(LSHIFT)
* (2) ACTION_MODS_KEY(LSHIFT, KC_A) を押す: weak_mods |= MOD_BIT(LSHIFT)
* (3) ACTION_MODS_KEY(LSHIFT, KC_A) を放す: weak_mods &= ~MOD_BIT(LSHIFT)
real_mods はモディファイアの状態を維持します。

weak mods 無しでは、
* (1) 左シフトキーを押し続ける: real_mods |= MOD_BIT(LSHIFT)
* (2) ACTION_MODS_KEY(LSHIFT, KC_A) を押す: real_mods |= MOD_BIT(LSHIFT)
* (3) ACTION_MODS_KEY(LSHIFT, KC_A) を放す: real_mods &= ~MOD_BIT(LSHIFT)
ここで、real_mods は 'physical left shift' '物理的な左シフト' の状態を見失います。

キーボードレポートが送信される時、weak_mods は real_mods と論理和がとられます。
https://github.com/tmk/tmk_core/blob/master/common/action_util.c#L57
