# 经常有人问的

## QMK 是什么？

[QMK](https://github.com/qmk)，是量子机械键盘（Quantum Mechanical Keyboard）的缩写，是一群键盘爱者为了 DIY 键盘而构建的工具。我们现在使用的 [QMK 固件](https://github.com/qmk/qmk_firmware)，是基于 [TMK](https://github.com/tmk/tmk_keyboard) 并经过大量修改的分支。

### 为什么命名为量子（Quantum）？

<!-- FIXME -->

## QMK 与 TMK 有什么区别？

TMK 最初由 [Jun Wako](https://github.com/tmk) 设计并实现。QMK 最初由 [Jack Humbert‘s](https://github.com/jackhumbert) 在 TMK 基础上分支出来并命名为 Planck。经过发展后 Jack's 的分支与 TMK 有了很大的区别，在 2015 年，Jack 决定将他的分支重新命名为 QMK。

从技术角度来看，QMK 在 TMK 的基础上构建了更多的新特性。最值得注意的是，QMK 扩展了更多的可用键码（keycodes），并实现了诸如 S()、LCTL() 和 MO() 等高级特性。您可以在 [Keycodes](keycodes.md) 中查看这些键码的完整列表。

从项目管理角度来看，TMK 自己维护所有官方支持的键盘，并提供一些社区支持。可以为其他键盘单独创建分支并自行维护，默认只提供几个键盘映射（KEYMAPS），用户之间并不共享键盘映射。QMK 鼓励通过集中管理的存储库共享键盘和键盘映射，并接受所有遵循质量标准的拉取请求。这些基本上是由社区维护的，但 QMK 团队在必要时会提供帮助。

QMK 与 TMK 各有优缺点，但只要有需要，代码可以在两者之间自由流动。
