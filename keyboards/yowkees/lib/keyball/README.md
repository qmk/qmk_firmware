# Keyball Core Function Library

## Scroll snap mode

When scrolling with the trackball, the scroll direction is restricted.
This restriction is called "scroll snap".

The direction of restriction can be changed using special key codes.
You can also release this restriction.
It is called as "scroll snap mode"
The current mode is displayed on the OLED.

There are 3 modes for scroll snap.

1. Vertical (default): key code is `SSNP_VRT`, indicated as `VT`.
2. Horizontal: key code is `SSNP_HOR`, indicated as `HO`.
3. Free: key code is `SSNP_FRE`, indicated as `SCR`.

The scroll snap mode at startup is vertical,
but you can change it by saving the current mode with `KBC_SAVE`

## MEMO

This section contains notes regarding the specifications of this library.
Since the purpose is to keep a record in whatever form it takes,
a lot of Japanese is included.
If you would like to read it in English, please request a translation via issue or discussion.
Of course you can translate it for us. If you translate it,
please make pull requests to share it us.

### Scroll Snap Spec

この機能は config.h に `#define KEYBALL_SCROLLSNAP_ENABLE 0` を書き加えることで無効化できる。

トラックボールによるスクロールの方向を制限するのがスクロールスナップ。
現在のスクロールスナップには3つのモードがある。

* 垂直方向にスナップ (デフォルト)
* 水平方向にスナップ
* スナップしない自由スクロール

以上を `SSNP_VRT`, `SSNP_HOR`, `SSNP_FRE` の独自キーコードを用いて手動で切り替える。

#### up to 1.3.2

初期状態でトラックボールによるスクロールを垂直方向に制限(スナップ)している。
この振る舞いは config.h に `#define KEYBALL_SCROLLSNAP_ENABLE 1` を書き加えることで有効化できる。

この機能はスナップモードとフリーモードから構成される。
初期状態はスナップモードで、このモードではスクロール方向は垂直に制限される。
スナップモードで水平の一定方向に一定カウント(デフォルトは12)以上スクロールするとフリーモードに遷移する。
なおこのカウントはスクロール除数適用後のカウントである。
フリーモードでは制限が取り払われ、水平と垂直どちらにも自由にスクロールできる。
フリーモードで一定時間(デフォルトは 100 ミリ秒)、スクロール操作を行わないとスナップモードに遷移する。

フリーモードに遷移するためのカウント数を変更するには `KEYBALL_SCROLLSNAP_TENSION_THRESHOLD` を、
スナップモードに遷移するためのインターバル(ミリ秒)を変更するには `KEYBALL_SCROLLSNAP_RESET_TIMER` を、それぞれ config.h で設定できる。

以下はカウント数を 5 に、インターバルを 200 ミリ秒に変更する例:

```c
#define KEYBALL_SCROLLSNAP_TENSION_THRESHOLD 5
#define KEYBALL_SCROLLSNAP_RESET_TIMER 200
```

#### History of Scroll Snap

もともとは自由にスクロールできるようにしていた。
しかし思ったよりもボールの感度が高く一定方向だけに動かすのが難しく、
誤操作を誘発していた。
そのためなんらかのスナップ機能が必要だと判断した。

最初のスナップ機能は垂直・水平のどちらかの軸から一定角度以内で収まってるうちはそちらへスナップするとした。
しかし回転開始初期にはその移動量が極小かつセンサーの感度が高いので、
垂直に動かしたい時に水平にも極小量の移動が発生しておりスナップ方向が定まらない、
という問題が発生した。
人間は自分が思うほどには指を正確に動かせていなかった。

そこで一定方向に一定以上のカウントを検出するまでは一切スクロールしないようにした。
これは回転開始初期のスクロール量を読み捨てるに等しい。

しかしWebブラウザを思い浮かべてもらえればすぐにわかるように、
一般のユースケースでは垂直方向のスクロールを頻繁に利用する。
先の読み捨てにより、垂直方向のスクロールがワンテンポ遅れ、体験を大幅に損なうことが明らかになった。
この解決のためモード: 初期は垂直のみ、後に自由スクロールする、を導入した。

### Scroll Divider / スクロール除数

Keyballのセンサーは感度がとても高い。
そのため生の値をスクロール量としてしまうとスクロール操作がとても難しくなった。
そこで生の値をある数で割ってスクロールに適用する方式を採用した。
この時の割る数をスクロール除数と言っている。

スクロール除数は、体感として小さく制御する意味がなかったので、
1, 2, 4, 8, 16, 32, 64 というように2の乗数とした。
2の乗数であるのならば値の表現として $2 ^ n$ の $n$ で表せる。
またEEPROMに設定値を保存できるようにするために、
ビット数を節約する目的で $n$ が取りうる値は 1~7 の範囲とした。
結果実際の割る数は以下の式で計算できる。

$$ 2 ^ {(n - 1)} $$

$n$ の初期値は 4 で 1/8 になることを意味する。
この値は config.h で `KEYBALL_SCROLL_DIV_DEFAULT` マクロを定義することで変更できる。
これを0にすることは考慮していないので設定しないこと。

### Scroll Inhivitor

トラックボールの移動量をポインタに適用するかスクロールに適用するか、
Keyballは内部にスクロールモードという名のモードで管理している。
スクロールモードはキーコードやAPI呼び出しの任意のタイミングで切り替えられる。
デフォルトのキーマップでは特定のレイヤーの状態を
スクロールモードのオンオフに適用している。

当初はスクロールモードの切り替え直後に、
トラックボールの移動が意図しない適用先に適用されることが頻発した。
ポインタをブラウザまで動かした後にスクロールモードに変更すると、
意図していない方向にスクロールするといった体験になる。

そこでスクロールモード切替直後の一定時間は
一切のトラックボール操作を読み捨てることにした。
この読み捨てる時間のことを Scroll Inhivitor と名付けた。
この Scroll Inhivitor のデフォルト値は 50 ミリ秒である。
短い時間ではあるが結構効いている。

Scroll Inhivitor は config.h で `KEYBALL_SCROLLBALL_INHIVITOR` マクロを定義することで変更できる。
無効化したい場合は値として `0` を設定する。
興味があれば無効にしてみるのも面白いかもしれない。
