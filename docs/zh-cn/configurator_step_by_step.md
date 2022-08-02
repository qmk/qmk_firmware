# QMK 配置器: 入门

<!---
  original document: 0.15.12:docs/configurator_step_by_step.md
  git diff 0.15.12 HEAD -- docs/configurator_step_by_step.md | cat
-->

本章节描述了如何使用QMK配置器构建出固件文件的过程。

## 第一步：选择键盘

从下拉列表中选择一款用于创建键映射的键盘。

?> 当键盘有多个版本可选择时，请确保选择正确。

因为很重要，这里我再次说一遍：

!> **请选择正确的版本！**

如果你的键盘声称是基于QMK的但未在列表中，可能是开发者还未提交给我们，或者提交还未被合并进来。若在[Pull Request](https://github.com/qmk/qmk_firmware/pulls?q=is%3Aopen+is%3Apr+label%3Akeyboard)中没有找到请求支持该键盘的issue，请到[QMK固件](https://github.com/qmk/qmk_firmware/issues)提交一个issue。也有一些基于QMK的键盘是由制造商自己的GitHub账号在维护着，请也确认一下。  <!-- FIXME(skullydazed): This feels too wordy and I'm not sure we want to encourage these kinds of issues. Also, should we prompt them to bug the manufacutrer? -->

## 第二部：选择键盘配列

选择最适合你要创建的键映射的配列，一些键盘的配列不完整或有问题，后续会逐渐支持。

!> 有时会遇到没有特别适合的配列的情况，请选择 `LAYOUT_all`。

## 第三步：命名你的键映射

如何起名完全取决于你。

?> 如果编译时遇到了问题，可能是因为QMK固件代码库中已经有了同名项，可以尝试改一下名字。

## 第四步：设计你的键映射

以下三种方法可以添加键码：

1. 拖拽
2. 点击布局上的空白项，再点击所需的键码
3. 点击布局上的空白项, 再点击你物理键盘上的按键

?> 鼠标在键上悬停时会有一个键码值的提示出现，详细描述信息请参见:

* [基础键码资料](zh-cn/keycodes_basic.md)
* [进阶键码资料](zh-cn/feature_advanced_keycodes.md)

!> 如果你选择的配列与物理实机有出入，请将不需要的按键留空。如果不清楚应该用哪个键，例如，你只需要一个退格键，但 `LAYOUT_all` 中有两个退格键，须将两个键都放上一样的键码。

## 第五步：保存键映射留待后续修订

当你调整完毕键映射方案，或打算以后继续编辑，点击 `导出Keymap JSON文件（Download this QMK Keymap JSON File）` 按钮，当前键映射方案将保存到你的计算机中，之后可以点击 `导入Keymap JSON文件(Upload a QMK Keymap JSON File)` 按钮导入后继续编辑。

!> **注意：** 导出的.json文件与 kbfirmware.com 和其它工具软件生成的并不兼容，如果你将导出的数据放到那些工具中，或尝试导入那些工具生成的.json文件，是不可行的。

## 第六步：编译固件

点击绿色的 `编译（Compile）` 按钮。

编译完成后，可以点击绿色的 `固件（Download Firmware）` 下载固件文件。

## 下一步：刷写到键盘中

参见[刷写固件](zh-cn/newbs_flashing.md).
