# 键映射FAQ

<!---
  original document: 0.15.12:docs/faq_keymap.md
  git diff 0.15.12 HEAD -- docs/faq_keymap.md | cat
-->

本页包含人们经常遇到的关于键映射的问题，如果你还没阅读过[键映射概览](zh-cn/keymap.md)，请先阅读一下。

## 我能使用的键码有哪些?
所有可用键码收录在[键码](zh-cn/keycodes.md)页，在有更详尽的文档时，我们会更新这个链接。

所有键码实际定义在[quantum/keycode.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/keycode.h).

## 默认键码是什么?

广为使用的键盘配列有三种——ANSI，ISO及JIS。北美主要使用ANSI，欧洲及非洲主要使用ISO，日本主要使用JIS，其它区域多为ANSI或ISO。这三种配列的键码可查阅：

<!-- Source for this image: https://www.keyboard-layout-editor.com/#/gists/bf431647d1001cff5eff20ae55621e9a -->
![键盘配列示意图](https://i.imgur.com/5wsh5wM.png)

## 如何对复杂的键码指定自定义的名称？

使用更容易理解的自定义的名字去指代一些键码有时很实用，通常我们使用 `#define` 来实现：

```c
#define FN_CAPS LT(_FL, KC_CAPSLOCK)
#define ALT_TAB LALT(KC_TAB)
```

这样键映射代码中就可以使用 `FN_CAPS` 和 `ALT_TAB` 了，可读性好得多。

## 一些按键发生了交换，或是不能用了

QMK有两个功能系列，Bootmagic及指令，都可以让键盘随时变得灵活多变，功能包含但不限于交换Ctrl/Caps、锁定Gui键、交换Alt/Gui、交换Backspace/Backslash、禁用所有按键等。

快速恢复的办法是插入键盘时按住空格+`Backspace`键，这样会重置键盘内存储的设置信息，键盘就会恢复常态。如果问题依旧存在，请参考：

* [Bootmagic](zh-cn/feature_bootmagic.md)
* [指令](zh-cn/feature_command.md) 

## 菜单键（Menu）不可用

现代键盘上，位于 `KC_RGUI` 及 `KC_RCTL` 间的按键实际上叫做 `KC_APP`。原因是该键被发明时，相关标准中已经有了 `菜单（MENU）` 键，因此微软将该键命名为 `APP` 键。

## `KC_SYSREQ` 不可用
请使用截图键码（`KC_PSCREEN` 及 `KC_PSCR`）替代 `KC_SYSREQ`，组合键’Alt + Print Screen‘实际上会被识别为’System request‘。

具体参见[issue #168](https://github.com/tmk/tmk_keyboard/issues/168)以及
* https://en.wikipedia.org/wiki/Magic_SysRq_key
* https://en.wikipedia.org/wiki/System_request

## 电源键不工作

QMK有两个容易让人迷惑的“电源键”键码：HID键盘页的 `KC_POWER`，及用户页的 `KC_SYSTEM_POWER`（或 `KC_PWR`）。

前者只有macOS支持，后者连同 `KC_SLEP` 及 `KC_WAKE` 在所有主流操作系统上都支持，因此使用后者是推荐的做法。在Windows下，按下按键即刻就会生效，而macOS下必须按住直到系统弹出一个对话框。

## 单发修饰键
用来解决我自己的’the‘麻烦，我总是会将’The‘错输入为’the‘或’THe‘，单发Shift键缓解了我的这个麻烦。
https://github.com/tmk/tmk_keyboard/issues/67

## 修饰键/层 卡住了
层切换功能只有在正确配置的情况下，才不会出现卡住修饰键和层的问题。
对于修饰键和层切换操作来讲，必须确保 `KC_TRANS` 在切换到目标layer时正确置位，才能让修饰键正确释放。或者在释放动作中确保返回到了之前的层。

* https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#31-momentary-switching
* https://geekhack.org/index.php?topic=57008.msg1492604#msg1492604
* https://github.com/tmk/tmk_keyboard/issues/248


## 机械锁定式开关支持

该功能支持形如[Alps这款](https://deskthority.net/wiki/Alps_SKCL_Lock)的*机械锁定式开关*，启用该功能须在 `config.h` 中添加如下定义：

```
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
```

启用该功能后，在你的键映射中须改为使用 `KC_LCAP`，`KC_LNUM` 和 `KC_LSCR`。

旧式复古风（vintage style）键盘偶尔能见到锁定式开关，但在现代键盘中见不到了。***因此你基本不会需要这个功能的，直接使用 `KC_CAPS`，`KC_NUM` 和 `KC_SCRL` 就好***

## 输入形如法语中软音'Ç'这样的非ASCII字符

参见[Unicode](zh-cn/feature_unicode.md)功能.

## macOS系统下的 `Fn`

和其它键盘不同，Apple键盘上的Fn有自己的键码...在某种程度上。其占用了基础6KRO HID事件上报中的第六个键码 —— 因此Apple键盘实际上只是5KRO（5键无冲）的。

技术上讲QMK确实能发送这种键码，但这么做需要修改上报事件中Fn键状态的格式。更麻烦的是，只有你的键盘的VID及PID与Apple键盘一致时才会生效。QMK对此提供官方支持可能会有法律风险，换句话说，我们不太可能去这么做的。

具体信息请参见[这个issue](https://github.com/qmk/qmk_firmware/issues/2179)。

## Mac OSX下支持的键有哪些？
你可以通过查阅以下代码确认OSX下支持的键码。

`usb_2_adb_keymap` 数组实现了从 Keyboard/Keypad 页到 ADB 扫描码（OSX内部使用的键码）的转换。

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/Cosmo_USB2ADB.c

以及 `IOHIDConsumer::dispatchConsumerEvent` 负责处理用户页部分。

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/IOHIDConsumer.cpp


## Mac OSX下的JIS键
日语体系的JIS键盘有些特殊键码：`無変換(Muhenkan)`, `変換(Henkan)`, `ひらがな(hiragana)` 在OSX下无法被识别，可以尝试通过以下配置借助 **Seil** 来启用这些键。

* 在PC键盘中启用NFER键
* 在PC键盘中启用XFER键
* 在PC键盘中启用KATAKANA键

https://pqrs.org/osx/karabiner/seil.html


## RN-42蓝牙模块与Karabiner的兼容性问题
Karabiner - Mac OSX系统下的键映射工具 - 默认会忽略RN-42模块的输入事件。须在Karabiner开启相关选项来支持你的键盘。
https://github.com/tekezo/Karabiner/issues/403#issuecomment-102559230
这个问题的其它详细信息参见
https://github.com/tmk/tmk_keyboard/issues/213
https://github.com/tekezo/Karabiner/issues/403


## Esc和<code>&#96;</code>位于同一个键位

参见[Grave Escape](zh-cn/feature_grave_esc.md)功能.

## Mac OSX下的弹出功能
`KC_EJCT` 在OSX下可用。 https://github.com/tmk/tmk_keyboard/issues/250
Windows 10应该是忽略了这个键码，Linux/Xorg能识别到，但默认没有映射处理。

目前尚不清楚Apple键盘上弹出键到底是啥，HHKB在Mac模式下使用 `F20` 来作为弹出键（`Fn+f`），但应该和Apple的弹出键码不是一回事儿。

## 在 `action_util.c` 中的 `weak_mods` 和 `real_mods` 是什么东西？
___待完善的内容___

real_mods保存的是现实的/物理上的修饰键状态，而weak_mods保存的是虚拟的或临时的修饰键状态，且不应该影响到真实的修饰键的状态。

例如你按住了物理键盘上的左shift键，又输入了 ACTION_MODS_KEY(LSHIFT, KC_A)，

在weak_mods下,
* (1) 按住左shift: real_mods |= MOD_BIT(LSHIFT)
* (2) 按下 ACTION_MODS_KEY(LSHIFT, KC_A): weak_mods |= MOD_BIT(LSHIFT)
* (3) 松开 ACTION_MODS_KEY(LSHIFT, KC_A): weak_mods &= ~MOD_BIT(LSHIFT)
real_mods依然保留着修饰键的状态值。

非weak_mods时,
* (1) 按住左shift: real_mods |= MOD_BIT(LSHIFT)
* (2) 按下 ACTION_MODS_KEY(LSHIFT, KC_A): real_mods |= MOD_BIT(LSHIFT)
* (3) 松开 ACTION_MODS_KEY(LSHIFT, KC_A): real_mods &= ~MOD_BIT(LSHIFT)
这时real_mods失去了‘物理键左shift’的状态值。

在键盘事件发送时，weak_mods会与real_mods求逻辑或。
https://github.com/tmk/tmk_core/blob/master/common/action_util.c#L57
