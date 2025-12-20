# qmk-translate-ansi-to-jis
ANSI (US)配列用のキーコードをJIS (JP)配列用キーコードに変換するQMK Firmware用ライブラリ


## 用途
QMK Firmware でキーマップを作成するほとんどの方はANSI配列で作成しており、当然そのキーボードはANSI配列としてOSに認識させていると思います。

このライブラリは、何かしらの事情によりANSI配列で作成したキーマップをJIS配列としてOSに認識させなければならない場合に有効です。

例えば、ANSI配列で作成したキーマップをJIS配列としてOSに認識した際、

- 「'」(KC_QUOT)は「'」ではなく「:」
- シフトした「2」(KC_2)は 「@」ではなく「"」
- シフトした「;」(KC_SCLN)は「:」ではなく「+」

というように、ANSI配列で想定していたものとは異なった文字が入力されてしまいます。
このライブラリを使用すれば、

- 「'」(KC_QUOT)は「'」
- シフトした「2」(KC_2)は 「@」
- シフトした「;」(KC_SCLN)は「:」

とANSI配列と同様の文字をJIS配列で認識させていても入力できるようになります。

## 使い方

### 1. このライブラリを submodule として追加

```
$ cd /path/to/your/keymap/dir
$ git submodule add https://github.com/m47ch4n/qmk-translate-ansi-to-jis.git a2j
```

### 2. `rules.mk` を編集

以下の行を追加
```
SRC += a2j/translate_ansi_to_jis.c
```

### 3. `keymap.c` を編集

3-1. ヘッダーファイルのインクルード
```c
#include "a2j/translate_ansi_to_jis.h"
```

3-2. `process_record_user` 関数に下記の行を追加

`return true;` で終了している行を以下のように編集してください。
```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  ...

  // 以下の行を追加
  return process_record_user_a2j(keycode, record);
}
```

### (Optional) ANSI配列、JIS配列両対応にする

`process_record_user_a2j` を呼ばなければ通常通りANSI用キーコードがOSに送信されるため、条件を追加すれば簡単にANSI配列、JIS配列両対応にできます。以下に例を示します。

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  ...

  if (!is_jis_mode()) {
    return true;
  }

  return process_record_user_a2j(keycode, record);
}
```

`is_jis_mode` はJIS配列として使いたい場合に`true`、そうでない場合に`false`が返るものとします。

以下を参考に実装してください。
- [Persistent Configuration (EEPROM) - Customizing Functionality - QMK](https://beta.docs.qmk.fm/using-qmk/guides/custom_quantum_functions#persistent-configuration-eeprom)
- [m47ch4n/helix-m5n-keymap: The m47ch4n keymap for Helix rev3 4rows.](https://github.com/m47ch4n/helix-m5n-keymap)
