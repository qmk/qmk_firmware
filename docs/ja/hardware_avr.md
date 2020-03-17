# AVR マイコンを使ったキーボード

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: c9e3fa6f7:docs/hardware_avr.md
  git diff c9e3fa6f7 HEAD -- docs/hardware_avr.md | cat
-->

このページでは QMK における AVR マイコンのサポートについて説明します。AVR マイコンには、Atmel 社製の atmega32u4、atmega32u2、at90usb1286 やその他のマイコンを含みます。AVR マイコンは、簡単に動かせるよう設計された8ビットの MCU です。キーボードでよく使用される AVR マイコンには USB 機能や大きなキーボードマトリックスのためのたくさんの GPIO を搭載しています。これらは、現在、キーボードで使われる最も一般的な MCU です。

もし[キーボードガイドライン](ja/hardware_keyboard_guidelines.md)をまだ読んでいなければ、先に目を通すとあなたのキーボードを QMK に対応させる方法をさっと理解できるかもしれません。

## AVR を使用したキーボードを QMK に追加する

QMK は AVR を使ったキーボードを簡単に動かすための機能をいくつか実装しています。大体のキーボードでは1行もコードを書く必要がありません。まずはじめに、`util/new_keyboard.sh` スクリプトを実行します。

```
$ ./util/new_keyboard.sh
Generating a new QMK keyboard directory

Keyboard Name: mycoolkb
Keyboard Type [avr]: 
Your Name [John Smith]: 

Copying base template files... done
Copying avr template files... done
Renaming keyboard files... done
Replacing %KEYBOARD% with mycoolkb... done
Replacing %YOUR_NAME% with John Smith... done

Created a new keyboard called mycoolkb.

To start working on things, cd into keyboards/mycoolkb,
or open the directory in your favourite text editor.
```

これは新しいキーボードに必要なファイルを追加しデフォルトの設定を入力します。そして、あなたのキーボードに対応するためにカスタマイズする必要があります。

## `readme.md`

このファイルではキーボードに関する説明を記述します。[キーボード Readme テンプレート](ja/documentation_templates.md#keyboard-readmemd-template)に従って `readme.md` を記入して下さい。`readme.md` の冒頭に画像を載せる場合は、[Imgur](http://imgur.com) のような画像をホスティングするための外部サービスを利用して下さい。

## `<keyboard>.c`

このファイルではキーボード上で実行される全てのカスタマイズされたロジックを記述します。多くのキーボードの場合、何も書く必要はありません。
[機能のカスタマイズ](ja/custom_quantum_functions.md)で、カスタマイズされたロジックの記述方法を詳しく学ぶことが出来ます。

## `<keyboard>.h`

このファイルでは、[レイアウト](ja/feature_layouts.md)を定義します。最低限、以下のような `#define LAYOUT` を記述する必要があります。

```c
#define LAYOUT(          \
      k00, k01, k02,     \
      k10,   k11         \
) {                      \
    { k00, k01,   k02 }, \
    { k10, KC_NO, k11 }, \
}
```

`LAYOUT` マクロの前半部ではキーの物理的な配置を定義します。後半部ではスイッチが接続されるマトリックスを定義します。これによってマトリックス配線の順とは異なるキーを物理的に配置できます。

それぞれの `k__` 変数はユニークでなければいけません。通常は `k<row><col>` というフォーマットに従って記述されます。

物理マトリックス（後半部）では、`MATRIX_ROWS` に等しい行数が必要であり、各行には正確に `MATRIX_COLS` と等しい数の要素が含まれていなければいけません。物理キーが存在しない場合は、`KC_NO` を使用して空白を埋める事ができます。

## `config.h`

`config.h` ファイルには、ハードウェアや機能の設定を記述します。このファイルで設定できるオプションはたくさんありますが、ここで列挙にするには多すぎます。利用できるオプションの概要は[設定オプション](ja/config_options.md)を参照して下さい。

### ハードウェアの設定

`config.h` の先頭には USB に関する設定があります。これらは OS からキーボードがどのように表示されるか制御しています。変更する理由がない場合は、`VENDOR_ID` を `0xFEED` のままにしておく必要があります。`PRODUCT_ID` にはまだ使用されていない番号を選ばなければいけません。

`MANUFACTURER`、 `PRODUCT`、 `DESCRIPTION` をキーボードにあった設定に変更します。

```c
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    You
#define PRODUCT         my_awesome_keyboard
#define DESCRIPTION     A custom keyboard
```

?> Windows や macOS では、`MANUFACTURER` と `PRODUCT` が USBデバイスのリストに表示されます。Linux 上の `lsusb` では、代わりにデフォルトで [USB ID Repository](http://www.linux-usb.org/usb-ids.html) によって維持されているリストからこれらを取得します。`lsusb -v` を使用するとデバイスから示された値を表示します。また、接続したときのカーネルログにも表示されます。

### キーボードマトリックスの設定

`config.h` ファイルの次のセクションではキーボードのマトリックスを扱います。最初に設定するのはマトリックスのサイズです。これは通常、常にではありませんが、物理キー配置と同じ数の行・列になります。

```c
#define MATRIX_ROWS 2
#define MATRIX_COLS 3
```

マトリックスのサイズを定義したら、MCU のどのピンを行と列に接続するかを定義します。そのためにはピンの名前を指定するだけです。

```c
#define MATRIX_ROW_PINS { D0, D5 }
#define MATRIX_COL_PINS { F1, F0, B0 }
#define UNUSED_PINS
```


`MATRIX_ROW_PINS` の要素の数は `MATRIX_ROWS` に定義した数と同じでなければいけません。同様に `MATRIX_COL_PINS` の要素の数も `MATRIX_COLS` と等しい必要があります。`UNUSED_PINS` は定義しなくても問題ありませんがどのピンが空いているのか記録しておきたい場合は定義できます。

最後にダイオードの方向を定義します。これには `COL2ROW` か `ROW2COL` を設定します。

```c
#define DIODE_DIRECTION COL2ROW
```

#### ダイレクトピンマトリックス

各スイッチが、列と行のピンを共有する代わりに、それぞれ個別のピンとグランドに接続されているキーボードを定義するには、`DIRECT_PINS` を使用します。マッピング定義では、列と行の各スイッチのピンを左から右の順に定義します。`MATRIX_ROWS` と `MATRIX_COLS` 内のサイズに準拠する必要があり、空白を埋めるには `NO_PIN` を使用します。これによって `DIODE_DIRECTION`、`MATRIX_ROW_PINS`、`MATRIX_COL_PINS` の動作を上書きします。

```c
// #define MATRIX_ROW_PINS { D0, D5 }
// #define MATRIX_COL_PINS { F1, F0, B0 }
#define DIRECT_PINS { \
    { F1, E6, B0, B2, B3 }, \
    { F5, F0, B1, B7, D2 }, \
    { F6, F7, C7, D5, D3 }, \
    { B5, C6, B6, NO_PIN, NO_PIN } \
}
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
//#define DIODE_DIRECTION
```

### バックライトの設定

QMK では GPIO ピンでのバックライト制御をサポートしています。これらの設定を選択して MCU から制御できます。詳しくは[バックライト](ja/feature_backlight.md)を参照して下さい。

```c
#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6
```

### その他の設定オプション

`config.h` で設定・調整できる機能はたくさんあります。詳しくは[設定オプション](ja/config_options.md)を参照して下さい。

## `rules.mk`

`rules.mk` ファイルを使用して、ビルドするファイルや有効にする機能をQMKへ指示します。atmega32u4 を使っている場合、これらのオプションはデフォルトのままにしておくことが出来ます。他の MCU を使用している場合はいくつかのパラメータを調整する必要があります。

### MCU オプション

このオプションではビルドする CPU をビルドシステムに指示します。これらの設定を変更する場合は非常に注意して下さい。キーボードを操作不能にしてしまう可能性があります。

```make
MCU = atmega32u4
F_CPU = 16000000
ARCH = AVR8
F_USB = $(F_CPU)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT
```

### ブートローダー

ブートローダーは MCU に保存されているプログラムをアップグレードするための特別なセクションです。キーボードのレスキューパーティションのようなものだと考えて下さい。

#### Teensy Bootloader の例

```make
BOOTLOADER = halfkay
```

#### Atmel DFU Loader の例

```make
BOOTLOADER = atmel-dfu
```

#### Pro Micro Bootloader の例

```make
BOOTLOADER = caterina
```

### ビルドオプション

`rules.mk` にはオン・オフできるたくさんの機能があります。詳細なリストと説明は[設定オプション](ja/config_options.md#feature-options)を参照して下さい。
