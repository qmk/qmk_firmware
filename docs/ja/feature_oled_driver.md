# OLEDドライバー
## サポートされるハードウェア

OLEDモジュールはSSD1306もしくはSH1106が搭載されたICを、I2Cを通じて使用します。

テスト済みの組み合わせ:

|IC       |サイズ|プラットフォーム|注記                   |
|---------|------|----------------|------------------------|
|SSD1306  |128x32|AVR     |主要サポート         |
|SSD1306  |128x64|AVR     |動作確認済み         |
|SSD1306  |128x32|Arm     |                    |
|SH1106   |128x64|AVR     |回転・スクロールは不可|

検証はされていませんが、ARMベースのマイコンや、サイズの違うOLEDモジュールでも互換性はあるでしょう。

!> 注意: このドライバーは、今のところ分割キーボードを元にしたi2c_masterドライバーを使用しています。もし分割キーボード間の通信にI2Cを利用している場合、アドレスの衝突が起こる可能性があります(シリアル通信では影響しない)。キーボードの開発者にコードのアップデートや修正を問い合わせてみてください。また、液晶の焼き付きを防ぐためのタイムアウトは、分割キーボード向けのキー押下検出プログラムに基づいているので、非分割キーボードでは、独自にタイムアウトのプログラムを実装する必要があります。

## 使い方

OLEDを有効にするには、はじめにコンパイルしたいキーボードの`rules.mk`に次の一文を追加します。

```make
OLED_DRIVER_ENABLE = yes
```

`keymap.c`ファイルにOLEDタスク呼び出しを実装します。この例におけるキーマップでは`_QWERTY`、`_FN`、`_ADJ`の3つのレイヤーが存在するものとします。 

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

    // キーボードのLED状態
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}
#endif
```

## ロゴ

標準フォントでは、QMKロゴのために一定の領域が予約済みです。液晶にロゴを描画するには、この例のように記述します:

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

分割キーボードでは2つのOLEDに異なる情報を描画したり、回転や反転させることがよくあります。描画したい情報の切り替えは、`split_util.h`に含まれる、`is_keyboard_master()`や`is_keyboard_left()`の戻り値によって実装できます:

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
        oled_scroll_left();  // スクロールを有効にする
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
|`OLED_TIMEOUT`             |`60000`          |焼き付き抑止のため、キーボードを操作していないときに60秒後にディスプレイを切る。0なら電源は切らない           |
|`OLED_SCROLL_TIMEOUT`      |`0`              |焼き付き抑止のため、キーボードを操作していないときにスクロールさせるまでの間隔。0ならスクロールはしない                     |
|`OLED_SCROLL_TIMEOUT_RIGHT`|*Not defined*    |定義された場合、右にスクロールする。未定義なら左方向                                                      |
|`OLED_IC`                  |`OLED_IC_SSD1306`|SH1106コントローラーを使う場合、`OLED_IC_SH1106`に設定                                                       |
|`OLED_COLUMN_OFFSET`       |`0`              |(SH1106のみ) 指定地だけピクセルを右にシフト。132x64サイズの液晶において128x64の画像を中寄せするときに便利です|

 ## 128x64と独自サイズのOLEDディスプレイ

標準の画面サイズは128x32で、すべての必要な定義はこの値を元に算出されています。128x64サイズのために`OLED_DISPLAY_128X64`という定義を追加しました。同様に独自の値を定義できるように`OLED_DISPLAY_CUSTOM`も追加しています。

|定義               |標準値        |内容                                                                                                                             |
|---------------------|---------------|----------------------------------------------------------------------------------------------------------------------------------------|
|`OLED_DISPLAY_128X64`|*Not defined*  |128x64ディスプレイの定義に変更                                                                               |
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

SSD1306ドライバーは0と180°の描画のみネイティブでサポートされています。この処理はソフトウェアレベルであり、無料では提供されていません。この機能を使用するとI2CからOLEDへ送信するための計算に時間がかかるようになります。処理が追いつかないとキーコードが認識しないことがあります。とはいうものの、テストしてみたところ、ATmega32U4では描画に2msから5msになったくらいで、キーコードの影響が出てくるのは15msくらいからでした。

90°回転はメモリーの各8ブロックをビット演算で回転させ、OLEDメモリーに転送するための事前計算の結果を2つのバッファメモリーに記録しています。メモリーマップの定義はリマップの効率化のため、画面とブロックサイズをもとに、あらかじめ計算されます。例えば、ブロックタイプが`uint8_t`の128x32サイズであれば、ブロックサイズは64byteになります。このとき、回転と描画には8個の8byteブロックが確保されます。OLEDは下図のように、ページを下に移動する前に、2つの8byteブロックを水平に描画します。

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

つまり、これらの計算された配列は、メモリーのオフセットを単にインデックス化しているだけなのです。

## OLED API

```c
// OLED回転列挙フラグ
typedef enum {
    OLED_ROTATION_0   = 0,
    OLED_ROTATION_90  = 1,
    OLED_ROTATION_180 = 2,
    OLED_ROTATION_270 = 3, // OLED_ROTATION_90 | OLED_ROTATION_180
} oled_rotation_t;

// OLEDを指定した角度での初期化。成功したらtrueが返る
bool oled_init(oled_rotation_t rotation);

// この関数をオーバーライドすることで、oled_initが開始されたら呼び出される。
// rotation - oled_initで渡された値
// rotationを上書きした場合は、その値を返す
oled_rotation_t oled_init_user(oled_rotation_t rotation);

// 画面バッファを消去し、描画位置を0にリセットし、再描画の要求をする
void oled_clear(void);

// 再描画の必要があるバッファの描画を実行する
void oled_render(void);

// 描画位置を列と行の値で移動する。範囲を超えている場合は折り返される。
// 列の最大値は'oled_max_chars()'で、行の最大値は'oled_max_lines()'で取得する。 
void oled_set_cursor(uint8_t col, uint8_t line);

// 描画位置を、引数がtrueであれば残りを空白で埋めた上で、次のページに進める。
// 開始位置が範囲外であれば折り返される。
void oled_advance_page(bool clearPageRemainder);

// 描画位置を1文字分進める
// 進めることができなければ次のページ（行）に移動する。
// 開始位置が範囲外であれば折り返される。
void oled_advance_char(void);

// 現在の描画位置に文字を書き込む。
// 書き込むと位置は進み、invertがtrueであれば、文字が反転する。
// メインルーチンは表示バッファーに文字を書き込む。
void oled_write_char(const char data, bool invert);

// 現在の描画位置に文字列を書き込む。
// 書き込むと位置は進み、invertがtrueであれば、文字が反転する。
void oled_write(const char *data, bool invert);

// 現在の描画位置に文字列を書き込む。
// 書き込むと位置は進み、invertがtrueであれば、文字が反転する。
// 描画位置は次のページに進み、残りの箇所は空白で埋められる。
void oled_write_ln(const char *data, bool invert);

// バッファーの中身を右（leftがtrueなら左）へ移動する。
// これは新しい描画の際に画面を移動させるのに便利。
// 焼き付きを避けるためのロゴなどの画像において、CPUの使用率を削減できる。
// 静的な移動であれば、oled_scroll_leftやoled_scroll_rightを使用すべき。
void oled_pan(bool left);

// 現在の描画位置にPROGMEMの文字列を書き込む。
// 書き込むと位置は進み、invertがtrueであれば、文字が反転する。
// ARM系なら'void oled_write(const char *data, bool invert);'を使う
void oled_write_P(const char *data, bool invert);

// 現在の描画位置にPROGMEMの文字列を書き込む。
// 書き込むと位置は進み、invertがtrueであれば、文字が反転する。
// 描画位置は次のページに進み、残りの箇所は空白で埋められる。
// ARM系なら'void oled_write_ln(const char *data, bool invert);'を使う
void oled_write_ln_P(const char *data, bool invert);

// 現在の描画位置に文字列を書き込む。
void oled_write_raw(const char *data, uint16_t size);

// 描画バッファ内の指定したインデックスに、1バイトを書き込む。
void oled_write_raw_byte(const char data, uint16_t index);

// 現在の描画位置にPROGMEMの文字列を書き込む。
void oled_write_raw_P(const char *data, uint16_t size);

// 特定のピクセルをオン、もしくはオフにする
// 位置は左上が基準(0,0)で、右下に向かうにつれて値が増える。
void oled_write_pixel(uint8_t x, uint8_t y, bool on);

// 画面が動作していない場合、手動で動作させる。
// 動作するようになるとtrueが返る。
bool oled_on(void);

// 画面の動作しているとき、手動で停止させる。
// 停止するとtrueが返る。
bool oled_off(void);

// 基本的にoled_renderと同じだが、タイムアウト管理が行われ、oled_task_userが呼び出される。
void oled_task(void);

// この関数をオーバーライドすることで、oled_taskが開始されると呼び出される。
void oled_task_user(void);

// スクロールさせる行を設定する。
// 標準は画面の高さで0と7。128x32の画面では4～7行は使われない。
void oled_scroll_set_area(uint8_t start_line, uint8_t end_line);

// スクロール速度の設定。0で最速、7で最も遅い。標準は3。
// スクロールが実行されるまでは反映されない。
// SSD1306では以下の遅延リスト（値はフレーム数）に従った8段階の速度がサポートされている。
// 0=2, 1=3, 2=4, 3=5, 4=25, 5=64, 6=128, 7=256
void oled_scroll_set_speed(uint8_t speed);

// 右方向へのスクロールを開始する。
// スクロールが開始、もしくは完了すればtrueが戻る。
// 注記：スクロール中の画面の変更はできない。
bool oled_scroll_right(void);

// 左方向へのスクロールを開始する。
// スクロールが開始、もしくは完了すればtrueが戻る。
// 注記：スクロール中の画面の変更はできない。
bool oled_scroll_left(void);

// スクロールを止める。
// スクロールが停止、もしくはスクロールが実行されていなければtrueが返る。
bool oled_scroll_off(void);

// 1行あたりの最大文字数を取得する
uint8_t oled_max_chars(void);

// OLEDの最大行数を取得する
uint8_t oled_max_lines(void);
```

!> スクロールと回転はSH1106ではサポートされていない。

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