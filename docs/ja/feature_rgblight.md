# RGB照明

<!---
  original document: 0.9.52:docs/feature_oled_driver.md
  git diff 0.9.52 HEAD -- docs/feature_oled_driver.md | cat
-->

QMK にはキーボードに設置した RGB LED を制御する機能があります。LED をキーボードの底面に設置することが多いため、一般に*アンダーグロー*と呼ばれており、透明なケースと組み合わせると、綺麗な拡散効果が得られます。

![Planck with RGB Underglow](https://raw.githubusercontent.com/qmk/qmk_firmware/3774a7fcdab5544fc787f4c200be05fcd417e31f/keyboards/planck/keymaps/yang/planck-with-rgb-underglow.jpg)

キーボードによっては RGB LED があらかじめ取り付けられているものもありますが、それら以外は後付けしなくてはいけません。キーボードに RGB 照明を追加する方法については[ハードウェアの改造](#hardware-modification)の項目を参照してください。

現在、QMK は以下のアドレサブルLEDをサポートしています(RGBW 方式による白色 LED はサポートしていません):

 * WS2811、WS2812、WS2812B、WS2812C など。
 * SK6812、SK6812MINI、SK6805

色ごとに配線するのではなく、単線で送信される特別なプロトコルを解析する小さなマイクロチップが含まれた LED は「アドレサブル」と呼ばれています。チップは残りのデータを次のLEDに渡すことで連携を可能にしています。これにより、個々の LED の色を簡単に制御できるようになっています。

## 使い方

RGB LED が搭載されたキーボードにおいては、通常は標準で有効になっています。動作しないようであれば、`rules.mk` 内の次の項目を調べてください。

```make
RGBLIGHT_ENABLE = yes
```

少なくとも、LED ストリップが接続されているデータピンと LED の個数を `config.h` で定義する必要があります。LED が搭載済みのキーボードなら、キーマップを用意するだけで、値を変更する必要はないでしょう。

|定義         |内容                                                                                              |
|---------------|---------------------------------------------------------------------------------------------------------|
|`RGB_DI_PIN`   |LED に接続するデータピン                                                            |
|`RGBLED_NUM`   |接続する LED の数                                                                             |
|`RGBLED_SPLIT` |(オプション)分割キーボードにおける、個別の `RGB_DI_PIN` に直接つながっている LED の数。|

後述のキーコードを使用することで、任意の RGB 照明に変更することができます。

### 色の選択

QMK は RGB ではなく、[HSV色空間](https://ja.wikipedia.org/wiki/HSV%E8%89%B2%E7%A9%BA%E9%96%93)で色を選択します。このカラー環はこれがどのように動作するかを示します。

<img src="gitbook/images/color-wheel.svg" alt="HSV Color Wheel" width="250"/>

**Hue** を変更すると円を回ります<br>
**Saturation** を変更すると、円の中央ないしは外へと向かい、色の強度に影響します<br>
**Value** を変更すると明るさが変わります<br>

## キーコード

|キー                |代替名   |内容                                                         |
|-------------------|----------|--------------------------------------------------------------------|
|`RGB_TOG`          |          |照明のオン・オフ切り替え                                       |
|`RGB_MODE_FORWARD` |`RGB_MOD` |モードを循環します。シフトキーが押されているときは逆方向に循環します。           |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|モードを逆方向に循環します。シフトキーが押されているときは正方向に循環します。|
|`RGB_HUI`          |          |hue値を増やします。シフトキーが押されていると、値は減ります。                       |
|`RGB_HUD`          |          |hue値を減らします。シフトキーが押されていると、値は増えます。                       |
|`RGB_SAI`          |          |saturation値を増やします。シフトキーが押されていると、値は減ります。         |
|`RGB_SAD`          |          |saturation値を減らします。シフトキーが押されていると、値は増えます。         |
|`RGB_VAI`          |          |value値を増やします(明るくなる)。シフトキーが押されているときは値は減ります。 |
|`RGB_VAD`          |          |value値を減らします(暗くなる)。シフトキーが押されていると、値は増えます。      |
|`RGB_MODE_PLAIN`   |`RGB_M_P `|静的 (アニメーションなし)                                           |
|`RGB_MODE_BREATHE` |`RGB_M_B` |ブレスアニメーション                                            |
|`RGB_MODE_RAINBOW` |`RGB_M_R` |レインボーアニメーション                                              |
|`RGB_MODE_SWIRL`   |`RGB_M_SW`|渦巻きアニメーション                                                |
|`RGB_MODE_SNAKE`   |`RGB_M_SN`|スネークアニメーション                                                |
|`RGB_MODE_KNIGHT`  |`RGB_M_K` |「ナイトライダー」アニメーション                                       |
|`RGB_MODE_XMAS`    |`RGB_M_X` |クリスマスアニメーション                                            |
|`RGB_MODE_GRADIENT`|`RGB_M_G` |静的グラデーションアニメーション                                       |
|`RGB_MODE_RGBTEST` |`RGB_M_T` |RGB テストアニメーション                                |

!> 標準では、RGB 照明と[RGBマトリクス](feature_rgb_matrix.md)を同時に使用していると、キーコードは両方に機能します。特定の機能に対して `*_DISABLE_KEYCODES` オプションを定義することで、キーコードを無効化できます。


## 設定

RGB 照明を設定するには、`config.h` 内で `#define` として宣言します。

|定義               |規定値      |内容                                                                  |
|---------------------|-------------|-----------------------------------------------------------------------------|
|`RGBLIGHT_HUE_STEP`  |`10`         |色相を循環させるステップ数                              |
|`RGBLIGHT_SAT_STEP`  |`17`         |彩度の増加ステップ数                           |
|`RGBLIGHT_VAL_STEP`  |`17`         |明度の増加ステップ数                           |
|`RGBLIGHT_LIMIT_VAL` |`255`        |最大明度                                                 |
|`RGBLIGHT_SLEEP`     |*未定義*|定義すると、スリープモードに入ると照明が切れます。|
|`RGBLIGHT_SPLIT`     |*未定義*|定義すると、分割キーボードの同期機能が追加されます。|
|`RGBLIGHT_DISABLE_KEYCODES`|*未定義*|定義すると、キーコードからの制御ができなくなります。この場合はプログラム命令で制御することになります。| 

## アニメーション効果

色を変更できるだけではなく、`RGBLIGHT_EFFECT_xxxx` や `RGBLIGHT_ANIMATIONS` を定義することによって、いくつかのアニメーションを適用できます。

|モード番号           |追加値  |内容                            |
|-----------------------------|-------------------|---------------------------------------|
|`RGBLIGHT_MODE_STATIC_LIGHT` | *なし*            |単色(このモードは常に有効) |
|`RGBLIGHT_MODE_BREATHING`    | 0,1,2,3           |単色ブレス                  |
|`RGBLIGHT_MODE_RAINBOW_MOOD` | 0,1,2             |循環レインボー                        |
|`RGBLIGHT_MODE_RAINBOW_SWIRL`| 0,1,2,3,4,5       |渦巻きレインボー                       |
|`RGBLIGHT_MODE_SNAKE`        | 0,1,2,3,4,5       |スネーク                                  |
|`RGBLIGHT_MODE_KNIGHT`       | 0,1,2             |ナイトライダー                                 |
|`RGBLIGHT_MODE_CHRISTMAS`    | *なし*            |クリスマス                              |
|`RGBLIGHT_MODE_STATIC_GRADIENT`| 0,1,..,9        |静的グラデーション                        |
|`RGBLIGHT_MODE_RGB_TEST`     | *なし*            |RGB テスト                               |
|`RGBLIGHT_MODE_ALTERNATING`  | *なし*            |交互                            |
|`RGBLIGHT_MODE_TWINKLE`      | 0,1,2,3,4,5       |きらきら                                |

[こちらの映像](https://youtube.com/watch?v=VKrpPAHlisY)でデモンストレーションを公開しています。

注記: 0.6.117 以前のバージョンにおいては、モード番号は直接記述します。`quantum/rgblight.h` に、モード番号と名称の対比表が含まれています。

### アニメーション効果の切り替え

これらの定義を使用して、ファームウェアからアニメーションを追加したり削除したりします。書き込み領域が不足しているのであれば、使用しないアニメーションを無効にすると良いでしょう。

|定義                              |規定値      |内容                                                              |
|------------------------------------|-------------|-------------------------------------------------------------------------|
|`RGBLIGHT_ANIMATIONS`               |*未定義*|すべてのアニメーションを有効                                   |
|`RGBLIGHT_EFFECT_ALTERNATING`       |*未定義*|交互アニメを有効                                       |
|`RGBLIGHT_EFFECT_BREATHING`         |*未定義*|ブレスアニメを有効                                         |
|`RGBLIGHT_EFFECT_CHRISTMAS`         |*未定義*|クリスマスアニメを有効                                         |
|`RGBLIGHT_EFFECT_KNIGHT`            |*未定義*|ナイトライダーアニメを有効                                            |
|`RGBLIGHT_EFFECT_RAINBOW_MOOD`      |*未定義*|レインボーアニメを有効                                      |
|`RGBLIGHT_EFFECT_RAINBOW_SWIRL`     |*未定義*|レインボー渦巻きアニメを有効                                     |
|`RGBLIGHT_EFFECT_RGB_TEST`          |*未定義*|RGBテストアニメを有効                                          |
|`RGBLIGHT_EFFECT_SNAKE`             |*未定義*|スネークアニメを有効                                             |
|`RGBLIGHT_EFFECT_STATIC_GRADIENT`   |*未定義*|静的グラデーションアニメを有効                                             |
|`RGBLIGHT_EFFECT_TWINKLE`           |*未定義*|きらきらアニメを有効                                           |

### アニメーション効果の設定

以下のオプションでは様々なアニメーションを調整できます:

|定義                              |規定値      |内容                                                                          |
|------------------------------------|-------------|-------------------------------------------------------------------------------------|
|`RGBLIGHT_EFFECT_BREATHE_CENTER`    |*未定義*|ブレスアニメのカーブ計算に使用します。有効値は 1.0～2.7 |
|`RGBLIGHT_EFFECT_BREATHE_MAX`       |`255`        |ブレスにおける明度の最大値。有効値は 1～255             |
|`RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL`|`1000`       |クリスマスにおいて点灯する間隔(ミリ秒)。|
|`RGBLIGHT_EFFECT_CHRISTMAS_STEP`    |`2`          |クリスマスにおいて、赤や緑に点灯する LED の数    |
|`RGBLIGHT_EFFECT_KNIGHT_LED_NUM`    |`RGBLED_NUM` |ナイトライダーにおいて、使用する LED の数                             |
|`RGBLIGHT_EFFECT_KNIGHT_LENGTH`     |`3`          |ナイトライダーにおいて、点灯させる LED の数                            |
|`RGBLIGHT_EFFECT_KNIGHT_OFFSET`     |`0`          |ナイトライダーにおいて、点灯を開始させる LED の位置    |
|`RGBLIGHT_RAINBOW_SWIRL_RANGE`      |`255`        |レインボー渦巻きにおいて、異なる渦巻きに対する範囲の調整                |
|`RGBLIGHT_EFFECT_SNAKE_LENGTH`      |`4`          |スネークにおいて、点灯させる LED の数                             |
|`RGBLIGHT_EFFECT_TWINKLE_LIFE`      |`75`         |きらきらにおける、点滅の早さ(アニメーションのステップ数)  |
|`RGBLIGHT_EFFECT_TWINKLE_PROBABILITY`|`1/127`     |きらきらにおける、個々の点滅の調整(個々のアニメーションのステップ数)                   |

### データ領域削減のための例
  1. `config.h` から `RGBLIGHT_ANIMATIONS` を削除します。
  1. 有効にしたいアニメーションのみ選択します。以下の事例では、2つのアニメーションのみを有効にして約4KiB節約しています。

```diff
 #undef RGBLED_NUM
-#define RGBLIGHT_ANIMATIONS
+#define RGBLIGHT_EFFECT_STATIC_GRADIENT
+#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
 #define RGBLED_NUM 12
 #define RGBLIGHT_HUE_STEP 8
 #define RGBLIGHT_SAT_STEP 8
```

### アニメーション速度

それぞれのモードにおいてアニメーションの速度を変更することができます。

これは[Youtubeのクイックデモ(NPKC KC60を使用)](https://www.youtube.com/watch?v=VKrpPAHlisY)です。

```c
// 単色ブレスのアニメーション間隔(ミリ秒)
const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {30, 20, 10, 5};

// レインボー循環のアニメーション間隔(ミリ秒)
const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {120, 60, 30};

// レインボー渦巻きのアニメーション間隔(ミリ秒)
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {100, 50, 20};

// スネークのアニメーション間隔(ミリ秒)
const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {100, 50, 20};

// ナイトライダーのアニメーション間隔(ミリ秒)
const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {127, 63, 31};

// きらきらのアニメーション間隔(ミリ秒)
const uint8_t RGBLED_TWINKLE_INTERVALS[] PROGMEM = {50, 25, 10};

// 静的グラデーションの色相の制御
const uint8_t RGBLED_GRADIENT_RANGES[] PROGMEM = {255, 170, 127, 85, 64};
```

## 照明レイヤー

`config.h` に `#define RGBLIGHT_LAYERS` を含めることで、照明レイヤーを有効にできます。これらはアニメーションを中断することなく、アクティブなレイヤーや Caps Lock 状態の表示などのために、アンダーグロー LED を簡単に使用できるようになります。具体的に何ができるかは、[この映像例](https://youtu.be/uLGE1epbmdY)をご覧ください。

### 照明レイヤーの定義 :id=defining-lighting-layers

初期状態では8つのレイヤーが使用できます。これは `config.h` の `RGBLIGHT_MAX_LAYERS` の値を変えることで、32層(例：`#define RGBLIGHT_MAX_LAYERS 32`)まで拡張できます。分割キーボードの場合、変更後は両方のボードを更新する必要があることに気をつけましょう。また、最大値を増やすと、ファームウェアサイズが増え、分割キーボードの同期が遅くなります。

レイヤーを定義するには、`keymap.c` において `RGBLIGHT_LAYER_SEGMENTS` マクロを使い、`rgblight_segment_t` 配列によって LED の範囲と上書きしたい色を列挙させます。複数のレイヤーを定義することで、それらを個別に有効・無効にできます。

```c
// Caps Lockが有効の時、6～9、12～15の LED を赤く点灯させます。見落とすことはまずないでしょう！
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 4, HSV_RED},       // 6から始まる、4つのLED
    {12, 4, HSV_RED}       // 12から始まる、4つのLED
);
// Layer1がアクティブの時、9と10のLEDをシアン色で点灯
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 2, HSV_CYAN}
);
// Layer2がアクティブの時、11と12のLEDを紫色で点灯

const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 2, HSV_PURPLE}
);
// 必要に応じて追加...
```

これらのレイヤーは `RGBLIGHT_LAYERS_LIST` マクロによってひとつにまとめ、キーボードの初期化時に `rgblight_layers` 変数に代入します。上限を超えるレイヤーは無視されます。異なる照明レイヤーが重なっている場合は、配列順で後のレイヤーが優先されます。

```c
// レイヤーの配列を定義。後のレイヤーが優先されます。
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_layer1_layer,    // Overrides caps lock layer
    my_layer2_layer     // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}
```

注記: 2つのマイコンを搭載した分割キーボードでは、rgblight_layers の内容を変更する際には、両方とも更新する必要があります。

### 照明レイヤーの切り替え :id=enabling-lighting-layers

各照明レイヤーの定義を設定したので、キーボードの状態でレイヤーを切り替えてみましょう。

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    // キーボードレイヤーが2つとも有効なら、レイヤーが2つとも光ります
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}
```

### 照明レイヤーの点滅 :id=lighting-layer-blink

`config.h` に `#define RGBLIGHT_LAYER_BLINK` を含めることで、指定した間隔(ミリ秒)で点滅させることができます。これは設定などに変更があったときの確認を、利用者に提起することなどに使えます。

```c
const rgblight_segment_t PROGMEM _yes_layer[] = RGBLIGHT_LAYER_SEGMENTS( {9, 6, HSV_GREEN} );
const rgblight_segment_t PROGMEM _no_layer[] = RGBLIGHT_LAYER_SEGMENTS( {9, 6, HSV_RED} );

const rgblight_segment_t* const PROGMEM _rgb_layers[] =
    RGBLIGHT_LAYERS_LIST( _yes_layer, _no_layer );

void keyboard_post_init_user(void) {
    rgblight_layers = _rgb_layers;
}

// 状態が切り替わった後の値を取得するため、
// post_process_record_user で呼び出していることに注意してください。
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DEBUG:
            rgblight_blink_layer(debug_enable ? 0 : 1, 500);
            break;

        case NK_TOGG:
        case NK_ON:
        case NK_OFF:
            rgblight_blink_layer(keymap_config.nkro ? 0 : 1, 500);
            break;
    }
}
```

### RGB照明の状態を上書きする

`RGB_TOG` を使うなどして、RGB照明を無効にしているとき、通常は照明レイヤーは見えない状態になっています。RGB 照明を無効にしているときでも、レイヤーを動作させたいのであれば、`config.h` に `#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF`を追加します。

## 関数

レイヤーを切り替えるたびに色を変えるといった、RGB 照明を変更するプログラムを書きたいのであれば、QMK にはそれを手助けする関数を提供しています。完全なリストは [`rgblight.h`](https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight.h) を見ることになりますが、ここでは頻繁に使われると思われる関数を紹介します。

### 便利な関数
|関数                                    |内容                                                        |
|--------------------------------------------|-------------------------------------------------------------------|
|`sethsv(hue, sat, val, ledbuf)`             |ledbuf に HSV値を設置します                                  |
|`sethsv_raw(hue, sat, val, ledbuf)`         |RGBLIGHT_LIMIT_VAL を無視して、ledbuf に HSV値を設置します |
|`setrgb(r, g, b, ledbuf)`                   |ledbuf に RGB値を設置します                |

### 低レベル関数
|関数                                    |内容                                |
|--------------------------------------------|-------------------------------------------|
|`rgblight_set()`                            |バッファから LED へフラッシュします              |
|`rgblight_set_clipping_range(pos, num)`     |クリップ範囲の指定。[クリップ範囲](#clipping-range)を参照してください。 |

例:
```c
sethsv(HSV_WHITE, (LED_TYPE *)&led[0]); // led 0
sethsv(HSV_RED,   (LED_TYPE *)&led[1]); // led 1
sethsv(HSV_GREEN, (LED_TYPE *)&led[2]); // led 2
// 上記の関数はrgblight_set()を自動で呼ばないので、
// 明示的に呼び出す必要があります。
rgblight_set();
```

### アニメーション効果関数
#### 効果範囲の設定
|関数                                    |内容         |
|----------------------------------------|-------------|
|`rgblight_set_effect_range(pos, num)`   |効果範囲の設定|

#### 直接制御
- RGB、HSV ともに、指定する値の範囲は 0～255 です。
- 指定する LED のインデックス範囲は 0～`RGBLED_NUM` までです。
- 設定値は EEPROM には書き込まれません。

|関数                                    |内容  |
|--------------------------------------------|-------------|
|`rgblight_setrgb_at(r, g, b, index)`          |ひとつの LED に RGB値を設定します。|
|`rgblight_sethsv_at(h, s, v, index)`          |ひとつの LED に HSV値を設定します。|
|`rgblight_setrgb_range(r, g, b, start, end)`|指定した範囲（start 以上、end 未満）の LED にRGB値を設定します。|
|`rgblight_sethsv_range(h, s, v, start, end)`|指定した範囲（start 以上、end 未満）の LED にHSV値を設定します。|
|`rgblight_setrgb(r, g, b)`                  |効果が適用される LED に RGB値を設定します。|
|`rgblight_setrgb_master(r, g, b)`           |メインボードの LED に対して、RGB値をで設定します。|
|`rgblight_setrgb_slave(r, g, b)`            |サブボードの LED に対して、RGB値をで設定します。|
|`rgblight_sethsv_master(h, s, v)`           |メインボードの LED に対して、HSV値を設定します。|
|`rgblight_sethsv_slave(h, s, v)`            |サブボードの LED に対して、HSV値を設定します。|


例:
```c
rgblight_sethsv(HSV_WHITE, 0); // led 0
rgblight_sethsv(HSV_RED,   1); // led 1
rgblight_sethsv(HSV_GREEN, 2); // led 2
// これらの関数は自動でrgblight_set()を呼び出すため、明示的に更新する必要はありません。
// 頻繁に呼び出すと負荷がかかるので注意してください。
.. 
```

#### 効果の変更
|関数                                    |内容  |
|--------------------------------------------|-------------|
|`rgblight_mode(x)`                          |RGBアニメーションが有効であれば、モードを指定します。 |
|`rgblight_mode_noeeprom(x)`                 |RGBアニメーションが有効であれば、モードを指定します(EEPROM には書き込まれません)。 |
|`rgblight_step()`                           |RGBアニメーションが有効であれば、リスト内の次のモードに切り替える |
|`rgblight_step_noeeprom()`                  |RGBアニメーションが有効であれば、リスト内の次のモードに切り替える(EEPROM には書き込まれません)。 |
|`rgblight_step_reverse()`                   |RGBアニメーションが有効であれば、リスト内の前のモードに切り替える|
|`rgblight_step_reverse_noeeprom()`          |RGBアニメーションが有効であれば、リスト内の前のモードに切り替える(EEPROM には書き込まれません)。 |

#### モードの切り替え
|関数                                    |内容  |
|--------------------------------------------|-------------|
|`rgblight_toggle()`                         |適用範囲の LED の有効・無効を切り替えます。 |
|`rgblight_toggle_noeeprom()`                |適用範囲の LED の有効・無効を切り替えます (EEPROM には書き込まれません)。 |
|`rgblight_enable()`                         |適用範囲の LED を直前の状態に沿って有効にします。 |
|`rgblight_enable_noeeprom()`                |適用範囲の LED を直前の状態に沿って有効にします(EEPROM には書き込まれません)。 |
|`rgblight_disable()`                        |適用範囲の LED を無効にします。|
|`rgblight_disable_noeeprom()`               |適用範囲の LED を無効にします (EEPROM には書き込まれません)。 |

#### HSV色相値の変更
|関数                                    |内容  |
|--------------------------------------------|-------------|
|`rgblight_increase_hue()`                   |適用範囲の LED の hue値を増加させます。255を超えると0に戻ります。 |
|`rgblight_increase_hue_noeeprom()`          |適用範囲の LED の hue値を増加させます。 (EEPROM には書き込まれません)。 |
|`rgblight_decrease_hue()`                   |適用範囲の LED の hue値を減少させます。0を下回ると255になります。 |
|`rgblight_decrease_hue_noeeprom()`          |適用範囲の LED の hue値を減少させます。 (EEPROM には書き込まれません)。 |
|`rgblight_increase_sat()`                   |適用範囲の LED の saturation値を増加させます。255を超えた場合、255に丸められます。 |
|`rgblight_increase_sat_noeeprom()`          |適用範囲の LED の saturation値を増加させます。 (EEPROM には書き込まれません)。 |
|`rgblight_decrease_sat()`                   |適用範囲の LED の saturation値を減少させます。0を下回ると0に丸められます。 |
|`rgblight_decrease_sat_noeeprom()`          |適用範囲の LED の saturation値を減少させます。 (EEPROM には書き込まれません)。 |
|`rgblight_increase_val()`                   |適用範囲の LED の value値を増加させます。255を超えた場合、255に丸められます。 |
|`rgblight_increase_val_noeeprom()`          |適用範囲の LED の value値を増加させます。 (EEPROM には書き込まれません)。 |
|`rgblight_decrease_val()`                   |適用範囲の LED の value値を減少させます。0を下回ると0に丸められます。 |
|`rgblight_decrease_val_noeeprom()`          |適用範囲の LED の value値を減少させます。 (EEPROM には書き込まれません)。 |
|`rgblight_sethsv(h, s, v)`                  |適用範囲の LED の HSV値を0～255の範囲で設置します。 |
|`rgblight_sethsv_noeeprom(h, s, v)`         |適用範囲の LED の HSV値を0～255の範囲で設置します (EEPROM には書き込まれません)。 |

#### レイヤー関数
|関数                                        |内容  |
|--------------------------------------------|-------------|
|`rgblight_get_layer_state(i)`               |照明レイヤー `i` が有効なら `true` が返されます。 |
|`rgblight_set_layer_state(i, is_on)`        |照明レイヤー `i` の状態を変更する。`is_on` が true なら有効になります。 |

#### クエリ
|関数                   |内容                 |
|-----------------------|---------------------|
|`rgblight_is_enabled()`|現在の有効・無効の状態 |
|`rgblight_get_mode()`  |現在のモード          |
|`rgblight_get_hue()`   |現在の hue値           |
|`rgblight_get_sat()`   |現在の sat値           |
|`rgblight_get_val()`   |現在の val値           |
|`rgblight_get_speed()` |現在の速度            |

## 色

これらは一般的な色の略記です。`RGB` は `setrgb` 関数への値として、`HSV` は `sethsv` 関数への値として使えます。

|RGB                |HSV                |
|-------------------|-------------------|
|`RGB_WHITE`        |`HSV_WHITE`        |
|`RGB_RED`          |`HSV_RED`          |
|`RGB_CORAL`        |`HSV_CORAL`        |
|`RGB_ORANGE`       |`HSV_ORANGE`       |
|`RGB_GOLDENROD`    |`HSV_GOLDENROD`    |
|`RGB_GOLD`         |`HSV_GOLD`         |
|`RGB_YELLOW`       |`HSV_YELLOW`       |
|`RGB_CHARTREUSE`   |`HSV_CHARTREUSE`   |
|`RGB_GREEN`        |`HSV_GREEN`        |
|`RGB_SPRINGGREEN`  |`HSV_SPRINGGREEN`  |
|`RGB_TURQUOISE`    |`HSV_TURQUOISE`    |
|`RGB_TEAL`         |`HSV_TEAL`         |
|`RGB_CYAN`         |`HSV_CYAN`         |
|`RGB_AZURE`        |`HSV_AZURE`        |
|`RGB_BLUE`         |`HSV_BLUE`         |
|`RGB_PURPLE`       |`HSV_PURPLE`       |
|`RGB_MAGENTA`      |`HSV_MAGENTA`      |
|`RGB_PINK`         |`HSV_PINK`         |

```c
rgblight_setrgb(RGB_ORANGE);
rgblight_sethsv_noeeprom(HSV_GREEN);
rgblight_setrgb_at(RGB_GOLD, 3);
rgblight_sethsv_range(HSV_WHITE, 0, 6);
```

これらは [`rgblight_list.h`](https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight_list.h) で定義されています。気軽に追加してください！


## LEDの順序を変更

LEDの論理的な順序を電子回路上の接続順とは異なるようにしたければ、`config.h` で `RGBLIGHT_LED_MAP` マクロを定義します。

通常は LED バッファの内容は、その順番に沿って LED に出力されます。
<img src="https://user-images.githubusercontent.com/2170248/55743718-01866c80-5a6e-11e9-8134-25419928327a.JPG" alt="simple dicrect" width="50%"/>

例えば、下記のように `RGBLIGHT_LED_MAP` を定義すると、電子回路の接続とは逆の順番で LED を制御することができます。

```c
// config.h

#define RGBLED_NUM 4
#define RGBLIGHT_LED_MAP { 3, 2, 1, 0 }

```
<img src="https://user-images.githubusercontent.com/2170248/55743725-08ad7a80-5a6e-11e9-83ed-126a2b0209fc.JPG" alt="simple mapped" width="50%"/>

キーごとに対応するバックライトとして LED を用いているキーボードであれば、以下のように定義することもできます。

```c
// config.h

#define RGBLED_NUM 30

/* 物理的配列から電気的配列への RGB LED 変換マクロ */
#define LED_LAYOUT( \
    L00, L01, L02, L03, L04, L05,  \
    L10, L11, L12, L13, L14, L15,  \
    L20, L21, L22, L23, L24, L25,  \
    L30, L31, L32, L33, L34, L35,  \
    L40, L41, L42, L43, L44, L45 ) \
  { \
    L05, L04, L03, L02, L01, L00,   \
    L10, L11, L12, L13, L14, L15,   \
    L25, L24, L23, L22, L21, L20,   \
    L30, L31, L32, L33, L34, L35,   \
    L46, L45, L44, L43, L42, L41    \
  }

/* RGB LED 論理配列変換マップ */
/* 上から下、右から左 */
#define RGBLIGHT_LED_MAP LED_LAYOUT( \
  25, 20, 15, 10,  5,  0,       \
  26, 21, 16, 11,  6,  1,       \
  27, 22, 17, 12,  7,  2,       \
  28, 23, 18, 13,  8,  3,       \
  29, 24, 19, 14,  9,  4 )

```
## 範囲のクリッピング

`rgblight_set_clipping_range()` 関数を使うと、実際の LWS 数よりも多くのバッファを確保して、そのバッファの一部を LED に出力することができます。これは分割キーボードにおいて、左右の LED を論理的に連続したものとして扱いたい場合に便利です。

クリッピングは以下のコードのように実行します。

```c
// 処理ルーチン内
  rgblight_set_clipping_range(3, 4);
```
<img src="https://user-images.githubusercontent.com/2170248/55743785-2bd82a00-5a6e-11e9-9d4b-1b4ffaf4932b.JPG" alt="clip direct" width="70%"/>

`RGBLIGHT_LED_MAP` も同時に使用できます。

```c
// config.h
#define RGBLED_NUM 8
#define RGBLIGHT_LED_MAP { 7, 6, 5, 4, 3, 2, 1, 0 }

// 処理ルーチン内
  rgblight_set_clipping_range(3, 4);
```
<img src="https://user-images.githubusercontent.com/2170248/55743747-119e4c00-5a6e-11e9-91e5-013203ffae8a.JPG" alt="clip mapped" width="70%"/>

## ハードウェアの改造

キーボードに LED が搭載されていないのであれば、自分でLEDをはんだ付けできるかもしれません。接続には配線のための未使用のピンを探す必要があります。キーボードによっては、はんだ付けを容易にするために、マイコンから未使用のピンを取り出すことができるでしょう。また、VCC と GND も適切な電源ピンに接続する必要もあります。
