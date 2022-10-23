# 常见问题（FAQ）

<!---
  original document: 0.15.12:docs/faq_general.md
  git diff 0.15.12 HEAD -- docs/faq_general.md | cat
-->

## QMK是什么?

[QMK](https://github.com/qmk), 是量子机械键盘（Quantum Mechanical Keyboard）的缩写, 是制作自定义键盘工具的人组成的组织。 一切始于[QMK固件](https://github.com/qmk/qmk_firmware)项目, 可以认为是[TMK](https://github.com/tmk/tmk_keyboard)的改进版本.

## 不知道从哪开始搞！

这样的话建议从[新手指引](zh-cn/newbs.md)开始。那里有你需要的高质量的入门信息。

如果还是搞不懂的话，直接跳到[QMK配置器](https://config.qmk.fm)吧，你核心需要的东西都在那里。

## 我的固件如何刷写到硬件上？

先参考[编译/刷写固件FAQ](zh-cn/faq_build.md)，里面有充足的资料，常见的问题也给出了足够多的解决办法。

## 我的问题这里找不到相关信息怎么办？

没有关系，请到[GitHub上发issue](https://github.com/qmk/qmk_firmware/issues)看看是否有人遇到了相同的问题（留意一定是相同的问题，而不是相似的）。

如果还是找不到解决办法，请[新建issue](https://github.com/qmk/qmk_firmware/issues/new)！

## 我好像找到了bug？

那么新建一个[issue](https://github.com/qmk/qmk_firmware/issues/new)吧，如果你还知道怎么修，带着修复方案发个Pull Request吧。

## 但是 `git` 和 `GitHub` 我实在是玩不转！

别担心，这里有很好的[入门指引](zh-cn/newbs_git_best_practices.md)可以教你怎么轻松快乐地使用 `git` 和GitHub进行开发。

更多的 `git` 和GitHub知识，参考[这里](zh-cn/newbs_learn_more_resources.md)。

## 我可以添加一个支持的键盘

太棒啦！请发Pull Request吧，在代码审阅后，我们会合并进去！

### 我可以打上 `QMK` 的标吗?

很好啊！我们甚至乐意帮你这么做！

我们有[一整页](https://qmk.fm/powered/)的资料旨在帮你在页面和键盘上打上QMK的标，里面有QMK官方提供的所有支援（信息及图片）。

如果你有任何疑问，可以发issue或通过[Discord](https://discord.gg/Uq7gcHh)联系我们。

## QMK和TMK区别是什么？

TMK原先是由[Jun Wako](https://github.com/tmk)设计实现的，QMK来源于[Jack Humbert](https://github.com/jackhumbert)的Planck的TMK fork。一段时间后，Jack的这个fork与TMK渐行渐远，到2015年时，Jack决定将这份fork重命名为QMK。

技术上讲QMK等同于基于TMK增加了一些新功能，最显著的是在扩充了可用键码后，实现了很多诸如 `S()`, `LCTL()` 及 `MO()` 这样的高级功能，所有这些键码可以参见[键码](zh-cn/keycodes.md)页。

从工程项目及社区维护角度来看，TMK维护了一份官方支持的键盘及很少量的社区贡献，社区中各自维护着各自的fork，且因为默认键映射很少，TMK的使用者基本不会共享键映射。QMK通过统一的集约式仓库（repo）管理来鼓励分享键盘及键映射，任何符合质量基线的pull request都会被采纳，因此绝大部分贡献都来源于社区，QMK小组会在必要时提供支援。

两种模式各有利弊，并且TMK和QMK之间也会有合乎理法的代码交流。
