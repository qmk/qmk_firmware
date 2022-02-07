# PR 审阅规则清单

<!---
  original document: 0.15.20:docs/pr_checklist.md
  git diff 0.15.20 HEAD -- docs/pr_checklist.md | cat
-->

本文以非穷尽式的方式列出了 QMK 协作者（Collaborators）在审阅一个PR时会查验的主要内容。

若你对此篇文档列出的建议有任何异议，请[提交一个 issue](https://github.com/qmk/qmk_firmware/issues/new) 来发起相关的讨论，也可以在 [Discord](https://discord.gg/Uq7gcHh) 上与协作者们进行沟通交流。

## 所有 PR 必须遵循的基本要求

- 所有提交的 PR 绝不能来自源仓库内的 `master` 分支
    - 并不是指示你将 PR 的提交目标分支指向其它，而是为了确保你不是在自己仓库的 master 分支上进行开发
    - 若提交者 _仍然_ 在 `master` 分支上进行开发，在代码被合并后，其会收到一个指向[“如何使用 git”](zh-cn/newbs_git_using_your_master_branch)的页面的链接的消息 -- （本文末尾有这条消息的内容）
- 新目录及文件的名称须为小写
    - 对于其名称的原始来源天然就含有大写的情况（比如 LUFA，ChibiOS，或从其它仓库引用来的文件等），本规则可不适用
    - 若确有正当的理由（即为了与核心文件保持一致等），本规则可不适用
        - 主控板设计者在命名时包含了大写字母，不是一个足够正当的理由
- 所有的 `*.c` 和 `*.h` 源文件头部须有开源协议头
    - 基于一致性考虑，推荐使用 GPL2/GPL3
    - 可以从本文最下方拷贝 GPL2+ 开源协议头的范本
    - 允许使用其它开源协议，但必须与 GPL 兼容且允许再发布。但使用特异的开源协议基本肯定会导致 PR 的合入被推迟
    - 缺失开源协议头时会因为无法确认开源协议是否会有冲突，从而导致 PR 的合入受阻
- 遵循 QMK 仓库的“最佳实践”
    - 本文不会穷尽式地列举所有要求，且随着时间推移一定会继续追加
    - 在头文件中使用 `#pragma once` 来替代 `#ifndef` 实现 include guard
    - 不能使用“传统式”的或底层的 GPIO/I2C/SPI 函数 -- 必须使用 QMK 抽象后的函数，除非有充足的理由（懒惰不是充足的理由）
    - 时间相关的函数也必须使用抽象后的：
        - 用 `wait_ms()` 替代 `_delay_ms()`（同时须移除 `#include <util/delay.h>`）
        - 应使用 `timer_read()` 及 `timer_read32()` 等。 -- 与时间相关的AIP可参见 [timer.h](https://github.com/qmk/qmk_firmware/blob/master/platforms/timer.h)
    - 若你认为一个新的抽象层很有必要，我们鼓励你：
        - 在你的键盘中先实现一个原型版本，直至其功能完备
        - 在Discord上与 QMK 协作者们对其进行探讨交流
        - 在新的独立的关键变更中进行重构
        - 移除你键盘内的独立副本
- 在开启 PR 前解决掉所有的合并冲突（在你需要帮助的时候，请到 Discord 上联系 QMK 协作者们）

## 对于键映射的 PR

- 倾向于通过 `#include QMK_KEYBOARD_H` 来引用特定的主控板文件
- 倾向于使用 `enum` 而不是 `#define` 来定义层
- 须使用 `enum` 而非 `#define` 来定义自定义键码，第一个定义必须含 ` = SAFE_RANGE`
- 在层定义宏的参数行中使用换行反斜杠（`\`）纯属多余
- 多使用空格调整一下排布（如让逗号或键码的第一个字符对齐）可以让键映射的可读性大大增强

## 对于键盘的 PR

已关闭的 PR 列表（用于参阅，这些审阅中的回复信息可以帮助你减少在你的审阅过程中出现多轮拉锯战式的沟通）：
https://github.com/qmk/qmk_firmware/pulls?q=is%3Apr+is%3Aclosed+label%3Akeyboard

- `info.json`
    - 合法的 URL
    - 正确的维护者信息
    - 在配置器内展现无异常（点击 Ctrl+Shift+I 来预览本地文件，打开快速输入可以验证其排布顺序）。
- `readme.md`
    - 须使用标准模板 -- [模板链接在此](https://github.com/qmk/qmk_firmware/blob/master/data/templates/avr/readme.md)
    - 须包含刷写命令，且其结尾须有 `:flash`
    - 正确的硬件采购链接（手工搭建的除外）-- 私下的组团购买形式是可以的，但若只是一次性的原型产品会遭到质疑。若其开源，应提供一个相关文件的地址链接。
    - 须提供清晰的重置到 bootloader 模式的操作指引
    - 一张该键盘的照片，最好再有一张PCB的照片
        - 图片不应存放在 `qmk_firmware` 仓库中
        - 图片应上传到其它的图片托管（外链）站上，比如 [imgur](https://imgur.com/).
- `rules.mk`
    - `MIDI_ENABLE`，`FAUXCLICKY_ENABLE` 及 `HD44780_ENABLE` 应已移除
    - 修正 `# Enable Bluetooth with the Adafruit EZ-Key HID` -> `# Enable Bluetooth`
    - 没有与启用功能相关的 `(-/+size)` 注释 
    - 若已指定了 bootloader，须删除列表中其它的 bootloader。
    - 若默认的 MCU 参数与 [mcu_selection.mk](https://github.com/qmk/qmk_firmware/blob/master/quantum/mcu_selection.mk) 中的一致，不应进行重复的定义。
- 键盘的 `config.h`
    - 在 `PRODUCT` 中不要重复列出 `MANUFACTURER`
    - 不使用 `#define DESCRIPTION`
    - 没有 Magic Key、MIDI 或 HD44780 的配置
    - 用户的 `#define` 配置项应移动到键映射的 `config.h` 文件中
    - 使用 "`DEBOUNCE`" 而非 "`DEBOUNCING_DELAY`"
    - 应提供主控板能够启动到 QMK 所需的最低限度的代码
        - 包含矩阵及核心设备的初始化代码
        - 对商用产品上的功能的仿制（如自定义键码及特别的灯光动画等）应在“非默认”（non-`default`）的键映射中实现
    - Vial 相关的文件或更改不会被采纳，因为 QMK 固件不依赖它（目前也没有 Vial 相关的核心代码被提交或是合入）
- `<keyboard>.c`
    - 空的 `xxxx_xxxx_kb()` 或其它的弱定义（weak-defined）的默认函数实现应移除
    - 被注释掉的函数也应被移除
    - `matrix_init_board()` 等已迁移到 `keyboard_pre_init_kb()`，参见：[keyboard_pre_init*](zh-cn/custom_quantum_functions?id=keyboard_pre_init_-function-documentation)
    - 若有自定义矩阵，应使用 `CUSTOM_MATRIX = lite`，以确保可应用标准的防抖处理，参见[自定义矩阵 'lite'](zh-cn/custom_matrix?id=lite)
    - 应尽量使用 LED 指示器[配置器选项](zh-cn/feature_led_indicators?id=configuration-options) 来实现 `led_update_*()` 的定制化
- `<keyboard>.h`
    - 文件头部有 `#include "quantum.h"`
    - 在适用的情况下，应有限使用标准定义的 `LAYOUT` 宏定义
        - 在适用的情况下，应优先使用社区配列的宏名称（`LAYOUT`/`LAYOUT_all` 上优先于上述规则）
- 键映射的 `config.h`
    - 除键盘定义外不应存在多余的 `rules.mk` 或 `config.h`
- `keymaps/default/keymap.c`
    - 须移除 `QMKBEST`/`QMKURL`
    - 若使用了 `MO(_LOWER)` 和 `MO(_RAISE)` 键码或等效键码，并且键映射中有校准层且同时按下了两个键 -- 在键映射中没有“直达校准层” 键码（比如 `MO(_ADJUST)`）时，应使用如下代码……
        ```
        layer_state_t layer_state_set_user(layer_state_t state) {
          return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
        }
        ```
        ……而不是自己在键映射的 `process_record_user()` 中手动处理 `layer_on()`，`update_tri_layer()`。
- 默认的（以及 via）键映射应当保持“原状”
    - 保持一个最基础的“白板”状态以允许其它用户基于它开发出新的自定义的键映射
    - 在可能的情况下，键映射应使用标准的配列
    - 默认键映射中不应启用 VIA -- 在 VIA 集成文档中要求应有独立的命名为 `via` 的键映射
- 提交者可以在 PR 中附带一个个人的（或用于展现亮点）的功能演示用键映射，但不应与'默认'键映射存在绑定关系
- 对于适配已存在的键盘主控的 PR，提交者也可以提供一份以“适配原产品”为目的的键映射，用于将其已有功能映射到社区版本中
- PR 中不可以包含 VIA 的 json 文件。这些文件即不属于 QMK 仓库，并且 QMK 固件也不会使用它们 -- 它们应当存放于 [VIA 键盘仓库](https://github.com/the-via/keyboards)
- 不要去包含（include）其它键盘或销售商目录下的文件，但核心文件是允许的。
  - 举个例子，只有 `wilba_tech` 可以去包含 `keyboards/wilba_tech/wt_main.c` 和  `keyboards/wilba_tech/wt_rgb_backlight.c`。但包含 `drivers/sensors/pmw3360.c` 是没有问题的。
  - 需要在多个主控板中使用的代码应考虑作为核心代码的新变更，并应被独立出来。

另外，针对 ChibiOS 而言：
- **偏硬性**地要求使用已有的 ChibiOS 主控板的定义。
    - 很多情况下，一个等效的 Nucleo 主控板可以在不同的闪存尺寸或同一个系列下仅略有差异的方案间共用
        - 例如：对于 STM32L082KZ 而言，其与 STM32L073RZ 基本一致，可以在 rules.mk 中使用 `BOARD = ST_NUCLEO64_L073RZ`
    - QMK 已逐渐转向尽量不接纳自定义的主控板定义，因为无力承担 ChibiOS 升级时带来的维护工作
- 新的主控板定义不得与键盘在一个 PR 中
    - 查阅下方的[核心 PR](#core-pr) 来了解如何向 QMK 添加新的主控板
- 若不可避免地需要一个新的主控板定义，`board.c` 中必须有标准的 `__early_init()` 实现（与其它的 ChibiOS 主控板定义一样）且有一个空的 `boardInit()`：
    - 参见 Arm/ChibiOS 的[早期初始化](zh-cn/platformdev_chibios_earlyinit?id=board-init)
    - `__early_init()` 应视情况替换为 `early_hardware_init_pre()` 或 `early_hardware_init_post()`
    - `boardInit()` 应迁移至 `board_init()`

## 核心 PR :id=core-pr

- 现在须以 `develop` 分支为目标分支，随后会随着重大变化的时间计划合入到 `master` 中
- 所有用于支持新硬件而引入的新主控板都需要在 `keyboards/handwired/onekey` 下添加对应的测试用项目
    - 对于新的微处理器，应添加一个新的以该微处理器为目标方案的“子”键盘，以用于验证编译构建
    - 对于新硬件的支持，比如显示屏、核心的矩阵定义、其它外围设备等，应提供一个对应的键映射
    - 若已存在可用于验证该功能的键映射，则该约束不再是必须项（比如一个新的 RGB 驱动芯片，已经被 `rgb` 键映射支持了）-- 可以在 Discord 上咨询 QMK 协作者来判断是否已有合适的已覆盖其功能的键映射
- 其他的要求由 QMK 协作者们决定
    - 因为这些变更覆盖面广，对于核心变更来说，这些要求会更主观一些

---

## 注意事项

对于使用自己的 `master` 分支进行开发的用户，会在 PR 合并完成后发送出如下内容：
```
For future reference, we recommend against committing to your `master` branch as you've done here, because pull requests from modified `master` branches can make it more difficult to keep your QMK fork updated. It is highly recommended for QMK development – regardless of what is being done or where – to keep your master updated, but **NEVER** commit to it. Instead, do all your changes in a branch (branches are basically free in Git) and issue PRs from your branches when you're developing.

There are instructions on how to keep your fork updated here:

[**Best Practices: Your Fork's Master: Update Often, Commit Never**](https://docs.qmk.fm/#/newbs_git_using_your_master_branch)

[Fixing Your Branch](https://docs.qmk.fm/#/newbs_git_resynchronize_a_branch) will walk you through fixing up your `master` branch moving forward. If you need any help with this just ask.

Thanks for contributing!
```

以上内容的译文：

```
以下内容供您日后参考，我们不推荐当前这种的将变更提交到 `master` 分支的方式，这是因为若有来自于 `master` 分支的 PR，将导致你难以将 QMK 仓库的更新同步到你的 fork 中。我们极力建议各位 QMK 开发者们 - 无论是要在哪里做出任何改动 - 保持 master 分支的同步更新，且**绝不**在上面进行提交。相应地，将所有开发中的变更提交到你的另一个分支中（Git下的分支基本是可以随意使用的）并基于此分支发起 PR 请求。

这里提供了如何保持你的 fork 更新状态的指引：

[在你Fork的主干上：频繁更新，不要提交](https://docs.qmk.fm/#/zh-cn/newbs_git_using_your_master_branch)

[恢复分支状态](https://docs.qmk.fm/#/zh-cn/newbs_git_resynchronize_a_branch)中将指引你如何修正你的 `master` 分支并让其同步到最新。若你在这个问题上需要任何帮助，请随时提出来。

感谢您所做出的贡献！
```

## 审阅流程

一般来讲，在 PR 被考虑合入前，我们期望能看到两个（或更多）的有意义（比如审阅了代码）的审核确认（approval）。审阅工作不限于协作者 -- 每一位意愿投入时间的社区成员都是受欢迎（且受鼓励）的，唯一的区别只是确认标记不会显示为绿色，这并不是什么问题！

此外，对 PR 的审阅都是在闲余时间进行的，我们并不是有偿在做审阅，仅仅是基于喜好。因此，可能过段时间我们才会关注到你的 PR。诸如家庭及个人生活等都会打断我们对 PR 的审阅，另一个重要的原因是防止激情耗竭。QMK 固件仓库每个月平均会有 200 个新增 PR 及 200 个 PR 被合入，因此还请多一些耐心。

## GPLv2 开源协议文件头范本

```
/* Copyright 2021 Your Name (@yourgithub)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
```

另一个可供考虑的是转为使用 [SPDX 标记](https://spdx.org/licenses/)：

```
// Copyright 2021 Your Name (@yourgithub)
// SPDX-License-Identifier: GPL-2.0-or-later
```
