# 向QMK配置器中添加默认键映射 :id=adding-default-keymaps

<!---
  original document: 0.15.12:docs/configurator_default_keymaps.md
  git diff 0.15.12 HEAD -- docs/configurator_default_keymaps.md | cat
-->

本章节描述了如何向QMK配置器中添加一款键盘的默认键映射


## 技术信息 :id=technical-information

QMK配置器使用JSON作为键映射的本地文件格式。我们尽力确保其行为与在 `qmk_firmware` 中 执行 `make <keyboard>:default` 时一致。

该目录下的键映射需要定义四个键值对：

* `keyboard` (字符串)
  * 键盘名称，与执行 `make` 进行编译时使用的一致（如 `make 1upkeyboards/1up60rgb:default`）。
* `keymap` (字符串)
  * 应设置为 `default`.
* `layout` (字符串)
  * 默认键映射应使用的配列宏定义。
* `layers` (数组)
  * 键映射数据。此键下的每行元素对应一个层定义，层定义中包含该层的键码组成信息。

额外地，大部分键映射中还有一个 `commit` 项，该项并不是QMK配置器后端服务API所需，而是用于告知配置器维护者这份JSON键映射数据来源于代码库中的哪个版本的键映射。该值为 `qmk_firmware` 代码库中最后一次修改键盘默认 `keymap.c` 文件提交的commit的SHA标记。该SHA值的获取方式是拉取[`qmk/qmk_firmware` 库的 `master`分支](https://github.com/qmk/qmk_firmware/tree/master/)后，执行 `git log -1 --pretty=oneline -- keyboards/<keyboard>/keymaps/default/keymap.c`（若键盘有什么问题且存在 `keymap.json` 文件，则用之作为替代），执行结果应类似于：

```
f14629ed1cd7c7ec9089604d64f29a99981558e8 Remove/migrate action_get_macro()s from default keymaps (#5625)
```

本例中，`f14629ed1cd7c7ec9089604d64f29a99981558e8` 即应为 `commit` 的值。


## 示例 :id=example

若某人想添加H87a Hineybush键盘的默认键映射方案，应到 `qmk_firmware` 下H87a的默认键映射下执行上述 `git log` 命令：

```
user ~/qmk_firmware (master)
$ git log -1 --pretty=oneline master -- keyboards/hineybush/h87a/keymaps/default/keymap.c
ef8878fba5d3786e3f9c66436da63a560cd36ac9 Hineybush h87a lock indicators (#8237)
```

在我们获取了commit哈希值后，还需要键映射定义（为加强可读性进行了编辑处理）：

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
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_MPLY, KC_MNXT, KC_VOLD,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS),

};
```

默认键映射使用了 `LAYOUT_all` 宏，最后其会成为 `layout` 项的值。编译为QMK配置器的JSON键映射数据后，输出文件应为：

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
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "QK_BOOT", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",               "KC_MPLY", "KC_MNXT", "KC_VOLD",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",                          "KC_TRNS",
      "KC_TRNS", "KC_TRNS", "KC_TRNS",                                  "KC_TRNS",                                  "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",               "KC_TRNS", "KC_TRNS", "KC_TRNS"
    ]
  ]
}
```

`layers` 数组中的空白区域不影响键映射功能，仅为了方便阅读。


## 附加说明 :id=caveats

### 层定义只能通过序号进行引用 :id=layer-references

QMK中常见的一种做法是通过一系列 `#define` 或 `enum` 类型声明来对层定义进行命名：

```c
enum layer_names {
    _BASE,
    _MEDIA,
    _FN
};
```

对于C代码来讲可行，但对于配置器来讲，你*必须*使用层序号 - 上例中的`MO(_FN)` 应使用 `MO(2)`。

### 不支持任何形式的定制化代码 :id=custom-code

需要在 keymap.c 文件中添加函数代码的功能，如Tap Dance或是Unicode，都*完全*无法在配置器中构建。即便是在 `qmk_firmware` 代码库中在键盘定义中设置了 `TAP_DANCE_ENABLE = yes`，也只会导致*任何*固件构建在配置器中行不通。这是由API及JSON格式的键映射数据同时造成的限制。

### 对自定义键码的不完全支持 :id=custom-keycodes

仅有一个方案可以支持自定义键码：若自定义键码的逻辑实现是在 qmk_firmware 下的键盘定义中完成的，而非在键映射中，那么这个键码*可以*在配置器中使用且*可以*编译运行。（因此，）相对于在 `keymap.c` 中使用如下代码段：

```c
enum custom_keycodes {
    CUSTOM_1 = SAFE_RANGE,
    CUSTOM_2,
    CUSTOM_3
};
...
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case CUSTOM_1:
            if (record->event.pressed) {
                SEND_STRING("This is custom keycode #1.");
            }
            return false;
        case CUSTOM_2:
            if (record->event.pressed) {
                SEND_STRING("This is custom keycode #2.");
            }
            return false;
        case CUSTOM_3:
            if (record->event.pressed) {
                SEND_STRING("This is custom keycode #3.");
            }
            return false;
    }
    return true;
};
```

... 请将键码的 `enum` 定义块添加到键盘的头文件（`<keyboard.h>`）中，例如（留意 `enum` 在这里命名为 `keyboard_keycodes`）：

```c
enum keyboard_keycodes {
    CUSTOM_1 = SAFE_RANGE,
    CUSTOM_2,
    CUSTOM_3,
    NEW_SAFE_RANGE  // 重要!
};
```

... 之后在 `<keyboard>.c` 中的 `process_record_kb()` 代码逻辑应为：

```c
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case CUSTOM_1:
            if (record->event.pressed) {
                SEND_STRING("This is custom keycode #1.");
            }
            return false;
        case CUSTOM_2:
            if (record->event.pressed) {
                SEND_STRING("This is custom keycode #2.");
            }
            return false;
        case CUSTOM_3:
            if (record->event.pressed) {
                SEND_STRING("This is custom keycode #3.");
            }
            return false;
    }
    return process_record_user(keycode, record);
};
```

注意最后的 `process_record_user()` 调用，若用户需要添加自定义键码到键映射中，须使用 `NEW_SAFE_RANGE` 替代 `SAFE_RANGE`，而其定义来自于上面键盘层定义中。


## 更多资料 :id=additional-reading

为了让QMK配置器支持你的键盘，你的键盘定义必须存在于 `qmk_firmware` 代码库的 `master` 分支中。相关操作指引，请参见[在QMK配置器中支持你的键盘](zh-cn/reference_configurator_support.md).
