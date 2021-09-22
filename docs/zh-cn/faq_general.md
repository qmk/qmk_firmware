# 常见问题

## QMK是什么?

[QMK](https://github.com/qmk), 是量子机械键盘(Quantum Mechanical Keyboard)的缩写，是一群开源爱好者为定制键盘开发的工具。我们从[QMK固件](https://github.com/qmk/qmk_firmware)开始，这是[TMK](https://github.com/tmk/tmk_keyboard)的魔改分叉。

### 为什么叫量子(Quantum)?

<!-- 待修复 译者吐槽：文档作者竟然也不知道为啥。。。 -->

## QMK和TMK有什么区别?

TMK最初由[Jun Wako](https://github.com/tmk)设计和执行。QMK始于[Jack Humbert](https://github.com/jackhumbert)为Planck键盘创建的TMK分叉。一段时间后，Jack的分叉就和TMK相去甚远了，于是在2015年，Jack决定改名QMK。

从技术观点来讲，QMK是TMK添加一些新功能而成的。尤其是QMK扩展了可用的键码，使高级功能进一步丰富比如 `S()`, `LCTL()`, 和 `MO()`。全部键码见[键码](keycodes.md).

从工程的社区管理来讲TMK自己维护了所有官方支持的键盘，只有很小一部分社区支持。独立社区维护已存在分叉或为其他键盘创建的分叉。默认支持很少的键码，所以用户通常不会与他人分享布局。QMK鼓励通过集中管理仓库分享布局和键盘，我们会采纳所有符合质量标准的PR。这就极大的保证了社区维护，同时QMK小组也会在必要时给予帮助。

这两种方法都有其优点和缺点，并且代码在有意义时在TMK和QMK之间自由流动。
