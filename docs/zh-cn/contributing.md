# 如何做贡献

👍🎉 首先感谢各位百忙之中抽空阅读本文档，并为我们无私奉献。给您点赞啦！ 🎉👍

第三方的帮助让Q酱成长了许多呢，Q酱也从你们那学到了不少新东西。Q酱希望每一个想帮助我的人都能很方便的做出有用的贡献。在这里我给摩拳擦掌的你们写了一点引导，让你们的代码在不对我做重大改动的情况下都能成功的被采纳哦。

* [项目概况](#项目概况)
* [代码规范](#代码规范)
* [一般教程](#一般教程)
* [行为守则对于我来说有何意义?](#行为守则对于我来说有何意义?)

## 这文章巨长无比不想读啊! 我就想问个问题而已!

您要是想问关于Q酱的问题的话可以在[OLKB Subreddit](https://reddit.com/r/olkb)或者是[Discord](https://discord.gg/Uq7gcHh)随意问。

请记住:

* 维护Q酱的小可爱有的时候可能会有点忙，不能及时回答您的问题，耐心等等，他们都是很nice的人呀。
* 维护Q酱的人都是很无私的善良的人。无论是贡献代码还是回答问题，都是义务的。有时见到他们努力回答各种问题，解决各种BUG，Q酱也是很心疼的。
* 您可以看看下面的教程，可以让您的问题浅显易懂，更容易回答：
  * https://opensource.com/life/16/10/how-ask-technical-questions
  * http://www.catb.org/esr/faqs/smart-questions.html

# 项目概况

Q酱很大一部分是用C语言组成的，不过有一小部分特性是C++的。怎么说呢，都是我的一部分，两个我都爱。Q酱一般是在键盘上的嵌入式处理器那里工作的，尤其与AVR([LUFA](http://www.fourwalledcubicle.com/LUFA.php))和ARM ([ChibiOS](http://www.chibios.com))两小哥哥搭配，干活不累，嘻嘻。如果您精通Arduino的话您会发现很多熟悉的概念，但也有点不爽，因为您以前的经验可能没法用来帮助Q酱。

<!-- 需要修正: 这里放些学习C语言的资源。另外感谢修正的小可爱。谢谢您了。-->

# Q酱，我在哪能帮助你嘞?

您要是有问题的话可以 [提出一个issue](https://github.com/qmk/qmk_firmware/issues) 或 [在Discord上交流一下](https://discord.gg/Uq7gcHh).

# Q酱，我如何帮助你?

您以前是否没为开源贡献过代码，而又想知道帮助Q酱是怎么一回事? 稍安勿躁，咱给您总结一下！

0. 先注册一个 [GitHub](https://github.com) 账户。
1. 做好一个你要贡献的布局，那就要 [找一个你想解决的问题](https://github.com/qmk/qmk_firmware/issues)，或者 [找一个你想添加的特性](https://github.com/qmk/qmk_firmware/issues?q=is%3Aopen+is%3Aissue+label%3Afeature)。
2. 把关联着问题的仓库分叉（fork）到你的仓库。这样你在`你的GitHub用户名/qmk_firmware`就有一个仓库备份啦。
3. 使用 `git clone https://github.com/此处添GitHub用户名/此处添仓库名.git`这个命令把仓库同步到你的电脑中。
4. 您要是想开发一个新特性的话可以先创建一个issue和Q酱的维护者讨论一下您要做什么。
5. 使用`git checkout -b 此处写分支名字（别用汉字）`命令来创建一个分支（branch）用于开发。
6. 对要解决的问题或要添加的特性进行适当的更改。
7. 使用 `git add 把改变的文件的目录写这里` 可以添加改变的文件内容到git用于管理工程状态的索引（快照）里。
8. 使用 `git commit -m "这里写修改的相关信息"` 来描述你做出了什么修改。
9. 使用 `git push origin 此处写分支名字`来把你的更改同步到GitHub库里（反正不是打篮球那个库里）。
10. 提交一个[QMK 固件的pull request](https://github.com/qmk/qmk_firmware/pull/new/master)。
11. 给你的pull request拟一个标题，包括简短的描述和问题或错误代码。比如, 你可以起一个这样的"Added more log outputting to resolve #4352"（最好用英语，毕竟Q酱的中文也不是那么的溜，有可能会看不懂中文）。
12. 在描述（description）里面写你做了哪些更改，你的代码里还存在什么问题, 或者你想问维护的小可爱们的问题。你的your pull request有点小问题无伤大雅(本来也没有完美的代码嘛), 维护的小可爱们会竭尽全力帮您改进的！
13. 维护人员审查代码可能需要一些时间。
14. 维护人员会通知您要更改什么地方，然后您就按照建议改一改。
15. 预祝您合并成功！

# 代码规范

其实也没有什么特别严格的规范啦，但是俗话说的好：没有规矩，不成方圆。您可以看一下您的要改动的代码周围的画风，然后保持队形。如果你感觉周围都不知道是什么牛鬼蛇神的话就看看下面的建议：

* 我们用肆(4)个空格来缩进(软件中也可以设置到Tab键)
* 我们使用改良的1TBS(允许单行样式)
  * 左大括号: 在开放性语句块那行的末尾
  * 右大括号: 和开放性语句块第一个字母对齐
  * Else If: 将右大括号放在行的开头，下一个左大括号放在同一行的结尾
  * 可选大括号: 可选大括号是必选的
    * 应该这样: if (condition) { return false; }
    * 不应该这样: if (condition) return false;
* 建议使用C语言风格的注释: `/* */`
  * 把注释想象成一个描述特征的故事
  * 充分使用注释来描述你为何这样修改
  * 有些公认的东西就不要写到注释里面了
  * 如果你不知道注释是否多余,看下面
* 一般不要主动换行，主动换行的话每行不要超过76列
* 要把 `#pragma once` 放到头文件的开始哦，抛弃老土的(`#ifndef THIS_FILE_H`, `#define THIS_FILE_H`, ..., `#endif`)吧
* 下面两种预处理命令都可以用: `#ifdef DEFINED` 还有 `#if defined(DEFINED)`
  * 以上那句对处女座不是很友好哈，处女座的朋友们就别纠结了，直接 `#if defined(DEFINED)` 。
  * 还有就是选好一种风格就一直用，一直用一直爽，不要朝三暮四, 除非你要变化到多重条件的 `#if`。
  * `#` 和 `if`要挨在一起哦，再让本空格在中间冒充电灯泡本空格会生气的。
  * 以下是缩进规则:
    * 首先考虑可读性，强迫症的朋友们总想要保持代码的高一致性，这样可不好。
    * 保证文件已有风格不变。如果代码本来就是杂糅风格，那就见机行事，让你的修改更有意义些。
    * 其实你也可以在缩进的时候看看周围其他代码，然后范水模山，预处理命令可以有自己的缩进风格。

可以参照下面:

```c
/* foo 的 Enums*/
enum foo_state {
  FOO_BAR,
  FOO_BAZ,
};

/* 有返回值的情况 */
int foo(void) {
  if (some_condition) {
    return FOO_BAR;
  } else {
    return -1;
  }
}
```

# Clang-format的自动格式化
[Clang-format](https://clang.llvm.org/docs/ClangFormat.html) 是LLVM的一部分，可以帮你自动格式化代码。我们给你准备好了一个适用于以上规范的配置文件，会帮你调整缩进和换行，你只需要写好括号就好。有了它，你再也不用担心调整代码格式太耗时，没有时间陪伴自己（虚构）的另一半了。

使用[LLVM 完整安装](http://llvm.org/builds/)可以在Windows上安装clang-format, Ubuntu用户要用`sudo apt install clang-format`。

命令行的朋友们, 加上 `-style=file`选项就会自动在QMK的根目录寻找.clang-format配置文件了。

VSCode用户, 标准的 C/C++ 插件就支持clang-format, 或者可以用[独立扩展](https://marketplace.visualstudio.com/items?itemName=LLVMExtensions.ClangFormat)也行。

有些东西(比如LAYOUT宏) 会被clang-format打乱，所以那些文件就别用clang-format了,这里就教您一个小窍门，在`// clang-format off` 和 `//clang-format on`之间装上会被搞乱的代码就好了。

# 一般教程

你可以给Q酱的不同部分添砖加瓦，但也要用不同的方法严谨检查。不论你修改哪里最好还是看看下边。

* 将PR（pull request）分成一个个的逻辑单元。 比如，不要一次将两个新特性PR出去。要添加的特性排好队，一个一个来。
* 提交之前看一眼，`git diff --check`的空格一定要写对了
* 确定你的代码能通过编译
  * 布局: 确定`make keyboard:your_new_keymap` 不返回错误
  * 键盘: 确定 `make keyboard:all` 不返回错误
  * 核心代码: 确定 `make all` 不返回错误
* 提交的信息尽量明确。第一行写点简短介绍(每行不多于70个英文字母), 第二行空着,第三行和后面就要写些必要的细节了。最好用英文写，比如:

```
Adjust the fronzlebop for the kerpleplork

The kerpleplork was intermittently failing with error code 23. The root cause was the fronzlebop setting, which causes the kerpleplork to activate every N iterations.

Limited experimentation on the devices I have available shows that 7 is high enough to avoid confusing the kerpleplork, but I'd like to get some feedback from people with ARM devices to be sure.
```

## 文档

想帮助Q酱当然是先看文档最简单了。找到这个文档哪里错了然后改正它对于你来说超级简单! 我们也对有写文档能力的人求贤若渴，如果你是对的人[点这个](#Q酱，我在哪能帮助你嘞?)!

文档呢，都静静的放在`qmk_firmware/docs` 目录里, 也或者您想为网页做贡献的话也是可以的哦。

在文档中附代码案例时, 先观察文档其他地方的命名规范。比如, 把enums的名字都改成像`my_layers`或者`my_keycodes`来防止名字不一致的enums被当作特务枪毙:

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

## 布局

大多数QMK新手都从创建一个自己的布局开始。我们尽力保证布局规范宽松 (毕竟布局是个性的体现) 不过建议遵守以下准则，这样可以让别人更好理解你的代码

* 用 [模板](documentation_templates.md)写个`readme.md`。
* 所有的布局PR都会被squash, 如果你想知道你的提交是怎么被squash的那你就自己来吧
* 不要把新特性和布局一起PR。可以分别PR他们
* 布局文件夹就不要放`Makefile`了，这个操作都过时啦
* 更新文件头部的copyrights(看`%YOUR_NAME%`那)

## 键盘

QMK的最终归宿是键盘。有些键盘是社区维护的，有一些是制作这些键盘的人维护的。`readme.md`会告诉你是谁维护了这个键盘，如果你对某个键盘有疑问，可以 [创建一个Issue](https://github.com/qmk/qmk_firmware/issues) 来问一问维护者。

我们建议你按下面的来操作:

* 用[模板](documentation_templates.md)写`readme.md`。
* 提交数量尽量合理，不然我们可就要把你的PR给squash了。
* 不要把新特性和新键盘一起PR。可以分别PR他们
* 用父文件夹的名字命名 `.c`/`.h`文件, 比如`/keyboards/<kb1>/<kb2>/<kb2>.[ch]`
* 键盘文件夹就不要放`Makefile`了，这个操作都过时啦
* 更新文件头部的copyrights(看`%YOUR_NAME%`那)

## Quantum/TMK 核心

在您废寝忘食地开发Q酱新特性或者帮Q酱驱虫之前，一定要确保你的工作是有意义的。看看[了解QMK](understanding_qmk.md)你会对Q酱有更深的了解，这个文档将带你领略QMK的程序流程。现在你应该和维护团对谈谈来了解实现你想法的最佳方法了。一下渠道都可以：

* [在Discord交流](https://discord.gg/Uq7gcHh)
* [建立一个Issue](https://github.com/qmk/qmk_firmware/issues/new)

新特性和BUG的修复影响所有键盘。开发组也在翻修QMK。所以，在实施重大返修之前一定要讨论一下。如果你在没有事先与维护团队沟通的情况下提交了一个PR，而且你的选择与维护团队的计划方向不符，那你可能要面临大改了。

修复BUG或者开发新特性之前看看这个：

* **默认不启用** - QMK运行的芯片多数内存有限，所以首要考虑的还应该是布局不要被破坏，于是特性默认是不启用的。你喜欢什么特性的话就打开它，如果你觉得有些特性应该默认开启或者你能帮助缩减代码，那就联系维护组吧。
* **提交之前在本地编译** - 这个简直就是家喻户晓了，但是也确实需要编译啊！ 我们的Travis系统会发现一切问题，但是自己编译一下可要比在线等快多了。
* **注意版本和芯片平台** - 有那么几个键盘有支持不同配置甚至是不同芯片的版本。试着写一个能AVR和ARM两个平台运行的特性，或者在不支持的平台自动禁用。
* **解释你的新特性** - 在`docs/`写个文档, 你可以创建新文档或者写到现有文档中。如果你不把它记录下来，其他人就无法从你的努力中获益。

也可以看看以下建议：

* 提交数量尽量合理，不然我们可就要把你的PR给squash了。
* 不要把新特性、布局和键盘一起PR。可以分别PR他们。
* 给你的特性写[单元测试](unit_testing.md)。
* 你编辑的文件风格要一致，如果风格不明确或者是混搭风的，你就要先看看[代码规范](#代码规范)确认情况。

## 重构

为了保持QMK脉络清晰，Q酱打算深入规划重构一下自己，然后让合作者进行修改。如果你有重构的思路或建议[创建一个issue](https://github.com/qmk/qmk_firmware/issues), Q酱很乐意讨论一下怎么改进一下。

# 行为守则对于我来说有何意义?

我们的[行为守则](https://github.com/qmk/qmk_firmware/blob/master/CODE_OF_CONDUCT.md) 是说明您有责任尊重和礼貌地对待项目中的每个人，无论他们的身份如何。 如果你是我们行为准则所描述的不当行为的受害者，我们将站在你这边，并按照行为准则对施暴者进行适当谴责。
