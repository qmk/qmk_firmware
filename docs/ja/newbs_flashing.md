# ファームウェアを書きこむ

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: ed0575fc8:docs/newbs_flashing.md
  git diff ed0575fc8 HEAD -- docs/newbs_flashing.md | cat
-->

カスタムファームウェアは出来たので、キーボードに書き込みたくなるでしょう/フラッシュしたくなるでしょう。

## QMK Toolbox を使ってキーボードに書き込む

キーボードに書き込む最も簡単な方法は [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) を使うことです。

ただし、QMK Toolbox は、現在は Windows と macOS でしか使えません。
Linuxを使用している場合(および、コマンドラインでファームウェアを書き込みたい場合)は、下の方で概説する[方法](ja/newbs_flashing.md#flash-your-keyboard-from-the-command-line)で行なう必要があります。

### QMK Toolbox にファイルをロードする

まず QMK Toolbox アプリケーションを起動します。
Finder またはエクスプローラーでファームウェアのファイルを探します。
ファイル名は `.hex` または `.bin` のどちらかの形式です。
ビルド時に QMK は、キーボードに適した形式のものを `qmk_firmware` のトップフォルダにコピーしているはずです。

Windows か macOS を使用しているときは現在のファームウェアフォルダをエクスプローラーか Finder で簡単に開くためのコマンドがあります。

#### Windows

```
start .
```

#### macOS

```
open .
```

ファームウェアファイルは常に以下の命名形式に従っています。

```
<keyboard_name>_<keymap_name>.{bin,hex}
```

例えば、`plank/rev5` の `default` キーマップのファイル名は以下のようになります。

```
planck_rev5_default.hex
```

ファームウェアファイルを見つけたら、QMK Toolbox の "Local file" ボックスにドラッグするか、"Open" をクリックしてファームウェアファイルを指定します。

### キーボードを DFU (Bootloader) モードにする

ファームウェアを書き込むには、キーボードを普段とは違う特別な状態、フラッシュモードにする必要があります。
このモードでは、キーボードはキーボードとしての機能をはたしません。
ファームウェアの書き込み中にキーボードのケーブルを抜いたり、書き込みプロセスを中断したりしないことが非常に重要です。

キーボードによって、この特別なモードに入る方法は異なります。
キーボードが現在 QMK または TMK を実行しており、キーボードメーカーから具体的な指示が与えられていない場合は、次を順番に試してください。

* 両方のシフトキーを押しながら、`Pause` キーを押す
* 両方のシフトキーを押しながら、`B` キーを押す
* キーボードのケーブルを抜いて、スペースバーとBを同時に押しながら、キーボードを再び接続し、1秒待ってからキーを放す
* 基板(PCB)に付けられている物理的な `RESET` ボタンを押す
* PCB 上の `BOOT0` か `RESET` のラベルの付いたヘッダピンを探し、PCB 接続中にそれらを互いにショートする

うまくいけば、QMK Toolboxに次のようなメッセージが表示されます。

```
*** Clueboard - Clueboard 66% HotSwap disconnected -- 0xC1ED:0x2390
*** DFU device connected
```

### キーボードへの書き込み

QMK Toolbox の `Flash` ボタンをクリックします。
次のような出力が表示されます。

```
*** Clueboard - Clueboard 66% HotSwap disconnected -- 0xC1ED:0x2390
*** DFU device connected
*** Attempting to flash, please don't remove device
>>> dfu-programmer atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer atmega32u4 flash /Users/skully/qmk_firmware/clueboard_66_hotswap_gen1_skully.hex
    Checking memory from 0x0 to 0x55FF...  Empty.
    0%                            100%  Programming 0x5600 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x5600 bytes written into 0x7000 bytes memory (76.79%).
>>> dfu-programmer atmega32u4 reset
    
*** DFU device disconnected
*** Clueboard - Clueboard 66% HotSwap connected -- 0xC1ED:0x2390
```

## コマンドラインでファームウェアを書き込む :id=flash-your-keyboard-from-the-command-line

これは、以前のものと比較して非常に単純になりました。
ファームウェアをコンパイルして書き込む準備ができたら、ターミナルウィンドウを開いてビルドコマンドを実行します。

    make <my_keyboard>:<my_keymap>:flash

たとえば、キーマップの名前が xyverz で、rev5 planck のキーマップを作成している場合、次のコマンドを使用します。

    make planck/rev5:xyverz:flash

これにより、キーボードの構成が確認され、指定されたブートローダに基づいてキーボードへの書き込みが試行されます。
これはあなたがキーボードが使用するブートローダを知る必要がないことを意味します。
コマンドをただ実行して、コマンド自身に難しい処理を任せます。

ただし、これはキーボードごとに設定されているブートローダに依存します。
もしこの情報が設定されていない場合、または使用しているキーボードのファームウェアの書き込みにサポートしていないターゲットが設定されている場合、次のエラーが表示されます。

    WARNING: This board's bootloader is not specified or is not supported by the ":flash" target at this time.

この場合、あなたは明示的にブートローダを指定する方法を使わなければなりません。

ブートローダは主に 5 種類のものが使われています。
Pro Micro とそのクローンは Caterina を、Teensy は HalfKay を、OLKBの AVR ボードは QMK-DFU を、その他の ATmega32U4 ボードは DFU を、そして多くの ARM ボードは ARM DFU を使います。

より詳しいブートローダの情報は、[Flashing Instructions and Bootloader Information](ja/flashing.md) にあります。

使用しているブートローダがわかっているならば、ファームウェアをコンパイルするときに、実は `make` コマンドにブートローダを指定するテキストを追加して、書き込みプロセスを自動化できます。

### DFU

DFU ブートローダの場合、ファームウェアをコンパイルして書き込む準備ができたら、ターミナルウィンドウを開いてビルドコマンドを実行します。

    make <my_keyboard>:<my_keymap>:dfu

たとえば、キーマップの名前が xyverz で、rev5 planck のキーマップを作成している場合、次のコマンドを使用します。

    make planck/rev5:xyverz:dfu

コンパイルが終了すると、以下の出力になるはずです。

```
Linking: .build/planck_rev5_xyverz.elf                                          [OK]
Creating load file for flashing: .build/planck_rev5_xyverz.hex                  [OK]
Copying planck_rev5_xyverz.hex to qmk_firmware folder                           [OK]
Checking file size of planck_rev5_xyverz.hex
 * File size is fine - 18574/28672
 ```

ここまでくると、ビルドスクリプトは5秒ごとに DFU ブートローダを探します。
デバイスが見つかるか、あなたがキャンセルするまで、以下を繰り返します。

    dfu-programmer: no device present.
    Error: Bootloader not found. Trying again in 5s.

これを実行したら、コントローラーをリセットする必要があります。
そして下のような出力が表示されます。

```
*** Attempting to flash, please don't remove device
>>> dfu-programmer atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer atmega32u4 flash /Users/skully/qmk_firmware/clueboard_66_hotswap_gen1_skully.hex
    Checking memory from 0x0 to 0x55FF...  Empty.
    0%                            100%  Programming 0x5600 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x5600 bytes written into 0x7000 bytes memory (76.79%).
>>> dfu-programmer atmega32u4 reset
```

?> `dfu-programmer：no device present` など、これに関する問題がある場合は、[よくある質問](ja/faq_build.md) を参照してください。

#### DFU コマンド

ファームウェアを DFU デバイスに書き込むために使用できる DFU コマンドがいくつかあります。

* `:dfu` - これが通常のオプションで、DFUデバイスが使用可能になるまで待機したのちファームウェアを書き込みます。5秒ごとに、DFUデバイスが存在するかチェックしています。
* `:dfu-ee` - 通常の hex ファイルの代わりに `eep` ファイルを書き込みます。これを使用するのはまれです。
* `:dfu-split-left` - デフォルトオプション (`:dfu`) と同様に、通常のファームウェアが書き込まれます。ただし、分割キーボードの「左側の」 EEPROMファイルも書き込まれます。_これは、Elite C ベースの分割キーボードに最適です。_
* `:dfu-split-right` - デフォルトオプション (`:dfu`) と同様に、通常のファームウェアが書き込まれます。ただし、分割キーボードの「右側の」EEPROMファイルも書き込まれます。_これは、Elite C ベースの分割キーボードに最適です。_


### Caterina 

Arduino ボードとそれらのクローンの場合(たとえば SparkFun ProMicro)、ファームウェアをコンパイルして書き込む準備ができたら、ターミナルウィンドウを開いてビルドコマンドを実行します。

    make <my_keyboard>:<my_keymap>:avrdude

たとえば、キーマップの名前が xyverz で、rev2 Lets Split のキーマップを作成している場合、次のコマンドを使用します。

    make lets_split/rev2:xyverz:avrdude

ファームウェアのコンパイルが完了すると、以下のように出力されます。

```
Linking: .build/lets_split_rev2_xyverz.elf                                      [OK]
Creating load file for flashing: .build/lets_split_rev2_xyverz.hex              [OK]
Checking file size of lets_split_rev2_xyverz.hex                                [OK]
 * File size is fine - 27938/28672
Detecting USB port, reset your controller now..............
```

この時点で、キーボードをリセットすると、スクリプトがブートローダを検出し、キーボードに書き込みます。出力は次のようになります。

```
Detected controller on USB port at /dev/ttyS15

Connecting to programmer: .
Found programmer: Id = "CATERIN"; type = S
    Software Version = 1.0; No Hardware Version given.
Programmer supports auto addr increment.
Programmer supports buffered memory access with buffersize=128 bytes.

Programmer supports the following devices:
    Device code: 0x44

avrdude.exe: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude.exe: Device signature = 0x1e9587 (probably m32u4)
avrdude.exe: NOTE: "flash" memory has been specified, an erase cycle will be performed
             To disable this feature, specify the -D option.
avrdude.exe: erasing chip
avrdude.exe: reading input file "./.build/lets_split_rev2_xyverz.hex"
avrdude.exe: input file ./.build/lets_split_rev2_xyverz.hex auto detected as Intel Hex
avrdude.exe: writing flash (27938 bytes):

Writing | ################################################## | 100% 2.40s

avrdude.exe: 27938 bytes of flash written
avrdude.exe: verifying flash memory against ./.build/lets_split_rev2_xyverz.hex:
avrdude.exe: load data flash data from input file ./.build/lets_split_rev2_xyverz.hex:
avrdude.exe: input file ./.build/lets_split_rev2_xyverz.hex auto detected as Intel Hex
avrdude.exe: input file ./.build/lets_split_rev2_xyverz.hex contains 27938 bytes
avrdude.exe: reading on-chip flash data:

Reading | ################################################## | 100% 0.43s

avrdude.exe: verifying ...
avrdude.exe: 27938 bytes of flash verified

avrdude.exe: safemode: Fuses OK (E:CB, H:D8, L:FF)

avrdude.exe done.  Thank you.
```
うまくいかない時は、以下のようにする必要があるかもしれません。

    sudo make <my_keyboard>:<my_keymap>:avrdude


#### Caterina コマンド

ファームウェアを DFU デバイスに書き込むために使用できる DFU コマンドがいくつかあります。

* `:avrdude` - これが通常のオプションで、Caterina デバイスが(新しい COM ポートを検出して)使用可能になるまで待機し、ファームウェアを書き込みます。
* `:avrdude-loop` - これは `:avrdude` と同じです。ただし書き込みが終了すると再び Caterina デバイスの書き込み待ちに戻ります。これは何台ものデバイスへの書き込みに便利です。_Control+C を押して、手動でこの繰り返しを終了させる必要があります。_
* `:avrdude-split-left` - デフォルトオプション(`:avrdude`)と同様に通常のファームウェアが書き込まれます。ただし、分割キーボードの「左側の」EEPROMファイルもフラッシュされます。 _これは、Pro Micro ベースの分割キーボードに最適です。_
* `:avrdude-split-right` - デフォルトオプション(`:avrdude`)と同様に通常のファームウェアが書き込まれます。ただし、分割キーボードの「右側の」EEPROMファイルもフラッシュされます。 _これは、Pro Micro ベースの分割キーボードに最適です。_

### HalfKay

PJRC デバイス(Teensy シリーズ)の場合、ファームウェアをコンパイルして書き込む準備ができたら、ターミナルウィンドウを開いてビルドコマンドを実行します。

    make <my_keyboard>:<my_keymap>:teensy

たとえば、キーマップの名前が xyverz で、Ergodox または Ergodox EZ のキーマップを作成している場合、次のコマンドを使用します。

    make ergodox_ez:xyverz:teensy

ファームウェアのコンパイルが完了すると、以下のように出力されます。

```
Linking: .build/ergodox_ez_xyverz.elf                                            [OK]
Creating load file for flashing: .build/ergodox_ez_xyverz.hex                    [OK]
Checking file size of ergodox_ez_xyverz.hex                                      [OK]
 * File size is fine - 25584/32256
 Teensy Loader, Command Line, Version 2.1
Read "./.build/ergodox_ez_xyverz.hex": 25584 bytes, 79.3% usage
Waiting for Teensy device...
 (hint: press the reset button)
 ```

この時点で、キーボードをリセットします。すると、次のような出力が表示されます。

 ```
 Found HalfKay Bootloader
Read "./.build/ergodox_ez_xyverz.hex": 28532 bytes, 88.5% usage
Programming............................................................................................................................................................................
...................................................
Booting
```

### STM32 (ARM)

主な ARM ボード (Proton C, Planck Rev 6, Preonic Rev 3 を含む)の場合、ファームウェアをコンパイルして書き込む準備ができたら、ターミナルウィンドウを開いてビルドコマンドを実行します。

    make <my_keyboard>:<my_keymap>:dfu-util

たとえば、キーマップの名前が xyverz で、Planck Revision 6 のキーマップを作成している場合、次のコマンドを使用し、(コンパイルが終わる前に)キーボードを再起動してブートローダを起動します:

    make planck/rev6:xyverz:dfu-util

ファームウェアのコンパイルが完了すると、以下のように出力されます。

```
Linking: .build/planck_rev6_xyverz.elf                                          [OK]
Creating binary load file for flashing: .build/planck_rev6_xyverz.bin           [OK]
Creating load file for flashing: .build/planck_rev6_xyverz.hex                  [OK]

Size after:
   text    data     bss     dec     hex filename
      0   41820       0   41820    a35c .build/planck_rev6_xyverz.hex

Copying planck_rev6_xyverz.bin to qmk_firmware folder                           [OK]
dfu-util 0.9

Copyright 2005-2009 Weston Schmidt, Harald Welte and OpenMoko Inc.
Copyright 2010-2016 Tormod Volden and Stefan Schmidt
This program is Free Software and has ABSOLUTELY NO WARRANTY
Please report bugs to http://sourceforge.net/p/dfu-util/tickets/

Invalid DFU suffix signature
A valid DFU suffix will be required in a future dfu-util release!!!
Opening DFU capable USB device...
ID 0483:df11
Run-time device DFU version 011a
Claiming USB DFU Interface...
Setting Alternate Setting #0 ...
Determining device status: state = dfuERROR, status = 10
dfuERROR, clearing status
Determining device status: state = dfuIDLE, status = 0
dfuIDLE, continuing
DFU mode device DFU version 011a
Device returned transfer size 2048
DfuSe interface name: "Internal Flash  "
Downloading to address = 0x08000000, size = 41824
Download        [=========================] 100%        41824 bytes
Download done.
File downloaded successfully
Transitioning to dfuMANIFEST state
```

#### STM32 コマンド

ファームウェアを STM32 デバイスに書き込むために使用できる DFU コマンドがいくつかあります。

* `:dfu-util` - STM32 デバイスに書き込むためのデフォルトコマンドで、STM32 ブートローダが見つかるまで待機します。
* `:dfu-util-split-left` - デフォルトのオプション (`:dfu-util`) と同様に、通常のファームウェアが書き込まれます。 ただし、分割キーボードの「左側の」EEPROM の設定も行われます。
* `:dfu-util-split-right` - デフォルトのオプション (`:dfu-util`) と同様に、通常のファームウェアが書き込まれます。 ただし、分割キーボードの「右側の」EEPROM の設定も行われます。
* `:st-link-cli` - dfu-util ではなく、ST-LINK の CLI ユーティリティを介してファームウェアを書き込めます。

### BootloadHID

Bootmapper Client(BMC)/bootloadHID/ATmega32A ベースのキーボードの場合、ファームウェアをコンパイルして書き込む準備ができたら、ターミナルウィンドウを開いてビルドコマンドを実行します。

    make <my_keyboard>:<my_keymap>:bootloaderHID

たとえば、キーマップの名前が xyverz で、jj40 のキーマップを作成している場合、次のコマンドを使用します。

    make jj40:xyverz:bootloaderHID

ファームウェアのコンパイルが完了すると、以下のように出力されます。

```
Linking: .build/jj40_default.elf                                                [OK]
Creating load file for flashing: .build/jj40_default.hex                        [OK]
Copying jj40_default.hex to qmk_firmware folder                                 [OK]
Checking file size of jj40_default.hex                                          [OK]
 * The firmware size is fine - 21920/28672 (6752 bytes free)
```

ここまでくると、ビルドスクリプトは5秒ごとに DFU ブートローダを探します。
デバイスが見つかるか、あなたがキャンセルするまで、以下を繰り返します。

```
Error opening HIDBoot device: The specified device was not found
Trying again in 5s.
```

これを実行したら、コントローラーをリセットする必要があります。
そして下のような出力が表示されます。

```
Page size   = 128 (0x80)
Device size = 32768 (0x8000); 30720 bytes remaining
Uploading 22016 (0x5600) bytes starting at 0 (0x0)
0x05580 ... 0x05600
```

## テストしましょう！

おめでとうございます！ カスタムファームウェアがキーボードにプログラムされました！

使ってみて、すべてがあなたの望むように動作するかどうか確認してください。
この初心者ガイドを完全なものにするために [テストとデバッグ](ja/newbs_testing_debugging.md) を書いたので、カスタム機能のトラブルシューティング方法については、こちらをご覧ください。
