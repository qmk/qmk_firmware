# 常被问及的编译问题

<!---
  original document: 0.15.12:docs/faq_build.md
  git diff 0.15.12 HEAD -- docs/faq_build.md | cat
-->

本页涉及所有编译QMK的问题，如果你还没有试过，请先阅读[编译环境配置](zh-cn/getting_started_build_tools.md)及[Make指引](zh-cn/getting_started_make_guide.md)。

## 无法在Linux下编程
操作设备需要足够的权限，对于Linux用户，请参阅下方有关 `udev` 的规则说明。如果你对 `udev` 有困惑，可以先试试 `sudo` 命令，如果你对这个命令不熟悉，可以通过 `man sudo` 或 [这个web页面](https://linux.die.net/man/8/sudo)进行了解。

一个使用 `sudo` 的示例，这里假设你的控制器是ATMega32u4:

    $ sudo dfu-programmer atmega32u4 erase --force
    $ sudo dfu-programmer atmega32u4 flash your.hex
    $ sudo dfu-programmer atmega32u4 reset

或者只是:

    $ sudo make <keyboard>:<keymap>:flash

但请留意，用 `sudo` 来执行 `make` 通常***不是***一个好主意，请尽量考虑使用上面的办法。

### Linux `udev` 规则 :id=linux-udev-rules

在linux下，需要足够的权限才能读写bootloader设备，可以使用 `sudo` 来刷写固件（不推荐），也可以将[这个文件](https://github.com/qmk/qmk_firmware/tree/master/util/udev/50-qmk.rules) 放到 `/etc/udev/rules.d/` 目录下。

放好后，执行：

```
sudo udevadm control --reload-rules
sudo udevadm trigger
```

**注意：**在旧版ModeManager（<1.12）中，过滤功能仅在严格模式（strict mode）下可用，可以调整一下配置：

```
printf '[Service]\nExecStart=\nExecStart=/usr/sbin/ModemManager --filter-policy=default' | sudo tee /etc/systemd/system/ModemManager.service.d/policy.conf
sudo systemctl daemon-reload
sudo systemctl restart ModemManager
```

### 在Linux下无法检测到bootloader模式下的串口设备
确认一下你的内核版本是否已配置为支持该设备。如果你的设备使用USB ACM，如Pro Micro（Atmega32u4），确认内核 配置中包含 `CONFIG_USB_ACM=y`，其它类型的设备可能需要 `USB_SERIAL` 及相关子配置的支持。

## DFU Bootloader显示为未知设备

在Windows下刷写键盘固件时很常见的一个问题。主要原因是安装了错误的驱动，或者压根没有装驱动。

要修复这个问题，可以尝试重新执行QMK安装脚本(位于MSYS2或WSL中的 `qmk_firmware` 目录下的 `./util/qmk_install.sh`)或重新安装QMK工具箱。此外，也可以尝试下载安装[QMK驱动安装包 `qmk_driver_installer`](https://github.com/qmk/qmk_driver_installer)来修复。

如果问题依旧，可能是需要下载安装Zadig，具体请参考[通过Zadig安装bootloader驱动](zh-cn/driver_installation_zadig.md)。

## USB VID 和 PID
通过编辑 `config.h` 你可以自由指定ID，随便选一个看起来不常用的ID一般不会有什么问题，冲突的概率很低。

大部分QMK设备都选用 `0xFEED` 作为VID，选取PID前请先看一下其它键盘的情况再决定。

同时请阅读这个issue：
https://github.com/tmk/tmk_keyboard/issues/150

你可以在以下地址购买唯一的VID:PID，但我觉得个人使用情况下没有必要。
- https://www.obdev.at/products/vusb/license.html
- https://www.mcselec.com/index.php?page=shop.product_details&flypage=shop.flypage&product_id=92&option=com_phpshop&Itemid=1

### 在我刷写完键盘后就没响应了/点了没动静了 -- 设备是arm的（rev6 planck, clueboard 60, hs60v2等）(2019年2月)
因为ARM平台下EEPROM特殊的工作模式，已保存的配置可能会失效。主要影响的是默认层，有概率在特定情况下会导致键盘不可用，我们还没有搞明白原因。这个问题可以在重置EEPROM后恢复。

[Planck rev6 上重置 EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/539284620861243409/planck_rev6_default.bin) 可以用于强制重置EEPROM。刷入这个文件后，再次刷入正常固件，会将键盘恢复到_正常_工作状态。
[Preonic rev3 上重置 EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/537849497313738762/preonic_rev3_default.bin)

也可以考虑使用bootmagic，只要它可以用。（参见[Bootmagic文档](zh-cn/feature_bootmagic.md)并结合键盘情况来了解如何操作）
