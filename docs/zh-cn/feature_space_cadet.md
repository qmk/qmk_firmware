# Space Cadet: The Future, Built In
<!-- Deliberately not translated, leave it to a suitable translation -->

<!---
  original document: 0.15.12:docs/feature_space_cadet.md
  git diff 0.15.12 HEAD -- docs/feature_space_cadet.md | cat
-->

*译注：Space Cadet来源于(在西方早期程序员中)著名的键盘Space Cadet Keyboard，具体信息参见下面的链接或[维基百科](https://en.wikipedia.org/wiki/Space-cadet_keyboard)*

Steve Losh 在 [Space Cadet Shift](https://stevelosh.com/blog/2012/10/a-modern-space-cadet/) 详细地描述了该功能. 简而言之，点击左Shift时，会输出左括号；点击右Shift时，会输出右括号。如果按住Shift键，常规的Shift将正常工作。这功能实际上和听起来的一样爽，更爽的是现在连Control和Alt也支持！

## 使用指南

首先，在你的配列中完成以下任一项：
- 替换左Shift为 `KC_LSPO`（左Shift，左括号），替换右Shift为 `KC_RSPC`（右Shift，右括号）。
- 替换左Control为 `KC_LCPO`（左Control，左括号），替换右Control为 `KC_RCPC`（右Control，右括号）。
- 替换左Alt为 `KC_LAPO`（左Alt，左括号），替换右Alt为 `KC_RAPC`（右Alt，右括号）。
- 替换任意一个Shift为 `KC_SFTENT`（右Shift，回车）。

## 键码

|键码       |描述                          |
|-----------|-----------------------------|
|`KC_LSPO`  |按住时左Shift，点击时 `(`      |
|`KC_RSPC`  |按住时右Shift，点击时 `)`      |
|`KC_LCPO`  |按住时左Control，点击时 `(`    |
|`KC_RCPC`  |按住时右Control，点击时 `)`    |
|`KC_LAPO`  |按住时左Alt，点击时 `(`        |
|`KC_RAPC`  |按住时右Alt，点击时 `)`        |
|`KC_SFTENT`|按住时右Shift，点击时回车       |

## 须留意

同时按下两边的Shift键时会与Space Cadet功能冲突。请参见[指令功能](zh-cn/feature_command.md)以了解如何解决，也可以在 `rules.mk` 中禁用指令：

```make
COMMAND_ENABLE = no
```

## 配置

默认情况下Space Cadet假设键盘布局为US ANSI，如果你的布局使用不同的括号符，可以在 `config.h` 中重定义。可以修改修饰键点击时发送的字符，亦或阻止修饰键工作。这个新的配置项依次绑定了三个键码：按住或组合其它键使用时的修饰键；点击时发送的修饰键点击（`Tap Modifier`）（在 `KC_TRNS` 中没有修饰键时）；最后是点击时发送的键码。请记住，例如'KC_RSFT'按住时点击 `KC_KSPO` 及 `KC_TRNS` 时，修饰键依旧会对键码生效，即属于修饰键点击。

|定义             |默认值                          |描述                                                            |
|----------------|-------------------------------|----------------------------------------------------------------|
|`LSPO_KEYS`     |`KC_LSFT, LSPO_MOD, LSPO_KEY`  |按住时发送`KC_LSFT`，点击时发送 `LSPO_MOD` 及 `LSPO_KEY` 定义的键码. |
|`RSPC_KEYS`     |`KC_RSFT, RSPC_MOD, RSPC_KEY`  |按住时发送`KC_RSFT`，点击时发送 `RSPC_MOD` 及 `RSPC_KEY` 定义的键码. |
|`LCPO_KEYS`     |`KC_LCTL, KC_LSFT, KC_9`       |按住时发送`KC_LCTL`，点击时发送 `KC_LSFT` 及 `KC_9`.                |
|`RCPC_KEYS`     |`KC_RCTL, KC_RSFT, KC_0`       |按住时发送`KC_RCTL`，点击时发送 `KC_RSFT` 及 `KC_0`.                |
|`LAPO_KEYS`     |`KC_LALT, KC_LSFT, KC_9`       |按住时发送`KC_LALT`，点击时发送 `KC_LSFT` 及 `KC_9`.                |
|`RAPC_KEYS`     |`KC_RALT, KC_RSFT, KC_0`       |按住时发送`KC_RALT`，点击时发送 `KC_RSFT` 及 `KC_0`.                |
|`SFTENT_KEYS`   |`KC_RSFT, KC_TRNS, SFTENT_KEY` |按住时发送`KC_RSFT`，点击时发送 `SFTENT_KEY`.                       |
|`SPACE_CADET_MODIFIER_CARRYOVER`   |*未定义*     |在尝试触发其它修饰键的修饰键点击前，暂存目前的修饰键。这在尝试触发Space Cadet前频繁发生修饰键提前松开时会有用。(译注[^1]) |


## 过时的配置项

以下是一些内部用于向后兼容的定义，目前仍可以使用，但上面的定义适用性要强得多。例如，若你点击 `KC_LSPO` 时不想按住修饰键，在旧定义中只有一个办法，使用 `DISABLE_SPACE_CADET_MODIFIER`。但现在可以定义为：`#define LSPO_KEYS KC_LSFT, KC_TRNS, KC_9`，效果是在按住按键时触发左Shift，点击则发送 `KC_9`。

|定义                           |默认值        |描述                                 |
|------------------------------|-------------|-------------------------------------|
|`LSPO_KEY`                    |`KC_9`       |点击左Shift时发送的键码                |
|`RSPC_KEY`                    |`KC_0`       |点击右Shift时发送的键码                |
|`LSPO_MOD`                    |`KC_LSFT`    |应用在 `LSPO_KEY` 上的修饰键           |
|`RSPC_MOD`                    |`KC_RSFT`    |应用在 `RSPC_KEY` 上的修饰键           |
|`SFTENT_KEY`                  |`KC_ENT`     |点击Shift时发送的键码                  |
|`DISABLE_SPACE_CADET_MODIFIER`|*未定义*      |定义时将阻止修饰键应用在Space Cadet上   |

[^1]这句实在是绕，不能确保翻译到位，请参考英文文档
