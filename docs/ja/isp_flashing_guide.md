# ISP 書き込みガイド

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.9.46:docs/isp_flashing_guide.md
  git diff 0.9.46 HEAD -- docs/isp_flashing_guide.md | cat
-->

ISP 書き込み(ICSP 書き込みと呼ぶ場合もあります)とは、マイクロコントローラーを直接プログラミングするプロセスです。
これにより、ブートローダを交換したり、コントローラの「ヒューズ」を変更することができ、コントローラの速度や起動方法、その他のオプションなど、多くのハードウェアおよびソフトウェア関連の機能を制御します。

QMK の ISP 書き込みの主な用途は、AVRベースのコントローラ（Pro Micro、または V-USB チップ）のブートローダの書き込みまたは交換です。

?> これは Pro Micro や他の ATmega コントローラなどの AVR ベースのボードをプログラミングするためだけのものです。 Proton C などの Arm コントローラには使用できません。

## 破損したブートローダーの取り扱い

ボードの書き込み/消去で問題が発生し、DFU ベースのコントローラで次のような不可解なエラーメッセージが表示される場合：

    libusb: warning [darwin_transfer_status] transfer error: timed out
    dfu.c:844: -ETIMEDOUT: Transfer timed out, NAK 0xffffffc4 (-60)
    atmel.c:1627: atmel_flash: flash data dfu_download failed.
    atmel.c:1629: Expected message length of 1072, got -60.
    atmel.c:1434: Error flashing the block: err -2.
    ERROR
    Memory write error, use debug for more info.
    commands.c:360: Error writing memory data. (err -4)

    dfu.c:844: -EPIPE: a) Babble detect or b) Endpoint stalled 0xffffffe0 (-32)
    Device is write protected.
    dfu.c:252: dfu_clear_status( 0x7fff4fc2ea80 )
    atmel.c:1434: Error flashing the block: err -2.
    ERROR
    Memory write error, use debug for more info.
    commands.c:360: Error writing memory data. (err -4)

または、Pro Micro ベースのコントローラに対して次のようなメッセージが表示された場合:

    avrdude: butterfly_recv(): programmer is not responding
    avrdude: butterfly_recv(): programmer is not responding
    avrdude: verification error, first mismatch at byte 0x002a
            0x2b != 0x75
    avrdude: verification error; content mismatch
    avrdude: verification error; content mismatch


あなたのボード/デバイスを再び動作させるには、ISP 書き込みが必要になるかもしれません。

## 必要なハードウェア

実際に ISP の書き込みを行うには、以下のいずれか（その後に使用するプロトコルが続きます）が必要になります。

* [SparkFun PocketAVR](https://www.sparkfun.com/products/9825) - (USB Tiny)
* [USBtinyISP AVR Programmer Kit](https://www.adafruit.com/product/46) - (USB Tiny)
* [Teensy 2.0](https://www.pjrc.com/store/teensy.html) - (avrisp)
* [Pro Micro](https://www.sparkfun.com/products/12640)  - (avrisp)
* [Bus Pirate](https://www.adafruit.com/product/237) - (buspirate)

ISP 書き込みに使用できるデバイスは他にもありますが、これらが主なものです。
また、すべての製品リンクは公式バージョンへのものです。他の場所で入手することもできます。

また、「ISP プログラマ」をプログラミングするデバイスに配線するためのものも必要になります。
PCB の中には直接使用できる ISP ヘッダがあるものもありますが、そうではない場合が多いので、コントローラ自体にハンダ付けするか、別のスイッチや他のコンポーネントにハンダ付けする必要があるでしょう。

### ISP ファームウェア

Teensy と Pro Micro のコントローラを ISP プログラマとして使用するには、コントローラに ISP ファームウェアを書き込む必要があります。
それ以外のハードウェアは、あらかじめプログラムされているはずです。
そのため、これらのコントローラの場合は、正しい hex ファイルをダウンロードしてから書き込んでください。

* Teensy 2.0: [`util/teensy_2.0_ISP_B0.hex`](https://github.com/qmk/qmk_firmware/blob/master/util/teensy_2.0_ISP_B0.hex) (`B0`)
* Pro Micro: [`util/pro_micro_ISP_B6_10.hex`](https://github.com/qmk/qmk_firmware/blob/master/util/pro_micro_ISP_B6_10.hex) (`10/B6`)

コントローラに書き込んだら、この hex ファイルはもう必要ありません。

## 必要なソフトウェア

QMK ツールボックスは、このほとんど（すべて）に使用することができます。

ただし、Teensy 2.0 ボードを使っている場合は、[Teensy Loader](https:/www.pjrc.comteensyloader.html) を使えば、Teensy 2.0 ボードに書き込むことができます。
あるいは、`avrdude` (`qmk_install.sh` の一部としてインストールされています) や、[AVRDUDESS](https:/blog.zakkemble.netavrdudess-a-gui-for-avrdude)(Windows 用) を使って、Pro Micro に書き込んだり、ISP を書き込んだりすることができます。

## 配線

これは非常に簡単です。次のようにして、相互に対応するものを接続します。

### SparkFun Pocket AVR

    PocketAVR RST  <-> Keyboard RESET
    PocketAVR SCLK <-> Keyboard B1 (SCLK)
    PocketAVR MOSI <-> Keyboard B2 (MOSI)
    PocketAVR MISO <-> Keyboard B3 (MISO)
    PocketAVR VCC  <-> Keyboard VCC
    PocketAVR GND  <-> Keyboard GND

### Teensy 2.0

    Teensy B0  <-> Keyboard RESET
    Teensy B1  <-> Keyboard B1 (SCLK)
    Teensy B2  <-> Keyboard B2 (MOSI)
    Teensy B3  <-> Keyboard B3 (MISO)
    Teensy VCC <-> Keyboard VCC
    Teensy GND <-> Keyboard GND
    
!> Teensy の B0 ピンはキーボードのコントローラの RESET/RST ピンと配線されています。 Teensy の RESET ピンをキーボードの RESET に配線しないでください。

### Pro Micro

    Pro Micro 10 (B6)  <-> Keyboard RESET
    Pro Micro 15 (B1)  <-> Keyboard B1 (SCLK)
    Pro Micro 16 (B2)  <-> Keyboard B2 (MOSI)
    Pro Micro 14 (B3)  <-> Keyboard B3 (MISO)
    Pro Micro VCC      <-> Keyboard VCC
    Pro Micro GND      <-> Keyboard GND

!> Pro Micro の 10/B6 ピンはキーボードのコントローラの RESET/RST ピンに配線されています。 Pro Micro の RESET ピンをキーボードの RESET に配線 ***しないでください***。

## キーボードへの書き込み

ISP プログラマをセットアップして、キーボードに接続したら、キーボードに書き込みをします。

### ブートローダファイル

普通の状態に戻す一番簡単で手っ取り早い方法は、キーボードにブートローダだけ書き込むことです。
これが終れば、普通にキーボードを接続して、普通にキーボードに書き込みできるようになります。

標準のブートローダは[`util/` フォルダー](https://github.com/qmk/qmk_firmware/tree/master/util) にあります。
チップの正しいブートローダを書き込んでください:

* **Atmel DFU**
  * [ATmega16U4](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_atmega16u4_1.0.1.hex)
  * [ATmega32U4](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_atmega32u4_1.0.0.hex)
  * [AT90USB64](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_at90usb64_1.0.0.hex)
  * [AT90USB128](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_at90usb128_1.0.1.hex)
* **Caterina**
  * [Pro Micro (5V/16MHz)](https://github.com/sparkfun/Arduino_Boards/blob/master/sparkfun/avr/bootloaders/caterina/Caterina-promicro16.hex)
  * [Pro Micro (3.3V/8MHz)](https://github.com/sparkfun/Arduino_Boards/blob/master/sparkfun/avr/bootloaders/caterina/Caterina-promicro8.hex)
* **BootloadHID (PS2AVRGB)**
  * [ATmega32A](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_ps2avrgb_bootloadhid_1.0.1.hex)

お使いのボードが何を使っているかわからない場合は、QMK のキーボード用の `rules.mk` ファイルを見てください。
`MCU` と `BOOTLOADER` の行には必要な値が書かれています。これはボードのバージョンによって異なるかもしれません。

### 製造手法

ブートローダと通常のファームウェアを同時に書き込みたい場合、2つの方法があります。
手動で行うか、コンパイル時に `:production` ターゲットを使って行うかです。

手動で行うには:

1. オリジナルのファームウェアの .hex ファイルをテキストエディタで開きます
2. 最後の行を削除してください。(`:00000001FF`になっているはずです - これは EOF メッセージです)
3. ブートローダの内容全体を新しい行にコピーして(行間に空行を入れないように)、元のファイルの最後に貼り付けてください。
4. これを新しいファイルとして `<keyboard>_<keymap>_production.hex` という名前で保存します。

?> ここでは他のブートローダも同じように使うことができますが、__ブートローダが必要で__、そうしないとまた ISP を使ってキーボードに新しいファームウェアを書き込まなければならなくなります。

#### QMK DFU ブートローダとプロダクションイメージの作成

コンパイル時に `:production` ターゲットを使用して、ボード用のファームウェア、QMK DFU ブートローダ、プロダクションファームウェアイメージを作成することができます。
これが完了すると、3つのファイルが表示されます:

* `<keyboard>_<keymap>.hex`
* `<keyboard>_<keymap>_bootloader.hex`
* `<keyboard>_<keymap>_production.hex`

QMK DFU ブートローダは `atmega32u4` コントローラ (AVR ベースの Planck ボードや Pro Micro など) でしかテストされておらず、他のコントローラではテストされていません。
しかし、`atmega32a` や `atmega328p` のような V-USB コントローラでは間違いなく動作しません。

ブートローダかプロダクションファームウェアファイルのどちらかを書き込むことができます。
プロダクションファームウェアファイルの方が、より多くのデータを書き込むので、書き込みに時間がかかります。

?> 注意：同じブートローダを使用しつづけるべきです。すでに DFU を使用している場合は、QMK DFU に切り替えても問題ありません。しかし、例えば Pro Micro に QMK DFU を書き込むには、追加の手順が必要になります。

## ブートローダ/プロダクションファイルの書き込み

キーボードがどのデバイスにも接続されていないことを確認し、ISP プログラマを接続してください。

ブートローダの種類を変更したい場合は、コマンドラインを使用する必要があります。

### QMK Toolbox

1. 'AVRISP device connected' または `USB Tiny device connected` が黄色で表示されます。
2. `Open` ダイアログで正しいブートローダー/プロダクションの .hex ファイルを選択します（パスにスペースを含めることはできません）
3. 書きこもうとしているキーボード（ISP プログラマではなく）のための正しい `Microcontroller` オプションが選択されていることを確認してください。
4. `Flash` を押します
5. 特にプロダクションファイルの場合、しばらくは何も出力されませんが、待ちましょう。

検証とヒューズのチェックに問題がなければ、完了です。
ボードが自動的に再起動する場合があります。
それ以外の場合は、Teensy のプラグを抜いて、キーボードを接続します。
テスト中は、Teensy をキーボードに接続したままにすることができますが、すべてが正常に機能することを確認したら、はんだを外すか、配線を外すことをお勧めします。

### コマンドライン

ターミナル（Windows の場合は `cmd`）を開いて、修正した .hex ファイルがある場所に移動します。
ここでは、このファイルを `main.hex` と呼び、Teensy 2.0 が `COM3` ポートに接続されていると仮定します。
よくわからない場合は、デバイスマネージャを開いて、`Ports > USB Serial Device` を探してください。ここにある COM ポートを使ってください。
あなたはそれが正しいポートであることを確認することができます：

    avrdude -c avrisp -P COM3 -p atmega32u4

次のような出力が得られるはずです:

    avrdude: AVR device initialized and ready to accept instructions

    Reading | ################################################## | 100% 0.02s

    avrdude: Device signature = 0x1e9587

    avrdude: safemode: Fuses OK

    avrdude done.  Thank you.

私たちのキーボードは `atmega32u4`（共通）を使用しているので、これが指定するチップです。
以下が完全なコマンドです：

    avrdude -c avrisp -P COM3 -p atmega32u4 -U flash:w:main.hex:i

ボードが `atmega32a`（jj40 など）を使用している場合、コマンドは次のとおりです（最後の追加コードによりヒューズが正しく設定されます）。

	avrdude -c avrisp -P COM3 -p atmega32 -U flash:w:main.hex:i -U hfuse:w:0xD0:m -U lfuse:w:0x0F:m

プログレスバーが表示されてから、以下が表示されるはずです。

    avrdude: verifying ...
    avrdude: 32768 bytes of flash verified

    avrdude: safemode: Fuses OK

    avrdude done.  Thank you.

これは全てうまく動作したことを示しています。
ボードが自動的に再起動する場合もありますが、そうでない場合は、Teensy のプラグを抜いてキーボードを接続してください。
テスト中は、Teensy をキーボードに接続したままにすることができますが、すべてが正常に機能することを確認したら、はんだを外すか、配線を外すことをお勧めします。

SparkFun PocketAVR Programmer や、他の USB Tiny ベースの ISP プログラマを使用している場合は、次のようなものを使用すると良いでしょう。

    avrdude -c usbtiny -P usb -p atmega32u4

#### 上級者向け: ヒューズの変更

Pro Micro に QMK DFU を書き込むなど、ブートローダを切り替える場合は、ブートローダの hex ファイルの書き込みに加えて、ヒューズを変更する必要があります。
これは、`caterina` (Pro Micro ブートローダ) と `dfu` では起動ルーチンの扱いが異なり、その動作はヒューズによって制御されるからです。

!> これは、ヒューズを変更することは、永久にあなたのコントローラをレンガ化(訳注:日本では文鎮化と呼ぶことが多い、コントローラがまったく無反応になる状態)することができる方法の1つであるため、それは非常に注意が必要な1つの領域です。 

以下は、`atmega32u4`の 5V 16MHz 版（5V Pro Micro など）を想定しています。

`atmega32u4`の DFU の場合、必要なヒューズ設定は次のとおりです:

| ヒューズ | 設定             |
|----------|------------------|
| Low      | `0x5E`           |
| High     | `0xD9` or `0x99` |
| Extended | `0xC3`           |

High ヒューズは 0xD9 か 0x99 のどちらかになります。
違いは、0xD9 は QMK Firmware がソフトウェアでも無効化している JTAG を無効化しているのに対し、0x99 は JTAG を無効化していないことです。

これを設定するには、`-U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xC3:m` をコマンドに追加します。
そうすると、最終的なコマンドは次のようになります。

    avrdude -c avrisp -P COM3 -p atmega32u4 -U flash:w:main.hex:i -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xC3:m

`atmega32u4`の Caterina では、以下があなたに必要なヒューズの設定です。

| ヒューズ | 設定   |
|----------|--------|
| Low      | `0xFF` |
| High     | `0xD8` |
| Extended | `0xCB` |

これを設定するには、コマンドに `-U lfuse:w:0xFF:m -U hfuse:w:0xD8:m -U efuse:w:0xCB:m` を追加します。
これで、最終的なコマンドは次のようになるはずです。

    avrdude -c avrisp -P COM3 -p atmega32u4 -U flash:w:main.hex:i -U lfuse:w:0xFF:m -U hfuse:w:0xD8:m -U efuse:w:0xCB:m


別のコントローラーを使用している場合や、別の設定を希望する場合は、この[AVR ヒューズ計算機](https://www.engbedded.com/fusecalc)を使用して、より適切な値を見つけることができます。

## ヘルプ

ご質問・ご不明な点がありましたら、お気軽に[issue を開いてください](https://github.com/qmk/qmk_firmware/issues/new)！
