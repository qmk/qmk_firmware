# QMK入门教程

<!---
  original document: 0.15.12:docs/newbs.md
  git diff 0.15.12 HEAD -- docs/newbs.md | cat
-->

就像计算机一样，每把键盘里也有一个处理器，它的职责是在你点击键盘时，检测到这个动作并反馈给计算机。QMK固件即是为了这个目的而设计的一种"软件"，负责检测点击，反馈给电脑。当你构建出一个自定义键映射时，就是在创建一个新的键盘"软件"。

QMK的愿景是提供强有力的功能，让不可能的事情变得可能，简单的事情依旧简单。即便是不会编程也可以创建强大的键映射方案。

想知道你的键盘是否能运行QMK？如果这个键盘是你自己组建的，那么很可能是可以的。我们[已经支持很多键盘](https://qmk.fm/keyboards/)，所以即便你的键盘不能运行QMK，你也很容易能买到满足要求的键盘。

?> **这份指南适合于我吗？**<br>
编程对你是个困难的话，可以看看我们的[在线GUI页面](zh-cn/newbs_building_firmware_configurator.md)。</div>

## 总览

这份指南适用于想通过源代码编译出键盘固件的需求。对于程序员，全过程都会感觉很熟悉。教程主要分3部分：

1. [环境配置](zh-cn/newbs_getting_started.md)
2. [构建第一个固件](zh-cn/newbs_building_firmware.md)
3. [刷写固件](zh-cn/newbs_flashing.md)

该指南的目的是帮助那些从未编译过软件的人，很多取舍及建议都是基于这个考量。完成一个目标可能有多种方案，我们尽量都去支持，如果你搞不明白你的目标如何实现，可以[向我们寻求帮助](zh-cn/support.md)。

## 更多资料

这份指南之外，也有一些其它能帮助你学习QMK的资料。我们归纳整理在[大纲](zh-cn/syllabus.md)页面和[学习资料](zh-cn/newbs_learn_more_resources.md)页面
