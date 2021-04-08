# 如何定制你键盘的功能

对于很多人来说客制化键盘可不只是向你的电脑发送你按了那个件这么简单。你肯定想实现比简单按键和宏更复杂的功能。QMK有能让你注入代码的钩子, 覆盖功能, 另外，还可以自定义键盘在不同情况下的行为。

本页不假定任何特殊的QMK知识，但阅读[理解QMK](understanding_qmk.md)将会在更基础的层面帮你理解发生了什么。

## A Word on Core vs 键盘 vs 布局

我们把qmk组织成一个层次结构：

* Core (`_quantum`)
  * Keyboard/Revision (`_kb`)
    * Keymap (`_user`)

下面描述的每一个函数都可以在定义上加一个`_kb()`或 `_user()` 后缀。 建议在键盘/修订层使用`_kb()`后缀，在布局层使用`_user()`后缀。

在键盘/修订层定义函数时，`_kb()`在执行任何代码前先调用`_user()`是必要的，不然布局层函数就不要被调用。
<!-- 翻译问题：上面那句翻译的不太好-->
# 自定义键码

到目前为止，最常见的任务是更改现有键码的行为或创建新的键码。从代码角度来看这些操作都很相似。

## 定义一个新键码

创建键码第一步，先枚举出它全部，也就是给键码起个名字并分配唯一数值。QMK没有直接限制最大键码值大小，而是提供了一个`SAFE_RANGE`宏。你可以在枚举时用`SAFE_RANGE`来保证你取得了唯一的键码值。


这有枚举两个键码的例子。把这块加到`keymap.c`的话你就在布局中能用`FOO`和`BAR`了。

```c
enum my_keycodes {
  FOO = SAFE_RANGE,
  BAR
};
```

## 为键码的行为编程

当你覆盖一个已存在按键的行为时，或将这个行为赋给新键时，你要用`process_record_kb()`和`process_record_user()`函数。这俩函数在键处理中真实键事件被处理前被QMK调用。如果这俩函数返回`true`，QMK将会用正常的方式处理键码。这样可以很方便的扩展键码的功能而不是替换它。如果函数返回`false` QMK会跳过正常键处理，然后发送键子抬起还是按下事件就由你决定了。

当某个键按下或释放时这俩函数会被调用。

### process_record_user()`函数示例实现

这个例子做了两个事。自定义了一个叫做`FOO`的键码的行为，并补充了在按下回车时播放音符。

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FOO:
      if (record->event.pressed) {
        // 按下时做些什么
      } else {
        // 释放时做些什么
      }
      return false; // 跳过此键的所有进一步处理
    case KC_ENTER:
      // 当按下回车时播放音符
      if (record->event.pressed) {
        PLAY_SONG(tone_qwerty);
      }
      return true; // 让QMK触发回车按下/释放事件
    default:
      return true; // 正常处理其他键码
  }
}
```

### `process_record_*` 函数文档

* 键盘/修订: `bool process_record_kb(uint16_t keycode, keyrecord_t *record)`
* 布局: `bool process_record_user(uint16_t keycode, keyrecord_t *record)`

`keycode(键码)`参数是在布局上定义的，比如`MO(1)`, `KC_L`, 等等。 你要用 `switch...case` 块来处理这些事件。

`record`参数含有实际按键的信息：

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

# LED控制

qmk提供了读取HID规范包含的5个LED的方法。:

* `USB_LED_NUM_LOCK`
* `USB_LED_CAPS_LOCK`
* `USB_LED_SCROLL_LOCK`
* `USB_LED_COMPOSE`
* `USB_LED_KANA`

这五个常量对应于主机LED状态的位置位。
有两种方法可以获得主机LED状态：

* 通过执行 `led_set_user()`
* 通过调用 `host_keyboard_leds()`

## `led_set_user()`

当5个LED中任何一个的状态需要改变时，此函数将被调用。此函数通过参数输入LED参数。
使用`IS_LED_ON(usb_led, led_name)`和`IS_LED_OFF(usb_led, led_name)`这两个宏来检查LED状态。

!> `host_keyboard_leds()`可能会在`led_set_user()`被调用前返回新值。

### `led_set_user()`函数示例实现

```c
void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinLow(B0);
    } else {
        writePinHigh(B0);
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinLow(B1);
    } else {
        writePinHigh(B1);
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinLow(B2);
    } else {
        writePinHigh(B2);
    }
    if (IS_LED_ON(usb_led, USB_LED_COMPOSE)) {
        writePinLow(B3);
    } else {
        writePinHigh(B3);
    }
    if (IS_LED_ON(usb_led, USB_LED_KANA)) {
        writePinLow(B4);
    } else {
        writePinHigh(B4);
    }
}
```

### `led_set_*`函数文档

* 键盘/修订: `void led_set_kb(uint8_t usb_led)`
* 布局: `void led_set_user(uint8_t usb_led)`

## `host_keyboard_leds()`

调用这个函数会返回最后收到的LED状态。这个函数在`led_set_*`之外读取LED状态时很有用，比如在[`matrix_scan_user()`](#矩阵扫描代码).
为了便捷，你可以用`IS_HOST_LED_ON(led_name)`和`IS_HOST_LED_OFF(led_name)` 宏，而不直接调用和检查`host_keyboard_leds()`。

## 设置物理LED状态

一些键盘实现了为设置物理LED的状态提供了方便的方法。

### Ergodox Boards

Ergodox实现了提供`ergodox_right_led_1`/`2`/`3_on`/`off()`来让每个LED开或关, 也可以用 `ergodox_right_led_on`/`off(uint8_t led)` 按索引打开或关闭他们。

此外，还可以使用`ergodox_led_all_set(uint8_t n)`指定所有LED的亮度级别；针对每个LED用`ergodox_right_led_1`/`2`/`3_set(uint8_t n)`；使用索引的话用`ergodox_right_led_set(uint8_t led, uint8_t n)`。

Ergodox boards 同时定义了最低亮度级别`LED_BRIGHTNESS_LO`和最高亮度级别`LED_BRIGHTNESS_HI`(默认最高).

# 键盘初始化代码

键盘初始化过程有几个步骤。你是用那个函数取决于你想要做什么。

有三个主要初始化函数，按调用顺序列出。

* `keyboard_pre_init_*` - 会在大多数其他东西运行前运行。适用于哪些需要提前运行的硬件初始化。
* `matrix_init_*` - 在固件启动过程中间被调用。此时硬件已初始化，功能尚未初始化。
* `keyboard_post_init_*` - 在固件启动过程最后被调用。大多数情况下，你的“客制化”代码都可以放在这里。

!> 对于大多数人来说`keyboard_post_init_user`是你想要调用的函数。例如, 此时你可以设置RGB灯发光。

## 键盘预初始化代码

这代码极早运行，甚至都在USB初始化前运行。

在这之后不久矩阵就被初始化了。

对于大多数用户来说,这用不到，因为它主要是用于面向硬件的初始化。

但如果你有硬件初始化的话放在这里再好不过了(比如初始化LED引脚一类的).

### `keyboard_pre_init_user()`函数示例实现

本例中在键盘级别，设定 B0, B1, B2, B3, 和 B4 是LED引脚。

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

* 键盘/修订: `void keyboard_pre_init_kb(void)`
* 布局: `void keyboard_pre_init_user(void)`

## 矩阵初始化代码

这将会在矩阵初始化时被调用，在某些硬件设置好后，但在一些功能被初始化前。 

这在你设置其他地方会用到的东西的时候会很有用，但与硬件无关，也不依赖于它的启动位置。


### `matrix_init_*`函数文档

* 键盘/修订: `void matrix_init_kb(void)`
* 布局: `void matrix_init_user(void)`


## 键盘后初始化代码

这是键盘初始化过程中的最后一个任务。如果您想更改某些特性，这会很有用，因为此时应该对它们进行初始化。


### `keyboard_post_init_user()`示例实现

本示例在所有初始化完成后运行，配置RGB灯。

```c
void keyboard_post_init_user(void) {
  // 调用后初始化代码
  rgblight_enable_noeeprom(); // 使能Rgb，不保存设置
  rgblight_sethsv_noeeprom(180, 255, 255); // 将颜色设置到蓝绿色(青色)不保存
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // 设置快速呼吸模式不保存
}
```

### `keyboard_post_init_*` 函数文档

* 键盘/修订: `void keyboard_post_init_kb(void)`
* 布局: `void keyboard_post_init_user(void)`

# 矩阵扫描代码

可能的话你要用`process_record_*()`自定义键盘，以这种方式连接到事件中，以确保代码不会对键盘产生负面的性能影响。然而，在极少数情况下，有必要进行矩阵扫描。在这些函数中要特别注意代码的性能，因为它每秒至少被调用10次。

### `matrix_scan_*`示例实现

这个例子被故意省略了。在hook这样一个对性能及其敏感的区域之前，您应该足够了解qmk的内部结构，以便在没有示例的情况下编写。如果你需要帮助，请[建立一个issue](https://github.com/qmk/qmk_firmware/issues/new)或[在Discord上与我们交流](https://discord.gg/Uq7gcHh).

### `matrix_scan_*` 函数文档

* 键盘/修订: `void matrix_scan_kb(void)`
* 布局: `void matrix_scan_user(void)`

该函数在每次矩阵扫描时被调用，这基本与MCU处理能力上限相同。在这里写代码要谨慎，因为它会运行很多次。

你会在自定义矩阵扫描代码时用到这个函数。这也可以用作自定义状态输出(比如LED灯或者屏幕)或者其他即便用户不输入你也想定期运行的功能。


# 键盘 空闲/唤醒 代码

如果键盘支持就可以通过停止一大票功能来达到"空闲"。RGB灯和背光就是很好的例子。这可以节约能耗，也可能让你键盘风味更佳。

用两个函数控制: `suspend_power_down_*`和`suspend_wakeup_init_*`, 分别在系统板空闲和唤醒时调用。


### suspend_power_down_user()和suspend_wakeup_init_user()示例实现


```c
void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}
```

### 键盘 挂起/唤醒 函数文档

* 键盘/修订: `void suspend_power_down_kb(void)` 和`void suspend_wakeup_init_user(void)`
* 布局: `void suspend_power_down_kb(void)` 和 `void suspend_wakeup_init_user(void)`

# 层改变代码

每当层改变这个就运行代码。这对于层指示或自定义层处理很有用。

### `layer_state_set_*` 示例实现

本例使用了Planck键盘示范了如何设置 [RGB背光灯](feature_rgblight.md)使之与层对应

```c
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
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
    default: //  for any other layers, or the default layer
        rgblight_setrgb (0x00,  0xFF, 0xFF);
        break;
    }
  return state;
}
```
### `layer_state_set_*` 函数文档

* 键盘/修订: `uint32_t layer_state_set_kb(uint32_t state)`
* 布局: `uint32_t layer_state_set_user(uint32_t state)`


该`状态`是活动层的bitmask, 详见[布局概述](keymap.md#布局的层状态)


# 掉电保存配置 (EEPROM)

这会让你的配置长期的保存在键盘中。这些配置保存在你主控的EEPROM里，掉电不会消失。 设置可以用`eeconfig_read_kb`和`eeconfig_read_user`读取，可以用`eeconfig_update_kb`和`eeconfig_update_user`写入。这对于您希望能够切换的功能很有用(比如切换RGB层指示。此外，你可以用`eeconfig_init_kb`和`eeconfig_init_user`来设置EEPROM默认值。 

最复杂的部分可能是，有很多方法可以通过EEPROM存储和访问数据，并且并没有用哪种方法是“政治正确”的。你每个功能只有一个双字(四字节)空间。

记住EEPROM是有写入寿命的。尽管写入寿命很高，但是并不是只有设置写道EEPROM中。如果你写入频繁，你的MCU寿命将会变短。

* 如果您不理解这个例子，那么您可能希望避免使用这个特性，因为它相当复杂。

### 示例实现

本例讲解了如何添加设置，并且读写。本里使用了用户布局。这是一个复杂的函数，有很多事情要做。实际上，它使用了很多上述函数来工作！


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

以上代码建立了一个结构体，该结构体可以存储设置并可用于写入EEPROM。如此这般将无需定义变量，因为在结构体中已然定义。要记住`bool` (布尔)值使用1位, `uint8_t`使用8位, `uint16_t`使用16位。你可以混合搭配使用，但是顺序记错可能会招致麻烦，因为那会改变写入写出的值。 

 `layer_state_set_*`函数中使用了`rgb_layer_change`，使用了`keyboard_post_init_user`和`process_record_user`来配置一切。

首先要使用`keyboard_post_init_user，你要加入`eeconfig_read_user()`来填充你刚刚创建的结构体。然后您可以立即使用这个结构来控制您的布局中的功能。就像这样： 
```c
void keyboard_post_init_user(void) {
  // 调用布局级别的矩阵初始化

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
以上函数会在读EEPROM配置后立即使用该设置来设置默认层RGB颜色。"raw"的值是从你上面基于"union"创建的结构体中转换来的。 

```c
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
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
这样仅在值使能时会改变RGB背光灯。现在配置这个值, 为`process_record_user`创建一个新键码叫做`RGB_LYR`。我们要确保，如果使用正常的RGB代码，使用上面的示例将其关闭，请将其设置为：
```c

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FOO:
      if (record->event.pressed) {
        // 按下时做点什么
      } else {
        // 释放时做点什么
      }
      return false; // 跳过此键的进一步处理
    case KC_ENTER:
        // 在按下回车时播放音符
        if (record->event.pressed) {
            PLAY_SONG(tone_qwerty);
        }
        return true; // 让QMK产生回车按下/释放事件
    case RGB_LYR:  // 本句让underglow作为层指示，或正常使用。
        if (record->event.pressed) { 
            user_config.rgb_layer_change ^= 1; // 切换状态
            eeconfig_update_user(user_config.raw); // 向EEPROM写入新状态
            if (user_config.rgb_layer_change) { // 如果层状态被使能
                layer_state_set(layer_state);   // 那么立刻更新层颜色
            }
        }
        return false;
    case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // 对于所有的RGB代码 (see quantum_keycodes.h, L400 可以参考)
        if (record->event.pressed) { //本句失能层指示，假设你改变了这个…你要把它禁用
            if (user_config.rgb_layer_change) {        // 仅当使能时
                user_config.rgb_layer_change = false;  // 失能，然后 
                eeconfig_update_user(user_config.raw); // 向EEPROM写入设置
            }
        }
        return true; break;
    default:
      return true; // 按其他键正常
  }
}
```
最后你要加入`eeconfig_init_user`函数，所以当EEPROM重置时，可以指定默认值, 甚至自定义操作。想强制重置EEPROM，请用`EEP_RST`键码或[Bootmagic](feature_bootmagic.md)函数。比如，如果要在默认情况下设置RGB层指示，并保存默认值

```c
void eeconfig_init_user(void) {  // EEPROM正被重置
  user_config.raw = 0;
  user_config.rgb_layer_change = true; // 我们想要默认使能
  eeconfig_update_user(user_config.raw); // 向EEPROM写入默认值

  // use the non noeeprom versions, 还要向EEPROM写入这些值
  rgblight_enable(); // 默认使能RGB
  rgblight_sethsv_cyan();  // 默认设置青色
  rgblight_mode(1); // 默认设置长亮
}
```

然后就完事了。RGB层指示会在你想让它工作时工作。这个设置会一直保存，即便你拔下键盘。如果你使用其他RGB代码，层指示将失能，现在它可以做你所想了。 

### 'EECONFIG' 函数文档

* 键盘/修订: `void eeconfig_init_kb(void)`, `uint32_t eeconfig_read_kb(void)`和`void eeconfig_update_kb(uint32_t val)`
* 布局: `void eeconfig_init_user(void)`, `uint32_t eeconfig_read_user(void)`和`void eeconfig_update_user(uint32_t val)`

`val` 是你想写入EEPROM的值，`eeconfig_read_*`函数会从EEPROM返回一个32位(双字)的值。

# 自定义击键-长按临界值(TAPPING_TERM)
默认情况下,击键-长按临界值是全球统一的，并且不能通过键进行配置。对于大多数用户来说这很好。但是在有些情况下，对于`LT`键来说按键延时对双功能键的提升更大，可能是因为有些键比其他的键更容易按住。为了不给每个都自定义键码，本功能可以为每个键定义`TAPPING_TERM`。

想使能这个功能的话, 要先在`config.h`加上`#define TAPPING_TERM_PER_KEY`。


## `get_tapping_term`示例实现

想要修改基于键码的`TAPPING TERM`,你要向`keymap.c`文件添加如下代码: 

```c
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SFT_T(KC_SPC):
      return TAPPING_TERM + 1250;
    case LT(1, KC_GRV):
      return 130;
    default:
      return TAPPING_TERM;
  }
}
```

### `get_tapping_term` 函数文档

不像这篇的其他功能,这个不需要quantum或者键盘级别的函数，只要用户级函数即可。
