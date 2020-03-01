# QMK ハードウェアドライバー

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: c9e3fa6f7:docs/hardware_drivers.md
  git diff c9e3fa6f7 HEAD -- docs/hardware_drivers.md | cat
-->

QMKはたくさんの異なるハードウェアで使われています。最も一般的なMCUとマトリクス構成をサポートしていますが、キーボードへ他のハードウェアを追加し制御するためのドライバーもいくつか用意されています。例えば、マウスやポインティングデバイス、スプリットキーボード用のIOエクスパンダー、Bluetoothモジュール、LCD、OLED、TFTスクリーンなどがあります。

<!-- FIXME: This should talk about how drivers are integrated into QMK and how you can add your own driver.

# Driver System Overview

-->

# 使用できるドライバー

## ProMicro (AVRのみ)

ProMicroのピンをAVRの名前ではなく、Arduinoの名前で指定できます。この部分はより詳しく文書化される必要があります。もしこれを使用したい場合にコードを読んでも分からない場合、[issueを開く](https://github.com/qmk/qmk_firmware/issues/new)を通して助けることができるかもしれません。

## SSD1306 OLED ドライバー

SSD1306ベースのOLEDディスプレイのサポート。詳しくは[OLEDドライバ](feature_oled_driver.md)を参照して下さい。

## uGFX

QMK内でuGFXを使用して、キャラクタLCDやグラフィックLCD、LEDアレイ、OLEDディスプレイ、TFT液晶や他のディスプレイを制御できます。この部分はより詳しく文書化される必要があります。もしこれを使用したい場合にコードを読んでも分からない場合、[issueを開く](https://github.com/qmk/qmk_firmware/issues/new)を通して助けることができるかもしれません。

## WS2812

WS2811/WS2812{a,b,c} LEDのサポート。 詳しくは[RGB ライト](feature_rgblight.md)を参照して下さい。

## IS31FL3731

最大2つのLEDドライバーのサポート。それぞれのドライバーで、2つのチャーリープレクスマトリクスを実装するとI2CからLEDを個別に制御できます。最大144個の単色LEDか32個のRGB LEDを使用できます。詳しくは[RGB マトリクス](feature_rgb_matrix.md)を参照して下さい。

## IS31FL3733

拡張の余地がある最大1つのLEDドライバーのサポート。それぞれのでライバーで192個の単色LEDか64個のRGB LEDを制御できます。詳しくは[RGB マトリクス](feature_rgb_matrix.md)を参照して下さい。

## 24xx シリーズ 外部 I2C EEPROM

オンチップEEPROMの代わりに使用するI2Cベースの外部EEPROMのサポート。詳しくは[EEPROM ドライバー](eeprom_driver.md)を参照して下さい。 
