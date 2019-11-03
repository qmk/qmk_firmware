## PS/2 マウスサポート

PS/2マウス (例えばタッチパッドあるいはトラックポイント)を複合デバイスとしてキーボードに接続することができます。

トラックポイントを接続するには、トラックポイント モジュール (つまり、Thinkpadキーボードから収穫)を取得し、モジュールの各ピンの機能を特定し、コントローラとトラックポイント モジュールの間に必要な回路を作成する必要があります。詳細については、Deskthority Wikiの[トラックポイント ハードウェア](https://deskthority.net/wiki/TrackPoint_Hardware)ページを参照してください。

PS/2デバイスを接続するために3つの利用可能なモードがあります: USART (最善), interrupts (次善) あるいは busywait (非推奨)。

### トラックポイントとコントローラの間の回路

動作させるには、DATA と CLK と 回線5+ の間の2つの回線に 4.7Kのドラッグが必要です。

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


### Busywait バージョン

注意: これは非推奨です。ギクシャクした動きや、未送信の入力が発生するかもしれません。可能であれば、interrupt または USART バージョンを使ってください。

rules.mkで:

```
PS2_MOUSE_ENABLE = yes
PS2_USE_BUSYWAIT = yes
```

キーボードのconfig.hで:

```
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

### Interrupt バージョン

以下の例はクロックのためにD2を、データのためにD5を使います。クロックには任意のINTあるいはPCINTピンを、データには任意のピンを使うことができます。

rules.mkで:

```
PS2_MOUSE_ENABLE = yes
PS2_USE_INT = yes
```

キーボードのconfig.hで:

```
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

### USART バージョン

ATMega32u4でUSARTを使うには、クロックのために PD5 を、データのために PD2 を使う必要があります。それらのいずれかが利用できない場合は、interrupt バージョンを使う必要があります。

rules.mkで:

```
PS2_MOUSE_ENABLE = yes
PS2_USE_USART = yes
```

キーボードのconfig.hで:

```
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
/* CLOCKのDDRを入力としてスレーブに設定 */
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

### 追加の設定

#### PS/2 マウス機能

これらはPS/2マウスプロトコルによってサポートされる設定を有効にします。

```
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

以下の関数をps2_mouse.hから呼び出すこともできます

```
void ps2_mouse_disable_data_reporting(void);

void ps2_mouse_enable_data_reporting(void);

void ps2_mouse_set_remote_mode(void);

void ps2_mouse_set_stream_mode(void);

void ps2_mouse_set_scaling_2_1(void);

void ps2_mouse_set_scaling_1_1(void);

void ps2_mouse_set_resolution(ps2_mouse_resolution_t resolution);

void ps2_mouse_set_sample_rate(ps2_mouse_sample_rate_t sample_rate);
```

#### 微調整

マウスの感度と速度を変更するために以下の定義を使います。
注意: 同じ効果のために`ps2_mouse_set_resolution` も使うことができます (ほとんどのタッチパッドではサポートされません)。

```
#define PS2_MOUSE_X_MULTIPLIER 3
#define PS2_MOUSE_Y_MULTIPLIER 3
#define PS2_MOUSE_V_MULTIPLIER 1
```

#### スクロールボタン

トラックポイントを使っている場合は、スクロールのためにそれを使えるようにしたいでしょう。
押された時に移動の代わりにスクロールさせる "scroll button/s" を有効にすることができます。
この機能を有効にするには、以下のようにスクロールボタンマスクを設定する必要があります:

```
#define PS2_MOUSE_SCROLL_BTN_MASK (1<<PS2_MOUSE_BUTTON_MIDDLE) /* Default */
```

スクロールボタン機能を無効にするには:

```
#define PS2_MOUSE_SCROLL_BTN_MASK 0
```

利用可能なボタンは:

```
#define PS2_MOUSE_BTN_LEFT      0
#define PS2_MOUSE_BTN_RIGHT     1
#define PS2_MOUSE_BTN_MIDDLE    2
```

ボタンを一緒に `|` することでマスク内でボタンを組み合わせることができます。

スクロールボタン マスクを設定したら、スクロールボタンの送信間隔を設定する必要があります。
これは、スクロールボタンが放された場合にホストに送信されるまでの間隔です。
この間隔の後で、マウスはスクロールし、送信されません。

```
#define PS2_MOUSE_SCROLL_BTN_SEND 300 /* Default */
```

スクロールボタンの送信を無効にするには:
```
#define PS2_MOUSE_SCROLL_BTN_SEND 0
```

以下の定義でスクロールの詳細な制御がサポートされます:

```
#define PS2_MOUSE_SCROLL_DIVISOR_H 2
#define PS2_MOUSE_SCROLL_DIVISOR_V 2
```

#### マウスとスクロールの軸の反転

XとY軸を反転するには、以下を配置します:

```
#define PS2_MOUSE_INVERT_X
#define PS2_MOUSE_INVERT_Y
```

config.hに。

スクロールの軸を逆にするには、以下を配置します:

```
#define PS2_MOUSE_INVERT_H
#define PS2_MOUSE_INVERT_V
```

config.hに。

#### デバッグ設定

マウスをデバッグするには、`debug_mouse = true`を追加するか、ブートマジックを介して有効にします。

```
/* マウスレポートをデバッグするには */
#define PS2_MOUSE_DEBUG_HID
#define PS2_MOUSE_DEBUG_RAW
```
