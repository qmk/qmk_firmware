# Supporting Your Keyboard in QMK Configurator

This page covers how to properly support keyboards in the [QMK Configurator](https://config.qmk.fm/).


## How the Configurator Understands Keyboards

To understand how the Configurator understands keyboards, first one must understand layout macros. For this exercise, we're going to imagine a 17-key numpad PCB, which we're going to call `numpad`.

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

::: tip
For more on layout macros, see [Understanding QMK: Matrix Scanning](understanding_qmk#matrix-scanning) and [Understanding QMK: Matrix to Physical Layout Map](understanding_qmk#matrix-to-physical-layout-map).
:::

The Configurator's API reads the keyboard's `.h` file from `qmk_firmware/keyboards/<keyboard>/<keyboard>.h`. For our numpad, this file would be `qmk_firmware/keyboards/numpad/numpad.h`:

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

QMK uses `KC_NO` to designate places in the switch matrix where there is no switch. Sometimes, `XXX`, `___` or `____` are used as shorthand to make this section easier to read if it needs to be debugged. This is usually defined near the beginning of the `.h` file:

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

::: warning
This usage differs from that of keymap macros, which almost always use `XXXXXXX` (seven capital X's) for `KC_NO` and `_______` (seven underscores) for `KC_TRNS`.
:::

::: warning
To prevent user confusion, using `KC_NO` is preferred.
:::

The layout macro tells the Configurator that our keyboard has 17 keys, arranged in five rows of four columns each. Our switch positions are named `k<row><column>`, counting from 0. The names themselves actually don't matter, as long as they match between the top section, which receives the keycodes from the keymap, and the bottom half which designates where each key is in the matrix.

To display our keyboard in a way that resembles the physical keyboard, we need to build a JSON file that tells the Configurator how to tie the physical locations and sizes of our keys to our switch matrix.

## Building the JSON file

To build the JSON file, the easiest way is to build the layout in [Keyboard Layout Editor](https://www.keyboard-layout-editor.com/) ("KLE"), from which we'll feed the Raw Data into a QMK tool that converts this data into a JSON the Configurator will read and use. Since KLE opens by default with a numpad layout, we're just going to remove the Getting Started instructions, and use what's left.

Once the layout is as desired, move to the Raw Data tab in KLE, and copy the contents:

```
["Num Lock","/","*","-"],
["7\nHome","8\n↑","9\nPgUp",{h:2},"+"],
["4\n←","5","6\n→"],
["1\nEnd","2\n↓","3\nPgDn",{h:2},"Enter"],
[{w:2},"0\nIns",".\nDel"]
```

To convert this data into our JSON, go to the [QMK KLE-JSON Converter](https://qmk.fm/converter/), paste the Raw Data into the Input field, and click the Convert button. After a moment, our JSON data will appear in the Output field. Copy the contents to a new text document, and name the document `info.json`, saving it in the same folder that contains `numpad.h`.

Use the `keyboard_name` object to set the name of the keyboard. For instruction purposes, we will put each key's object on its own line. This is only to make the file more human-readable, and does not affect the Configurator's functionality.

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

The `layouts` object contains the data that represents the physical layout of the keyboard. It has an object `LAYOUT`, which needs to match the name of our layout macro from `numpad.h`. The `LAYOUT` object itself has an object named `layout`, which contains one JSON object for each physical key on our keyboard, formatted as follows:

```
  The name of the key. Not displayed in the Configurator.
  |
  |                   The key's X-axis location, in key units from the
  |                   | keyboard's left edge.
  |                   |
  |                   |      The key's Y-axis location, in key units from
  |                   |      | the keyboard's top (rear-facing) edge.
  ↓                   ↓      ↓
{"label":"Num Lock", "x":0, "y":0},
```

Some objects will also have `"w"` and `"h"` keys, which represent a key's width and height, respectively.

::: tip
For more on the `info.json` files, see [`info.json` Format](reference_info_json).
:::


## How the Configurator Programs Keys

The Configurator's API uses the layout macro and the JSON file we've given it to create a visual representation of the keyboard that has each visual object tied to a specific key, in sequence:

| Key in layout macro | JSON object used                         |
| ------------------- | ---------------------------------------- |
| k00                 | `{"label":"Num Lock", "x":0, "y":0}`     |
| k01                 | `{"label":"/", "x":1, "y":0}`            |
| k02                 | `{"label":"*", "x":2, "y":0}`            |
| k03                 | `{"label":"-", "x":3, "y":0}`            |
| k10                 | `{"label":"7", "x":0, "y":1}`            |
| k11                 | `{"label":"8", "x":1, "y":1}`            |
| k12                 | `{"label":"9", "x":2, "y":1}`            |
| k13                 | `{"label":"+", "x":3, "y":1, "h":2}`     |
| k20                 | `{"label":"4", "x":0, "y":2}`            |
| k21                 | `{"label":"5", "x":1, "y":2}`            |
| k22                 | `{"label":"6", "x":2, "y":2}`            |
| k30                 | `{"label":"1", "x":0, "y":3}`            |
| k31                 | `{"label":"2", "x":1, "y":3}`            |
| k32                 | `{"label":"3", "x":2, "y":3}`            |
| k33                 | `{"label":"Enter", "x":3, "y":3, "h":2}` |
| k40                 | `{"label":"0", "x":0, "y":4, "w":2}`     |
| k42                 | `{"label":".", "x":2, "y":4}`            |

When a user selects the top-left key in the Configurator, and assigns Num Lock to it, the Configurator builds a keymap file with `KC_NUM` as the first key, and so on as the keymap is built. The `label` keys are not used; they are only for the user's reference in identifying specific keys when debugging the `info.json` file.


## Issues and Hazards

Currently, the Configurator does not support key rotation or non-rectangular key shapes like ISO Enter. Additionally, keys that are vertically-offset from their "row" &mdash; the arrow keys on 1800-layouts like the [TKC1800](https://github.com/qmk/qmk_firmware/tree/4ac48a61a66206beaf2fdd5f2939d8bbedd0004c/keyboards/tkc1800/) being a prominent example &mdash; confuse the KLE-to-JSON Converter, if not adjusted for by the contributor of the `info.json` file.

### Workarounds

#### Non-rectangular keys

For ISO Enter keys, QMK custom is to display it as a rectangular key, 1.25u wide and 2u high, aligned so its right edge is aligned with the right edge of the alphanumeric key block.

![](/JKngtTw.png)  
*A 60% keyboard in standard ISO layout, as rendered by QMK Configurator.*

#### Vertically-offset keys

For vertically-offset keys, place them in KLE as if they were not offset, then edit the Y-values as needed in the converted JSON file

![](/fmDvDzR.png)  
*An 1800-layout keyboard as rendered in Keyboard Layout Editor, without the vertical offset applied to the arrow keys.*

```diff
-{"label": "\u2191", "x", 14.25, "y": 5},
+{"label": "\u2191", "x", 14.25, "y": 5.25},
...
-{"label": "\u2190", "x", 13.25, "y": 6},
-{"label": "\u2193", "x", 14.25, "y": 6},
-{"label": "\u2192", "x", 15.25, "y": 6},
+{"label": "\u2190", "x", 13.25, "y": 6.25},
+{"label": "\u2193", "x", 14.25, "y": 6.25},
+{"label": "\u2192", "x", 15.25, "y": 6.25},
```
*A diff showing the changes needed to vertically-offset the arrow keys in our keyboard's JSON file.*
