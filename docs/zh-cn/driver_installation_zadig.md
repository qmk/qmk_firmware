# 利用Zadig安装Bootloader驱动

<!---
  original document: 0.15.12:docs/driver_installation_zadig.md
  git diff 0.15.12 HEAD -- docs/driver_installation_zadig.md | cat
-->

QMK在主机侧会展现为一台HID键盘设备，因此不需要额外的驱动。但若要在Windows下刷写键盘固件，重置主控板时出现的bootloader设备则通常需要一些驱动程序。

已知的特例有两个：常见于Pro Micro的Caterina bootloader，以及PJRC Teensys上的HalfKay bootloader, 会同时提供一个串行端口设备及一个HID设备，因此不需要额外的驱动。

这里我们推荐使用[Zadig](https://zadig.akeo.ie/)工具软件。若你在MSYS2中配置了开发环境，`qmk_install.sh` 脚本已经替你安装了相关驱动。

## 安装

将键盘重置为bootloader模式，点击 `RESET` 键码（可能在别的层中），或按一下通常在主控板背面上的重置开关，如果你的键盘上没有前两者，尝试在按住Esc键或空格+`B`键时插上键盘（更多信息参见[Bootmagic](zh-cn/feature_bootmagic.md)）。有些键盘使用[指令](zh-cn/feature_command.md)功能来代替Bootmagic，这种情况下，可以在键盘插入状态下点击 左Shift+右Shift+`B` 或 左Shift+右Shift+Esc组合键来进入bootloader模式。
也有一些键盘需要特别的操作才能进入bootloader状态。例如，[Bootmagic](zh-cn/feature_bootmagic.md)键（默认为：Esc键）在其它键上，比如左Control；或是指令组合键（默认为：左Shift+右Shift）为其它组合，如左Control+右Control。当不确定的时候，可以查阅一下主控板的README文件。

若要将USBaspLoader设备置为bootloader模式，请在按住 `BOOT` 按钮时点击 `RESET` 按钮，或是在按住 `BOOT` 按钮时插入USB线缆。

Zadig可以自动检测到bootloader设备，但有时你需要在 **Options（选项） → List All Devices（列出所有设备）** 的下拉列表中选择正确的设备。

!> 如果Zadig中列出的一个或多个设备为 `HidUsb` 驱动的，那么你的键盘应该没有进入bootloader模式，此时箭头会标记成橙色并会询问你确认是否要修改系统驱动，此时**不要**允许该操作。

如果箭头呈现绿色，选择所需的驱动，点击**Install Driver（安装驱动）**。如何选择正确的驱动进行安装请参见[已知驱动列表](#list-of-known-bootloaders)。

![在Zadig中安装了正确的bootloader驱动](https://i.imgur.com/b8VgXzx.png)

最后，重新拔插一次键盘，确认驱动可以正常加载。如果你在使用QMK工具箱进行刷写，记得也重启一下，因为有时它不会检测到驱动的变化。

## 从错误的驱动安装中恢复

如果你发现键盘无法输入了，应当是因为错误地替换了键盘本身的驱动，而不是bootloader的驱动，你的键盘没有进入bootloader模式就进行安装时就会遇到这个问题。在Zadig中很容易看出这个问题 - 正常的键盘在其所有的接口上都应该有 `HidUsb` 驱动：

![在Zadig中的一个正常的键盘](https://i.imgur.com/Hx0E5kC.png)

打开Device Manager（设备管理器），选择**View（查看） → Devices by container（依类型排序设备）**，并定位到你键盘名所在的节点。

![在设备管理器中安装了错误的驱动的主控板](https://i.imgur.com/o7WLvBl.png)

在这些节点上右键，选择**Uninstall device（卸载）**。如果出现了**Delete the driver software for this device（同时卸载该设备驱动文件）**也请勾选上。

![设备卸载确认对话框，选中了“删除驱动文件”](https://i.imgur.com/aEs2RuA.png)

点击 **Action（操作） → Scan for hardware changes（扫描检测硬件改动）**。此时，键盘应该恢复可用状态了。再确认一下Zadig中键盘是否在使用 `HidUsb` 驱动，如果是，键盘即完全恢复可用状态了，如果不是，重复这一步直到Zadig中报告了正确的驱动。

?> 在这一步有时需要重启电脑，以便Windows可以选用新驱动文件。

## 卸载

卸载bootloadeer设备要比安装过程复杂一些。

打开设备管理器，选择**查看 → 依类型排序设备**，并找到bootloader设备，寻找USB VID和PID与Zadig的[该表格](#list-of-known-bootloaders)中一致的项。

在设备属性的详细信息tab中，找到 `Inf name（INF名称）` 值，通常该值类似于 `oemXX.inf`：

![设备属性中的INF名称值](https://i.imgur.com/Bu4mk9m.png)

之后使用管理员权限打开一个命令行窗口（在开始菜单处输出 `cmd` 并点击Ctrl+Shift+回车）。执行 `pnputil /enum-drivers` 并找到 `INF名称` 与 `Published Name（发布名称）` 一致的项：

![对pnputil输出中匹配驱动项进行高亮展示](https://i.imgur.com/3RrSjzW.png)

执行 `pnputil /delete-driver oemXX.inf /uninstall`，之后该驱动会被删除，相关设备也不再使用该驱动，但设备是不会被移除的。

与上一节相似，本流程也可能需要执行多次，因为一个设备可能会有多个可用的驱动。

!> **警告：** 操作过程中*务必非常小心*！以免不小心卸载掉其它关键驱动。如果你对操作不是很确定，多次检查 `/enum-drivers`的输出信息，也可以考虑执行 `/delete-driver` 时不添加 `/uninstall` 开关\。

## 已知驱动列表 :id=list-of-known-bootloaders

该表列出了已知的bootloader设备及其USB VID（厂商ID）和PID（产品ID），以及可用于QMK刷写固件的驱动。留意usbser及HidUsb驱动是随Windows附带的，无法通过Zadig安装 - 如果你的设备驱动不符，请参照上节来卸载这些驱动。

此处列出的设备名应与Zadig中的一致，但不一定与设备管理器及QMK工具箱展示的一致。

|Bootloader    |设备名                         |VID/PID       |驱动   |
|--------------|------------------------------|--------------|-------|
|`atmel-dfu`   |ATmega16u2 DFU                |`03EB:2FEF`   |libusb0|
|`atmel-dfu`   |ATmega32U2 DFU                |`03EB:2FF0`   |libusb0|
|`atmel-dfu`   |ATm16U4 DFU V1.0.2            |`03EB:2FF3`   |libusb0|
|`atmel-dfu`   |ATm32U4DFU                    |`03EB:2FF4`   |libusb0|
|`atmel-dfu`   |*none* (AT90USB64)            |`03EB:2FF9`   |libusb0|
|`atmel-dfu`   |AT90USB128 DFU                |`03EB:2FFB`   |libusb0|
|`qmk-dfu`     |(键盘名) Bootloader            |同`atmel-dfu` |libusb0|
|`halfkay`     |*none*                        |`16C0:0478`   |HidUsb |
|`caterina`    |Pro Micro 3.3V                |`1B4F:9203`   |usbser |
|`caterina`    |Pro Micro 5V                  |`1B4F:9205`   |usbser |
|`caterina`    |LilyPadUSB                    |`1B4F:9207`   |usbser |
|`caterina`    |Pololu A-Star 32U4 Bootloader |`1FFB:0101`   |usbser |
|`caterina`    |Arduino Leonardo              |`2341:0036`   |usbser |
|`caterina`    |Arduino Micro                 |`2341:0037`   |usbser |
|`caterina`    |Adafruit Feather 32u4         |`239A:000C`   |usbser |
|`caterina`    |Adafruit ItsyBitsy 32u4 3V    |`239A:000D`   |usbser |
|`caterina`    |Adafruit ItsyBitsy 32u4 5V    |`239A:000E`   |usbser |
|`caterina`    |Arduino Leonardo              |`2A03:0036`   |usbser |
|`caterina`    |Arduino Micro                 |`2A03:0037`   |usbser |
|`bootloadhid` |HIDBoot                       |`16C0:05DF`   |HidUsb |
|`usbasploader`|USBasp                        |`16C0:05DC`   |libusbK|
|`apm32-dfu`   |APM32 DFU ISP Mode            |`314B:0106`   |WinUSB |
|`stm32-dfu`   |STM32 BOOTLOADER              |`0483:DF11`   |WinUSB |
|`kiibohd`     |Kiibohd DFU Bootloader        |`1C11:B007`   |WinUSB |
|`stm32duino`  |Maple 003                     |`1EAF:0003`   |WinUSB |
|`qmk-hid`     |(键盘名) Bootloader            |`03EB:2067`   |HidUsb |
