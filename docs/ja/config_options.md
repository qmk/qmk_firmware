# QMK の設定

<!---
  original document: 0.12.41:docs/config_options.md
  git diff 0.12.41 HEAD -- docs/config_options.md | cat
-->

QMK はほぼ無制限に設定可能です。可能なところはいかなるところでも、やりすぎな程、ユーザーがコードサイズを犠牲にしてでも彼らのキーボードをカスタマイズをすることを許しています。ただし、このレベルの柔軟性により設定が困難になります。

QMK には主に２種類の設定ファイルがあります- `config.h` と `rules.mk`。これらのファイルは QMK の様々なレベルに存在し、同じ種類の全てのファイルは最終的な設定を構築するために組み合わされます。最低の優先度から最高の優先度までのレベルは以下の通りです:

* QMK デフォルト
* キーボード
* フォルダ (最大5レべルの深さ)
* キーマップ

## QMK デフォルト

QMK での全ての利用可能な設定にはデフォルトがあります。その設定がキーボード、フォルダ、あるいはキーマップレべルで設定されない場合、これが使用される設定です。

## キーボード

このレベルにはキーボード全体に適用される設定オプションが含まれています。一部の設定は、リビジョンあるいはほとんどのキーマップで変更されません。他の設定はこのキーボードのデフォルトに過ぎず、フォルダあるいはキーマップによって上書きされる可能性があります。

## フォルダ

一部のキーボードには、異なるハードウェア構成のためのフォルダとサブフォルダがあります。ほとんどのキーボードは深さ1のフォルダのみですが、QMK は最大深さ5のフォルダの構造をサポートします。各フォルダは、最終的な設定に組み込まれる独自の `config.h` と `rules.mk` ファイルを持つことができます。

## キーマップ

このレベルには特定のキーマップのための全てのオプションが含まれています。以前の定義を上書きしたい場合は、`#undef <variable>` を使って定義を解除し、エラー無しで再定義することができます。

# `config.h` ファイル

これは最初に include されるものの 1 つである C ヘッダファイルで、プロジェクト全体(もし含まれる場合)にわたって持続します。多くの変数をここで設定し、他の場所からアクセスすることができます。`config.h` ファイルでは、以下のもの以外の、他の `config.h`  ファイルやその他のファイルの include をしないでください:

```c
#include "config_common.h"
```


## ハードウェアオプション
* `#define VENDOR_ID 0x1234`
  * VID を定義します。ほとんどの DIY プロジェクトにおいて、任意のものを定義できます
* `#define PRODUCT_ID 0x5678`
  * PID を定義します。ほとんどの DIY プロジェクトでは、任意のものを定義できます
* `#define DEVICE_VER 0`
  * デバイスのバージョンを定義します (多くの場合リビジョンに使われます)
* `#define MANUFACTURER Me`
  * 一般的に、誰もしくはどのブランドがボードを作成したか
* `#define PRODUCT Board`
  * キーボードの名前
* `#define MATRIX_ROWS 5`
  * キーボードのマトリックスの行の数
* `#define MATRIX_COLS 15`
  * キーボードのマトリックスの列の数
* `#define MATRIX_ROW_PINS { D0, D5, B5, B6 }`
  * 行のピン、上から下へ
* `#define MATRIX_COL_PINS { F1, F0, B0, C7, F4, F5, F6, F7, D4, D6, B4, D7 }`
  * 列のピン、左から右へ
* `#define MATRIX_IO_DELAY 30`
  * マトリックスピン状態の変更と値の読み取り間のマイクロ秒単位の遅延
* `#define UNUSED_PINS { D1, D2, D3, B1, B2, B3 }`
  * 参考として、キーボードで使われていないピン
* `#define MATRIX_HAS_GHOST`
  * マトリックスにゴーストがあるか(ありそうにないか)定義します
* `#define DIODE_DIRECTION COL2ROW`
  * COL2ROW あるいは ROW2COL - マトリックスがどのように設定されているか。COL2ROW は、スイッチとロウ(行)ラインの間にダイオードが黒い印をロウ(行)ラインに向けて置いてあることを意味します。
* `#define DIRECT_PINS { { F1, F0, B0, C7 }, { F4, F5, F6, F7 } }`
  * ロウ(行)ラインとカラム(列)ラインにマップされているピンを左から右に。各スイッチが個別のピンとグラウンドに接続されているマトリックスを定義します。
* `#define AUDIO_VOICES`
  * (循環させるために)代替音声を有効にします
* `#define C4_AUDIO`
  * ピン C4 のオーディオを有効にします
  * 非推奨。`#define AUDIO_PIN C4` を使ってください
* `#define C5_AUDIO`
  * ピン C5 のオーディオを有効にします
  * 非推奨。`#define AUDIO_PIN C5` を使ってください
* `#define C6_AUDIO`
  * ピン C6 のオーディオを有効にします
  * 非推奨。`#define AUDIO_PIN C6` を使ってください
* `#define B5_AUDIO`
  * ピン B5 のオーディオを有効にします (C ピンの1つとともに B ピンの1つが有効にされている場合、疑似ステレオが有効にされます)
  * 非推奨。もし `AUDIO_PIN` で `C` ピンを有効にしている場合は、`#define AUDIO_PIN_ALT B5` を使い、そうでなければ `#define AUDIO_PIN B5` を使います。
* `#define B6_AUDIO`
  * ピン B6 のオーディオを有効にします (C ピンの1つとともに B ピンの1つが有効にされている場合、疑似ステレオが有効にされます)
  * 非推奨。もし `AUDIO_PIN` で `C` ピンを有効にしている場合は、`#define AUDIO_PIN_ALT B6` を使い、そうでなければ `#define AUDIO_PIN B6` を使います。
* `#define B7_AUDIO`
  * ピン B7 のオーディオを有効にします (C ピンの1つとともに B ピンの1つが有効にされている場合、疑似ステレオが有効にされます)
  * 非推奨。もし `AUDIO_PIN` で `C` ピンを有効にしている場合は、`#define AUDIO_PIN_ALT B7` を使い、そうでなければ `#define AUDIO_PIN B7` を使います。
* `#define BACKLIGHT_PIN B7`
  * バックライトのピン
* `#define BACKLIGHT_LEVELS 3`
  * バックライトのレベル数 (off を除いて最大31)
* `#define BACKLIGHT_BREATHING`
  * バックライトのブレスを有効にします
* `#define BREATHING_PERIOD 6`
  * 1つのバックライトの "ブレス" の長さの秒数
* `#define DEBOUNCE 5`
  * ピンの値を読み取る時の遅延 (5がデフォルト)
* `#define LOCKING_SUPPORT_ENABLE`
  * メカニカルロックのサポート。キーマップで KC_LCAP、KC_LNUM そして KC_LSCR を使えるようにします
* `#define LOCKING_RESYNC_ENABLE`
  * キーボードの LED の状態をスイッチの状態と一致させ続けようとします
* `#define IS_COMMAND() (get_mods() == MOD_MASK_SHIFT)`
  * マジックコマンドの使用を可能にするキーの組み合わせ (デバッグに便利です)
* `#define USB_MAX_POWER_CONSUMPTION 500`
  * デバイスの USB 経由の最大電力(mA) を設定します (デフォルト: 500)
* `#define USB_POLLING_INTERVAL_MS 10`
  * キーボード、マウス および 共有 (NKRO/メディアキー) インタフェースのための USB ポーリングレートをミリ秒で設定します
* `#define USB_SUSPEND_WAKEUP_DELAY 200`
   * ウェイクアップパケットを送信した後で一時停止するミリ秒を設定します
* `#define F_SCL 100000L`
  * I2C を使用するキーボードのための I2C クロックレート速度を設定します。デフォルトは `400000L` ですが、`split_common` を使っているキーボードは別でデフォルトは `100000L` です。

## 無効にできる機能

これらのオプションを定義すると、関連する機能が無効になり、コードサイズを節約できます。

* `#define NO_DEBUG`
  * デバッグを無効にします
* `#define NO_PRINT`
  * hid_listen を使った出力やデバッグを無効にします
* `#define NO_ACTION_LAYER`
  * レイヤーを無効にします
* `#define NO_ACTION_TAPPING`
  * タップダンスと他のタップ機能を無効にします
* `#define NO_ACTION_ONESHOT`
  * ワンショットモディファイアを無効にします
* `#define NO_ACTION_MACRO`
  * `MACRO()`、`action_get_macro()` _(非推奨)_ を使う古い形式のマクロ処理を無効にします
* `#define NO_ACTION_FUNCTION`
  * `fn_actions`、`action_function()` _(非推奨)_ を使う古い形式の関数処理を無効にします

## 有効にできる機能

これらのオプションを定義すると、関連する機能が有効になり、コードサイズが大きくなるかもしれません。

* `#define FORCE_NKRO`
  * NKRO をデフォルトでオンにする必要があります。これにより EEPROM の設定に関係なく、キーボードの起動時に NKRO が強制的にオンになります。NKRO は引き続きオフにできますが、キーボードを再起動すると再びオンになります。
* `#define STRICT_LAYER_RELEASE`
  * キーリリースがどのレイヤーから来たのかを覚えるのではなく、現在のレイヤースタックを使って強制的に評価されるようにします (高度なケースに使われます)

## 設定可能な挙動

* `#define TAPPING_TERM 200`
  * タップがホールドになるまでの時間。500以上に設定された場合、タップ期間中にタップされたキーもホールドになります。(訳注: PERMISSIVE_HOLDも参照)
* `#define TAPPING_TERM_PER_KEY`
  * キーごとの `TAPPING_TERM` 設定の処理を有効にします
* `#define RETRO_TAPPING`
  * 押下とリリースの間に他のキーによる中断がなければ、TAPPING_TERM の後であってもとにかくタップします
  * 詳細は [Retro Tapping](ja/tap_hold.md#retro-tapping) を見てください
* `#define RETRO_TAPPING_PER_KEY`
  * キーごとの `RETRO_TAPPING` 設定の処理を有効にします
* `#define TAPPING_TOGGLE 2`
  * トグルを引き起こす前のタップ数
* `#define PERMISSIVE_HOLD`
  * `TAPPING_TERM` にヒットしていなくても、リリースする前に別のキーが押されると、タップとホールドキーがホールドを引き起こします
  * 詳細は [Permissive Hold](ja/tap_hold.md#permissive-hold) を見てください
* `#define PERMISSIVE_HOLD_PER_KEY`
  * キーごとの `PERMISSIVE_HOLD` 設定の処理を有効にします
* `#define IGNORE_MOD_TAP_INTERRUPT`
  * 両方のキーに `TAPPING_TERM` を適用することで、ホールド時に他のキーに変換するキーを使ってローリングコンボ (zx) をすることができるようにします
  * 詳細は [Ignore Mod Tap Interrupt](ja/tap_hold.md#ignore-mod-tap-interrupt) を見てください
* `#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY`
  * キーごとの `IGNORE_MOD_TAP_INTERRUPT` 設定の処理を有効にします
* `#define TAPPING_FORCE_HOLD`
  * タップされた直後に、デュアルロールキーを修飾子として使用できるようにします
  * [Tapping Force Hold](ja/tap_hold.md#tapping-force-hold)を見てください
  * タップトグル機能を無効にします (`TT` あるいは One Shot Tap Toggle)
* `#define TAPPING_FORCE_HOLD_PER_KEY`
  * キーごとの `TAPPING_FORCE_HOLD` 設定処理を有効にします。
* `#define LEADER_TIMEOUT 300`
  * リーダーキーがタイムアウトするまでの時間
    * タイムアウトする前にシーケンスを終了できない場合は、タイムアウトの設定を増やす必要があるかもしれません。あるいは、`LEADER_PER_KEY_TIMING` オプションを有効にすると良いでしょう。これは各キーがタップされた後でタイムアウトを再設定します。
* `#define LEADER_PER_KEY_TIMING`
  * 全体では無く各キーを押すたびに実行されるリーダーキーコードのタイマーを設定します
* `#define LEADER_KEY_STRICT_KEY_PROCESSING`
  * Mod-Tap および Layer-Tap キーコードのためのキーコードフィルタリングを無効にします。例えば、これを有効にすると、`KC_A` を使いたい場合は `MT(MOD_CTL, KC_A)` を指定する必要があります。
* `#define ONESHOT_TIMEOUT 300`
  * ワンショットがタイムアウトするまでの時間
* `#define ONESHOT_TAP_TOGGLE 2`
  * ワンショットトグルが引き起こされるまでのタップ数
* `#define QMK_KEYS_PER_SCAN 4`
  * 走査ごとに1つ以上のキーを送信できるようにします。デフォルトでは、走査ごとに `process_record()` 経由で1つのキーイベントのみが送信されます。これはほとんどのタイピングにほとんど影響しませんが、多くのコードを入力しているか、走査レートが最初から遅い場合、キーイベントの処理に多少の遅延が生じる可能性があります。それぞれのプレスとリリースは別のイベントです。スキャン時間が 1ms 程度のキーボードの場合、とても高速なタイピストでさえ、実際にキーボードから数 ms 以上の遅延を発生させるのに必要な 500 キーストロークを1秒間に生成することはないでしょう。しかし、3～4ms の走査時間でコードを入力している場合はどうでしょうか？おそらくこれが必要です。
* `#define COMBO_COUNT 2`
  * [コンボ](ja/feature_combo.md)機能で使っているコンボの数にこれを設定します。
* `#define COMBO_TERM 200`
  * コンボキーが検出されるまでの時間。定義されていない場合は、デフォルトは `TAPPING_TERM` です。
* `#define TAP_CODE_DELAY 100`
  * 適切な登録に問題がある場合(VUSB ボードで珍しくない)、`register_code` と `unregister_code` の間の遅延を設定します。値はミリ秒です。
* `#define TAP_HOLD_CAPS_DELAY 80`
  * MacOS で特別な処理が行われるため、`KC_CAPSLOCK` を使う時にタップホールドキー (`LT`, `MT`) に遅延を設定します。この値はミリ秒で、定義されていない場合はデフォルトは80msです。macOS については、これを200以上に設定すると良いでしょう。

## RGB ライト設定 :id=rgb-light-configuration

* `#define RGB_DI_PIN D7`
  * WS2812 の DI 端子につなぐピン
* `#define RGBLIGHT_ANIMATIONS`
  * RGB アニメーションを実行します
* `#define RGBLIGHT_LAYERS`
  * オンとオフを切り替えることができる [ライトレイヤー](ja/feature_rgblight.md?id=lighting-layers) を定義できます。現在のキーボードレイヤーまたは Caps Lock 状態を表示するのに最適です。
* `#define RGBLIGHT_MAX_LAYERS`
  * デフォルトは8です。もしさらに [ライトレイヤー](ja/feature_rgblight.md?id=lighting-layers) が必要であれば、32まで拡張できます。
  * メモ: 最大値を大きくするとファームウェアサイズが大きくなり、分割キーボードで同期が遅くなります。
* `#define RGBLIGHT_LAYER_BLINK`
  * 指定されたミリ秒の間、ライトレイヤーを [点滅](ja/feature_rgblight.md?id=lighting-layer-blink) する機能を追加します(例えば、アクションを確認するため)。
* `#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF`
  * 定義されている場合、RGB ライトがオフになっている場合でも [ライトレイヤー](ja/feature_rgblight?id=overriding-rgb-lighting-onoff-status) が表示されます。
* `#define RGBLED_NUM 12`
  * LED の数
* `#define RGBLIGHT_SPLIT`
  * 分割キーボードの左半分の RGB LED の出力を右半分の RGB LED の入力につなげるかわりに、それぞれの側で個別にコントローラの出力ピンが直接 RGB LED の入力に繋がっているときは、この定義が必要です。
* `#define RGBLED_SPLIT { 6, 6 }`
  * 分割キーボードの各半分の `RGB_DI_PIN` に直接配線されている接続されている LED の数
  * 最初の値は左半分の LED の数を示し、2番目の値は右半分です。
  * RGBLED_SPLIT が定義されている場合、RGBLIGHT_SPLIT は暗黙的に定義されます。
* `#define RGBLIGHT_HUE_STEP 12`
  * 色相の増減時のステップ単位
* `#define RGBLIGHT_SAT_STEP 25`
  * 彩度の増減時のステップ単位
* `#define RGBLIGHT_VAL_STEP 12`
  * 値(明度)の増減時のステップ単位
* `#define RGBW`
  * RGBW LED のサポートを有効にします

## マウスキーオプション

* `#define MOUSEKEY_INTERVAL 20`
* `#define MOUSEKEY_DELAY 0`
* `#define MOUSEKEY_TIME_TO_MAX 60`
* `#define MOUSEKEY_MAX_SPEED 7`
* `#define MOUSEKEY_WHEEL_DELAY 0`

## 分割キーボードオプション

分割キーボード固有のオプション。あなたの rules.mk に 'SPLIT_KEYBOARD = yes' が有ることを確認してください。

* `SPLIT_TRANSPORT = custom`
  * 標準の分割通信ルーチンをカスタムのものに置き換えることができます。現在、ARM ベースの分割キーボードはこれを使わなければなりません。

### 左右の設定

1つ覚えておかなければならないことは、USB ポートが接続されている側が常にマスター側であるということです。USB に接続されていない側はスレーブです。

分割キーボードの左右を設定するには、幾つかの異なる方法があります (優先度の順にリストされています):

1. `SPLIT_HAND_PIN` を設定します: 左右を決定するためにピンを読み込みます。ピンが high の場合、それが左側です。low であれば、その半分側が右側であると決定されます。
2. `EE_HANDS` を設定し、各半分に `eeprom-lefthand.eep`/`eeprom-righthand.eep` を書き込みます
   * DFU ブートローダを搭載したボードでは、これらの EEPROM ファイルを書き込むために `:dfu-split-left`/`:dfu-split-right` を使うことができます
   * Caterina ブートローダを搭載したボード (標準的な Pro Micros など)では、`:avrdude-split-left`/`:avrdude-split-right` を使ってください
   * ARM DFU ブートローダを搭載したボード (Proton C など)では、`:dfu-util-split-left`/`:dfu-util-split-right` を使ってください
3. `MASTER_RIGHT` を設定します: USB ポートに差し込まれた側はマスター側で右側であると決定されます(デフォルトの逆)
4. デフォルト: USB ポートに差し込まれている側がマスター側であり、左側であると見なされます。スレーブ側は右側です

#### 左右を定義します

* `#define SPLIT_HAND_PIN B7`
  * high/low ピンを使って左右を決定します。low = 右手、high = 左手。`B7` を使っているピンに置き換えます。これはオプションで、`SPLIT_HAND_PIN` が未定義のままである場合、EE_HANDS メソッドまたは標準の Let's Splitが使っている MASTER_LEFT / MASTER_RIGHT 定義をまだ使うことができます。

* `#define SPLIT_HAND_MATRIX_GRID <out_pin>,<in_pin>`
  * 左右はキーマトリックスのキースイッチが存在しない交点を使って決定されます。通常、この交点が短絡している(ローレベル)のときに左側と見なされます。もし `#define SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT` が定義されている場合は、ローレベルの時に右側と決定されます。

* `#define EE_HANDS` (`SPLIT_HAND_PIN` と `SPLIT_HAND_MATRIX_GRID` が定義されていない場合のみ動作します)
  * `eeprom-lefthand.eep`/`eeprom-righthand.eep` がそれぞれの半分に書き込まれた後で、EEPROM 内に格納されている左右の設定の値を読み込みます。

* `#define MASTER_RIGHT`
  * マスター側が右側と定義されます。

### 他のオプション

* `#define USE_I2C`
  * Serial の代わりに I2C を使う場合 (デフォルトは serial)

* `#define SOFT_SERIAL_PIN D0`
  * serial を使う場合、これを定義します。`D0` あるいは `D1`,`D2`,`D3`,`E6`。

* `#define MATRIX_ROW_PINS_RIGHT { <row pins> }`
* `#define MATRIX_COL_PINS_RIGHT { <col pins> }`
  * 右半分に左半分と異なるピン配置を指定したい場合は、`MATRIX_ROW_PINS_RIGHT`/`MATRIX_COL_PINS_RIGHT` を定義することができます。現在のところ、`MATRIX_ROW_PINS` のサイズは `MATRIX_ROW_PINS_RIGHT` と同じでなければならず、列の定義も同様です。

* `#define DIRECT_PINS_RIGHT { { F1, F0, B0, C7 }, { F4, F5, F6, F7 } }`
  * 右半分に左半分と異なる直接ピン配置を指定したい場合は、`DIRECT_PINS_RIGHT` を定義することができます。現在のところ、`DIRECT_PINS` のサイズは `DIRECT_PINS_RIGHT` と同じでなければなりません。

* `#define RGBLED_SPLIT { 6, 6 }`
  * [RGB ライト設定](#rgb-light-configuration)を見てください。

* `#define SELECT_SOFT_SERIAL_SPEED <speed>` (デフォルトの速度は1です)
  * serial 通信を使う時のプロトコルの速度を設定します。
  * 速度:
    * 0: 約 189kbps (実験目的のみ)
    * 1: 約 137kbps (デフォルト)
    * 2: 約 75kbps
    * 3: 約 39kbps
    * 4: 約 26kbps
    * 5: 約 20kbps

* `#define SPLIT_USB_DETECT`
  * マスタ/スレーブを委任する時に(タイムアウト付きで) USB 接続を検出します
  * ARM についてはデフォルトの挙動
  * AVR Teensy については必須

* `#define SPLIT_USB_TIMEOUT 2000`
  * `SPLIT_USB_DETECT` を使う時のマスタ/スレーブを検出する場合の最大タイムアウト

* `#define SPLIT_USB_TIMEOUT_POLL 10`
  * `SPLIT_USB_DETECT` を使う時のマスタ/スレーブを検出する場合のポーリング頻度

# `rules.mk` ファイル

これは、トップレベルの `Makefile` から include される [make](https://www.gnu.org/software/make/manual/make.html) ファイルです。これは特定の機能を有効または無効にするだけでなく、コンパイルする MCU に関する情報を設定するために使われます。

## ビルドオプション

* `DEFAULT_FOLDER`
  * キーボードに1つ以上のサブフォルダがある場合にデフォルトのフォルダを指定するために使われます。
* `FIRMWARE_FORMAT`
  * ビルドの後でルート `qmk_firmware` フォルダにコピーされる形式 (bin, hex) を定義します。
* `SRC`
  * コンパイル・リンクリストにファイルを追加するために使われます。
* `LIB_SRC`
  * コンパイル・リンクリストにライブラリとしてファイルを追加するために使われます。  
    `LIB_SRC` で指定されたファイルは、`SRC` で指定されたファイルの後にリンクされます。  
    例えば、次のように指定した場合:
    ```
    SRC += a.c
    LIB_SRC += lib_b.c
    SRC += c.c
    LIB_SRC += lib_d.c
    ```
    リンク順は以下の通りです。
    ```
     ...  a.o c.o  ...  lib_b.a lib_d.a  ...
    ```
* `LAYOUTS`
  * このキーボードがサポートする[レイアウト](ja/feature_layouts.md)のリスト
* `LTO_ENABLE`
  * キーボードをコンパイルする時に、Link Time Optimization (LTO) を有効にします。これは処理に時間が掛かりますが、コンパイルされたサイズを大幅に減らします (そして、ファームウェアが小さいため、追加の時間は分からないくらいです)。
ただし、LTO が有効な場合、古い TMK のマクロと関数の機能が壊れるため、自動的にこれらの機能を無効にします。これは `NO_ACTION_MACRO` と `NO_ACTION_FUNCTION` を自動的に定義することで行われます。(メモ: これは QMK の [マクロ](ja/feature_macros.md) と [レイヤー](ja/feature_layers.md) には影響を与えません。)

## AVR MCU オプション
* `MCU = atmega32u4`
* `F_CPU = 16000000`
* `ARCH = AVR8`
* `F_USB = $(F_CPU)`
* `OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT`
* `BOOTLOADER = atmel-dfu` と以下のオプション:
  * `atmel-dfu`
  * `lufa-dfu`
  * `qmk-dfu`
  * `halfkay`
  * `caterina`
  * `bootloadHID`
  * `USBasp`

## 機能オプション :id=feature-options

これらを使って特定の機能のビルドを有効または無効にします。有効にすればするほどファームウェアが大きくなり、MCU には大きすぎるファームウェアを構築するリスクがあります。

* `BOOTMAGIC_ENABLE`
  * 仮想 DIP スイッチ設定
* `MOUSEKEY_ENABLE`
  * マウスキー
* `EXTRAKEY_ENABLE`
  * オーディオ制御とシステム制御
* `CONSOLE_ENABLE`
  * デバッグ用コンソール
* `COMMAND_ENABLE`
  * デバッグ及び設定用のコマンド
* `COMBO_ENABLE`
  * キーコンボ機能
* `NKRO_ENABLE`
  * USB N-キーロールオーバー - これが動作しない場合は、ここを見てください: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
* `AUDIO_ENABLE`
  * オーディオサブシステムを有効にします。
* `RGBLIGHT_ENABLE`
  * キーボードアンダーライト機能を有効にします
* `LEADER_ENABLE`
  * リーダーキーコードを有効にします
* `MIDI_ENABLE`
  * MIDI 制御
* `UNICODE_ENABLE`
  * Unicode
* `BLUETOOTH`
  * 現在のオプションは、AdafruitBLE、RN42
* `SPLIT_KEYBOARD`
  * 分割キーボード (let's split や bakingpy のキーボードのようなデュアル MCU) のサポートを有効にし、quantum/split_common にある全ての必要なファイルをインクルードします
* `CUSTOM_MATRIX`
  * 標準マトリックス走査ルーチンを独自のものに置き換えることができます。
* `DEBOUNCE_TYPE`
  * 標準キーデバウンスルーチンを代替または独自のものに置き換えることができます。
* `WAIT_FOR_USB`
  * キーボードが起動する前に、USB 接続が確立されるのをキーボードに待機させます
* `NO_USB_STARTUP_CHECK`
  * キーボードの起動後の usb サスペンドチェックを無効にします。通常、キーボードはタスクが実行される前にホストがウェイク アップするのを待ちます。分割キーボードは半分はウェイクアップコールを取得できませんが、マスタにコマンドを送信する必要があるため、役に立ちます。

## USB エンドポイントの制限

USB 経由でサービスを提供するために、QMK は USB エンドポイントを使う必要があります。
これらは有限なリソースです: 各マイクロコントローラは特定の数しか持ちません。
これは一緒に有効にできる機能を制限します。
利用可能なエンドポイントを超えると、ビルドエラーをひきおこします。

以下の機能は個別のエンドポイントを必要とするかもしれません:

* `MOUSEKEY_ENABLE`
* `EXTRAKEY_ENABLE`
* `CONSOLE_ENABLE`
* `NKRO_ENABLE`
* `MIDI_ENABLE`
* `RAW_ENABLE`
* `VIRTSER_ENABLE`

エンドポイントの使用率を向上させるために、HID 機能を組み合わせて1つのエンドポイントを使うようにすることができます。
デフォルトでは、`MOUSEKEY`、`EXTRAKEY` および `NKRO` が単一のエンドポイントに結合されます。

基本キーボード機能も、`KEYBOARD_SHARED_EP = yes` を設定することで同じエンドポイントに結合することができます。
これによりもう1つのエンドポイントが解放されますが、一部の BIOS ではブートキーボードプロトコルの切り替えを実装しないため、キーボードが動作しなくなるかもしれません。

マウスの結合も、ブートマウス互換性を破壊します。
この機能が必要な場合は、`MOUSE_SHARED_EP = no` を設定することで、マウスを結合しないようにすることができます。
