# Bluetooth

## Bluetoothの既知のサポート ハードウェア

現在のところBluetoothのサポートはAVRベースのチップに限られます。Bluetooth 2.1 については、Qmkは RN-42 HID ファームウェアと、Bluefruit EZ Keyをサポートしますが、後者はもう生産されていません。より最近のBLEプロトコルについては、現在のところ Adafruit Bluefruit SPI フレンドのみが直接サポートされています。iOSデバイスに接続するには、BLEが必要です。iOSはマウス入力をサポートしないことに注意してください。

| ボード | Bluetooth プロトコル | 接続タイプ | Rules.mk | Bluetooth チップ |
|----------------------------------------------------------------|----------------------------|----------------|---------------------------|--------------|
| [Adafruit EzKey HID]("https://www.adafruit.com/product/1535") | Bluetooth Classic | UART | BLUETOOTH = AdafruitEZKey |  |
| Rover Networks RN-42 (Sparkfun Bluesmirf) | Bluetooth Classic | UART | BLUETOOTH = RN42 | RN-42 |
| [Bluefruit LE SPI フレンド](https://www.adafruit.com/product/2633) | Bluetooth Low Energy | SPI | BLUETOOTH = AdafruitBLE | nRF5182 |

まだサポートされていませんが、おそらく:
* [Bluefruit LE UART フレンド](https://www.adafruit.com/product/2479)。[tmk実装がおそらく見つかります](https://github.com/tmk/tmk_keyboard/issues/514)
* HC-05 boards flashed with RN-42 firmware. どちらも明らかに CSR BC417 チップを使っています。RN-42 ファームウェアを使ってフラッシュすると、HID機能が提供されます。
* [Sparkfun Bluetooth mate](https://www.sparkfun.com/products/14839)
* HM-13 ベースのボード

### Adafruit BLE SPI Friend
現在のところQMKによってサポートされている唯一の bluetooth チップセットは、Adafruit Bluefruit SPI Friend です。Adafruitのカスタムファームウェアを実行するNordic nRF5182 ベースのチップです。データはAdafruitのSDEP over Hardware SPIを使って転送されます。[Feather 32u4 Bluefruit LE](https://www.adafruit.com/product/2829)はAdafruitファームウェアを搭載したNordic BLEチップにSPI経由で接続されたAVR mcuであるため、サポートされます。SPIフレンドを使ってカスタムボードを構築する場合、32u4フェザーが使用するピン選択を使うのが最も簡単ですが、以下の定義でconfig.h内のピンを変更することができます:
* 
   # define AdafruitBleResetPin D4
* 
   # define AdafruitBleCSPin    B4
* 
   # define AdafruitBleIRQPin   E6

Bluefruit UART friend は SPI friend に変換することができますが、これには再フラッシュとMDBT40チップへの直接のはんだ付けが[必要です](https://github.com/qmk/qmk_firmware/issues/2274)。

## Adafruit EZ-Key hid
これには[ハードウェアの変更](https://www.reddit.com/r/MechanicalKeyboards/comments/3psx0q/the_planck_keyboard_with_bluetooth_guide_and/?ref=search_posts)が必要ですが、Makefileを使って有効にすることができます。ファームウェアは引き続きUSB経由で文字を出力するため、コンピュータ経由で充電する場合は注意してください。任意にオフにするためにBluefruit上にスイッチを持つことは理にかなっています。


<!-- FIXME: Document bluetooth support more completely. -->
## Bluetooth Rules.mk オプション
これらのうちの1つだけを使ってください
* BLUETOOTH_ENABLE = yes (レガシーオプション)
* BLUETOOTH = RN42
* BLUETOOTH = AdafruitEZKey
* BLUETOOTH = AdafruitBLE

## Bluetooth キーコード

複数のキーボードの出力が選択できる場合に使われます。現在のところ、これはUSBとBluetoothの両方をサポートするキーボード上でそれらの間を切り替えのみを許可します。

| 名前 | 説明 |
|----------|----------------------------------------------|
| `OUT_AUTO` | USBとBluetoothを自動的に切り替える |
| `OUT_USB` | USB のみ |
| `OUT_BT` | Bluetooth のみ |
