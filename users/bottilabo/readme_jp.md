# QMK Harmonizeライブラリ

Copyright 2019-2020 Bottilabo [twitter @bottilabo](https://twitter.com/bottilabo)
                         [https://github.com/bottilabo/qmk]

QMK Harmonizeライブラリは、
- 一つの仮想的なキーボードの定義から各キーボードに配列をマッピングさせることにより、仮想キーボードの定義を変更するだけで、対応するすべてのキーボードの配列を同じように変更することができます。
- QMKを使った一般的なキーボードであれば、簡単に組み込むことができます。
- コンパイル時にキー配列を最大３種類、日本語入力モードを最大３種類設定し、仮想キーボードの配列をベースにして動作時に切り替えることができます。
- 日本語入力モードのかな配列では、PCへのキー出力を「かな」もしくは「ローマ字」のどちらかを動作中に変更できます。
- コンパイル時にpluginとしてoled,rgblightの機能を組み込むことができます（一部）

![atreus42](https://github.com/bottilabo/qmk-harmonize/raw/master/img/bottilabo-atreus42.png)

![crkbd](https://github.com/bottilabo/qmk-harmonize/raw/master/img/bottilabo-crkbd.png)

![nicola](https://github.com/bottilabo/qmk-harmonize/raw/master/img/nicola.png)

![tron](https://github.com/bottilabo/qmk-harmonize/raw/master/img/tron.png)

# 操作方法

- ADJ + G
IMを使用しない。通常のローマ字入力になります。
- ADJ + F
IM1を使用する。
- ADJ + D
IM2を使用する。
- ADJ + S
IM3を使用する。

- ADJ + B
QWERTYを使用します。
- ADJ + V
KBLAYOUT1を使用する。
- ADJ + C
KBLAYOUT2を使用する。
- ADJ + X
KBLAYOUT3を使用する。

- TL2(CAPS) + D
IMを使用しない通常の入力モード。選択済みのKBLAYOUTが使用されます。
- TL2(CAPS) + F
IMを使用する入力モード。選択済みのIMが使用されます。

# IMでの入力方法
TL0(左の親指。通常はシフト),TR0(右の親指。通常はスペース)がそれぞれ左シフト、右シフトとなっています。
右シフトは単打でスペースになります。


# ビルド例
```
cd qmk_firmware

`make crkbd:bottilabo:avrdude EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA PLUG1=PLUG_OLED'`

`make claw44:bottilabo:avrdude EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA PLUG1=PLUG_OLED'`


`make naked64:bottilabo:avrdude EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA PLUG1=PLUG_RGBLIGHT'`
`make silverbullet44:bottilabo:avrdude EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA PLUG1=PLUG_RGBLIGHT'`

`make mint60:bottilabo:avrdude EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA PLUG1=PLUG_RGBLIGHT'`

`make ergo42:bottilabo:avrdude EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA'`
`make numatreus:bottilabo:avrdude EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA'`
`make treadstone48:bottilabo:avrdude EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA'`
`make atreus62:bottilabo:avrdude EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA'`
`make ergodash/mini:bottilabo:avrdude EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA'`
`make projectkb/alice:bottilabo:flash EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA'`
`make reviung41:bottilabo:flash EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA'`

```



# ビルド方法
```
make crkbd:harmonize-crkbd EXTRAFLAGS='-DKBD=KBD_HARMONIZE -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBLAYOUT3=KB_MSIKI -DKBIM1=IM_ROMAJI_COLEMAK -DKBIM2=IM_TRON -DKBIM3=IM_NAGINATA'
```

例のようにKBLAYOUT1-3 KBIM1-3に使用したい配列、日本語入力モードを指定してください。  
ProMicroは容量が少ないため、日本語入力モードを複数入れることができないことがあります。  
容量が足りない場合は、次のように必要なものだけ指定してビルドします。  
```
make crkbd:harmonize-crkbd EXTRAFLAGS='-DKBD=KBD_HARMONIZE -DKBLAYOUT1=KB_COLEMAK -DKBIM1=IM_ROMAJI_COLEMAK'
```

## 容量削減

```
-DNO_KANA
```
かなキーでの出力を無効にし、ローマ字のみの出力にして使用する容量を削減します
。

# 作成済みのキー配列

- arensito
- Astarte
- beakl4opt-ergo
- capewell-dvorak
- colemak
- colemak-mod_dh
- dvorak
- eucalyn
- harmonix
- harmony
- M式
- mtgap
- mtgap2
- norman
- plum
- qgmlwy
- workman

# 作成済み日本語入力モード

## かな入力
- 親指シフト（ニコラ配列）
- Tron配列
- 薙刀式

かな入力配列では、キーの出力を「ローマ字」と「かな」のどちらでも行えます。ローマ字出力で後置の濁点を処理するため、新JISなどでは濁点をすばやく後置入力しなければなりません。また、後置入力を処理するため、入力から一呼吸おいてからキーが出力されます。


## ローマ字入力
- カタナ式
- Ｍ式
- ローマ字colemak


# キー配列を変更する

qmk_firmware/users/bottilabo/KBD_HARMONIZE を参考に独自の KBD_USER を作ってください。
コンパイル時に -DKBK=KBD_USER を追加して指定します。


# keymap.cへの追加方法
- 仮想キーボードからのマッピング定義
- harmonizeライブラリの読み込み
- matrix_init_userへの追加
- matrix_scan_userへの追加
- process_record_userへの追加
が必要です。


## keymap.c 例
```
#include QMK_KEYBOARD_H

#define HAS_THUMBROW

//      +    +    +    *                                 *    +    +    +
//4     4    3    2    1    1      1              1      1    1    2    3    4      4
#define LAYOUT_remapper( \
ESC ,   NL5, NL4, NL3, NL2, NL1,              NR1, NR2, NR3, NR4, NR5,   NR6, NR7, BSPC,  \
TAB ,   L05, L04, L03, L02, L01,              R01, R02, R03, R04, R05,   R06, R07, BSLS,   \
CAPS,   L15, L14, L13, L12, L11,              R11, R12, R13, R14, R15,   R16, R17, ENTR,  \
LSFT,   L25, L24, L23, L22, L21,              R21, R22, R23, R24, R25,   R26,      RSFT,  \
MOUS,  LCTL,LALT,LGUI,                                            RGUI,RALT,RCTL,   ADJ, \
                       TL2,                                   TR2,                       \
       PGUP,                TL1,                         TR1,                UP,         \
HOME,  PGDN,END ,                  TL0,           TR0,                 LEFT,DOWN,  RIGT, \
INS ,DEL   ,PRNT,BRK,                                                ZENHN,KANA,MHEN,HENK  \
  ) \
  LAYOUT( \
ESC , L05, L04, L03, L02, L01,                     R01, R02, R03, R04, R05, R06,BSPC, \
CAPS, L15, L14, L13, L12, L11,                     R11, R12, R13, R14, R15, ENTR , \
LCTL, L24, L23, L22, L21, L25,                     R21, R22, R23, R24, R25, ADJ, \
        LGUI ,TL1   ,      TL0,   TR0,              TR1,RCTL,RALT  \
    )
#define LAYOUT_DEF(...)                  LAYOUT_remapper(__VA_ARGS__)

#include "../../../harmonize/harmonize.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  HARMONIZE_PROC_RECORD_USER;
  return true;
}
void matrix_init_user(void) {
    harmonize_init();
}
void matrix_scan_user(void) {
   HARMONIZE_MATRIX_SCAN_USER;
}

```



# License
　特にこだわりはないのでとりあえずGPLにしました。

