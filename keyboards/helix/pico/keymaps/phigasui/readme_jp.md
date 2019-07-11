# The Default HelixPico Layout
## 配列

### Qwerty配列

```
 ,-----------------------------------------.             ,-----------------------------------------.
 | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |Enter |
 |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 |Adjust| Esc  | Alt  | GUI  | EISU |Lower |Space |Space |Raise | KANA | Left | Down |  Up  |Right |
 `-------------------------------------------------------------------------------------------------'
```

### Lower
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  | Del  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   _  |   +  |   {  |   }  |  |   |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 |      | PrSc | Home | End  |      |
 |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 `-------------------------------------------------------------------------------------------------'
```

### Raise
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |  \   |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 |      | PrSc |PageDn|PageUp|      |
 |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 `-------------------------------------------------------------------------------------------------'
```

### Adjust (Lower + Raise)
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |      | Reset|      |      |      |      |             |      |      |      |      |      |      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |Aud on|Audoff|MU TOG|MU MOD| Mac  |             | Win  |Qwerty|Colemk|Dvorak|      |      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |CK TOG|CK RST| CK UP|CK DWN|      |             |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
 `-------------------------------------------------------------------------------------------------'
```

他の配列(Colemak,Dvorak)は、[readme.md](readme.md) を参照

## コンパイルの仕方

コンパイルは、qmk_firmware のトップディレクトリで行います。

```
$ cd qmk_firmware
```
qmk_firmwareでは各キーボードのコンパイルは、`<キーボード名>:<キーマップ名>`という指定で行います。

```
$ make helix/pico:default
```

キーボードへの書き込みまで同時に行うには下記のように`:avrdude`を付けます。

```
$ make helix/pico:default:avrdude
```

コンパイル結果と中間生成物を消去したい場合は以下のようにします。

```
$ make helix/pico:default:clean
```

## カスタマイズ

オプションの OLED をつけたり、
RGB バックライトまたは、RGB Underglow をつけた場合は、
`qmk_firmware/keyboards/helix/pico/keymaps/default/rules.mk` の以下の部分を編集して機能を有効化してください。

```
# Helix keyboard customize
# you can edit follows 6 Variables
#  jp: 以下の6つの変数を必要に応じて編集します。
OLED_ENABLE = no            # OLED_ENABLE
LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)

```

## RGB バックライトを有効にする

rules.mk の下記の部分を編集して no を yes に変更してください。

```
LED_BACK_ENABLE = yes        # LED backlight (Enable WS2812 RGB underlight.)
```

## RGB Underglow を有効にする

rules.mk の下記の部分を編集して no を yes に変更してください。
```
LED_UNDERGLOW_ENABLE = yes   # LED underglow (Enable WS2812 RGB underlight.)
```

## OLEDを有効にする

rules.mk の下記の部分を編集して no を yes に変更してください。
```
OLED_ENABLE = yes            # OLED_ENABLE
```

## iPad/iPhoneサポートを有効にする。

rules.mk の下記の部分を編集して no を yes に変更してください。
RBG Underglow や RGBバックライトの輝度を抑えて、iPad, iPhone にも接続できるようになります。

```
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
```

## リンク

* さらに詳細は、[こちら helix/Doc/firmware_jp.md](https://github.com/MakotoKurauchi/helix/blob/master/Doc/firmware_jp.md)をご覧ください。
* [Helix top](https://github.com/MakotoKurauchi/helix)
