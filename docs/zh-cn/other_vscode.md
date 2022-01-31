#  在Visual Studio Code中设置QMK开发环境

<!---
  original document: 0.15.12:docs/other_vscode.md 
  git diff 0.15.12 HEAD -- docs/other_vscode.md  | cat
-->

[Visual Studio Code](https://code.visualstudio.com/) (VS Code) 是一款支援非常多种不同编程语言的开源编辑器。

相比于使用简陋的文本编辑器，形如VS Code这样的多功能编辑器有诸多优势，比如：
* 智能的代码补全
* 便捷的代码导航
* 重构工具
* 自动化构建支持（不再需要命令行操作）
* 图形化的GIT界面
* 调试器、代码格式化、显示调用层级等多种工具

本章节旨在阐述如何配置VS Code以在其上进行QMK固件开发。

这份指引提供了在Windows及Ubuntu 18.04下所有的配置方法。

# 配置VS Code
一开始，你需要首先确认所有的构建工具已经安装配置完成，且QMK Firmware仓库已拷贝至本地。前往参阅[新人指引](zh-cn/newbs_getting_started.md)确保已完成初始配置。

## Windows

### 依赖项

* [Git for Windows](https://git-scm.com/download/win) (该链接会自动提示你保存或运行安装包)

  1. 除 `Git LFS (Large File Support)（大文件支援）` 及 `Check daily for Git for Windows updates（每天检查更新）` 外取消所有可选项。
  2. 将默认编辑器改为 `Use Visual Studio Code as Git's default editor（将VS Code作为默认编辑器）`
  3. 选择 `Use Git from Git Bash only（仅在Git Bash中使用Git）`，这是应使用的方案。
  4. 在 `Choosing HTTPS transport backend（选择HTTPS传输服务）` 选项上，皆可。
  5. 选择 `Checkout as-is, commit Unix-style line endings（检出不作更改，提交时使用Unix风格换行符）`，QMK仓库使用的是Unix style提交。
  6. 在额外选项页，保持默认选择即可。

  该软件是VS Code支持Git的所需项目，是有可能不去使用它，但直接用它会省很多事。

* [Git Credential Manager for Windows（Windows版Git凭据管理器）](https://github.com/Microsoft/Git-Credential-Manager-for-Windows/releases) （可选）

  该软件提供了更好的git 凭据加密存储、多因素身份认证（MFA）及私有访问token生成器。

  这个不是严格必须的，但我们依旧推荐使用。


### 安装VS Code

1. 到[VS Code](https://code.visualstudio.com/)下载安装包
2. 运行安装包

很简单的操作。然而，仍有一些配置我们需要确保是设置正确的。

### VS Code设置

首先来配置IntelliSense，虽不是严格必要的，但能让你后续使用便捷**很多**。首先，在QMK Firmware目录下创建文件 `.vscode/c_cpp_properties.json`，之后的操作可以手动完成，但我已经完成了大部分。

获取[这份文件](https://gist.github.com/drashna/48e2c49ce877be592a1650f91f8473e8)，如果你的MSYS2没有安装在默认路径，或在用WSL/LxSS，你可能需要做一下编辑修改。

在保存妥当后，如果你有已打开的VS Code，你需要reload一下。

?> 在 `.vscode` 目录下你应该还能看到 `extensions.json` 和 `settings.json` 文件。

现在，我们配置MSYS2作为VSCode的集成终端。这么做有很多好处，最主要的是可以通过按住control点击错误消息直接跳转到文件，调试起来会简单得多，另外的好处是，你不用在窗口间切换。

1. 点击 <kbd><kbd>文件</kbd> > <kbd>首选项 ></kbd> > <kbd>设置</kbd> </kbd>
2. 点击上方右侧的 <kbd>{}</kbd> 按钮，打开 `settings.json` 文件。
3. 将文件改为：

   ```json
   {
        "terminal.integrated.profiles.windows": {
            "QMK_MSYS": {
                "path": "C:/QMK_MSYS/usr/bin/bash.exe",
                "env": {
                    "MSYSTEM": "MINGW64",
                    "CHERE_INVOKING": "1"
                },
                "args": ["--login"]
            }
        },

        "terminal.integrated.cursorStyle": "line"
    }
    ```

   如果该文件内已经有一些配置项，将上面的内容粘贴在最外层的花括号内，并用一个逗号将新旧内容分隔开。

?> 如果你的MSYS2安装在不同的目录下，你需要将 `terminal.integrated.shell.windows` 更改为你系统中正确的目录。

4. 点击Ctrl-<code>&#96;</code> (Grave) 或在 <kbd><kbd>视图</kbd> > <kbd>终端</kbd></kbd> 可以打开终端界面 (`workbench.action.terminal.toggleTerminal` 命令)。如果没有终端它会自动打开一个。

   终端应启动于工程目录中（即 `qmk_firmware` 目录），之后你可以构建键盘了。


## 其它系统

1. 到[VS Code](https://code.visualstudio.com/)下载安装包
2. 运行安装包
3. 搞定

是的，确实是搞定了。安装的时候所有所需的路径配置都会被包含进来，在检查当前工程文件并进行IntelliSense解析上表现也会更好。

## 插件

有一些你可能感兴趣的扩展可以安装：<!-- 老外自己也分不清plugin和extension啊-_-||| -->

* [Git Extension Pack](https://marketplace.visualstudio.com/items?itemName=donjayamanne.git-extension-pack) - 提供了一系列的Git工具可以让你在QMK Firmware中使用Git便捷一些。
* [EditorConfig for VS Code](https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig) - _[可选]_ -  可以让你的代码更符合QMK规范。
* [Bracket Pair Colorizer 2](https://marketplace.visualstudio.com/items?itemName=CoenraadS.bracket-pair-colorizer-2) - _[可选]_ - 可以给大括号着色，可以更好地阅读嵌套代码。
* [GitHub Markdown Preview](https://marketplace.visualstudio.com/items?itemName=bierner.github-markdown-preview) - _[可选]_ - 使得VS Code下的markdown预览更符合Github的效果。
* [VS Live Share Extension Pack](https://marketplace.visualstudio.com/items?itemName=MS-vsliveshare.vsliveshare-pack) - _[可选]_ - 这个扩展允许他人访问你的工作区（或反之）进行协作，在你遇到问题需要他人帮助时挺有用。
* [VIM Keymap](https://marketplace.visualstudio.com/items?itemName=GiuseppeCesarano.vim-keymap) - _[可选]_ - 为那些更喜欢VIM风格的按键操作的人所准备。这样的扩展还有挺多。

安装扩展后需要重启VS Code。

# 配置VS Code下的QMK
1. 点击 <kbd><kbd>文件</kbd> > <kbd>打开目录</kbd></kbd>
2. 打开你从Github克隆的QMK固件仓库所在目录。
3. 点击 <kbd><kbd>文件</kbd> > <kbd>保存工作区为...</kbd></kbd>

此时你已完成了在VS Code下编写QMK固件的准备工作。
