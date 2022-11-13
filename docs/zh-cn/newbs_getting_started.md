# 配置环境

<!---
  original document: 0.15.12:docs/newbs_getting_started.md
  git diff 0.15.12 HEAD -- docs/newbs_getting_started.md | cat
-->

构建键映射前，有一些必须安装配置的构建工具，但无论你要编译多少个固件，这一步只需要做一次。

## 1. 必备工具

首先需要确保一些基本的软件配备。

* [文本编辑器](zh-cn/newbs_learn_more_resources.md#text-editor-resources)
  * 你需要至少一个能编辑常规文本的软件。系统自带的编辑器通常不会如实保存（会做一些额外的处理，如回车），所以选择编辑器时需要留意。
* [QMK工具箱(可选)](https://github.com/qmk/qmk_toolbox)
  * 在Windows及macOS上可用的图形程序，用于编辑及调试你的键盘

?> 如果你没有Linux/Unix命令行使用经验，有些基本概念需要先学习一下。[这些资料](zh-cn/newbs_learn_more_resources.md#command-line-resources)是个使用QMK很好的参考。

## 2. 准备构建环境 :id=set-up-your-environment

我们已经尽力让QMK易于配置了，你只要准备好Linux或Unix环境，剩余的交给QMK来安装。

<!-- tabs:start -->

### ** Windows **

QMK有维护一套基于MSYS2的软件包，所有命令行程序和依赖都是齐备的。通过 `QMK MSYS` 快捷命令可以快速启动开发环境。

#### 依赖项

需安装[QMK MSYS](https://msys.qmk.fm/)，最新版在[这里](https://github.com/qmk/qmk_distro_msys/releases/latest)。

此外，如果想自行安装MSYS2环境，下面给出了具体的步骤。

<details>
  <summary>自行安装</summary>

?> 若决定使用 `QMK MSYS`，请跳过此节.

#### 依赖项

遵循 https://www.msys2.org 上的指引，安装MSYS2、Git和Python。

在MSYS2安装完毕后，关闭所有的MSYS终端，启动新的MinGW 64-bit终端。

!> **注意:** MinGW 64-bit 终端*不同于*安装包最后打开的MSYS终端，窗口标题应当是紫色的"MINGW64"而不是"MSYS"。具体的差异可以[参考这里](https://www.msys2.org/wiki/MSYS2-introduction/#subsystems)。

执行如下命令：

    pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-python3-pip

#### 安装

安装QMK命令行程序:

    python3 -m pip install qmk

</details>

### ** macOS **

QMK维护了一套Homebrew tap和formula以用于自动安装命令行程序及依赖项。

#### 依赖项

须先安装Homebrew，可以参考 https://brew.sh

#### 安装

安装QMK命令行程序：

    brew install qmk/qmk/qmk

### ** Linux/WSL **

?> **WSL用户注意**: 默认情况下，QMK仓库会被clone到home目录下，如果想指定其它目录，务必留意要放在WSL文件系统中（即，非 `/mnt` 目录下），否则文件读写会[非常慢](https://github.com/microsoft/WSL/issues/4197).

#### 依赖项

须安装Git及Python，通常你肯定已经有了，如果确实没有，请使用下面的方法尝试安装：

* Debian / Ubuntu / Devuan: `sudo apt install -y git python3-pip`
* Fedora / Red Hat / CentOS: `sudo yum -y install git python3-pip`
* Arch / Manjaro: `sudo pacman --needed --noconfirm -S git python-pip libffi`
* Void: `sudo xbps-install -y git python3-pip`
* Solus: `sudo eopkg -y install git python3`
* Sabayon: `sudo equo install dev-vcs/git dev-python/pip`
* Gentoo: `sudo emerge dev-vcs/git dev-python/pip`

#### 安装

安装QMK命令行程序：

    python3 -m pip install --user qmk

#### 社区提供的包

有一些社区成员提供的包，可能版本会有落后或是功能不全的问题，如果你遇到了什么问题，请联系维护它的社区成员。

Arch系环境下可以使用官方源安装命令行程序（在写这份文档时，有些依赖项被标记为可选的，其实不是）：

    sudo pacman -S qmk

也可以尝试AUR的 `qmk-git`：

    yay -S qmk-git

###  ** FreeBSD **

#### 安装

使用FreeBSD包安装QMK命令行程序：

    pkg install -g "py*-qmk"

请遵循安装后输出的指引操作进行配置（使用 `pkg info -Dg "py*-qmk"` 可以显示这份指引）。

<!-- tabs:end -->

## 3. 执行QMK配置 :id=set-up-qmk
*译注：由于setup过程中需要从github clone依赖项，请先确保科学上网*

<!-- tabs:start -->

### ** Windows **

安装QMK后，执行：

    qmk setup

通常所有的询问回复 `y` 就行了。

### ** macOS **

安装QMK后，执行：

    qmk setup

通常所有的询问回复 `y` 就行了。

### ** Linux/WSL **

安装QMK后，执行：

    qmk setup

通常所有的询问回复 `y` 就行了。

?>**Debian及Ubuntu系环境须留意**:
也许你会遇到 `bash: qmk: command not found` 错误，主要是因为Debian上的Bash 4.4版本引入的一个[bug](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=839155)，`$HOME/.local/bin` 被从PATH环境变量中删除了，后续版本中这个问题已被修复。
然而Ubuntu很挫地再次引入了这个bug[且没有修复](https://bugs.launchpad.net/ubuntu/+source/bash/+bug/1588562)。
不过修复也很容易，在当前账户中执行：`echo 'PATH="$HOME/.local/bin:$PATH"' >> $HOME/.bashrc && source $HOME/.bashrc`

###  ** FreeBSD **

安装QMK后，执行：

    qmk setup

通常所有的询问回复 `y` 就行了。

<!-- tabs:end -->

?> QMK的home目录可以在安装时通过 `qmk setup -H <path>` 来指定，安装后也可以通过[命令行程序来配置](zh-cn/cli_configuration.md?id=single-key-example)`user.qmk_home`变量，可以通过 `qmk setup --help` 查看所有可用配置。

?> 若你熟悉GitHub，[推荐阅读这份指引](zh-cn/getting_started_github.md)通过 `qmk setup <github_username>/qmk_firmware` 来clone你自己的fork。如果你看不懂这一段啥意思，忽略就是了。

## 4. 测试你的构建环境

QMK构建环境搭建完成，可以尝试构建一个键盘固件。使用以下指令格式，先试试编译默认提供的键映射：

    qmk compile -kb <keyboard> -km default

例如，要构建一个Clueboard 66%，就这样执行：

    qmk compile -kb clueboard/66/rev3 -km default

你应当能看到像这样的输出信息：

```
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

## 5. 配置你的构建环境 (可选的)

通过对默认配置的简单调整，QMK用起来会更有趣一些，我们来试试！

大部分QMK新手手头只有一把键盘，可以通过 `qmk config` 命令将它设置为默认键盘，例如你想将 `clueboard/66/rev4` 设置为默认，可以这样：

    qmk config user.keyboard=clueboard/66/rev4

也可以调整默认的键映射名称。社区上大家常用自己的GitHub用户名，这也是我们推荐的做法。

    qmk config user.keymap=<github_username>

完成后，这些配置就不用管了，编译键盘固件就可以直接这样执行：

    qmk compile

# 制作你自己的键映射

万事俱备啦！请继续阅读[构建第一个固件](zh-cn/newbs_building_firmware.md).
