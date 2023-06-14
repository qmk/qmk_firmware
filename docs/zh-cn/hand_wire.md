# 手工搭建指南

<!---
  original document: 0.15.17:docs/hand_wire.md 
  git diff 0.15.17 HEAD -- docs/hand_wire.md  | cat
-->

## 模块清单

你需要的模块有：（*x*为你设计的键盘的键数）

* QMK所兼容的主控板（Teensy, Pro-Micro, QMK Proton C 等）
* *x* 个键轴 （MX, Matias, Gateron 等）
* *x* 个通孔二极管（译注：即普通的直插二极管）
* 定位板及卫星轴
* 电线
* 电烙铁
* 松香/焊油
* 通风的环境/风扇通风
* 剪线钳

可选地但比较有用的：

* 剥线钳/一把锋利的剪刀
* 镊子及小尖嘴钳
* 焊台/一位助手

## 前期工作

组装PCB矩阵的方法多种多样，这份指引会描述一些基础信息并给出一些推荐方案。

既然我们要进行手工飞线搭建，这里就假设你已经有了定位板。如果你想构建完全定制化的配列，有 [ai03 Plate Generator](https://kbplate.ai03.me/) 以及 [Swillkb Plate & Case Builder](http://builder.swillkb.com/) 这样的工具可以助你设计出一个新的。

首先从安装键轴及卫星轴开始，考虑厚度及材质的影响，可能需要热熔胶来固定。

## 设计矩阵 :id=planning-the-matrix

如果你在参考已有的手工搭建指南（比如[自制键盘固件目录](https://github.com/qmk/qmk_firmware/tree/master/keyboards/handwired)下的键盘），可以跳过该步骤，确保是按照文中的矩阵方案连线即可。

如果你的方案是将每个开关的一个引脚与两边的开关相连（行方向），另一个引脚与上下的开关相连（列方向），并串联一个二极管到一端，最常用的方案是二极管背对着连接到行方向的引脚（列向行）。即让远离二极管黑线一端连接到开关上（电流只能从一个方向通过二极管）。

可以很容易地设计出正交连接的键盘（如Planck）。
（译注：这里的“正交”意思是行列方向连接规整）

![Planck矩阵示例图](https://i.imgur.com/FRShcLD.png)
[作者：RoastPotatoe "如何手工搭建Planck键盘"](https://blog.roastpotatoes.co/guide/2015/11/04/how-to-handwire-a-planck/) （英文）内的图例

键盘配列越大，功能越丰富，则矩阵也会更复杂。[Keyboard Firmware Builder](https://kbfirmware.com/) 可以帮助你设计矩阵配列（下图为通过 [Keyboard Layout Editor](https://www.keyboard-layout-editor.com) 导出的全尺寸ISO键盘）。

![ISO键盘矩阵示例图](https://i.imgur.com/UlJ4ZDP.png)

必须时刻留意矩阵的行列数总和不能超出控制器的IO引脚数，因此上图的方案可以使用 Proton C 或 Teensy++ 控制器，但常规 Teensy 或 Pro Micro 不行。

### 常见微控制器板 :id=common-microcontroller-boards

| 控制器板       | 控制器方案     | # I/O引脚数  | 引脚图 |
| :------------ |:-------------:| ------:| ------ |
| Pro Micro*    | ATmega32u4    |     20 | [链接](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/hardware-overview-pro-micro#Teensy++_2.0)       |
| Teensy 2.0    | ATmega32u4    |     25 | [链接](https://www.pjrc.com/teensy/pinout.html)       |
| [QMK Proton C](https://qmk.fm/proton-c/)      | STM32F303xC   |     36 | [链接 1](https://i.imgur.com/RhtrAlc.png), [2](https://deskthority.net/wiki/QMK_Proton_C)       |
| Teensy++ 2.0  | AT90USB1286   |     46 | [链接](https://www.pjrc.com/teensy/pinout.html#Teensy_2.0)       |

*Elite C 与 Pro Micro 除将 Micro USB 替换为 USB-C 外其余无差别。

一些主控板专门为手工接线设计，除可直接连接少量开关外还有额外的引脚，但这些通常会更贵一些，也更难掌控。

<img src="https://i.imgur.com/QiA3ta6.jpg" alt="实装的 Postage mini 主控板" width="500"/>

| 控制器板       | 控制器方案    | # I/O引脚数  |
| :------------ |:-------------:| ------:|
| [Swiss helper](https://www.reddit.com/r/MechanicalKeyboards/comments/8jg5d6/hand_wiring_this_might_help/) |  ATmega32u4 | 20 |
| [Postage 主控板](https://github.com/LifeIsOnTheWire/Postage-Board/)| ATmega32u4| 25 |
| [Postage mini 主控板](https://geekhack.org/index.php?topic=101460.0)| ATmega32u4| 25 |

## 矩阵布线

布线方案不是唯一的，要达成的效果是可以正确连接所有的焊点并不会出现预期外的短路。

公开的材料和技术方案：

（译注：链接文章及标题恕不翻译）

| 技术方案     | 示例 | 优点 | 缺点 | 图片
| :-----------| :------- | :------ | :--- | :---
| 间断开口的线缆 | [Sasha Solomon's Dactyl](https://medium.com/@sachee/building-my-first-keyboard-and-you-can-too-512c0f8a4c5f) 以及 [Cribbit's modern hand wire](https://geekhack.org/index.php?topic=87689.0) | 整洁 | 线缆开口的操作会有些困难 | ![开口的线缆](https://i.imgur.com/0GNIYY0.jpg)
| 适宜长度的线缆 | [u/xicolinguada's ortho build](https://www.reddit.com/r/MechanicalKeyboards/comments/c39k4f/my_first_hand_wired_keyboard_its_not_perfect_but/) | 剥线容易 | 较难固定位置 | ![适宜长度的线缆](https://i.imgur.com/mBe5vkL.jpg)
| 漆包线 | [fknraiden's custom board](https://geekhack.org/index.php?topic=74223.0) | 可以直接焊接（烧掉绝缘层） | 外观差？ | ![漆包线](https://i.imgur.com/b4b7KDb.jpg)
| 弯折二极管引脚作为行方向连线 | [Matt3o's Brownfox](https://deskthority.net/viewtopic.php?f=7&t=6050) | 焊点更少 | 绝缘性差 | ![弯折了的二极管引脚](https://i.imgur.com/aTnG8TV.jpg)
| 硬线（如铜管） | [u/d_stilgar's invisible hardline](https://www.reddit.com/r/MechanicalKeyboards/comments/8aw5j2/invisible_hardline_keyboard_progress_update_april/) 以及 [u/jonasfasler's first attempt](https://www.reddit.com/r/MechanicalKeyboards/comments/de1jyv/my_first_attempt_at_handwiring_a_keyboard/) | 非常漂亮 | 难度高，没有物理绝缘 | ![手工连接的硬线](https://i.imgur.com/CnASmPo.jpg)
| 用绝缘胶带（如高温胶带*）隔离开的裸线 | [Matt3o's 65% on his website](https://matt3o.com/hand-wiring-a-custom-keyboard/) | 简单（不用剥线） | 丑拒 | ![裸线](https://i.imgur.com/AvXZShD.jpg)
| 铜箔胶带 | [ManuForm Dactyl](https://github.com/tshort/dactyl-keyboard) | 非常简单 | 只适用于定位板/外壳与开关底部平齐的情况 | ![铜箔胶带](https://i.imgur.com/RFyNMlL.jpg)

（*译注：原文是聚酰亚胺胶带，在中国通常叫高温胶带）


以上方案可以结合使用，在焊接前请准备好各种长度的线缆。


### 分体键盘的注意事项

如果你想制作的是分体键盘（如Dactyl），每一半边都需要一个控制器以及连通两方的通信用线（如TRRS或硬连接线）。更多资料参见[QMK分体键盘文档](zh-cn/feature_split_keyboard.md)。
（译注：TRRS即一种常用的4线耳机线插口，具体信息请查阅维基百科或[这份知乎文章](https://zhuanlan.zhihu.com/p/144233538)）


### 焊接

你可以找到很多焊接指导及技巧，这里列出了最相关及最关键的部分：

要想焊接的牢固需要确保焊料与焊接两端的金属面充分地接触，一个好办法（也不是必须）是上锡前先（将线缆）在针脚上绕一圈或先拧在一起。

<img src="https://i.imgur.com/eHJjmnU.jpg" alt="杆上绕圈" width="200"/> <img src="https://i.imgur.com/8nbxmmr.jpg?1" alt="绕环的二极管引脚" width="200"/>

如果二极管还在包装条上且需要弯折（作为绕圈的起点处或用于连接到邻接处），一个简便的办法是找一个盒子、桌子或尺子的直边上进行弯折。由于弯折统一在二极管一侧，也有助于区分二极管的方向。

<img src="https://i.imgur.com/oITudbX.jpg" alt="弯折二极管引脚" width="200"/>

如果你的电烙铁有温控功能，将其设置在 315ºC（600ºF）。

热起来后，给电烙铁上锡 - 即融化一部分锡料到烙铁头上然后立刻用湿海绵或烙铁头海绵擦掉，这样烙铁头上会有一层光滑明亮的焊料，以防止氧化且有助于焊料的焊接操作。

接下来进行焊接，先将烙铁头在焊接面上接触一会儿进行加热，然后上焊料焊接两侧。加热焊接面的目的是为了确保焊料可以粘附且不会过早冷却下来。

不能让焊料/焊点加热过度，热量会通过接触面烧毁原件（融毁开关外壳等）。并且，由于焊锡中有帮助[“浸润”](https://en.m.wikipedia.org/wiki/Wetting)（即上锡）的助焊剂，加热的越久助焊剂蒸发掉的越多，最终导致焊接点虚焊，除了看起来糟糕外，还有导致电路短路的风险。

#### 焊接二极管

从左上角的那个开关开始，将二极管放到开关上（用镊子，如果有的话）并纵向放直，有黑线的一端朝向你。让二极管间并联（二极管的阴极不应连接到其它二极管的阳极），二极管的阳极应连接到开关的左引脚上，而弯曲的阴极应朝向右边放置，如图：

![soldering-diodes-01.png](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/docs/hand_wire/soldering-diodes-01.png)

在放稳二极管后，拿起焊锡，将其与左轴脚同时接触到电烙铁上 - 在松香的帮助下焊锡会很容易地覆盖在二极管及轴脚上。二极管可能会有些位移，此时你可以抓住二极管另外一端弯折过的引脚，小心地放回到位置上 - 但请留意另一端是会迅速变得烫手的。如果二极管容易乱跑，可以使用尖嘴钳之类的东西在焊接时辅助保持稳固。

松香加热时升起的烟有害，注意保护口鼻，不要熏到眼睛或皮肤。

焊接到位时，可以将焊点升起的烟吹走以免熏脸，也能帮助焊点快速降温。焊点在冷却后会形成沙哑状（无光泽）的表面，但请注意此时它依旧非常烫，需要几分钟时间的冷却才可以触摸，多吹吹有助于快速冷却。

在第一个二极管焊接完毕后，第二个二极管需要焊接轴脚以及上一个二极管弯折的那一端，看起来像这样：

![soldering-diodes-02.png](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/docs/hand_wire/soldering-diodes-02.png)

在焊接完毕一整行后，用剪线钳剪掉二极管上方（绕轴脚后多出的部分），以及这一行最后侧多出来的引脚部分。在每一行焊接完毕后都要记得这一步。

在你完成了所有的二极管的焊接工作后，最好是逐一测试一下以确保焊接牢固稳定 - 再往后不是不能回头修正，但会越来越困难。

#### 纵向上的焊接

这一步你有几个可选项需考虑 - 给横向电缆进行绝缘处理是个好主意（毕竟二极管没有绝缘层），但如果你足够小心，横向电缆裸露着也行 - 但仍旧不建议这么做。如果你用的是单芯线，先将外皮整个褪下来再酌情装回去可能是最好的办法，但会因尺寸及材质原因造成操作困难，你可以将线缆上需要焊接到开关轴的部分裸露出来。

如果你使用多股线/铜绞线，可能最简单的方案就是用不固定长度的小段电线来纵向连接开关。通过融化掉焊接点的外皮的方式来用一整根线不是不可以，但这里不推荐这样做，这种操作会产生更多的有害烟尘，也会毁掉你的电烙铁。

在进行焊接操作前，先预弯折好线缆（如果是单芯线），或至少心中已经规划好焊接路线顺序（特别是你要做的设计是错列的时）。实际上焊接顺序不是特别重要，因为我们是通过焊接方案来确定键映射定义的 - 只要确保一行上的所有按键都有独自的列，且从左到右依次排列。

如果你不做任何的绝缘处理，可以将纵向的线升高一些，焊接在轴脚尖端上 - 如果线缆本身足够稳固，不会短路到连接着二极管的横线线缆上。

## 连接控制器

在矩阵焊接完成后，可以将其焊接到微控制器板上了。

将微控制器放在预期的位置上，同时要考虑到安装及外壳对齐问题。须记得USB槽的位置是可以与微控制器分开的，只需使用一小段公对母线接驳下即可。

找到微控制器板的引脚定义/文档（[链接](#common-microcontroller-boards)）并将所有的I/O引脚标出来（留意像teensy这种的控制器，模拟I/O引脚可能是数字I/O引脚的两倍），将线缆连接到这些引脚上。

----

### 针对 Teensy 2.0 的特殊说明

Teensy 上的部分引脚有点特殊，像 D6（片上LED），及一些 UART、SPI、I2C或PWM通道，不过只是在你计划着在键盘上还有其它功能设计时才需避免使用。如果你还不是很确定以后会不会增加什么功能上去，引脚应该还是足够充足到可以剩一部分出来的。

那些无论在什么控制器上都不应去使用的引脚，有：GND、VCC、AREF以及RST - 其它所有引脚都是可以用且也能在固件中访问的到的。

----


将电线切割为控制器到各行/列上某一点距离的长度。可以焊到各行的任意位置上，只需要确保是在二极管之后 - 焊接到二极管前面（轴脚侧）的话该行将无法正常使用。

这里用排线的话会显得非常整洁，你也可以考虑如何排布线缆以连接到各行/列的近处。

<img src="https://i.imgur.com/z2QlKfB.jpg" alt="排线" width="350"/>

在往控制器上焊接电线时，请记住各引脚连接的是哪一行/列，在后续制作固件时我们需要用到这些信息来定义矩阵。

在你往下继续以前，请确保控制器已装配到位 - 切掉线缆再重新焊接非常麻烦！


## 一些基础的固件配置

至此，在你构建好固件后，键盘就应该能正常工作了。

通过 [Keyboard Firmware Builder](https://kbfirmware.com/) 网站可以轻松地创建一个简单的固件。通过 [Keyboard Layout Editor](https://www.keyboard-layout-editor.com) 可以自己制作配列数据，之后就可以导入进来并重新构建矩阵信息（如果你没有在先前的 [设计矩阵](#planning-the-matrix) 完成的话）。

继续完成剩下的步骤，在逐一配置完所有的按键后就可以编译下载固件了。其中 .hex 文件可以用来直接刷写到键盘上，而 .zip 包中的源代码可以用来添加高级功能并通过 [构建第一个固件](zh-cn/newbs_building_firmware?id=build-your-firmware) 中详述的方法进行本地构建。

Keyboard Firmware Builder提供的源代码是QMK的，但版本是2017年初的。如果要用现今版本的QMK来构建 .zip 中的源代码，需要在打开 .zip 后遵循以下几步：

1. 解压 `kb` 目录到 `qmk_firmware/keyboards/handwired/`。
2. 进入解压的 `kb` 目录，转到 `keymaps/default/` 目录下，打开 `keymap.c`。
3. 找到并删除 `action_get_macro` 代码段：
   ```
    const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
        ...
        return MACRO_NONE;
    }
   ```
4. 保存并关闭 `keymap.c`。

## 刷写固件

安装 [QMK Toolbox](https://github.com/qmk/qmk_toolbox).

![QMK Toolbox](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/docs/hand_wire/qmk_toolbox.png "QMK Toolbox 0.0.16 on Windows 8.1")

在 “Local File” 栏处定位到你新创建的 .hex 文件，在 “MicroController” 中选择你的控制器板（常见型号[这里](#common-microcontroller-boards)有）。

插上你的键盘后在QMK Toolbox中点击reset（重置）按钮（如果没有重置按钮，短接一下Reset和接地引脚）再点击“Flash”（刷写）按钮。


## 测试固件

可以用 [QMK配置器的键盘测试器](https://config.qmk.fm/#/test)、[Keyboard Tester](https://www.keyboardtester.com/tester.html) 或 [Keyboard Checker](https://keyboardchecker.com/) 进行测试，也可以打开一个文本编辑器并试着输入 - 你应该能成功输入键映射方案中的所有字符。对每个按键进行测试，并记录下不能正常工作的按键。对这些不能正常工作的按键，这里有一个快速排查指引：

1. 将键盘翻过来，用一段金属物短接一下轴脚 - 这么做可以排除掉需要更换掉的坏轴的可能性。
2. 检查轴脚上的焊点 - 应该是饱满且完整覆盖的。如果你稍加用力就能将其弄下来，那么就是焊接不到位。
3. 检查二极管的焊点 - 如果二极管虚焊了，部分行可以使用，但其它的可能就不行了。
4. 检查连接到各行的焊点 - 如果这里虚焊了，这些行就无法正常使用。
5. 检查 Teensy 两侧的进/出线的焊点 - 两侧的线缆都必须确保已被良好地焊接。
6. 检查 `<project_name>.h` 文件中是否有错误或不当的 `KC_NO` - 如果不确定在哪里，用已有的 k*xy* 变量替换一下。
7. 检查固件文件确实经过编译且正确刷写到Teensy上了。除非你在终端看到了错误消息，或是刷写时出现了弹框，否则一切应该是正常的。
8. 使用万用表实测一下，触发开关时是否成功闭合（按下时可以连通电路）。

如果你完成了上述所有检查，应当留意有时可能是多种因素共同造成了开关的异常，因此最后将其短路掉来排查问题并没有什么害处。

## 即将完成

在确认键盘可以正常使用后，如果你用的是独立的控制器模块（非手工构建用），须将其固定好。办法有很多，比如热熔胶、双面胶带、3D打印的盒子、电工胶带等。

如果你觉得成就感满满，可以试着增加一些额外的功能，比如 [轴内LED](https://geekhack.org/index.php?topic=94258.0)，[轴内RGB](https://www.reddit.com/r/MechanicalKeyboards/comments/5s1l5u/photoskeyboard_science_i_made_a_handwired_rgb/)，[RGB背光](https://medium.com/@DavidNZ/hand-wired-custom-keyboard-cdd14429c7b3#.7a1ovebsk) 甚至可以是 [OLED显示屏！](https://www.reddit.com/r/olkb/comments/5zy7og/adding_ssd1306_oled_display_to_your_build/) 

固件的潜力非常大 - 阅览 [docs.qmk.fm](https://docs.qmk.fm) 可以看到全部功能的列表，也能深入了解人们是如何使用那些五花八门的键盘的。随时欢迎到 [OLKB subreddit](https://reddit.com/r/olkb) 或 [QMK Discord](https://discord.gg/Uq7gcHh) 上寻求帮助！

## 其它指引链接

- [matt3o 的分步指引 (BrownFox build)](https://deskthority.net/viewtopic.php?f=7&t=6050) 以及他的 [个人站点](https://matt3o.com/hand-wiring-a-custom-keyboard/) 和 [指导视频](https://www.youtube.com/watch?v=LVzpsjFWPP4)
- [Cribbit：“现代化的手工搭建指南 - 强大，简洁，友好”](https://geekhack.org/index.php?topic=87689.0) 
- [Sasha Solomon：“打造我的第一把键盘”](https://medium.com/@sachee/building-my-first-keyboard-and-you-can-too-512c0f8a4c5f)
- [RoastPotatoe： “如何手工搭建Planck键盘”](https://blog.roastpotatoes.co/guide/2015/11/04/how-to-handwire-a-planck/)
- [Masterzen：“手工搭建键盘记录”](https://www.masterzen.fr/2018/12/16/handwired-keyboard-build-log-part-1/)


# 遗留内容

以前本页内还有其它内容，现在我们已经将他们单独分离出去了。以下的内容是一些重定向链接，以供那些从老链接地址过来的人能找到自己要找的内容。

## 序: 键盘矩阵是如何工作的（以及为什么需要二极管） :id=preamble-how-a-keyboard-matrix-works-and-why-we-need-diodes

* [键盘矩阵是如何工作的](zh-cn/how_a_matrix_works.md)
