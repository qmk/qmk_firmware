# 建立你的 QMK 环境

在你创建键盘映射前，你需要安装一些软件来建立你的环境。之后无论你想编译多少固件，这个操作只需执行一次。

## 1. 下载软件

以下是几个你需要入门的软件

### 文本编辑器

你需要一个可以编辑 **纯文本** 文件的程序。你可以 Windows 上使用 Notepad，在 Linux 上使用gedit，两者都是简单又实用的文本编辑工具。在 macOS 上，请小心使用 "TextEdit" 这个默认软件：如果你不在 _Format_ 菜单明确地选择 _Make Plain Text_ 选项的话将不会被保存为纯文本。

你也可以安装一个专用编辑器 [Sublime Text](https://www.sublimetext.com/) 或 [VS Code](https://code.visualstudio.com/)。这大概是跨平台的最好方法了，这些编辑器是专门为了编辑代码设计的。

?> 搞不清用哪种编辑器？Laurence Bradford 写了篇关于编辑器选择的文章 [a great introduction](https://learntocodewith.me/programming/basics/text-editors/)。

### QMK 工具箱(Toolbox)

QMK 工具箱是一个可选用于 Windows 和 macOS 下的图形化工具，它可以对你的定制键盘进行编程和调试。你很有可能会发现它是一个能简单的烧录键盘固件和查看调试信息的神器。

[在这里下载最新发布版本](https://github.com/qmk/qmk_toolbox/releases/latest)

* Windows 用户：`qmk_toolbox.exe` (便携版) 或 `qmk_toolbox_install.exe` (安装版)
* macOS 用户：`QMK.Toolbox.app.zip` (便携版) 或 `QMK.Toolbox.pkg` (安装版)

### 类 Unix 环境

Linux 和 macOS 附带了可以执行的 unix shell。您只需要设置您的构建环境。

在 Windows 上，您需要安装 MSYS2 或 WSL 并使用这些环境。下面提供了设置 MSYS2 的说明。

## 2. 准备你的构建环境 :id=set-up-your-environment

我们为了使 QMK 环境变得更容易建立已竭尽所能。你只需要准备 Linux 或 Unix 环境，之后 QMK 会安装余下部分。

?> 如果你从未使用过 Linux/Unix 命令行，那么你有些基础概念和命令需要学习，以下资料将教会您使用 QMK 环境的必要能力：<br>
[Must Know Linux Commands](https://www.guru99.com/must-know-linux-commands.html)<br>
[Some Basic Unix Commands](https://www.tjhsst.edu/~dhyatt/superap/unixcmd.html)

### Windows

你需要安装 MSYS2, Git 以及 QMK 命令行工具(CLI).

按照以下安装说明进行操作 [MSYS2 主页](http://www.msys2.org)。
关闭所有打开的 MSYS2 终端并打开新的 MinGW 64 位终端。
**注意: 安装完打开的终端和之前的 MSYS 终端*不一样***

然后运行以下命令

    pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-python3-pip
    python3 -m pip install qmk

### macOS

你需要安装Homebrew。按照以下说明进行操作 [Homebrew 主页](https://brew.sh)。

Homebrew 安装完成后，运行以下命令：

    brew install qmk/qmk/qmk

### Linux

你需要安装 Git 和 Python。你很有可能已经安装，但若你尚未安装，则可以使用以下命令进行安装:

* Debian / Ubuntu / Devuan: `sudo apt install -y git python3-pip`
* Fedora / Red Hat / CentOS: `sudo yum -y install git python3-pip`
* Arch / Manjaro: `sudo pacman --needed --noconfirm -S git python-pip libffi`
* Void: `sudo xbps-install -y git python3-pip`
* Solus: `sudo eopkg -y install git python3`
* Sabayon: `sudo equo install dev-vcs/git dev-python/pip`

安装全局 CLI 来引导你的系统。

`python3 -m pip install --user qmk` (在 Arch 发行版下你也使用来自 `AUR` 的 `qmk` (**note**: 由一名社区成员维护): `yay -S qmk`)

### FreeBSD

你需要安装 Git 和 Python。你很有可能已经安装，但若你尚未安装，则可以使用以下命令进行安装:

    pkg install git python3

确保已将 `$HOME/.local/bin` 其添加到 `$PATH` 中，以便可以直接使用 Python 安装的软件包(packages)。

安装完成后，你可以安装QMK CLI：

    python3 -m pip install --user qmk

## 3. 运行 `qmk setup` :id=set-up-qmk

在 QMK 安装完成后，你可以通过这个命令进行启动：

    qmk setup

大部分情况下所有的提示你都要回答 Yes 。

?>**Debian, Ubuntu及其衍生系统的注意事项**：
很有可能会类似这样的错误：`bash: qmk: command not found`.
这是由于 Debian 在其 Bash 4.4 版本引入了一个 [bug](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=839155), 从环境变量移除了 `$HOME/.local/bin`。这个 bug 后来在 Debian 和 Ubuntu 上修复了。
遗憾的是，Ubuntu 又引入了这个 bug 而且 [尚未修复](https://bugs.launchpad.net/ubuntu/+source/bash/+bug/1588562)。
幸运的是，修复很容易。以你的用户身份运行以下命令：``echo 'PATH="$HOME/.local/bin:$PATH"' >> $HOME/.bashrc && source $HOME/.bashrc``

?>**关于 FreeBSD 的注意事项**:
建议首先以 `非root` 用户身份运行 `qmk setup` 命令，but this will likely identify packages that need to be installed to your base system using `pkg`。
但是，当以非特权用户身份运行时，安装可能会失败。
手动安装基本依赖项，请用 `root` 用户或着`sudo` 没了来运行 `./util/qmk_install.sh`。完成后，再次 `qmk setup` 以完成设置和检查

?> 如果你已经知道 [如何使用GitHub](getting_started_github.md)，我们推荐创建自己的分支并使用 `qmk setup <github_username>/qmk_firmware` 来克隆你自己的分叉。 如果您不知道这是什么，您完全可以忽略。

## 4. 测试你的开发环境

现在你的 QMK 环境已经建立完毕，你可以为你的键盘构建固件了。开始试着创建键盘的默认固件吧。 你需要使用以下格式的命令创建固件:

    qmk compile -kb <keyboard> -km default

比如，制作一个 66% Clueboard 的固件，需要用:

    qmk compile -kb clueboard/66/rev3 -km default

当输入完成后你会看到到许多输出，输出的最后大概是这样的:

```
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

## 5. 配置你的构建环境（可选）
您可以配置你的默认构建环境来减少使用 QMK 的繁琐工作。让我们现在就开始吧！

大多数的 QMK 新手只有一个键盘。你可以使用 `qmk config` 命令将该键盘设置为默认键盘。例如，将默认键盘设置为 `clueboard/66/rev4`：

    qmk config user.keyboard=clueboard/66/rev4

您还可以设置默认键盘映射名称。大多数人在这里使用他们的 GitHub 用户名，我们建议你也这样做。

    qmk config user.keymap=<github_username>

之后，您可以不理会这些参数并按如下命令编译你的键盘：

    qmk compile

## 创建你的键盘映射

现在你可以创建属于你自己的映射了! 请移步 [构建你的第一个固件](zh-cn/newbs_building_firmware.md)来继续。
