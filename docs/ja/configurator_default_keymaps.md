# QMK Configurator にデフォルトキーマップを追加する :id=adding-default-keymaps
<!---
  original document: 0.13.15:docs/configurator_default_keymaps.md
  git diff 0.13.15 HEAD -- docs/configurator_default_keymaps.md | cat
-->

このページは、QMK Configurator にキーボードのデフォルトキーマップを追加する方法を取り上げます。


## 技術情報 :id=technical-information

QMK Configurator は、キーマップのネイティブファイル形式に JSON ファイルを使います。可能な限り、QMK Configurator で作成したファームウェアと、`qmk_firmware` で `make <keyboard>:default` を実行して作成したファームウェアが同じ動作となるべきです。

このディレクトリ内のキーマップは、4つのキー/値ペアを必要とします。

* `keyboard` (文字列)
  * これはキーボード名で、`make` コマンドでコンパイルするときに使われるものと同じです。 (例: `make 1upkeyboards/1up60rgb:default`).
* `keymap` (文字列)
  * `default` と設定する必要があります。
* `layout` (文字列)
  * デフォルトキーマップによって使われるレイアウトマクロです。
* `layers` (配列)
  * キーマップそのものです。このキーは、レイヤー毎に1つの配列を含む必要があり、配列はレイヤーを構成するキーコードを含む必要があります。

さらに、たいていのキーマップは `commit` キーを含みます。このキーは、QMK Configurator を支える API では使用されませんが、QMK Configurator のメンテナーがリポジトリ内の JSON 形式のキーマップを作るために使われたキーマップのバージョンを通知するために使われます。この値は、`qmk_firmware` リポジトリ内のキーボードのデフォルトの `keymap.c` を変更する最後のコミットの SHA です。この SHA の値は、[`qmk_firmware` リポジトリの `master` ブランチ](https://github.com/qmk/qmk_firmware/tree/master/) をチェックアウトして、`git log -1 --pretty=oneline -- keyboards/<keyboard>/keymaps/default/keymap.c` (問題のキーボードに `keymap.json` ファイルがあれば、代わりにそれを使います。) を実行すると、次のようなものが返ってきます:

```shell
f14629ed1cd7c7ec9089604d64f29a99981558e8 Remove/migrate action_get_macro()s from default keymaps (#5625)
```

この例では、`f14629ed1cd7c7ec9089604d64f29a99981558e8` が `commit` キーで使われるべき値です。


## 例 :id=example

もし、Hineybush の H87a キーボードのデフォルトキーマップを追加したいなら、`qmk_firmware` ディレクトリの H87a のデフォルトキーマップに対して上記の `git log` コマンドを実行します。

```shell
user ~/qmk_firmware (master)
$ git log -1 --pretty=oneline master -- keyboards/hineybush/h87a/keymaps/default/keymap.c
ef8878fba5d3786e3f9c66436da63a560cd36ac9 Hineybush h87a lock indicators (#8237)
```

これでコミットハッシュを入手しましたので、次はキーマップが必要です。(キーマップは読みやすさのために編集しています)

```c
...
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_all(
    KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,              KC_PSCR, KC_SLCK, KC_PAUS,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,             KC_DEL,  KC_END,  KC_PGDN,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_TRNS,                      KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RGUI, KC_RCTL,             KC_LEFT, KC_DOWN, KC_RGHT),

  [1] = LAYOUT_all(
    KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI,             BL_TOGG, BL_DEC,  BL_INC,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_VOLU,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_MPLY, KC_MNXT, KC_VOLD,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS),

};
```

デフォルトキーマップが `LAYOUT_all` マクロを使うため、これが `layout` キーの値となります。QMK Configurator が JSON キーマップにコンパイルすると、結果は次のようになるはずです。

```json
{
  "keyboard": "hineybush/h87a",
  "keymap": "default",
  "commit": "ef8878fba5d3786e3f9c66436da63a560cd36ac9",
  "layout": "LAYOUT_all",
  "layers": [
    [
      "KC_ESC",             "KC_F1",   "KC_F2",   "KC_F3",   "KC_F4",   "KC_F5",   "KC_F6",   "KC_F7",   "KC_F8",   "KC_F9",   "KC_F10",  "KC_F11",  "KC_F12",                "KC_PSCR", "KC_SLCK", "KC_PAUS",
      "KC_GRV",  "KC_1",    "KC_2",    "KC_3",    "KC_4",    "KC_5",    "KC_6",    "KC_7",    "KC_8",    "KC_9",    "KC_0",    "KC_MINS", "KC_EQL",  "KC_BSPC", "KC_BSPC",    "KC_INS",  "KC_HOME", "KC_PGUP",
      "KC_TAB",  "KC_Q",    "KC_W",    "KC_E",    "KC_R",    "KC_T",    "KC_Y",    "KC_U",    "KC_I",    "KC_O",    "KC_P",    "KC_LBRC", "KC_RBRC", "KC_BSLS",               "KC_DEL",  "KC_END",  "KC_PGDN",
      "KC_CAPS", "KC_A",    "KC_S",    "KC_D",    "KC_F",    "KC_G",    "KC_H",    "KC_J",    "KC_K",    "KC_L",    "KC_SCLN", "KC_QUOT", "KC_NUHS", "KC_ENT",
      "KC_LSFT", "KC_NUBS", "KC_Z",    "KC_X",    "KC_C",    "KC_V",    "KC_B",    "KC_N",    "KC_M",    "KC_COMM", "KC_DOT",  "KC_SLSH", "KC_RSFT", "KC_TRNS",                          "KC_UP",
      "KC_LCTL", "KC_LGUI", "KC_LALT",                                  "KC_SPC",                                   "KC_RALT", "MO(1)",   "KC_RGUI", "KC_RCTL",               "KC_LEFT", "KC_DOWN", "KC_RGHT"
    ],
    [
      "KC_TRNS",            "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "RGB_TOG", "RGB_MOD", "RGB_HUD", "RGB_HUI", "RGB_SAD", "RGB_SAI", "RGB_VAD", "RGB_VAI",               "BL_TOGG", "BL_DEC",  "BL_INC",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",    "KC_TRNS", "KC_TRNS", "KC_VOLU",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "RESET",   "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",               "KC_MPLY", "KC_MNXT", "KC_VOLD",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",                          "KC_TRNS",
      "KC_TRNS", "KC_TRNS", "KC_TRNS",                                  "KC_TRNS",                                  "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",               "KC_TRNS", "KC_TRNS", "KC_TRNS"
    ]
  ]
}
```

`layers` 配列にあるホワイトスペースはキーマップの機能に影響を及ぼしませんが、これらのファイルを人間が読みやすくするために使われています。


## 注意書き :id=caveats

### レイヤーは数値で参照する :id=layer-references

通常の QMK の慣習では、レイヤーを命名するためにいくつかの `#define` か `enum` 宣言を使います。

```c
enum layer_names {
    _BASE,
    _MEDIA,
    _FN
};
```

これは C 言語では動作しますが、QMK Configurator では動作しません。レイヤーのインデックスには数値を使用する *必要があります*。上記の例だと、`MO(_FN)` ではなく `MO(2)` とする必要があります。

### カスタムコードはサポート対象外 :id=custom-code

タップダンスやユニコードのように keymap.c ファイルに関数を追加する必要がある機能は、QMK Configurator では **全て**コンパイルできません。`qmk_firmware` リポジトリ内のキーボードレベルで `TAP_DANCE_ENABLE = yes` と設定しても、QMK Configurator はファームウェアをコンパイルできません。これは、API と 現在の JSON キーマップ形式の仕様による制限です。


### カスタムキーコードの限定的なサポート :id=custom-keycodes

カスタムキーコードをサポートする方法はあります。qmk_firmware 内のキーマップレベルではなくキーボードレベルでカスタムキーコードのロジックが実装されていれば、それらのキーコードは QMK Configurator で*使用でき*、コンパイルして機能*するようになります*。

```c
enum custom_keycodes {
    MACRO_1 = SAFE_RANGE,
    MACRO_2,
    MACRO_3
};
...
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MACRO_1:
            if (record->event.pressed) {
                SEND_STRING("This is macro #1.");
            }
            return false;
        case MACRO_2:
            if (record->event.pressed) {
                SEND_STRING("This is macro #2.");
            }
            return false;
        case MACRO_3:
            if (record->event.pressed) {
                SEND_STRING("This is macro #3.");
            }
            return false;
    }
    return true;
};
```

... `enum` ブロックのキーコードをキーボードのヘッダーファイル (`<keyboard>.h`) に次のように追加します。 (`enum` がここでは `keyboard_keycodes` と命名されていることに注意してください):

```c
enum keyboard_keycodes {
    MACRO_1 = SAFE_RANGE,
    MACRO_2,
    MACRO_3,
    NEW_SAFE_RANGE  // Important!
};
```

... それから、`<keyboard>.c` の `process_record_kb()` にカスタムキーコードのロジックを追加します: 

```c
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MACRO_1:
            if (record->event.pressed) {
                SEND_STRING("This is macro #1.");
            }
            return false;
        case MACRO_2:
            if (record->event.pressed) {
                SEND_STRING("This is macro #2.");
            }
            return false;
        case MACRO_3:
            if (record->event.pressed) {
                SEND_STRING("This is macro #3.");
            }
            return false;
    }
    return process_record_user(keycode, record);
};
```

最後に `process_record_user()` を呼び出すことに注意してください。さらに、ユーザーが自身のカスタムキーコードをキーボードによって提供される以上にキーマップレベルで追加したい場合は、`SAFE_RANGE` の代わりに `NEW_SAFE_RANGE` を使う必要があります。


## 追加説明 :id=additional-reading

QMK Configurator があなたのキーボードをサポートするためには、あなたのキーボードが `qmk_firmware` リポジトリの `master` ブランチに存在していなければなりません。この点の説明は、[キーボードサポート](https://docs.qmk.fm/#/ja/reference_configurator_support)を参照してください。
