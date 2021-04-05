# QMK Configurator でのキーボードのサポート

<!---
  original document: 0.9.46:docs/reference_configurator_support.md
  git diff 0.9.46 HEAD -- docs/reference_configurator_support.md | cat
-->

このページは [QMK Configurator](https://config.qmk.fm/) でキーボードを適切にサポートする方法について説明します。


## Configurator がキーボードを理解する方法

Configurator がキーボードをどのように理解するかを理解するには、最初にレイアウトマクロを理解する必要があります。この演習では、17キーのテンキー PCB を想定します。これを `numpad` と呼びます。

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

レイアウトマクロは、キーボードに17個のキーがあり、4列それぞれが5行に配置されていることを Configurator に伝えます。スイッチの位置は、0から始まる `k<row><column>` という名前が付けられています。キーマップからキーコードを受け取る上部セクションと、マトリックス内の各キーの位置を指定する下部セクションとが一致する限り、名前自体は実際には問題ではありません。

物理的なキーボードに似た形でキーボードを表示するには、それぞれのキーの物理的な位置とサイズをスイッチマトリックスに結びつけることを Configurator に伝える JSON ファイルを作成する必要があります。

## JSON ファイルのビルド

JSON ファイルをビルドする最も簡単な方法は、[Keyboard Layout Editor](https://www.keyboard-layout-editor.com/) ("KLE") でレイアウトを作成することです。この Raw Data を QMK tool に入れて、Configurator が読み出して使用する JSON ファイルに変換します。KLE は numpad レイアウトをデフォルトで開くため、Getting Started の説明を削除し、残りを使います。

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

`layouts` オブジェクトにはキーボードの物理レイアウトを表すデータが含まれます。このオブジェクトには `LAYOUT` という名前のオブジェクトがあり、このオブジェクト名は `numpad.h` のレイアウトマクロの名前と一致する必要があります。`LAYOUT` オブジェクト自体には `layout` という名前のオブジェクトがあります。このオブジェクトにはキーボードの物理キーごとに 1つの JSON オブジェクトが以下の形式で含まれています:

```
  キーの名前。Configurator では表示されません。
  |
  |                   キーボードの左端からのキー単位での
  |                   | キーの X 軸の位置。
  |                   |
  |                   |      キーボードの上端(奥側)からのキー単位での
  |                   |      | キーの Y 軸位置。
  ↓                   ↓      ↓
{"label":"Num Lock", "x":0, "y":0},
```

一部のオブジェクトには、それぞれキーの幅と高さを表す `"w"` 属性キーと `"h"` 属性キーがあります。

?> `info.json` ファイルの詳細については、[`info.json` 形式](ja/reference_info_json.md) を参照してください。


## Configurator がキーをプログラムする方法

Configurator の API は、指定されたレイアウトマクロと JSON ファイルを使って、特定のキーに関連付けられた各ビジュアルオブジェクトを順番に持つキーボードのビジュアル表現を作成します:

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

ユーザが Configurator で左上のキーを選択し、Num Lock を割り当てると、Configurator は最初のキーとして `KC_NLCK` を持つキーマップを作成し、同様にキーマップが作成されます。`label` キーは使われません; それらは `info.json` ファイルをデバッグする時に特定のキーを識別するためのユーザの参照のためだけのものです。


## 問題と危険

現在のところ、Configurator はキーの回転または ISO Enter などの長方形ではないキーをサポートしません。さらに、"行"から垂直方向にずれているキー、&mdash; 顕著な例として [TKC1800](https://github.com/qmk/qmk_firmware/tree/4ac48a61a66206beaf2fdd5f2939d8bbedd0004c/keyboards/tkc1800/) のような1800レイアウト上の矢印キー &mdash; は、 `info.json` ファイルの提供者によって調整されていない場合は、KLE-to-JSON コンバータを混乱させます。

### 回避策

#### 長方形ではないキー

ISO Enter キーについては、QMK custom は幅 1.25u、高さ 2u の長方形のキーとして表示し、右端が英数字キーブロックの右端に揃うように配置されます。

![](https://i.imgur.com/JKngtTw.png)  
*QMK Configurator によって描画される標準 ISO レイアウトの60%キーボード。*

#### 垂直方向にずれたキー

垂直方向にずれたキーについては、ずれていないかのように KLE で配置し、変換された JSON ファイルで必要に応じて Y 値を編集します。

![](https://i.imgur.com/fmDvDzR.png)  
*矢印キーに適用される垂直方向のずれのない、Keyboard Layout Editor で描画された1800レイアウトのキーボード。*

![](https://i.imgur.com/8beYMBR.png)  
*キーボードの JSON ファイルで矢印キーを垂直方向にずらすために必要な変更を示す、Unix の diff ファイル。*
