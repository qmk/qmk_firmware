# よくあるビルドの質問

このページはQMKのビルドに関する質問をカバーします。まだビルドをしていない場合は、[ビルド環境のセットアップ](getting_started_build_tools.md) および [Makeの指示](getting_started_make_guide.md)ガイドを読むべきです。

## Linuxでプログラムできません
デバイスを操作するには適切な権限が必要です。Linuxユーザに関しては、以下の`udev`ルールに関する指示を見てください。`udev`に問題がある場合は、回避策は`sudo` コマンドを使うことです。このコマンドに慣れていない場合は、`man sudo`を使ってマニュアルを確認するか、[このwebページを見てください](https://linux.die.net/man/8/sudo)。

コントローラがATMega32u4の場合の`sudo`の使い方の例:

    $ sudo dfu-programmer atmega32u4 erase --force
    $ sudo dfu-programmer atmega32u4 flash your.hex
    $ sudo dfu-programmer atmega32u4 reset

あるいは、単純に:

    $ sudo make <keyboard>:<keymap>:dfu

`make`を `sudo` で実行することは、一般的には良い考えでは***なく***、可能jであれば前者のメソッドのうちの1つを使うべきです。

### Linuxの`udev`ルール
Linuxでは、MCUにアクセスするには適切な権限が必要です。ファームウェアをフラッシュする時に`sudo`を使うか、`/etc/udev/rules.d/`にこれらのファイルを配置するかのどちらかを使うことができます。追加をしたら、以下を実行します:
```console
sudo udevadm control --reload-rules
sudo udevadm trigger
```

**/etc/udev/rules.d/50-atmel-dfu.rules:**
```
# Atmel ATMega32U4
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff4", MODE:="0666"
# Atmel USBKEY AT90USB1287
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ffb", MODE:="0666"
# Atmel ATMega32U2
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff0", MODE:="0666"
```

**/etc/udev/rules.d/52-tmk-keyboard.rules:**
```
# tmk keyboard products     https://github.com/tmk/tmk_keyboard
SUBSYSTEMS=="usb", ATTRS{idVendor}=="feed", MODE:="0666"
```
**/etc/udev/rules.d/54-input-club-keyboard.rules:**

```
# Input Club keyboard bootloader
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1c11", MODE:="0666"
```

**/etc/udev/rules.d/55-catalina.rules:**
```
# ModemManager should ignore the following devices
ATTRS{idVendor}=="2a03", ENV{ID_MM_DEVICE_IGNORE}="1"
ATTRS{idVendor}=="2341", ENV{ID_MM_DEVICE_IGNORE}="1"
```

**注意:** ModemManager フィルタリングは厳格モードで無い場合のみ動作します。以下のコマンドはその設定を更新することができます:
```console
sudo sed -i 's/--filter-policy=strict/--filter-policy=default/' /lib/systemd/system/ModemManager.service
sudo systemctl daemon-reload
sudo systemctl restart ModemManager
```

**/etc/udev/rules.d/56-dfu-util.rules:**
```
# stm32duino
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1eaf", ATTRS{idProduct}=="0003", MODE:="0666"
# Generic stm32
SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="df11", MODE:="0666"
```

### Linuxのブートローダ モードでSerialデバイスが検知されない
カーネルがデバイスの適切なサポートを持つことを確認してください。デバイスが、Pro Micro (Atmega32u4)のようなUSB ACMを使う場合、`CONFIG_USB_ACM=y`を含めるようにしてください。他のデバイスは`USB_SERIAL`およびそのサブオプションを必要とするかもしれません。

## DFUブートローダの不明なデバイス

Windows上でキーボードをフラッシュする時に発生する問題は、ブートローダに間違ったドライバがインストールされているか、全くインストールされていないかによるものがほとんどです。

QMK インストール スクリプト (MSYS2あるいはWSL内の`qmk_firmware` ディレクトリから`./util/qmk_install.sh`)を再実行するか、QMK Toolbox の再インストールでこの問題が解決するかもしれません。別のやり方として、手動で[`qmk_driver_installer`](https://github.com/qmk/qmk_driver_installer) パッケージをダウンロードして実行することができます。

それでもうまく行かない場合は、Zadigをダウンロードして実行する必要があります。詳細な情報は [Zadigを使ったブートローダ ドライバのインストール](driver_installation_zadig.md)を見てください。

## WINAVR は非推奨です。
もう推奨されなくなり、何らかの問題を起こすかもしれません。
[TMK Issue #99](https://github.com/tmk/tmk_keyboard/issues/99)を見てください。

## USB VID と PID
`config.h`を編集することで必要なIDを使うことができます。おそらく未使用のIDを使っても、他の製品との衝突の可能性が低いことを除いて、実際には問題はありません。

QMKのほとんどのボードは、vendor IDとして、`0xFEED`を使います。ユニークなIDを選択したことを確認するために、他のキーボードを調べるべきです。

またこれも見てください。
https://github.com/tmk/tmk_keyboard/issues/150

ここで本当にユニークな VID:PID を買うことができます。個人的な使用にはこれは必要ないと思います。
- http://www.obdev.at/products/vusb/license.html
- http://www.mcselec.com/index.php?page=shop.product_details&flypage=shop.flypage&product_id=92&option=com_phpshop&Itemid=1

## Cortex: `cstddef: No such file or directory`
Ubuntu 14.04のGCC 4.8にはこの問題があり、このPPAを使って4.9に更新する必要がありました。
https://launchpad.net/~terry.guo/+archive/ubuntu/gcc-arm-embedded

https://github.com/tmk/tmk_keyboard/issues/212
https://github.com/tmk/tmk_keyboard/wiki/mbed-cortex-porting#compile-error-cstddef
https://developer.mbed.org/forum/mbed/topic/5205/

## `clock_prescale_set` と `clock_div_1` が利用不可能
ツールチェーンが古すぎるため、MCUをサポートできません。例えば WinAVR 20100110 は ATMega32u2 をサポートしません。

```
Compiling C: ../../tmk_core/protocol/lufa/lufa.c
avr-gcc -c -mmcu=atmega32u2 -gdwarf-2 -DF_CPU=16000000UL -DINTERRUPT_CONTROL_ENDPOINT -DBOOTLOADER_SIZE=4096 -DF_USB=16000000UL -DARCH=ARCH_AVR8 -DUSB_DEVICE_ONLY -DUSE_FLASH_DESCRIPTORS -DUSE_STATIC_OPTIONS="(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)" -DFIXED_CONTROL_ENDPOINT_SIZE=8  -DFIXED_NUM_CONFIGURATIONS=1 -DPROTOCOL_LUFA -DEXTRAKEY_ENABLE -DCONSOLE_ENABLE -DCOMMAND_ENABLE -DVERSION=unknown -Os -funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections -fno-inline-small-functions -fpack-struct -fshort-enums -fno-strict-aliasing -Wall -Wstrict-prototypes -Wa,-adhlns=obj_alps64/protocol/lufa/lufa.lst -I. -I../../tmk_core -I../../tmk_core/protocol/lufa -I../../tmk_core/protocol/lufa/LUFA-git -I../../tmk_core/common -std=gnu99 -include config.h -MMD -MP -MF .dep/obj_alps64_protocol_lufa_lufa.o.d  ../../tmk_core/protocol/lufa/lufa.c -o obj_alps64/protocol/lufa/lufa.o
../../tmk_core/protocol/lufa/lufa.c: In function 'setup_mcu':
../../tmk_core/protocol/lufa/lufa.c:575: warning: implicit declaration of function 'clock_prescale_set'
../../tmk_core/protocol/lufa/lufa.c:575: error: 'clock_div_1' undeclared (first use in this function)
../../tmk_core/protocol/lufa/lufa.c:575: error: (Each undeclared identifier is reported only once
../../tmk_core/protocol/lufa/lufa.c:575: error: for each function it appears in.)
make: *** [obj_alps64/protocol/lufa/lufa.o] Error 1
```


## AVRのためのBOOTLOADER_SIZE
Teensy2.0++ ブートローダのサイズは2048バイトであることに注意してください。一部のMakefileには間違ったコメントがあります。

```
# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 2048
#   Atmel DFU loader 4096       (TMK Alt Controller)
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=2048
```

## MacOSでの`avr-gcc: internal compiler error: Abort trap: 6 (program cc1)` 
これはbrewでの更新に関する問題で、avr-gccが依存するシムリンクを壊します。

解決法はすべr手の影響を受けたモジュールを削除し再インストールすることです。

```
brew rm avr-gcc
brew rm dfu-programmer
brew rm dfu-util
brew rm gcc-arm-none-eabi
brew rm avrdude
brew install avr-gcc
brew install dfu-programmer
brew install dfu-util
brew install gcc-arm-none-eabi
brew install avrdude
```

### avr-gcc 8.1 と LUFA

avr-gcc を 7 より上に更新した場合、LUFAに関連するエラーが表示されるかもしれません。例えば:

`lib/lufa/LUFA/Drivers/USB/Class/Device/AudioClassDevice.h:380:5: error: 'const' attribute on function returning 'void'`

今のところ、brewで avr-gcc を 7 にロールバックする必要があります。

```
brew uninstall --force avr-gcc
brew install avr-gcc@8
brew link --force avr-gcc@8
```

### キーボードをフラッシュしただけで何も起こらない/キーの押下が登録されない - ARMでも同じ (rev6 planck, clueboard 60, hs60v2 など) (Feb 2019)
ARMベースのチップ上でEEPROMがどのように動作するかにより、保存された設定が無効になる場合があります。これはデフォルト レイヤに影響し、まだ解明中の特定の環境下でキーボー尾が不安定になるかも*しれません*。EEPROMの再設定でこれが修正されます。

[Planck rev6 reset EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/539284620861243409/planck_rev6_default.bin) をeeprom再設定を強制するために使うことができます。このイメージをフラッシュした後で、通常のファームウェアをフラッシュすると、キーボードが_通常_ の正常な順序に復元されます。
[Preonic rev3 reset EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/537849497313738762/preonic_rev3_default.bin)

いずれかの形式でブートマジックが有効になっている場合は、これも実行できるはずです (実行方法の詳細については、[Bootmagic ドキュメント](feature_bootmagic.md)を見てください)。
