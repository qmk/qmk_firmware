# デバッグの FAQ

<!---
  original document: 0.12.45:docs/faq_debug.md
  git diff 0.12.45 HEAD -- docs/faq_debug.md | cat
-->

このページは、キーボードのトラブルシューティングについての様々な一般的な質問を説明します。

## デバッグ :id=debugging

`rules.mk` へ `CONSOLE_ENABLE = yes` の設定をするとキーボードはデバッグ情報を出力します。デフォルトの出力は非常に限られたものですが、デバッグモードをオンにすることでデバッグ情報の量を増やすことが出来ます。キーマップの `DEBUG` キーコードを使用するか、デバッグモードを有効にする[コマンド](ja/feature_command.md)機能を使用するか、以下のコードをキーマップに追加します。

```c
void keyboard_post_init_user(void) {
  // 希望する動作に合わせて値をカスタマイズします
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```

## デバッグツール

キーボードのデバッグに使えるツールは2つあります。

### QMK Toolbox を使ったデバッグ

互換性のある環境では、[QMK Toolbox](https://github.com/qmk/qmk_toolbox) を使うことでキーボードからのデバッグメッセージを表示できます。

### hid_listen を使ったデバッグ

ターミナルベースの方法がお好みですか？PJRC が提供する [hid_listen](https://www.pjrc.com/teensy/hid_listen.html) もデバッグメッセージの表示に使用できます。ビルド済みの実行ファイルは Windows、Linux、MacOS 用が用意されています。

## 独自のデバッグメッセージを送信する

[カスタムコード](ja/custom_quantum_functions.md)内からデバッグメッセージを出力すると便利な場合があります。それはとても簡単です。ファイルの先頭に `print.h` のインクルードを追加します:

```c
#include "print.h"
```

その後は、いくつかの異なった print 関数を使用することが出来ます:

* `print("string")`: シンプルな文字列を出力します
* `uprintf("%s string", var)`: フォーマットされた文字列を出力します
* `dprint("string")` デバッグモードが有効な場合のみ、シンプルな文字列を出力します
* `dprintf("%s string", var)`: デバッグモードが有効な場合のみ、フォーマットされた文字列を出力します

## デバッグの例

以下は現実世界での実際のデバッグ手法の例を集めたものです。

### マトリックス上のどの場所でキー押下が起こったか？

移植する場合や、PCB の問題を診断する場合、キー入力が正しくスキャンされているかどうかを確認することが役立つ場合があります。この手法でのロギングを有効化するには、`keymap.c` へ以下のコードを追加します。

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // コンソールが有効化されている場合、マトリックス上の位置とキー押下状態を出力します
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
  return true;
}
```

出力例
```text
Waiting for device:.......
Listening:
KL: kc: 169, col: 0, row: 0, pressed: 1
KL: kc: 169, col: 0, row: 0, pressed: 0
KL: kc: 174, col: 1, row: 0, pressed: 1
KL: kc: 174, col: 1, row: 0, pressed: 0
KL: kc: 172, col: 2, row: 0, pressed: 1
KL: kc: 172, col: 2, row: 0, pressed: 0
```

### キースキャンにかかる時間の測定

パフォーマンスの問題をテストする場合、スイッチマトリックスをスキャンする頻度を知ることが役立ちます。この手法でのロギングを有効化するには `config.h` へ以下のコードを追加します。

```c
#define DEBUG_MATRIX_SCAN_RATE
```

出力例
```text
  > matrix scan frequency: 315
  > matrix scan frequency: 313
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
```

## `hid_listen` がデバイスを認識できない
デバイスのデバッグコンソールの準備ができていない場合、以下のように表示されます:

```
Waiting for device:.........
```

デバイスが接続されると、*hid_listen* がデバイスを見つけ、以下のメッセージが表示されます:

```
Waiting for new device:.........................
Listening:
```

この 'Listening:' のメッセージが表示されない場合は、[Makefile] を `CONSOLE_ENABLE=yes` に設定してビルドしてみてください

Linux のような OS でデバイスにアクセスするには、特権が必要かもしれません。`sudo hid_listen` を試してください。

多くの Linux ディストリビューションでは、次の内容で `/etc/udev/rules.d/70-hid-listen.rules` というファイルを作成することで、root として hid_listen を実行する必要がなくなります:

```
SUBSYSTEM=="hidraw", ATTRS{idVendor}=="abcd", ATTRS{idProduct}=="def1", TAG+="uaccess", RUN{builtin}+="uaccess"
```

abcd と def1 をキーボードのベンダーとプロダクト IDに置き換えてください。文字は小文字でなければなりません。`RUN{builtin}+="uaccess"` の部分は、古いディストリビューションでのみ必要です。

## コンソールにメッセージが表示されない
以下を調べてください:
- *hid_listen* がデバイスを検出する。上記を見てください。
- **Magic**+d を使ってデバッグを有効にする。[マジックコマンド](https://github.com/tmk/tmk_keyboard#magic-commands)を見てください。
- `debug_enable=true` を設定します。[デバッグ](#debugging)を見てください。
- デバッグプリントの代わりに `print` 関数を使ってみてください。**common/print.h** を見てください。
- コンソール機能を持つ他のデバイスを切断します。[Issue #97](https://github.com/tmk/tmk_keyboard/issues/97) を見てください。
