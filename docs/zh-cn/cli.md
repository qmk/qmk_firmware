# QMK CLI :id=qmk-cli

<!---
  original document: 0.15.12:docs/cli.md
  git diff 0.15.12 HEAD -- docs/cli.md | cat
-->

## 总览 :id=overview

QMK CLI可以让构建QMK键盘的过程更轻松一些，我们已提供的一批指令可用于简化及流式化地处理一些常见工作，如获取并编译QMK固件，创建新的键映射等。

### 依赖项 :id=requirements

QMK依赖Python 3.6或更高版本。我们已经尽力缩减依赖项，但在[`requirements.txt`](https://github.com/qmk/qmk_firmware/blob/master/requirements.txt)中的依赖项是需安装的包。在安装QMK CLI时这些依赖项也会自动完成安装。

### 通过 Homebrew 安装(macOS 及部分 Linux) :id=install-using-homebrew

若已安装[Homebrew](https://brew.sh)，可以按如下方法安装QMK:

```
brew install qmk/qmk/qmk
export QMK_HOME='~/qmk_firmware' # 可选，指定 `qmk_firmware` 的路径
qmk setup  # 拉取 `qmk/qmk_firmware` 并选择性地配置构建环境
```

### 通过 pip 安装 :id=install-using-easy_install-or-pip

未在以上列出的操作系统可以手动安装QMK。首先确认已安装Python 3.6（或更高版本）及 pip，然后通过如下指令安装QMK：

```
python3 -m pip install qmk
export QMK_HOME='~/qmk_firmware' # 可选，指定 `qmk_firmware` 的路径
qmk setup  # 拉取 `qmk/qmk_firmware` 并选择性地配置构建环境
```

### 其它操作系统的安装包 :id=packaging-for-other-operating-systems

我们正在寻求可以制作维护更多操作系统下可用的 `qmk` 安装包的开发者，若您愿意为您的操作系统制作安装包，请遵循如下指引：

* 当该系统下的最佳实践与本指引冲突时，请遵循系统的最佳实践方案
    * 但请在注释中列明此处违反这份指引的原因
* 在 virtualenv 下安装
* 指引用户去设置 `QMK_HOME` 环境变量，使得固件源文件拉取路径不再是默认的 `~/qmk_firmware`
