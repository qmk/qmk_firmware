# LED マトリックス ライト

この機能により、外部ドライバによって駆動されるLEDマトリクスを使うことができます。バックライトシステムにフックするため、制御するためにバックライトと同じキーコードを使うことができます。

RGB LEDを使いたい場合は、代わりに[RGB Matrix Subsystem](feature_rgb_matrix.md)を使うべきです。

## ドライバ設定

### IS31FL3731

There is basic support for addressable LED matrix lighting with the I2C IS31FL3731 RGB controller. 有効にするには、`rules.mk`に以下を追加します:

    LED_MATRIX_ENABLE = IS31FL3731

1から4個の IS31FL3731 IC を使うことができます。キーボード上に存在しないICの `LED_DRIVER_ADDR_<N>` 定義を指定しないでください。`config.h`に以下の項目を定義することができます:

| 変数 | 説明 | デフォルト |
|----------|-------------|---------|
| `ISSI_TIMEOUT` | (オプション) i2cメッセージを待つ時間 | 100 |
| `ISSI_PERSISTENCE` | (オプション) 失敗したメッセージを何度も再試行する | 0 |
| `LED_DRIVER_COUNT` | (必須) LED ドライバ ICの数 |  |
| `LED_DRIVER_LED_COUNT` | (必須) 全てのドライバのLEDライトの数 |  |
| `LED_DRIVER_ADDR_1` | (必須) 最初のLEDドライバのアドレス |  |
| `LED_DRIVER_ADDR_2` | (オプション) 2番目のLEDドライバのアドレス |  |
| `LED_DRIVER_ADDR_3` | (オプション) 3番目のLEDドライバのアドレス |  |
| `LED_DRIVER_ADDR_4` | (オプション) 4番目のLEDドライバのアドレス |  |

2つのドライバを使う例です。

    // This is a 7-bit address, that gets left-shifted and bit 0
    // set to 0 for write, 1 for read (as per I2C protocol)
    // The address will vary depending on your wiring:
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

現在、2つのドライバのみがサポートされますが、4つの組み合わせ全てをサポートするのは簡単です。

`<keyboard>.c`に全てのLEDをリストする配列を定義します:

    const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
    /* Refer to IS31 manual for these locations
    *   driver
    *   |  LED address
    *   |  | */
    {0, C3_3},
    ....
    }

ここで、`Cx_y`は[データシート](http://www.issi.com/WW/pdf/31FL3731.pdf)およびヘッダファイル`drivers/issi/is31fl3731-simple.h`で定義されるマトリックス内のLEDの位置です。`driver`は`config.h`で定義したドライバのインデックスです (`0`, `1`, `2`あるいは`3` )。

## キーコード

現在のところ、全てのLEDマトリックスのキーコードは[バックライト システム](feature_backlight.md)と共有されます。

## LEDマトリックス効果

現在のところ、LEDマトリックス効果は作成されていません。

## カスタム レイヤ効果

カスタム レイヤ効果は`<keyboard>.c`内で以下を定義することで行うことができます:

    void led_matrix_indicators_kb(void) {
    led_matrix_set_index_value(index, value);
    }

同様の関数がキーマップ内で`led_matrix_indicators_user`として動作します。

## 中断状態

中断機能を使うには、以下を`<keyboard>.c`に追加します:

    void suspend_power_down_kb(void)
    {
    led_matrix_set_suspend_state(true);
    }
    
    void suspend_wakeup_init_kb(void)
    {
    led_matrix_set_suspend_state(false);
    }
