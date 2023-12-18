#  调试 FAQ

<!---
  original document: 0.15.12:docs/faq_debug.md
  git diff 0.15.12 HEAD -- docs/faq_debug.md | cat
-->

此页面详细介绍了人们对键盘故障排除的各种常见问题。

## 调试 :id=debugging

如果你在 `rules.mk` 中配置了 `CONSOLE_ENABLE = yes`，你的键盘将会输出调试信息。默认情况下输出很有限，可以启用调试模式来增加调试输出的丰富度。使用你的键映射方案中的 `DEBUG` 键码，或使用[指令](zh-cn/feature_command.md)功能来启动调试模式，或者将下面这段代码放到你的键映射中：

```c
void keyboard_post_init_user(void) {
  // 通过调整这些值可以改变其表现
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```

## 调试工具

有多种可用于调试的工具。

### 使用QMK工具箱调试

在兼容的平台上，[QMK工具箱](https://github.com/qmk/qmk_toolbox)可以展示你的键盘的调试输出。

### 使用 QMK CLI 进行调试

倾向于在终端进行调试？使用 [QMK CLI 命令行](zh-cn/cli_commands.md#qmk-console)可以展示键盘输出的调试信息。

### 使用hid_listen调试

更喜欢使用终端的方案？PJRC提供的[hid_listen](https://www.pjrc.com/teensy/hid_listen.html)也可以用来展示调试信息，已有Windows、Linux及MacOS下预编译好的可执行文件。

## 发送自定义调试信息 :id=debug-api

有时在[自定义代码](zh-cn/custom_quantum_functions.md)中输出调试信息非常有用，要做到这个功能也很简单，在代码文件头部包含 `print.h` 文件：

```c
#include "print.h"
```

然后可以使用以下输出函数：

* `print("string")`: 字符串输出
* `uprintf("%s string", var)`: 格式化字符串输出
* `dprint("string")` 仅调试模式下，字符串输出
* `dprintf("%s string", var)`: 仅调试模式下，格式化字符串输出

## 调试示例

以下列出了一些实际出现过的调试范例，更多资料参见[调试/定位QMK问题](zh-cn/faq_debug.md)。

### 当前按下的键的矩阵坐标是什么？

在移植或尝试诊断PCB问题时，确认按下的键被正确扫描到是很有用的排查步骤。要启用该场景的日志输出，请在 `keymap.c` 中添加：

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
  return true;
}
```

输出示例
```text
Waiting for device:.......
Listening:
KL: kc: 169, col: 0, row: 0, pressed: 1
KL: kc: 169, col: 0, row: 0, pressed: 0
KL: kc: 174, col: 1, row: 0, pressed: 1
KL: kc: 174, col: 1, row: 0, pressed: 0
KL: kc: 172, col: 2, row: 0, pressed: 1
KL: kc: 172, col: 2, row: 0, pressed: 0
```

### 扫描到一个键码需要多久？

调试性能问题时，知晓开关矩阵的扫描频率是很有用的排查步骤。要启用该场景的日志输出，请在 `config.h` 中添加：

```c
#define DEBUG_MATRIX_SCAN_RATE
```

输出示例
```text
  > matrix scan frequency: 315
  > matrix scan frequency: 313
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
```

## `hid_listen` 无法识别到设备

如果设备没有就绪，在命令行下调试会看到如下输出：

```
Waiting for device:.........
```

当设备插入后，*hid_listen*可以发现设备，会有如下输出：

```
Waiting for new device:.........................
Listening:
```

若无法出现'Listening:'消息，尝试在[Makefile]中添加 `CONSOLE_ENABLE=yes`

在类Linux系统下，访问设备可能需要一定权限，尝试使用 `sudo hid_listen`。

此外，很多Linux发行版可以通过创建如下内容的文件 `/etc/udev/rules.d/70-hid-listen.rules` 来避免通过root权限执行hid_listen：

```
SUBSYSTEM=="hidraw", ATTRS{idVendor}=="abcd", ATTRS{idProduct}=="def1", TAG+="uaccess", RUN{builtin}+="uaccess"
```

使用设备的真实VID和PID替换上面的abcd和def1，留意必须全小写。其中 `RUN{builtin}+="uaccess"` 仅在较老的发行版中需要使用。

## 命令行无法成功输出消息
请检查:
- *hid_listen*确实找到了设备，如前文所述。
- 通过**Magic**+d命令启用调试模式，参见[Magic Commands](https://github.com/tmk/tmk_keyboard#magic-commands).
- 配置`debug_enable=true`. 参见[调试](#debugging)
- 尝试用 `print` 替代 `dprint`， 参见**common/print.h**.
- 拔出其它可能影响命令行的设备，参见[Issue #97](https://github.com/tmk/tmk_keyboard/issues/97).
