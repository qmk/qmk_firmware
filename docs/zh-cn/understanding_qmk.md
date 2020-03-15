# 理解QMK的代码

本文档尝试在非常高的角度解释QMK固件工作原理。本文假设您明白基本的编程概念但并不太熟悉C语言(除非事先说明)。本文假设您基本理解以下文档：

* [介绍](zh-cn/getting_started_introduction.md)
* [键盘工作原理](zh-cn/how_keyboards_work.md)
* [问题与解答](zh-cnfaq.md)

## 开始

你可以认为QMK与其他的计算机程序没有什么不同，都是开始，执行任务，然后结束。程序的入口点是`main()`函数，就和其他的C语言程序一样。但是，对于一个QMK的新人来说可能会找不着北，因为`main()`函数在很多地方都有出现，很难说应该看哪一个。

出现这种情况的原因是QMK需要支持多平台。最普通的平台叫`lufa`，该平台在AVR处理器平台运行，比atmega32u4。我们也支持`chibios` 和 `vusb`。

我们现在看AVR平台,也就是用 `lufa` 的那个。入口函数 `main()` 在 [tmk_core/protocol/lufa/lufa.c](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/tmk_core/protocol/lufa/lufa.c#L1028)。如果你浏览该函数你将会发现它初始化了被配置的所有硬件(包括连接在主机上的USB)，然后它就在[`while(1)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/tmk_core/protocol/lufa/lufa.c#L1069)中运行核心部分。这就是[主循环](#主循环)。

## 主循环

这部分的代码叫做“主循环”是因为它负责循环同一组指令。这是QMK调度那些实现QMK功能的函数的地方。乍一看有很多函数，但是大多数情况下代码都是被`#define`给禁用掉了。

```
    keyboard_task();
```

这是调度键盘特定功能的地方。`keyboard_task()`的源码详见[tmk_core/common/keyboard.c](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/tmk_core/common/keyboard.c#L216), 它负责检测矩阵变化并打开或关闭状态指示LED。

对于 `keyboard_task()` 您可以找到处理一下事务的代码：

* [矩阵扫描](#矩阵扫描)
* 鼠标处理
* 串行连接(们)
* Visualizer
* 键盘状态灯(Caps Lock, Num Lock, Scroll Lock)

#### 矩阵扫描

矩阵扫描是键盘固件的核心功能。事实上就是检测哪个键被按下，一秒之内本功能会被键盘运行多次。毫不夸张地说99%的CPU时间花费在矩阵扫描上。

对于矩阵检测有不同策略，这就不包含在本文档之内了，将矩阵扫描认为是黑盒的就好了。请求矩阵状态会返回类似下方的数据结构：


```
{
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
}
```

这个数据结构是4行5列的数字小键盘的矩阵的直接表示。当一个键被按下，矩阵相应位置将会返回`1`而不是`0`。

矩阵扫描每秒运行多次。确切的数字可能会有所不同，但是基本上每秒要运行10词以防键盘后知后觉导致的延迟。

##### 矩阵到物理布局的映射

当我们直到所有按键的状态后，我们就可以把他对应到键码了。在QMK中，这是通过使用C宏来完成的，以使我们能够将物理布局的定义与键码的定义分开。

在键盘的级别，我们定义了一个C宏(通常叫做 `LAYOUT()`)，这个宏将键盘矩阵映射到物理按键。 有时矩阵有的位置并没有按键，我们可以使用这个宏将这些地方预填充为KC_NO，这样可以让键映射 更容易使用。以下为`LAYOUT()`宏数字小键盘的示例：

```c
#define LAYOUT( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, \
    k30, k31, k32, k33, \
    k40,      k42 \
) { \
    { k00, k01, k02, k03, }, \
    { k10, k11, k12, k13, }, \
    { k20, k21, k22, KC_NO, }, \
    { k30, k31, k32, k33, }, \
    { k40, KC_NO, k42, KC_NO } \
}
```

注意`LAYOUT()`宏的第二个空白处是怎么对应对应它下面矩阵扫描数组的？这个宏是将矩阵扫描数组映射到键码。但是，如果你看一个17键数字小键盘，你会发现有三个位置矩阵应该有键子但是没有，因为有长键占住了位置。我们使用`KC_NO`填充那些位置，是因为键映射不需要定义这些地方。

你也可以用这个宏处理非常见矩阵布局，比如[Clueboard rev 2](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/keyboards/clueboard/66/rev2/rev2.h)。本文档不作详细解释。

##### 键码分配

在键映射级别，我们利用上面提到的`LAYOUT()`宏来将键码映射到物理位置和矩阵位置。如下所示:<!--TODO：翻译需改进，或原文问题。原文为：map keycodes to physical locations to matrix locations.-->

```
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
  KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
  KC_P4,   KC_P5,   KC_P6, \
  KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
  KC_P0,            KC_PDOT)
}
```

注意所有的参数如何与最后一部分中的`LAYOUT()`宏的前半部分匹配？这就是我们将一个键码映射到之前的矩阵扫描的方法。<!--译者表示没理解，按字面译的，有更好的请改进。谢谢。-->

##### 状态变化检测

上面的矩阵扫描告诉我们在某个时刻矩阵的状态，但是你的电脑只想知道状态的改变，他才不想知道现在的状态呢。QMK保存最后一次矩阵扫描结果并与本矩阵比较，决定何时某键被按下或被释放。

让我们来看示例。 我们跳到键盘的扫描循环中间来找到我们之前的扫描，如下:

```
{
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
}
```

当我们当前的扫描完成后，就会像这样:

```
{
    {1,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
}
```

比较我们的键映射就能发现按下的键是KC_NLCK。从这里我们调度到`process_record`函数集。<!--TODO：待改进翻译，原文为：From here we dispatch to the `process_record` set of functions-->

<!-- FIXME: Magic happens between here and process_record -->

##### 记录的处理

`process_record()`函数看似简单，但其中隐藏着QMK各级别的重要函数的路由。事件链如下所示，当我们想看键盘/键映射级别的函数时，详见Cluecard(译者注：在keyboards/clueboard/card)。由于`rules.mk`中或其它地方的设置的影响，下方函数只有一部分会包含在最终的固件中。

* [`void process_record(keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/tmk_core/common/action.c#L172)
  * [`bool process_record_quantum(keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/quantum.c#L206)
    * [Map this record to a keycode](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/quantum.c#L226)
    * [`void velocikey_accelerate(void)`](https://github.com/qmk/qmk_firmware/blob/c1c5922aae7b60b7c7d13d3769350eed9dda17ab/quantum/velocikey.c#L27)
    * [`void preprocess_tap_dance(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_tap_dance.c#L119)
    * [`bool process_key_lock(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_key_lock.c#L62)
    * [`bool process_clicky(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_clicky.c#L79)
    * [`bool process_haptic(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/2cee371bf125a6ec541dd7c5a809573facc7c456/drivers/haptic/haptic.c#L216)
    * [`bool process_record_kb(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/keyboards/clueboard/card/card.c#L20)
      * [`bool process_record_user(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/keyboards/clueboard/card/keymaps/default/keymap.c#L58)
    * [`bool process_rgb_matrix(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/rgb_matrix.c#L139)
    * [`bool process_midi(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_midi.c#L81)
    * [`bool process_audio(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_audio.c#L19)
    * [`bool process_steno(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_steno.c#L160)
    * [`bool process_music(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_music.c#L114)
    * [`bool process_tap_dance(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_tap_dance.c#L141)
    * [`bool process_unicode_common(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_unicode_common.c#L169)
      calls one of:
        * [`bool process_unicode(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_unicode.c#L20)
        * [`bool process_unicodemap(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_unicodemap.c#L46)
        * [`bool process_ucis(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_ucis.c#L95)
    * [`bool process_leader(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_leader.c#L51)
    * [`bool process_combo(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_combo.c#L115)
    * [`bool process_printer(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_printer.c#L77)
    * [`bool process_auto_shift(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_auto_shift.c#L94)
    * [`bool process_terminal(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_terminal.c#L264)
    * [Identify and process Quantum-specific keycodes](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/quantum.c#L291)

在这个事件链的任何一步，一个函数(比如`process_record_kb()`)可以`return false`来终止进一步处理。

<!--
#### Mouse Handling

FIXME: This needs to be written

#### Serial Link(s)

FIXME: This needs to be written

#### Visualizer

FIXME: This needs to be written

#### Keyboard state LEDs (Caps Lock, Num Lock, Scroll Lock)

FIXME: This needs to be written

-->

<!--源文件： https://raw.githubusercontent.com/qmk/qmk_firmware/f87908228ab0bcd5302feb5701443b8af708d947/docs/understanding_qmk.md
    源提交哈希：f87908228ab0bcd5302feb5701443b8af708d947-->
<!--翻译时间:20200315-17:55(GMT+8)-->