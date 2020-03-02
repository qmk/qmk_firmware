# QMK ハードウェアドライバー

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: c9e3fa6f7:docs/hardware_drivers.md
  git diff c9e3fa6f7 HEAD -- docs/hardware_drivers.md | cat
-->

QMK はたくさんの異なるハードウェアで使われています。最も一般的な MCU とマトリクス構成をサポートしていますが、キーボードへ他のハードウェアを追加し制御するためのドライバーもいくつか用意されています。例えば、マウスやポインティングデバイス、スプリットキーボード用のIOエキスパンダ、Bluetoothモジュール、LCD、OLED、TFT液晶などがあります。

<!-- FIXME: This should talk about how drivers are integrated into QMK and how you can add your own driver.

# Driver System Overview

-->

# 使用できるドライバー

## ProMicro ( AVR のみ)

ProMicro のピンを AVR の名前ではなく、Arduino の名前で指定できます。この部分はより詳しく文書化される必要があります。もしこれを使用したい場合にコードを読んでも分からない場合、[issue を開く](https://github.com/qmk/qmk_firmware/issues/new)を通して助けることができるかもしれません。

## SSD1306 OLED ドライバー

SSD1306 ベースの OLED ディスプレイのサポート。詳しくは[OLED ドライバ](ja/feature_oled_driver.md)を参照して下さい。

## uGFX

QMK 内で uGFX を使用して、キャラクタ LCD やグラフィック LCD、LED アレイ、OLED ディスプレイ、TFT 液晶や他のディスプレイを制御できます。この部分はより詳しく文書化される必要があります。もしこれを使用したい場合にコードを読んでも分からない場合、[issue を開く](https://github.com/qmk/qmk_firmware/issues/new)を通して助けることができるかもしれません。

## WS2812

WS2811/WS2812{a,b,c} LED のサポート。 詳しくは [RGB ライト](ja/feature_rgblight.md)を参照して下さい。

## IS31FL3731

最大2つの LED ドライバーのサポート。各ドライバー毎に2つのチャーリープレクスマトリクスを実装すると I2C から LED を個別に制御できます。最大144個の単色 LED か32個の RGB LED を使用できます。詳しくは[RGB マトリクス](ja/feature_rgb_matrix.md)を参照して下さい。

## IS31FL3733

拡張の余地がある最大1つの LED ドライバーのサポート。各ドライバー毎に192個の単色 LED か64個の RGB LED を制御できます。詳しくは [RGB マトリクス](ja/feature_rgb_matrix.md)を参照して下さい。

## 24xx シリーズ 外部 I2C EEPROM

オンチップEEPROM の代わりに使用する I2C ベースの外部EEPROMのサポート。詳しくは [EEPROM ドライバー](ja/eeprom_driver.md)を参照して下さい。 
