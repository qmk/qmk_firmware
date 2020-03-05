# 刷新你的键盘 

现在您已经构建了一个自定义固件文件，那么您就需要刷新键盘了。

## 用QMK工具箱刷新键盘

刷新键盘的最简单方法是使用[QMK 工具箱](https://github.com/qmk/qmk_toolbox/releases). 

但是，QMK工具箱目前仅适用于Windows和MacOS。如果您使用的是Linux（或者只是希望从命令行刷新固件），则必须使用 [方法概述](zh-cn/newbs_flashing.md#使用命令行刷新你的键盘).

### 将文件加载到QMK工具箱中

首先打开QMK工具箱应用程序。您将要在访达或资源管理器中找到固件文件。您的键盘固件可能是两种格式之一`.hex`或`.bin`。qmk会尝试将键盘的相应文件复制到“qmk_firmware”根目录中。

如果您在Windows或MacOS上，可以使用以下命令轻松地在资源管理器或访达中打开当前固件文件夹。

#### Windows

```
start .
```

#### macOS

```
open .
```

固件文件始终遵循此命名格式:

```
<keyboard_name>_<keymap_name>.{bin,hex}
```

例如，使用 `default` 映射的 `plank/rev5` 将使用以下名字：

```
planck_rev5_default.hex
```

找到固件文件后，将其拖到QMK工具箱中的“Local file”框中，或单击“Open”并导航到固件文件的存储位置。

### 将键盘置于DFU（Bootloader）模式

要刷新自定义固件，您必须将键盘置于特殊的刷新模式。在此模式下，您将无法键入或使用键盘。在写入固件时，不要拔下键盘插头或以其他方式中断刷新过程，这一点非常重要。

不同的键盘有不同的方式进入这种特殊模式。如果您的键盘当前运行的是QMK或TMK，而您没有得到特定的指示，请按顺序尝试以下操作:

* 按住两个shift键并按 `Pause`
* 按住两个shift键并按 `B`
* 拔下键盘插头, 同时按住空格键和 `B` , 插上键盘然后等一会再放开按键
* 按下PCB底部的 `RESET` 物理按键
* 找到PCB上标记有 `BOOT0` 或 `RESET`的金属点, 在插入PCB的同时短接它们

成功后，您将在QMK工具箱中看到类似以下内容的消息:

```
*** Clueboard - Clueboard 66% HotSwap disconnected -- 0xC1ED:0x2390
*** DFU device connected
```

### 刷新你的键盘

单击QMK工具箱中的 `Flash` 按钮。您将看到类似以下内容的输出:

```
*** Clueboard - Clueboard 66% HotSwap disconnected -- 0xC1ED:0x2390
*** DFU device connected
*** Attempting to flash, please don't remove device
>>> dfu-programmer atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer atmega32u4 flash /Users/skully/qmk_firmware/clueboard_66_hotswap_gen1_skully.hex
    Checking memory from 0x0 to 0x55FF...  Empty.
    0%                            100%  Programming 0x5600 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x5600 bytes written into 0x7000 bytes memory (76.79%).
>>> dfu-programmer atmega32u4 reset
    
*** DFU device disconnected
*** Clueboard - Clueboard 66% HotSwap connected -- 0xC1ED:0x2390
```

## 使用命令行刷新键盘

与过去相比，这已变得非常简单。当比准备好编译并刷新固件时，打开命令刚窗口并运行构建命令： 

    make <my_keyboard>:<my_keymap>:flash

比如，如果映射叫做"xyverz"并且该映射是rev5 planck的，使用以下命令：

    make planck/rev5:xyverz:flash

这将会检查键盘的配置并尝试基于指定bootloader刷新键盘。也就是说你无须知道你的键盘使用的是哪种bootloader。只需运行该命令，编译刷新一蹴而就。

但是这依赖于键盘设置的bootloader。如果该信息未配置或你的键盘板并没有支持的目标来刷新，你将会见到以下错误<!--TODO：翻译不准确，原文为： If this information is not configured, or you're using a board that doesn't have a supported target to flash it, you will see this error-->

    WARNING: This board's bootloader is not specified or is not supported by the ":flash" target at this time.

出现这种情况，说明你搞错了bootloader的种类。

一般来说可能会使用五种bootloader之一。Pro Micro 和其他兼容板使用Caterina, Teensys使用HalfKay, OLKB的AVR板使用QMK-DFU，其他ATmega32U4板使用DFU，大多数ARM板使用ARM DFU.

欲了解更多，详见[刷新说明和bootloader信息](zh-cn/flashing.md)。 

如果你知道你用的是何种bootloader，当你编译固件时，你可以向 `make`命令添加其他参数来自动化刷新过程。<!--译者注：添加啥啊，你也没说--> 

### DFU

对于DFU引导加载程序，当您准备好编译和刷新固件时，打开终端窗口并运行构建命令: 

    make <键盘名>:<映射名>:dfu

例如，如果您的布局名为“xyverz”，并且您正在为rev5 planck构建一个布局，那么您可以使用此命令：

    make planck/rev5:xyverz:dfu

编译完成后，应输出以下内容：

```
Linking: .build/planck_rev5_xyverz.elf                                                              [OK]
Creating load file for flashing: .build/planck_rev5_xyverz.hex                                      [OK]
Copying planck_rev5_xyverz.hex to qmk_firmware folder                                               [OK]
Checking file size of planck_rev5_xyverz.hex                                                        
 * File size is fine - 18574/28672
 ```

到了这个时候, 构建脚本将每隔5秒查找一次DFU。它将重复以下操作，直到找到设备或将其取消。

    dfu-programmer: no device present.
    Error: Bootloader not found. Trying again in 5s.

一旦出现以上回显，您将需要重置控制器。然后，它应该显示与以下类似的输出：

```
*** Attempting to flash, please don't remove device
>>> dfu-programmer atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer atmega32u4 flash /Users/skully/qmk_firmware/clueboard_66_hotswap_gen1_skully.hex
    Checking memory from 0x0 to 0x55FF...  Empty.
    0%                            100%  Programming 0x5600 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x5600 bytes written into 0x7000 bytes memory (76.79%).
>>> dfu-programmer atmega32u4 reset
```

?> 如果你对此有任何问题 - 比如 `dfu-programmer: no device present` - 详见 [常见的构建问题](zh-cn/faq_build.md)。

#### DFU命令

有许多DFU命令可用于将固件下载到DFU设备：

* `:dfu` - 这是正常选项，等待DFU设备可用，然后刷新固件。这将每隔5秒检查一次，以查看是否出现了DFU设备。
* `:dfu-ee` - 这将刷新一个`eep`文件，而不是普通的十六进制文件。这很不常见。
* `:dfu-split-left` - 这将刷新正常固件，就像默认选项 (`:dfu`)一样. 但是，这也会刷新“左侧”EEPROM文件，用于分割键盘。 _这是基于Elite C的键盘的推荐选择。_
* `:dfu-split-right` - 这将刷新正常固件，就像默认选项(`:dfu`). 但是，这也会刷新“右侧”EEPROM文件，用于分割键盘。 _这是基于Elite C的键盘的推荐选择。_


### Caterina 

对于Arduino板以及其兼容板来说(比如SparkFun和ProMicro), 准备好编译和刷新固件后，打开终端窗口并运行构建命令: 

    make <my_keyboard>:<my_keymap>:avrdude

比如, 你的布局叫"xyverz"你要创建一个rev2 Lets Split的布局,你要用以下命令:

    make lets_split/rev2:xyverz:avrdude

固件完成编译后，它将输出类似以下的内容: 

```
Linking: .build/lets_split_rev2_xyverz.elf                                                            [OK]
Creating load file for flashing: .build/lets_split_rev2_xyverz.hex                                    [OK]
Checking file size of lets_split_rev2_xyverz.hex                                                      [OK]
 * File size is fine - 27938/28672
Detecting USB port, reset your controller now..............
```

此时，复位，然后脚本将检测bootloader，然后刷新固件。输出应该像这样:

```
Detected controller on USB port at /dev/ttyS15

Connecting to programmer: .
Found programmer: Id = "CATERIN"; type = S
    Software Version = 1.0; No Hardware Version given.
Programmer supports auto addr increment.
Programmer supports buffered memory access with buffersize=128 bytes.

Programmer supports the following devices:
    Device code: 0x44

avrdude.exe: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude.exe: Device signature = 0x1e9587 (probably m32u4)
avrdude.exe: NOTE: "flash" memory has been specified, an erase cycle will be performed
             To disable this feature, specify the -D option.
avrdude.exe: erasing chip
avrdude.exe: reading input file "./.build/lets_split_rev2_xyverz.hex"
avrdude.exe: input file ./.build/lets_split_rev2_xyverz.hex auto detected as Intel Hex
avrdude.exe: writing flash (27938 bytes):

Writing | ################################################## | 100% 2.40s

avrdude.exe: 27938 bytes of flash written
avrdude.exe: verifying flash memory against ./.build/lets_split_rev2_xyverz.hex:
avrdude.exe: load data flash data from input file ./.build/lets_split_rev2_xyverz.hex:
avrdude.exe: input file ./.build/lets_split_rev2_xyverz.hex auto detected as Intel Hex
avrdude.exe: input file ./.build/lets_split_rev2_xyverz.hex contains 27938 bytes
avrdude.exe: reading on-chip flash data:

Reading | ################################################## | 100% 0.43s

avrdude.exe: verifying ...
avrdude.exe: 27938 bytes of flash verified

avrdude.exe: safemode: Fuses OK (E:CB, H:D8, L:FF)

avrdude.exe done.  Thank you.
```
如果您对此有任何问题，您可能需要这样做：

    sudo make <键盘名>:<映射名>:avrdude


#### Caterina命令

有很多DFU命令，你可以使用它们刷新DFU设备的固件：

* `:avrdude` - 这是个正常选项，用于等待直到Caterina设备可用(检测到一个新的COM口)，然后刷新固件。
* `:avrdude-loop` - 该命令会运行与`:avrdude`相同的命令，但当设备刷新后，它将会尝试再次刷新。适用于批量刷新。 _该循环命令需要手动终止，快捷键为Control+C._
* `:avrdude-split-left` - 该命令刷新正常的固件，就像默认选项 (`:avrdude`)。但是，也会为分体式键盘刷新"左侧"EEPROM文件。 _该命令完美适配基于Pro Micro的分体键盘。_
* `:avrdude-split-right` - 该命令刷新正常的固件，就像默认选项 (`:avrdude`)。但是，也会为分体式键盘刷新"右侧"EEPROM文件。 _该命令完美适配基于Pro Micro的分体键盘。_


## HalfKay

对于PJRC设备（Teensy），当您准备好编译和刷新固件时，打开终端窗口并运行构建命令: 

    make <键盘名>:<映射名>:teensy

比如, 如果你的布局叫做"xyverz"你想创建Ergodox or Ergodox EZ的布局,你要使用以下命令:

    make erdogox_ez:xyverz:teensy

固件完成编译后，它将输出如下内容：

```
Linking: .build/ergodox_ez_xyverz.elf                                                               [OK]
Creating load file for flashing: .build/ergodox_ez_xyverz.hex                                       [OK]
Checking file size of ergodox_ez_xyverz.hex                                                         [OK]
 * File size is fine - 25584/32256
 Teensy Loader, Command Line, Version 2.1
Read "./.build/ergodox_ez_xyverz.hex": 25584 bytes, 79.3% usage
Waiting for Teensy device...
 (hint: press the reset button)
 ```

此时，复位键盘。完成后，您将看到如下输出：

 ```
 Found HalfKay Bootloader
Read "./.build/ergodox_ez_xyverz.hex": 28532 bytes, 88.5% usage
Programming............................................................................................................................................................................
...................................................
Booting
```

## STM32 (ARM)

对于大多数ARM板（包括Proton C、Planck Rev 6和Preonic Rev 3），当您准备好编译和刷新固件时，打开终端窗口并运行构建命令：

    make <键盘名>:<映射名>:dfu-util

例如，如果您的keymap被命名为“xyverz”，并且您正在为Planck Revision 6键盘构建一个布局，那么您需要使用以下命令，然后手动将键盘重新启动到bootloader（在完成编译之前）：

    make planck/rev6:xyverz:dfu-util

固件完成编译后，它将输出如下内容：

```
Linking: .build/planck_rev6_xyverz.elf                                                             [OK]
Creating binary load file for flashing: .build/planck_rev6_xyverz.bin                               [OK]
Creating load file for flashing: .build/planck_rev6_xyverz.hex                                     [OK]

Size after:
   text    data     bss     dec     hex filename
      0   41820       0   41820    a35c .build/planck_rev6_xyverz.hex

Copying planck_rev6_xyverz.bin to qmk_firmware folder                                              [OK]
dfu-util 0.9

Copyright 2005-2009 Weston Schmidt, Harald Welte and OpenMoko Inc.
Copyright 2010-2016 Tormod Volden and Stefan Schmidt
This program is Free Software and has ABSOLUTELY NO WARRANTY
Please report bugs to http://sourceforge.net/p/dfu-util/tickets/

Invalid DFU suffix signature
A valid DFU suffix will be required in a future dfu-util release!!!
Opening DFU capable USB device...
ID 0483:df11
Run-time device DFU version 011a
Claiming USB DFU Interface...
Setting Alternate Setting #0 ...
Determining device status: state = dfuERROR, status = 10
dfuERROR, clearing status
Determining device status: state = dfuIDLE, status = 0
dfuIDLE, continuing
DFU mode device DFU version 011a
Device returned transfer size 2048
DfuSe interface name: "Internal Flash  "
Downloading to address = 0x08000000, size = 41824
Download        [=========================] 100%        41824 bytes
Download done.
File downloaded successfully
Transitioning to dfuMANIFEST state
```

#### STM32命令

有一些DFU命令你可以用于刷新STM32设备：

* `:dfu-util` - 刷新STM32设备的默认命令，会等待直到STM32的bootloader可用. .<!--TODO：present不知道什么意思，自己理解翻译的，原文为：and will wait until an STM32 bootloader is present. .-->  
* `:dfu-util-split-left` - 刷新正常的固件，就像默认选项(`:dfu-util`)那样。但是也会为分体式键盘配置"左侧"EEPROM设置。
* `:dfu-util-split-right` - 刷新正常的固件，就像默认选项(`:dfu-util`)那样。但是也会为分体式键盘配置"右侧"EEPROM设置。
* `:st-link-cli` - 该命令允许你是通过ST-LINK的命令行实用程序刷新固件，而不是用DFU实用程序。


### BootloadHID

对于基于Bootmapper Client(BMC)/bootloadHID/ATmega32A的键盘，当你准备好编译并刷新固件时，打开终端窗口并运行构建命令： 

    make <键盘名>:<映射名>:bootloaderHID

比如你的映射名叫做"xyverz"，对应键盘是jj40，使用以下命令：

    make jj40:xyverz:bootloaderHID

当你的固件完成编译后会有类似如下的输出：

```
Linking: .build/jj40_default.elf                                                                   [OK]
Creating load file for flashing: .build/jj40_default.hex                                           [OK]
Copying jj40_default.hex to qmk_firmware folder                                                    [OK]
Checking file size of jj40_default.hex                                                             [OK]
 * The firmware size is fine - 21920/28672 (6752 bytes free)
```

在这之后，构建脚本会每5秒寻找一次DFU bootloader。如下回显将在找到设备或你取消之前一直重复。 

```
Error opening HIDBoot device: The specified device was not found
Trying again in 5s.
```

完成此操作后，您将需要重置控制器。回显类似如下： 

```
Page size   = 128 (0x80)
Device size = 32768 (0x8000); 30720 bytes remaining
Uploading 22016 (0x5600) bytes starting at 0 (0x0)
0x05580 ... 0x05600
```

## 试一试吧!

恭喜您! 您的自定义固件已经刷写到您的键盘

试一试，确保一切按你想的方式进行。我们写了[测试和调试](zh-cn/newbs_testing_debugging.md)来完善新手引导。 因此，请前往那里了解如何排除自定义功能的故障。

<!--源文件：https://raw.githubusercontent.com/qmk/qmk_firmware/0e6f78547eca1e7bbb093265e79c26a301e6635a/docs/newbs_flashing.md 
    源提交哈希：0e6f78547eca1e7bbb093265e79c26a301e6635a-->
<!--翻译时间:20200226-18:28(GMT+8)-->
