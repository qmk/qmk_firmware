## ポインティング デバイス

ポインティング デバイスは汎用的な機能の総称です: システム ポインタを移動します。マウスキーのような他のオプションも確かにありますが、これは簡単に変更可能で軽量であることを目指しています。機能を制御するためにカスタムキーを実装したり、他の周辺機器から情報を収集してここに直接挿入したりできます - QMKに処理を任せてください。

ポインティングデバイスを有効にするには、rules.mkの以下の行をコメントを解除します:

```
POINTING_DEVICE_ENABLE = yes
```

マウスレポートを操作するために、以下の関数を使うことができます:

* `pointing_device_get_report()` - ホストコンピュータに送信された情報を表す現在の report_mouse_t を返します。
* `pointing_device_set_report(report_mouse_t newMouseReport)` - ホストコンピュータに送信される report_mouse_t を上書きし保存します。

report_mouse_t (here "mouseReport") が以下のプロパティを持つことを覚えておいてください:

* `mouseReport.x` - これは、x軸の動き(+ 右へ、- 左へ)を表す -127 から 127 (128ではなく、USB HID仕様で定義されます)の符号付き整数です。
* `mouseReport.y` - これは、y軸の動き(+ 上へ、- 下へ)を表す -127 から 127 (128ではなく、USB HID仕様で定義されます)の符号付き整数です。
* `mouseReport.v` - これは、垂直スクロール(+ 上へ、- 下へ)を表す -127 から 127 (128ではなく、USB HID仕様で定義されます)の符号付き整数です。
* `mouseReport.h` - これは、水平スクロール(+ 右へ、- 左へ)を表す -127 から 127 (128ではなく、USB HID仕様で定義されます)の符号付き整数です。
* `mouseReport.buttons` - これは、最後の5ビットが使われる uint8_t です。これらのビットはマウスボタンの状態を表します - ビット 3 はマウスボタン 5、ビット 7 はマウスボタン 1 です。

マウスレポートが送信される時、x, y, v および h の値は 0 に設定されます (これは "pointing_device_send()" で行われます。この挙動を回避するために上書きすることができます)。このように、ボタンの状態は持続しますが、動きは1度だけ起こります。さらにカスタマイズするために、`pointing_device_init` および `pointing_device_task` の両方を上書きすることができます。

以下の例では、マウスをクリックし垂直および水平方向に127単位スクロールするためにカスタムキーが使われ、リリースされた時にそれを全て元に戻します - なぜならこれは完全に便利な機能だからです。聞いてください。以下は例です:

```
case MS_SPECIAL:
	report_mouse_t currentReport = pointing_device_get_report();
    if (record->event.pressed)
    {
        currentReport.v = 127;
		currentReport.h = 127;
		currentReport.buttons |= MOUSE_BTN1; //this is defined in report.h
    }
    else
    {
        currentReport.v = -127;
        currentReport.h = -127;
        currentReport.buttons &= ~MOUSE_BTN1;
    }
	pointing_device_set_report(currentReport);
    break;
```

マウスレポートは送信されるたびに 0 (ボタンを除く)に設定されるため、スクロールはそれぞれの場合に1度だけ発生することを思い出してください。
