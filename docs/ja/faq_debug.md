# デバッグの FAQ

<!---
  original document: d598f01cb:docs/faq_debug.md
  git diff d598f01cb HEAD docs/faq_debug.md | cat
-->

このページは、キーボードのトラブルシューティングについての様々な一般的な質問を説明します。

# デバッグコンソール

## `hid_listen` デバイスを認識できない
デバイスのデバッグコンソールの準備ができていない場合、以下のように表示されます:

```
Waiting for device:.........
```

デバイスが接続されると、*hid_listen* がデバイスを見つけ、以下のメッセージが表示されます:

```
Waiting for new device:.........................
Listening:
```

この 'Listening:' のメッセージが表示されない場合は、[Makefile] を `CONSOLE_ENABLE=yes` に設定してビルドしてみてください

Linux のような OS でデバイスにアクセスするには、権限が必要かもしれません。
- `sudo hid_listen` を試してください

## コンソールにメッセージが表示されない
以下を調べてください:
- *hid_listen* がデバイスを検出する。上記を見てください。
- **Magic**+d を使ってデバッグを有効にする。[マジックコマンド](https://github.com/tmk/tmk_keyboard#magic-commands)を見てください。
- `debug_enable=true` を設定します。[テストとデバッグ](ja/newbs_testing_debugging.md#debugging)を見てください
- デバッグ print の代わりに 'print' 関数を使ってみてください。**common/print.h** を見てください。
- コンソール機能を持つ他のデバイスを切断します。[Issue #97](https://github.com/tmk/tmk_keyboard/issues/97) を見てください。

## Linux あるいは UNIX のようなシステムは Super User 権限を必要とします
権限付きで *hid_listen* を実行するために 'sudo' を使ってください。
```
$ sudo hid_listen
```

または rules ディレクトリにファイルを置いて、TMK デバイスのための *udev rule* を追加します。ディレクトリは各システムで異なるかもしれません。

File: /etc/udev/rules.d/52-tmk-keyboard.rules (Ubuntu の場合)
```
# tmk keyboard products     https://github.com/tmk/tmk_keyboard
SUBSYSTEMS=="usb", ATTRS{idVendor}=="feed", MODE:="0666"
```

***

# 雑多なこと
## 安全性の考慮

あなたはおそらくキーボードを"文鎮化"したくないでしょう。ファームウェアを書き換えられないようにします。リスクがあまりに高い(そしてそうでないかもしれない)ものの一部のリストを示します。

- キーボードマップに RESET が含まれない場合、DFU モードに入るには、PCB のリセットボタンを押す必要があります。底部のネジを外す必要があります。
- tmk_core / common ファイルを触るとキーボードが操作不能になるかもしれません。
- Too large a .hex file is trouble; `make dfu` will erase the block,
test the size (oops, wrong order!), which errors out, failing to
flash the keyboard, leaving it in DFU mode.
   - To this end, note that the maximum .hex file size on Planck is
7000h (28672 decimal)

```
Linking: .build/planck_rev4_cbbrowne.elf                                                            [OK]
Creating load file for Flash: .build/planck_rev4_cbbrowne.hex                                       [OK]

Size after:
   text    data     bss     dec     hex filename
      0   22396       0   22396    577c planck_rev4_cbbrowne.hex
```

- 上のファイルのサイズは 22396/577ch で、28672/7000h より小さいです
- 適切な替わりの .hex ファイルがある限り、それをロードして再試行することができます
- あなたがキーボードの Makefile で指定したかもしれない一部のオプションは、余分なメモリを消費します; BOOTMAGIC_ENABLE、MOUSEKEY_ENABLE、EXTRAKEY_ENABLE、CONSOLE_ENABLE、API_SYSEX_ENABLE に注意してください
- DFU tools do /not/ allow you to write into the bootloader (unless
you throw in extra fruit salad of options), so there is little risk
there.
- EEPROM の書き込みサイクルは、約100000です。ファームウェアを繰り返し継続的に書き換えるべきではありません。それは最終的に EEPROM を焼き焦がします。

## NKRO が動作しません
最初に、**Makefile** 内でビルドオプション `NKRO_ENABLE` を使ってファームウェアをコンパイルする必要があります。

**NKRO** がまだ動作しない場合は、`Magic` **N** コマンド(デフォルトでは `LShift+RShift+N`)を試してみてください。**NKRO** モードと **6KRO** モードの間で一時的に切り替えるためにこのコマンドを使うことができます。**NKRO** が機能しない状況、特に BIOS の場合は **6KRO** モードに切り替える必要があります。

ファームウェアが `BOOTMAGIC_ENABLE` でビルドされた場合、`ブートマジック` **N** コマンドによって切り替える必要があります (デフォルトでは `Space+N`)。この設定は EEPROM に格納され、電源を入れ直しても保持されます。

https://github.com/tmk/tmk_keyboard#boot-magic-configuration---virtual-dip-switch


## TrackPoint はリセット回路が必要です (PS/2 マウスサポート)
リセット回路が無いとハードウェアの不適切な初期化のために一貫性の無い結果になります。TPM754 の回路図を見てください。

- http://geekhack.org/index.php?topic=50176.msg1127447#msg1127447
- http://www.mikrocontroller.net/attachment/52583/tpm754.pdf


## 16 を超えるマトリックの列を読み込めない
列が 16 を超える場合、[matrix.h] の `read_cols()` 内の `1<<16` の代わりに `1UL<<16` を使います。

C では、`1` は AVR の場合には [16 bit] である [int] 型の1つを意味し、15 を超えて左にシフトすることはできません。`1<<16` にする時に予期しないゼロが発生します。`1UL` で [unsigned long] 型を使う必要があります。

http://deskthority.net/workshop-f7/rebuilding-and-redesigning-a-classic-thinkpad-keyboard-t6181-60.html#p146279


## ブートローダの Jump が動作しない
**Makefile** 内でブートローダのサイズを適切に設定します。間違ったセクションサイズのブートローダは、おそらく**マジックコマンド**および**ブートマジック**で起動しません。
```
# Size of Bootloaders in bytes:
#   Atmel DFU loader(ATmega32U4)   4096
#   Atmel DFU loader(AT90USB128)   8192
#   LUFA bootloader(ATmega32U4)    4096
#   Arduino Caterina(ATmega32U4)   4096
#   USBaspLoader(ATmega***)        2048
#   Teensy   halfKay(ATmega32U4)   512
#   Teensy++ halfKay(AT90USB128)   2048
OPT_DEFS += -DBOOTLOADER_SIZE=4096
```
AVR ブートセクションのサイズは実際には **BOOTSZ** ヒューズを設定することで定義されます。MCU のデータシートを参照してください。
TMK は**バイト**を使いますが、データシートでは **Word** (2 バイト) のサイズとアドレスが使われることに注意してください。

AVR ブートセクションは以下のように Flash メモリの最後にあります。
```
byte     Atmel/LUFA(ATMega32u4)          byte     Atmel(AT90SUB1286)
0x0000   +---------------+               0x00000  +---------------+
         |               |                        |               |
         |               |                        |               |
         |  Application  |                        |  Application  |
         |               |                        |               |
         =               =                        =               =
         |               | 32KB-4KB               |               | 128KB-8KB
0x6000   +---------------+               0x1E000  +---------------+
         |  Bootloader   | 4KB                    |  Bootloader   | 8KB
0x7FFF   +---------------+               0x1FFFF  +---------------+


byte     Teensy(ATMega32u4)              byte     Teensy++(AT90SUB1286)
0x0000   +---------------+               0x00000  +---------------+
         |               |                        |               |
         |               |                        |               |
         |  Application  |                        |  Application  |
         |               |                        |               |
         =               =                        =               =
         |               | 32KB-512B              |               | 128KB-2KB
0x7E00   +---------------+               0x1FC00  +---------------+
         |  Bootloader   | 512B                   |  Bootloader   | 2KB
0x7FFF   +---------------+               0x1FFFF  +---------------+
```

詳細についてはこの議論を見てください。
https://github.com/tmk/tmk_keyboard/issues/179

TeensyUSB を使っている場合、ハードウェアリセットボタンによって RESET キーが機能しなくなる[既知のバグ](https://github.com/qmk/qmk_firmware/issues/164)があります。キーボードのプラグを抜いて再接続すると、問題が解決するはずです。

## 特別なエクストラキーが動作しない (システム、オーディオコントロールキー)
QMK でそれらを使うには、`rules.mk` 内で `EXTRAKEY_ENABLE` を定義する必要があります。

```
EXTRAKEY_ENABLE = yes          # オーディオ制御とシステム制御
```

## スリープから復帰しない

Windows では、**デバイスマネージャ**の**電源の管理**タブ内の `このデバイスで、コンピュータのスタンバイ状態を解除できるようにする` 設定を調べてください。また BIOS 設定も調べてください。

スリープ中に任意のキーを押すとホストが起動するはずです。

## Arduino を使っていますか？

**Arduino のピンの命名は実際のチップと異なることに注意してください。** 例えば、Arduino のピン `D0` は `PD0` ではありません。回路図を自身で確認してください。

- http://arduino.cc/en/uploads/Main/arduino-leonardo-schematic_3b.pdf
- http://arduino.cc/en/uploads/Main/arduino-micro-schematic.pdf

Arduino の Leonardo と micro には **ATMega32U4** があり、TMK に使うことができますが、Arduino のブートローダが問題になります。

## JTAG を有効にする

デフォルトでは、キーボードが起動するとすぐに JTAG デバッグインタフェースが無効になります。JTAG 対応 MCU は出荷時に `JTAGEN` ヒューズセットが搭載されており、ボードがスイッチマトリックス、LED などに使用している MCU の特定のピンを引き継ぎます。

JTAG を有効にしたい場合は、単に以下のものを `config.h` に追加します:

```c
#define NO_JTAG_DISABLE
```

## Lock キーの LED 表示を追加
CapsLock、ScrollLock および NumLock 用の独自の LED 表示が必要ですか？この投稿を見てください。

http://deskthority.net/workshop-f7/tmk-keyboard-firmware-collection-t4478-120.html#p191560

## Arduino Micro/Leonardo プログラム
リセットボタンを押して、8秒以内にこのようなコマンドを実行します。

```
avrdude -patmega32u4 -cavr109 -b57600 -Uflash:w:adb_usb.hex -P/dev/ttyACM0
```

デバイス名はシステムによって異なります。

http://arduino.cc/en/Main/ArduinoBoardMicro
https://geekhack.org/index.php?topic=14290.msg1563867#msg1563867


## USB 3 互換性
USB 3 ポートで問題がある人がいると聞きました。USB 2 ポートを試してください。


## Mac 互換性
### OS X 10.11 と Hub
https://geekhack.org/index.php?topic=14290.msg1884034#msg1884034


## BIOS (UEFI)/Resume (Sleep & Wake)/電源サイクル の問題
一部の人がキーボードが BIOS で動作しなくなった、または再開(電源サイクル)の後で動作しなくなったと報告しました。

今のところ、この問題の根本は明確ではないですが、幾つかのビルドオプションが関係しているようです。Makefileで、`CONSOLE_ENABLE`、`NKRO_ENABLE`、`SLEEP_LED_ENABLE` あるいは他のオプションを無効にしてみてください。

https://github.com/tmk/tmk_keyboard/issues/266
https://geekhack.org/index.php?topic=41989.msg1967778#msg1967778



## FLIP が動作しない
### `AtLibUsbDfu.dll` が見つかりません。
デバイスマネージャから現在のドライバを削除し、FLIP が提供するものを再インストールします。
http://imgur.com/a/bnwzy
