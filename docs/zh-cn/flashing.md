# 刷写指引及Bootloader资料

<!---
  original document: 0.15.12:docs/flashing.md
  git diff 0.15.12 HEAD -- docs/flashing.md | cat
-->

用于键盘的bootloader有很多种，几乎每一种都在使用私有的刷写协议及工具。幸运的是，形如[QMK工具箱](https://github.com/qmk/qmk_toolbox/releases)这样的工程目标就是尽量支持这些工具，本文会探讨各种bootloader的差异，以及可用的刷写方案。

针对基于AVR的键盘，QMK会自动检查所要刷写的 `.hex` 文件大小是否与在 `rules.mk` 中设置的 `BOOTLOADER` 值所匹配，同时会输出字节大小信息（及最大限制）。

同时也可以使用CLI工具刷写键盘，执行：
```
$ qmk flash -kb <keyboard> -km <keymap>
```
更多信息参见文档[`qmk flash`](zh-cn/cli_commands.md#qmk-flash)。

## Atmel DFU

Atmel系列的DFU bootloader默认配备在所有USB AVR系列上（16/32U4RC除外），广泛用于一些PCB上具备私有集成电路模块（IC）的键盘上（老款OLKB、Clueboards等）。有些使用的是LUFA实现的DFU bootloader，或是QMK的分支版本（新款OLKB），后者对硬件功能进行了扩充加强。

为保证对DFU bootloader的兼容性，请确保在 `rules.mk` 中存在如下部分内容（可选的值还有 `lufa-dfu` 或 `qmk-dfu`）：

```make
# 选择Bootloader
BOOTLOADER = atmel-dfu
```

兼容的刷写工具：

* [QMK工具箱](https://github.com/qmk/qmk_toolbox/releases)（推荐的图形化工具）
* [dfu-programmer](https://github.com/dfu-programmer/dfu-programmer) / QMK中将构建目标设为 `:dfu`（推荐的命令行工具）

刷写过程：

1. 使用如下任一方式进入bootloader模式：
    * 点击 `RESET` 键码
    * 如果PCB上有 `RESET` 键，点击之
    * 快速短接一下RST到GND
2. 等待操作系统识别到设备
3. 清空flash存储数据（如果使用QMK工具箱或CLI的 `make`会自动进行）
4. 将.hex文件刷写进去
5. 重置设备进入应用模式（如上，会自动进行）

### QMK DFU

QMK维护了[一个LUFA DFU bootloader的分支版本](https://github.com/qmk/lufa/tree/master/Bootloaders/DFU)，其可以进行一次矩阵扫描来退出bootloader进入应用模式，同时会让LED闪烁或蜂鸣器响一声。若要启用该功能，将以下定义添加到 `config.h`：

```c
#define QMK_ESC_OUTPUT F1  // COL pin if COL2ROW
#define QMK_ESC_INPUT  D5  // ROW pin if COL2ROW
// 可选:
//#define QMK_LED E6
//#define QMK_SPEAKER C6
```
目前来讲不推荐将 `QMK_ESC` 键设置成与[Bootmagic](zh-cn/feature_bootmagic.md)同一个键，否则按下该键时只会让MCU在bootloader模式上反复进出。

制造商及型号字符串自动从 `config.h` 中获取，并会在型号后追加 " Bootloader"。

要生成该bootloader，需指定 `bootloader` 构建目标，即 `make planck/rev4:default:bootloader`。要生成可部署到正式产品的.hex文件（同时包含QMK及bootloader），使用 `production` 构建目标，即 `make planck/rev4:default:production`。

### `make` 构建目标

* `:dfu`: 每5秒检测一次直到发现可用的DFU设备，然后进行固件刷写。
* `:dfu-split-left` 和 `:dfu-split-right`: 同 `:dfu` 一样会刷写固件，但额外地会设置手性设置到EEPROM中，对于基于Elite-C的分体式键盘这是理想的方法。

## Caterina

Arduino及其仿制板使用[Caterina bootloader](https://github.com/arduino/ArduinoCore-avr/tree/master/bootloaders/caterina)或某种变体（使用Pro Micro或其仿制芯片、Pololu A-Star等构建的所有键盘），并基于虚拟串口使用AVR109协议进行通信。

为确保对Caterina bootloader的兼容性，请添加如下代码块至 `rules.mk`：

```make
# 选择Bootloader
BOOTLOADER = caterina
```

兼容的刷写工具：

* [QMK工具箱](https://github.com/qmk/qmk_toolbox/releases) （推荐的图形化工具）
* [avrdude](https://www.nongnu.org/avrdude/) QMK中须基于 `avr109` 编程器 / `:avrdude` 构建目标 （推荐的命令行工具）
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)

刷写过程：

1. 使用如下任一方式进入bootloader模式（进入该模式后只有7秒时间可以刷写；一些型号需要你在750ms内重置两次）：
    * 点击 `RESET` 键码
    * 如果PCB上有 `RESET` 键，点击之
    * 快速短接一下RST到GND
2. 等待操作系统识别到设备
3. 将.hex文件刷写进去
4. 等待设备自动重置

### `make` 构建目标

* `:avrdude`: 每5秒检测一次直到发现可用的Caterina设备（通过检测新COM端口），然后进行固件刷写。
* `:avrdude-loop`: 同 `:avrdude` 一样刷写固件，但会在一个设备刷写完后再次尝试刷写。主要用于批量刷写设备。按 Ctrl+C 以终止循环检测。
* `:avrdude-split-left` 和 `:avrdude-split-right`: 同 `:avrdude` 一样会刷写固件，但额外地会设置手性设置到EEPROM中，对于基于Pro Micro的分体式键盘这是理想的方法。

## HalfKay

HalfKay是一款由PJRC开发的超精简的bootloader，且呈现为HID设备（因此不需要额外的驱动），在所有的Teensys，即"the 2.0"，上已经预刷写过。该bootloader目前是闭源的，因此一旦覆写（即通过ISP刷入其它bootloader）掉，就无法复原了。

为确保对Halfkay bootloader的兼容性，请添加如下代码块至 `rules.mk`：

```make
# 选择Bootloader
BOOTLOADER = halfkay
```

兼容的刷写工具：

* [QMK工具箱](https://github.com/qmk/qmk_toolbox/releases)（推荐的图形化工具）
* [Teensy Loader Command Line](https://www.pjrc.com/teensy/loader_cli.html) / QMK中将构建目标设为 `:teensy`（推荐的命令行工具）
* [Teensy Loader](https://www.pjrc.com/teensy/loader.html)

刷写过程：

1. 使用如下任一方式进入bootloader模式（进入该模式后只有7秒时间可以刷写）：
    * 点击 `RESET` 键码
    * 如果Teensy上或PCB上有 `RESET` 键，点击之
    * 快速短接一下RST到GND
2. 等待操作系统识别到设备
3. 将.hex文件刷写进去
4. 重置设备进入应用模式（可能会自动进行）

## USBasploader

USBasploader是一款来源于[Objective Development](https://www.obdev.at/products/vusb/usbasploader.html)的bootloader。它通过模拟出一个USBasp ISP编程器来运行V-USB以用于一些形如ATmega328P这样的“非USB AVR芯片”。

为确保对USBasploader bootloader的兼容性，请添加如下代码块至 `rules.mk`：

```make
# 选择Bootloader
BOOTLOADER = usbasploader
```

兼容的刷写工具：

* [QMK工具箱](https://github.com/qmk/qmk_toolbox/releases)（推荐的图形化工具）
* [avrdude](https://www.nongnu.org/avrdude/) QMK中须基于 `usbasp` 编程器 / `:usbasp` 构建目标（推荐的命令行工具）
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)

刷写过程：

1. 使用如下任一方式进入bootloader模式：
    * 点击 `RESET` 键码
    * 在按住 `BOOT` 按钮时，快速点击一下PCB上的 `RESET`
2. 等待操作系统识别到设备
3. 将.hex文件刷写进去
4. 点击PCB上的 `RESET` 按钮或将RST短接至GND一下。

## BootloadHID

BootloadHID是一款用于AVR微控制器的bootloader，其呈现为HID输入设备，和HalkKay很像，因此在Windows下也无需安装驱动。

为确保对bootloadHID bootloader的兼容性，请添加如下代码块至 `rules.mk`：

```make
# 选择Bootloader
BOOTLOADER = bootloadhid
```

兼容的刷写工具：

* [QMK工具箱](https://github.com/qmk/qmk_toolbox/releases)（推荐的图形化工具）
* [bootloadHID CLI](https://www.obdev.at/products/vusb/bootloadhid.html) / QMK中将构建目标设为 `:bootloadhid`（推荐的命令行工具）
* [HIDBootFlash](http://vusb.wikidot.com/project:hidbootflash)


刷写过程：

1. 使用如下任一方式进入bootloader模式：
    * 点击 `RESET` 键码
    * 在按住“盐键”（salt key）时插入键盘 - 在PS2AVRGB板上，通常在MCU的A0及B0引脚上有这个按键，否则请查看键盘的使用说明。
2. 等待操作系统识别到设备
3. 将.hex文件刷写进去
4. 重置设备到应用模式（可能会自动进行）

### QMK HID

QMK维护了[一个LUFA HID bootloader的分支版本](https://github.com/qmk/lufa/tree/master/Bootloaders/HID)，通过USB HID节点设备进行刷写，工作模式类似于PJRC的Teensy Loader刷写器以及HalfKay bootloader。其可以进行一次矩阵扫描来退出bootloader进入应用模式，同时会让LED闪烁或蜂鸣器响一声。

为确保对QMK HID bootloader的兼容性，请添加如下代码块至 `rules.mk`：

```make
# 选择Bootloader
BOOTLOADER = qmk-hid
```

要启用额外的功能支持，请添加如下定义至 `config.h`：

```c
#define QMK_ESC_OUTPUT F1  // COL pin if COL2ROW
#define QMK_ESC_INPUT  D5  // ROW pin if COL2ROW
// 可选:
//#define QMK_LED E6
//#define QMK_SPEAKER C6
```

目前来讲不推荐将 `QMK_ESC` 键设置成与[Bootmagic Lite](zh-cn/feature_bootmagic.md)同一个键，否则按下该键时只会让MCU在bootloader模式上反复进出。

制造商及型号字符串自动从 `config.h` 中获取，并会在型号后追加 " Bootloader"。

要生成该bootloader，需指定 `bootloader` 构建目标，即 `make planck/rev4:default:bootloader`。要生成可部署到正式产品的.hex文件（同时包含QMK及bootloader），使用 `production` 构建目标，即 `make planck/rev4:default:production`。

兼容的刷写工具：

* TBD
  * 目前只能选择使用该 [Python脚本](https://github.com/qmk/lufa/tree/master/Bootloaders/HID/HostLoaderApp_python), 或从LUFA仓库中构建[`hid_bootloader_cli`](https://github.com/qmk/lufa/tree/master/Bootloaders/HID/HostLoaderApp)。Homebrew也许（即将）能直接支持（通过 `brew install qmk/qmk/hid_bootloader_cli`）。

刷写过程：

1. 使用如下任一方式进入bootloader模式：
    * 点击 `RESET` 键码
    * 如果PCB上有 `RESET` 键，点击之
    * 快速短接一下RST到GND
2. 等待操作系统识别到设备
4. 将.hex文件刷写进去
5. 重置设备进入应用模式（可能会自动进行）

### `make` 构建目标

* `:qmk-hid`: 每5秒检测一次直到发现可用的DFU设备，然后进行固件刷写。

## STM32/APM32 DFU

所有的STM32及APM32 MCU系列，除F103型号外（参见[STM32duino小节](#stm32duino)）都在出场时预装了bootloader且无法修改或删除。

为确保对STM32-DFU bootloader的兼容性，请添加如下代码块至 `rules.mk`（可选替代项为 `apm32-dfu`）：

```make
# 选择Bootloader
BOOTLOADER = stm32-dfu
```

兼容的刷写工具：

* [QMK工具箱](https://github.com/qmk/qmk_toolbox/releases) （推荐的图形化工具）
* [dfu-util](https://dfu-util.sourceforge.net/) / QMK中将构建目标设为 `:dfu-util`（推荐的命令行工具）

刷写过程：

1. 使用如下任一方式进入bootloader模式（进入该模式后只有7秒时间可以刷写）：
    * 点击 `RESET` 键码（对STM32F042设备可能无效）
    * 如果有重置电路，点击PCB上的 `RESET` 键；有些主控板上可能会有一个开关需要先打开
    * 否则，你需要将 `BOOT0` 接线到VCC（通过 `BOOT0` 按钮或跳线），短接 `RESET` 至GND（通过 `RESET` 按钮或条线），然后断开 `BOOT0` 的接线。
2. 等待操作系统识别到设备
3. 将.bin文件刷写进去
4. 重置设备进入应用模式（可能会自动进行）

### `make` 构建目标

* `:dfu-util`: 每5秒检测一次直到发现可用的STM32 bootloader设备，然后进行固件刷写。
* `:dfu-util-split-left` 和 `:dfu-util-split-right`: 同 `:dfu-util` 一样会刷写固件，但额外地会设置手性设置到EEPROM中，对于基于Proton-C的分体式键盘这是理想的方法。
* `:st-link-cli`: 通过ST-Link CLI工具集而非dfu-util进行刷写，需要有ST-Link电子狗。
* `:st-flash`: 通过[STLink工具](https://github.com/stlink-org/stlink)内的 `st-flash` 工具而非dfu-util进行刷写，需要有ST-Link电子狗。

## STM32duino :id=stm32duino

该bootloader几乎是STM32F103板专用，该型号出厂不带USB DFU bootloader。其源代码及预编译好的二进制文件[在这里](https://github.com/rogerclarkmelbourne/STM32duino-bootloader)。

为确保对STM32duino bootloader的兼容性，请添加如下代码块至 `rules.mk`：

```make
# 选择Bootloader
BOOTLOADER = stm32duino
```

兼容的刷写工具：

* [QMK工具箱](https://github.com/qmk/qmk_toolbox/releases) （推荐的图形化工具）
* [dfu-util](https://dfu-util.sourceforge.net/) / QMK中将构建目标设为 `:dfu-util`（推荐的命令行工具）

刷写过程：

1. 使用如下任一方式进入bootloader模式（进入该模式后只有7秒时间可以刷写）：
    * 点击 `RESET` 键码（对STM32F042设备可能无效）
    * 如果有重置电路，点击PCB上的 `RESET` 键；有些主控板上可能会有一个开关需要先打开
    * 否则，你需要将 `BOOT0` 接线到VCC（通过 `BOOT0` 按钮或跳线），短接 `RESET` 至GND（通过 `RESET` 按钮或条线），然后断开 `BOOT0` 的接线。
2. 等待操作系统识别到设备
3. 将.bin文件刷写进去
4. 重置设备进入应用模式（可能会自动进行）

## Kiibohd DFU

Input Club出品的键盘使用NXP Kinetis微控制器而非STM32，并使用了独有的[自制bootloader](https://github.com/kiibohd/controller/tree/master/Bootloader)，然而处理器 及协议上两者大部分是一致的。

在 `rules.mk` 中该bootloader的设置项为 `kiibohd`，但既然该bootloader仅用在Input Club主控板上，就不必要设置到键映射或是用户级<!--译：不清楚这里的“user level”是个啥……-->了。

兼容的刷写工具：

* [QMK工具箱](https://github.com/qmk/qmk_toolbox/releases)（推荐的图形化工具）
* [dfu-util](https://dfu-util.sourceforge.net/) / QMK中将构建目标设为 `:dfu-util`（推荐的命令行工具）

刷写过程：

1. 使用如下任一方式进入bootloader模式：
    * 点击 `RESET` 键码（有可能只能进入到“安全”bootloader模式，参见[这里](https://github.com/qmk/qmk_firmware/issues/6112)）
    * 如果PCB上有 `RESET` 键，点击之
2. 等待操作系统识别到设备
3. 将.bin文件刷写进去
4. 重置设备进入应用模式（可能会自动进行）

## tinyuf2

键盘可以考虑支持tinyuf2 bootloader，目前唯一支持的设备是F401/F411 blackpill。

在 `rules.mk` 中该bootloader的设置项为 `tinyuf2`，也可指定到键映射及用户级中。

为确保对tinyuf2 bootloader的兼容性，请添加如下代码块至 `rules.mk`：

```make
# 选择Bootloader
BOOTLOADER = tinyuf2
```

兼容的刷写工具：

* 任何具备文件拷贝能力的程序，如 _macOS Finder_ 或 _Windows Explorer_ *。

刷写过程：

1. 使用如下任一方式进入bootloader模式：
    * 点击 `RESET` 键码
    * 双击PCB上的 `nRST` 键
2. 等待操作系统识别到设备
3. 将.uf2文件拷贝到新出现的USB存储设备上
4. 等待设备恢复可用状态
