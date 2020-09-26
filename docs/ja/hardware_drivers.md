# QMK ハードウェアドライバー

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.9.0:docs/hardware_drivers.md
  git diff 0.9.0 HEAD -- docs/hardware_drivers.md | cat
-->

QMK はたくさんの異なるハードウェアで使われています。最も一般的な MCU とマトリックス構成をサポートしていますが、キーボードへ他のハードウェアを追加し制御するためのドライバーもいくつか用意されています。例えば、マウスやポインティングデバイス、分割キーボード用の IO エキスパンダ、Bluetooth モジュール、LCD、OLED、TFT 液晶などがあります。

<!-- FIXME: This should talk about how drivers are integrated into QMK and how you can add your own driver.

# Driver System Overview

-->

# 使用できるドライバー

## ProMicro (AVR のみ)

ProMicro のピンを AVR の名前ではなく、Arduino の名前で指定できます。この部分はより詳しく文書化される必要があります。もしこれを使用したい場合にコードを読んでも分からない場合、[issue を開く](https://github.com/qmk/qmk_firmware/issues/new)を通して助けることができるかもしれません。

## SSD1306 OLED ドライバー

SSD1306 ベースの OLED ディスプレイのサポート。詳しくは[OLED ドライバ](ja/feature_oled_driver.md)を参照して下さい。

## uGFX

QMK 内で uGFX を使用して、キャラクタ LCD やグラフィック LCD、LED アレイ、OLED ディスプレイ、TFT 液晶や他のディスプレイを制御できます。この部分はより詳しく文書化される必要があります。もしこれを使用したい場合にコードを読んでも分からない場合、[issue を開く](https://github.com/qmk/qmk_firmware/issues/new)を通して助けることができるかもしれません。

## WS2812

WS2811/WS2812{a,b,c} LED のサポート。 詳しくは [RGB ライト](ja/feature_rgblight.md)を参照して下さい。

## IS31FL3731

最大2つの LED ドライバーのサポート。各ドライバーは、I2C を使って個別に LED を制御する2つのチャーリープレクスマトリックスを実装しています。最大144個の単色 LED か32個の RGB LED を使用できます。ドライバーの設定方法の詳細は[RGB マトリックス](ja/feature_rgb_matrix.md)を参照して下さい。

## IS31FL3733

拡張の余地がある最大1つの LED ドライバーのサポート。各ドライバーは192個の単色 LED か64個の RGB LED を制御できます。ドライバーの設定方法の詳細は [RGB マトリックス](ja/feature_rgb_matrix.md)を参照して下さい。

## 24xx シリーズ 外部 I2C EEPROM

オンチップ EEPROM の代わりに使用する I2C ベースの外部 EEPROM のサポート。ドライバーの設定方法の詳細は [EEPROM ドライバー](ja/eeprom_driver.md)を参照して下さい。 
