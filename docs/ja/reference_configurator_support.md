# QMK Configurator でのキーボードのサポート

<!---
  original document: 0.9.46:docs/reference_configurator_support.md
  git diff 0.9.46 HEAD -- docs/reference_configurator_support.md | cat
-->

このページは [QMK Configurator](https://config.qmk.fm/) でキーボードを適切にサポートする方法について説明します。


## Configurator がキーボードを理解する方法

Configurator がキーボードをどのように理解するかを理解するには、最初にレイアウトマクロを理解する必要があります。この演習では、17キーの numpad PCB を仮定します。これを `numpad` と呼びます。

```
|---------------|
|NLk| / | * | - |
|---+---+---+---|
|7  |8  |9  | + |
|---+---+---|   |
|4  |5  |6  |   |
|---+---+---+---|
|1  |2  |3  |Ent|
|-------+---|   |
|0      | . |   |
|---------------|
```

?> レイアウトマクロの詳細については、[QMK の理解: マトリックススキャン](ja/understanding_qmk.md?id=matrix-scanning) と [QMK の理解: マトリックスから物理レイアウトへのマップ](ja/understanding_qmk.md?id=matrix-to-physical-layout-map) を見てください。

Configurator の API はキーボードの `.h` ファイルを `qmk_firmware/keyboards/<keyboard>/<keyboard>.h` から読み取ります。numpad の場合、このファイルは `qmk_firmware/keyboards/numpad/numpad.h` です:

```c
#pragma once

#define LAYOUT( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22,      \
    k30, k31, k32, k33, \
    k40,      k42       \
  ) { \
    { k00, k01,   k02, k03   }, \
    { k10, k11,   k12, k13   }, \
    { k20, k21,   k22, KC_NO }, \
    { k30, k31,   k32, k33   }, \
    { k40, KC_NO, k42, KC_NO }  \
}
```

QMK は `KC_NO` を使って、スイッチマトリックス内のスイッチがない場所を指定します。デバッグが必要な場合に、このセクションを読みやすくするために、`XXX`、`___`、`____` を略記として使うこともあります。通常は `.h` ファイルの先頭近くで定義されます:

```c
#pragma once

#define XXX KC_NO

#define LAYOUT( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22,      \
    k30, k31, k32, k33, \
    k40,      k42       \
  ) { \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, XXX }, \
    { k30, k31, k32, k33 }, \
    { k40, XXX, k42, XXX }  \
}
```

!> この使用方法はキーマップマクロと異なります。キーマップマクロはほとんど常に`KC_NO`については`XXXXXXX` (7つの大文字の X) を、`KC_TRNS` については `_______` (7つのアンダースコア)を使います。

!> ユーザの混乱を防ぐために、`KC_NO` を使うことをお勧めします。

レイアウトマクロは、キーボードに17個のキーがあり、それぞれが4列の5行に配置されていることを Configurator に伝えます。スイッチの位置は、0から始まる `k<row><column>` という名前が付けられています。キーマップからキーコードを受け取る上部セクションと、マトリックス内の各キーの位置を指定する下部セクションとが一致する限り、名前自体は実際には問題ありません。

物理キーボードに似た方法でキーボードを表示するには、キーボーとの物理的な位置とサイズをスイッチマトリックスに関連付ける方法を Configurator に伝える JSON ファイルを作成する必要があります。

## JSON ファイルのビルド

JSON ファイルをビルドする最も簡単な方法は、[Keyboard Layout Editor](http://www.keyboard-layout-editor.com/) ("KLE") でレイアウトを作成することです。この Raw Data を Configurator が読み出し使用する JSON ファイルに変換する QMK tool に入れます。KLE は nampad レイアウトをデフォルトで開くため、Getting Started の指示を削除し、残っているものを使います。

レイアウトが望み通りのものになったら、KLE の Raw Data タブに移動し、内容をコピーします:

```
["Num Lock","/","*","-"],
["7\nHome","8\n↑","9\nPgUp",{h:2},"+"],
["4\n←","5","6\n→"],
["1\nEnd","2\n↓","3\nPgDn",{h:2},"Enter"],
[{w:2},"0\nIns",".\nDel"]
```

このデータを JSON に変換するには、[QMK KLE-JSON Converter](https://qmk.fm/converter/) に移動し、Raw Data を Input フィールド に貼り付け、Convert ボタンをクリックします。しばらくすると、JSON データが Output フィールドに表示されます。内容を新しいテキストドキュメントにコピーし、ドキュメントに `info.json` という名前を付け、`numpad.h` を含む同じフォルダに保存します。

`keyboard_name` オブジェクトを使ってキーボードの名前を設定します。説明のために、各キーのオブジェクトを各行に配置します。これはファイルを人間が読みやすいものにするためのもので、Configurator の機能には影響しません。

```json
{
    "keyboard_name": "Numpad",
    "url": "",
    "maintainer": "qmk",
    "tags": {
        "form_factor": "numpad"
    },
    "width": 4,
    "height": 5,
    "layouts": {
        "LAYOUT": {
            "layout": [
                {"label":"Num Lock", "x":0, "y":0},
                {"label":"/", "x":1, "y":0},
                {"label":"*", "x":2, "y":0},
                {"label":"-", "x":3, "y":0},
                {"label":"7", "x":0, "y":1},
                {"label":"8", "x":1, "y":1},
                {"label":"9", "x":2, "y":1},
                {"label":"+", "x":3, "y":1, "h":2},
                {"label":"4", "x":0, "y":2},
                {"label":"5", "x":1, "y":2},
                {"label":"6", "x":2, "y":2},
                {"label":"1", "x":0, "y":3},
                {"label":"2", "x":1, "y":3},
                {"label":"3", "x":2, "y":3},
                {"label":"Enter", "x":3, "y":3, "h":2},
                {"label":"0", "x":0, "y":4, "w":2},
                {"label":".", "x":2, "y":4}
            ]
        }
    }
}
```

`layouts` オブジェクトはキーボードの物理レイアウトを表すデータを含みます。オブジェクト `LAYOUT` は `numpad.h` のレイアウトマクロの名前と一致する必要があります。`LAYOUT` オブジェクト自身には `layout` という名前のオブジェクトがあります。このオブジェクトはキーボードの物理キーごとに以下の形式の1つの JSON オブジェクトを含みます:

```
  The name of the key. Configurator では表示されません。
  |
  |                   The key's X-axis location, in key units from the
  |                   | keyboard's left edge.
  |                   |
  |                   |      The key's Y-axis location, in key units from
  |                   |      | the keyboard's top (rear-facing) edge.
  ↓                   ↓      ↓
{"label":"Num Lock", "x":0, "y":0},
```

一部のオブジェクトは `"w"` および `"h"` キーを持ちます。これらはそれぞれキーの幅と高さを表します。

?> For more on the `info.json` files, see [`info.json` Format](ja/reference_info_json.md).


## Configurator がキーをプログラムする方法

Configurator の API は、指定されたレイアウトマクロと JSON ファイルを使って、特定のキーに順番に関連付けられた各ビジュアルオブジェクトを持つキーボードのビジュアル表現を作成します:

| レイアウトマクロのキー | 使用される JSON オブジェクト |
:---: | :----
| k00 | {"label":"Num Lock", "x":0, "y":0} |
| k01 | {"label":"/", "x":1, "y":0} |
| k02 | {"label":"*", "x":2, "y":0} |
| k03 | {"label":"-", "x":3, "y":0} |
| k10 | {"label":"7", "x":0, "y":1} |
| k11 | {"label":"8", "x":1, "y":1} |
| k12 | {"label":"9", "x":2, "y":1} |
| k13 | {"label":"+", "x":3, "y":1, "h":2} |
| k20 | {"label":"4", "x":0, "y":2} |
| k21 | {"label":"5", "x":1, "y":2} |
| k22 | {"label":"6", "x":2, "y":2} |
| k30 | {"label":"1", "x":0, "y":3} |
| k31 | {"label":"2", "x":1, "y":3} |
| k32 | {"label":"3", "x":2, "y":3} |
| k33 | {"label":"Enter", "x":3, "y":3, "h":2} |
| k40 | {"label":"0", "x":0, "y":4, "w":2} |
| k42 | {"label":".", "x":2, "y":4} |

ユーザが Configurator で左上のキーを選択し、Num Lock を割り当てると、Configurator はキーマップを作成する時に最初のキーとして `KC_NLCK` を持つキーマップを作成します。`label` キーは使われません; それらは `info.json` ファイルをデバッグする時に特定のキーを識別するためのユーザの参照のためだけのものです。


## 問題と危険

現在のところ、Configurator はキーの回転または ISO Enter などの長方形ではないキーをサポートしません。さらに、"行" &mdash; から垂直方向にオフセットされているキー、顕著な例として [TKC1800](https://github.com/qmk/qmk_firmware/tree/4ac48a61a66206beaf2fdd5f2939d8bbedd0004c/keyboards/tkc1800/) のような1800レイアウト上の矢印キー &mdash; は、 `info.json` ファイルの貢献者によって調整されていない場合は、KLE-to-JSON コンバータを混乱させます。

### 回避策

#### 表方形ではないキー

ISO Enter キーについては、QMK custom は幅 1.25u、高さ 2u の長方形のキーとして表示し、右端が英数字キーブロックの右端に揃うように配置されます。

![](https://i.imgur.com/JKngtTw.png)
*QMK Configurator によって描画される標準 ISO レイアウトの60%キーボード。*

#### 垂直方向のオフセットキー

垂直方向のオフセットキーについては、オフセットされていないかのようにKLEで配置し、変換された JSON ファイルで必要に応じて Y 値を編集します。

![](https://i.imgur.com/fmDvDzR.png)
*矢印キーに適用される垂直方向のオフセットを持たない、Keyboard Layout Editor で描画された1800レイアウトのキーボード。*

![](https://i.imgur.com/8beYMBR.png)
*キーボードの JSON ファイルで矢印キーを垂直方向にオフセットするために必要な変更を示す、Unix の diff ファイル。*
