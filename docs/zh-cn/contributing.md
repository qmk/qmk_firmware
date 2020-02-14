<!--源文件：https://raw.githubusercontent.com/qmk/qmk_firmware/3c190f8927f8676febb5e247908d2bdfd574a54b/docs/contributing.md 
    源提交哈希：3c190f8927f8676febb5e247908d2bdfd574a54b-->
<!--翻译时间:20200214-17:44(GMT+8)-->
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

Q酱很大一部分是用C语言组成的，不过有一小部分特性是C++的。怎么说呢，都是我的一部分，两个我都爱。Q酱一般是在键盘上的嵌入式处理器那里工作的，尤其与AVR([LUFA](http://www.fourwalledcubicle.com/LUFA.php))和ARM ([ChibiOS](http://www.chibios.com))两小哥哥搭配，干活不累，嘻嘻。如果您精通Arduino的话您会发现很多熟悉的概念， 不过您以前的经验可能没法用来帮助Q酱。

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

我们的大多数风格您都是能接受的，如果您会C或者Python的话我们的代码都会让您有家一样的感觉。

* [代码规范 - C](zh-cn/coding_conventions_c.md)
* [代码规范 - Python](zh-cn/coding_conventions_python.md)

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

!> **重点来了:** 如果您想为用户代码做漏洞修复或者改进，比如改进一下非默认的映射、用户空间或布局什么的，请务必标注你的PR中代码的原始提交者。有好些开发者小可爱就因为自己的代码在不知情的情况下被修改了，都急哭了，他们中还有很多是平常表现很坚强的大神哦。

## 文档

想帮助Q酱当然是先看文档最简单了。找到这个文档哪里错了然后改正它对于你来说超级简单! 我们也对有写文档能力的人求贤若渴，如果你是对的人[点这个](#Q酱，我在哪能帮助你嘞?)!

文档呢，都静静的放在`qmk_firmware/docs` 目录里, 您如果习惯网页的话也是可以的哦，点击 https://docs.qmk.fm/ 页面下面的"Edit this page"就可以啦。

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

### 预览布局

在做出PR之前，你可以先预览一下文档。如果你安装了开大环境的话，在 `qmk_firmware/` 文件夹下使用下列命令:

    ./bin/qmk docs

或者你安装了Python3的话使用:

    python3 -m http.server 8936

然后访问 `http://localhost:8936/`.

## 映射

大多数QMK新手都从创建一个自己的映射开始。我们尽力保证映射规范宽松 (毕竟映射是个性的体现) 不过建议遵守以下准则，这样可以让别人更好理解你的代码

* 用 [模板](documentation_templates.md)写个`readme.md`。
* 所有的映射PR都会被squash, 如果你想知道你的提交是怎么被squash的那你就自己来吧
* 不要把新特性和映射一起PR。可以分别PR他们
* 映射文件夹就不要放`Makefile`了，这个操作都过时啦
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
