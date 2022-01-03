# ISP刷写指南

如果想通过USB刷写微控制器，我们需要bootloader的支持。bootloader存储在闪存的特定区块中，它的职责也包括将真正的固件应用程序（即QMK）写入到闪存的其余区块中。

不过，有时也会出现bootloader损坏需要重新刷写的情况，又或者是你希望换一个bootloader程序。我们无法通过已有的bootloader达成这个目标，原因很明显，它无法覆写掉正在运行中的自己。因此，你需要对微控制器进行ISP刷写。

AVR微控制器有很多种bootloader。而绝大部分 ARM 架构的 STM32 微控制器的ROM中都已配备了支持USB通信的bootloader，因此通常不需要进行ISP刷写。

## 硬件 :id=hardware

以下是支持ISP刷写的硬件设备，其产品链接指向的是官方版本，当然你也可以在其它的地方找得到。

你需要一些桥接用的线来连接ISP刷写器以及要刷写的控制器板。一些板子上会提供已导出的ISP引脚，如果没有的话，只能临时将电线接到PCB上 -- 一般是接到开关引脚或MCU针脚上。

接线比较简单，大部分情况下接到对应的上面就行。可以查阅MCU的数据手册以确定准确的 `RESET`、`SCLK`、`MOSI` 以及 `MISO` 引脚。

### 使用 Pro Micro 作为 ISP 刷写器

[SparkFun Pro Micro](https://www.sparkfun.com/products/12640)

若要将一个 5V/16MHz 的 Pro Micro 作为 ISP 刷写器，需要先加载一个[特别的固件](https://github.com/qmk/qmk_firmware/blob/master/util/pro_micro_ISP_B6_10.hex)来模拟出物理ISP刷写器。

**AVRDUDE 编程器**: `avrisp`  
**AVRDUDE 端口**: 串口

#### 接线

|Pro Micro  |Keyboard|
|-----------|--------|
|`VCC`      |`VCC`   |
|`GND`      |`GND`   |
|`10` (`B6`)|`RESET` |
|`15` (`B1`)|`SCLK`  |
|`16` (`B2`)|`MOSI`  |
|`14` (`B3`)|`MISO`  |

!> 注意 `10` 号引脚须接到键盘控制器的 `RESET` 引脚上，***不要***把 Pro Micro 的 `RESET` 引脚接到键盘的 `RESET` 引脚上去。

### Teensy 2.0 作为 ISP 刷写器

[PJRC Teensy 2.0](https://www.pjrc.com/store/teensy.html)

要将一个 Teensy 2.0 作为 ISP 刷写器，需要先加载一个[特别的固件](https://github.com/qmk/qmk_firmware/blob/master/util/teensy_2.0_ISP_B0.hex)来模拟出物理ISP刷写器。

**AVRDUDE 编程器**: `avrisp`  
**AVRDUDE 端口**: 串口

#### 接线

|Teensy|Keyboard|
|------|--------|
|`VCC` |`VCC`   |
|`GND` |`GND`   |
|`B0`  |`RESET` |
|`B1`  |`SCLK`  |
|`B2`  |`MOSI`  |
|`B3`  |`MISO`  |

!> 注意 `B0` 引脚须接到键盘控制器的 `RESET` 引脚上，***不要***把 Teensy 的 `RESET` 引脚接到键盘的 `RESET` 引脚上去。

### SparkFun PocketAVR / USBtinyISP / USBasp

[SparkFun PocketAVR](https://www.sparkfun.com/products/9825)  
[Adafruit USBtinyISP](https://www.adafruit.com/product/46)  
[Thomas Fischl's USBasp](https://www.fischl.de/usbasp/)

**AVRDUDE 编程器**: `usbtiny` / `usbasp`  
**AVRDUDE 端口**: `usb`

#### 接线

|ISP      |Keyboard|
|---------|--------|
|`VCC`    |`VCC`   |
|`GND`    |`GND`   |
|`RST`    |`RESET` |
|`SCLK`   |`SCLK`  |
|`MOSI`   |`MOSI`  |
|`MISO`   |`MISO`  |


### Bus Pirate

[Adafruit Bus Pirate](https://www.adafruit.com/product/237)

!> 5针的 "ICSP" 接口是用来对 Bus Pirate 的微控制器进行ISP刷写的，因此你应该将你的目标板连接在usb接口对面的10针接口上。

**AVRDUDE 编程器**: `buspirate`  
**AVRDUDE 端口**: 串口

#### 接线

|Bus Pirate|Keyboard|
|----------|--------|
|`+5V`     |`VCC`   |
|`GND`     |`GND`   |
|`RST`     |`RESET` |
|`CLK`     |`SCLK`  |
|`MOSI`    |`MOSI`  |
|`MISO`    |`MISO`  |

## 软件 :id=software

[QMK 工具箱](https://github.com/qmk/qmk_toolbox/releases) 同时支持ISP固件及bootloader的刷写，但是（目前还）不能在AVR的ISP刷写流程中设置熔丝字节*（fuse bytes），所以你可以考虑使用 `avrdude` 作为替代品。

（译注：熔丝字节内存储的是熔丝位（fuse bits），简而言之是用来控制一些基本硬件环境的配置信息，如时钟。由于找不到合适的中文说明页面，这里没有链接提供，请谅解）

我们极力推荐先配置 [QMK 开发环境](zh-cn/newbs.md)，它会将 `avrdude` 及其它的工具一并安装完成。

## Bootloader 固件

以下是可通过ISP刷写写到主控板上的文件，默认的熔丝配置也已列出。

如果你不确信你使用的是什么主控板，查看一下QMK中keyboard下的 `rules.mk` 文件，其 `MCU` 及 `BOOTLOADER` 行会列出这些信息。不同版本的键盘可能使用不同的主控板。

### Atmel DFU

这里是由 Atmel（现在是Microchip）[出厂默认配备的 bootloader](https://www.microchip.com/content/dam/mchp/documents/OTH/ProductDocuments/SoftwareLibraries/Firmware/megaUSB_DFU_Bootloaders.zip)。留意 AT90USB64 及 AT90USB128 的 bootloaders [略有改动](https://github.com/qmk/qmk_firmware/pull/14064)，因为在 Windows 8 及之后的版本中由于bug无法枚举到设备。

（译注：以下多个表格中的Low/High/Extended为熔丝字节的低/高/扩展字节）

|MCU                                                                                               |Low   |High                           |Extended|USB ID     |
|--------------------------------------------------------------------------------------------------|------|-------------------------------|--------|-----------|
|[ATmega16U4](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_atmega16u4_1.0.1.hex)|`0x5E`|`0x99` / `0xD9` (JTAG未启用)|`0xF3`  |`03EB:2FF3`|
|[ATmega32U4](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_atmega32u4_1.0.0.hex)|`0x5E`|`0x99` / `0xD9` (JTAG未启用)|`0xF3`  |`03EB:2FF4`|
|[AT90USB64](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_at90usb64_1.0.0.hex)  |`0x5E`|`0x9B` / `0xDB` (JTAG未启用)|`0xF3`  |`03EB:2FF9`|
|[AT90USB128](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_at90usb128_1.0.1.hex)|`0x5E`|`0x99` / `0xD9` (JTAG未启用)|`0xF3`  |`03EB:2FFB`|

### Caterina

这是继承自[LUFA CDC bootloader](https://github.com/abcminiuser/lufa/tree/master/Bootloaders/CDC)的 Arduino 风格的 bootloader，且仅用于 ATmega32U4。

一些配置随厂商不同而有差异，但基本工作逻辑一致。比如 SparkFun 配置，要求将 `RESET` 引脚[快速接地两次](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide#ts-reset)以使其处于 bootloader 模式能超过 750 ms。

|MCU                                                                                                                                                              |Low   |High  |Extended|USB ID     |
|-----------------------------------------------------------------------------------------------------------------------------------------------------------------|------|------|--------|-----------|
|[SparkFun Pro Micro (3V3/8MHz)](https://github.com/sparkfun/Arduino_Boards/blob/master/sparkfun/avr/bootloaders/caterina/Caterina-promicro8.hex)                 |`0xFF`|`0xD8`|`0xFE`  |`1B4F:9203`|
|[SparkFun Pro Micro (5V/16MHz)](https://github.com/sparkfun/Arduino_Boards/blob/master/sparkfun/avr/bootloaders/caterina/Caterina-promicro16.hex)                |`0xFF`|`0xD8`|`0xFB`  |`1B4F:9205`|
|[SparkFun LilyPadUSB（及一些Pro Micro的仿品）](https://github.com/sparkfun/Arduino_Boards/blob/main/sparkfun/avr/bootloaders/caterina/Caterina-lilypadusb.hex)|`0xFF`|`0xD8`|`0xFE`  |`1B4F:9207`|
|[Pololu A-Star 32U4](https://github.com/pololu/a-star/blob/master/bootloaders/caterina/Caterina-A-Star.hex)*                                                     |`0xFF`|`0xD0`|`0xF8`  |`1FFB:0101`|
|[Adafruit Feather 32U4](https://github.com/adafruit/Caterina-Bootloader/blob/master/Built%20Firmwares/Caterina-Feather32u4.hex)                                  |`0xFF`|`0xD8`|`0xFB`  |`239A:000C`|
|[Adafruit ItsyBitsy 32U4 (3V3/8MHz)](https://github.com/adafruit/Caterina-Bootloader/blob/master/Caterina_itsybitsy3V.hex)*                                      |`0xFF`|`0xD8`|`0xFB`  |`239A:000D`|
|[Adafruit ItsyBitsy 32U4 (5V/16MHz)](https://github.com/adafruit/Caterina-Bootloader/blob/master/Caterina_itsybitsy5V.hex)                                       |`0xFF`|`0xD8`|`0xFB`  |`239A:000E`|
|[Arduino Leonardo](https://github.com/arduino/ArduinoCore-avr/blob/master/bootloaders/caterina/Caterina-Leonardo.hex)*                                           |`0xFF`|`0xD8`|`0xFB`  |`2341:0036`|
|[Arduino Micro](https://github.com/arduino/ArduinoCore-avr/blob/master/bootloaders/caterina/Caterina-Micro.hex)*                                                 |`0xFF`|`0xD8`|`0xFB`  |`2341:0037`|

?> 标 * 的文件同时附带了 Arduino sketch，默认启动且也会呈现出一个串口，但那个*可不是* bootloader 设备。

### BootloadHID (PS2AVRGB)

该 bootloader 主要设计用于 PS2AVRGB 键盘的固件及 Bootmapper 客户端，在新的设计方案中已不推荐使用。

|MCU                                                                                                        |Low   |High  |USB ID     |
|-----------------------------------------------------------------------------------------------------------|------|------|-----------|
|[ATmega32A](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_ps2avrgb_bootloadhid_1.0.1.hex)|`0x0F`|`0xD0`|`16C0:05DF`|

### USBaspLoader

USBaspLoader 是一款基于 V-USB 来进行硬件 USBasp 设备模拟的 bootloader，运行在 ATmega32A 及 ATmega328P MCU 之上。

预编译的 `.hex` 文件通常不能使用，你可以在设置好QMK开发环境后按照 Coseyfannitutti 提供的指引来自行编译对应的MCU的版本：

|MCU                                                                                  |Low   |High  |Extended|USB ID     |
|-------------------------------------------------------------------------------------|------|------|--------|-----------|
|[ATmega32A](https://github.com/coseyfannitutti/discipline/tree/master/doc/bootloader)|`0x1F`|`0xC0`|*n/a*   |`16C0:05DC`|
|[ATmega328P](https://github.com/coseyfannitutti/discipad/tree/master/doc/bootloader) |`0xD7`|`0xD0`|`0x04`  |`16C0:05DC`|

须留意一些主控板会有特化的 bootloader 并由单独的仓库维护，通常可以在主控板的 readme 文件中找得到关联信息。

## 刷写 Bootloader

打开新的终端窗口 - 在 Windows 下请使用 MSYS2 或 QMK MSYS，而非命令提示符。转到 bootloader 的 `.hex` 文件所在目录，之后执行 `avrdude` 命令。

`avrdude` 的命令语法为：

```
avrdude -c <programmer> -P <port> -p <mcu> -U flash:w:<filename>:i
```

 * `<programmer>` 对应的是[硬件](#hardware)一节中列出的各 ISP 刷写器的编程器类型，比如 `avrisp`。
 * `<port>` 是插入 ISP 刷写器（若有）时出现的串口。部分编程器这里只使用 `usb`（也可以完全省略 `-P` 参数），因为它们不作为一个串口设备工作。
   * Windows: `COMx` - 打开设备管理器，在 "端口 (COM & LPT)" 分支下可以查到。
   * Linux: `/dev/ttyACMx`
   * macOS: `/dev/tty.usbmodemXXXXXX`
 * `<mcu>` 为目标 AVR 微控制器的小写名称，比如 `atmega32u4`。
 * `<filename>` 为要刷入的 bootloader 文件的绝对或相对路径，如 `Caterina-Micro.hex`。

可以通过 `man avrdude` 查阅到更多信息。

在正常情况下，你应该能看到类似如下输出内容：

```
avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e9587 (probably m32u4)
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "Caterina-Micro.hex"
avrdude: writing flash (32730 bytes):

Writing | ################################################## | 100% 11.58s

avrdude: 32730 bytes of flash written
avrdude: verifying flash memory against Caterina-Micro.hex:
avrdude: load data flash data from input file Caterina-Micro.hex:
avrdude: input file Caterina-Micro.hex contains 32730 bytes
avrdude: reading on-chip flash data:

Reading | ################################################## | 100% 10.33s

avrdude: verifying ...
avrdude: 32730 bytes of flash verified

avrdude: safemode: Fuses OK (E:CB, H:D8, L:FF)

avrdude done.  Thank you.
```

### 设置熔丝

这是一个比较高级些的话题，但在你更换新的 bootloader 类型时可能是必要信息（比如将 Pro Micro 上的 Caterina 更换为 Atmel/QMK 时）。熔丝控制着 AVR 微控制器的一些底层功能，如时钟频率，JTAG 是否启用，以及闪存中保留多大的空间给bootloader等。在[这里](https://www.engbedded.com/conffuse/)可以找到很多 AVR 的熔丝计算器。

!> **警告：** 设置错误的熔丝值，特别是时钟相关的位，很容易导致 MCU 进入不可恢复的状态，除非有更高电压的编程器（本文不会涉及）！在你执行这些命令前，务必再次检查确认。

若要设置熔丝值，添加如下参数到 `avrdude` 命令上：

```
-U lfuse:w:0xXX:m -U hfuse:w:0xXX:m -U efuse:w:0xXX:m
```

其中 `lfuse`，`hfuse` 及 `efuse` 参数为[硬件](#hardware)一节中列出的低、高熔丝字节及扩展熔丝字节。

?> 你可能会收到 `avrdude` 给出的扩展熔丝字节回读确认异常警告，如果十六进制值的低位值是正确的，通常这个警告可以忽略。这是因为一些 AVR 设备的扩展熔丝字节实际上并没有高4位，因此回读的值可能是任何值。

## 制作 "可量产"（production）的固件

对于量产目标来讲，是可以将 bootloader 及 QMK 固件整合成一个文件的，这主要归功于[Intel十六进制式规格](https://en.wikipedia.org/wiki/Intel_HEX)的特征：

 1. 在文本编辑器中打开 QMK 固件以及 bootloader 的 `.hex` 文件。
 2. 移除 QMK 固件中的最后一行（应该是 `:00000001FF` - 文件结尾的标识符）。
 3. 将 bootloader 的 `.hex` 文件中的内容粘贴到 QMK 固件文件的后面，中间不留空行。
 4. 另存为新文件，如 `<键盘>_<键映射>_production.hex`.

之后就可以刷写这个合并后的固件，以省去再次通过USB去刷写 QMK 固件的麻烦。
