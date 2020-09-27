# Bluetooth

<!---
  original document: 0.9.0:docs/feature_bluetooth.md
  git diff 0.9.0 HEAD -- docs/feature_bluetooth.md | cat
-->

## Bluetooth の既知のサポートハードウェア

現在のところ Bluetooth のサポートは AVR ベースのチップに限られます。Bluetooth 2.1 については、QMK は RN-42 モジュールをサポートします。より最近の BLE プロトコルについては、現在のところ Adafruit Bluefruit SPI Friend のみが直接サポートされています。iOS デバイスに接続するには、BLE が必要です。iOS はマウス入力をサポートしないことに注意してください。

| ボード | Bluetooth プロトコル | 接続タイプ | rules.mk | Bluetooth チップ |
|----------------------------------------------------------------|----------------------------|----------------|---------------------------|--------------|
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

Bluefruit UART friend は SPI friend に変換することができますが、これにはMDBT40 チップへの直接の再書き込みとはんだ付けが[必要です](https://github.com/qmk/qmk_firmware/issues/2274)。

<!-- FIXME: Document bluetooth support more completely. -->
## Bluetooth の Rules.mk オプション
これらのうちの1つだけを使ってください
* BLUETOOTH_ENABLE = yes (レガシーオプション)
* BLUETOOTH = RN42
* BLUETOOTH = AdafruitBLE

## Bluetooth キーコード

これは複数のキーボードの出力が選択できる場合に使われます。現在のところ、これは USB と Bluetooth の両方をサポートするキーボードで、それらの間の切り替えのみが可能です。

| 名前 | 説明 |
|----------|----------------------------------------------|
| `OUT_AUTO` | USB と Bluetooth を自動的に切り替える |
| `OUT_USB` | USB のみ |
| `OUT_BT` | Bluetooth のみ |
