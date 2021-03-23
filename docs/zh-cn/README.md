# QMK机械键盘固件

[![当前版本](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![开发状态](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![异议](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![文档状态](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub贡献者](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub分支](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## 什么是 QMK 固件?

QMK (*Quantum Mechanical Keyboard*) 是一个社区维护的开源软件，包括 QMK 固件, QMK 工具箱, qmk.fm网站, 和这些文档。QMK 固件是一个基于[tmk\_keyboard](https://github.com/tmk/tmk_keyboard)的键盘固件，它在爱特梅尔AVR微控制器实现一些有用的功能,确切地说, 是在 [OLKB product line](https://olkb.com), 在 [ErgoDox EZ](https://www.ergodox-ez.com) 键盘, 和 [Clueboard product line](https://clueboard.co/). 上。它被移植到使用ChibiOS的ARM芯片上. 它可以在飞线键盘或定制PCB键盘中发挥功能.

## 如何得到它

如果你打算贡献布局, 键盘, 或者其他QMK特性, 一下是最简单的方法：[从GitHub获得repo分支](https://github.com/qmk/qmk_firmware#fork-destination-box), 并克隆你的repo到本地进行编辑，推送，然后从你的分支打开 [Pull Request](https://github.com/qmk/qmk_firmware/pulls).

此外, 你也可以直接下载 ([zip](https://github.com/qmk/qmk_firmware/zipball/master), [tar](https://github.com/qmk/qmk_firmware/tarball/master)), 或者从git克隆 (`git@github.com:qmk/qmk_firmware.git`), 或 https (`https://github.com/qmk/qmk_firmware.git`).

## 如何编译

在你能编译之前, 你需要[部署环境](zh-cn/getting_started_build_tools.md) 用于 AVR or/and ARM 开发。完成后, 你可以使用 `make` 命令来编译一个键盘和布局使用以下命令:

    make planck/rev4:default

这将建立 `planck`的`rev4` 修订版本并使用 `default`布局。并非所有键盘都有修订版本 (也叫做子项目或文件夹)，在此情况下，修订版本可以省略，如下:

    make preonic:default

## 如何定制

QMK 有许多 [特性](zh-cn/features.md)来探索，也有很多 [参考文档](https://docs.qmk.fm) 供您发掘。你可以通过修改 [布局](zh-cn/keymap.md)和[键码](zh-cn/keycodes.md)来利用许多特性。
