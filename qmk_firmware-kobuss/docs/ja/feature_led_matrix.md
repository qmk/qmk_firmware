# LED マトリックスライト

<!---
  original document: 0.8.141:docs/feature_led_matrix.md
  git diff 0.8.141 HEAD -- docs/feature_led_matrix.md | cat
-->

この機能により、外部ドライバによって駆動される LED マトリックスを使うことができます。この機能は、バックライト制御と同じキーコードを使えるようにするため、バックライトシステムに接続します。

RGB LED を使いたい場合は、代わりに [RGB マトリックスサブシステム](ja/feature_rgb_matrix.md) を使うべきです。

## ドライバ設定

### IS31FL3731

I2C IS31FL3731 RGB コントローラを使ったアドレス指定可能な LED マトリックスライトのための基本的なサポートがあります:有効にするには、`rules.mk` に以下を追加します:

    LED_MATRIX_ENABLE = yes
    LED_MATRIX_DRIVER = IS31FL3731

1から4個の IS31FL3731 IC を使うことができます。キーボード上に存在しない IC の `LED_DRIVER_ADDR_<N>` 定義を指定しないでください。`config.h` に以下の項目を定義することができます:

| 変数 | 説明 | デフォルト |
|----------|-------------|---------|
| `ISSI_TIMEOUT` | (オプション) i2c メッセージを待つ時間 | 100 |
| `ISSI_PERSISTENCE` | (オプション) 失敗したメッセージをこの回数再試行する | 0 |
| `LED_DRIVER_COUNT` | (必須) LED ドライバ IC の数 |  |
| `LED_DRIVER_LED_COUNT` | (必須) 全てのドライバの LED ライトの数 |  |
| `LED_DRIVER_ADDR_1` | (必須) 最初の LED ドライバのアドレス |  |
| `LED_DRIVER_ADDR_2` | (オプション) 2番目の LED ドライバのアドレス |  |
| `LED_DRIVER_ADDR_3` | (オプション) 3番目の LED ドライバのアドレス |  |
| `LED_DRIVER_ADDR_4` | (オプション) 4番目の LED ドライバのアドレス |  |

2つのドライバを使う例です。

    // これは7ビットのアドレスで、左シフトされます
    // ビット0に0を設定すると書き込み、1を設定すると読み込みです (I2C プロトコルに従う)
    // アドレスは配線によって変わります:
    // 0b1110100 AD <-> GND
    // 0b1110111 AD <-> VCC
    // 0b1110101 AD <-> SCL
    // 0b1110110 AD <-> SDA
    #define LED_DRIVER_ADDR_1 0b1110100
    #define LED_DRIVER_ADDR_2 0b1110110
    
    #define LED_DRIVER_COUNT 2
    #define LED_DRIVER_1_LED_COUNT 25
    #define LED_DRIVER_2_LED_COUNT 24
    #define LED_DRIVER_LED_COUNT LED_DRIVER_1_LED_TOTAL + LED_DRIVER_2_LED_TOTAL

現在、2つのドライバのみがサポートされますが、4つの組み合わせ全てをサポートすることは簡単です。

`<keyboard>.c` に全ての LED を列挙する配列を定義します:

    const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
    /* これらの位置については IS31 マニュアルを参照してください
    *   driver
    *   |  LED address
    *   |  | */
    {0, C3_3},
    ....
    }

ここで、`Cx_y` は[データシート](http://www.issi.com/WW/pdf/31FL3731.pdf)およびヘッダファイル `drivers/issi/is31fl3731-simple.h` で定義されるマトリックス内の LED の位置です。`driver` は `config.h` で定義したドライバのインデックス(`0`、`1`、`2`、`3`のいずれか)です。

## キーコード

現在のところ、全ての LED マトリックスのキーコードは[バックライトシステム](ja/feature_backlight.md)と共有されます。

## LED マトリックス効果

現在のところ、LED マトリックス効果は作成されていません。

## カスタムレイヤー効果

カスタムレイヤー効果は `<keyboard>.c` 内で以下を定義することで行うことができます:

    void led_matrix_indicators_kb(void) {
    led_matrix_set_index_value(index, value);
    }

同様の関数がキーマップ内で `led_matrix_indicators_user` として動作します。

## サスペンド状態

サスペンド機能を使うには、以下を `<keyboard>.c` に追加します:

    void suspend_power_down_kb(void)
    {
    led_matrix_set_suspend_state(true);
    }
    
    void suspend_wakeup_init_kb(void)
    {
    led_matrix_set_suspend_state(false);
    }
