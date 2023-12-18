# The VIA Zinc Layout
## 配列

### Qwerty配列

```
 ,-----------------------------------------.             ,-----------------------------------------.
 | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |Enter |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Esc  |  Fn  | Alt  | Win  |Lower |Space |             | Space| Raise| Left | Down |  Up  | Right|
 `------------------------------------------             ------------------------------------------'
```

 ### Lower
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |      |      |      |      |      |             |   -  |   _  |   +  |   {  |   }  |  |   |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |      |      |      |      |      |             |      |      |      | Home | End  |      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |      |      |      |      |      |             |      |      | Next | Vol- | Vol+ | Play |
 `-----------------------------------------'             `-----------------------------------------'
```

### RAISE
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |  \   |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 |      |      |      |      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |      |      |      |      |      |             |      |      | Next | Vol- | Vol+ | Play |
 `-----------------------------------------'             `-----------------------------------------'
```

### Adjust
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |      | Reset|RGBRST|Aud on|Audoff|      |             |      |Qwerty|Colemk|Dvorak|      | Ins  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |RGB ON| HUE+ | SAT+ | VAL+ | Mac  |             | Win  |  -   |   =  |Print |ScLock|Pause |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |MODE R|RGBMOD| HUE- | SAT- | VAL- |      |             |      |      |      |      |PageUp|      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |      |      | EISU | EISU | EISU |             | KANA | KANA | KANA | Home |PageDn| End  |
 `-----------------------------------------'             `-----------------------------------------'
```

### Adjust2 (Lower + Raise)
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |      | Reset|RGBRST|Aud on|Audoff|      |             |      |Qwerty|Colemk|Dvorak|      | Ins  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |RGB ON| HUE+ | SAT+ | VAL+ | Mac  |             | Win  |  -   |   =  |Print |ScLock|Pause |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |MODE R|RGBMOD| HUE- | SAT- | VAL- |      |             |      |      |      |      |PageUp|      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |      |      | EISU | EISU | EISU |             | KANA | KANA | KANA | Home |PageDn| End  |
 `-----------------------------------------'             `-----------------------------------------'
```
※AdjustとAdjust2は同じものが入っています。このデータの冗長化は、VIA Configuratorでの変更を容易にするために実装を単純化する必要があったためです。Adjust2はLowerとRaiseの同時押しの際に有効になるレイヤーです


## コンパイルの仕方

コンパイルは、qmk_firmware のトップディレクトリで行います。

```
$ cd qmk_firmware
```
qmk_firmwareでは各キーボードのコンパイルは、`<キーボード名>:<キーマップ名>`という指定で行います。

```
$ make zinc:via
```

キーボードへの書き込みまで同時に行うには下記のように`:avrdude`を付けます。

```
$ make zinc:via:avrdude
```

コンパイル結果と中間生成物を消去したい場合は以下のようにします。

```
$ make zinc:via:clean
```

## カスタマイズ

コマンドラインからオプションを指定してビルドすることが出来ます。
ただしVIAキーマップではオプションなしでbothが指定されますので、ほとんどの場合はオプション記述なしでmake zinc:viaとします。

```
# Zinc keyboard 'via' keymap: convenient command line option
make ZINC=<options> zinc:via
#    option= back | under | both | cont | na | ios
#    ex.
#      make ZINC=under    zinc:via
#      make ZINC=under,ios zinc:via
#      make ZINC=back     zinc:via
#      make ZINC=back,na  zinc:via
#      make zinc:via
```

あるいは`qmk_firmware/keyboards/zinc/rev1/keymaps/~/rules.mk` の以下の部分を直接編集して機能を有効化してください。

```
# Zinc keyboard customize
LED_BACK_ENABLE = no        # LED backlight (Enable SK6812mini backlight)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight)
LED_BOTH_ENABLE = yes       # LED backlight and underglow
LED_RGB_CONT = yes           # LED continuous backlight or/and underglow between left Zinc and right Zinc
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
```

## RGB backlight を有効にする

rules.mk の下記の部分を編集して no を yes に変更してください。
```
LED_BACK_ENABLE = yes   # LED backlight (Enable SK6812mini backlight)
```
※VIAキーマップではオプションなしでbothが指定されます

## RGB Underglow を有効にする

rules.mk の下記の部分を編集して no を yes に変更してください。
```
LED_UNDERGLOW_ENABLE = yes   # LED underglow (Enable WS2812 RGB underlight.)
```
※VIAキーマップではオプションなしでbothが指定されます

## iPad/iPhoneサポートを有効にする。

rules.mk の下記の部分を編集して no を yes に変更してください。
RBG Underglow や RGBバックライトの輝度を抑えて、iPad, iPhone にも接続できるようになります。

```
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
```
