# テストとデバッグ

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: ed0575fc8:docs/newbs_testing_debugging.md
  git diff ed0575fc8 HEAD -- docs/newbs_testing_debugging.md | cat
-->

カスタムファームウェアをキーボードへ書き込んだら、テストする準備が整います。運が良ければ全て問題なく動作しているはずですが、もしそうでなければこのドキュメントがどこが悪いのか調べるのに役立ちます。

## テスト

通常、キーボードをテストするのは非常に簡単です。全てのキーをひとつずつ押して、期待されるキーが送信されていることを確認します。キーを押したことを見逃さないためのプログラムもあります。

メモ：　これらのプログラムはQMKによって提供・承認されたものではありません。

* [QMK Configurator](https://config.qmk.fm/#/test/) (Web Based)
* [Switch Hitter](https://web.archive.org/web/20190413233743/https://elitekeyboards.com/switchhitter.php) (Windows Only)
* [Keyboard Viewer](https://www.imore.com/how-use-keyboard-viewer-your-mac) (Mac Only)
* [Keyboard Tester](http://www.keyboardtester.com) (Web Based)
* [Keyboard Checker](http://keyboardchecker.com) (Web Based)

## デバッグ

`rules.mk`へ`CONSOLE_ENABLE = yes`の設定をするとキーボードはデバッグ情報を出力します。デフォルトの出力は非常に限られたものですが、デバッグモードをオンにすることでデバッグ情報の量を増やすことが出来ます。キーマップの`DEBUG`キーコードを使用するか、デバッグモードを有効にする [Command](ja/feature_command.md) 機能を使用するか、以下のコードをキーマップに追加します。

```c
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```

### QMK Toolboxを使ったデバッグ

互換性のある環境では、[QMK Toolbox](https://github.com/qmk/qmk_toolbox)を使うことでキーボードからのデバッグメッセージを表示できます。

### hid_listenを使ったデバッグ

ターミナルベースの方法がお好みですか？PJRCが提供する[hid_listen](https://www.pjrc.com/teensy/hid_listen.html)もデバッグメッセージの表示に使用できます。ビルド済みの実行ファイルはWindows, Linux, MacOS用が用意されています。

<!-- FIXME: Describe the debugging messages here. -->

## 独自のデバッグメッセージを送信する

[custom code](ja/custom_quantum_functions.md)内からデバッグメッセージを出力すると便利な場合があります。それはとても簡単です。ファイルの先頭に`print.h`のインクルードを追加します:

    #include <print.h>

そのあとは、いくつかの異なったprint関数を使用することが出来ます。

* `print("string")`: シンプルな文字列を出力します
* `uprintf("%s string", var)`: フォーマットされた文字列を出力します
* `dprint("string")` デバッグモードが有効な場合のみ、シンプルな文字列を出力します
* `dprintf("%s string", var)`: デバッグモードが有効な場合のみ、フォーマットされた文字列を出力します

## デバッグの例

以下は現実世界での実際のデバッグ手法の例を集めたものです。追加情報は[Debugging/Troubleshooting QMK](ja/faq_debug.md)を参照してください。

### マトリックス上のどの場所でキー押下が起こったか？

移植する、PCBの問題を診断する場合、キー入力が正しくスキャンされているかどうかを確認することが役立つ場合があります。この手法でのロギングを有効化するには、`keymap.c`へ以下のコードを追加します。

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // コンソールが有効化されている場合、マトリックス上の位置とキー押下状態を出力します
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
  return true;
}
```

出力の例
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

パフォーマンスの問題をテストする場合、スイッチマトリックスをスキャンする頻度を知ることが役立ちます。この手法でのロギングを有効化するには`config.h`へ以下のコードを追加します。


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
