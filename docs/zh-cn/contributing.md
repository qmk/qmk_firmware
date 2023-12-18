# 如何做贡献

<!---
  original document: 0.15.12:docs/contributing.md
  git diff 0.15.12 HEAD -- docs/contributing.md | cat
-->

👍🎉 首先感谢各位百忙之中抽空阅读本文档，并为我们无私奉献。给您点赞啦！ 🎉👍

第三方的帮助让QMK获得了成长与进步。我们希望提供一套对贡献者和维护者都感到简便实用的PR（pull request）及贡献流程，因此我们整理出了一些准则，以免你的PR在被接纳前需要大改一番。

* [项目概况](#project-overview)
* [代码规范](#coding-conventions)
* [一般教程](#general-guidelines)
* [行为守则对于我来说有何意义？](#what-does-the-code-of-conduct-mean-for-me)

## 这文章巨长无比不想读啊! 我就想问个问题而已!

您要是有关于QMK的问题，请在[OLKB Subreddit](https://reddit.com/r/olkb)或者是[Discord](https://discord.gg/Uq7gcHh)上进行提问。

请记住:

* 你的问题也许要过几个小时才会有人回复，请耐心一些。
* 参与到QMK中的成员都是在无偿地贡献着自己的时间和精力，我们没有受雇于开发QMK或是专职回答你的疑问。
* 您可以看看下面的教程，可以让您的问题浅显易懂，更容易回答：
  * https://opensource.com/life/16/10/how-ask-technical-questions
  * http://www.catb.org/esr/faqs/smart-questions.html

# 项目概况 :id=project-overview

QMK很大一部分是C语言编写的，小部分特性是C++的。QMK的设计目标是在键盘上的嵌入式处理器中工作，如AVR([LUFA](https://www.fourwalledcubicle.com/LUFA.php))和ARM ([ChibiOS](https://www.chibios.org))。如果您对Arduino很熟悉的话，会发现优缺点也基本是相似的。但无论你之前是否有Arduino使用经验，都不会影响你参与到QMK贡献中来。

<!-- FIXME: 这里应当放些C语言的学习资源。 -->

# 我到哪里寻求帮助？

您要是有问题的话可以 [提出一个issue](https://github.com/qmk/qmk_firmware/issues) 或 [在Discord上交流一下](https://discord.gg/Uq7gcHh).

# 我怎样才能做出贡献？

您以前是否没有参与贡献过开源社区，而又想知道如何对QMK提供帮助？这里有一份快速指引！
*译注：对于没有基本编程经验的人，请谨慎考虑这套操作流程，可参考，照着做很容易出问题，社区的语言障碍也会阻碍你对这些步骤的细节进行咨询*

0. 先注册一个 [GitHub](https://github.com) 账户。
1. 完整整理出来你要贡献的键映射，或是 [找一个你想解决的问题](https://github.com/qmk/qmk_firmware/issues)，或者 [找一个你想添加的特性](https://github.com/qmk/qmk_firmware/issues?q=is%3Aopen+is%3Aissue+label%3Afeature)。
2. 把关联着问题的仓库fork到你的仓库。这样在`你的GitHub用户名/qmk_firmware` 下就有一个副本啦。
3. 使用 `git clone https://github.com/你的GitHub用户名/仓库名.git` 命令把仓库同步到你的电脑中。
4. 您要是想开发一个新特性的话可以先创建一个issue和QMK的维护者讨论一下您要做什么。
5. 使用 `git checkout -b 此处写分支名字（别用汉字）` 命令来创建一个新分支（branch）用于开发。
6. 对要解决的问题或要添加的特性进行适当的更改。
7. 使用 `git add 把改变的文件的目录写这里` 可以添加改变的文件内容到git用于管理工程状态的索引（快照）里。
8. 使用 `git commit -m "这里写修改的相关信息"` 来描述你做出了什么修改。
9. 使用 `git push origin 此处写分支名字`来把你的更改同步到GitHub库里（反正不是打篮球那个库里）。
10. 提交一个[QMK 固件的pull request](https://github.com/qmk/qmk_firmware/pull/new/master)。
11. 给你的pull request拟一个标题，包括简短的描述和问题或错误代码。比如, 你可以起一个这样的"Added more log outputting to resolve #4352"（最好用英语，毕竟QMK的维护团队成员都是英语语系，有可能会看不懂中文）。
12. 在描述（description）里面写你做了哪些更改，你的代码里还存在什么问题, 或者你想对QMK维护着询问的问题。你的pull request有点小问题无伤大雅（没有完美的pull request）, QMK维护团队会尽力帮您改进的！
13. 维护人员审查代码可能需要一些时间。
14. 维护人员会通知您要更改什么地方，然后您就按照建议改一改。
15. 你的pull request合并成功了，恭喜！

# 代码规范 :id=coding-conventions

我们的编码风格很容易掌握，如果你有C语言或Python编码经验，跟随我们的编码风格不会有什么困难。

* [编码规范 - C](zh-cn/coding_conventions_c.md)
* [编码规范 - Python](zh-cn/coding_conventions_python.md)

# 基本准则 :id=general-guidelines

在QMK中存在多种类型的修改需求，因此也会有审查严格性上的差异。请在做出任何修改时留意，你的改动隶属于什么类型。

* 将PR（pull request）分成一个个的逻辑单元。 比如，不要一次将两个新特性PR出去。要添加的特性排好队，一个一个来。
* 提交之前使用 `git diff --check` 做以下检查，不要提交多余的空格
* 确定你的代码能通过编译
  * 键映射: 确定`make keyboard:your_new_keymap` 不返回错误
  * 键盘: 确定 `make keyboard:all` 不返回错误
  * 核心代码: 确定 `make all` 不返回错误
* 提交的信息尽量明确。第一行写点简短介绍(每行不多于70个英文字母), 第二行空着,第三行和后面就要写些必要的细节了。最好用英文写，比如:

```
Adjust the fronzlebop for the kerpleplork

The kerpleplork was intermittently failing with error code 23. The root cause was the fronzlebop setting, which causes the kerpleplork to activate every N iterations.

Limited experimentation on the devices I have available shows that 7 is high enough to avoid confusing the kerpleplork, but I'd like to get some feedback from people with ARM devices to be sure.
```

!> **特别留意：** 若你要对其它QMK使用者提交的代码进行功能修改或尝试修复bug，例如非默认的键映射、用户空间和配列部分，须在PR中标记出代码的原始提交者。很多QMK使用者都会对自己提交的代码在不知晓的情况下产生了改动感到困惑和沮丧，无论他的Git及Github经验丰富与否。

## 文档

对文档进行修正是最简单的参与贡献的一个办法，找到错误放置的文档或是修复不完备的部分很容易！我们也急需能修订文档的贡献者参与进来，所以如果你具备这样的能力但不清楚如何开始，请[看这里](#我怎样才能做出贡献？)！

文档位于 `qmk_firmware/docs` 目录下，如果你习惯于在web页面中完成工作目标，可以在 https://docs.qmk.fm/ 各文档页面下方点击“Edit this page”在线进行编辑。

在文档中附代码案例时, 先观察文档其他地方的命名规范。比如, 将enum类型的定义命名为 `my_layers` 或 `my_keycodes` 的形式可以保持前后一致性：

```c
enum my_layers {
  _FIRST_LAYER,
  _SECOND_LAYER
};

enum my_keycodes {
  FIRST_LAYER = SAFE_RANGE,
  SECOND_LAYER
};
```

### 预览文档 :id=previewing-the-documentation

在发起pull request前，请通过文档预览来检查你的本地更改。可以在 `qmk_firmware/` 目录下执行以下命令来配置文档开发环境：

    qmk docs

或者，如果你有安装Python 3，可以尝试：

    python3 -m http.server 8936 --directory docs

然后在本地浏览器打开 `http://localhost:8936/`.

## 键映射

大多数QMK新手都从创建一个自己的键映射
开始。我们尽力保证键映射规范宽松 (毕竟键映射体现的是个人喜好) 不过我们仍要求须遵守以下准则，以便他人更好地发现并理解你的键映射代码。

* 使用这份 [模板](zh-cn/documentation_templates.md) 写一份 `readme.md`。
* 所有的键映射PR都会被压缩处理（squashed，参见[Github文档](https://docs.github.com/cn/github/collaborating-with-pull-requests/incorporating-changes-from-a-pull-request/about-pull-request-merges)），如果你对commit被压缩很介意，请自行处理
* 不要把新特性和键映射放在一个PR中。先提交新特性，再通过PR提交键映射
* 键映射文件夹中不要提交 `Makefile` 文件（已不再使用）
* 更新头文件中的copyrights信息(看 `%YOUR_NAME%` 部分)

## 键盘

QMK的最终归宿是键盘。有些键盘是社区维护的，有一些是制作这些键盘的人维护的。`readme.md` 会告诉你是谁维护了这个键盘，如果你对某个键盘有疑问，可以 [创建一个Issue](https://github.com/qmk/qmk_firmware/issues) 来问一问维护者。

我们建议你按下面的来操作:

* 基于[模板](zh-cn/documentation_templates.md)编写 `readme.md`。
* commit数量尽量合理，否则你的PR可能会被我们压缩。
* 不要把新特性和新键盘定义放在一个PR中。先提交新特性，再通过PR提交新键盘定义
* 用最近一级的父文件夹的名字命名 `.c`/`.h` 文件, 比如 `/keyboards/<kb1>/<kb2>/<kb2>.[ch]`
* 键盘文件夹就不要放`Makefile`了，这个操作都过时啦
* 更新文件头部的copyrights(看`%YOUR_NAME%`那)

## Quantum/TMK 核心

在你投入大量精力到新功能开发中之前，请先确保使用了最佳的实现方案。通过阅读[了解QMK](zh-cn/understanding_qmk.md)可以获得对QMK的基本认知，这个文档将带你领略QMK的程序流程，然后你可以和维护团队探讨一下实现你想法的最佳方法的思路，以下渠道都可以：

* [在Discord中交流](https://discord.gg/Uq7gcHh)
* [建立一个Issue](https://github.com/qmk/qmk_firmware/issues/new)

新特性和BUG的修复影响所有键盘，开发组也在翻修QMK。所以，在实施重大改动之前一定要讨论一下。如果你在没有事先与维护团队沟通的情况下提交了一个PR，而且你的选择与维护团队的计划方向不符，那你可能要面临大改了。

修复BUG或者开发新特性之前看看这个：

* **默认不启用** - QMK运行的芯片多数内存有限，首要考虑的应是已有的键映射不要被破坏，因此你的功能应当是“可以**启用**”的，而不是“可以禁用”的。如果你觉得该特性应该默认开启或者你能帮助缩减代码，请先和我们沟通一下。
* **提交之前在本地编译** - 这个简直就是家喻户晓了，但是也确实需要编译啊！ 在你发起PR前，请确保任何改动都通过了编译验证。
* **注意版本和芯片平台兼容性** - 有那么几个键盘有支持不同配置甚至是不同芯片的版本。请确保你开发的特性同时支持AVR和ARM两个平台，或者在不支持的平台自动禁用。
* **解释你的新特性** - 在`docs/`写个文档, 你可以创建新文档或者写到现有文档中。如果你不把它记录下来，其他人就无法从你的努力中获益。

也可以看看以下建议：

* commit数量尽量合理，否则你的PR可能会被我们压缩。
* 不要把新键盘定义或新键映射与关键改动放在一个PR中。先提交关键改动。
* 给你的特性编写[单元测试](zh-cn/unit_testing.md)。
* 你编辑的文件风格要一致，如果风格不明确或者是混搭风的，请先阅读上方的[代码规范](#coding-conventions)。

## 重构

为了保持QMK脉络清晰，QMK的深度重构工作已在规划中，并会通过合作者进行相应的修改。如果你有重构的思路或建议请[创建一个issue](https://github.com/qmk/qmk_firmware/issues), 我们很乐意讨论一下QMK可以如何改进。

# 行为守则对于我来说有何意义？ :id=what-does-the-code-of-conduct-mean-for-me

我们的[行为守则](https://qmk.fm/coc/) 指出您有责任尊重并礼貌地对待项目中的每个人，无论他们的身份如何。如果你是我们行为守则所描述的不当行为的受害者，我们将站在你这边，尽最大努力对施暴者进行谴责。
