# ISP Flashing Guide

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.9.46:docs/isp_flashing_guide.md
  git diff 0.9.46 HEAD -- docs/isp_flashing_guide.md | cat
-->

ISP flashing (also known as ICSP flashing) is the process of programming a microcontroller directly.  This allows you to replace the bootloader, or change the "fuses" on the controller, which control a number of hardware- and software-related functions, such as the speed of the controller, how it boots, and other options.  
ISP 書き込み(ICSP 書き込みと呼ぶ場合もあります)とは、マイクロコントローラーを直接プログラミングするプロセスです。
これにより、ブートローダを交換したり、コントローラの「ヒューズ」を変更したりすることができ、コントローラの速度や起動方法、その他のオプションなど、多くのハードウェアおよびソフトウェア関連の機能を制御します。

The main use of ISP flashing for QMK is flashing or replacing the bootloader on your AVR-based controller (Pro Micros, or V-USB chips).  
QMK の ISP 書き込みの主な用途は、AVRベースのコントローラ（Pro Micros、またはV-USBチップ）のブートローダの書き込みまたは交換です。

?> This is only for programming AVR based boards, such as the Pro Micro or other ATmega controllers.  It is not for Arm controllers, such as the Proton C. 
?> これは Pro Micro や他の ATmega コントローラなどの AVR ベースのボードをプログラミングするためだけのものです。 Proton C などの Arm コントローラには使用できません。

## 破損したブートローダーの取り扱い Dealing with Corrupted Bootloaders

If you're having trouble flashing/erasing your board, and running into cryptic error messages like any of the following for a DFU based controller:
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

Or, if you see this sort of message for a Pro Micro based controller:
または、Pro Micro ベースのコントローラに対して次のようなメッセージが表示された場合：

    avrdude: butterfly_recv(): programmer is not responding
    avrdude: butterfly_recv(): programmer is not responding
    avrdude: verification error, first mismatch at byte 0x002a
            0x2b != 0x75
    avrdude: verification error; content mismatch
    avrdude: verification error; content mismatch


You're likely going to need to ISP flash your board/device to get it working again. 
あなたのボード/デバイスを再び動作させるには、ISP 書き込みが必要になるかもしれません。

## 必要なハードウェア Hardware Needed

You'll need one of the following to actually perform the ISP flashing (followed by the protocol they use):
実際にISPの書き込みを行うには、以下のいずれかが必要になります（その後に使用するプロトコルが続きます）。

* [SparkFun PocketAVR](https://www.sparkfun.com/products/9825) - (USB Tiny)
* [USBtinyISP AVR Programmer Kit](https://www.adafruit.com/product/46) - (USB Tiny)
* [Teensy 2.0](https://www.pjrc.com/store/teensy.html) - (avrisp)
* [Pro Micro](https://www.sparkfun.com/products/12640)  - (avrisp)
* [Bus Pirate](https://www.adafruit.com/product/237) - (buspirate)

There are other devices that can be used to ISP flash, but these are the main ones.  Also, all product links are to the official versions. You can source them elsewhere. 
ISP書き込みに使用できるデバイスは他にもありますが、これらが主なものです。 また、すべての製品リンクは公式バージョンへのものです。他の場所で入手することができます。

You'll also need something to wire your "ISP Programmer" to the device that you're programming.  Some PCBs may have ISP headers that you can use directly, but this often isn't the case, so you'll likely need to solder to the controller itself or to different switches or other components. 
また、"ISP Programmer" をプログラミングするデバイスに配線するためのものも必要になります。
PCB の中には ISP ヘッダを直接使用できるものもありますが、そうではない場合が多いので、コントローラ自体にハンダ付けするか、別のスイッチや他のコンポーネントにハンダ付けする必要があるでしょう。

### ISP ファームウェア The ISP Firmware

The Teensy and Pro Micro controllers will need you to flash the ISP firmware to the controllers before you can use them as an ISP programmer.  The rest of the hardware should come preprogrammed.  So, for these controllers, download the correct hex file, and flash it first. 
Teensy と Pro Micro のコントローラを ISP プログラマとして使用するには、コントローラに ISP ファームウェアを書き込む必要があります。
それ以外のハードウェアは、あらかじめプログラムされているはずです。
そのため、これらのコントローラの場合は、正しいヘキサファイルをダウンロードしてから書き込んでください。

* Teensy 2.0: [`util/teensy_2.0_ISP_B0.hex`](https://github.com/qmk/qmk_firmware/blob/master/util/teensy_2.0_ISP_B0.hex) (`B0`)
* Pro Micro: [`util/pro_micro_ISP_B6_10.hex`](https://github.com/qmk/qmk_firmware/blob/master/util/pro_micro_ISP_B6_10.hex) (`10/B6`)

Once you've flashed your controller, you won't need this hex file anymore.
コントローラに書き込んだら、このヘキサファイルはもう必要ありません。

## 必要なソフトウェア Software Neede

The QMK Toolbox can be used for most (all) of this.  
QMK ツールボックスは、このほとんど（すべて）に使用することができます。

However, you can grab the [Teensy Loader](https://www.pjrc.com/teensy/loader.html) to flash your Teensy 2.0 board, if you are using that. Or you can use `avrdude` (installed as part of `qmk_install.sh`), or [AVRDUDESS](https://blog.zakkemble.net/avrdudess-a-gui-for-avrdude/) (for Windows) to flash the Pro Micro, and the ISP flashing. 
[Teensy Loader](https:/www.pjrc.comteensyloader.html) を使えば、Teensy 2.0 ボードに書き込むことができます。あるいは、`avrdude` (`qmk_install.sh` の一部としてインストールされています) や、[AVRDUDESS](https:/blog.zakkemble.netavrdudess-a-gui-for-avrdude)(Windows用) を使って、Pro Micro に書き込んだり、ISPを書き込んだりすることができます。

## 配線 Wiring

This is pretty straight-forward - we'll be connecting like-things to like-things in the following manner.
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
    
!> Note that the B0 pin on the Teensy is wired to the RESET/RST pin on the keyboard's controller.  ***DO NOT*** wire the RESET pin on the Teensy to the RESET on the keyboard. 
!> Teensy の B0 ピンはキーボードのコントローラの RESET/RST ピンと配線されています。 Teensy の RESETピンをキーボードの RESET に配線しないでください。

### Pro Micro

    Pro Micro 10 (B6)  <-> Keyboard RESET
    Pro Micro 15 (B1)  <-> Keyboard B1 (SCLK)
    Pro Micro 16 (B2)  <-> Keyboard B2 (MOSI)
    Pro Micro 14 (B3)  <-> Keyboard B3 (MISO)
    Pro Micro VCC      <-> Keyboard VCC
    Pro Micro GND      <-> Keyboard GND

!> Note that the 10/B6 pin on the Pro Micro is wired to the RESET/RST pin on the keyboard's controller.  ***DO NOT*** wire the RESET pin on the Pro Micro to the RESET on the keyboard. 
!> Pro Micro の 10/B6 ピンはキーボードのコントローラの RESET/RST ピンに配線されています。 Pro Micro の RESET ピンをキーボードの RESET に配線しないでください。

## キーボードの書き込み Flashing Your Keyboard

After you have your ISP programmer set up, and wired to your keyboard, it's time to flash your keyboard.  
ISP プログラマをセットアップして、キーボードに接続したら、キーボードに書き込みをします。

### ブートローダファイル The Bootloader File

The simplest and quickest way to get things back to normal is to flash only a bootloader to the keyboard. Once this is done, you can connect the keyboard normally and flash the keyboard like you normally would. 
一番簡単で手っ取り早い方法は、キーボードにブートローダだけ書き込むことです。これが終れば、普通にキーボードを接続して、普通にキーボードに書き込みできるようになります。

You can find the stock bootloaders in the [`util/` folder](https://github.com/qmk/qmk_firmware/tree/master/util). Be sure to flash the correct bootloader for your chip:
標準のブートローダは[`util/` フォルダー]（https://github.com/qmk/qmk_firmware/tree/master/util）にあります。 チップの正しいブートローダを書き込んでください:

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

If you're not sure what your board uses, look in the `rules.mk` file for the keyboard in QMK. The `MCU` and `BOOTLOADER` lines will have the value you need. It may differ between different versions of the board.
お使いのボードが何を使っているかわからない場合は、QMKのキーボード用の `rules.mk` ファイルを見てください。
`MCU` と `BOOTLOADER` の行には必要な値が書かれています。これはボードのバージョンによって異なるかもしれません。

### Production Techniques

If you'd like to flash both the bootloader **and** the regular firmware at the same time, there are two options to do so.  Manually, or with the `:production` target when compiling. 

To do this manually: 

1. Open the original firmware .hex file in a text editor
2. Remove the last line (which should be `:00000001FF` - this is an EOF message)
3. Copy the entire bootloader's contents onto a new line (with no empty lines between) and paste it at the end of the original file
4. Save it as a new file by naming it `<keyboard>_<keymap>_production.hex`

?> It's possible to use other bootloaders here in the same way, but __you need a bootloader__, otherwise you'll have to use ISP again to write new firmware to your keyboard.

#### Create QMK DFU Bootloader and Production images

You can create the firmware, the QMK DFU Bootloader and the production firmware images for the board using the `:production` target when compiling.  Once this is done, you'll see three files: 
* `<keyboard>_<keymap>.hex`
* `<keyboard>_<keymap>_bootloader.hex`
* `<keyboard>_<keymap>_production.hex`

The QMK DFU bootloader has only really been tested on `atmega32u4` controllers (such as the AVR based Planck boards, and the Pro Micro), and hasn't been tested on other controllers.  However, it will definitely not work on V-USB controllers, such as the `atmega32a` or `atmega328p`.

You can flash either the bootloader or the production firmware file. The production firmware file will take a lot longer to flash, since it's flashing a lot more data. 

?> Note: You should stay with the same bootloader. If you're using DFU already, switching to QMK DFU is fine. But flashing QMK DFU onto a Pro Micro, for instance, has additional steps needed.

## Flashing Your Bootloader/Production File

Make sure your keyboard is unplugged from any device, and plug in your ISP Programmer.

If you want to change bootloader types, You'll need to use the command line. 

### QMK Toolbox

1. `AVRISP device connected` or `USB Tiny device connected` will show up in yellow
2. Select the correct bootloader/production .hex file with the `Open` dialog (spaces can't be in the path)
3. Be sure the correct `Microcontroller` option for the keyboard you're flashing (not the ISP programmer) is selected
4. Hit `Flash`
5. Wait, as nothing will output for a while, especially with production files

If the verification and fuse checks are ok, you're done! Your board may restart automatically, otherwise, unplug your Teensy and plug in your keyboard - you can leave your Teensy wired to your keyboard while testing things, but it's recommended that you desolder it/remove the wiring once you're sure everything works.

### Command Line

Open a terminal (`cmd` on Windows, for instance) and navigate to your where your modified .hex file is. We'll pretend this file is called `main.hex`, and that your Teensy 2.0 is on the `COM3` port - if you're unsure, you can open your Device Manager, and look for `Ports > USB Serial Device`. Use that COM port here. You can confirm it's the right port with:

    avrdude -c avrisp -P COM3 -p atmega32u4

and you should get something like the following output:

    avrdude: AVR device initialized and ready to accept instructions

    Reading | ################################################## | 100% 0.02s

    avrdude: Device signature = 0x1e9587

    avrdude: safemode: Fuses OK

    avrdude done.  Thank you.

Since our keyboard uses an `atmega32u4` (common), that is the chip we'll specify. This is the full command:

    avrdude -c avrisp -P COM3 -p atmega32u4 -U flash:w:main.hex:i

If your board uses an `atmega32a` (e.g. on a jj40), the command is this (the extra code at the end sets the fuses correctly):

	avrdude -c avrisp -P COM3 -p atmega32 -U flash:w:main.hex:i -U hfuse:w:0xD0:m -U lfuse:w:0x0F:m

You should see a couple of progress bars, then you should see:

    avrdude: verifying ...
    avrdude: 32768 bytes of flash verified

    avrdude: safemode: Fuses OK

    avrdude done.  Thank you.

Which means everything should be ok! Your board may restart automatically, otherwise, unplug your Teensy and plug in your keyboard - you can leave your Teensy wired to your keyboard while testing things, but it's recommended that you desolder it/remove the wiring once you're sure everything works.

If you're using a SparkFun PocketAVR Programmer, or another USB Tiny based ISP programmer, you will want to use something like this: 

    avrdude -c usbtiny -P usb -p atmega32u4

#### Advanced: Changing Fuses

If you're switching bootloaders, such as flashing QMK DFU on a Pro Micro, you will need to change the fuses, in additional to flashing the bootloader hex file.  This is because `caterina` (the Pro Micro bootloader) and `dfu` handle the startup routines differently, and that behavior is controlled by the fuses.  

!> This is one area that it is very important to be careful, as changing fuses is one of the ways that you can permanently brick your controller.  

For this, we are assuming the 5V 16MHz versions of the `atmega32u4` (such as the 5V Pro Micro).

For DFU on the `atmega32u4`, these are the fuse settings that you want: 

| Fuse     | Setting          |
|----------|------------------|
| Low      | `0x5E`           |
| High     | `0xD9` or `0x99` |
| Extended | `0xC3`           |

The High fuse can be 0xD9 or 0x99. The difference is that 0xD9 disables JTAG, which QMK Firmware disables via software as well, while 0x99 doesn't disable JTAG. 

To set this add `-U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xC3:m` to your command.  So the final command should look something like: 

    avrdude -c avrisp -P COM3 -p atmega32u4 -U flash:w:main.hex:i -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xC3:m

For Caterina on the `atmega32u4`, these are the fuse settings that you want: 

| Fuse     | Setting|
|----------|--------|
| Low      | `0xFF` |
| High     | `0xD8` |
| Extended | `0xCB` |

To set this add `-U lfuse:w:0xFF:m -U hfuse:w:0xD8:m -U efuse:w:0xCB:m` to your command.  So the final command should look something like: 

    avrdude -c avrisp -P COM3 -p atmega32u4 -U flash:w:main.hex:i -U lfuse:w:0xFF:m -U hfuse:w:0xD8:m -U efuse:w:0xCB:m


If you are using a different controller or want different configuration, you can use [this AVR Fuse Calculator](http://www.engbedded.com/fusecalc/) to find a better value for you.

## Help

If you have any questions/problems, feel free to [open an issue](https://github.com/qmk/qmk_firmware/issues/new)!
ご質問・ご不明な点がありましたら、お気軽に[open an issue](https://github.com/qmk/qmk_firmware/issues/new)まで!
