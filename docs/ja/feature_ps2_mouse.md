# PS/2 マウスサポート :id=ps2-mouse-support

<!---
  original document: 0.9.44:docs/feature_ps2_mouse.md
  git diff 0.9.44 HEAD -- docs/feature_ps2_mouse.md | cat
-->

PS/2 マウス (例えばタッチパッドあるいはトラックポイント)を複合デバイスとしてキーボードに接続することができます。

トラックポイントを接続するには、トラックポイントモジュールを入手し (つまり、Thinkpad キーボードから部品を取って)、モジュールの各ピンの機能を特定し、コントローラとトラックポイントモジュールの間に必要な回路を作成する必要があります。詳細については、Deskthority Wiki の[トラックポイントハードウェア](https://deskthority.net/wiki/TrackPoint_Hardware)ページを参照してください。

PS/2 デバイスの接続は、USART(最善)、割り込み(次善)、 または busywait(非推奨)の3つのやり方が有ります。

## トラックポイントとコントローラ間の回路 :id=the-circuitry-between-trackpoint-and-controller

動作させるには、DATA と CLK のふたつのラインを 4.7k の抵抗で 5V にプルアップしてやる必要があります。

```
          DATA ----------+--------- PIN
                         |
                        4.7K
                         |
MODULE    5+  --------+--+--------- PWR   CONTROLLER
                      |
                     4.7K
                      |    
          CLK   ------+------------ PIN
```


## Busywait バージョン :id=busywait-version

注意: これは非推奨です。ギクシャクした動きや、未送信の入力が発生するかもしれません。可能であれば、割り込みまたは USART バージョンを使ってください。

rules.mk で:

```makefile
PS2_MOUSE_ENABLE = yes
PS2_USE_BUSYWAIT = yes
```

キーボードの config.h で:

```c
#ifdef PS2_USE_BUSYWAIT
#   define PS2_CLOCK_PORT  PORTD
#   define PS2_CLOCK_PIN   PIND
#   define PS2_CLOCK_DDR   DDRD
#   define PS2_CLOCK_BIT   1
#   define PS2_DATA_PORT   PORTD
#   define PS2_DATA_PIN    PIND
#   define PS2_DATA_DDR    DDRD
#   define PS2_DATA_BIT    2
#endif
```

## 割り込みバージョン :id=interrupt-version

以下の例はクロックのために D2 を、データのために D5 を使います。クロックには任意の INT あるいは PCINT ピンを、データには任意のピンを使うことができます。

rules.mk で:

```makefile
PS2_MOUSE_ENABLE = yes
PS2_USE_INT = yes
```

キーボードの config.h で:

```c
#ifdef PS2_USE_INT
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   2
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    5

#define PS2_INT_INIT()  do {    \
    EICRA |= ((1<<ISC21) |      \
              (0<<ISC20));      \
} while (0)
#define PS2_INT_ON()  do {      \
    EIMSK |= (1<<INT2);         \
} while (0)
#define PS2_INT_OFF() do {      \
    EIMSK &= ~(1<<INT2);        \
} while (0)
#define PS2_INT_VECT   INT2_vect
#endif
```

## USART バージョン :id=usart-version

ATMega32u4 で USART を使うには、クロックのために PD5 を、データのために PD2 を使う必要があります。それらのいずれかが利用できない場合は、割り込みバージョンを使う必要があります。

rules.mk で:

```makefile
PS2_MOUSE_ENABLE = yes
PS2_USE_USART = yes
```

キーボードの config.h で:

```c
#ifdef PS2_USE_USART
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   5
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    2

/* 同期、奇数パリティ、1-bit ストップ、8-bit データ、立ち下がりエッジでサンプル */
/* CLOCK の DDR を入力としてスレーブに設定 */
#define PS2_USART_INIT() do {   \
    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
    UCSR1C = ((1 << UMSEL10) |  \
              (3 << UPM10)   |  \
              (0 << USBS1)   |  \
              (3 << UCSZ10)  |  \
              (0 << UCPOL1));   \
    UCSR1A = 0;                 \
    UBRR1H = 0;                 \
    UBRR1L = 0;                 \
} while (0)
#define PS2_USART_RX_INT_ON() do {  \
    UCSR1B = ((1 << RXCIE1) |       \
              (1 << RXEN1));        \
} while (0)
#define PS2_USART_RX_POLL_ON() do { \
    UCSR1B = (1 << RXEN1);          \
} while (0)
#define PS2_USART_OFF() do {    \
    UCSR1C = 0;                 \
    UCSR1B &= ~((1 << RXEN1) |  \
                (1 << TXEN1));  \
} while (0)
#define PS2_USART_RX_READY      (UCSR1A & (1<<RXC1))
#define PS2_USART_RX_DATA       UDR1
#define PS2_USART_ERROR         (UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1)))
#define PS2_USART_RX_VECT       USART1_RX_vect
#endif
```

## 追加の設定 :id=additional-settings

### PS/2 マウス機能 :id=ps2-mouse-features

以下の PS/2 マウスプロトコルによってサポートされる設定を有効にします。

```c
/* デフォルトのストリームモードの代わりにリモートモードを使います (リンクを見てください) */
#define PS2_MOUSE_USE_REMOTE_MODE

/* マウスあるいはタッチパッドでスクロールホイールあるいはスクロールジェスチャーを有効にします */
#define PS2_MOUSE_ENABLE_SCROLLING

/* 一部のマウスでは、スクロールマスクを設定する必要があります。デフォルトは 0xFF です。*/
#define PS2_MOUSE_SCROLL_MASK 0x0F

/* ホストに送信する前に、動きに変換を適用します (リンクを見てください) */
#define PS2_MOUSE_USE_2_1_SCALING

/* ps2ホストを初期化した後の待機時間 */
#define PS2_MOUSE_INIT_DELAY 1000 /* Default */
```

ps2_mouse.h をインクルードして、以下の関数を呼び出すこともできます。

```c
void ps2_mouse_disable_data_reporting(void);

void ps2_mouse_enable_data_reporting(void);

void ps2_mouse_set_remote_mode(void);

void ps2_mouse_set_stream_mode(void);

void ps2_mouse_set_scaling_2_1(void);

void ps2_mouse_set_scaling_1_1(void);

void ps2_mouse_set_resolution(ps2_mouse_resolution_t resolution);

void ps2_mouse_set_sample_rate(ps2_mouse_sample_rate_t sample_rate);
```

### 細かい調整 :id=fine-control

マウスの感度と速度を変更するには以下の定義を使います。
注意: 同じ効果のために `ps2_mouse_set_resolution` も使うことができます (ほとんどのタッチパッドではサポートされません)。

```c
#define PS2_MOUSE_X_MULTIPLIER 3
#define PS2_MOUSE_Y_MULTIPLIER 3
#define PS2_MOUSE_V_MULTIPLIER 1
```

### スクロールボタン :id=scroll-button

トラックポイントを使っている場合は、スクロールのためにそれを使えるようにしたいでしょう。
押された時にマウスを移動させる代わりにスクロールさせる「スクロールボタン」を有効にすることができます。
この機能を有効にするには、以下のようにスクロールボタンマスクを設定する必要があります:

```c
#define PS2_MOUSE_SCROLL_BTN_MASK (1<<PS2_MOUSE_BUTTON_MIDDLE) /* Default */
```

スクロールボタン機能を無効にするには:

```c
#define PS2_MOUSE_SCROLL_BTN_MASK 0
```

利用可能なボタンは:

```c
#define PS2_MOUSE_BTN_LEFT      0
#define PS2_MOUSE_BTN_RIGHT     1
#define PS2_MOUSE_BTN_MIDDLE    2
```

ボタン定数を `|` で結合したマスクでボタンを組み合わせることができます。

スクロールボタンマスクを設定したら、スクロールボタンの送信間隔を設定する必要があります。
これは、スクロールボタンが離された場合に、スクロールボタンがホストに送信されるまでの間隔です。
この時間が経過すると、マウスはスクロールして送信されなくなります。

```c
#define PS2_MOUSE_SCROLL_BTN_SEND 300 /* Default */
```

スクロールボタンの送信を無効にするには:

```c
#define PS2_MOUSE_SCROLL_BTN_SEND 0
```

以下の定義でスクロールの細かい制御がサポートされます:

```c
#define PS2_MOUSE_SCROLL_DIVISOR_H 2
#define PS2_MOUSE_SCROLL_DIVISOR_V 2
```

### マウスとスクロールの軸の反転 :id=invert-mouse-and-scroll-axes

X 軸と Y 軸を反転するには、以下を config.h に配置します:

```c
#define PS2_MOUSE_INVERT_X
#define PS2_MOUSE_INVERT_Y
```

スクロールの軸を逆にするには、以下を config.h に配置します:

```c
#define PS2_MOUSE_INVERT_H
#define PS2_MOUSE_INVERT_V
```

### マウスの軸の回転 :id=rotate-mouse-axes

デバイスの出力を時計回りに 90 か 180 か 270 度変換します。

デバイスの向きを補正する場合は、出力を逆の方向に同じ量だけ回転します。例えば、通常のデバイスの向きが北向きの場合、以下のように補正します:

```c
#define PS2_MOUSE_ROTATE 270 /* 東向きのデバイスの向きの補正*/
```
```c
#define PS2_MOUSE_ROTATE 180 /* 南向きのデバイスの向きの補正*/
```
```c
#define PS2_MOUSE_ROTATE 90 /* 西向きのデバイスの向きの補正*/
```

### デバッグ設定 :id=debug-settings

マウスをデバッグするには、`debug_mouse = true` を追加するか、ブートマジックを使って有効にします。

```c
/* マウスレポートをデバッグするには */
#define PS2_MOUSE_DEBUG_HID
#define PS2_MOUSE_DEBUG_RAW
```

### 動作フック :id=movement-hook

ホストに送信される前にキーマップでマウスの動作を処理します。使用例として、
ノイズのフィルタリング、加速の追加、レイヤーの自動アクティブ化が含まれます。
使用するには、キーマップで次の関数を定義します:

```c
void ps2_mouse_moved_user(report_mouse_t *mouse_report);
```
