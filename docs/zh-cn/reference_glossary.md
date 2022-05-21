# QMK术语表

<!---
  original document: 0.15.12:docs/reference_glossary.md
  git diff 0.15.12 HEAD -- docs/reference_glossary.md | cat
-->

## ARM
多家公司生产的32位单片机系列，例如Atmel, Cypress, Kinetis, NXP, ST, 和 TI等公司。

## AVR
[Atmel](https://www.microchip.com/)公司的单片机系列。 AVR是TMK的初始支持平台。

## AZERTY
Français （法语）标准键盘布局。用键盘的前六个字母命名。

## Backlight(背光)
键盘上照明的通称。背光通常是一组LED灯，穿过键帽或者轴体发光，但也不总是这样。

## Bluetooth(蓝牙)
一种短距离点对点无线传输协议。许多无线键盘使用此协议。

## Bootloader(引导加载程序)
一种写到你单片机保护区的特殊程序，该程序可以使单片机升级自己的固件，通常是通过USB来升级。

## Bootmagic(热改键)
允许各种键盘行为动态变化的功能，如交换或禁用常用键。

## C
一种适用于系统代码的低级编程语言。大多数qmk代码是用C编写的。

## Colemak
一种流行的键盘布局。

## Compile(编译)
把人可读的代码转换成你的单片机可以运行的机器代码的过程。

## Dvorak
一个由August Dvorak博士在20世纪30年代创建的布局。Dvorak简化键盘(Dvorak Simplified Keyboard)的缩写。

## Dynamic Macro(动态宏)
一种记录在键盘上的宏，当键盘拔出或计算机重新启动时，宏将丢失。

* [动态宏文档](zh-cn/feature_dynamic_macros.md)

## Eclipse
是一种受C语言开发者追捧的集成开发环境(IDE)。

* [Eclipse安装说明](zh-cn/other_eclipse.md)

## Firmware(固件)
用来控制单片机的软件。

## git
命令行版本控制软件

## GitHub
负责大多数QMK项目的网站。它是Git、问题跟踪和其他帮助我们运行qmk的功能的集成平台。

## ISP(在线系统编程)
在线系统编程(In-system programming), 使用外部硬件和JTAG管脚对AVR芯片进行编程的一种方法。

## hid_listen
从键盘接收调试消息的接口。 您可以使用[QMK Flasher](https://github.com/qmk/qmk_flasher)或[PJRC's hid_listen](https://www.pjrc.com/teensy/hid_listen.html)查看这些消息

## Keycode(键码)
表示特定键的2字节数据。`0x00`-`0xFF`用于[基本键码](zh-cn/keycodes_basic.md)而`0x100`-`0xFFFF`用于[量子键码](zh-cn/quantum_keycodes.md).

## Key Down
一个键按下尚未抬起时触发的事件。

## Key Up
一个键抬起时触发的事件。

## Keymap(键映射)
映射到物理键盘布局的一组键码，在按键和按键释放时进行处理。有时翻译为布局，意为软件上表示的布局，即映射。

## Layer(层)
为了让一个键实现多个功能的抽象结构。可用层数有上限。

## Leader Key(前导键、设置菜单键)
本功能允许您点击前导键，然后按顺序按1-3个键子来激活按键或其他量子功能。

* [前导键文档](zh-cn/feature_leader_key.md)

## LED
发光二极管，键盘上最常用的指示灯装置。

## Make
用于编译所有源文件的软件包。可以使用`make`命令和其他参数来编译你的固件。

## Matrix(矩阵)
一种由列和行组成的接线模式，使单片机能够用较少的引脚检测按键。矩阵通常包含二极管，以达到全键无冲。

## Macro(宏)
本功能可以在敲击单个键后发送多个按键事件(hid报告)。

* [宏文档](zh-cn/feature_macros.md)

## MCU(单片机、微控制单元)
微控制单元，键盘的处理器。

## Modifier(修饰键、修改键、功能键)
按住该键将会改变其他键的功能，修饰键包括 Ctrl, Alt, 和 Shift。

## Mousekeys(鼠标键)
本功能在您敲击键盘时会控制鼠标光标。

* [鼠标键文档](zh-cn/feature_mouse_keys.md)

## N-Key Rollover (NKRO、全键无冲)
一种术语，适用于能够同时报告任意数量按键的键盘。

## Oneshot Modifier(粘滞键)
一种能让你的功能键一直保持按下，直到你按下其他键的功能。它叫做粘滞键或叫做粘连键，该功能由软件实现而非机械结构。

## ProMicro
一种低成本AVR开发板。这种板子很容易在购物网站找到(价格不到20RMB)，但是据说刷写pro micro有点令人抓狂。

## Pull Request(拉请求、PR)
向QMK请求提交代码。我们鼓励所有用户提交你们自己的键盘的代码。

## QWERTY
标准英文键盘，通常也用于其他语言，例如中文。是用键盘前6个字母命名的。

## QWERTZ
标准Deutsche(德语)键盘布局。使用前6个字母明名。

## Rollover(允许翻转、无冲形式)
该术语表示在一个键已按下时按下另一个键。形式包括2KRO(双键无冲),6KRO(6键无冲),和NKRO(全键无冲)，无冲表示可同时按下而不产生冲突的键的数量。

## Scancode(扫描码)
HID报告中的一个1字节的数字，表示一个键子。这些数字在下列文档中[HID Usage Tables](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf)该文档发布于[USB-IF](https://www.usb.org/)。

## Space Cadet键盘的shift键
一种特殊的shift设置，能让你通过敲击左或右shift一次或多次键入不同的括号。

* [Space Cadet键盘文档](zh-cn/feature_space_cadet.md)

## Tap(敲击、单击)
按下并抬起一个键。在某些情况下您需要区分键按下和键抬起，但是单击把两个事件都包括了。

## Tap Dance(多击键)
本功能允许向同一个键子分配多个键码，并根据按键次数区分。

* [多击键文档](zh-cn/feature_tap_dance.md)

## Teensy
一种低成本AVR开发板<!--译者吐槽：我怎么感觉成本不低。好吧，我穷。 -->，通常用于手工连线键盘。这个teensy是有点小贵但是halfkay bootloader会让它刷写十分简单，所以也很常用。

## Underlight(背光)
用于照亮电路板底面的LED的总称。这些LED通常从印刷电路板的底部向键盘所在的表面发光。

## Unicode
在广阔的计算机世界中，Unicode是一组编码方案，用于表示任何语言中的字符。 与qmk相关的是，它意味着使用各种操作系统方案来发送Unicode码点，而不是扫描码。

* [Unicode文档](zh-cn/feature_unicode.md)

## Unit Testing(单元测试)
针对qmk的自动测试框架。单元测试帮助我们确信我们的更改不会破坏任何东西。

* [单元测试文档](zh-cn/unit_testing.md)

## USB
通用串行总线，键盘最常见的有线接口。

## USB 主机 (简称主机)
USB主机就是你的电脑，或者你的键盘所插的任何设备。

# 并没有找到你想找到的术语?

[新建一个issue](https://github.com/qmk/qmk_firmware/issues) ，想好你的问题，或许你所问的术语就会添加到这里。创建一个PR帮我们添加需要添加的术语当然坠吼了:)

## 中文翻译术语特别说明（terms of Chinese translation）:id=terms-of-zh-cn-translate
!>如果你对QMK文档翻译中的细节不关心，请跳过该节

由于语言及文化差异，QMK英文文档中的部分内容，很难在**保持原句结构**的情况下，完美地翻译为中文，而保持翻译前后的语句结构一致对于开源代码的文档翻译来讲十分重要，这样才能确保不同的文档贡献者不会*夹带私货*，防止不同的翻译风格、不同的翻译水准、不同的理解与润色最终产生糟糕的混合。
因此，这里会对一些词组的的翻译进行规范化，并希望阅读者及后续文档翻译维护者，维持这种统一的范式。

### keyboard（键盘）及keymap（键映射）
QMK文档中使用最多的两个术语是keyboard及keymap
* 键盘：在中文语境下，我们提及键盘，基本是在指物理键盘，而在QMK文档中到处可见的“键盘”一词，多对应的是代码中 `keyboards\` 目录下的键盘定义，其更接近于我们讲的“配列”的概念，主要描述了键盘的大体结构，物理键数量及排列。
* 键映射：keymap的作用是定义物理键盘到实际输出键值(keycode)的映射关系，也是QMK最重要、涉及最多的概念。QMK很多功能就是为了能够在不改变键盘物理排列/电路组成/芯片程序的情况下，动态地改变物理按键输出的键值。如，通过层切换，将原先的wasd键，切换到可以上下左右的模式，或是一键切换CapsLock和Control，实现这些功能的核心工作就是一套动态的keymap，即键映射逻辑。这里不使用“布局”一词作为keymap的翻译，是因为该词过于宽泛。键映射即便是不好听，至少解释了意思且语境中不容易误解。

### mod-tap
倾向于不翻译，直接使用原词。因为找不到合适的译法

### dead key
直译为死键，西语体系下使用的特殊符号，中文中无对应概念。

### flashing（firmware）
使用“刷写”而非容易迷惑的“刷新”

### option/configuration/setting
根据上下文灵活考虑。对于组件化配置的概念，如一个功能支持与否，使用“配置”一词；对于客观上一定存在的某项设置值，使用“设置”一词。

### commit/push/pull等Git术语
倾向于不翻译。这些词语的对应中文词语过于宽泛或词性不明，非常容易混淆上下文。
