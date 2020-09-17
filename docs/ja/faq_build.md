# よくあるビルドの質問

<!---
  original document: 0.9.43:docs/faq_build.md
  git diff 0.9.43 HEAD -- docs/faq_build.md | cat
-->

このページは QMK のビルドに関する質問を説明します。まだビルドをしていない場合は、[ビルド環境のセットアップ](ja/getting_started_build_tools.md) および [Make 手順](ja/getting_started_make_guide.md)ガイドを読むべきです。

## Linux でプログラムできません
デバイスを操作するには適切な権限が必要です。Linux ユーザの場合は、以下の `udev` ルールに関する指示を見てください。`udev` に問題がある場合は、回避策は `sudo` コマンドを使うことです。このコマンドに慣れていない場合は、`man sudo` コマンドでマニュアルを確認するか、[この web ページを見てください](https://linux.die.net/man/8/sudo)。

コントローラが ATMega32u4 の場合の `sudo` の使い方の例:

    $ sudo dfu-programmer atmega32u4 erase --force
    $ sudo dfu-programmer atmega32u4 flash your.hex
    $ sudo dfu-programmer atmega32u4 reset

あるいは、単純に:

    $ sudo make <keyboard>:<keymap>:dfu

`make` を `sudo` で実行することは一般的には良い考えでは***なく***、可能であれば前者の方法のいずれかを使うべきです。

### Linux の `udev` ルール
Linux では、MCU にアクセスするには適切な権限が必要です。ファームウェアを書き込む時に `sudo` を使うか、`/etc/udev/rules.d/` にこれらのファイルを配置することで、アクセスすることができます。権限の追加が完了したら、以下を実行します:
```console
sudo udevadm control --reload-rules
sudo udevadm trigger
```

**/etc/udev/rules.d/50-atmel-dfu.rules:**
```
# Atmel ATMega32U4
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff4", TAG+="uaccess", RUN{builtin}+="uaccess"
# Atmel USBKEY AT90USB1287
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ffb", TAG+="uaccess", RUN{builtin}+="uaccess"
# Atmel ATMega32U2
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff0", TAG+="uaccess", RUN{builtin}+="uaccess"
```

**/etc/udev/rules.d/54-input-club-keyboard.rules:**

```
# Input Club keyboard bootloader
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1c11", ATTRS{idProduct}=="b007", TAG+="uaccess", RUN{builtin}+="uaccess"
```

**/etc/udev/rules.d/55-caterina.rules:**
```
# ModemManager should ignore the following devices
SUBSYSTEMS=="usb", ATTRS{idVendor}=="2a03", ATTRS{idProduct}=="0036", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="0036", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1b4f", ATTRS{idProduct}=="9205", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1b4f", ATTRS{idProduct}=="9203", TAG+="uaccess", RUN{builtin}+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"
```

**注意:** 古い(1.12以前の) ModemManager では、フィルタリングは厳密なモードではない場合にのみ動作し、以下のコマンドはその設定を更新することができます。
```console
printf '[Service]\nExecStart=\nExecStart=/usr/sbin/ModemManager --filter-policy=default' | sudo tee /etc/systemd/system/ModemManager.service.d/policy.conf
sudo systemctl daemon-reload
sudo systemctl restart ModemManager
```

**/etc/udev/rules.d/56-dfu-util.rules:**
```
# stm32duino
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1eaf", ATTRS{idProduct}=="0003", TAG+="uaccess", RUN{builtin}+="uaccess"
# Generic stm32
SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="df11", TAG+="uaccess", RUN{builtin}+="uaccess"
```

**/etc/udev/rules.d/57-bootloadhid.rules:**
```
# bootloadHID
SUBSYSTEMS=="usb", ATTRS{idVendor}=="16c0", ATTRS{idProduct}=="05df", TAG+="uaccess", RUN{builtin}+="uaccess"
```

### Linux のブートローダモードで Serial デバイスが検知されない
カーネルがデバイスを適切にサポートしていることを確認してください。デバイスが、Pro Micro (Atmega32u4) のように USB ACM を使う場合、`CONFIG_USB_ACM=y` を含めるようにしてください。他のデバイスは `USB_SERIAL` およびそのサブオプションを必要とするかもしれません。

## DFU ブートローダの不明なデバイス

Windows 上でキーボードを書き込む時に発生する問題は、ブートローダ用に間違ったドライバがインストールされているか、全くインストールされていないかによるものがほとんどです。

QMK インストールスクリプト (MSYS2 あるいは WSL 内の `qmk_firmware` ディレクトリから `./util/qmk_install.sh`) を再実行するか、QMK Toolbox の再インストールでこの問題が解決するかもしれません。別のやり方として、手動で [`qmk_driver_installer`](https://github.com/qmk/qmk_driver_installer) パッケージをダウンロードして実行することができます。

それでもうまく行かない場合は、Zadig をダウンロードして実行する必要があります。詳細な情報は [Zadig を使ったブートローダドライバのインストール](ja/driver_installation_zadig.md)を見てください。

## USB VID と PID
`config.h` を編集することで任意の ID を使うことができます。おそらく未使用の ID を使っても、他の製品と衝突するとても低い可能性があることを除いて、実際には問題はありません。

QMK のほとんどのキーボードは、vendor ID として、`0xFEED` を使います。他のキーボードを調べて、ユニークな ID を選択してください。

またこれも見てください。
https://github.com/tmk/tmk_keyboard/issues/150

ここで本当にユニークな VID:PID を買うことができます。個人的な使用にはこれは必要ないと思います。
- http://www.obdev.at/products/vusb/license.html
- http://www.mcselec.com/index.php?page=shop.product_details&flypage=shop.flypage&product_id=92&option=com_phpshop&Itemid=1

## AVR のための BOOTLOADER_SIZE
Teensy2.0++ ブートローダのサイズは 2048 バイトであることに注意してください。一部の Makefile には間違ったコメントがあります。

```
# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 2048
#   Atmel DFU loader 4096       (TMK Alt Controller)
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=2048
```

## MacOS での `avr-gcc: internal compiler error: Abort trap: 6 (program cc1)` 

これは brew での更新に関する問題で、avr-gcc が依存するシンボリックリンクを壊します。

解決法は全ての影響を受けたモジュールを削除し再インストールすることです。

```
brew rm avr-gcc avr-gcc@8 dfu-programmer dfu-util gcc-arm-none-eabi arm-gcc-bin@8 avrdude qmk
brew install qmk/qmk/qmk
brew link --force avr-gcc@8
brew link --force arm-gcc-bin@8
```

### `avr-gcc` と LUFA

`avr-gcc` を更新し、LUFA に関連するエラーが表示された場合、例えば:

`lib/lufa/LUFA/Drivers/USB/Class/Device/AudioClassDevice.h:380:5: error: 'const' attribute on function returning 'void'`

今のところ、Homebrew で `avr-gcc` を 8 にロールバックする必要があります。

```
brew uninstall --force avr-gcc
brew install avr-gcc@8
brew link --force avr-gcc@8
```

### キーボードに書き込んだが何も起こらない、あるいはキーの押下が登録されない - ARM (rev6 planck、clueboard 60、hs60v2 など) でも同じ (Feb 2019)
ARM ベースのチップ上での EEPROM の動作によって、保存された設定が無効になる場合があります。これはデフォルトレイヤに影響し、まだ調査中の特定の環境下でキーボードが使えなくなる*しれません*。EEPROM のリセットでこれが修正されます。

[Planck rev6 reset EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/539284620861243409/planck_rev6_default.bin) を使って eeprom のリセットを強制することができます。このイメージを書き込んだ後で、通常のファームウェアを書き込むと、キーボードが_通常_ の動作順序に復元されます。
[Preonic rev3 reset EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/537849497313738762/preonic_rev3_default.bin)

いずれかの形式でブートマジックが有効になっている場合は、これも実行できるはずです (実行方法の詳細については、[ブートマジックドキュメント](ja/feature_bootmagic.md)とキーボード情報を見てください)。
