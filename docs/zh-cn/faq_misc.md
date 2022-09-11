# 其它 FAQ

<!---
  original document: 0.15.12:docs/faq_misc.md
  git diff 0.15.12 HEAD -- docs/faq_misc.md | cat
-->

## 怎么对键盘进行测试？ :id=testing

测试键盘就简单直接，把每个按键按一遍后确认发送的是正确的就行。也可以使用[QMK配置器](https://config.qmk.fm/#/test/)的测试模式检查键盘，即便这键盘没有运行着QMK。

## 安全措施

你应该不想见到键盘变砖，变得不能再刷写固件。这里给出了一些非常危险（或相反不太危险）的因素。

- 如果你的键盘没有RESET键，在你需要进入DFU模式时，不得不需要用螺丝刀打开后盖去按PCB上的RESET键。
- 把 tmk_core/common 下的文件搞乱的话，容易导致键盘无法使用
- .hex文件太大的话也会引起问题。`make dfu` 会先擦除存储块，再检查固件大小（哎呀，顺序错了），此时发现错误进而导致刷写失败，键盘停留在DFU模式下。
  - 因此，请留意.hex文件尺寸有大小限制，例如在Planck上是十六进制7000（十进制的28672）

```
Linking: .build/planck_rev4_cbbrowne.elf                                                            [OK]
Creating load file for Flash: .build/planck_rev4_cbbrowne.hex                                       [OK]

Size after:
   text    data     bss     dec     hex filename
      0   22396       0   22396    577c planck_rev4_cbbrowne.hex
```

  - 上面的文件大小是22396/577ch, 小于28672/7000h
  - 任何合适的其它.hex文件，都可以尝试加载
  - 在键盘的Makefile中你添加的一些配置也会额外占用空间，在使用BOOTMAGIC_ENABLE,
    MOUSEKEY_ENABLE, EXTRAKEY_ENABLE, CONSOLE_ENABLE, API_SYSEX_ENABLE
    时请留意
- DFU工具/不会/允许bootloader被覆写（除非你往DFU工具上塞自己的东西），这个风险不大。
- EEPROM的写循环一般是 100000（100k）次，不应不停地持续重复地刷写固件，不然很快就烧毁了。

## NKRO 不好使
首先请确保在编译固件时有在**Makefile**中启用 `NKRO_ENABLE`

如果依旧不行，尝试一下 `Magic` **N** 指令（默认是左Shift+右Shift+N），这个指令可以让键盘在**NKRO**和**6KRO**模式间临时切换。有的场景下**NKRO**无法工作必须切换到**6KRO**模式，比如在BIOS中操作时。

如果你的固件编译时指定了 `BOOTMAGIC_ENABLE` ，则需要使用 `BootMagic`**N** 指令（默认是空格+N）。这个配置保存在EEPROM中，断电也会留存。

https://github.com/tmk/tmk_keyboard#boot-magic-configuration---virtual-dip-switch


## 轨迹球需要复位电路 (PS/2鼠标支持)
缺失复位电路的情况下，由于不正确的硬件初始化，可能会导致设备不稳定，具体请参阅TPM754的电路原理图：

- https://geekhack.org/index.php?topic=50176.msg1127447#msg1127447
- https://www.mikrocontroller.net/attachment/52583/tpm754.pdf


## 无法读到大于16的矩阵列
当列数大于16时，在 [matrix.h] 中的 `read_cols()` 中请用 `1UL<<16` 替代 `1<<16`。

在C语言中，对于AVR上的 `1`，会被视作一种[16位]的[整形(int)]类型，因此无法左移超过15位。因此 `1<<16` 的计算结果会错误地变成0。解决办法就是将类型改为[无符号长整形(unsigned long)]类型的 `1UL`。

https://deskthority.net/workshop-f7/rebuilding-and-redesigning-a-classic-thinkpad-keyboard-t6181-60.html#p146279

## 有些额外的按键不好使（系统，音频控制键）
在QMK的 `rules.mk` 中须定义 `EXTRAKEY_ENABLE`

```
EXTRAKEY_ENABLE = yes          # 音频及系统控制
```

## 无法从休眠唤醒

在Windows的**电源管理**的**设备管理**中，检查 `允许该设备唤醒计算机` 选项，同时检查一下BIOS中的相关设置，任意一个按键都应该能将计算机从休眠状态唤醒。

## 在使用Arduino?

**注意Arduino的引脚编号与芯片的引脚编号是不同的**。例如，Arduino的 `D0` 引脚并不是 `PD0`，请对照其电路图检查电路。

- https://arduino.cc/en/uploads/Main/arduino-leonardo-schematic_3b.pdf
- https://arduino.cc/en/uploads/Main/arduino-micro-schematic.pdf

Arduino Leonardo 以及 micro 使用的是**ATMega32U4**因此可以用TMK，但bootloader可能会是个麻烦的问题。

## 启用JTAG

默认情况下，键盘启动后JTAG调试接口就被禁用了。支持JTAG的MCU出场时会带着 `JTAGEN` 保险丝，而键盘因为需要这部分MCU的引脚去控制开关矩阵、LED等功能。

如果你希望启用JTAG，在 `config.h` 中添加定义：

```c
#define NO_JTAG_DISABLE
```

## USB 3兼容性问题
将设备从USB 3.x端口改插到USB 2.0端口能解决一些问题。


## Mac相关兼容性问题
### OS X 10.11 和 Hub
参见: https://geekhack.org/index.php?topic=14290.msg1884034#msg1884034


## BIOS (UEFI) 配置/恢复 (休眠 & 唤醒)/电源循环
有人反馈过他们的键盘在BIOS下或是从休眠状态唤醒后会不可用。

目前这个问题的原因还不清楚，但一些编译选项应该和这个问题有关，你可以在Makefile中禁用 `CONSOLE_ENABLE`, `NKRO_ENABLE`, `SLEEP_LED_ENABLE` 或其他的试一试。

更多信息：
- https://github.com/tmk/tmk_keyboard/issues/266
- https://geekhack.org/index.php?topic=41989.msg1967778#msg1967778
