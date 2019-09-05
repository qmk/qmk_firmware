# 布局常见问题

本页本页包含人们经常遇到的关于布局的问题。如果你觉得没什么问题，请先看[布局概览](keymap.md)。

## 我能用什么键码?
看[键码](keycodes.md)你可以找到你能用的键码索引。可以的话这些链接可以连接到更广泛的文档。

键码实际上定义在[common/keycode.h](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/keycode.h).

## 默认的键码什么样?

世界上有三种标准键盘设计，分别是：ANSI, ISO, and JIS. 主要是北美用ANSI(译者注：中国很多键盘使用这个), 欧洲和非洲主要使用ISO，日本使用JIS。未提及的区域通常使用ANSI或ISO。与这些设计对应的键代码如下所示：

<!-- 该图片的来源: http://www.keyboard-layout-editor.com/#/gists/bf431647d1001cff5eff20ae55621e9a -->
![键盘设计图](https://i.imgur.com/5wsh5wM.png)

## 我有一些键变成了其他功能或者不工作了

QMK有两个功能，Bootmagic和命令行，它允许您在运行中更改键盘的行为。该功能包括但不仅限于, 交换Ctrl/Caps，关闭界面，交换Alt/Gui，交换 Backspace/Backslash，禁用所有键，以及其他的行为改变。

快速解决方法是插入键盘时按住`Space`+`Backspace`。该操作将重置已保存设置，让这些键回复初始功能。这招不好用的话参阅下方：

* [Bootmagic](feature_bootmagic.md)
* [命令](feature_command.md) 

## 菜单键不好用

现在大多数键盘 `KC_RGUI`和`KC_RCTL`中间的键子叫做`KC_APP`。这是因为在这个键子发明之前相关标准里就已经有键叫做`MENU(菜单)`了，所以微软叫他`APP(应用)`键。

## `KC_SYSREQ` 不工作
使用抓屏的键码(`KC_PSCREEN`或`KC_PSCR`)而不用`KC_SYSREQ`。组合键'Alt + Print Screen'会被当作'System request'。

见[issue #168](https://github.com/tmk/tmk_keyboard/issues/168)和
* http://en.wikipedia.org/wiki/Magic_SysRq_key
* http://en.wikipedia.org/wiki/System_request

## 电源键不工作

这有点让人困惑,QMK有两个"Power(电源)"键码: `KC_POWER` 在键盘/小键盘的HID使用页面中，`KC_SYSTEM_POWER` (或者叫`KC_PWR`)在用户页。

前者只能被macOS识别，但是后者，即`KC_SLEP`和`KC_WAKE`三大主要操作系统全都支持，所以推荐使用这两个。Windows下这些键立即生效，macOS要长按直到弹出对话框。

## 自动大小写锁定
可以解决'the'问题(正常应为The)。我经常在输入'The'时不慎输入了'the'或者'THe'。自动大小写锁定可以修正此类问题。详见下方链接。
https://github.com/tmk/tmk_keyboard/issues/67

## 修改 键/层 卡住
除非正确配置层切换，否则修改键或层可能会卡住。
对于修改键和图层操作，必须把`KC_TRANS`放到目标层的相同位置，用于注销修改键或在释放事件时返回到上一层。
* https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#31-momentary-switching
* http://geekhack.org/index.php?topic=57008.msg1492604#msg1492604
* https://github.com/tmk/tmk_keyboard/issues/248


## 机械自锁开关支持Mechanical Lock Switch Support

本功能用于*机械自锁开关*比如[this Alps one](http://deskthority.net/wiki/Alps_SKCL_Lock)。你可以通过向`config.h`添加以下宏来使能该功能：

```
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
```

在使能该功能后，要在键盘中使用`KC_LCAP`, `KC_LNUM` 和 `KC_LSCR`这三个键码。

远古机械键盘偶尔会有自锁机械开关，现在几乎没有了。***大多数情况下你不需要使用该功能，且要使用`KC_CAPS`, `KC_NLCK`和`KC_SLCK`这三个键码。***

## 输入ASCII之外的特殊字符比如Cédille 'Ç'
没有在所有系统中输入这个的通用方法。你要定义针对你的特定操作系统或布局的**宏**。

比如看这个**宏**代码的文章。

http://deskthority.net/workshop-f7/tmk-keyboard-firmware-collection-t4478-120.html#p195620
<!--翻译问题：下方维基百科链接应全部替换为中文链接，暂未找到全部-->
在**Windows**上，可以用`AltGr`键或**Alt码**。
* http://en.wikipedia.org/wiki/AltGr_key
* https://zh.wikipedia.org/wiki/Alt%E7%A0%81

在**Mac OS**定义`Option`键组合。
* https://zh.wikipedia.org/wiki/Option%E9%94%AE#%E6%9B%BF%E4%BB%A3%E9%94%AE%E7%9B%98%E8%BE%93%E5%85%A5

在**Xorg**可以改用`compose`键。
* http://en.wikipedia.org/wiki/Compose_key

下方链接查看**Unicode**输入。
* http://en.wikipedia.org/wiki/Unicode_input

## macOS上的`Fn` 

不像大多数FN键，苹果上那个有自己的键码...呃，基本上算吧。 他取缔了基本6键无冲HID报告的第六个键码 -- 所以苹果键盘其实是5键无冲的。

技术上说QMK可以发送这个键。但是，这样做需要修改报告格式以添加FN键的状态。这还不是最糟糕的，你的键盘的VID和PID和真的苹果键盘不一样的话还不会被识别。
QMK官方支持这个会被律师函的，所以就当我没说过。

详见[issue#2179](https://github.com/qmk/qmk_firmware/issues/2179)。


## Mac OSX的媒体控制键
#### KC_MNXT 和 KC_MPRV 在Mac上不好用
使用 `KC_MFFD`(`KC_MEDIA_FAST_FORWARD`) 和 `KC_MRWD`(`KC_MEDIA_REWIND`)，不要用 `KC_MNXT` 和 `KC_MPRV`.
详见 https://github.com/tmk/tmk_keyboard/issues/195


## Mac OSX中支持那些键?
你可以从此源码中获知在OSX中支持哪些键码

`usb_2_adb_keymap` 阵列映射 键盘/小键盘 页用于ADB扫描码(OSX内部键码).

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/Cosmo_USB2ADB.c

`IOHIDConsumer::dispatchConsumerEvent`会处理用户页面用法。
<!--翻译问题：上面那两句翻译的不好-> handles Consumer page usages. -->
https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/IOHIDConsumer.cpp


## Mac OSX中的JIS键
岛国特别键比如`無変換(Muhenkan)`, `変換(Henkan)`, `ひらがな(hiragana)`OSX是不是别的。You can use **Seil** to enable those keys, try following options.
<!--翻译问题：以上“岛国特别键”没有任何地域歧视的意思 -->
* 在电脑键盘上使能NFER键
* 在电脑键盘上使能XFER键
* 在电脑键盘上使能KATAKAN键

https://pqrs.org/osx/karabiner/seil.html


## RN-42蓝牙模块与Karabiner不能有效协同工作
Karabiner - Mac OSX的改键软件 - 默认RN-42模块是不会被响应的。想要Karabiner和你的键盘协同工作你要使能此选项：
https://github.com/tekezo/Karabiner/issues/403#issuecomment-102559237

此问题详见下方链接。
https://github.com/tmk/tmk_keyboard/issues/213
https://github.com/tekezo/Karabiner/issues/403


## Esc 和 <code>&#96;</code> 双功能键

请见[Grave Escape](feature_grave_esc.md)功能。

## 右侧双角色修改键(诸如Shift、Alt等有修改其他键作用的键)变箭头键
右侧修改键单击时会变为箭头键，长按就还是修改键。在TMK中双角色键称之为**TAP**.
```

#include "keymap_common.h"


/* 用TMK双角色键功能实现右侧修改键改箭头键
 *
 *  https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#213-modifier-with-tap-keydual-role
 *  https://en.wikipedia.org/wiki/Modifier_key#Dual-role_keys
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    [0] = LAYOUT( \
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, NUHS,BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT,  \
        LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,FN0, ESC, \
        FN4, LGUI,LALT,          SPC,                     APP, FN2, FN1, FN3),
    [1] = LAYOUT( \
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,\
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN5, TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,FN7, FN6, FN8),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_UP),
    [1] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_DOWN),
    [2] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_LEFT),
    [3] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_RIGHT),
    [4] = ACTION_LAYER_MOMENTARY(1),
    [5] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_PGUP),
    [6] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_PGDN),
    [7] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_HOME),
    [8] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_END),
};

```

双角色键说明: https://en.wikipedia.org/wiki/Modifier_key#Dual-role_keys


## Mac OSX的弹出键
`KC_EJCT` 键码在OSX可以使用 https://github.com/tmk/tmk_keyboard/issues/250
似乎Windows10会忽略该键码，Linux/Xorg可以识别该键码但默认不映射。

目前尚不清楚如何在真正的苹果键盘按出弹出键。HHKB使用`F20`用于弹出键(`Fn+f`)，该功能在MAC模式有效但不保证与苹果弹出键码相符。


## `action_util.c`中的 `weak_mods`和`real_mods`是什么
___待改善___

real_mods 用于保存实际(物理)修改键的实际状态。
weak_mods 用于保存虚拟或临时修改键，它将不会影响实际修改键。

以按下左侧Shift键然后输入ACTION_MODS_KEY(LSHIFT, KC_A)为例，

在weak_mods时，
* (1) 按下不抬起左Shift: real_mods |= MOD_BIT(LSHIFT)
* (2) 按 ACTION_MODS_KEY(LSHIFT, KC_A): weak_mods |= MOD_BIT(LSHIFT)
* (3) 抬起 ACTION_MODS_KEY(LSHIFT, KC_A): weak_mods &= ~MOD_BIT(LSHIFT)
real_mods 还是保持在修改状态。

在没有weak_mods时，
* (1) 按下不抬起左Shift: real_mods |= MOD_BIT(LSHIFT)
* (2) 按 ACTION_MODS_KEY(LSHIFT, KC_A): real_mods |= MOD_BIT(LSHIFT)
* (3) 抬起 ACTION_MODS_KEY(LSHIFT, KC_A): real_mods &= ~MOD_BIT(LSHIFT)
此时real_mods失去‘实际左Shift’的状态。

weak_mods和real_mods现已全部加入键盘数据包发送豪华套餐。
https://github.com/tmk/tmk_core/blob/master/common/action_util.c#L57
