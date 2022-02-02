# 宏

<!---
  original document: 0.15.18:docs/feature_macros.md
  git diff 0.15.18 HEAD -- docs/feature_macros.md | cat
-->

利用宏可以实现单键触发多键输入的效果。QMK支持多种定义及使用宏的方法，能够做到很多事情：输入常用语句，一键复制粘贴（copypasta，译注：可以认为是一种复制或粘贴目的地固定的一种操作），游戏里重复性的操作，甚至是帮助你写代码。

!> **安全性警告**：虽然可以通过宏输入密码、信用卡号等敏感数据，但这真的是个超级糟糕的主意。任何可以碰到你键盘的人，都可以打开一个文本编辑器获取到这些信息。

## 在 JSON 格式的键映射中使用宏

在 `keymap.json` 文件中可以定义最多32个宏，可以在 [配置器](zh-cn/newbs_building_firmware_configurator.md) 和 `qmk compile` 命令中使用它们。宏须定义在 `macro` 字段下的列表中，如下所示：

```json
{
    "keyboard": "handwired/my_macropad",
    "keymap": "my_keymap",
    "macros": [
        [
            {"action":"down", "keycodes": ["LSFT"]},
            "hello world1",
            {"action": "up","keycodes": ["LSFT"]}
        ],
        [
            {"action":"tap", "keycodes": ["LCTL", "LALT", "DEL"]}
        ],
        [
            "ding!",
            {"action":"beep"}
        ],
        [
            {"action":"tap", "keycodes": ["F1"]},
            {"action":"delay", "duration": "1000"},
            {"action":"tap", "keycodes": ["PGDN"]}
        ]
    ],
    "layout": "LAYOUT_all",
    "layers": [
        ["MACRO_0", "MACRO_1", "MACRO_2", "MACRO_3"]
    ]
}
```

### 选择主布局

如果你要输入非英文语言，或使用 Colemak、Dvorak 或 Workman 这类非 QWERTY 布局的键盘，你需要将系统的输入语言设置为匹配的。对于宏的创建这可能造成一些问题 - 要输入一致的单词你可能点击的是不同的按键！一个解决方案是在 `keymap.json` 中添加 `host_language` 键值，如下所示：

```json
{
    "keyboard": "handwired/my_macropad",
    "keymap": "my_keymap",
    "host_language": "dvorak",
    "macros": [
        ["Hello, World!"]
    ],
    "layout": "LAYOUT_all",
    "layers": [
        ["MACRO_0"]
    ]
}
```

目前可用的语言定义参见下表：

| belgian | bepo | br_abnt2 | canadian_multilingual |
|:-------:|:----:|:--------:|:---------------------:|
| **colemak** | **croatian** | **czech** | **danish** |
| **dvorak_fr** | **dvorak** | **dvp** | **estonian** |
| **finnish** | **fr_ch** | **french_afnor** | **french** |
| **french_osx** | **german_ch** | **german** | **german_osx** |
| **hungarian** | **icelandic** | **italian** | **italian_osx_ansi** |
| **italian_osx_iso** | **jis** | **latvian** | **lithuanian_azerty** |
| **lithuanian_qwerty** | **norman** | **norwegian** | **portuguese** |
| **portuguese_osx_iso** | **romanian** | **serbian_latin** | **slovak** |
| **slovenian** | **spanish_dvorak** | **spanish** | **swedish** |
| **turkish_f** | **turkish_q** | **uk** | **us_international** |
| **workman** | **workman_zxcvm** |

针对键盘布局的详细信息，可以参阅 [kbdlayout.info](http://kbdlayout.info/)（尽管这些信息是针对Windows的，但绝大多数在其它系统的表现也是一致的）

### 宏的基础用法

每个宏由字符串及对象（字典）组成，字符串会直接输出至电脑，而对象可以用来控制宏的输出方式。

#### 对象格式

每个对象都需要一个必选字段：`action`，该字段用于告诉 QMK 其功能，目前支持5种功能：beep（蜂鸣），delay（延时），down（按下），tap（点击），up（抬起）

只支持基础键码（`KC_`起始），但使用时不要带 `KC_` 前缀。

* `beep`
    * 若[已启用音频功能](feature_audio.md)，将会响一声
    * 示例：`{"action": "beep"}`
* `delay`
    * 暂停宏回放，时间长度由毫秒数（ms）控制。
    * 示例：`{"action": "delay", "duration": 500}`
* `down`
    * 发送若干个按键的按下事件。
    * 单键示例：`{"action":"down", "keycodes": ["LSFT"]}`
    * 多键示例：`{"action":"down", "keycodes": ["CTRL", "LSFT"]}`
* `tap`
    * 输入和弦（Type a chord）（译注1），即先发送若干个键的按下事件，再依次发送这些键的抬起事件。
    * 单键示例：`{"action":"tap", "keycodes": ["F13"]}`
    * 多键示例：`{"action":"tap", "keycodes": ["CTRL", "LALT", "DEL"]}`
* `up`
    * 发送若干个按键的抬起事件。
    * 单键示例：`{"action":"up", "keycodes": ["LSFT"]}`
    * 多键示例：`{"action":"up", "keycodes": ["CTRL", "LSFT"]}`
    
*译注1：比喻这种输入模式像钢琴上弹和弦，同时按下，再同时抬起*

## 在 keymap 的 C 代码中使用宏

### `SEND_STRING()` & `process_record_user`

有时你想让一个键可以输出一个单词或一句话，大部分情况下，使用已提供的 `SEND_STRING()` 即可输入一段字符串（即一串字符）。所有可以简单地映射到键码的 ASCII 字符都可以使用（例如 `qmk 123\n\t`）

以下为一个两个键的键盘的 `keymap.c` 文件示例：

```c
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMKBEST:
        if (record->event.pressed) {
            // 按下 QMKBEST 键
            SEND_STRING("QMK is the best thing ever!");
        } else {
            // 松开 QMKBEST 键
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {QMKBEST, KC_ESC},
        // ...
    },
};
```

上例的详细解释：
首先在不会与其它键码冲突的值域范围内自定义一个新键码；
然后，在 `process_record_user` 函数内检查自定义键码是否被触发，该函数在任意键按下或抬起时都会被调用；
若自定义键被触发，我们通过 `SEND_STRING` 宏（一个C语言预处理宏，不要和 QMK 宏搞混）将字符串 `"QMK is the best thing ever!"` 发送给电脑；
通过返回 `true` 以告知该函数的调用方刚才的点击事件需要继续按常规流程处理（即我们不是在替换或修改这个键的功能）；
最后，我们定义出一个键映射配置，第一个键为可以触发上述宏功能的自定义键，第二个键则只是个 Escape 键。

?>每个[定制功能](zh-cn/custom_quantum_functions.md)键码都推荐使用 SAFE_RANGE 宏。

你或许希望不仅仅只有一个宏，那么可以再添加一个键码，并在 switch 语句中增加 case 处理逻辑，就像这样：

```c
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL,
    MY_OTHER_MACRO,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMKBEST:
        if (record->event.pressed) {
            // 按下 QMKBEST 键
            SEND_STRING("QMK is the best thing ever!");
        } else {
            // 松开 QMKBEST 键
        }
        break;

    case QMKURL:
        if (record->event.pressed) {
            // 按下 QMKURL 键
            SEND_STRING("https://qmk.fm/\n");
        } else {
            // 松开 QMKURL 键
        }
        break;

    case MY_OTHER_MACRO:
        if (record->event.pressed) {
           SEND_STRING(SS_LCTL("ac")); // 全选并拷贝
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {MY_CUSTOM_MACRO, MY_OTHER_MACRO},
        // ...
    },
};
```

?> 自定义键码的枚举值定义列表（`enum custom_keycodes`）必须定义在 `keymaps[]` 数组、`process_record_user()` 以及其它需要用到该符号定义进行编译处理的代码前面。

#### 宏的进阶用法

除了 `process_record_user()` 函数之外，还有一个 `post_process_record_user()` 函数，该函数会在 `process_record` 之后执行，可用于在按键事件发生时添加额外的行为。比如可以在一个键按下前先按下特定键，并在这个键松开时再松开这个特定键。

下面示例中，我们让大部分常规键按下事件发送前，先按下 `F22` 键，并 __一直到__ 这些常规键松开后，才松开此键。

```c
static uint8_t f22_tracker;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_A ... KC_F21: // 注意这里跳过了 F22
    case KC_F23 ... KC_EXSEL: // exsel 是修饰键之前的最后一个键
      if (record->event.pressed) {
        register_code(KC_F22); // 这里用途是发送 F22 按下事件
        f22_tracker++;
        register_code(keycode);
        return false;
      }
      break;
  }
  return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_A ... KC_F21: // 注意这里跳过了 F22
    case KC_F23 ... KC_EXSL: // exsel 是修饰键之前的最后一个键
      if (!record->event.pressed) {
        f22_tracker--;
        if (!f22_tracker) {
            unregister_code(KC_F22); // 这里用途是发送 F22 抬起事件
        }
      }
      break;
  }
}
```


#### “点击”、“按下”以及“抬起”

在你想在宏里使用那些无法写出来的按键时，可以将它们包在这三个函数里来实现，如 `Ctrl` 和 `Home`：

* `SS_TAP()` 按下并抬起一个键。
* `SS_DOWN()` 按下（但不抬起）一个键
* `SS_UP()` 抬起一个键

例如：

    SEND_STRING(SS_TAP(X_HOME));

这会触发 `KC_HOME` 的点击 - 注意其前缀为 `X_`，而不是 `KC_`。其可以与其它字符串结合使用，如：

    SEND_STRING("VE"SS_TAP(X_HOME)"LO");

这样则会先发送 "VE"，跟随一个 `KC_HOME` 点击事件，之后是发送 "LO"（如果是在一个空行，会拼写出 "LOVE"）。

同样字符串内可以添加延时：

* `SS_DELAY(msecs)` 可以延时指定个毫秒时长。

例如：

    SEND_STRING("VE" SS_DELAY(1000) SS_TAP(X_HOME) "LO");

这样会先发送 "VE"，在1秒的延时后跟随一个 `KC_HOME` 点击事件，之后是发送 "LO"（如果是在一个空行，会拼写出 "LOVE"，但中间会有停顿）。

我们还提供了一些带修饰键的快捷函数：

* `SS_LCTL(string)`
* `SS_LSFT(string)`
* `SS_LALT(string)` 或 `SS_LOPT(string)`
* `SS_LGUI(string)`, `SS_LCMD(string)` 或 `SS_LWIN(string)`
* `SS_RCTL(string)`
* `SS_RSFT(string)`
* `SS_RALT(string)`, `SS_ROPT(string)` 或 `SS_ALGR(string)`
* `SS_RGUI(string)`, `SS_RCMD(string)` 或 `SS_RWIN(string)`

以上函数会先按下对应的修饰键，然后发送给定的字符串，最后松开按下的修饰键。
使用方式如下：

    SEND_STRING(SS_LCTL("a"));

这样会发送 左Control + `a`（左Control按下，点击 `a`，左Control抬起） - 注意这些函数传入的是字符串（如 `"K"`），而不是 `X_K` 这样的键码。

#### 键映射的替换

默认情况下QMK会假设当前使用的是 US 键映射方案的 QWERTY 配列；若想进行更改（例如你的操作系统在使用软件式 Colemak），请在键映射源代码文件中包含以下文件：

```c
#include "sendstring_colemak.h"
```

#### 内存中的字符串

有时基于某些目的，你在内存中维护了一个字符串并且需要将刚生成的字符串输出出来（以取代使用字面量或固定的字符串），可以通过 `sned_string()` 实现，如下：

```c
char my_str[4] = "ok.";
send_string(my_str);
```

前述的快捷函数无法在 `send_string()` 中使用，如有需要，可以将内容分行输出：

```c
char my_str[4] = "ok.";
SEND_STRING("I said: ");
send_string(my_str);
SEND_STRING(".."SS_TAP(X_END));
```


### 进阶宏函数

在编写宏功能时有些辅助函数可能会很有用处。请注意，虽然在宏中可以写出一些相当高级的代码，但当宏过于复杂时，应使用自定义键码作为替代方案。宏应始终保持精简。

?> 可以使用[实用函数](zh-cn/ref_functions.md)以及[检查修饰键状态](zh-cn/feature_advanced_keycodes#checking-modifier-state)中提及的函数实现额外的功能。例如，`reset_keyboard()` 可以作为宏的一部分来重置键盘，`get_mods() & MOD_MASK_SHIFT` 可以检查是否有已被激活的 shift 修饰键。

#### `record->event.pressed`

该布尔值可用来确认开关的按下状态。如下为一个示例：

```c
    if (record->event.pressed) {
        // 按键按下
    } else {
        // 按键抬起
    }
```

#### `register_code(<kc>);`

用于向电脑发送 `<kc>` 的按下事件。例举可用的键码有 `KC_ESC`，`KC_C`，`KC_4`，以及修饰键如 `KC_LSFT` 和 `KC_LGUI`。

#### `unregister_code(<kc>);`

与 `register_code` 函数协同，用于向电脑发送 `<kc>` 的抬起事件。如果你不使用该函数，该键将在下次发送事件前一直保持按下状态。

#### `tap_code(<kc>);`

依次发送 `register_code(<kc>)` 和 `unregister_code(<kc>)`。用于希望按键按下及抬起事件都要发送的时候（触发按键“点击”，而不是按住）。

若定义了 `TAP_CODE_DELAY`（默认值0），该函数会在调用 `unregister_code(<kc>)` 前等待指定的毫秒数。在你遇到点击动作无法释放的问题时可以有所帮助。

若点击的键码是 `KC_CAPS`，其会转为等待 `TAP_HOLD_CAPS_DELAY` 个毫秒（默认值80），这是由于在 macOS 系统中，为了防止误触 Caps Lock 键，需要按下足够的时长才可以被激活。

#### `tap_code_delay(<kc>, <delay>);`

与 `tap_code(<kc>)` 类似，但额外地附带 `delay` 参数用以指定按键释放事件的（相比于固定的宏定义）特定的等待时长。

#### `register_code16(<kc>);`, `unregister_code16(<kc>);` and `tap_code16(<kc>);`

这些函数与其常规版本功能一致，但可以附带修饰键的键码（伴随着 Shift，Alt，Control 和/或 GUI 修饰键）。

即，可以使用 `register_code16(S(KC_5));` 来替代注册（registering）修饰键，再注册所需键码。

#### `clear_keyboard();`

用于清除所有修饰键及常规键的按下状态。

#### `clear_mods();`

用于清除所有修饰键的按下状态。

#### `clear_keyboard_but_mods();`

用于清除除修饰键外所有键的按下状态。

### 进阶示例：

#### 超级 ALT↯TAB

以下宏会先注册 `KC_LALT` 再注册 `KC_TAB`，然后等待1000ms，若时限内再次点击该键，将继续发送一个 `KC_TAB`；若没有点击，`KC_LALT` 将被松开，这样就可以在多个窗口间循环切换。

```c
bool is_alt_tab_active = false; // 将该行添加到 keymap.c 文件的前部
uint16_t alt_tab_timer = 0;     // 稍后会用到

enum custom_keycodes {          // 确保我们所需的炫酷键码可用
  ALT_TAB = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { // 用以处理大部分无聊的键码响应工作
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) { // 核心计时器
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
```
