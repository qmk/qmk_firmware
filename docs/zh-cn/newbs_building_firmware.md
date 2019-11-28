# 构建第一个固件

现在您已经建立了构建环境，就可以开始构建自定义固件了。对于本指南的这一部分，我们将在3个程序之间切换——文件管理器、文本编辑器和终端窗口。请保持所有3个程序打开，直到您完成并对键盘固件满意。

如果您在按照指南第一部分的操作之后关闭并重新打开了终端窗口，请不要忘记输入“cd qmk_firmware”，来使您的终端位于正确的目录。

## 导航到您的keymaps文件夹

首先导航到键盘的 `keymaps` 文件夹.

?> 如果您使用的是MacOS或Windows，可以使用以下命令轻松地打开keymaps文件夹。

?> macOS:

    open keyboards/<keyboard_folder>/keymaps

?> Windows:

    start .\\keyboards\\<keyboard_folder>\\keymaps

## 创建`default` 布局副本

打开`keymaps`文件夹后，您将需要创建`default`文件夹的副本。我们强烈建议您将文件夹命名为与Github用户名相同的名称，但您也可以使用任何您想使用的名称，只要它只包含小写字母、数字和下划线字符。

要自动执行此过程，您还可以选择运行`new_keymap.sh`脚本。

导航到`qmk_firmware/util` 目录然后输入以下命令：

```
./new_keymap.sh <keyboard path> <username>
```

例如，一个名字叫ymzcdg的用户要创建1up60hse的布局，他需要输入

```
./new_keymap.sh 1upkeyboards/1up60hse ymzcdg
```

## 在你最钟爱的文本编辑器中打开`keymap.c`

打开你的`keymap.c`. 在这个文件中，您可以找到控制键盘行为的结构。 在你的`keymap.c` 的顶部有一些让布局更易读的define和enum。在靠下的位置你会找到一行和下面这句很像的:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

从这一行开始便是层列表。这行下面你会看到包括 `LAYOUT` 或 `KEYMAP`这两个词的几行, 从这些行开始就是层。在这一行下面是组成该特定层的键的列表。

!> 编辑您的keymap文件时，注意不要添加或删除任何逗号。如果这样做，您将阻止您的固件编译，并且您可能不容易找出多余的或缺少的逗号在哪里。

## 根据您的喜好自定义布局

如何完成这一步骤完全取决于您。改变一直困扰着你的问题，或者完全重做所有的事情。如果您不需要全部图层，可以删除图层，或者将图层总数增加到32个。查看以下文档，了解可以在此处定义的内容:

* [键码](keycodes.md)
* [特性](features.md)
* [问题与解答](faq.md)

?> 当你明白布局是怎么工作时，您也要让每次改变尽可能小。一次改变很大在调试时找出问题会十分困难。

## 构建你的固件

完成对布局的更改后，您就要构建固件了。为此，请返回终端窗口并运行build命令:

    make <my_keyboard>:<my_keymap>

例如，如果您的keymap名为“xyverz”，并且您正在为rev5 planck构建一个keymap，那么您将使用此命令：

    make planck/rev5:xyverz

在编译过程中，你将看到屏幕上有很多输出，通知您正在编译哪些文件他应该以与下文类似的输出结束:

```
Linking: .build/planck_rev5_xyverz.elf                                                              [OK]
Creating load file for flashing: .build/planck_rev5_xyverz.hex                                      [OK]
Copying planck_rev5_xyverz.hex to qmk_firmware folder                                               [OK]
Checking file size of planck_rev5_xyverz.hex                                                        [OK]
 * File size is fine - 18392/28672
```

## 刷新你的固件

请移步 [Flashing Firmware](newbs_flashing.md) 来继续。
