# 关于构建的常见问题

本页所写是QMK构建的常见问题.如果你还没有进行过编译,就看一下[构建环境搭建](getting_started_build_tools.md) 和 [make的说明](getting_started_make_guide.md).

## 如果您不能在Linux上编程
您需要适当的权限才能操作设备。对于Linux用户, 请参阅下方有关`udev`规则的说明。如果您对`udev`有问题，解决方法是用`sudo`命令。如果您不熟悉此命令，使用`man sudo`查看其手册或[看这个网页](https://linux.die.net/man/8/sudo).

在你的主控是ATMega32u4时，以下是使用`sudo`命令的样例：

    $ sudo dfu-programmer atmega32u4 erase --force
    $ sudo dfu-programmer atmega32u4 flash your.hex
    $ sudo dfu-programmer atmega32u4 reset

或只用；

    $ sudo make <keyboard>:<keymap>:dfu

使用`sudo`运行`make`一般来说**不**推荐，如果可能，尽量使用前一种方法之一。

### Linux `udev` 规则
在Linux上，您需要适当的权限才能访问MCU。你也可以在刷新固件时使用 `sudo`，或把这些文件放到`/etc/udev/rules.d/`。

**/etc/udev/rules.d/50-atmel-dfu.rules:**
```
# Atmel ATMega32U4
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff4", MODE:="0666"
# Atmel USBKEY AT90USB1287
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ffb", MODE:="0666"
# Atmel ATMega32U2
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff0", MODE:="0666"
```

**/etc/udev/rules.d/52-tmk-keyboard.rules:**
```
# tmk键盘产品     https://github.com/tmk/tmk_keyboard
SUBSYSTEMS=="usb", ATTRS{idVendor}=="feed", MODE:="0666"
```
**/etc/udev/rules.d/54-input-club-keyboard.rules:**

```
# Input Club keyboard bootloader
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1c11", MODE:="0666"
```

### 串行设备在Linux上检测不到bootloader模式
确保您的内核对您的设备有相应的支持。 如果你的设备是 USB ACM, 比如Pro Micro (Atmega32u4)，就要加上`CONFIG_USB_ACM=y`. 其他设备可能需要`USB_SERIAL` 及其任何子选项。

## DFU Bootloader的未知设备

如果您在使用Windows来刷新键盘的时候碰到了问题，检查设备管理器。如果在键盘处于 "bootloader模式"时你看到 "未知设备"，说明你可能面临设备问题。

重新运行MSYS2上的安装脚本或许会凑效（比如在MSYS2/WSL运行 `./util/qmk_install.sh`) 或者重新安装QMK工具箱也可能会解决你的问题。

如果以上方法还是短针攻疽，那您可能需要使用[Zadig Utility](https://zadig.akeo.ie/)。下载此程序, 找到设备问题, 然后选择 `WinUSB`选项, 然后点击"Reinstall driver"。完成后再试试刷新你的键盘。倘若依然徒劳无功，那就尝试所有选项直到好用为止。

?> 事实上没有一个驱动的最佳选择，有些选项就是和某些系统相辅相成。但libUSB和WinUSB似乎也算是这里的最佳选择了。
如果bootloader在设备列表中没有显示，你可能要使能 "List all devices"选项在选项菜单中`Options`，然后找到有问题的bootloader设备。(译者注：在win10中可能为 查看-显示隐藏的设备)

## USB VID 和 PID
你可以在编辑`config.h`时使用任何你想用的ID值。实际上，使用任何可能未使用的ID都没有问题，除了有极低的与其他产品发生冲突的可能性。

大多数QMK主板使用`0xFEED`作为vendor ID。您应该查看其他键盘，以确保选择了唯一的Product ID。

也要看看这个。
https://github.com/tmk/tmk_keyboard/issues/150

一也可以在下方链接购买一个唯一的VID:PID。不过个人使用似乎用不着这个。
- http://www.obdev.at/products/vusb/license.html
- http://www.mcselec.com/index.php?page=shop.product_details&flypage=shop.flypage&product_id=92&option=com_phpshop&Itemid=1

## AVR的BOOTLOADER_SIZE
注意Teensy2.0++ bootloader的大小是2048字节。有些Makefile注释错了。

```
# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 2048
#   Atmel DFU loader 4096       (TMK Alt Controller)
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=2048
```

## 在MacOS上 `avr-gcc: internal compiler error: Abort trap: 6 (program cc1)` 
这是brew更新的问题，导致AVR GCC依赖的符号链接被损坏。

解决方案是移除并重新安装所有受影响的模块。

```
brew rm avr-gcc
brew rm dfu-programmer
brew rm dfu-util
brew rm gcc-arm-none-eabi
brew rm avrdude
brew install avr-gcc
brew install dfu-programmer
brew install dfu-util
brew install gcc-arm-none-eabi
brew install avrdude
```

### avr-gcc 8.1 和 LUFA

如果你把avr-gcc升级到7以上你可能会遇到关于LUFA的问题。比如:

`lib/lufa/LUFA/Drivers/USB/Class/Device/AudioClassDevice.h:380:5: error: 'const' attribute on function returning 'void'`

那你就需要在brew中把avr-gcc回退到7。

```
brew uninstall --force avr-gcc
brew install avr-gcc@8
brew link --force avr-gcc@8
```

### 我刷新了我的键盘但是键盘不工作/按键没有注册 - 而且还是ARM的 (rev6 planck, clueboard 60, hs60v2, etc...) (Feb 2019)
由于EEPROM在基于ARM的芯片上的工作原理，保存的设置可能不再有效。这会影响默认层，而且*或许*在某些情况下，会使键盘不好用，我们仍在调查这些情况。重置EEPROM将解决此问题。

[Planck rev6键盘重置EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/539284620861243409/planck_rev6_default.bin) 是用于强制重置EEPROM的。刷入这个文件后，再次刷入正常固件，这会将键盘恢复到_正常_工作状态。
[Preonic rev3键盘重置EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/537849497313738762/preonic_rev3_default.bin)

如果以任何形式启用了bootmagic， 那么您还需要(看[Bootmagic文档](feature_bootmagic.md) 以及键盘信息，以了解如何执行此操作的详细信息).
