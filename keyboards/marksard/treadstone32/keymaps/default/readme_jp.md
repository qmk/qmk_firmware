# US配列ライクデフォルトキーマップ

## 概要

　US配列ライクなデフォルトキーマップです。  

## キーマップの見かた

qmk_firmware\tmk_core\common\keycode.h  
に基本的なキーコードがあります。また、Keymap.cの上部にカスタムしたKC_で始まるものを登録しています。  

Leyer Tap、Mod TapというQMKの機能を使っています。  

Layer Tapはタップで指定したキー、長押しで指定したレイヤーに移動します。  
例：LT(RAISE, KC_V) → タップでV、長押しでRAISEレイヤー移動

Mod Tapはタップで視程したキー、長押しで視程したレイヤーに移動します。  
例：LSFT_T(KC_Z) → タップでZ、長押しで左シフト

もう少し詳しい内容についてはQMK Documentをお読みいただくかネットを検索すれば情報が載っていますので別途検索してみてください。  

## 機能

　QWERTYキーマップをベースにしていて、LowerレイヤーとRaiseレイヤーに他のキーを配置しています。  
　Lowerを最初し続けながらRaiseを同時押しするとAdjustレイヤーを使うことが出来ます。  

## OS切り替え方法

　Adjustレイヤーにあります。LowerとRaiseを同時押しでAdjustレイヤーを使うことが出来ます。  

- KNRM: QMKのノーマル状態です。macだと正常に使える（はず）です
- KSWP: ノーマル状態のままWindowsで使用するとALTキーとGUI（win）キーが逆ですので、それを入れ換えます。Windowsユーザーはこちらのモードにしてください

## IME切り替え方法

　Winの場合、LowerレイヤーにKANJIキー（半角/全角　漢字）がありますので、Lower+KANJIで切り替えてください。  

## ソフトウェアリセットについて

　キーボードにはハードウェアのリセットボタンが付いていますが、ソフトウェアリセットをかけられます。  
　LowerとRaiseを同時押しでAdjustレイヤーを使うことが出来、AdjustレイヤーのRESETを押下するとリセットがかかります。  

## LEDの点灯切り替え方法

　Adjustレイヤーにあります。LowerとRaiseを同時押しでAdjustレイヤーを使うことが出来ます。  

- RGBRST: LEDのリセット
- RGB_TOG: LEDのON/OFF切り替え
- RGB_MOD: LEDの光り方の変更
- RGB_HUI: Hue+ 色合いを変更
- RGB_HUD: Hue- 色合いを変更
- RGB_SAI: Saturation+ 色の濃さを変更
- RGB_SAD: Saturation- 色の濃さを変更
- RGB_VAI: Value+ 明るさを変更
- RGB_VAD: Value- 明るさを変更
