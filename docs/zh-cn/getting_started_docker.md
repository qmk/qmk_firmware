# Docker快速上手指引

<!---
  original document: 0.15.12:docs/getting_started_docker.md
  git diff 0.15.12 HEAD -- docs/getting_started_docker.md | cat
-->

本工程包含了一套Docker工作流，可以方便地在不更改你主系统环境情况下完成新固件文件的构建工作。这同时也保证了在你拉取该工程代码后的编译环境与其他人以及QMK开发者的一致。当你需要其他人协助你排查遇到的问题时会方便很多。

## 需求

核心需求是一个已安装的可用的 `docker` 或 `podman`。
* [Docker CE](https://docs.docker.com/install/#supported-platforms)
* [Podman](https://podman.io/getting-started/installation)

## 用法

拉取QMK仓库到本地（包括所有的子模块）：

```bash
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
```

执行以下命令构建键映射：
```bash
util/docker_build.sh <keyboard>:<keymap>
# 例: util/docker_build.sh planck/rev6:default
```

如上可以构建所需的键盘/键映射，可用于刷写的 `.hex` 及 `.bin` 输出文件存放在QMK目录下。如果省略了 `:keymap` 参数，所有的键映射都会被编译。留意编译参数格式与 `make` 构建时的一致。

同时也支持直接从Docker中编译和刷写，只需要指定 `target`：

```bash
util/docker_build.sh keyboard:keymap:target
# 例: util/docker_build.sh planck/rev6:default:flash
```

可以不带参数地执行该脚本，其会依次要求你输入这些参数，也许你会觉得这样更好用：

```bash
util/docker_build.sh
# 从输入中读取参数 (留空则构建所有的键盘/键映射)
```

可以通过设置环境变量 `RUNTIME` 为想使用的容器运行时的名称或路径来指定运行时，默认其会检测并自动选取docker或podman，相比于podman会更倾向于用docker。

```bash
RUNTIME="podman" util/docker_build.sh keyboard:keymap:target
```

## FAQ

### 为什么我无法在我的Windows/macOS下刷写固件

在Windows及macOS上，需要有[Docker Machine](http://gw.tnode.com/docker/docker-machine-with-usb-support-on-windows-macos/)运行着，配置过程很繁琐，因此我们没有做推荐。请考虑使用[QMK工具箱](https://github.com/qmk/qmk_toolbox)。

!> Windows下需要启用[Hyper-V](https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/quick-start/enable-hyper-v)才能运行Docker，这也意味着它无法运行在没有Hyper-V的Windows版本下，如Windows 7，Windows 8及**Windows 10家庭版**。
