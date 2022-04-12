# 构建第一个固件

<!---
  original document: 0.15.12:docs/newbs_building_firmware.md
  git diff 0.15.12 HEAD -- docs/newbs_building_firmware.md | cat
-->

现在您已经准备好了构建环境，就可以开始构建自定义固件了。在这节指南中，我们将在3个程序中开展工作——文件管理器、文本编辑器和终端。在做出心满意足的固件前，请不要关闭它们。
## 新建键映射

也许你会考虑从默认键映射复制一份来开始，如果你遵循编译环境配置指南到了最后，那么使用QMK命令行可以简单地做到：

    qmk new-keymap

如果你的环境没有那样配置，或者你有多个键盘要做，可以指定键盘名：

    qmk new-keymap -kb <keyboard_name>

检查命令行输出，应该类似于：

    Ψ <github_username> keymap directory created in: /home/me/qmk_firmware/keyboards/clueboard/66/rev3/keymaps/<github_username>

上面就是创建出的新 `keymap.c` 文件的路径。

## 使用趁手的编辑器打开 `keymap.c`

在编辑器中打开 `keymap.c`，可以看到控制键盘所有功能的关键结构。`keymap.c` 文件头部的一些define和enum定义能让代码容易阅读一些，继续往下会找到这么一行：

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

这行是所有层定义的起点，往下能看到有 `LAYOUT` 的行，都是一个层定义的起始，其下方为该层的组成定义。

!> 编辑时请非常留意不要错误增加/删除了逗号分隔符，否则很可能无法编译固件，且很难排查是哪里的逗号不对。

## 按照个人喜好设计层级

这一步的目标完全取决于你，既可以去修复一个你不爽的问题，也可以完全重写一个新的。你可以删除不需要的层，或是增加层到32个的上限，QMK功能丰富，可以在左边的导航栏中寻找“使用QMK”一节，浏览完整的功能信息，也可以看看这些比较简单的：

* [基础键码](zh-cn/keycodes_basic.md)
* [量子键码](zh-cn/quantum_keycodes.md)
* [Grave/Escape](zh-cn/feature_grave_esc.md)
* [鼠标键](zh-cn/feature_mouse_keys.md)

?> 你大概理解了键映射如何工作的话，留心尽量少去做改动，改动越多出了问题越难排查。

## 构建固件 :id=build-your-firmware

对键映射做完修改后，该编译固件了。回到终端中使用编译命令：

    qmk compile

如果没有完整地配置环境，或你有多个目标键盘，可以指定键盘及键映射：

    qmk compile -kb <keyboard> -km <keymap>

编译完成后，会输出详尽的编译产出文件信息，其末尾应该看起来像这样：

```
Linking: .build/planck_rev5_default.elf                                                             [OK]
Creating load file for flashing: .build/planck_rev5_default.hex                                     [OK]
Copying planck_rev5_default.hex to qmk_firmware folder                                              [OK]
Checking file size of planck_rev5_default.hex                                                       [OK]
 * The firmware size is fine - 27312/28672 (95%, 1360 bytes free)
```

## 刷写固件

参阅[刷写固件](zh-cn/newbs_flashing.md)以了解如何将固件写入键盘主控。
