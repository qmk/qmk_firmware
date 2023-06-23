# 如何定制化键盘功能

<!---
  original document: 0.15.12:docs/custom_quantum_functions.md
  git diff 0.15.12 HEAD -- docs/custom_quantum_functions.md | cat
-->

对于很多人来说对客制化键盘的诉求不只是向电脑输入按下的键。你肯定想实现比简单按键和宏更复杂的功能。QMK支持基于注入点的代码注入，功能重写，另外还可以自定义键盘在不同情况下的行为。

本页不要求任何额外的QMK知识基础，但阅读[理解QMK](zh-cn/understanding_qmk.md)将会在更基础的层面帮你理解发生了什么。

## 核心/键盘/键映射的概念 :id=a-word-on-core-vs-keyboards-vs-keymap

QMK基于如下层级组成：

* Core (`_quantum`)
  * Keyboard/Revision (`_kb`)
    * Keymap (`_user`)

该文后续部分所提及的函数在定义时皆可添加 `_kb()` 或 `_user()` 后缀，我们建议在键盘及其子版本中使用 `_kb()` 后缀，而在键映射中使用 `_user()` 后缀。

在键盘及其子版本中定义函数时，一个重要的点是在 `_kb()` 函数执行任何逻辑前，应先调用 `_user()` 函数，否则这些键映射中的函数将没有机会被执行。
# 自定义键码

到目前为止，最常见的任务是更改现有键码的行为或创建新的键码。从代码角度来看这些操作都很相似。

## 定义一个新键码

创建键码的第一步，是先定义其枚举值，也就是给键码起个名字并分配一个唯一值。QMK没有直接限制最大可用的键码值，而是提供了一个 `SAFE_RANGE` 宏。你可以在定义枚举时用 `SAFE_RANGE` 来保证你取得了唯一的键码值。


这有定义两个键码的枚举值的例子。添加以下代码块至 `keymap.c` 后你就可以在布局中使用 `FOO` 和 `BAR` 了。

```c
enum my_keycodes {
  FOO = SAFE_RANGE,
  BAR
};
```

## 编程设计你的键码的行为 :id=programming-the-behavior-of-any-keycode

当你覆盖一个已存在按键的行为时，或是给新按键设计功能时，请使用 `process_record_kb()` 和 `process_record_user()` 函数。QMK会在响应并处理按键事件前调用这些函数，如果这些函数返回值为 `true`，QMK将继续用常规的方式处理键码，这样可以很方便的扩展键码的功能而不需要替换代码实现。如果函数返回`false` QMK会跳过常规的键处理逻辑，需要发送的按键按下或抬起事件则需交由你负责完成。

任意按键在按下或抬起时，每次都会调用这些函数。

### process_record_user()` 实现示例

这个例子做了两个事。自定义了一个叫做 `FOO` 的键码的行为，并提供了在按下回车时播放音符的功能。

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FOO:
      if (record->event.pressed) {
        // 按下时做些什么
      } else {
        // 抬起时做些什么
      }
      return false; // 跳过此键的所有进一步处理
    case KC_ENTER:
      // 当按下回车时播放音符
      if (record->event.pressed) {
        PLAY_SONG(tone_qwerty);
      }
      return true; // 让QMK响应回车按下/抬起事件
    default:
      return true; // 正常响应其他键码
  }
}
```

### `process_record_*` 实现示例

* 键盘/各子版本：`bool process_record_kb(uint16_t keycode, keyrecord_t *record)`
* 键映射：`bool process_record_user(uint16_t keycode, keyrecord_t *record)`

`keycode` 参数为键映射中形如 `MO(1)`，`KC_L` 等定义的键值项。 应使用 `switch...case` 代码块来处理这些事件。

`record` 参数含有按键的真实状态信息：

```c
keyrecord_t record {
  keyevent_t event {
    keypos_t key {
      uint8_t col
      uint8_t row
    }
    bool     pressed
    uint16_t time
  }
}
```

# 键盘初始化代码

键盘初始化过程须经过几个步骤，而你的目的决定了你需要关注哪些函数。

有三个主要初始化函数，按调用顺序列出。

* `keyboard_pre_init_*` - 会在大多数其他功能运行前执行。适用于那些需要尽早执行的硬件初始化工作。
* `matrix_init_*` - 在固件启动过程中被调用。此时硬件已初始化，但部分功能还不可用。
* `keyboard_post_init_*` - 在固件启动过程的最后被调用。大多数情况下，你的“客制化”代码都可以放在这里。

!> 对于大多数人来说 `keyboard_post_init_user` 是你想要关注的函数。例如, 你可以在这里启动RGB背光灯。

## 键盘预初始化代码

这部分代码执行的非常早，甚至是在USB通信功能启动之前。

在这之后不久即会完成矩阵的初始化。

对于大多数用户来说不应在此处进行修改，因为它主要用于硬件初始化。

但如果你有硬件须初始化的话放在这里再好不过了（比如初始化LED引脚）.

### `keyboard_pre_init_user()` 实现示例

本例中，在键盘层将 B0, B1, B2, B3, 和 B4 引脚设置为LED引脚。

```c
void keyboard_pre_init_user(void) {
  // 调用键盘预初始化代码

  // 设置LED引脚为输出模式
  setPinOutput(B0);
  setPinOutput(B1);
  setPinOutput(B2);
  setPinOutput(B3);
  setPinOutput(B4);
}
```

### `keyboard_pre_init_*` 函数文档

* 键盘/各子版本：`void keyboard_pre_init_kb(void)`
* 键映射：`void keyboard_pre_init_user(void)`

## 矩阵初始化代码

在矩阵初始化后被调用。此时一部分硬件已设置完成，但一些功能尚未完成初始化。 

此处可以用来设置一些与硬件无关，且对初始化位置没有特殊要求的功能。


### `matrix_init_*` 函数文档

* 键盘/各子版本：`void matrix_init_kb(void)`
* 键映射：`void matrix_init_user(void)`

### 低级矩阵函数的重写 :id=low-level-matrix-overrides

* GPIO引脚初始化：`void matrix_init_pins(void)`
  * 此处须完成低级行列引脚的初始化。默认实现中，这里会参考可选的键盘设置项 `ROW2COL`，`COL2ROW` 及 `DIRECT_PINS` 来初始化所有 `MATRIX_ROW_PINS` 及 `MATRIX_COL_PINS` 中定义的GPIO引脚的输入/输出状态。当键盘设计者重写该函数后，QMK本身不会进行任何引脚的初始化，只会听从重写的函数的实现逻辑。
* `COL2ROW`-从行中读: `void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)`
* `ROW2COL`-从列中读: `void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)`
* `DIRECT_PINS`-直读: `void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)`
  * 以上三个函数须参考矩阵类别，从底层矩阵的相关引脚状态中获取输入信息，并且应该只需要实现三者之一。默认情况下，在遍历 `MATRIX_ROW_PINS` and `MATRIX_COL_PINS` 时，会根据是否设置了 `ROW2COL`，`COL2ROW` 或 `DIRECT_PINS` 来配置输入输出方式。当键盘设计者重写该函数后，QMK本身不会进行任何矩阵GPIO引脚状态的变更，只会听从重写的函数的实现逻辑。

## 键盘后初始化代码

这是键盘初始化过程中的最后一个任务。此时您可以配置并调整某些特性，因为此时这些特性已初始化完毕。

### `keyboard_post_init_user()` 实现示例

本示例在所有初始化完成后运行，配置RGB背光。

```c
void keyboard_post_init_user(void) {
  // 调用后初始化代码
  rgblight_enable_noeeprom(); // 使能Rgb，不保存设置
  rgblight_sethsv_noeeprom(180, 255, 255); // 将颜色设置到蓝绿色(青色)，不保存设置
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // 设置快速呼吸模式，不保存设置
}
```

### `keyboard_post_init_*` 函数文档

* 键盘/各子版本：`void keyboard_post_init_kb(void)`
* 布局: `void keyboard_post_init_user(void)`

# 矩阵扫描码

应尽量使用 `process_record_*()` 实现所需的键盘自定义以及事件监听，以确保这些代码不会对键盘性能产生负面的影响。然而，在极少数情况下需要在矩阵扫描中添加监听，此时需要极端留意这些函数代码的性能表现，因为这些函数每秒可能被执行十数次。

### `matrix_scan_*` 实现示例

这个例子被故意省略了。在监听处理这样一个对性能及其敏感的部分之前，您应该足够了解qmk的内部结构，才可以在没有示例的情况下编写。如果你需要帮助，请[新建一个issue](https://github.com/qmk/qmk_firmware/issues/new)或[在Discord上与我们交流](https://discord.gg/Uq7gcHh).

### `matrix_scan_*` 函数文档

* 键盘/各子版本：`void matrix_scan_kb(void)`
* 布局: `void matrix_scan_user(void)`

该函数在每次矩阵扫描时被调用，这基本与MCU处理能力上限相同。在这里写代码要谨慎，因为它会运行很多次。

在需要自定义矩阵扫描代码时可以使用该函数。这也可以用作自定义状态输出(比如LED灯或者屏幕)或者其他即便用户没有输入时你也想定期运行的功能。

# Keyboard housekeeping

* 键盘/各子版本：`void housekeeping_task_kb(void)`
* 键映射：`void housekeeping_task_user(void)`

该函数在所有QMK处理工作完毕后，下一轮开始执行前被执行。可以放心地假设此时QMK已对最新的矩阵扫描结果完成了所有的处理工作 -- 更新层状态，发送USB事件，更新LED状态，刷新显示屏。

与 `matrix_scan_*` 类似，这些函数会频繁调用直至MCU处理能力上限。为了确保键盘的响应能力，建议在这些函数中尽量做最少的事情，在你确实需要在这里实现特别的功能时，可能会影响到其它功能的表现。

# 键盘 空闲/唤醒 代码

在主控板支持情况下，暂停大部分功能可以实现“空闲”状态，例如RGB灯光和背光。既可以节省电量消耗，也可能增强键盘的表现。

这由两个函数控制: `suspend_power_down_*` 和 `suspend_wakeup_init_*`，分别在主控板空闲和唤醒时被调用。


### suspend_power_down_user() 和 suspend_wakeup_init_user() 的实现示例


```c
void suspend_power_down_user(void) {
    // 当键盘挂起时会被多次调用的代码
}

void suspend_wakeup_init_user(void) {
    // 键盘唤醒时被调用的代码
}
```

### 键盘 挂起/唤醒 函数文档

* 键盘/各子版本：`void suspend_power_down_kb(void)` 和 `void suspend_wakeup_init_user(void)`
* 键映射：`void suspend_power_down_kb(void)` 和 `void suspend_wakeup_init_user(void)`

# 层切换代码 :id=layer-change-code

每当层发生切换时被执行，可用于感知层切换事件，或自定义层处理逻辑。

### `layer_state_set_*` 实现示例

本例中，通过Planck键盘示范了如何将[RGB背光灯](zh-cn/feature_rgblight.md)设置为与层同步。

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _RAISE:
        rgblight_setrgb (0x00,  0x00, 0xFF);
        break;
    case _LOWER:
        rgblight_setrgb (0xFF,  0x00, 0x00);
        break;
    case _PLOVER:
        rgblight_setrgb (0x00,  0xFF, 0x00);
        break;
    case _ADJUST:
        rgblight_setrgb (0x7A,  0x00, 0xFF);
        break;
    default: // 默认层及其它层
        rgblight_setrgb (0x00,  0xFF, 0xFF);
        break;
    }
  return state;
}
```

可以通过 `IS_LAYER_ON_STATE(state, layer)` 和 `IS_LAYER_OFF_STATE(state, layer)` 宏来确认常规层的状态。

如果不在 `layer_state_set_*` 函数中，可以通过 `IS_LAYER_ON(layer)` 和 `IS_LAYER_OFF(layer)` 宏来确认全局的层状态。

### `layer_state_set_*` 函数文档

* 键盘/各子版本：`layer_state_t layer_state_set_kb(layer_state_t state)`
* 布局: `layer_state_t layer_state_set_user(layer_state_t state)`


此处的 `state` 为当前活跃层的位掩码, 详见[键映射概述](zh-cn/keymap.md#keymap-layer-status)


# 配置的持久存储（EEPROM）

该功能可以让键盘的配置持久存储下来。这些配置存储在控制器的EEPROM中，即便掉电后依旧可以留存下来。可以通过 `eeconfig_read_kb` 和 `eeconfig_read_user` 来读取，通过 `eeconfig_update_kb` and `eeconfig_update_user` 来进行保存。该功能常用于保存一些开关状态（比如rgb层指示灯）。此外，可以通过 `eeconfig_init_kb` 和 `eeconfig_init_user` 来设置EEPROM的默认配置值。

复杂的地方是，有很多方法可以存储和访问EEPROM数据，并且没有哪种方法是“正确”的。但是，每个功能只有一个双字(四字节)空间可用。

记住EEPROM是有写入寿命的。尽管写入寿命很高，但是并不是只有这些配置信息会写到EEPROM中。如果你写入过于频繁，你的MCU寿命将会急速减少。

* 如果您不理解这个例子，那么您可以不使用这个特性，因为它相当复杂。

### 实现示例

本例讲解了如何添加并读写设置项。本例使用用户键映射来实现。这是一个复杂的函数，有很多事情要做。实际上，它使用了很多前述的函数来工作！
（译注：该示例由于英文行文，可能会觉得看得稀里糊涂。实现的功能很简单，即开启了层指示功能（RGB_LYR）时，rgb背光灯会展示当前层的特定颜色用以指示层状态，而触发任何改变rgb背光颜色的键码时，rgb背光灯将回归普通的背光灯角色，不再作为层指示器）

在你的keymap.c文件中，将以下代码添加至顶部:
```c
typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} user_config_t;

user_config_t user_config;
```

以上代码建立了一个32位的结构体，用于在内存及EEPROM中存储配置项。此时不再需要再单独声明变量，因为都已经在该结构体中定义了。须记住 `bool`（布尔）值占用1位，`uint8_t` 占用8位，`uint16_t` 占用16位。你可以混合搭配使用，但改变这些顺序会因为错误的读写而招致问题。

我们在 `layer_state_set_*` 函数中会使用 `rgb_layer_change`。通过 `keyboard_post_init_user` 和 `process_record_user` 来配置所需的一切。

在编写 `keyboard_post_init_user` 时，你需要使用 `eeconfig_read_user()` 来计算并填充你刚刚创建的结构体。然后即可以使用结构体数据来控制键映射中的功能。就像这样： 
```c
void keyboard_post_init_user(void) {
  // 调用键映射级别的矩阵初始化

  // 从EEPROM读用户配置
  user_config.raw = eeconfig_read_user();

  // 如使能，设置默认层
  if (user_config.rgb_layer_change) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom_cyan(); 
    rgblight_mode_noeeprom(1);
  }
}
```
以上函数会在读EEPROM配置后立即设置默认层的RGB颜色。"raw"值将被转换为上述创建的实际使用的"union"结构体。 

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _RAISE:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_magenta(); rgblight_mode_noeeprom(1); }
        break;
    case _LOWER:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_red(); rgblight_mode_noeeprom(1); }
        break;
    case _PLOVER:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_green(); rgblight_mode_noeeprom(1); }
        break;
    case _ADJUST:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_white(); rgblight_mode_noeeprom(1); }
        break;
    default: //  针对其他层或默认层
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_cyan(); rgblight_mode_noeeprom(1); }
        break;
    }
  return state;
}
```
这样仅在相关值使能时才会改变RGB背光灯。若要配置该值, 为 `process_record_user` 创建一个新键码 `RGB_LYR`。此时我们想实现的是，如果触发了常规的RGB码，以上示例中的逻辑都将不生效，形如：
```c

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FOO:
      if (record->event.pressed) {
        // 按下时做点什么
      } else {
        // 抬起时做点什么
      }
      return false; // 跳过此键的进一步处理
    case KC_ENTER:
        // 在按下回车时播放音符
        if (record->event.pressed) {
            PLAY_SONG(tone_qwerty);
        }
        return true; // 让QMK产生回车按下/抬起事件
    case RGB_LYR:  // 这允许我们将背光灯作为层指示，或正常用途
        if (record->event.pressed) { 
            user_config.rgb_layer_change ^= 1; // 切换状态
            eeconfig_update_user(user_config.raw); // 向EEPROM写入新状态
            if (user_config.rgb_layer_change) { // 如果层指示功能被使能
                layer_state_set(layer_state);   // 那么立刻更新层颜色
            }
        }
        return false;
    case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // 对于所有的RGB代码 (参考 quantum_keycodes.h, 400 行处)
        if (record->event.pressed) { // 本句失能层指示功能，假设你现在要调整该功能…你要把它禁用
            if (user_config.rgb_layer_change) {        // 仅当使能时
                user_config.rgb_layer_change = false;  // 失能，然后
                eeconfig_update_user(user_config.raw); // 向EEPROM写入设置
            }
        }
        return true; break;
    default:
      return true; // 其他键码正常处理
  }
}
```
最后，须添加 `eeconfig_init_user` 函数，从而当EEPROM重置时，可以指定默认值, 甚至自定义操作。若想强制重置EEPROM，请用 `EEP_RST` 键码或[Bootmagic](zh-cn/feature_bootmagic.md) 功能。比如，在你想重置RGB层指示配置，并保存默认值时。

```c
void eeconfig_init_user(void) {  // EEPROM被重置
  user_config.raw = 0;
  user_config.rgb_layer_change = true; // 我们想要默认使能
  eeconfig_update_user(user_config.raw); // 向EEPROM写入默认值

  // 通过使用非'noeeprom'版本的函数，可以同时写入这些配置到EEPROM中。
  rgblight_enable(); // 默认使能RGB
  rgblight_sethsv_cyan();  // 默认设置青色
  rgblight_mode(1); // 默认设置长亮
}
```

一切已就绪，RGB层指示将在需要时生效。这个设置会持久存储，即便是拔下键盘。如果你使用其他RGB码，层指示将失效，从而可以停留在期望的模式及颜色下。

### 'EECONFIG' 函数文档

* 键盘/各子版本：`void eeconfig_init_kb(void)`, `uint32_t eeconfig_read_kb(void)` 和 `void eeconfig_update_kb(uint32_t val)`
* 键映射：`void eeconfig_init_user(void)`, `uint32_t eeconfig_read_user(void)` 和 `void eeconfig_update_user(uint32_t val)`

`val` 是你想写入EEPROM的值，`eeconfig_read_*`函数会从EEPROM返回一个32位(双字)的值。

### 定时执行 :id=deferred-execution

QMK支持在特定时间间隔后执行回调，以代替手动的计时器管理。

#### 定时回调函数

所有的 _定时回调函数_ 使用同样的函数签名，如下：

```c
uint32_t my_callback(uint32_t trigger_time, void *cb_arg) {
    /* 处理了一些工作 */
    bool repeat = my_deferred_functionality();
    return repeat ? 500 : 0;
}
```

第一个参数 `trigger_time` 为预期的执行时间，如果因为其它事情造成了延迟未能在准确的时间点执行，可以利用这个参数“追赶”或者跳过这次间隔，取决于你的目的是什么。

第二个参数 `cb_arg` 为下述的 `defer_exec()` 传入的参数，由此可以获取调用时的状态信息。

返回值为该函数下一次期望被回调的时间间隔毫秒数 -- 若返回 `0` 则会自动被注销掉。上例中，通过执行假想的 `my_deferred_functionality()` 函数来决策回调是否继续下去 -- 若是，则给出一个 `500` 毫秒的延迟计划，否则，返回 `0` 来告知定时处理后台任务该计划已执行完毕。

?> 须留意返回的延时时间是相对原定的触发时间点的，而不是回调执行完的时间点。这样可以防止偶发的执行延迟影响稳定的定时事件计划。

#### 注册定时回调

在定义好回调后，通过如下API进行定时回调注册：

```c
deferred_token my_token = defer_exec(1500, my_callback, NULL);
```

第一个参数为执行 `my_callback` 的毫秒时间延迟 -- 上例中为 `1500` 毫秒，即 1.5 秒。

第三个参数为回调执行时传入的 `cb_arg` 参数。须确保该值在回调时依旧有效 -- 局部函数内的变量会在回调执行前就被释放掉因此不能用。如果并不需要这个参数，可以传入 `NULL`。

返回值 `deferred_token` 可被用于在回调执行前取消该定时计划。如果该函数调用失败，会返回 `INVALID_DEFERRED_TOKEN`，一般错误原因是延时值被设置为 `0` 或回调函数参数为 `NULL`，还有一种可能是已有过量的回调在等待被处理 -- 可以按照下述方法修改这个阈值。

#### 延长定时回调时间

由 `defer_exec()` 返回的 `deferred_token` 可以用来修改回调执行所需等待的时延值：
```c
// 重新调整 my_token 后续的执行计划为当前时间起800ms后
extend_deferred_exec(my_token, 800);
```

#### 取消定时回调

由 `defer_exec()` 返回的 `deferred_token` 可以用来取消掉后续的执行计划：
```c
// 取消 my_token 的后续回调
cancel_deferred_exec(my_token);
```

一旦 token 被取消了，即视为不再可用。重新使用该 token 是不支持的。

#### 定时回调的限制

可安排的定时回调计划数量是有限的，由 `MAX_DEFERRED_EXECUTORS` 定义的值确定。

如果定时回调注册失败了，可以在对应的键盘或键映射下的 `config.h` 文件中修改该值，比如将默认的 8 改为 16：

```c
#define MAX_DEFERRED_EXECUTORS 16
```
