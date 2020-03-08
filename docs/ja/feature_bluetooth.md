# Bluetooth

<!---
  original document: 0d3f0889c:docs/feature_bluetooth.md
  git diff 0d3f0889c HEAD -- docs/feature_bluetooth.md | cat
-->

## Bluetooth の既知のサポートハードウェア

現在のところ Bluetooth のサポートは AVR ベースのチップに限られます。Bluetooth 2.1 については、QMK は RN-42 モジュールと、Bluefruit EZ-Key をサポートしますが、後者はもう生産されていません。より最近の BLE プロトコルについては、現在のところ Adafruit Bluefruit SPI Friend のみが直接サポートされています。iOS デバイスに接続するには、BLE が必要です。iOS はマウス入力をサポートしないことに注意してください。

| ボード | Bluetooth プロトコル | 接続タイプ | rules.mk | Bluetooth チップ |
|----------------------------------------------------------------|----------------------------|----------------|---------------------------|--------------|
| [Adafruit EZ-Key HID](https://www.adafruit.com/product/1535) | Bluetooth Classic | UART | `BLUETOOTH = AdafruitEZKey` |  |
| Roving Networks RN-42 (Sparkfun Bluesmirf) | Bluetooth Classic | UART | `BLUETOOTH = RN42` | RN-42 |
| [Bluefruit LE SPI Friend](https://www.adafruit.com/product/2633) | Bluetooth Low Energy | SPI | `BLUETOOTH = AdafruitBLE` | nRF51822 |

まだサポートされていませんが、可能性のあるもの:
* [Bluefruit LE UART Friend](https://www.adafruit.com/product/2479)。[tmk 実装がおそらく見つかります](https://github.com/tmk/tmk_keyboard/issues/514)
* RN-42 ファームウェアが書き込まれた HC-05 ボード。どちらも明らかに CSR BC417 チップを使っています。RN-42 ファームウェアを使って書き込むと、HID 機能が提供されます。
* Sparkfun Bluetooth Mate
* HM-13 ベースのボード

### Adafruit BLE SPI Friend
現在のところ QMK によってサポートされている唯一の bluetooth チップセットは、Adafruit Bluefruit SPI Friend です。Adafruit のカスタムファームウェアを実行する Nordic nRF5182 ベースのチップです。データは Hardware SPI を介した Adafruit の SDEP を使って転送されます。[Feather 32u4 Bluefruit LE](https://www.adafruit.com/product/2829) は Adafruit ファームウェアを搭載した Nordic BLE チップに SPI 経由で接続された AVR mcu であるため、サポートされます。SPI friend を使ってカスタムボードを構築する場合、32u4 feather が使用するピン選択を使うのが最も簡単ですが、以下の定義で config.h オプションでピンを変更することができます:
* #define AdafruitBleResetPin D4
* #define AdafruitBleCSPin    B4
* #define AdafruitBleIRQPin   E6

Bluefruit UART friend は SPI friend に変換することができますが、これには再書き込みと MDBT40 チップへ直接はんだ付けする[必要があります](https://github.com/qmk/qmk_firmware/issues/2274)。

## Adafruit EZ-Key hid
これには[ハードウェアの変更](https://www.reddit.com/r/MechanicalKeyboards/comments/3psx0q/the_planck_keyboard_with_bluetooth_guide_and/?ref=search_posts)が必要ですが、Makefile を使って有効にすることができます。ファームウェアは引き続き USB 経由で文字を出力するため、コンピュータ経由で充電する場合は注意してください。任意にオフにするために Bluefruit 上にスイッチを持つことは理にかなっています。


<!-- FIXME: Document bluetooth support more completely. -->
## Bluetooth の Rules.mk オプション
これらのうちの1つだけを使ってください
* BLUETOOTH_ENABLE = yes (レガシーオプション)
* BLUETOOTH = RN42
* BLUETOOTH = AdafruitEZKey
* BLUETOOTH = AdafruitBLE

## Bluetooth キーコード

これは複数のキーボードの出力が選択できる場合に使われます。現在のところ、これは USB と Bluetooth の両方をサポートするキーボードで、それらの間の切り替えのみが可能です。

| 名前 | 説明 |
|----------|----------------------------------------------|
| `OUT_AUTO` | USB と Bluetooth を自動的に切り替える |
| `OUT_USB` | USB のみ |
| `OUT_BT` | Bluetooth のみ |
