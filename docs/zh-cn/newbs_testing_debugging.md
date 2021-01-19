# 测试和调试

使用自定义固件刷新键盘后，您就可以测试它了。如果您幸运，一切都会完美运行，但如果没有，这份文件将帮助您找出问题所在。

## 测试

测试键盘通常非常简单。按下每一个键并确保它发送的是您期望的键。甚至有一些程序可以帮助您确保没有任何键失效。

注意：这些程序不是由QMK提供或认可的。

* [QMK Configurator](https://config.qmk.fm/#/test/) (网页版)
* [Switch Hitter](https://web.archive.org/web/20190413233743/https://elitekeyboards.com/switchhitter.php) (仅Windows)
* [Keyboard Viewer](https://www.imore.com/how-use-keyboard-viewer-your-mac) (仅Mac)
* [Keyboard Tester](http://www.keyboardtester.com) (网页版)
* [Keyboard Checker](http://keyboardchecker.com) (网页版)

## 使用QMK工具箱进行调试

[QMK工具箱](https://github.com/qmk/qmk_toolbox) 将会在你的`rules.mk`中有`CONSOLE_ENABLE = yes`的时候显示你键盘发来的消息。 默认情况下，输出极为有限，不过您可以打开调试模式来增加输出信息量。使用你键盘布局中的`DEBUG`键码,使用 [命令](feature_command.md) 特性来使能调试模式, 或者向你的布局中添加以下代码。

```c
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```

<!-- 需要修改之处:这里要添加调试回显。 -->

## 发送您自己的调试消息

有时用[custom code](custom_quantum_functions.md)发送自定义调试信息很有用. 这么做很简单. 首先在你文件头部包含`print.h`:

```c
#include "print.h"
```

之后，您可以使用一些不同的打印功能:

* `print("string")`: 打印简单字符串.
* `uprintf("%s string", var)`: 打印格式化字符串
* `dprint("string")`: 仅在调试模式使能时打印简单字符串
* `dprintf("%s string", var)`: 仅在调试模式使能时打印格式化字符串
