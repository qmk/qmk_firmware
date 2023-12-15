# 极简式制作 - 通过配置器进行一次性的工程构建

<!---
  original document: 0.15.12:docs/easy_maker.md
  git diff 0.15.12 HEAD -- docs/easy_maker.md | cat
-->

你是否需要一种极简的控制器编程方案，类似Proton C或Teensy 2.0，以进行一次性的工程构建？QMK提供了极简制作器，通过QMK配置器可以在几分钟内制作一个固件。

有几种极简制作器，取决于你需要什么样的：

* [引脚直连](https://config.qmk.fm/#/?filter=ez_maker/direct) - 将每个开关独立直连到一个引脚
* 引脚直连 + 背光 (即将可用) - 类似引脚直连，单独加一个引脚连接到[背光](zh-cn/feature_backlight.md)控制器上
* 引脚直连 + 小键盘锁 (即将可用) - 类似引脚直连，单独加一个引脚连接到Numlock LED上
* 引脚直连 + 大写锁 (即将可用) - 类似引脚直连， 单独加一个引脚连接到Capslock LED上
* 引脚直连 + 编码器 (即将可用) - 类似引脚直连， 再加两个引脚用于连接一个旋钮编码器

## 快速指引

最简单的情况是使用一个引脚直连的主控板，将每个引脚连接到一个开关，另一端再接地即可，从以下键盘列表中可以选择一款支持的MCU：

* <https://config.qmk.fm/#/?filter=ez_maker/direct>

更多信息请参见[引脚直连](#direct-pin)一节。

# 引脚直连 :id=direct-pin

与其名字表意相同，它的原理是一个引脚连接一个开关，每个开关的另一端接地（VSS或GND），不需要额外的部件，通常MCU内部自带上拉电阻，因此可以感知开关动作。


这里有一个示意图，展示了如何将一个按钮连接到ProMicro的A3引脚上：

![该示意图中的ProMicro的A3引脚导出一根线，连接到了开关的左边，另一根线从开关右边引出并接地。](https://i.imgur.com/JcDhZll.png)

在开关连接到各自的引脚后，在键盘下拉列表中选择所使用的MCU，将键码指定到对应的引脚上即可构建出固件。以下链接仅展示支持引脚直连的极简式制作：

* <https://config.qmk.fm/#/?filter=ez_maker/direct>
