# その他の FAQ

<!---
  original document: 0.12.45:docs/faq_misc.md
  git diff 0.12.45 HEAD -- docs/faq_misc.md | cat
-->

## どうやってキーボードをテストすればいいですか？ :id=testing

通常、キーボードのテストは非常に簡単です。全てのキーをひとつずつ押して、期待するキーが送信されることを確認します。例え QMK で動作していない場合でも、[QMK Configurator](https://config.qmk.fm/#/test/) のテストモードを使用すると、キーボードをチェックできます。

## 安全性の考慮

あなたはおそらくキーボードを「文鎮化」したくないでしょう。文鎮化するとファームウェアを書き換えられないようになります。リスクがあまりに高い(そしてそうでないかもしれない)ものの一部のリストを示します。

- キーボードマップに RESET が含まれない場合、DFU モードに入るには、PCB のリセットボタンを押す必要があります。底部のネジを外す必要があります。
- tmk_core / common にあるファイルを触るとキーボードが操作不能になるかもしれません。
- .hex ファイルが大きすぎると問題を引き起こします; `make dfu` コマンドはブロックを削除し、サイズを検査し(おっと、間違った順序です！)、エラーを出力し、
キーボードへの書き込みに失敗し、DFU モードのままになります。
  - この目的のためには、Planck の最大の .hex ファイルサイズは 7000h (10進数で28672)であることに注意してください。

```
Linking: .build/planck_rev4_cbbrowne.elf                                                            [OK]
Creating load file for Flash: .build/planck_rev4_cbbrowne.hex                                       [OK]

Size after:
   text    data     bss     dec     hex filename
      0   22396       0   22396    577c planck_rev4_cbbrowne.hex
```

  - 上のファイルのサイズは 22396/577ch で、28672/7000h より小さいです。
  - 適切な代わりの .hex ファイルがある限り、それをロードして再試行することができます。
  - あなたがキーボードの Makefile で指定したかもしれない一部のオプションは、余分なメモリを消費します; BOOTMAGIC_ENABLE、MOUSEKEY_ENABLE、EXTRAKEY_ENABLE、CONSOLE_ENABLE、API_SYSEX_ENABLE に注意してください。
- DFU ツールは(オプションの余計なフルーツサラダを投げ込まない限り)ブートローダに書き込むことを許可しないので、ここにはリスクはほとんどありません。
- EEPROM の書き込みサイクルは、約100000(10万)です。ファームウェアを繰り返し継続的に書き換えるべきではありません。それは最終的に EEPROM を焼き焦がします。

## NKRO が動作しません
最初に、**Makefile** 内でビルドオプション `NKRO_ENABLE` を使ってファームウェアをコンパイルする必要があります。

**NKRO** がまだ動作しない場合は、`Magic` **N** コマンド(デフォルトでは `LShift+RShift+N`)を試してみてください。**NKRO** モードと **6KRO** モード間を一時的に切り替えるためにこのコマンドを使うことができます。**NKRO** が機能しない状況、特に BIOS の場合は **6KRO** モードに切り替える必要があります。


## トラックポイントははリセット回路が必要です (PS/2 マウスサポート)
リセット回路が無いとハードウェアの不適切な初期化のために一貫性の無い結果になります。TPM754 の回路図を見てください:

- https://geekhack.org/index.php?topic=50176.msg1127447#msg1127447
- https://www.mikrocontroller.net/attachment/52583/tpm754.pdf


## 16 を超えるマトリックの列を読み込めない
列が 16 を超える場合、[matrix.h] の `read_cols()` 内の `1<<16` の代わりに `1UL<<16` を使ってください。

C では、AVR の場合 `1` は [16 bit] である [int] 型の1を意味し、15を超えて左にシフトすることはできません。従って、`1<<16` を計算すると予期せずゼロになります。これを回避するには `1UL` として [unsigned long] 型を使う必要があります。

https://deskthority.net/workshop-f7/rebuilding-and-redesigning-a-classic-thinkpad-keyboard-t6181-60.html#p146279

## 特別なエクストラキーが動作しない(システム、オーディオコントロールキー)
QMK でそれらを使うには、`rules.mk` 内で `EXTRAKEY_ENABLE` を定義する必要があります。

```
EXTRAKEY_ENABLE = yes          # オーディオ制御とシステム制御
```

## スリープから復帰しない

**デバイスマネージャ**の**電源の管理**タブ内の `このデバイスで、コンピュータのスタンバイ状態を解除できるようにする` 設定を調べてください。また BIOS 設定も調べてください。スリープ中に任意のキーを押すとホストが起動するはずです。

## Arduino を使っていますか？

**Arduino のピンの命名は実際のチップと異なることに注意してください。** 例えば、Arduino のピン `D0` は `PD0` ではありません。回路図を自身で確認してください。

- https://arduino.cc/en/uploads/Main/arduino-leonardo-schematic_3b.pdf
- https://arduino.cc/en/uploads/Main/arduino-micro-schematic.pdf

Arduino の Leonardo と micro には **ATMega32U4** が載っていて、TMK 用に使うことができますが、Arduino のブートローダが問題になることがあります。

## JTAG を有効にする

デフォルトでは、キーボードが起動するとすぐに JTAG デバッグインタフェースが無効になります。JTAG 対応 MCU は `JTAGEN` ヒューズが設定された状態で出荷されており、キーボードがスイッチマトリックス、LED などに使用している可能性のある MCU の特定のピンを乗っ取ります。

JTAG を有効にしたままにしたい場合は、単に以下のものを `config.h` に追加します:

```c
#define NO_JTAG_DISABLE
```

## USB 3 の互換性
一部の問題は、USB 3.x ポートから USB 2.0 ポートに切り替えることで修正できます。


## Mac の互換性
### OS X 10.11 と Hub
こちらを見てください: https://geekhack.org/index.php?topic=14290.msg1884034#msg1884034


## BIOS (UEFI) 設定/リジューム (スリープとウェークアップ)/電源サイクルの問題
一部の人がキーボードが BIOS で動作しなくなった、またはリジューム(電源サイクル)の後で動作しなくなったと報告しました。

今のところ、この問題の根本は明確ではないですが、幾つかのビルドオプションが関係しているようです。Makefile で、`CONSOLE_ENABLE`、`NKRO_ENABLE`、`SLEEP_LED_ENABLE` あるいは他のオプションを無効にしてみてください。

より詳しい情報:
- https://github.com/tmk/tmk_keyboard/issues/266
- https://geekhack.org/index.php?topic=41989.msg1967778#msg1967778
