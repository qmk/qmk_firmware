# monksoffunk's personal zinc Layout
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
 | Esc  |ADJUST| Alt  | GUI  |LOWER |Space |             | Space| RAISE| KANA | Left | Down | Right|
 `------------------------------------------             ------------------------------------------'
```

KANAキーを独立させ、UPキーをLOWER＋スラッシュに当てています。そのほかデフォルトからレイヤーをかなりいじっています。
また、RGB LEDがアンコメントしてありますので、実装していない場合はソースを見て適宜コメントアウトしてください。

## コンパイルの仕方

コンパイルは、qmk_firmware のトップディレクトリで行います。

```
$ cd qmk_firmware
```
qmk_firmwareでは各キーボードのコンパイルは、`<キーボード名>:<キーマップ名>`という指定で行います。

```
$ make zinc:monks
```

キーボードへの書き込みまで同時に行うには下記のように`:avrdude`を付けます。

```
$ make zinc:monks:avrdude
```

コンパイル結果と中間生成物を消去したい場合は以下のようにします。

```
$ make zinc:monks:clean
```

なお、avrdudeではなくQMK Toolbox（GUIツール）を使う方法もあります。

https://github.com/qmk/qmk_toolbox/releases

その場合は、$ make zinc:monksでビルドした成果物をQMK Toolboxから指定してください。

## カスタマイズ

コマンドラインからオプションを指定してビルドすることが出来ます。

```
# Zinc keyboard 'monks' keymap: convenient command line option
make ZINC=<options> zinc:monks
#    option= back | under | na | ios
#    ex.
#      make ZINC=under    zinc:monks
#      make ZINC=under,ios zinc:monks
#      make ZINC=back     zinc:monks
#      make ZINC=back,na  zinc:monks
#      make ZINC=back,ios zinc:monks
```

あるいは`qmk_firmware/keyboards/zinc/rev1/keymaps/monks/rules.mk` の以下の部分を編集して機能を有効化してください。

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
LED_UNDERGLOW_ENABLE = yes   # LED underglow (Enable WS2812 RGB underlight)
```


## iPad/iPhoneサポートを有効にする。

rules.mk の下記の部分を編集して no を yes に変更してください。
RBG Underglow や RGBバックライトの輝度を抑えて、iPad, iPhone にも接続できるようになります。

```
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
```