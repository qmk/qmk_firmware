# JISキーボードライクなキーマップ

## 概要

　デフォルトキーマップの記号類をJISライクな配置に揃えなおしたものです。  

## キーマップの見かた

qmk_firmware\tmk_core\common\keycode.h  
に基本的なキーコードがあります。また、Keymap.cの上部にカスタムしたKC_で始まるものを登録しています。  
キーマップに書くときは「KC_」を省略して書いています。
例：KC_A → A  

Leyer Tap、Mod Tap、Tap DanceというQMKの機能を使っています。  

Layer Tapはタップで指定したキー、長押しで指定したレイヤーに移動します。  
例：LT(RAISE, KC_V) → タップでV、長押しでRAISEレイヤー移動

Mod Tapはタップで視程したキー、長押しで視程したレイヤーに移動します。  
例：LSFT_T(KC_Z) → タップでZ、長押しで左シフト

Tap Danceは指定した二つのキーをシングルタップ、ダブルタップで切り替えられます。  
例：[TD_CODO] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_DOT) → シングルタップでCOMM、ダブルタップでDOT

もう少し詳しい内容についてはQMK Documentをお読みいただくかネットを検索すれば情報が載っていますので別途検索してみてください。  

## 機能

　QWERTYキーマップをベースにしていて、LowerレイヤーとRaiseレイヤーに他のキーを配置しています。  
　LowerとRaiseを同時押しでAdjustレイヤーを使うことが出来ます。  
　DOTの横、SLROと書いてあるのはシングルタップで/記号、ダブルタップで\記号が入力出来るようになっています。
　Lの横、SCCLと書いてあるのはシングルタップで;記号、ダブルタップで:記号が入力出来るようになっています。
　マウスキーの割り当てがありますので、もし使用したい場合はrules.mkでMOUSEKEY_ENABLE = yesにしてmakeすると使用することができます。  

## 48キー目について

　このキーボードはEnterキーの上の2Uキーを1Ux2個にして使用する事が出来るようになっています。  使用する場合はキーマップの書き換えが必要です。  

　各レイヤーの最下段の

```c
      XXXXX \
  // ExtraKey: Split backspace key or it is below the enter key.
```

　のXXXXXに任意のキーを入れることでPの右隣のキーとして動作するようになっています。その右隣りに従来のキーが配置されています。  

## OS切り替え方法

　Adjustレイヤーにあります。LowerとRaiseを同時押しでAdjustレイヤーを使うことが出来ます。  

- KNRM: QMKのノーマル状態です。macだと正常に使える（はず）です
- KSWP: ノーマル状態のままWindowsで使用するとALTキーとGUI（win）キーが逆ですので、それを入れ換えます。Windowsユーザーはこちらのモードにしてください

## NUMPADモードについて

　Lower + DLNPキーを一度押下するとNumpadモードになります。通常モードに戻す場合はDLBSキーを押下してください。  

## IME切り替え方法

　Winの場合、LowerレイヤーにKANJIキー（半角/全角　漢字）がありますので、Lower+KANJIで切り替えてください。  

## ソフトウェアリセットについて

　キーボードにはハードウェアのリセットボタンが付いていますが、ソフトウェアリセットをかけられます。  
　LowerとRaiseを同時押しでAdjustレイヤーを使うことが出来、AdjustレイヤーのRSTを押下するとリセットがかかります。  

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
