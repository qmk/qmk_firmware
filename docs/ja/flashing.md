# 書き込みの手順とブートローダ情報

<!---
  original document: 0.8.62:docs/flashing.md
  git diff 0.8.62 HEAD -- docs/flashing.md | cat
-->

キーボードが使用するブートローダにはかなり多くの種類があり、ほぼ全てが異なる書き込みの方法を使います。幸いなことに、[QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) のようなプロジェクトは、あまり深く考える必要無しに様々なタイプと互換性を持つことを目指していますが、この文章では様々なタイプのブートローダとそれらを書き込むために利用可能な方法について説明します。

`rules.mk` の `BOOTLOADER` 変数で選択されたブートローダがある場合、QMK は .hex ファイルがデバイスに書き込むのに適切なサイズかどうかを自動的に計算し、合計サイズをバイト単位で(最大値とともに)出力します。

## DFU

Atmel の DFU ブートローダはデフォルトで全ての atmega32u4 チップに搭載されており、PCB (旧 OLKB キーボード、Clueboard) に独自の IC を持つ多くのキーボードで使われています。一部のキーボードは、LUFA の DFU ブートローダ(または QMK のフォーク) (新しい OLKB キーボード)を使う場合もあり、そのハードウェアに固有の追加機能が追加されます。

DFU ブートローダとの互換性を確保するために、以下のブロックが `rules.mk` にあることを確認してください(オプションとして代わりに `lufa-dfu` や `qmk-dfu` が使えます):

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu
```

互換性のあるフラッシャ:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (推奨の GUI)
* QMK の [dfu-programmer](https://github.com/dfu-programmer/dfu-programmer) / `:dfu` (推奨のコマンドライン)
* [Atmel の Flip](http://www.microchip.com/developmenttools/productdetails.aspx?partno=flip) (非推奨)

書き込み手順:

1. `RESET` キーコードを押すか、RESET ボタンをタップします(または RST を GND にショートします)。
2. OS がデバイスを検知するのを待ちます。
3. メモリを消去します(自動的に実行されるかもしれません)
4. .hex ファイルを書き込みます
5. デバイスをアプリケーションモードにリセットします(自動的に実行されるかもしれません)

あるいは:

    make <keyboard>:<keymap>:dfu

### QMK DFU

QMK には LUFA DFU ブートローダのフォークがあり、ブートローダを終了してアプリケーションに戻る時に単純なマトリックススキャンを行うことができます。また、何かが起きた時に、LED を点滅したり、スピーカーでカチカチ音をたてたりします。これらの機能を有効にするには、`config.h` で以下のブロックを有効にします (ブートローダを終了するキーは、ここで定義された INPUT と OUTPUT に接続する必要があります):

    #define QMK_ESC_OUTPUT F1 // 通常 COL
    #define QMK_ESC_INPUT D5 // 通常 ROW
    #define QMK_LED E6
    #define QMK_SPEAKER C6

製造元と製品名は `config.h` から自動的に取得され、製品に「Bootloader」が追加されます。

このブートローダを生成するには、`bootloader` ターゲット、例えば `make planck/rev4:default:bootloader` を使います。

実稼働対応の .hex ファイル(アプリケーションおよびブートローダを含む)を生成するには、`production` ターゲット、例えば `make planck/rev4:default:production` を使います。

### DFU コマンド

ファームウェアを DFU デバイスに書き込むために使用できる DFU コマンドがいくつかあります。

* `:dfu` - これが通常のオプションで、DFU デバイスが使用可能になるまで待機したのちファームウェアを書き込みます。5秒ごとに、DFU デバイスが存在するかチェックしています。
* `:dfu-ee` - 通常の hex ファイルの代わりに `eep` ファイルを書き込みます。これを使用するのはまれです。
* `:dfu-split-left` - デフォルトオプション (`:dfu`) と同様に、通常のファームウェアが書き込まれます。ただし、分割キーボードの「左側の」 EEPROM ファイルも書き込まれます。_これは、Elite C ベースの分割キーボードに最適です。_
* `:dfu-split-right` - デフォルトオプション (`:dfu`) と同様に、通常のファームウェアが書き込まれます。ただし、分割キーボードの「右側の」 EEPROM ファイルも書き込まれます。_これは、Elite C ベースの分割キーボードに最適です。_

## Caterina

Arduino ボードとそのクローンは [Caterina ブートローダ](https://github.com/arduino/ArduinoCore-avr/tree/master/bootloaders/caterina) (Pro Micro またはそのクローンで構築されたキーボード)を使用し、avr109 プロトコルを使って仮想シリアルを介して通信します。[A-Star](https://www.pololu.com/docs/0J61/9) のようなブートローダは Caterina に基づいています。

Caterina ブートローダとの互換性を確保するために、以下のブロックが `rules.mk` にあることを確認してください:

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina
```

互換性のあるフラッシャ:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (推奨の GUI)
* avr109 を使った [avrdude](http://www.nongnu.org/avrdude/) / `:avrdude` (推奨のコマンドライン)
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)

書き込み手順:

1. `RESET` キーコードを押すか、RST をすばやく GND にショートします (入力後7秒で書き込みます)
2. OS がデバイスを検知するのを待ちます。
3. .hex ファイルを書き込みます
4. デバイスが自動的にリセットされるのを待ちます

あるいは

    make <keyboard>:<keymap>:avrdude


### Caterina コマンド

ファームウェアを DFU デバイスに書き込むために使用できる DFU コマンドがいくつかあります。

* `:avrdude` - これが通常のオプションで、Caterina デバイスが(新しい COM ポートを検出して)使用可能になるまで待機し、ファームウェアを書き込みます。
* `:avrdude-loop` - これは `:avrdude` と同じコマンドを実行します。ただし書き込みが終了すると再び Caterina デバイスの書き込み待ちに戻ります。これは何台ものデバイスへ書き込むのに便利です。_Ctrl+C を押して、手動でこの繰り返しを終了させる必要があります。_
* `:avrdude-split-left` - デフォルトオプション (`:avrdude`) と同様に通常のファームウェアが書き込まれます。ただし、分割キーボードの「左側の」 EEPROM ファイルも書き込まれます。_これは、Pro Micro ベースの分割キーボードに最適です。_
* `:avrdude-split-right` - デフォルトオプション (`:avrdude`) と同様に通常のファームウェアが書き込まれます。ただし、分割キーボードの「右側の」 EEPROM ファイルも書き込まれます。_これは、Pro Micro ベースの分割キーボードに最適です。_



## Halfkay

Halfkay は PJRC によって開発された超スリムなプロトコルであり、HID を使用し、全ての Teensys (つまり 2.0)に搭載されています。

Halfkay ブートローダとの互換性を確保するために、以下のブロックが `rules.mk` にあることを確認してください:

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = halfkay
```

互換性のあるフラッシャ:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (推奨の GUI)
* [Teensy ローダー](https://www.pjrc.com/teensy/loader.html)
* [Teensy ローダーコマンドライン](https://www.pjrc.com/teensy/loader_cli.html) (推奨のコマンドライン)

書き込み手順:

1. `RESET` キーコードを押すか、RST をすばやく GND にショートします (入力後7秒で書き込みます)
2. OS がデバイスを検知するのを待ちます。
3. .hex ファイルを書き込みます
4. デバイスをアプリケーションモードにリセットします(自動的に実行されるかもしれません)

## USBasploader

USBasploader は matrixstorm によって開発されたブートローダです。V-USB を実行する ATmega328P のような非 USB AVR チップで使われます。

USBasploader ブートローダとの互換性を確保するために、以下のブロックが `rules.mk` にあることを確認してください:

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = USBasp
```

互換性のあるフラッシャ:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (推奨の GUI)
* `usbasp` プログラマを使った [avrdude](http://www.nongnu.org/avrdude/)
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)

書き込み手順:

1. `RESET` キーコードを押すか、RST を GND にすばやくショートしながら、ブートピンを GND にショートしたままにします。
2. OS がデバイスを検知するのを待ちます。
3. .hex ファイルを書き込みます
4. デバイスをアプリケーションモードにリセットします(自動的に実行されるかもしれません)

## BootloadHID

BootloadHID は AVR マイクロコントローラ用の USB ブートローダです。アップローダーツールは Windows でカーネルレベルのドライバを必要としないため、DLL をインストールせずに実行することができます。

bootloadHID ブートローダとの互換性を確保するために、以下のブロックが `rules.mk` にあることを確認してください:

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = bootloadHID
```

互換性のあるフラッシャ:

* [HIDBootFlash](http://vusb.wikidot.com/project:hidbootflash) (推奨の Windows GUI)
* [bootloadhid コマンドライン](https://www.obdev.at/products/vusb/bootloadhid.html) / QMK の `:BootloadHID` (推奨のコマンドライン)

書き込み手順:

1. 以下のいずれかの方法を使ってブートローダに入ります:
   * `RESET` キーコードをタップします (全てのデバイスでは動作しないかもしれません)
   * キーボードを接続しながらソルトキーを押し続けます (通常はキーボードの readme に書かれています)
2. OS がデバイスを検知するのを待ちます。
3. .hex ファイルを書き込みます
4. デバイスをアプリケーションモードにリセットします(自動的に実行されるかもしれません)

あるいは:

    make <keyboard>:<keymap>:bootloadHID

## STM32

全ての STM32 チップには、変更も削除もできない工場出荷時のブートローダがプリロードされています。一部の STM32 チップには USB プログラミングが付属していないブートローダがありますが(例えば STM32F103)、プロセスは同じです。

現時点では、STM32 の `rules.mk` には、`BOOTLOADER` 変数は不要です。

互換性のあるフラッシャ:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (推奨の GUI)
* [dfu-util](https://github.com/Stefan-Schmidt/dfu-util) / `:dfu-util` (推奨のコマンドライン)

書き込み手順:

1. 以下のいずれかの方法を使ってブートローダに入ります:
   * `RESET` キーコードをタップします (STM32F042 デバイスでは動作しないかもしれません)
   * リセット回路が存在する場合、RESET ボタンをタップします
   * それ以外の場合は、(BOOT0 ボタンあるいはブリッジ経由で)BOOT0 を VCC にブリッジし、(REEST ボタンあるいはブリッジ経由で)RESET を GND にショートし、BOOT0 ブリッジを放す必要があります。
2. OS がデバイスを検知するのを待ちます。
3. .bin ファイルを書き込みます
   * DFU 署名に関する警告が表示されます; 無視してください
4. デバイスをアプリケーションモードにリセットします(自動的に実行されるかもしれません)
   * コマンドラインからビルドする場合(例えば、`make planck/rev6:default:dfu-util`)、`rules.mk` の中で `:leave` が `DFU_ARGS` 変数に渡されるようにしてください (例えば、`DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave`)。そうすれば、書き込みの後でデバイスがリセットされます

### STM32 コマンド

ファームウェアを STM32 デバイスに書き込むために使用できる DFU コマンドがいくつかあります。

* `:dfu-util` - STM32 デバイスに書き込むためのデフォルトコマンドで、STM32 ブートローダデバイスが見つかるまで待機します。
* `:dfu-util-split-left` - デフォルトのオプション (`:dfu-util`) と同様に、通常のファームウェアが書き込まれます。ただし、分割キーボードの「左側の」 EEPROM の設定も行われます。
* `:dfu-util-split-right` - デフォルトのオプション (`:dfu-util`) と同様に、通常のファームウェアが書き込まれます。ただし、分割キーボードの「右側の」 EEPROM の設定も行われます。
* `:st-link-cli` - dfu-util ではなく、ST-LINK の CLI ユーティリティを介してファームウェアを書き込めます。
