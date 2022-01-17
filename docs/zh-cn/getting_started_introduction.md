# 介绍

<!---
  original document: 0.15.12:docs/getting_started_introduction.md
  git diff 0.15.12 HEAD -- docs/getting_started_introduction.md | cat
-->

本页解释了使用QMK项目所需的基本信息。它假定您能熟练使用Unix shell，但您不熟悉C语言也不熟悉使用make编译。

## 基本QMK结构

QMK是[Jun Wako](https://github.com/tmk)的[tmk_keyboard](https://github.com/tmk/tmk_keyboard)工程的一个分叉。经过更改的TMK原始代码放在`tmk_core` 文件夹中。 QMK增加的新东西可以在 `quantum` 文件夹中找到。 键盘项目可以在 `handwired`（手动飞线） 和 `keyboard`（PCB键盘）这两个文件夹找到。

### 用户空间结构

在`users`文件夹里面的目录是每个用户的目录。这个文件夹里面放的是用户们在不同键盘都能用到的代码。详见[用户空间特性](zh-cn/feature_userspace.md) 

### 键盘项目结构

在`keyboards`文件夹和他的子文件夹`handwired`中就是各个键盘的项目了，比如`qmk_firmware/keyboards/clueboard`。内部结构与如下:

* `keymaps/`: 可以构建的不同布局
* `rules.mk`: 用来设置 "make" 命令默认选项的文件。别直接编辑这个文件,你应该使用具体某个布局的 `rules.mk`.
* `config.h`: 用于设置默认编译选项的文件。别直接编辑这个文件, 你应该使用具体某个布局的 `config.h`.

### 布局结构

在各个布局的文件夹，你能找到以下文件。只有 `keymap.c` 是必要的, 如果其他文件找不到就会直接选择默认选项。

* `config.h`: 配置布局的选项
* `keymap.c`: 布局的全部代码, 必要文件
* `rules.mk`: 使能的QMK特性
* `readme.md`:介绍你的布局,告诉别人怎么使用，附上功能说明。请将图片上传到imgur等图床（译注：imgur可能已被墙，为了方便国人访问，建议使用国内可以直接访问的图床）。

# `config.h` 文件

有三个重要的`config.h` 位置:

* 键盘 (`/keyboards/<keyboard>/config.h`)
* 用户空间 (`/users/<user>/config.h`)
* 布局 (`/keyboards/<keyboard>/keymaps/<keymap>/config.h`)

构建系统按照上述顺序自动获取配置文件。如果要覆盖由上一个 `config.h` 所做的设置，您需要首先为要更改的设置包含一些样板代码。

```
#pragma once
```

要覆盖上一个 `config.h` 所做的设置，你要先 `#undef` 然后再 `#define` 这个设置.

样板代码和设置看起来像这样：

```
#pragma once

// 像下面那样覆盖设置（MY_SETTING指的是你要覆盖的设置项）!
#undef MY_SETTING
#define MY_SETTING 4
```
