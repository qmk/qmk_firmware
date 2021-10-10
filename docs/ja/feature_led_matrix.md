# LED マトリックスライト

<!---
  original document: 0.14.14:docs/feature_led_matrix.md
  git diff 0.14.14 HEAD -- docs/feature_led_matrix.md | cat
-->

この機能により、外部ドライバによって駆動される LED マトリックスを使うことができます。この機能は、バックライト制御と同じキーコードを使えるようにするため、バックライトシステムに接続します。

RGB LED を使いたい場合は、代わりに [RGB マトリックスサブシステム](ja/feature_rgb_matrix.md) を使うべきです。

## ドライバ設定 :id=driver-configuration
---
### IS31FL3731 :id=is31fl3731

I2C IS31FL3731 RGB コントローラを使ったアドレス指定可能な LED マトリックスライトのための基本的なサポートがあります。有効にするには、`rules.mk` に以下を追加します:

```make
LED_MATRIX_ENABLE = yes
LED_MATRIX_DRIVER = IS31FL3731
```

1から4個の IS31FL3731 IC を使うことができます。キーボード上に存在しない IC の `LED_DRIVER_ADDR_<N>` 定義を指定しないでください。`config.h` に以下の項目を定義することができます:

| 変数                | 説明                                                | デフォルト |
|---------------------|-----------------------------------------------------|------------|
| `ISSI_TIMEOUT`      | (オプション) i2c メッセージを待つ時間               | 100        |
| `ISSI_PERSISTENCE`  | (オプション) 失敗したメッセージをこの回数再試行する | 0          |
| `LED_DRIVER_COUNT`  | (必須) LED ドライバ IC の数                         |            |
| `DRIVER_LED_TOTAL`  | (必須) 全てのドライバの LED ライトの数              |            |
| `LED_DRIVER_ADDR_1` | (必須) 最初の LED ドライバのアドレス                |            |
| `LED_DRIVER_ADDR_2` | (オプション) 2番目の LED ドライバのアドレス         |            |
| `LED_DRIVER_ADDR_3` | (オプション) 3番目の LED ドライバのアドレス         |            |
| `LED_DRIVER_ADDR_4` | (オプション) 4番目の LED ドライバのアドレス         |            |

2つのドライバを使う例です。

```c
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
#define LED_DRIVER_1_LED_TOTAL 25
#define LED_DRIVER_2_LED_TOTAL 24
#define DRIVER_LED_TOTAL (LED_DRIVER_1_LED_TOTAL + LED_DRIVER_2_LED_TOTAL)
```

!> 括弧に注意してください。`LED_DRIVER_LED_TOTAL` がコードの中で使われ展開されると、追加の計算が適用される前に値が加算されます。例として、`rand() % (LED_DRIVER_1_LED_TOTAL + LED_DRIVER_2_LED_TOTAL)` は`rand() % LED_DRIVER_1_LED_TOTAL + LED_DRIVER_2_LED_TOTAL` とはかなり異なる結果になります。

`<keyboard>.c` に全ての LED を列挙する配列を定義します:

```c
const is31_led __flash g_is31_leds[DRIVER_LED_TOTAL] = {
/* これらの位置については IS31 マニュアルを参照してください
 *   driver
 *   |  LED address
 *   |  | */
   { 0, C1_1  },
   { 0, C1_15 },
   // ...
}
```

ここで、`Cx_y` は[データシート](https://www.issi.com/WW/pdf/31FL3731.pdf)およびヘッダファイル `drivers/led/issi/is31fl3731-simple.h` で定義されるマトリックス内の LED の位置です。`driver` は `config.h` で定義したドライバのインデックス(`0`、`1`、`2`、`3`のいずれか)です。

---

## 共通の設定 :id=common-configuration

この時点から、全てのドライバについて設定が同じになります。`led_config_t` 構造体は、led インデックスルックアップテーブルへのキーの電気的なマトリックス、キーボード上の各 LED の物理的な位置、LED が表明する場合は LED のキーの種類と使い方を提供します。以下は簡単な例です:

```c
led_config_t g_led_config = { {
  // LED インデックスへのキーマトリックス
  {   5, NO_LED, NO_LED,   0 },
  { NO_LED, NO_LED, NO_LED, NO_LED },
  {   4, NO_LED, NO_LED,   1 },
  {   3, NO_LED, NO_LED,   2 }
}, {
  // 物理位置に対する LED インデックス
  { 188,  16 }, { 187,  48 }, { 149,  64 }, { 112,  64 }, {  37,  48 }, {  38,  16 }
}, {
  // フラグへの LED インデックス
  1, 4, 4, 4, 4, 1
} };
```

最初の部分、`// LED インデックスへのキーマトリックス`は、キーの電気的なマトリックス 行&列を使ってこの LED が表すキーをシステムに伝えます。 2番目の部分、`// 物理位置に対する LED インデックス`は、キーボード上の LED の物理的な `{ x, y }` 位置を表します。`{ x, y }` のデフォルトの予期される値の範囲は `{ 0..224, 0..64 }` の両端を含む範囲です。このデフォルトの予想範囲は、アニメーションのキーボードの中心を計算する効果によるものです。これらの位置を計算する最も簡単な方法は、キーボードが格子であり、キーボードの左上が `{ x, y }` 座標 `{ 0, 0 }` を表し、キーボードの右下が `{ 224, 64 }` を表すと想像することです。これを基礎として、物理位置を計算するために以下の式を使うことができます:

```c
x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION
y =  64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION
```

ここで、NUMBER_OF_COLS、NUMBER_OF_ROWS、COL_POSITION & ROW_POSITION は全て、電気的レイアウトではなく、キーボードの物理的レイアウトに基づいています。

前述のように、キーボードの中心はデフォルトで `{ 112, 32 }` であることを期待されますが、LED の物理的な `{ x, y }` 位置をより正確に計算したい場合は、これを変更することができます。キーボードの設計者は、キーボードの新しい中心を使って、あるいは `{ x, y }` 値のより多くの可能性を許可して、config.h の中で `#define LED_MATRIX_CENTER { 112, 32 }` を実装することができます。x または y の最大値は 255 で、推奨される最大は 224 であることに注意してください。これにより、アニメーションがリセットされる前に余裕が生まれます。

`// フラグへの LED インデックス` は、特定の LED が特定のタイプであるかどうかのビットマスクです。LED は1種類のみに設定することをお勧めします。

## フラグ :id=flags

| 定義                         | 値     | 説明                                                                    |
|------------------------------|--------|-------------------------------------------------------------------------|
| `HAS_FLAGS(bits, flags)`     | *n/a*  | `bits` に全ての `flags` が設定されている場合、`true` と評価されます     |
| `HAS_ANY_FLAGS(bits, flags)` | *n/a*  | `bits` にいずれかの `flags` が設定されている場合、`true` と評価されます |
| `LED_FLAG_NONE`              | `0x00` | この LED にフラグが設定されていない場合                                 |
| `LED_FLAG_ALL`               | `0xFF` | この LED に全てのフラグが設定されている場合                             |
| `LED_FLAG_MODIFIER`          | `0x01` | LED が修飾キーの上にある場合                                            |
| `LED_FLAG_KEYLIGHT`          | `0x04` | LED がキーのバックライト用の場合                                        |
| `LED_FLAG_INDICATOR`         | `0x08` | LED がキーボードの状態のインジケータの場合                              |

## キーコード :id=keycodes

現在のところ、全ての LED マトリックスのキーコードは[バックライト機能](ja/feature_backlight.md)と共有されます。

| キー      | 説明                                           |
|-----------|------------------------------------------------|
| `BL_TOGG` | LED マトリックスのオンあるいはオフを切り替える |
| `BL_STEP` | モードを循環する                               |
| `BL_ON`   | LED マトリックスをオンにする                   |
| `BL_OFF`  | LED マトリックスをオフにする                   |
| `BL_INC`  | 明度を上げる                                   |
| `BL_DEC`  | 明度を下げる                                   |

## LED マトリックスの効果 :id=led-matrix-effects

以下は現在利用可能な効果です:

```c
enum led_matrix_effects {
    LED_MATRIX_NONE = 0,
    LED_MATRIX_SOLID = 1,           // Static single val, no speed support
    LED_MATRIX_ALPHAS_MODS,         // Static dual val, speed is val for LEDs marked as modifiers
    LED_MATRIX_BREATHING,           // Cycling brightness animation
    LED_MATRIX_BAND,                // Band fading brightness scrolling left to right
    LED_MATRIX_BAND_PINWHEEL,       // 3 blade spinning pinwheel fades brightness
    LED_MATRIX_BAND_SPIRAL,         // Spinning spiral fades brightness
    LED_MATRIX_CYCLE_LEFT_RIGHT,    // Full gradient scrolling left to right
    LED_MATRIX_CYCLE_UP_DOWN,       // Full gradient scrolling top to bottom
    LED_MATRIX_CYCLE_OUT_IN,        // Full gradient scrolling out to in
    LED_MATRIX_DUAL_BEACON,         // Full gradient spinning around center of keyboard
#if defined(LED_MATRIX_KEYPRESSES) || defined(LED_MATRIX_KEYRELEASES)
    LED_MATRIX_SOLID_REACTIVE_SIMPLE,   // Pulses keys hit then fades out
    LED_MATRIX_SOLID_REACTIVE_WIDE       // Value pulses near a single key hit then fades out
    LED_MATRIX_SOLID_REACTIVE_MULTIWIDE  // Value pulses near multiple key hits then fades out
    LED_MATRIX_SOLID_REACTIVE_CROSS      // Value pulses the same column and row of a single key hit then fades out
    LED_MATRIX_SOLID_REACTIVE_MULTICROSS // Value pulses the same column and row of multiple key hits then fades out
    LED_MATRIX_SOLID_REACTIVE_NEXUS      // Value pulses away on the same column and row of a single key hit then fades out
    LED_MATRIX_SOLID_REACTIVE_MULTINEXUS // Value pulses away on the same column and row of multiple key hits then fades out
    LED_MATRIX_SOLID_SPLASH,             // Value pulses away from a single key hit then fades out
    LED_MATRIX_SOLID_MULTISPLASH,        // Value pulses away from multiple key hits then fades out
#endif
    LED_MATRIX_WAVE_LEFT_RIGHT           // Sine wave scrolling from left to right
    LED_MATRIX_WAVE_UP_DOWN              // Sine wave scrolling from up to down
    LED_MATRIX_EFFECT_MAX
};
```

`config.h` で `DISABLE_[EFFECT_NAME]` を定義することで単一の効果を無効にすることができます:


| 定義                                                   | 説明                                                |
|--------------------------------------------------------|-----------------------------------------------------|
| `#define DISABLE_LED_MATRIX_ALPHAS_MODS`               | `LED_MATRIX_ALPHAS_MODS` を無効にする               |
| `#define DISABLE_LED_MATRIX_BREATHING`                 | `LED_MATRIX_BREATHING` を無効にする                 |
| `#define DISABLE_LED_MATRIX_BAND`                      | `LED_MATRIX_BAND` を無効にする                      |
| `#define DISABLE_LED_MATRIX_BAND_PINWHEEL`             | `LED_MATRIX_BAND_PINWHEEL` を無効にする             |
| `#define DISABLE_LED_MATRIX_BAND_SPIRAL`               | `LED_MATRIX_BAND_SPIRAL` を無効にする               |
| `#define DISABLE_LED_MATRIX_CYCLE_LEFT_RIGHT`          | `LED_MATRIX_CYCLE_LEFT_RIGHT` を無効にする          |
| `#define DISABLE_LED_MATRIX_CYCLE_UP_DOWN`             | `LED_MATRIX_CYCLE_UP_DOWN` を無効にする             |
| `#define DISABLE_LED_MATRIX_CYCLE_OUT_IN`              | `LED_MATRIX_CYCLE_OUT_IN` を無効にする              |
| `#define DISABLE_LED_MATRIX_DUAL_BEACON`               | `LED_MATRIX_DUAL_BEACON` を無効にする               |
| `#define DISABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE`     | `LED_MATRIX_SOLID_REACTIVE_SIMPLE` を無効にする     |
| `#define DISABLE_LED_MATRIX_SOLID_REACTIVE_WIDE`       | `LED_MATRIX_SOLID_REACTIVE_WIDE` を無効にする       |
| `#define DISABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE`  | `LED_MATRIX_SOLID_REACTIVE_MULTIWIDE` を無効にする  |
| `#define DISABLE_LED_MATRIX_SOLID_REACTIVE_CROSS`      | `LED_MATRIX_SOLID_REACTIVE_CROSS` を無効にする      |
| `#define DISABLE_LED_MATRIX_SOLID_REACTIVE_MULTICROSS` | `LED_MATRIX_SOLID_REACTIVE_MULTICROSS` を無効にする |
| `#define DISABLE_LED_MATRIX_SOLID_REACTIVE_NEXUS`      | `LED_MATRIX_SOLID_REACTIVE_NEXUS` を無効にする      |
| `#define DISABLE_LED_MATRIX_SOLID_REACTIVE_MULTINEXUS` | `LED_MATRIX_SOLID_REACTIVE_MULTINEXUS` を無効にする |
| `#define DISABLE_LED_MATRIX_SOLID_SPLASH`              | `LED_MATRIX_SOLID_SPLASH` を無効にする              |
| `#define DISABLE_LED_MATRIX_SOLID_MULTISPLASH`         | `LED_MATRIX_SOLID_MULTISPLASH` を無効にする         |
| `#define DISABLE_LED_MATRIX_WAVE_LEFT_RIGHT`           | `LED_MATRIX_WAVE_LEFT_RIGHT` を無効にする           |
| `#define DISABLE_LED_MATRIX_WAVE_UP_DOWN`              | `LED_MATRIX_WAVE_UP_DOWN` を無効にする              |

## 独自の LED マトリックス効果 :id=custom-led-matrix-effects

`rules.mk` に `LED_MATRIX_CUSTOM_USER` (あるいは `LED_MATRIX_CUSTOM_KB`) を設定することで、QMK コアファイルを編集すること無しに新しい効果をユーザスペースから直接定義することができます。

新しい効果を宣言するには、以下のような新しい `led_matrix_user/kb.inc` を作成します:

`led_matrix_user.inc` はキーマップディレクトリのルートにある必要があります。
`led_matrix_kb.inc` はキーボードディレクトリのルートにある必要があります。

独自の効果をコードで使うには、`LED_MATRIX_EFFECT()` で指定した効果名の前に `LED_MATRIX_CUSTOM_` を追加するだけです。例えば、`LED_MATRIX_EFFECT(my_cool_effect)` として宣言された効果は、以下のように参照されます:

```c
led_matrix_mode(led_MATRIX_CUSTOM_my_cool_effect);
```

```c
// !!!#pragma once を追加しないこと!!!//

// ステップ 1.
// LED_MATRIX_EFFECT マクロを使ってカスタム効果を宣言します
// (マクロの後にセミコロンが無いことに注意してください！)
LED_MATRIX_EFFECT(my_cool_effect)
LED_MATRIX_EFFECT(my_cool_effect2)

// ステップ 2.
// `LED_MATRIX_CUSTOM_EFFECT_IMPLS` の ifdef ブロックの中で効果を定義します
#ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

// 例えば: 1つのメソッド内で完結するシンプルな効果
static bool my_cool_effect(effect_params_t* params) {
  LED_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    led_matrix_set_value(i, 0xFF);
    }
  return led_max < DRIVER_LED_TOTAL;
}
    
// 例: 外部メソッドと状態に依存する、より複雑な効果
// 専用の init と run メソッド
static uint8_t some_global_state;
static void my_cool_effect2_complex_init(effect_params_t* params) {
  some_global_state = 1;
}
static bool my_cool_effect2_complex_run(effect_params_t* params) {
  LED_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    led_matrix_set_value(i, some_global_state++);
    }

  return led_max < DRIVER_LED_TOTAL;
}
static bool my_cool_effect2(effect_params_t* params) {
  if (params->init) my_cool_effect2_complex_init(params);
  return my_cool_effect2_complex_run(params);
}

#endif // LED_MATRIX_CUSTOM_EFFECT_IMPLS
```

インスピレーションと例については、`quantum/led_matrix_animations/` の下にある組み込みの効果を調べてください









## 追加の `config.h` オプション:id=additional-configh-options

```c
#define LED_MATRIX_KEYPRESSES // キー押下に反応
#define LED_MATRIX_KEYRELEASES // キーリリースに反応(キー押下の代わり)
#define LED_MATRIX_FRAMEBUFFER_EFFECTS // フレームバッファ効果を有効化
#define LED_DISABLE_TIMEOUT 0 // led が自動的にオフになるまでのミリ秒数
#define LED_DISABLE_AFTER_TIMEOUT 0 // 非推奨: 効果を無効にするまでのティック数
#define LED_DISABLE_WHEN_USB_SUSPENDED // 一時停止時に効果をオフ
#define LED_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // タスクの実行ごとにアニメーションで処理する LED の数を制限(キーボードの応答性を高める)
#define LED_MATRIX_LED_FLUSH_LIMIT 16 // アニメーションが LED を更新する頻度を制限するミリ秒。16 (16ms) は、60fps に制限することと同じ (キーボードの応答性を高める)
#define LED_MATRIX_MAXIMUM_BRIGHTNESS 255 // LED の最大光度を設定する
#define LED_MATRIX_STARTUP_MODE LED_MATRIX_SOLID // モードが設定されていない場合は、デフォルトのモードを設定する
#define LED_MATRIX_STARTUP_VAL LED_MATRIX_MAXIMUM_BRIGHTNESS // 光度が設定されていない場合は、デフォルトの光度を設定する
#define LED_MATRIX_STARTUP_SPD 127 // アニメーションの速度が設定されていない場合は、デフォルトのアニメーションの速度を設定する
#define LED_MATRIX_SPLIT { X, Y }   // (オプション) 分割キーボードの場合、それぞれの側に接続されている LED の数X = left, Y = Right.
                                    // LED_MATRIX_KEYPRESSES  や LED_MATRIX_KEYRELEASES が有効な場合、SPLIT_TRANSPORT_MIRROR も有効にする必要があります
```

## EEPROM ストレージ :id=eeprom-storage

LED マトリックスのための EEPROM は現在のところ RGB マトリックスシステムと共有されています (一般的に一度に1つの機能が使われると想定されています)が、独自の32ビットアドレスを使うように設定することができます:

```c
#define EECONFIG_LED_MATRIX (uint32_t *)28
```

ここで、`28` は `eeconfig.h` からの未使用のインデックスです。

### 直接的な操作 :id=direct-operation
| 関数                             | 説明                                                                                                                                       |
|----------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------|
| `led_matrix_set_value_all(v)`    | 全ての LED を指定された値に設定する。ここで、`v` は 0 から 255 です (EEPROM には書き込まれません)                                          |
| `led_matrix_set_value(index, v)` | 単一の LED を指定された値に設定する。ここで、`v` は 0 から 255 で、`index` は 0 から `DRIVER_LED_TOTAL` です (EEPROM には書き込まれません) |

### 効果を無効/有効にする :id=disable-enable-effects
| 関数                            | 説明                                                                           |
|---------------------------------|--------------------------------------------------------------------------------|
| `led_matrix_toggle()`           | LED の効果範囲のオンとオフを切り替える                                         |
| `led_matrix_toggle_noeeprom()`  | LED の効果範囲のオンとオフを切り替える (EEPROM には書き込まれません)           |
| `led_matrix_enable()`           | 以前の状態に基づいて、LED の効果範囲をオンにする                               |
| `led_matrix_enable_noeeprom()`  | 以前の状態に基づいて、LED の効果範囲をオンにする (EEPROM には書き込まれません) |
| `led_matrix_disable()`          | 以前の状態に基づいて、LED の効果範囲をオフにする                               |
| `led_matrix_disable_noeeprom()` | 以前の状態に基づいて、LED の効果範囲をオフにする (EEPROM には書き込まれません) |

### 効果モードの変更 :id=change-effect-mode
| 関数                                   | 説明                                                                                                           |
|----------------------------------------|----------------------------------------------------------------------------------------------------------------|
| `led_matrix_mode(mode)`                | LED アニメーションが有効な場合、モードを設定する                                                               |
| `led_matrix_mode_noeeprom(mode)`       | LED アニメーションが有効な場合、モードを設定する (EEPROM には書き込まれません)                                 |
| `led_matrix_step()`                    | モードを有効な LED アニメーションのリスト内の次の LED アニメーションに変更する                                 |
| `led_matrix_step_noeeprom()`           | モードを有効な LED アニメーションのリスト内の次の LED アニメーションに変更する (EEPROM には書き込まれません)   |
| `led_matrix_step_reverse()`            | モードを有効な LED アニメーションのリスト内の前の LED アニメーションに変更する                                 |
| `led_matrix_step_reverse_noeeprom()`   | モードを有効な LED アニメーションのリスト内の前の LED アニメーションに変更する (EEPROM には書き込まれません)   |
| `led_matrix_increase_speed()`          | アニメーションの速度を増やす                                                                                   |
| `led_matrix_increase_speed_noeeprom()` | アニメーションの速度を増やす (EEPROM には書き込まれません)                                                     |
| `led_matrix_decrease_speed()`          | アニメーションの速度を減らす                                                                                   |
| `led_matrix_decrease_speed_noeeprom()` | アニメーションの速度を増やす (EEPROM には書き込まれません)                                                     |
| `led_matrix_set_speed(speed)`          | アニメーションの速度を指定された値に設定する。ここで、`speed` は 0 から 255 です                               |
| `led_matrix_set_speed_noeeprom(speed)` | アニメーションの速度を指定された値に設定する。ここで、`speed` は 0 から 255 です (EEPROM には書き込まれません) |

### 値の変更 :id=change-value
| 関数                                 | 説明                                                                                 |
|--------------------------------------|--------------------------------------------------------------------------------------|
| `led_matrix_increase_val()`          | LED の効果範囲の明度を増やす。最大の明度で折り返します。                             |
| `led_matrix_increase_val_noeeprom()` | LED の効果範囲の明度を増やす。最大の明度で折り返します (EEPROM には書き込まれません) |
| `led_matrix_decrease_val()`          | LED の効果範囲の明度を減らす。最小の明度で折り返します。                             |
| `led_matrix_decrease_val_noeeprom()` | LED の効果範囲の明度を減らす。最小の明度で折り返します (EEPROM には書き込まれません) |

### 現在の状態の問い合わせ :id=query-current-status
| 関数                             | 説明                            |
|----------------------------------|---------------------------------|
| `led_matrix_is_enabled()`        | 現在のオン/オフの状態を取得する |
| `led_matrix_get_mode()`          | 現在のモードを取得する          |
| `led_matrix_get_val()`           | 現在の明度を取得する            |
| `led_matrix_get_speed()`         | 現在の速度を取得する            |
| `led_matrix_get_suspend_state()` | 現在の一時停止状態を取得する    |

## コールバック :id=callbacks

### インジケータ :id=indicators

Caps Lock のための LED、レイヤーの表示などの独自のインジケータを設定したい場合は、`led_matrix_indicators_kb` または `led_matrix_indicators_user` を使うことができます:
```c
void led_matrix_indicators_kb(void) {
    led_matrix_set_color(index, value);
}
```

さらに高度なインジケータの関数があります。これらは、1サイクルごとに全ての LED をレンダリングすることが負担となる、高度にカスタマイズされたディスプレイを使用するユーザを対象としています。この関数には、これを使いやすくするための特別なマクロが含まれています: `LED_MATRIX_INDICATOR_SET_VALUE(i, v)`。

```c
void led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    LED_MATRIX_INDICATOR_SET_VALUE(index, value);
}
```
