# 在Eclipse中设置QMK开发环境

<!---
  original document: 0.15.16:docs/other_eclipse.md 
  git diff 0.15.16 HEAD -- docs/other_eclipse.md  | cat
-->


[Eclipse][1]是一款广泛用于Java开发的[集成开发环境](https://en.wikipedia.org/wiki/Integrated_development_environment)（IDE），但有着强大的插件体系允许自定义开发其它语言及用途。

相对于使用普通的文本编辑器，使用形如Eclipse这样的IDE有着诸多好处，例如：
* 智能代码补全
* 快速代码跳转
* 重构工具
* 构建自动化（无需使用命令行）
* 图形化交互的GIT
* 静态代码分析
* 以及大量其它工具，如调试器，代码格式化，显示调用链等。

本文专注于阐述如何将Eclipse配置为AVR软件开发环境，并用于基于QMK代码的开发工作。

注意，在本文编写时，仅在Ubuntu 16.04环境中进行过验证。

# 需求
## 构建环境
在开始之前，你需要确保遵循了新手教程中的[新手指引](zh-cn/newbs_getting_started.md)一节。通常，此时你应该具备了[通过 `qmk complile` 命令](zh-cn/newbs_building_firmware.md#build-your-firmware)构建固件文件的能力。

## Java
Eclipse为Java程序，因此需要安装Java 8或更高版本才能运行。你可以选择JRE或JDK，后者在进行Java开发时需要用到。

# 安装Eclipse及插件
Eclipse有[多种可选安装方式](https://www.eclipse.org/downloads/eclipse-packages/)，取决于你的使用目标。目前没有完备的AVR开发栈安装包，所以我们需要从Eclipse CDT（C/C++ 开发工具环境）开始并安装对应的插件。

## 下载安装Eclipse CDT
如果系统中已安装了Eclipse CDT，可以跳过本步骤。同时，为了确保版本支持情况，我们推荐保持其更新至最新版。

如果你已安装了Eclipse包，通常也可以[在上面再安装CDT插件](https://eclipse.org/cdt/downloads.php)。但是可能更好的方案是重新全新安装一下，以确保环境轻量，以及防止已安装的工具对后续的工程开发工作产生干扰。

安装很简单：遵循[Eclipse安装5步走](https://eclipse.org/downloads/eclipse-packages/?show_instructions=TRUE)，并在第三步选择 **用于C/C++开发者的Eclipse IDE（Eclipse IDE for C/C++ Developers）**。

此外，也可以选择直接[下载 用于C/C++开发者的Eclipse IDE](https://www.eclipse.org/downloads/eclipse-packages/)（[最新版直达链接](https://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers/neonr)）并解压至任意目录下（会生成 `eclipse` 目录）。

## 首次运行
在安装完毕后，点击<kbd>运行</kbd>按钮。（如果是手动解压的，请在安装目录下双击 `eclipse` 可执行程序

在提示你选择工作区目录时，选择一个可用于存储Eclipse元数据及工程的目录。**不要选择 `qmk_firmware` 目录**，这是你的项目目录。可以使用其父目录，或其它（最好是空）目录（默认目标目录如果未作他用亦可使用）。

启动后，点击右上角的<kbd>工作台（Workbench）</kbd>按钮切换到工作台视图（启动时的欢迎页最下方有个确认框可以在下次启动时不再展示欢迎页）。

## 安装必要的插件
注意：无需在每个插件安装完成时重启Eclipse，全部安装完毕后重启一次即可。

### [AVR插件](https://avr-eclipse.sourceforge.net/)
这是最重要的一个插件，可以帮助Eclipse理解AVR下的C语言代码。参照执行[更新网址使用指引](https://avr-eclipse.sourceforge.net/wiki/index.php/Plugin_Download#Update_Site)，并允许那些未签名内容产生的警告。

### [ANSI Escape in Console（命令行下的ANSI转义符）](https://marketplace.eclipse.org/content/ansi-escape-console)
该插件可以允许QMK makefile产生的具有颜色标记的构建输出信息能够正确显示。

1. 打开<kbd>帮助</kbd> > <kbd>Eclipse插件市场…</kbd>
2. 搜索_ANSI Escape in Console_
3. 点击插件的<samp>安装</samp>按钮
4. 跟随安装指引并再次允许那些未签名的内容产生的警告。

在插件皆安装完毕后，依照提示重启Eclipse。

# 配置Eclipse QMK环境
## 导入工程
1. 点击<kbd>文件</kbd> > <kbd>新建</kbd> > <kbd>现有的Makefile工程代码</kbd>
2. 在之后这一页中：
  * 选择仓库所克隆到的目录位置作为 _现有代码位置_；
  * （可选地）指定一个不同的工程名，如 _QMK_ 或 _Quantum_ ；
  * 选择 _AVR-GCC Toolchain_;
  * 其它选项保留不动，点击<kbd>完成</kbd>

  ![Importing QMK in Eclipse](https://i.imgur.com/oHYR1yW.png)

3. 工程即完成加载及分析，其下的文件可以方便地在左侧的 _Project Explorer_ 中查看了。

¹ 导入工程时若自定义名称有时会遇到些问题，如果行不通，保留默认的工程名（即目录名，通常是 `qmk_firmware`）再试一次。

## 构建你的键盘

我们将默认构建目标从 `all` 调整到我们期望构建的键盘及键映射组合上，即 `kinesis/kint36:stapelberg`。此时，形如清理、构建等工程级别的操作可以很快地执行完毕，而不至于耗费大量时间且导致Eclipse卡住。

1. 焦点置于工程下的任一编辑器tab中
2. 打开`工程` > `属性`窗口， 选择 `C/C++构建` 菜单项并切至 `Behavior` 标签。
3. 将 `Make build target`选项中的全量构建 `all` 改为 `kinesis/kint41:stapelberg`。
4. 点击 `工程` > `清理...` 以确认配置正确。

  [1]: https://en.wikipedia.org/wiki/Eclipse_(software)
