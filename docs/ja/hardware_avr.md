# AVRマイコンを使ったキーボード

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: c9e3fa6f7:docs/hardware_avr.md
  git diff c9e3fa6f7 HEAD -- docs/hardware_avr.md | cat
-->

このページではQMKにおけるAVRマイコンのサポートについて説明します。AVRマイコンには、Atmel社製のatmega32u4, atmega32u2, at90usb1286やその他のマイコンを含みます。AVRマイコンは8ビットのMCUで簡単に動かせるよう設計されています。キーボードでよく使用されるAVRマイコンにはUSB機能や大きなキーボードマトリクスのためのたくさんのGPIOを搭載しています。現在、キーボード用のMCUとして最も一般的に使われています。

もし[キーボードガイドライン](hardware_keyboard_guidelines.md)をまだ読んでいなければ、先に目を通しておけばキーボードをQMKに対応させる方法をさっと理解できるかもしれません。

## AVRを使用したキーボードをQMKに追加する

QMKはAVRを使ったキーボードを簡単に動かすための機能をいくつか実装しています。大体のキーボードでは1行もコードを書く必要がありません。はじめに、`util/new_keyboard.sh`を実行します。

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

これは新しいキーボードに必要なファイルを追加し、デフォルトの設定を入力します。そして、あなたのキーボードに対応するためにカスタマイズする必要があります。

## `readme.md`

このファイルではあなたのキーボードに関する説明を記述します。[キーボード Readme テンプレート](documentation_templates.md#keyboard-readmemd-template)に従って、 `readme.md`を記入して下さい。`readme.md`に画像を載せる場合は、画像をホスティングするための外部サービス、[Imgur](http://imgur.com)などを利用して下さい。

## `<keyboard>.c`

このファイルではあなたのキーボード上で実行される全てのカスタマイズされたロジックを記述します。多くのキーボードの場合、何も書く必要はありません。
[機能のカスタマイズ](custom_quantum_functions.md)で、カスタマイズされたロジックの記述方法を詳しく学ぶことが出来ます。

## `<keyboard>.h`

このファイルでは、[レイアウト](feature_layouts.md)を定義します。最低限、以下のような`#define LAYOUT`を記述する必要があります。

```c
#define LAYOUT(          \
      k00, k01, k02,     \
      k10,   k11         \
) {                      \
    { k00, k01,   k02 }, \
    { k10, KC_NO, k11 }, \
}
```

`LAYOUT`マクロの前半部ではキーの物理的な配置を定義します。後半ではスイッチが接続されるマトリクスを定義します。これによってマトリクス配線の順とは異なるキーを物理的に配置できます。

それぞれの`k__`変数はユニークでなければいけません。通常は`k<row><col>`というフォーマットに従って記述されます。

物理マトリクス（後半部）では、`MATRIX_ROWS`に等しい行数が必要であり、各行には正確な数の`MATRIX_COLS`要素が含まれていなければいけません。物理キーが存在しない場合は、`KC_NO`を使用して空白を埋める事ができます。

## `config.h`

`config.h`には、ハードウェアや機能の設定を記述します。このファイルで設定できるオプションはたくさんありますが、ここでリストにするには多すぎます。利用できるオプションの概要は[設定オプション](config_options.md)を参照して下さい。

### ハードウェアの設定

`config.h`の先頭にはUSBに関する設定があります。これらはOSからキーボードがどのように表示されるか制御しています。変更する理由がない場合は、`VENDOR_ID`を`0xFEED`のままにしておく必要があります。`PRODUCT_ID`にはまだ使用されていない番号を選ばなければいけません。

`MANUFACTURER`, `PRODUCT`, `DESCRIPTION`をキーボードにあった設定に変更します。

```c
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    You
#define PRODUCT         my_awesome_keyboard
#define DESCRIPTION     A custom keyboard
```

?> WindowsやmacOSでは、`MANUFACTURER`と`PRODUCT`がUSBデバイスのリストに表示されます。Linux上の`lsusb`では、代わりにデフォルトで[USB ID Repository](http://www.linux-usb.org/usb-ids.html)によって維持されているリストからこれらを取得します。`lsusb -v`を使用するとデバイスから示された値を表示します。また、接続したカーネルログにも表示されます。

### キーボードマトリクスの設定

`config.h`の次のセクションではキーボードのマトリクスを扱います。最初に設定するのはマトリクスのサイズです。これは通常、常にではありませんが、物理キー配置と同じ数の行・列になります。

```c
#define MATRIX_ROWS 2
#define MATRIX_COLS 3
```

マトリクスのサイズを定義したら、MCUのどのピンを行と列に接続するかを定義します。そのためにはこれらのピンの名前を指定するだけです。

```c
#define MATRIX_ROW_PINS { D0, D5 }
#define MATRIX_COL_PINS { F1, F0, B0 }
#define UNUSED_PINS
```


`MATRIX_ROW_PINS`の要素の数は`MATRIX_ROWS`に定義した数と同じでなければいけません。同様に`MATRIX_COL_PINS`の要素の数も`MATRIX_COLS`と等しい必要があります。`UNUSED_PINS`を定義する必要はありませんが、どのピンが空いているのか記録しておきたい場合はできます。

最後にダイオードの方向を定義します。これには`COL2ROW`か`ROW2COL`を設定します。

```c
#define DIODE_DIRECTION COL2ROW
```

#### ダイレクトピンマトリクス

各スイッチで列と行を共有する代わりに、それぞれ個別のピンとグランドに接続されているキーボードを定義するには、`DIRECT_PINS`を使用します。マッピング定義では列と行で左から右に定義します。`MATRIX_ROWS`と`MATRIX_COLS`内のサイズに準拠する必要があり、空白を埋めるには`NO_PIN`を使用します。`DIODE_DIRECTION`,　`MATRIX_ROW_PINS`と`MATRIX_COL_PINS`の動作を上書きします。

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

QMKではGPIOピンでのバックライト制御をサポートしています。これらの設定を選択してMCUから制御できます。詳しくは[バックライト](feature_backlight.md)を参照して下さい。

```c
#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6
```

### その他の設定オプション

`config.h`で設定・調整できる機能はたくさんあります。詳しくは[設定オプション](config_options.md)を参照して下さい。

## `rules.mk`

`rules.mk`を使用して、ビルドするファイルや有効にする機能をQMKへ指示します。atmega32u4を使っている場合、これらのオプションはデフォルトのままにしておくことが出来ます。他のMCUを使用している場合はいくつかのパラメータを調整する必要があります。

### MCUオプション

このオプションではビルドするCPUをビルドシステムに指示します。これらの設定を変更する場合は非常に注意して下さい。キーボードを操作不能にしてしまう可能性があります。

```make
MCU = atmega32u4
F_CPU = 16000000
ARCH = AVR8
F_USB = $(F_CPU)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT
```

### ブートローダー

ブートローダーはMCUに保存されているプログラムをアップグレードするための特別なセクションです。キーボードのレスキューパーティションのようなものだと考えて下さい。

#### Teensy Bootloaderの例

```make
BOOTLOADER = halfkay
```

#### Atmel DFU Loaderの例

```make
BOOTLOADER = atmel-dfu
```

#### Pro Micro Bootloaderの例

```make
BOOTLOADER = caterina
```

### ビルドオプション

`rules.mk`にはオン・オフできるたくさんの機能があります。詳細なリストと説明は[設定オプション](config_options.md#feature-options)を参照して下さい。
