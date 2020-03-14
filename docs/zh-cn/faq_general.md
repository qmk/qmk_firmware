# 常见问题

## QMK是什么?

[QMK](https://github.com/qmk), 是量子机械键盘(Quantum Mechanical Keyboard)的缩写，是一群开源爱好者为定制键盘开发的工具。我们从[QMK固件](https://github.com/qmk/qmk_firmware)开始，这是[TMK](https://github.com/tmk/tmk_keyboard)的魔改分叉。

## 我不知道从哪里开始!

在这种情况下，你应该首先看[新手引导](zh-cn/newbs.md)。这个文档有很多有用的信息，几乎包含了所有你着手开发需要的信息。

如果有个问题，请访问[QMK配置工具](https://config.qmk.fm)，这个将会解决一大票你的需求。

## 我怎么才能向键盘刷新我编译的固件?

首先，看[编译/刷新问题页](zh-cn/faq_build.md)。这里有很多信息，你可以发现很多问题的解决方案。

## 那我要是发现这里没有提及的问题呢?

那也不是事。请先检查[GitHub中开放的issue](https://github.com/qmk/qmk_firmware/issues)看看是不是有人发现了相同的问题(请确认不是相似，而是相同)。

如果你还没找到请[打开一个新issue](https://github.com/qmk/qmk_firmware/issues/new)!

## 如果我发现了个bug怎么办?

请打开一个[issue](https://github.com/qmk/qmk_firmware/issues/new)，如果你知道如何修复，请在Github打开一个PR，提交修复。

## 不过`git`和`GitHub`听起来好吓人哦(摊手)!

别担心，我们有超棒的[指南](zh-cn/newbs_git_best_practices.md)告诉你如何让开始使用`git`和`GitHub`，这会让开发变得简单。

而且还有其他`git`和`GitHub`相关链接[在这](zh-cn/newbs_learn_more_resources.md)。

## 我有一个键盘，我想添加支持

那你太棒了!为你的键盘提交PR吧。我们会在检查代码后，并合并到QMK工程中!

### 我想用`QMK`做商标呢?

那我们太开心了!我们很乐意帮助你!

其实，我们有[整页](https://qmk.fm/powered/) 添加到你的键盘和页面专用的图标。这包括很多你需要的(知识和图片)来正式支持QMK.

如果你对这个有疑问打开一个issue或访问[Discord](https://discord.gg/Uq7gcHh).

## QMK和TMK有什么区别?

TMK最初由[Jun Wako](https://github.com/tmk)设计和执行。QMK始于[Jack Humbert](https://github.com/jackhumbert)为Planck键盘创建的TMK分叉。一段时间后，Jack的分叉就和TMK相去甚远了，于是在2015年，Jack决定将他的分叉改名QMK。

从技术观点来讲，QMK是TMK添加一些新功能而成的。尤其是QMK扩展了可用的键码，使高级功能进一步丰富比如 `S()`, `LCTL()`, 和 `MO()`。全部键码见[键码](zh-cn/keycodes.md).

从工程的社区管理来讲TMK自己维护了所有官方支持的键盘，只有很小一部分社区支持。独立社区维护已存在分叉或为其他键盘创建的分叉。默认支持很少的映射，所以用户通常不会与他人分享映射。QMK鼓励通过集中管理仓库分享映射和键盘，我们会采纳所有符合质量标准的PR。这就极大的保证了社区维护，同时QMK小组也会在必要时给予帮助。

这两种方法都有其优点和缺点，并且代码在有意义时在TMK和QMK之间自由流动。

<!--源文件：https://raw.githubusercontent.com/qmk/qmk_firmware/a701c15d872ad171592335e61e91d7234dbec54a/docs/faq_general.md 
    源提交哈希：a701c15d872ad171592335e61e91d7234dbec54a-->
<!--翻译时间:20200314-17:34(GMT+8)-->
