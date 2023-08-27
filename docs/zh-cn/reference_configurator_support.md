# 在QMK配置器中支持您的键盘

<!---
  original document: 0.15.12:docs/reference_configurator_support.md
  git diff 0.15.12 HEAD -- docs/reference_configurator_support.md | cat
-->

本章节详述了如何在[QMK配置器](https://config.qmk.fm/)中对键盘进行支持。


## 配置器如何理解键盘

若要了解配置器如何理解键盘，须先理解配列的宏定义。这里有一份练习，假设这里有一个17键的小键盘PCB方案，就叫做 `numpad`。

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

?> 配列宏定义的更多资料，参见[理解QMK：矩阵扫描](zh-cn/understanding_qmk.md?id=matrix-scanning)及[理解QMK：矩阵到物理配列的映射](zh-cn/understanding_qmk.md?id=matrix-to-physical-layout-map)。

配置器的API会从 `qmk_firmware/keyboards/<keyboard>/<keyboard>.h` 中读取键盘定义的 `.h` 文件。在上面的小键盘示例中，对应文件应为 `qmk_firmware/keyboards/numpad/numpad.h`：

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

QMK使用 `KC_NO` 去标记开关矩阵中的空位。有时也会因方便或调试用途而使用 `XXX`，`___` 或 `____` 来替代。通产定义写在 `.h` 文件起始位置附近：

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

!> 注意这里的使用模式与键映射中的宏完全不同，后者几乎都在用 `XXXXXXX`（7个大写X）替代 `KC_NO`，用 `_______`（7个下划线）替代 `KC_TRNS`。

!> 为避免混淆，推荐使用 `KC_NO`。

配列宏定义描述该键盘有17个按键，分布在五行四列。我们将这些开关命名为 `k<行号><列号>`，从0计起。命名成什么不太重要，但须确保负责从键映射中接收键码的上半段，与描述矩阵中按键位置的下半段定义匹配一致。

为了能够重现键盘的物理组成样式，须构建并提供一份用于描述按键物理位置和尺寸与开关矩阵绑定关系的JSON文件，以告知配置器程序这些信息。

## 构建JSON文件

构建该JSON描述文件最简便的办法是使用[Keyboard Layout Editor](https://www.keyboard-layout-editor.com/) ("KLE"), 从中获取的原始数据（Raw Data）可以经QMK工具转换为配置器可用的JSON格式数据。由于KLE默认打开显示的是一个小键盘配列，请移除新手引导部分，从剩余部分开始使用。

在配列编辑完毕后，从KLE的原始数据（Raw Data tab）页中拷贝类似如下的内容：

```
["Num Lock","/","*","-"],
["7\nHome","8\n↑","9\nPgUp",{h:2},"+"],
["4\n←","5","6\n→"],
["1\nEnd","2\n↓","3\nPgDn",{h:2},"Enter"],
[{w:2},"0\nIns",".\nDel"]
```

要将这份数据转换为我们可用的JSON格式，请跳转至[QMK KLE-JSON转换工具](https://qmk.fm/converter/)页面并粘贴到输入框，点击转换按钮。稍后输出框中即可看到所需的JSON数据。将输出数据拷贝到文本文档中，并命名为 `info.json`，保存到 `numpad.h` 所在目录。

可以通过 `keyboard_name` 元素来指定键盘名称。这里为了演示，会将每个按键独立分行，以更方便于阅读，这不影响配置器的功能。

```json
{
    "keyboard_name": "Numpad",
    "url": "",
    "maintainer": "qmk",
    "tags": {
        "form_factor": "numpad"
    },
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

`layouts` 对象描述了键盘的物理配列信息，其下的 `LAYOUT` 对象命名须与 `numpad.h` 中的一致，而 `LAYOUT` 下的 `layout` 对象，其下每个JSON对象描述了各物理按键，格式如下：

```
  按键名，不会在配置器中展现。
  |
  |                   按键的X坐标，从键盘左侧开始数。
  |                   |
  |                   |
  |                   |      按键的Y坐标，从键盘上侧（后视角）开始数。
  |                   |      |
  ↓                   ↓      ↓
{"label":"Num Lock", "x":0, "y":0},
```

部分对象包含 `"w"` 和 `"h"` 字段，用以描述按键的宽高值。

?> 关于 `info.json` 文件的详细信息，参见[`info.json` 文件格式](zh-cn/reference_info_json.md)。


## 配置器如何配置按键

配置器API基于配列宏定义及JSON描述文件创建出键盘的可视化展现，并将每个可视化元素依序绑定到指定的按键：

配列宏定义中的键 | 所使用的JSON对象
:---: | :----
k00   | {"label":"Num Lock", "x":0, "y":0}
k01   | {"label":"/", "x":1, "y":0}
k02   | {"label":"*", "x":2, "y":0}
k03   | {"label":"-", "x":3, "y":0}
k10   | {"label":"7", "x":0, "y":1}
k11   | {"label":"8", "x":1, "y":1}
k12   | {"label":"9", "x":2, "y":1}
k13   | {"label":"+", "x":3, "y":1, "h":2}
k20   | {"label":"4", "x":0, "y":2}
k21   | {"label":"5", "x":1, "y":2}
k22   | {"label":"6", "x":2, "y":2}
k30   | {"label":"1", "x":0, "y":3}
k31   | {"label":"2", "x":1, "y":3}
k32   | {"label":"3", "x":2, "y":3}
k33   | {"label":"Enter", "x":3, "y":3, "h":2}
k40   | {"label":"0", "x":0, "y":4, "w":2}
k42   | {"label":".", "x":2, "y":4}

当用户在配置器中选中左上角的按键，并赋予数字区锁定键（NumLock）时，配置器会将 `KC_NUM` 作为第一个按键进行键映射文件的构建工作，其它按键逻辑类似。其中 `label` 键值未被用到，其用于用户在调试 `info.json` 文件时，可以参考辨认出各按键。


## 问题及副作用

目前配置器还不支持按键偏转及类似ISO回车键这种非矩形按键。另外，对于纵向上偏离其行的按键 &mdash; 特别是像[TKC1800](https://github.com/qmk/qmk_firmware/tree/4ac48a61a66206beaf2fdd5f2939d8bbedd0004c/keyboards/tkc1800/)这种1800配列的键盘中的方向键 &mdash; 如果 `info.json` 文件的贡献者没有做出修正，KLE转JSON数据工具将会不知如何处理。

### 解决方案

#### 非矩阵形状的按键

针对ISO回车键的情况，QMK会将其定制化显示成一个矩形键，宽1.25u高2u，按键矩阵的右边与字母区的右边对齐。

![](https://i.imgur.com/JKngtTw.png)  
*一款60% ISO配列的键盘, 在QMK配置器中的渲染样式。*

#### 纵向偏移的按键

对于纵向偏移的按键，将其视作未偏移的样子放入KLE，最后在转换后的JSON文件中，按需编辑其Y偏移值。

![](https://i.imgur.com/fmDvDzR.png)  
*一款1800配列键盘在KLE中的渲染样式，方向键未进行纵向偏移移动。*

![](https://i.imgur.com/8beYMBR.png)  
*这份Unix差异文件，展示了我们需要在JSON文件中进行的纵向偏移改动。*
