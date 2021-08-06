# 介绍

你的电脑键盘里面包含一个处理器, 这个处理器和你电脑里面的不太一样。这个处理器负责运行一些特殊的软件，这些软件可以监测按钮按下并将按钮处于按下还是释放状态的数据发送出去。QMK就是这样一种软件，即监测按钮被按下并发送这样的信息到作为主机的计算机上。当你创建了你的布局, 你也就创建了你的键盘运行的的可执行程序。

QMK试图通过使简单的事情变得更简单，使使不可能成为可能来把大量的权力交给你。你不需要懂如何通过程序创建强大的布局——你只需要遵循简单的语法规则。

# 新手上路

在你能创建布局前,你要安装一些软件来建立你的开发环境。无论你想编译多少固件，这个操作都只需要进行一次。

如果您更喜欢图形化界面, 请考虑使用在线工具[QMK配置器](https://config.qmk.fm)。 请参考 [使用在线GUI构建您的第一个固件](newbs_building_firmware_configurator.md)。


## 下载软件

### 文本编辑器

你需要一个可以编辑 **纯文本** 文件的程序。在Windows上你可以用Notepad, 在Linux上使用gedit，这两个都是简单又实用的文本编辑工具。 在macOS上, 请小心使用 “文本编辑” 这个默认软件: 如果你不明确的选择_格式_菜单中的 _制作纯文本_ 的话文本将不会被保存为纯文本。

你也可以下载并安装一个专用编辑器 [Sublime Text](https://www.sublimetext.com/) 或 [VS Code](https://code.visualstudio.com/)。 这大概是跨平台的最好方法了, 这些编辑器是专门为了编辑代码设计的。

?>搞不清用哪种编辑器? Laurence Bradford 写了篇关于编辑器选择的文章 [a great introduction](https://learntocodewith.me/programming/basics/text-editors/)。

### QMK 工具箱

QMK 工具箱 是一种可选的Windows和macOS下的图形化工具，它可以对你的定制键盘进行编程和调试。你可能会发现它就是你能简单的刷新你的键盘固件并查看调试信息的稀世珍宝。

[在这里下载最新发布版本](https://github.com/qmk/qmk_toolbox/releases/latest)

* Windows用户: `qmk_toolbox.exe` (绿色版) 或 `qmk_toolbox_install.exe` (安装版)
* macOS用户: `QMK.Toolbox.app.zip` (绿色版) or `QMK.Toolbox.pkg` (安装版)

## 建立你的环境

我们为了使QMK环境变得更容易建立已竭尽所能。你只需要准备Linux 或 Unix 环境, 然后让QMK安装剩余部分。

?> 如果你从未使用过Linux/Unix的命令行,有一些你需要学习的基础概念和命令，以下资料将教会您使用QMK环境的必要能力:<br>
[必会Linux命令](https://www.guru99.com/must-know-linux-commands.html)<br>
[一些基本的Unix命令](https://www.tjhsst.edu/~dhyatt/superap/unixcmd.html)

### Windows

你需要安装MSYS2和Git.

* 按照以下安装说明进行操作[MSYS2 主页](https://www.msys2.org)。
* 关闭所有打开的MSYS2终端并打开新的MSYS2 MinGW 64-bit终端。
* 使用以下命令安装Git: `pacman -S git`。

### macOS

你需要安装Homebrew。按照以下说明进行操作 [Homebrew 主页](https://brew.sh)。

在Homebrew安装完成后, 继续 _同步QMK工程_. 这一步你将会通过运行一个脚本安装其他包。

### Linux

你将需要安装Git.你很有可能已经安装,但若你尚未安装,可以使用以下命令进行安装:

* Debian / Ubuntu / Devuan: `apt-get install git`
* Fedora / Red Hat / CentOS: `yum install git`
* Arch: `pacman -S git`

?> 无论你使用哪种平台，Docker都可以是你的选择[点这里进一步了解](getting_started_build_tools.md#docker)

## 同步QMK工程

当你建立Linux/Unix环境后,你就已经可以下载QMK了.下载时我们可以用Git来 "clone" QMK仓库. 打开一个终端或MSYS2 MinGW 窗口，在阅读剩余的指南时请保持窗口打开。在窗口里面运行以下两句命令:

```shell
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
```

?> 如果您已经知道[如何使用GitHub](getting_started_github.md), 我们推荐您创建您自己的分支并克隆。 如果您不知道这是什么, 您完全可以忽略这句无关紧要的话。

QMK附带一个脚本，可帮助您设置剩余的所需内容.您可以通过输入此命令来运行它:

    util/qmk_install.sh

## 测试你的开发环境

现在你的QMK环境已经建立完毕, 你可以为你的键盘创建固件了。开始试着创建键盘的默认固件吧。 你需要使用以下格式的命令创建固件:

    make <keyboard>:default

比如, 制作一个Clueboard 66%的固件，需要用:

    make clueboard/66/rev3:default

当完成后你要看到一些回显，尾部如下:

```
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

# 创建你的布局

现在你可以创建属于你自己的布局了! 请移步 [构建你的第一个固件](newbs_building_firmware.md)来继续。
