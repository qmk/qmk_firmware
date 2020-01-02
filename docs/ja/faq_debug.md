# デバッグの FAQ

<!---
  original document: 376419a4f:docs/faq_debug.md
  git diff 376419a4f HEAD docs/faq_debug.md | cat
-->

このページは、キーボードのトラブルシューティングについての様々な一般的な質問を説明します。

# デバッグコンソール

## `hid_listen` がデバイスを認識できない
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

## Linux あるいは UNIX のようなシステムはスーパーユーザ権限を必要とします
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

あなたはおそらくキーボードを「文鎮化」したくないでしょう。文鎮化するとファームウェアを書き換えられないようになります。リスクがあまりに高い(そしてそうでないかもしれない)ものの一部のリストを示します。

- キーボードマップに RESET が含まれない場合、DFU モードに入るには、PCB のリセットボタンを押す必要があります。底部のネジを外す必要があります。
- tmk_core / common にあるファイルを触るとキーボードが操作不能になるかもしれません。
- .hex ファイルが大きすぎると問題を引き起こします; `make dfu` コマンドはブロックを削除し、
サイズを検査し(おっと、間違った順序です！)、エラーを出力し、
キーボードへの書き込みに失敗し、DFU モードのままになります。
   - この目的のためには、Planck の最大の .hex ファイルサイズは 7000h (10進数で28672)であることに注意してください。

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
- DFU ツールは(オプションの余計なフルーツサラダを投げ込まない限り)ブートローダに書き込むことを許可しないので、
ここにはリスクはほとんどありません。
- EEPROM の書き込みサイクルは、約100000です。ファームウェアを繰り返し継続的に書き換えるべきではありません。それは最終的に EEPROM を焼き焦がします。

## NKRO が動作しません
最初に、**Makefile** 内でビルドオプション `NKRO_ENABLE` を使ってファームウェアをコンパイルする必要があります。

**NKRO** がまだ動作しない場合は、`Magic` **N** コマンド(デフォルトでは `LShift+RShift+N`)を試してみてください。**NKRO** モードと **6KRO** モード間を一時的に切り替えるためにこのコマンドを使うことができます。**NKRO** が機能しない状況、特に BIOS の場合は **6KRO** モードに切り替える必要があります。

ファームウェアを `BOOTMAGIC_ENABLE` でビルドした場合、`ブートマジック` **N** コマンドで切り替える必要があります (デフォルトでは `Space+N`)。この設定は EEPROM に格納され、電源を入れ直しても保持されます。

https://github.com/tmk/tmk_keyboard#boot-magic-configuration---virtual-dip-switch


## TrackPoint はリセット回路が必要です (PS/2 マウスサポート)
リセット回路が無いとハードウェアの不適切な初期化のために一貫性の無い結果になります。TPM754 の回路図を見てください。

- http://geekhack.org/index.php?topic=50176.msg1127447#msg1127447
- http://www.mikrocontroller.net/attachment/52583/tpm754.pdf


## 16 を超えるマトリックの列を読み込めない
列が 16 を超える場合、[matrix.h] の `read_cols()` 内の `1<<16` の代わりに `1UL<<16` を使ってください。

C では、AVR の場合 `1` は [16 bit] である [int] 型の1を意味し、15 を超えて左にシフトすることはできません。`1<<16` すると予期しないゼロが発生します。`1UL` として [unsigned long] 型を使う必要があります。

http://deskthority.net/workshop-f7/rebuilding-and-redesigning-a-classic-thinkpad-keyboard-t6181-60.html#p146279

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

Arduino の Leonardo と micro には **ATMega32U4** が載っていて、TMK 用に使うことができますが、Arduino のブートローダが問題になることがあります。

## JTAG を有効にする

デフォルトでは、キーボードが起動するとすぐに JTAG デバッグインタフェースが無効になります。JTAG 対応 MCU は `JTAGEN` ヒューズが設定された状態で出荷されており、キーボードがスイッチマトリックス、LED などに使用している可能性のある MCU の特定のピンを乗っ取ります。

JTAG を有効にしたままにしたい場合は、単に以下のものを `config.h` に追加します:

```c
#define NO_JTAG_DISABLE
```

## USB 3 の互換性
USB 3 ポートで問題がある人がいると聞きました。USB 2 ポートを試してください。


## Mac の互換性
### OS X 10.11 と Hub
https://geekhack.org/index.php?topic=14290.msg1884034#msg1884034


## リジューム (スリープとウェークアップ)/電源サイクルの問題
一部の人がキーボードが BIOS で動作しなくなった、またはリジューム(電源サイクル)の後で動作しなくなったと報告しました。

今のところ、この問題の根本は明確ではないですが、幾つかのビルドオプションが関係しているようです。Makefileで、`CONSOLE_ENABLE`、`NKRO_ENABLE`、`SLEEP_LED_ENABLE` あるいは他のオプションを無効にしてみてください。

https://github.com/tmk/tmk_keyboard/issues/266
https://geekhack.org/index.php?topic=41989.msg1967778#msg1967778



## FLIP が動作しない
### `AtLibUsbDfu.dll` が見つかりません
デバイスマネージャから現在のドライバを削除し、FLIP が提供するものを再インストールします。
http://imgur.com/a/bnwzy
