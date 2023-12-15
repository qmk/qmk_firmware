# 键映射总览

<!---
  original document: 0.15.12:docs/keymap.md
  git diff 0.15.12 HEAD -- docs/keymap.md | cat
-->

QMK键映射定义在C源文件中，其数据结构上是一个容纳了数组的数组。外层数组容纳了各个层，内层各数组则为层内的键列表。基本所有键盘都通过定义 `LAYOUT()` 宏来创建该两级数组。


## 键映射与配列 :id=keymap-and-layers
在QMK中, **`const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS]`** 容纳了多个 **层**， 每个**层**下包含了由**16位**的**动作码**所组成的键映射信息。 最多可以定义**32个层**。

对于常规键的定义，其**动作码**的高8位皆为0，低8位保存了USB HID中使用的各个键对应的**键码**。

不同的层可以同时生效，层的编号从0至31，编号越高的层优先级越高。
（译注：由于是ascii图，掺杂中文会导致排版错乱，各翻译标注在图下方。下同）

    Keymap: 32 Layers                   Layer: action code matrix
    -----------------                   ---------------------
    stack of layers                     array_of_action_code[row][column]
           ____________ precedence               _______________________
          /           / | high                  / ESC / F1  / F2  / F3   ....
      31 /___________// |                      /-----/-----/-----/-----
      30 /___________// |                     / TAB /  Q  /  W  /  E   ....
      29 /___________/  |                    /-----/-----/-----/-----
       :   _:_:_:_:_:__ |               :   /LCtrl/  A  /  S  /  D   ....
       :  / : : : : : / |               :  /  :     :     :     :
       2 /___________// |               2 `--------------------------
       1 /___________// |               1 `--------------------------
       0 /___________/  V low           0 `--------------------------
翻译：

|原文                       |译文         |
|--------------------------|-------------|
|Keymap: 32 Layers         | 键映射：32个层|
|stack of layers           | 层堆栈       |
|precedence                | 优先级       |
|high/low                  | 高/低        |
|layer: action code matrix | 层：动作码矩阵|
|row/column                | 行/列        |

有时，键映射中存储的动作码在一些文档中也被称作键码，主要是由TMK沿袭而来的习惯。

### 键映射的层状态 :id=keymap-layer-status

键映射的层状态由两个32位参数决定：

* **`default_layer_state`** 指向一个总是可用的键映射层（0-31）（即默认层）。
* **`layer_state`** 每一位标记对应层的启用/停用状态。

通常键映射中的'0'层为 `default_layer（默认层）`，其它层在启动时会被固件置为停用状态，不过这些可以通过 `config.h` 进行配置。当你换了一个按键布局时可用于更改 `default_layer`，比如从Qwerty布局切换到了Colemak布局。

    Initial state of Keymap          Change base layout
    -----------------------          ------------------

      31                               31
      30                               30
      29                               29
       :                                :
       :                                :   ____________
       2   ____________                 2  /           /
       1  /           /              ,->1 /___________/
    ,->0 /___________/               |  0
    |                                |
    `--- default_layer = 0           `--- default_layer = 1
         layer_state   = 0x00000001       layer_state   = 0x00000002
翻译：

|原文                    |译文         |
|-----------------------|-------------|
|Initial state of Keymap| 键映射原始状态|
|Change base layout     | 更改了基础层  |

另外，可以通过修改 `layer_state` 做到其他层对基础层的覆盖，以实现诸如导航键、功能键（F1-F12）、多媒体键等特殊动作。

    Overlay feature layer
    ---------------------      bit|status
           ____________        ---+------
      31  /           /        31 |   0
      30 /___________// -----> 30 |   1
      29 /___________/  -----> 29 |   1
       :                        : |   :
       :   ____________         : |   :
       2  /           /         2 |   0
    ,->1 /___________/  ----->  1 |   1
    |  0                        0 |   0
    |                                 +
    `--- default_layer = 1            |
         layer_state   = 0x60000002 <-'



### 层优先级及穿透
须记住**层堆栈中更高的层有着更高的优先级**。固件会从最高的活跃层开始向下找键码，一旦固件在活跃层上找到了一个非 `KC_TRNS`（穿透）键码，就会停止查找，再往下的层级不会被查看。

           ____________
          /           /  <--- 较高的层
         /  KC_TRNS  //
        /___________//   <--- 较低的层 (KC_A)
        /___________/
    
    这个场景中，较高层级中的非穿透键是可用的，如果定义为 `KC_TRNS`（及同等效果的），较低层级的键码 `KC_A` 将被采纳。

**注意：** 在层中定义合法的穿透键的方法有：
* `KC_TRANSPARENT`
* `KC_TRNS`（别名）
* `_______`（别名）

这些键码允许在搜索非穿透键码时可以穿透当前层下落到更低层去。

## `keymap.c` 文件解析

本例中我们将深入到[Clueboard 66%的一款旧版的默认键映射](https://github.com/qmk/qmk_firmware/blob/ca01d94005f67ec4fa9528353481faa622d949ae/keyboards/clueboard/keymaps/default/keymap.c)方案中去。将该文件在另一个浏览器窗口中打开，以便对照本文进行同步阅览。

在一个 `keymap.c` 文件中会有三个你可能会关心的部分：

* [预定义](#definitions)
* [层/键映射数据结构](#layers-and-keymaps)
* [自定义函数](#custom-functions)，若有的话

### 预定义

文件头部可以看到：

    #include QMK_KEYBOARD_H

    // Helpful defines
    // 译：便捷性的宏定义
    #define GRAVE_MODS  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)|MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI)|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
     *  You can use _______ in place for KC_TRNS (transparent)   *
     *  Or you can use XXXXXXX for KC_NO (NOOP)                  *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    // 译：可以用 _______ 替代 KC_TRNS（穿透），用 XXXXXXX 替代 KC_NO (空操作)

    // Each layer gets a name for readability.
    // The underscores don't mean anything - you can
    // have a layer called STUFF or any other name.
    // Layer names don't all need to be of the same
    // length, and you can also skip them entirely
    // and just use numbers.
    // 译：每一层为了便于识别可以起一个名字，下划线没有实际意义 - 叫STUFF之类的也行的，
    // 译：层名不需要都一样长，甚至不定义这些直接用层号也是可以的
    enum layer_names {
        _BL,
        _FL,
        _CL,
    };

以上是一些便于编写键映射及自定义函数时可用的预定义，`GRAVE_MODS` 后续会用在自定义函数中，之后的 `_BL`, `_FL` 及 `_CL` 便于我们在代码中引用这些层。

注：在一些更早的键映射文件中，你可能会发现一些形如 `_______` 或 `XXXXXXX` 的定义，这些可以分别代替 `KC_TRNS` 及 `KC_NO`，这样可以更清楚地分辨出各层中定义了哪些键的键值。现在这些定义是不需要的，因为我们默认已经提供了这些定义。

### 层和键映射

这个文件中最主要的部分是 `keymaps[]` 定义，这里须列出你的层以及层中的内容。这一部分应该以如下定义起始：

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

之后是一个LAYOUT()宏组成的列表，一个LAYOUT()下定义了一个层中的键列表，一般你需要至少一个“基础层”（如QWERTY、Dvorak或Colemak），之后是在其之上的多个“功能”层。受限于对层的处理顺序，较低的层无法覆盖在较高的层上。

QMK在 `keymaps[][MATRIX_ROWS][MATRIX_COLS]` 中保存着16位的动作码（有些时候也被称作键码），对于与常规键一致的键码，其高字节为0，低字节为USB HID 键盘所使用的键码值。

> QMK的前身TMK中使用 `const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS]` 来存储8位的键码，一些键码被保留用于引用执行 `fn_actions[]` 数组中的特定功能。

#### 基础层

以下示例是Clueboard的基础层定义：

      /* Keymap _BL: Base Layer (Default Layer)
       */
    [_BL] = LAYOUT(
      F(0),    KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_GRV,  KC_BSPC,          KC_PGUP, \
      KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,                   KC_PGDN, \
      KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,                             \
      KC_LSFT, KC_NUBS, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,   KC_SLSH,  KC_RO,    KC_RSFT,          KC_UP,            \
      KC_LCTL, KC_LGUI, KC_LALT, KC_MHEN,          KC_SPC,KC_SPC,                        KC_HENK,  KC_RALT,  KC_RCTL,  MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT),

这里有一些值得留意的地方：

* 站在C语言源代码的角度看，这只是一个数组，但我们掺杂了大量括号使得每个键可以在视觉上与物理设备对齐。
* 常规的键盘扫描码以KC_起始，而那些“特殊”键则不是。
* 最左上的键可以触发自定义函数0（`F(0)`）
* "Fn"键定义为 `MO(_FL)`，当按住该键时会切换到 `_FL` 层。

#### 功能覆盖层

对于功能层，从代码角度讲与基础层没有任何区别。但在概念上讲，应该将其作为覆盖层而非替代层来定义。对大部分人来讲这个区别不重要，但当你构建越来越复杂的层结构时，其重要性会越来越凸显。

    [_FL] = LAYOUT(
      KC_GRV,  KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______, KC_DEL,           BL_STEP, \
      _______, _______, _______,_______,_______,_______,_______,_______,KC_PSCR,KC_SCRL, KC_PAUS,  _______,  _______,  _______,                   _______, \
      _______, _______, MO(_CL),_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______,                           \
      _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______,          KC_PGUP,         \
      _______, _______, _______, _______,        _______,_______,                        _______,  _______,  _______,  MO(_FL), KC_HOME, KC_PGDN, KC_END),

这里值得留意的有：

* 我们使用 `_______` 定义来替代 `KC_TRNS`， 以便凸显在该层中有变化的那些键。
* 对于这一层来讲，如果点击的是一个 `_______` 键，实际生效的将是其下的活跃层中的键。

# 核心细节

在阅读完本节后，你应该掌握了构建自己的键映射的基础能力，更多的资料请参见：

* [键码](zh-cn/keycodes.md)
* [键映射FAQ](zh-cn/faq_keymap.md)

我们仍在优化这份文档，如果你有更好的优化建议，请[提交一份issue](https://github.com/qmk/qmk_firmware/issues/new)！
