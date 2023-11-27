# 刷写键盘固件 

<!---
  original document: 0.15.12:docs/newbs_flashing.md
  git diff 0.15.12 HEAD -- docs/newbs_flashing.md | cat
-->

在自定义的固件文件构建出来后，可以刷写到键盘中了。

## 将键盘调至DFU（Bootloader）模式

在你将自定义固件刷写到键盘前，键盘必须处于特有的刷写模式下。此时，键盘会处于不会响应点击等常规操作的状态，并且一定留意不要打断刷写工作，刷写固件过程中不可以把键盘拔下来。

不同的键盘进入刷写模式的方法都是不同的，如果你的键盘运行的是QMK、TMK或PS2AVRGB(Bootmapper客户端)且没有写明特别的操作说明的话，可以依次尝试以下操作：

* 按住两边的Shift键，点击Pause
* 按住两边的Shift键，点击B
* 拔出键盘，同时按住“空格”键及B键，再插上键盘，等两秒后松开
* 拔出键盘，按住键盘左上或左下的按键（一般来讲是Escape或左Control），在插上键盘
* 按重置按键（Reset），一般在PCB背面
* 在PCB上寻找导出的 `RESET` 和 `GND` 引脚，在插电的情况下短接一下

如果上面的方法没有用，且键盘主板上的芯片是 `STM32` 系列，情况要复杂一些。通常在[Discord](https://discord.gg/Uq7gcHh)上寻求帮助是最好的办法，并且很可能需要你提供一些键盘主板的照片 —— 所以如果你能提前准备好，我们沟通起来会快得多。

如果没有遇到什么问题，你会在QMK工具箱的输出信息里找到类似下面的黄色文字的信息：

```
*** DFU device connected: Atmel Corp. ATmega32U4 (03EB:2FF4:0000)
```

已进入bootloader状态的设备也可以在设备管理器、系统信息或 `lsusb` 中看到。

## 使用QMK工具箱刷写固件

使用[QMK工具箱](https://github.com/qmk/qmk_toolbox/releases)刷写固件是最简单的方案。

然而该工具箱仅支持Windows及macOS，如果你在使用Linux环境（或是希望用命令行刷写固件），请参阅[在命令行中刷写固件](#使用命令行刷写固件)一节。

### 加载固件到QMK工具箱

打开QMK工具箱，在Finder或文件管理器中找到固件文件。键盘固件文件名后缀通常是 `.hex` 或 `.bin`，QMK工具箱会尝试将正确的文件拷贝到qmk根目录 `qmk_firmware` 中。

在Windows或macOS上，使用下面的指令可以快速打开当前目录。

<!-- tabs:start -->

#### ** Windows **

```
start .
```

#### ** macOS **

```
open .
```

<!-- tabs:end -->

固件文件的文件名格式为：

```
<keyboard_name>_<keymap_name>.{bin,hex}
<键盘名>_<键映射名>.{bin,hex}
```

例如， `planck/rev5` 的 `default` 键映射对应的文件名是：

```
planck_rev5_default.hex
```

找到固件文件后，将其拖拽至QMK工具箱的"Local file"框，或点击“Open”并定位至固件文件。

### 刷写到键盘

点击QMK工具箱的`Flash`，将看到如下输出信息：

```
*** DFU device connected: Atmel Corp. ATmega32U4 (03EB:2FF4:0000)
*** Attempting to flash, please don't remove device
>>> dfu-programmer.exe atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer.exe atmega32u4 flash "D:\Git\qmk_firmware\gh60_satan_default.hex"
    Checking memory from 0x0 to 0x3F7F...  Empty.
    0%                            100%  Programming 0x3F80 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x3F80 bytes written into 0x7000 bytes memory (56.70%).
>>> dfu-programmer.exe atmega32u4 reset
    
*** DFU device disconnected: Atmel Corp: ATmega32U4 (03EB:2FF4:0000)
```

## 使用命令行刷写固件

现在已经没有以前那样繁琐了，在编译固件后需要刷写时，打开终端输入如下刷写指令：

    qmk flash

如果未通过命令行工具配置过键盘/键映射名，或有多个目标键盘，可以指定目标键盘和键映射：

    qmk flash -kb <键盘名> -km <键映射名>

QMK将核查键盘配置，并尝试使用合适的bootloader进行刷写。也就是说，你不用关注应该使用什么bootloader，这些重活儿让qmk指令去承担就好。

但是，先决条件是键盘配置中已经设置了bootloader，如果未配置，或你的键盘板子不支持配置的刷写方式，你会看到这些错误信息：

    WARNING: This board's bootloader is not specified or is not supported by the ":flash" target at this time.

此时，只能退回到需要指定bootloader的方法，具体参见[刷写固件](zh-cn/flashing.md)指引。

## 上手试试键盘吧！

恭喜你，你的自定义固件成功刷写到键盘中了，快去试试吧！

运气不差的话一切都会是正常工作的，如果不幸遇到了些问题，有一些参考方案可以帮助你排查问题原因。
键盘测试就简单直接了，依次按一下各按键，检查它是不是发送了正确的输入。可以使用[QMK配置器](https://config.qmk.fm/#/test/)中的测试模式进行测试，即便你的键盘并不运行QMK。

还是不行吗？参阅一下FAQ或[通过Discord和我们聊聊](https://discord.gg/Uq7gcHh)吧。
