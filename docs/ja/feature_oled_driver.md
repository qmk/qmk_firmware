# OLEDドライバー

<!---
  original document: 0.9.52:docs/feature_oled_driver.md
  git diff 0.9.52 HEAD -- docs/feature_oled_driver.md | cat
-->

## サポートされるハードウェア

OLED モジュールは SSD1306 もしくは SH1106 が搭載された IC を、I2C を通じて使用します。

テスト済みの組み合わせ:

|IC       |サイズ|プラットフォーム|注記                   |
|---------|------|----------------|------------------------|
|SSD1306  |128x32|AVR     |主要サポート         |
|SSD1306  |128x64|AVR     |動作確認済み         |
|SSD1306  |128x32|Arm     |                    |
|SH1106   |128x64|AVR     |回転・スクロールは不可|

検証はされていませんが、ARM ベースのマイコンや、サイズの違う OLED モジュールでも互換性はあるでしょう。

!> 注意: このドライバーは、今のところ分割キーボードを元にした i2c_master ドライバーを使用しています。もし分割キーボード間の通信に I2C を利用している場合、アドレスの衝突が起こる可能性があります(シリアル通信では影響しない)。キーボードの開発者にコードのアップデートや修正を問い合わせてみてください。また、液晶の焼き付きを防ぐためのタイムアウトは、分割キーボード向けのキー押下検出プログラムに基づいているので、非分割キーボードでは、独自にタイムアウトのプログラムを実装する必要があります。

## 使い方

OLED を有効にするには、二段階のステップがあります。最初のステップは、コンパイルしたいキーボードの `rules.mk` への次の一文の追加です。

```make
OLED_DRIVER_ENABLE = yes
```

そして `keymap.c` ファイルに OLED タスク呼び出しを実装します。この例におけるキーマップでは `_QWERTY`、 `_FN`、 `_ADJ` の3つのレイヤーが存在するものとします。 

```c
#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
    // キーボードレイヤーの状態
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("FN\n"), false);
            break;
        case _ADJ:
            oled_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            // 文字列の最後に「\n」を追加する代わりに「write_ln」を使う例
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // キーボードの LED 状態
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}
#endif
```

## ロゴ

標準フォントでは、QMK ロゴのために一定の領域が予約済みです。液晶にロゴを描画するには、この例のように記述します:

```c
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}
```

## その他の例

分割キーボードでは2つの OLED に異なる情報を描画したり、回転や反転させることがよくあります。描画したい情報の切り替えは、 `split_util.h` に含まれる、`is_keyboard_master()` や `is_keyboard_left()` の戻り値によって実装できます:

```c
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // サブであれば180°反転
    }

    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();  // 現在のキーボードの状態を描画 (レイヤー、キーロックなど)
    } else {
        render_logo();  // ロゴの描画
        oled_scroll_left();  // スクロールを有効にします
    }
}
#endif
```

## 基本設定

|名称                       |初期値            |内容                                                                                                                      |
|---------------------------|-----------------|--------------------------------------------------------------------------------------------------------------------------|
|`OLED_DISPLAY_ADDRESS`     |`0x3C`           |ディスプレイのI2Cアドレス                                                                                                   |
|`OLED_FONT_H`              |`"glcdfont.c"`   |カスタムフォントのファイル                                                                                |
|`OLED_FONT_START`          |`0`              |カスタムフォントのキャラクターインデックスの最小値                                                                              |
|`OLED_FONT_END`            |`223`            |カスタムフォントのキャラクターインデックスの最大値                                                                                |
|`OLED_FONT_WIDTH`          |`6`              |フォントの幅                                                                                                            |
|`OLED_FONT_HEIGHT`         |`8`              |フォントの高さ(未検証)                                                                                                |
|`OLED_TIMEOUT`             |`60000`          |焼き付き抑止のため、キーボードを操作していないときに60秒後にディスプレイを切る。0なら電源は切られません           |
|`OLED_SCROLL_TIMEOUT`      |`0`              |焼き付き抑止のため、キーボードを操作していないときにスクロールさせるまでの間隔。0ならスクロールはしません                     |
|`OLED_SCROLL_TIMEOUT_RIGHT`|*Not defined*    |定義された場合、右にスクロールします。未定義なら左方向                                                      |
|`OLED_IC`                  |`OLED_IC_SSD1306`|SH1106コントローラーを使う場合、 `OLED_IC_SH1106` に設定                                                       |
|`OLED_COLUMN_OFFSET`       |`0`              |(SH1106のみ) 指定地だけピクセルを右にシフト。132x64サイズの液晶において128x64の画像を中寄せするときに便利です|

 ## 128x64と独自サイズのOLEDディスプレイ

標準の画面サイズは128x32で、全ての必要な定義はその点を考慮して事前に計算されています。また、ドライバに必要な値を供給できるようにするための `OLED_DISPLAY_CUSTOM` という定義だけではなく、全ての値を 128x64 サイズで使われる値に切り替えるための `OLED_DISPLAY_128X64` という定義も追加しています。

|定義               |標準値        |内容                                                                                                                             |
|---------------------|---------------|----------------------------------------------------------------------------------------------------------------------------------------|
|`OLED_DISPLAY_128X64`|*Not defined*  |128x64ディスプレイを使うための定義に変更                                                                               |
|`OLED_DISPLAY_CUSTOM`|*Not defined*  |独自の値を定義。実装には以下の定義が必要です                              |
|`OLED_DISPLAY_WIDTH` |`128`          |OLEDの横幅 display.                                                                                                          |
|`OLED_DISPLAY_HEIGHT`|`32`           |OLEDの縦幅 display.                                                                                                         |
|`OLED_MATRIX_SIZE`   |`512`          |確保するローカルバッファのサイズ<br>`(OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)`.                                                 |
|`OLED_BLOCK_TYPE`    |`uint16_t`     |描画に用いる符号なし整数型                                                                                   |
|`OLED_BLOCK_COUNT`   |`16`           |描画する分割されたブロックの数<br>`(sizeof(OLED_BLOCK_TYPE) * 8)`.                               |
|`OLED_BLOCK_SIZE`    |`32`           |描画のための各ブロックのサイズ<br>`(OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)`.                                                  |
|`OLED_COM_PINS`      |`COM_PINS_SEQ` |描画メモリーのためのSSD1306チップマップ<br>値は `COM_PINS_SEQ`, `COM_PINS_ALT`, `COM_PINS_SEQ_LR`, & `COM_PINS_ALT_LR`.|
|`OLED_SOURCE_MAP`    |`{ 0, ... N }` |90度回転における変換元マップ                               |
|`OLED_TARGET_MAP`    |`{ 24, ... N }`|90度回転における変換先マップ                               |


### 90°回転 - 技術云々

!> SH1106では回転はサポートされていません

```c
// OLED回転列挙フラグ
typedef enum {
    OLED_ROTATION_0   = 0,
    OLED_ROTATION_90  = 1,
    OLED_ROTATION_180 = 2,
    OLED_ROTATION_270 = 3, // OLED_ROTATION_90 | OLED_ROTATION_180
} oled_rotation_t;
```

SSD1306 ドライバーによって駆動される OLED ディスプレイは、ハードウェアとしては 0° と 180° の描画のみサポートしています。この処理はソフトウェアレベルであり、無料では提供されていません。この機能を使用すると、I2C を使って OLED へデータを送信するため計算する時間が増加します。処理が追いつかないとキーコードが認識されないことがあります。しかし、テストではATmega32U4 での描画時間が2msから5msになり、キーコードが登録されないことが認められたのは、15ミリ秒で1回でした。

90°回転は、メモリの各8ブロックを回転させるビット演算と、バッファメモリを OLED メモリに再配置するために2つの事前に計算された配列を使うことによって実現されています。メモリーマップの定義はリマップの効率化のため、画面の高さ、幅およびブロックサイズを元にあらかじめ計算されています。例えば、ブロックタイプが `uint8_t` の 128x32 サイズであれば、ブロックサイズは64byteになります。このとき、回転と描画には8個の8byteブロックが確保されます。OLED は下図のように、ページを下に移動する前に、2つの 8byte ブロックを水平に描画します。

|   |   |   |   |   |   |
|---|---|---|---|---|---|
| 0 | 1 |   |   |   |   |
| 2 | 3 |   |   |   |   |
| 4 | 5 |   |   |   |   |
| 6 | 7 |   |   |   |   |

ですが、ローカルバッファでは横x縦ではなく、縦x横のように記録されています。

|   |   |   |   |   |   |
|---|---|---|---|---|---|
| 3 | 7 |   |   |   |   |
| 2 | 6 |   |   |   |   |
| 1 | 5 |   |   |   |   |
| 0 | 4 |   |   |   |   |

メモリーマップの定義は、リマップの効率化のため、画面の高さ、幅およびブロックサイズを元にあらかじめ計算されています。

## OLED API

```c
// OLED 回転列挙フラグ
typedef enum {
    OLED_ROTATION_0   = 0,
    OLED_ROTATION_90  = 1,
    OLED_ROTATION_180 = 2,
    OLED_ROTATION_270 = 3, // OLED_ROTATION_90 | OLED_ROTATION_180
} oled_rotation_t;

// OLED を指定した角度での初期化。成功したら true が返ります
bool oled_init(oled_rotation_t rotation);

// ユーザーによってオーバーライド可能な weak 関数で、oled_init の開始時に呼び出されます。
// rotation - oled_init で渡す値
// デフォルト角度を上書きして、新しい oled_rotation_t を返します
oled_rotation_t oled_init_user(oled_rotation_t rotation);

// 画面バッファを消去し、描画位置を0にリセットし、描画のためのバッファをセットします。
void oled_clear(void);

// 再描画の必要があるバッファの描画を実行します
void oled_render(void);

// 描画位置を列と行の値で移動します。範囲を超えている場合は折り返されます。
// 列の最大値は oled_max_chars() によって、行の最大値は oled_max_lines() によって示されます。
void oled_set_cursor(uint8_t col, uint8_t line);

// 描画位置を、引数が true であれば残りを空白で埋めた上で、次のページに進めます。
// 開始位置が範囲外であれば折り返され、ます。
void oled_advance_page(bool clearPageRemainder);

// 描画位置を1文字分進める
// 進めることができなければ次のページ（行）に移動します。
// 開始位置が範囲外であれば折り返されます。
void oled_advance_char(void);

// 現在の描画位置に文字を書き込みます。
// 書き込むと位置は進み、引数の `invert` が `true` ならピクセルが反転します。
// メインルーチンは表示バッファーに文字を書き込みます。
void oled_write_char(const char data, bool invert);

// 現在の描画位置に文字列を書き込みます。
// 書き込み中に描画位置が進みます。引数の `invert` が `true` ならピクセルが反転します。
void oled_write(const char *data, bool invert);

// 現在の描画位置に文字列を書き込みます。
// 書き込むと位置は進み、引数の `invert` が `true` ならピクセルが反転します。
// 描画位置は次のページに進み、残りの箇所は空白で埋められます。
void oled_write_ln(const char *data, bool invert);

// バッファーの中身を右（left が true なら左）へ移動します。
// 新しい描画の準備中に画面を移動するのに役立ちます。
// ロゴのような静的な画像を移動したり、画面焼き付きを防ぐために移動したりする場合は、
// CPU 使用率を削減できる oled_scroll_left や oled_scroll_right を使用するべきです。
void oled_pan(bool left);

// 現在の描画位置に PROGMEM の文字列を書き込みます。
// 書き込むと位置は進み、引数の `invert` が `true` ならピクセルが反転します。
// ARM系なら 'void oled_write(const char *data, bool invert);' を使います。
void oled_write_P(const char *data, bool invert);

// 現在の描画位置に PROGMEM の文字列を書き込みます。
// 書き込むと位置は進み、引数の `invert` が `true` ならピクセルが反転します。
// 描画位置は次のページに進み、残りの箇所は空白で埋められます。
// ARM系なら 'void oled_write_ln(const char *data, bool invert);' を使います。
void oled_write_ln_P(const char *data, bool invert);

// 現在の描画位置に文字列を書き込みます。
void oled_write_raw(const char *data, uint16_t size);

// 描画バッファ内の指定したインデックスに、1バイトを書き込みます。
void oled_write_raw_byte(const char data, uint16_t index);

// 現在の描画位置に PROGMEM の文字列を書き込みます。
void oled_write_raw_P(const char *data, uint16_t size);

// 特定のピクセルをオン、もしくはオフにします。
// 位置は左上が基準(0,0)で、右下に向かうにつれて値が増えます。
void oled_write_pixel(uint8_t x, uint8_t y, bool on);

// 画面がオフになっている場合、手動でオンにできます。
// 画面がオンになっている、またはオンになった時に、`true` を返します。
bool oled_on(void);

// 画面の動作しているとき、手動で停止させます。
// 停止すると true が返ります。
bool oled_off(void);

// 基本的に oled_render と同じですが、タイムアウト管理機能があり、oled_task_user を呼び出します。
void oled_task(void);

// ユーザーによってオーバーライド可能な weak 関数で、oled_task の開始時に呼び出されます。
void oled_task_user(void);

// 特定の8行を、スクロールさせる画面の行として指定します。
// 引数の `start_line` のデフォルトは0、`end_line` のデフォルトは7 で、画面全体の高さを指定します。
// 128x32 の画面では、4-7は使用しません。
void oled_scroll_set_area(uint8_t start_line, uint8_t end_line);

// スクロール速度の設定。0で最速、7で最も遅い。標準は3です。
// スクロールが実行されるまでは反映されません。
// SSD1306では以下の遅延リスト（値はフレーム数）に従った8段階の速度がサポートされています。
// 0=2, 1=3, 2=4, 3=5, 4=25, 5=64, 6=128, 7=256 (※後述の訳注参照)
void oled_scroll_set_speed(uint8_t speed);

// 右方向へのスクロールを開始します。
// スクロールが開始、もしくは完了すれば true が戻ります。
// 注記：スクロール中の画面の変更はできません。
bool oled_scroll_right(void);

// 左方向へのスクロールを開始します。
// スクロールが開始、もしくは完了すれば true が戻ります。
// 注記：スクロール中の画面の変更はできません。
bool oled_scroll_left(void);

// スクロールを止めます。
// スクロールが停止、もしくはスクロールが実行されていなければ true が返ります。
bool oled_scroll_off(void);

// 1行あたりの最大文字数を取得します。
uint8_t oled_max_chars(void);

// OLEDの最大行数を取得します。
uint8_t oled_max_lines(void);
```

!> スクロールと回転はSH1106ではサポートされていません。

> **oled_scroll_set_speed の訳註**<br>
コメントにある遅延順序の対応値は原文に基づいていますが、
[qmk_firmware/oled_driver.c](https://github.com/qmk/qmk_firmware/blob/c9eaf1ac2ba0e9114343815432de524062f4c94f/drivers/oled/oled_driver.c#L537-L552) に従った場合、遅延順序は下記の通りになります。<br>
// 0=5, 1=64, 2=128, 3=256, 4=3, 5=4, 6=25, 7=2

## SSD1306.h ドライバー変換ガイド

|旧API                    |推奨する新しいAPI                 |
|-------------------------|---------------------------------|
|`struct CharacterMatrix` |*(削除されました)*                    |
|`iota_gfx_init`          |`oled_init`                      |
|`iota_gfx_on`            |`oled_on`                        |
|`iota_gfx_off`           |`oled_off`                       |
|`iota_gfx_flush`         |`oled_render`                    |
|`iota_gfx_write_char`    |`oled_write_char`                |
|`iota_gfx_write`         |`oled_write`                     |
|`iota_gfx_write_P`       |`oled_write_P`                   |
|`iota_gfx_clear_screen`  |`oled_clear`                     |
|`matrix_clear`           |*(削除されました)*                    |
|`matrix_write_char_inner`|`oled_write_char`                |
|`matrix_write_char`      |`oled_write_char`                |
|`matrix_write`           |`oled_write`                     |
|`matrix_write_ln`        |`oled_write_ln`                  |
|`matrix_write_P`         |`oled_write_P`                   |
|`matrix_write_ln_P`      |`oled_write_ln_P`                |
|`matrix_render`          |`oled_render`                    |
|`iota_gfx_task`          |`oled_task`                      |
|`iota_gfx_task_user`     |`oled_task_user`                 |
