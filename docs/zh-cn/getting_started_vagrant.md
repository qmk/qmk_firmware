# Vagrant快速上手指引

<!---
  original document: 0.15.12:docs/getting_started_vagrant.md
  git diff 0.15.12 HEAD -- docs/getting_started_vagrant.md | cat
-->

本工程包含一份 `Vagrantfile`，可以方便地在不更改你系统环境情况下完成新固件文件的构建工作。这同时也保证了在你拉取该工程代码后的编译环境与也使用Vagrantfile的其它人的一致。当你需要其他人协助你排查遇到的问题时会方便很多。

## 需求

本工程中的 `Vagrantfile` 需要安装[Vagrant](https://www.vagrantup.com/)以及可用的虚拟机服务：

* [VirtualBox](https://www.virtualbox.org/) (5.0.12及以后版本)
  * 卖点是'最适用于Vagrant的平台'
* [VMware Workstation](https://www.vmware.com/products/workstation) 及 [Vagrant VMware插件](https://www.vagrantup.com/vmware)
  * （付费购买的）VMware插件需要在经过正版授权的VMware Workstation/Fusion上运行
* [Docker](https://www.docker.com/)

安装了Vagrant之后，在安装合适的虚拟机服务后可能需要重启机器。拉取本工程后在工程目录下执行 'vagrant up' 将启动一个包含了所有本工程所需工具的构建环境（虚拟机或是容器）。最后会有一个vagrant启动提示告知你一切正常就绪，否则你也可以参考一下下面的构建文档。

## 刷写固件

比较“简单”的方案是在你的宿主系统上借助以下工具刷写固件：

* [QMK工具箱](https://github.com/qmk/qmk_toolbox) (推荐)
* [Teensy Loader](https://www.pjrc.com/teensy/loader.html)

如果你希望通过命令行进行编程工作，可以在Vagrantfile中取消掉['modifyvm']的注释以允许USB直通到Linux环境，既可以使用dfu-util/dfu-programmer之类的命令行工具进行编程工作，或是安装Teensy的命令行版本。

## Vagrantfile概览
开发环境被配置为运行QMK Docker镜像 `qmkfm/qmk_cli`，不仅让各系统下的功能预期一致，也是我们CI环境的镜像。

## FAQ

### 为什么我的VirtualBox环境会有问题？
VirtualBox 5的某些版本与工程中Vagrantfile中指定的VirtualBox扩展存在兼容问题。如果你遇到了/vagrant挂载不成功的问题，请升级VirtualBox至5.0.12或更高版本。**或者，可以尝试执行如下命令：**

```console
vagrant plugin install vagrant-vbguest
```

### 如何移除一个现有环境？
不再需要这个环境了是吗？在本工程目录下的任何位置，执行：

```console
vagrant destroy
```

### 如果我是想直接用Docker呢？
想在不使用虚拟机技术的情况下也能使用Vagrant工作流？Vagrangfile已配置为允许绕过运行虚拟机，直接运行容器。通过如下方式执行命令可以强制使用Docker来启动环境：
```console
vagrant up --provider=docker
```

### 如何访问虚拟机环境而非Docker容器？
通过如下方法跳过 `vagrant` 的用户初始化过程以在QMK构建镜像中直接执行：

```console
vagrant ssh -c 'sudo -i'
```
