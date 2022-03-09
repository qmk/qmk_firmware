# ポインティングデバイス :id=pointing-device

<!---
  original document: 0.12.41:docs/feature_pointing_device.md
  git diff 0.12.41 HEAD -- docs/feature_pointing_device.md | cat
-->

ポインティングデバイスは汎用的な機能の総称です: システムポインタを移動します。マウスキーのような他のオプションも確かにありますが、これは簡単に変更可能で軽量であることを目指しています。機能を制御するためにカスタムキーを実装したり、他の周辺機器から情報を収集してここに直接挿入したりできます - QMK に処理を任せてください。

ポインティングデバイスを有効にするには、rules.mk の以下の行のコメントを解除します:

```makefile
POINTING_DEVICE_ENABLE = yes
```

マウスレポートを操作するために、以下の関数を使うことができます:

* `pointing_device_get_report()` - ホストコンピュータに送信された情報を表す現在の report_mouse_t を返します。
* `pointing_device_set_report(report_mouse_t mouse_report)` - ホストコンピュータに送信される report_mouse_t を上書き保存します。

report_mouse_t (ここでは "mouseReport") が以下のプロパティを持つことを覚えておいてください:

* `mouseReport.x` - これは、x軸の動き(+ 右へ、- 左へ)を表す -127 から 127 (128ではなく、USB HID 仕様で定義されています)の符号付き整数です。
* `mouseReport.y` - これは、y軸の動き(+ 上へ、- 下へ)を表す -127 から 127 (128ではなく、USB HID 仕様で定義されています)の符号付き整数です。
* `mouseReport.v` - これは、垂直スクロール(+ 上へ、- 下へ)を表す -127 から 127 (128ではなく、USB HID 仕様で定義されています)の符号付き整数です。
* `mouseReport.h` - これは、水平スクロール(+ 右へ、- 左へ)を表す -127 から 127 (128ではなく、USB HID 仕様で定義されています)の符号付き整数です。
* `mouseReport.buttons` - これは uint8_t で、8ビット全てを使っています。これらのビットはマウスボタンの状態を表します - ビット 0 はマウスボタン 1、ビット 7 はマウスボタン 8 です。

マウスレポートに必要な変更を行ったら、それを送信する必要があります:

* `pointing_device_send()` - マウスレポートをホストに送信し、レポートをゼロにします。

マウスレポートが送信されると、x、y、v、h のいずれの値も 0 に設定されます (これは `pointing_device_send()` で行われます。この挙動を回避するためにオーバーライドすることができます)。このように、ボタンの状態は持続しますが、動きは1度だけ起こります。さらにカスタマイズするために、`pointing_device_init` と `pointing_device_task` のどちらもオーバーライドすることができます。

さらに、デフォルトでは、`pointing_device_send()` はレポートが実際に変更された場合のみレポートを送信します。これにより、マウスレポートが継続的に送信されてホストシステムが起動されたままになることを防ぎます。この動作は、独自の `pointing_device_send()` 関数を作成することで変更できます。

また、`has_mouse_report_changed(new_report, old_report)` 関数を使って、レポートが変更されたかどうかを確認できます。(訳注：独自の `pointing_device_send()` 関数を作成する場合でも、その中で `has_mouse_report_changed(new_report, old_report)` 関数でチェックして、デフォルトの `pointing_device_send()` と類似の無駄なレポートの抑制をして、ホストシステムがスリープ状態に入れる余地を残すようにしておくのが良いでしょう。)

以下の例では、カスタムキーを使ってマウスをクリックし垂直および水平方向に127単位スクロールし、リリースされた時にそれを全て元に戻します - なぜならこれは完全に便利な機能だからです。いいですか、以下はひとつの例です:

```c
case MS_SPECIAL:
    report_mouse_t currentReport = pointing_device_get_report();
    if (record->event.pressed) {
        currentReport.v = 127;
        currentReport.h = 127;
        currentReport.buttons |= MOUSE_BTN1;  // this is defined in report.h
    } else {
        currentReport.v = -127;
        currentReport.h = -127;
        currentReport.buttons &= ~MOUSE_BTN1;
    }
    pointing_device_set_report(currentReport);
    pointing_device_send();
    break;
```

マウスレポートは送信されるたびに 0 (ボタンを除く)に設定されることを思い出してください。そのため、スクロールはそれぞれの場合に1度だけ発生します。
