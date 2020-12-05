# The Default Zinc Layout
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

### Colemak

```
 ,-----------------------------------------.             ,-----------------------------------------.
 | Tab  |   Q  |   W  |   F  |   P  |   G  |             |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Ctrl |   A  |   R  |   S  |   T  |   D  |             |   H  |   N  |   E  |   I  |   O  |  '   |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Shift|   Z  |   X  |   C  |   V  |   B  |             |   K  |   M  |   ,  |   .  |   /  |Enter |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Esc  |ADJUST| Alt  | Win  |LOWER |Space |             | Space| RAISE| Left | Down |  Up  | Right|
 `------------------------------------------             ------------------------------------------'
```   
 
### Dvorak

```
 ,-----------------------------------------.             ,-----------------------------------------.
 | Tab  |   '  |   ,  |   .  |   P  |   Y  |             |   F  |   G  |   C  |   R  |   L  | Del  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Ctrl |   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   T  |   N  |   S  |  /   |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Shift|   ;  |   Q  |   J  |   K  |   X  |             |   B  |   M  |   W  |   V  |   Z  |Enter |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Esc  |ADJUST| Alt  | Win  |LOWER |Space |             | Space| RAISE| Left | Down |  Up  | Right|
 `-----------------------------------------'             `-----------------------------------------'
```


## コンパイルの仕方

コンパイルは、qmk_firmware のトップディレクトリで行います。

```
$ cd qmk_firmware
```
qmk_firmwareでは各キーボードのコンパイルは、`<キーボード名>:<キーマップ名>`という指定で行います。

```
$ make zinc:default
```

キーボードへの書き込みまで同時に行うには下記のように`:avrdude`を付けます。

```
$ make zinc:default:avrdude
```

コンパイル結果と中間生成物を消去したい場合は以下のようにします。

```
$ make zinc:default:clean
```

## カスタマイズ

コマンドラインからオプションを指定してビルドすることが出来ます。

```
# Zinc keyboard 'default' keymap: convenient command line option
make ZINC=<options> zinc:defualt
#    option= back | under | na | ios
#    ex.
#      make ZINC=under    zinc:defualt
#      make ZINC=under,ios zinc:defualt
#      make ZINC=back     zinc:default
#      make ZINC=back,na  zinc:default
#      make ZINC=back,ios zinc:default
```

あるいは`qmk_firmware/keyboards/zinc/rev1/keymaps/default/rules.mk` の以下の部分を直接編集して機能を有効化してください。

```
# Zinc keyboard customize
LED_BACK_ENABLE = no        # LED backlight (Enable SK6812mini backlight)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight)
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)


```

## RGB backlight を有効にする

rules.mk の下記の部分を編集して no を yes に変更してください。
```
LED_BACK_ENABLE = yes   # LED backlight (Enable SK6812mini backlight)
```


## RGB Underglow を有効にする

rules.mk の下記の部分を編集して no を yes に変更してください。
```
LED_UNDERGLOW_ENABLE = yes   # LED underglow (Enable WS2812 RGB underlight.)
```


## iPad/iPhoneサポートを有効にする。

rules.mk の下記の部分を編集して no を yes に変更してください。
RBG Underglow や RGBバックライトの輝度を抑えて、iPad, iPhone にも接続できるようになります。

```
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
```