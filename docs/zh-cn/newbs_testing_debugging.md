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

## 调试

如果在你的`rules.mk`中有`CONSOLE_ENABLE = yes`的话你的键盘将会输出调试信息。默认情况下输出非常有限，但是打开调试模式会让调试输出更多。使用你映射中的`DEBUG`键码，使用 [命令](zh-cn/feature_command.md)特性来使能调试模式，或添加以下代码到你的映射中。

```c
void keyboard_post_init_user(void) {
  // 自己设置这些值来达到你想要的效果
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```

### 使用QMK工具箱进行调试

对于兼容平台，[QMK工具箱](https://github.com/qmk/qmk_toolbox)可以用于显示键盘调试信息。

### 使用hid_listen调试

你更喜欢使用终端的解决方案？[hid_listen](https://www.pjrc.com/teensy/hid_listen.html)，是由PJRC提供的，可以用于显示调试信息。Windows，Linux，和MacOS的预构建的二进制文件都可使用。

<!-- 待完善: 此处应有调试信息。译者注：上面那段文字最后一句我不理解，瞎翻译的，应该翻译没错，只是不理解。 -->

## 发送您自己的调试消息

有时用[custom code](zh-cn/custom_quantum_functions.md)发送自定义调试信息很有用. 这么做很简单. 首先在你文件头部包含`print.h`:

    #include <print.h>

之后，您可以使用一些不同的打印功能:

* `print("string")`: 打印简单字符串.
* `uprintf("%s string", var)`: 打印格式化字符串
* `dprint("string")`: 仅在调试模式使能时打印简单字符串
* `dprintf("%s string", var)`: 仅在调试模式使能时打印格式化字符串

## 调试示例

以下就是一组实际挑食示例。欲了解更多，请参考[QMK的调试/故障排除](zh-cn/faq_debug.md).

### 这次击键在矩阵的哪个位置？

当移植或诊断PCB问题时，能知道一次击键是否被正确扫描是极为有用的。为这种情况启用日志记录，需要添加以下代码到你的映射`keymap.c`

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // 如果已经使能控制台，就会输出矩阵位置和每一个按下的键的状态
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
  return true;
}
```

输出示例如下
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

### 扫描一次击键要多长时间？

当测试性能问题时，了解扫描开关矩阵的频率是有用的。为这种情况启用日志记录，需要添加以下代码到你的映射 `config.h`

```c
#define DEBUG_MATRIX_SCAN_RATE
```

输出示例如下
```text
  > matrix scan frequency: 315
  > matrix scan frequency: 313
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
```

<!--源文件：https://raw.githubusercontent.com/qmk/qmk_firmware/feb116c4f33d1c4f451f3eecbf3d8f80be80e557/docs/newbs_testing_debugging.md 
    源提交哈希：feb116c4f33d1c4f451f3eecbf3d8f80be80e557-->
<!--翻译时间:20200227-16:29(GMT+8)-->
