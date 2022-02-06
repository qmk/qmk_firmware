# US ANSI 上档符号键值

<!---
  original document: 0.15.20:docs/keycodes_us_ansi_shifted.md
  git diff 0.15.20 HEAD -- docs/keycodes_us_ansi_shifted.md | cat
-->

这部分键码对应的是 US ANSI 键盘“上档后”输入的符号，这些符号没有独立的键码，因此只能算是 `LSFT(kc)` 的简写，也就是发送的是一个伴随着左 Shift 键的未上档的键码，而不是直接发送该符号。

## 注意事项

然而，这些键码并不能在 Mod-Tap 或 Layer-Tap 中使用，因为它们的修饰键部分会被忽略掉。

另外，在使用 Windows 远程桌面时也可能会有问题，这是由于触发的 Shift 键的动作很快，远程桌面可能会错过该键码。

要解决这个问题，可以在远程桌面的“选项”下，打开“本地资源”标签，在键盘设置中，将下拉选项改为“这台计算机上”，之后问题即可修复，这些符号也可以正常输入了。

## 键码

|键                      |别名                |描述       |
|------------------------|-------------------|-----------|
|`KC_TILDE`              |`KC_TILD`          |`~`        |
|`KC_EXCLAIM`            |`KC_EXLM`          |`!`        |
|`KC_AT`                 |                   |`@`        |
|`KC_HASH`               |                   |`#`        |
|`KC_DOLLAR`             |`KC_DLR`           |`$`        |
|`KC_PERCENT`            |`KC_PERC`          |`%`        |
|`KC_CIRCUMFLEX`         |`KC_CIRC`          |`^`        |
|`KC_AMPERSAND`          |`KC_AMPR`          |`&`        |
|`KC_ASTERISK`           |`KC_ASTR`          |`*`        |
|`KC_LEFT_PAREN`         |`KC_LPRN`          |`(`        |
|`KC_RIGHT_PAREN`        |`KC_RPRN`          |`)`        |
|`KC_UNDERSCORE`         |`KC_UNDS`          |`_`        |
|`KC_PLUS`               |                   |`+`        |
|`KC_LEFT_CURLY_BRACE`   |`KC_LCBR`          |`{`        |
|`KC_RIGHT_CURLY_BRACE`  |`KC_RCBR`          |`}`        |
|`KC_PIPE`               |                   |`\|`       |
|`KC_COLON`              |`KC_COLN`          |`:`        |
|`KC_DOUBLE_QUOTE`       |`KC_DQUO`, `KC_DQT`|`"`        |
|`KC_LEFT_ANGLE_BRACKET` |`KC_LABK`, `KC_LT` |`<`        |
|`KC_RIGHT_ANGLE_BRACKET`|`KC_RABK`, `KC_GT` |`>`        |
|`KC_QUESTION`           |`KC_QUES`          |`?`        |
