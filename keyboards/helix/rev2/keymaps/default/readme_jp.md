# The Default Helix Layout
## 配列

### Qwerty配列

```
 ,-----------------------------------------.             ,-----------------------------------------.
 |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |   /  |Enter |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |Adjust| Esc  | Alt  | GUI  | EISU |Lower |Space |Space |Raise | KANA | Left | Down |  Up  |Right |
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
$ make helix:default
```

キーボードへの書き込みまで同時に行うには下記のように`:avrdude`を付けます。

```
$ make helix:default:avrdude
```

コンパイル結果と中間生成物を消去したい場合は以下のようにします。

```
$ make helix:default:clean
```

## カスタマイズ

Helix キーボードを4行版として製作したり、オプションの OLED をつけたり、
RGB バックライトまたは、RGB Underglow をつけた場合は、
`qmk_firmware/keyboards/helix/rev2/keymaps/default/rules.mk` の以下の部分を編集して機能を有効化してください。

```
# Helix keyboard customize
# you can edit follows 5 Variables
#  jp: 以下の5つの変数を必要に応じて編集します。
HELIX_ROWS = 5              # Helix Rows is 4 or 5
OLED_ENABLE = no            # OLED_ENABLE
LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = yes        # LED animations

```

## 4行版Helix に対応する

rules.mk の下記の部分を編集して 5 を 4 に変更してください。

```
HELIX_ROWS = 4              # Helix Rows is 4 or 5
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

## リンク

* さらに詳細は、[こちら helix/Doc/firmware_jp.md](https://github.com/MakotoKurauchi/helix/blob/master/Doc/firmware_jp.md)をご覧ください。
* [Helix top](https://github.com/MakotoKurauchi/helix)
