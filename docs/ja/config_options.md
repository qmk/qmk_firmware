# QMKの設定

QMKはほぼ無制限に設定可能です。Wherever possible we err on the side of allowing users to customize their keyboard, even at the expense of code size. ただし、この柔軟性のレベルにより設定が困難になります。

QMKには2つの主な設定ファイルの種類があります- `config.h` と `rules.mk`。これらのファイルはQMKの様々なレベルに存在し、同じ種類の全てのファイルは最終的な設定を構築するために組み合わされます。最低の優先度から最高の優先度までのレベルは以下の通りです:

* QMK デフォルト
* キーボード
* フォルダ (最大5レべルの深さ)
* キーマップ

## QMK デフォルト

QMKでの全ての利用可能な設定はデフォルトを持ちます。設定がキーボード、フォルダ、あるいはキーマップレべルで設定されない場合、これが使用される設定です。

## キーボード

このレベルはキーボード全体に適用されるべき設定オプションを含みます。一部の設定は、リビジョンあるいはほとんどのキーマップで変更されません。他の設定はこのキーボードのデフォルトに過ぎず、フォルダ および/あるいは キーマップによって上書きされる可能性があります。

## フォルダ

一部のキーボードは、異なるハードウェア構成のためのフォルダとサブフォルダを持ちます。ほとんどのキーボードは深さ1のフォルダのみですが、QMKは最大深さ5のフォルダの構造をサポートします。各フォルダは、最終的な設定に組み込まれる独自の `config.h` と `rules.mk` ファイルを持つことができます。

## キーマップ

このレベルは特定のキーマップのための全てのオプションを含みます。以前の宣言を上書きしたい場合は、定義を解除するために`#undef <variable>`を使うことができます。エラー無しで再定義することができます。

# `config.h` ファイル

これは最初に含まれるものの1つであるCヘッダ ファイルで、プロジェクト全体(含まれる場合)にわたって持続します。多くの変数をここで設定し、他の場所からアクセスすることができます。The `config.h` file shouldn't be including other `config.h` files, or anything besides this:

    #include "config_common.h"


## ハードウェア オプション
* `#define VENDOR_ID 0x1234`
   * VIDを定義します。ほとんどのDIYプロジェクトでは、なんでも好きなものにできます
* `#define PRODUCT_ID 0x5678`
   * PIDを定義します。ほとんどのDIYプロジェクトでは、なんでも好きなものにできます
* `#define DEVICE_VER 0`
   * デバイスのバージョンを定義します (多くの場合リビジョンに使われます)
* `#define MANUFACTURER Me`
   * 一般的に、誰/どのブランドがボードを作成したか
* `#define PRODUCT Board`
   * キーボードの名前
* `#define DESCRIPTION a keyboard`
   * キーボードの簡単な説明
* `#define MATRIX_ROWS 5`
   * キーボードのマトリックスの行の数
* `#define MATRIX_COLS 15`
   * キーボードのマトリックスの列の数
* `#define MATRIX_ROW_PINS { D0, D5, B5, B6 }`
   * 上から下への行のピン
* `#define MATRIX_COL_PINS { F1, F0, B0, C7, F4, F5, F6, F7, D4, D6, B4, D7 }`
   * 左から右への列のピン
* `#define UNUSED_PINS { D1, D2, D3, B1, B2, B3 }`
   * 参照のために、キーボードで使われていないピン
* `#define MATRIX_HAS_GHOST`
   * define is matrix has ghost (unlikely)
* `#define DIODE_DIRECTION COL2ROW`
   * COL2ROW あるいは ROW2COL - マトリックスがどのように設定されているかCOL2ROW は、ダイオードの黒い印が行に向かっていて、スイッチと行の間にあることを意味します。
* `#define DIRECT_PINS { { F1, F0, B0, C7 }, { F4, F5, F6, F7 } }`
   * 行と列にマップされているピンを左から右に。各スイッチが個別のピンとグラウンドに接続されているマトリックスを定義します。
* `#define AUDIO_VOICES`
   * turns on the alternate audio voices (to cycle through)
* `#define C4_AUDIO`
   * pin C4のオーディオを有効にします
* `#define C5_AUDIO`
   * pin C5のオーディオを有効にします
* `#define C6_AUDIO`
   * pin C6のオーディオを有効にします
* `#define B5_AUDIO`
   * pin B5のオーディオを有効にします (C[4-6]\_AUDIO の1つとともに B[5-7]\_AUDIO の1つが有効にされている場合、duophonyが有効にされます)
* `#define B6_AUDIO`
   * pin B6のオーディオを有効にします (C[4-6]\_AUDIO の1つとともに B[5-7]\_AUDIO の1つが有効にされている場合、duophonyが有効にされます)
* `#define B7_AUDIO`
   * pin B7のオーディオを有効にします (C[4-6]\_AUDIO の1つとともに B[5-7]\_AUDIO の1つが有効にされている場合、duophonyが有効にされます)
* `#define BACKLIGHT_PIN B7`
   * バックライトのpin
* `#define BACKLIGHT_LEVELS 3`
   * バックライトのレベル数 (offを除いて最大15)
* `#define BACKLIGHT_BREATHING`
   * バックライトのブレスを有効にします
* `#define BREATHING_PERIOD 6`
   * 1つのバックライトの "ブレス" の長さの秒数
* `#define DEBOUNCE 5`
   * pinの値を読み取る時の遅延 (5がデフォルト)
* `#define LOCKING_SUPPORT_ENABLE`
   * メカニカル ロックのサポートキーマップでは代わりに KC_LCAP, KC_LNUM あるいは KC_LSCR を使います
* `#define LOCKING_RESYNC_ENABLE`
   * キーボードのLEDの状態をスイッチの状態と一貫させ続けようとします
* `#define IS_COMMAND() (get_mods() == MOD_MASK_SHIFT)`
   * マジック コマンドの使用を許可するキーの組み合わせ (デバッグに便利です)
* `#define USB_MAX_POWER_CONSUMPTION 500`
   * デバイスのためのUSB経由の最大電力(mA) を設定します (デフォルト: 500)
* `#define USB_POLLING_INTERVAL_MS 10`
   * キーボード、マウス および 共有 (NKRO/メディア キー) インタフェースのためのUSBポーリング レートのミリ秒を設定します
* `#define F_SCL 100000L`
   * I2Cを使用するキーボードのためのI2Cクロックレート速度を設定しますデフォルトは `400000L`です。ただし、デフォルトが`100000L`である `split_common` を使っているキーボードを除きます。

## 無効にできる機能

これらのオプションを定義すると、関連する機能が無効になり、コードサイズを節約できます。

* `#define NO_DEBUG`
   * デバッグを無効にします
* `#define NO_PRINT`
   * hid_listenを使った出力/デバッグを無効にします
* `#define NO_ACTION_LAYER`
   * レイヤーを無効にします
* `#define NO_ACTION_TAPPING`
   * タップダンスと他のタッピング機能を無効にします
* `#define NO_ACTION_ONESHOT`
   * ワンショット モディファイアを無効にします
* `#define NO_ACTION_MACRO`
   * 古い形式のマクロ処理を無効にします: MACRO() & action_get_macro
* `#define NO_ACTION_FUNCTION`
   * fn_actions 配列からのaction_function()の呼び出しを無効にします (非推奨)

## 有効にできる機能

これらのオプションを定義すると、関連する機能が有効になり、コードサイズが大きくなるかもしれません。

* `#define FORCE_NKRO`
   * NKROはデフォルトでオンにする必要があります。これによりEEPROMの設定に関係なく、キーボードの起動時に強制的にオンになります。NKRO は引き続きオフにできますが、キーボードを再起動すると再びオンになります。
* `#define STRICT_LAYER_RELEASE`
   * キーリリースがどのレイヤーから来たのかを覚えるのではなく、現在のレイヤー スタックを使って強制的に評価されるようにします (高度なケースに使われます)

## 設定可能な挙動

* `#define TAPPING_TERM 200`
   * タップがホールドになるまでの時間。500以上に設定された場合、タップ期間中にタップされたキーもホールドになります
* `#define TAPPING_TERM_PER_KEY`
   * キーごとの `TAPPING_TERM` 設定の処理を有効にします
* `#define RETRO_TAPPING`
   * 押しと離しの間に他のキーの中断がなければ、TAPPING_TERMの後であってもとにかくタップします
   * 詳細は[Retro Tapping](feature_advanced_keycodes.md#retro-tapping)を見てください
* `#define TAPPING_TOGGLE 2`
   * トグルを引き起こす前のタップ数
* `#define PERMISSIVE_HOLD`
   * `TAPPING_TERM`にヒットしていなくても、リリースする前に別のキーが押されると、タップ アンド フォールド キーがホールドを引き起こします
   * 詳細は[Permissive Hold](feature_advanced_keycodes.md#permissive-hold)を見てください
* `#define IGNORE_MOD_TAP_INTERRUPT`
   * 両方のキーに`TAPPING_TERM`を適用することで、ホールド時に他のキーに変換するキーを使ってローリング コンボ (zx) をすることができるようにします
   * 詳細は[Mod tap interrupt](feature_advanced_keycodes.md#ignore-mod-tap-interrupt)を見てください
* `#define TAPPING_FORCE_HOLD`
   * タップされた直後に、dual roleキーを修飾子として使用できるようにします
   * [Hold after tap](feature_advanced_keycodes.md#tapping-force-hold)を見てください
   * タップ トグル機能を無効にします (`TT` あるいは One Shot Tap Toggle)
* `#define LEADER_TIMEOUT 300`
   * リーダー キーがタイムアウトするまでの時間
      * タイムアウトする前にシーケンスを終了できない場合は、タイムアウトの設定を増やす必要があるかもしれません。あるいは、`LEADER_PER_KEY_TIMING` オプションを有効にしたいかもしれません。これは各キーがタップされた後でタイムアウトを再設定します。
* `#define LEADER_PER_KEY_TIMING`
   * 全体では無く各キーを押すたびに実行されるリーダー キー chord のタイマーを設定します
* `#define LEADER_KEY_STRICT_KEY_PROCESSING`
   * Mod-Tap および Layer-Tap キーコードのためのキーコード フィルタリングを無効にします例えば、これを有効にすると、`KC_A`を使いたい場合は`MT(MOD_CTL, KC_A)`を指定する必要があります。
* `#define ONESHOT_TIMEOUT 300`
   * ワンショットがタイムアウトするまでの時間
* `#define ONESHOT_TAP_TOGGLE 2`
   * ワンショット トグルが引き起こされるまでのタップ数
* `#define QMK_KEYS_PER_SCAN 4`
   * 走査ごとに1つ以上のキーを送信できます。デフォルトでは、走査ごとに`process_record()`経由で1つのキーイベントのみが送信されます。これはほとんどのタイピングにほとんど影響しませんが、多くの chord をしているか、走査レートが最初から遅い場合、キーイベントの処理に多少の遅延を入れることができます。それぞれのプレスとリリースは別のイベントです。For a keyboard with 1ms or so scan times, even a very fast typist isn't
going to produce the 500 keystrokes a second needed to actually get more than a
few ms of delay from this. But if you're doing chording on something with 3-4ms
scan times?おそらくこれが必要です。
* `#define COMBO_COUNT 2`
   * [Combo](feature_combo.md) 機能で使っているコンボの数にこれを設定します。
* `#define COMBO_TERM 200`
   * コンボ キーが検出されるまでの時間。定義されていない場合は、デフォルトは`TAPPING_TERM` です。
* `#define TAP_CODE_DELAY 100`
   * 適切に登録するのに問題がある場合(VUSBボードで珍しくない)、`register_code` と `unregister_code` の間の遅延を設定します。値はミリ秒です。
* `#define TAP_HOLD_CAPS_DELAY 80`
   * MacOSで特別な処理が行われるため、`KC_CAPSLOCK`を使う時にタップ フォールド キー (`LT`, `MT`) に遅延を設定します。この値はミリ秒で、定義されていない場合はデフォルトは80msです。macOSについては、これを200以上に設定したいかもしれません。

## RGB ライト設定

* `#define RGB_DI_PIN D7`
   * pin the DI on the WS2812 is hooked-up to
* `#define RGBLIGHT_ANIMATIONS`
   * RGBアニメーションを実行します
* `#define RGBLED_NUM 12`
   * LEDの数
* `#define RGBLIGHT_SPLIT`
   * Needed if both halves of the board have RGB LEDs wired directly to the RGB output pin on the controllers instead of passing the output of the left half to the input of the right half
* `#define RGBLED_SPLIT { 6, 6 }`
   * 分割キーボードの各半分の`RGB_DI_PIN`に直接配線されている接続されているLEDの数
   * 最初の値は左半分のLEDの数を示し、2番目の値は右半分です。
   * RGBLED_SPLIT が定義されている場合、RGBLIGHT_SPLIT は暗黙的に定義されます。
* `#define RGBLIGHT_HUE_STEP 12`
   * 色相の増減時のステップ単位
* `#define RGBLIGHT_SAT_STEP 25`
   * 彩度の増減時のステップ単位
* `#define RGBLIGHT_VAL_STEP 12`
   * 値の増減時のステップ単位 (明度)
* `#define RGBW_BB_TWI`
   * bit-bangs TWI to EZ RGBW LEDs (only required for Ergodox EZ)

## マウス キー オプション

* `#define MOUSEKEY_INTERVAL 20`
* `#define MOUSEKEY_DELAY 0`
* `#define MOUSEKEY_TIME_TO_MAX 60`
* `#define MOUSEKEY_MAX_SPEED 7`
* `#define MOUSEKEY_WHEEL_DELAY 0`

## 分割キーボード オプション

分割キーボード固有のオプション。rules.mkの中で 'SPLIT_KEYBOARD = yes' であることを確認します

* `SPLIT_TRANSPORT = custom`
   * 標準の分割通信ルーチンをカスタムのものに置き換えることができます。現在、ARMベースの分割キーボードはこれを使わなければなりません。

### 利き手の設定

一つ覚えておかなければならないことは、USBポートが接続されている側が常にマスター側であるということです。USBに接続されていない側はスレーブです。

分割キーボードの利き手を設定するには、幾つかの異なる方法があります (優先度の順にリストされています):

1. `SPLIT_HAND_PIN` を設定します: 利き手を決定するためにpinを読み込みます。pinがhighの場合、それが左側です。lowであれば、その半分側が右側であると決定されます。
2. `EE_HANDS` を設定し、各半分に`eeprom-lefthand.eep`/`eeprom-righthand.eep`をフラッシュします
   * DFUブートローダを搭載したボードでは、これらのEEPROMファイルをフラッシュするために`:dfu-split-left`/`:dfu-split-right`を使うことができます
   * Caterina ブートローダを搭載したボード (標準的な Pro Microsなど)では、`:avrdude-split-left`/`:avrdude-split-right` を使ってください
   * ARM DFU ブートローダを搭載したボード (Proton C など)では、`:dfu-util-split-left`/`:dfu-util-split-right` を使ってください
3. `MASTER_RIGHT`を設定します: USBポートに差し込まれた半分はマスターで右側であると決定されます(デフォルトの逆)
4. デフォルト: USBポートに差し込まれている側がマスターの半分であり、左半分であると見なされます。スレーブ側は右半分です

#### 利き手を定義します

* `#define SPLIT_HAND_PIN B7`
   * high/low ピンを使って利き手を決定します。low = 右手、high = 左手。`B7`を使っているピンと置き換えます。これはオプションで、`SPLIT_HAND_PIN` が未定義のままである場合、EE_HANDS メソッドまたは標準のLet'sが使っている MASTER_LEFT / MASTER_RIGHT 定義をまだ使うことができます。

* `#define EE_HANDS` (`SPLIT_HAND_PIN`が定義されていない場合のみ動作します)
   * `eeprom-lefthand.eep`/`eeprom-righthand.eep` がそれぞれの半分にフラッシュされた後で、EEPROM内に格納されている利き手の値を読み込みます。

* `#define MASTER_RIGHT`
   * マスターの半分が右半分と定義されます。

### 他のオプション

* `#define USE_I2C`
   * Serialの代わりにI2Cを使う場合 (デフォルトはserial)

* `#define SOFT_SERIAL_PIN D0`
   * serialを使う場合、これを定義します。`D0` あるいは `D1`,`D2`,`D3`,`E6`。

* `#define MATRIX_ROW_PINS_RIGHT { <row pins> }`
* `#define MATRIX_COL_PINS_RIGHT { <col pins> }`
   * 右半分に左半分と異なるピン配置を指定したい場合は、`MATRIX_ROW_PINS_RIGHT`/`MATRIX_COL_PINS_RIGHT` を定義することができます。現在のところ、`MATRIX_ROW_PINS` のサイズは`MATRIX_ROW_PINS_RIGHT`と同じでなければならず、列の定義も同様です。

* `#define DIRECT_PINS_RIGHT { { F1, F0, B0, C7 }, { F4, F5, F6, F7 } }`
   * 右半分に左半分と異なる直接ピン配置を指定したい場合は、`DIRECT_PINS_RIGHT`を定義することができます。現在のところ、`DIRECT_PINS` のサイズは`DIRECT_PINS_RIGHT`と同じでなければなりません。

* `#define RGBLED_SPLIT { 6, 6 }`
   * [RGB ライト設定](#rgb-light-configuration)を見てください。

* `#define SELECT_SOFT_SERIAL_SPEED <speed>` (デフォルトの速度は1です)
   * serial通信を使う時のプロトコルの速度を設定します。
   * 速度:
      * 0: about 189kbps (Experimental only)
      * 1: about 137kbps (default)
      * 2: about 75kbps
      * 3: about 39kbps
      * 4: about 26kbps
      * 5: about 20kbps

* `#define SPLIT_USB_DETECT`
   * マスタ/スレーブを委任する時に(タイムアウト付きで)USB接続を検出します
   * ARMについてはデフォルトの挙動
   * AVR Teensyについては必須

* `#define SPLIT_USB_TIMEOUT 2500`
   * `SPLIT_USB_DETECT`を使う時のマスタ/スレーブを検出する場合の最大タイムアウト

# `rules.mk` ファイル

これは、トップレベルの`Makefile`に含まれる[make](https://www.gnu.org/software/make/manual/make.html) ファイルです。これは特定の機能を有効または無効にするだけでなく、コンパイルするMCUに関する情報を設定するために使われます。

## ビルド オプション

* `DEFAULT_FOLDER`
   * キーボードが1つ以上のサブフォルダを持つ場合にデフォルトのフォルダを指定するために使われます。
* `FIRMWARE_FORMAT`
   * ビルドの後でルート`qmk_firmware` フォルダにコピーされる形式 (bin, hex) を定義します。
* `SRC`
   * コンパイル/リンク リストにファイルを追加するために使われます。
* `LAYOUTS`
   * このキーボードがサポートする[レイアウト](feature_layouts.md)のリスト

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

## 機能オプション

これらを使って特定の機能のビルドを有効または無効にします。有効にすればするほどファームウェアが大きくなり、MCUには大きすぎるファームウェアを構築するリスクがあります。

* `BOOTMAGIC_ENABLE`
   * 仮想 DIP スイッチ設定
* `MOUSEKEY_ENABLE`
   * マウス キー
* `EXTRAKEY_ENABLE`
   * オーディオ制御とシステム制御
* `CONSOLE_ENABLE`
   * デバッグ用コンソール
* `COMMAND_ENABLE`
   * デバッグ及び設定用のコマンド
* `COMBO_ENABLE`
   * キー コンボ 機能
* `NKRO_ENABLE`
   * USB N-キー ロールオーバー - これが動作しない場合は、ここを見てください: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
* `AUDIO_ENABLE`
   * オーディオ サブシステムを有効にします。
* `RGBLIGHT_ENABLE`
   * キーボード アンダーライト機能を有効にします
* `LEADER_ENABLE`
   * リーダー キー chordingを有効にします
* `MIDI_ENABLE`
   * MIDI 制御
* `UNICODE_ENABLE`
   * Unicode
* `BLUETOOTH_ENABLE`
   * Adafruit EZ-Key HID でBluetoothを有効にするレガシー オプション。BLUETOOTH を見てください
* `BLUETOOTH`
   * 現在のオプションは、AdafruitEzKey, AdafruitBLE, RN42
* `SPLIT_KEYBOARD`
   * 分割キーボード (let's split や bakingpy's boardsのようなデュアルMCU) のサポートを有効にし、quantum/split_common にある全ての必要なファイルをインクルードします
* `CUSTOM_MATRIX`
   * 標準マトリックス走査ルーチンを独自のものに置き換えることができます。
* `DEBOUNCE_TYPE`
   * 標準キー デバウンス ルーチンを代替または独自のものに置き換えることができます。
* `WAIT_FOR_USB`
   * キーボードが起動する前に、USB接続が確立されるのをキーボードに待機させます
* `NO_USB_STARTUP_CHECK`
   * キーボードの起動後のusbサスペンドチェックを無効にします。通常、キーボードはタスクが実行される前にホストがウェイク アップするのを待ちます。分割キーボードは半分はウェイクアップコールを取得できませんが、マスタにコマンドを送信する必要があるため、役に立ちます。
* `LINK_TIME_OPTIMIZATION_ENABLE`
= Enables Link Time Optimization (`LTO`) when compiling the keyboard.  これは処理に時間が掛かりますが、コンパイルされたサイズを大幅に減らします (そして、ファームウェアが小さいため、追加の時間は分からないくらいです)。ただし、`LTO`が有効な場合、これらの機能が壊れるため、これは自動的に古いマクロと関数の機能を無効にします。これは`NO_ACTION_MACRO` と `NO_ACTION_FUNCTION` を自動的に定義することで行われます

## USB エンドポイントの制限

USB経由でサービスを提供するために、QMKはUSBエンドポイントを使う必要があります。
これらは有限なリソースです: 各マイクロコントローラは特定の数しか持ちません。
これは一緒に有効にできる機能を制限します。
利用可能なエンドポイントを超えると、ビルド エラーが投げられます。

以下の機能は個別のエンドポイントを必要とするかもしれません:

* `MOUSEKEY_ENABLE`
* `EXTRAKEY_ENABLE`
* `CONSOLE_ENABLE`
* `NKRO_ENABLE`
* `MIDI_ENABLE`
* `RAW_ENABLE`
* `VIRTSER_ENABLE`

エンドポイントの使用率を向上させるために、HID機能を組み合わせて1つのエンドポイントを使うようにすることができます。
デフォルトでは、`MOUSEKEY`, `EXTRAKEY` および `NKRO` が単一のエンドポイントに結合されます。

基本キーボード機能も、`KEYBOARD_SHARED_EP = yes`を設定することでエンドポイントに結合することができます。
これによりもう1つのエンドポイントが解放されますが、一部のBIOSではブート キーボード プロトコル切り替えを実装しないため、キーボードが動作しなくなるかもしれません。

マウスの結合も、ブート マウス互換性を破壊します。
この機能が必要な場合は、`MOUSE_SHARED_EP = no` を設定することで、マウスを結合解除することができます。
