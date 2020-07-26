# ユーザスペース: キーマップ間でのコードの共有

<!---
  original document: 0.9.43:docs/feature_userspace.md
  git diff 0.9.43 HEAD -- docs/feature_userspace.md | cat
-->

似たキーマップを複数のキーボードで使う場合、それらの間でコードを共有できるという利点が得られることがあります。`users/`に以下の構造でキーマップ(理想的には GitHub のユーザ名、`<name>`)と同じ名前の独自のフォルダを作成します:

* `/users/<name>/` (パスに自動的に追加されます)
   * `readme.md` (オプション、推奨)
   * `rules.mk` (自動的に含まれます)
   * `config.h` (自動的に含まれます)
   * `<name>.h` (オプション)
   * `<name>.c` (オプション)
   * `cool_rgb_stuff.c` (オプション)
   * `cool_rgb_stuff.h` (オプション)


以下のように、`<name>` という名前のキーマップをビルドする時のみ、これが全て起きます:

    make planck:<name>

例えば、

    make planck:jack

は、`/users/jack/rules.mk` に加えて、パスに `/users/jack/` フォルダを含めます。

!> この `name` は必要に応じて[上書き](#override-default-userspace)することができます。

## `Rules.mk`

`rules.mk` は自動的に処理される2つファイルのうちの1つです。これにより、コンパイル時に追加のソースファイル( `<name>.c` など)を追加できます。

追加されるデフォルトのソースファイルとして `<name>.c` を使うことを強くお勧めします。それを追加するために、以下のように `rules.mk` に SRC を追加する必要があります:

    SRC += <name>.c

追加のファイルも同じ方法で追加できます - ただし、`<name>`.c/.h という名前のファイルを最初に用意することをお勧めします。

ビルド時に `/users/<name>/rules.mk` ファイルはキーマップの `rules.mk` の_後_でインクルードされます。これにより、キーボードによっては利用できないことのある個々の QMK 機能を利用する機能をユーザスペース `rules.mk` に持つことができます。

例えば、RGB ライトをサポートする全てのキーボード間で RGB 制御機能を共有する場合、RGBLIGHT 機能が有効であればサポートを追加することができます:
```make
ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  # ここにファンシーな rgb 関数のソースを含める
  SRC += cool_rgb_stuff.c
endif
```

別のやり方として、キーマップの `rules.mk` で `define RGB_ENABLE` と定義し、以下のようにユーザスペースの `rules.mk` で変数をチェックすることができます:
```make
ifdef RGB_ENABLE
  # ここにファンシーな rgb 関数のソースを含める
  SRC += cool_rgb_stuff.c
endif
```

### デフォルトのユーザスペースの上書き :id=override-default-userspace

デフォルトでは、使用されるユーザスペース名はキーマップ名と同じです。状況によってはこれは望ましくありません。例えば、[レイアウト](ja/feature_layouts.md)機能を使う場合、異なるキーマップに同じ名前 (例えば、ANSI および ISO) を使うことができません。レイアウトに `mylayout-ansi` や `mylayout-iso` という名前を付け、以下の行をレイアウトの `rules.mk` に追加します:

```
USER_NAME := mylayout
```

これは、基板上に物理的に異なる機能を備えた、複数の異なるキーボード(RGBライトを備えたキーボード、オーディオを備えたキーボード、LEDの数が異なる、コントローラ上の異なるPINに接続されているなど)がある場合にも役立ちます。

## 設定オプション (`config.h`)

さらに、ここにある `config.h` はキーマップフォルダ内の同名のファイルと同じように処理されます。これは `<name>.h` ファイルとは別個に処理されます。

この理由は、`<name>.h` は (`#define TAPPING_TERM 100` などのような)設定を追加する時には追加されず、`config.h` ファイル内の `<name.h>` ファイルを含めるとコンパイルの問題を引き起こすからです。

!>`config.h` は[設定オプション](ja/config_options.md)のために使い、`<name>.h` ファイルはユーザあるいは(レイヤーあるいはキーコードのための enum のような)キーマップ固有の設定のために使うべきです


## Readme (`readme.md`)

作者情報 (あなたの名前、GitHub ユーザ名、eメール)およびオプションで[GPL 互換のライセンス](https://www.gnu.org/licenses/license-list.html#GPLCompatibleLicenses)を含めてください。

以下をテンプレートとして使うことができます:
```
Copyright <year> <name> <email> @<github_username>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
```

年、名前、eメールおよび GitHub ユーザ名をあなたの情報に置き換えます。

さらに、コードを他の人に共有したい場合、ここはコードを文章化するのに適した場所です。

## 特定のキーマップをサポートする全てのキーボードをビルドする

1つのコマンドで全てのキーマップのビルドを確認したいですか？以下で実行することができます:

    make all:<name>

例えば、

    make all:jack

これは、[_プルリクエスト_](https://github.com/qmk/qmk_firmware/pulls) を準備する時に全てが正常にコンパイルされることを確認したい場合に最適です。

## 例

簡単な例については、[`/users/_example/`](https://github.com/qmk/qmk_firmware/tree/master/users/_example) を調べてください。
より複雑な例については、[`/users/drashna/`](https://github.com/qmk/qmk_firmware/tree/master/users/drashna) のユーザスペースを調べてください。


### カスタマイズされた関数 :id=customized-functions

QMK には、[`_quantum`、`_kb` および `_user` バージョン](ja/custom_quantum_functions.md#a-word-on-core-vs-keyboards-vs-keymap)を持つ使用可能な[関数](custom_quantum_functions.md)が山ほどあります。 ほとんどの場合、これらの関数のユーザバージョンを使う必要があります。しかし問題はそれらをユーザスペースで使う場合、キーマップで使うことができるバージョンが無いことです。

しかし、実際にはキーマップバージョンのサポートを追加し、ユーザスペースとキーマップの両方で使うことができます。


例えば、`layer_state_set_user()` 関数を見てみましょう。全てのキーボードで [Tri Layer State](ja/ref_functions.md#olkb-tri-layers) 機能を有効にしながら、`keymap.c` ファイルで Tri Layer 機能を保持することができます。

`<name.c>` ファイル内で、以下を追加する必要があります:
```c
__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

layer_state_t layer_state_set_user (layer_state_t state) {
  state = update_tri_layer_state(state, 2, 3, 5);
  return layer_state_set_keymap (state);
}
```
`__attribute__ ((weak))` 部分は、コンパイラにこれが `keymap.c` 内のバージョンに置き換えられるプレースホルダ関数であることを伝えます。そうすれば、`keymap.c` に追加する必要はありませんが、追加しても関数が同じ名前を持つため競合することはありません。

ここでの `_keymap` 部分は重要では無く、`_quantum`、`_kb` あるいは `_user` は既に使われているため、それら以外のものである必要があります。`layer_state_set_mine`、`layer_state_set_fn` などを使うことができます。

[`users/drashna`](https://github.com/qmk/qmk_firmware/tree/master/users/drashna) 内の [`template.c`](https://github.com/qmk/qmk_firmware/blob/master/users/drashna/template.c) でこのリストと他の一般的な関数を見つけることができます。

### カスタム機能

ユーザスペース機能は膨大な数のキーボードをサポートすることができるため、特定の機能は有効にしたいが、他のキーボードでは有効にしたくないかもしれません。そして実際に自分のユーザスペースで有効あるいは無効にすることができる「機能」を作成することができます。

例えば、(スペースを節約するために)特定のキーボードでのみたくさんのマクロを利用したい場合、それらを `#ifdef MACROS_ENABLED` して「見えないように」してから、キーボードごとに有効にすることができます。これを行うには、以下を rules.mk に追加します。
```make
ifeq ($(strip $(MACROS_ENABLED)), yes)
    OPT_DEFS += -DMACROS_ENABLED
endif
```
`OPT_DEFS` 設定は `MACROS_ENABLED` がキーボード用に定義されるようにし(名前の前に `-D` があることに注意してください)、c/h ファイルで状態をチェックするために `#ifdef MACROS_ENABLED` を使うことができ、それに基づいてそのコードを処理します。

次にキーマップの `rules.mk` に `MACROS_ENABLED = yes` を追加し、ユーザスペースでこの機能とコードを有効にします。

そして `process_record_user` 関数の中で、以下のようなことを行います:
```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
#ifdef MACROS_ENABLED
  case MACRO1:
    if (!record->event.pressed) {
      SEND_STRING("This is macro 1!");
    }
    break;
  case MACRO2:
    if (!record->event.pressed) {
      SEND_STRING("This is macro 2!");
    }
    break;
#endif
  }
  return true;
}
```


### 結合マクロ

全てのキーマップについてユーザスペースにマクロやそのほかの関数を統合したい場合は、そうすることができます。これは上記の[カスタマイズ関数](#customized-functions)の例に基づいています。これは異なるキーボード間で共有される大量のマクロを維持し、キーボード固有のマクロも可能です。

最初に、全ての `keymap.c` ファイルを調べ、代わりに `process_record_user` を `process_record_keymap` に置き換えます。この方法では、これらのキーボードでキーボード固有のコードを使用でき、カスタムの "global" キーコードも使うことができます。また、`SAFE_RANGE` を `NEW_SAFE_RANGE` に置き換えて、キーコードが重複しないようにすることもできます。

次に、全ての keymap.c ファイルに `#include <name.h>` を追加します。これにより、各キーマップでそれらを再定義することなく新しいキーコードを使うことができます。

それが完了したら、必要なキーコードの定義を `<name>.h` ファイルに設定します。例えば:
```c
#pragma once

#include "quantum.h"
#include "action.h"
#include "version.h"

// 全てを定義
enum custom_keycodes {
  KC_MAKE = SAFE_RANGE,
  NEW_SAFE_RANGE  // キーマップ固有のコードについては "NEW_SAFE_RANGE" を使用
};
```

ここで、`<name>.c` ファイルを作成し、この内容をそれに追加します:

```c
#include "<name>.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_MAKE:  // ファームウェアをコンパイルし、キーボードのブートローダに基づく書き込みコマンドを追加します
            if (!record->event.pressed) {
            uint8_t temp_mod = get_mods();
            uint8_t temp_osm = get_oneshot_mods();
            clear_mods(); clear_oneshot_mods();
            SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
    #ifndef FLASH_BOOTLOADER
            if ((temp_mod | temp_osm) & MOD_MASK_SHIFT)
    #endif
            {
                SEND_STRING(":flash");
            }
            if ((temp_mod | temp_osm) & MOD_MASK_CTRL) {
                SEND_STRING(" -j8 --output-sync");
            }
            tap_code(KC_ENT);
            set_mods(temp_mod);
        }
        break;

  }
  return process_record_keymap(keycode, record);
}
```

(マクロパッドのような) Shift ボタンを持たないキーボードについては、ブートローダオプションを常に含める方法が必要です。これを行うには、以下をユーザスペースフォルダ内の `rules.mk` に追加します:

```make
ifeq ($(strip $(FLASH_BOOTLOADER)), yes)
    OPT_DEFS += -DFLASH_BOOTLOADER
endif
```

これは任意のキーマップで使うことができる新しい `KC_MAKE` キーコードを追加します。そして、このキーコードは、`make <keyboard>:<keymap>` を出力するため、頻繁なコンパイルを簡単にします。そして、これは現在のキーボードの情報を出力するため、全てのキーボードとキーマップで動作します。そのため毎回これを入力する必要はありません。

また、Shift を押したままにすると書き込みの対象 (`:flash`) をコマンドに追加します。Control を押したままにすると、複数のファイルを一度に処理することでコンパイル時間を短縮する幾つかのコマンドを追加します。 

そして Shift キーが無いキーボード、あるいは常に書き込みを試したいキーボードについては、キーマップの `rules.mk` に `FLASH_BOOTLOADER = yes` を追加することができます。

?> これはブートローダの設定に基づいて正しいユーティリティを使って新しくコンパイルされたファームウェアを自動的に書き込むはずです (あるいはデフォルトで HEX ファイルを生成するだけ)。ただし、これは全てのシステムで動作するわけではないことに注意してください。はっきり言うと、AVRDUDE は WSL では動作しません。そして、これは BootloadHID あるいは mdloader をサポートしません。
