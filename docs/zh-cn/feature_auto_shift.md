# Auto Shift：我们为什么需要一个 Shift 键？

按下一个键你将得到它的字符。按下一个键，但是按住 *稍微* 长一会，你得到它的 shift 状态。瞧！我们不需要 shift 键！

## 为什么需要 Auto Shift？

很多人遭受各种形式的重复性劳损（RSI）。一个共同的原因是重复的长距离使用手指。在我们使用键盘时，当要按下 shift 键时，小指就会经常这样做。Auto Shift 看起来可以缓解这个问题。

## 它是如何工作的？

当你按下一个键，在释放之前，它会保持一小段时间的按下状态。这个按下的时间，对每个人来说长短不同。Auto Shift 定义了一个常量 `AUTO_SHIFT_TIMEOUT`，它是你正常按下时间的两倍。当你按下一个键，一个计时器启动，如果你在 `AUTO_SHIFT_TIMEOUT` 时间内没有释放按键，此键以 shift 后状态发送。如果时间小于 `AUTO_SHIFT_TIMEOUT`，或者你按下了其他键，此键以正常状态发送。

如果 `AUTO_SHIFT_REPEAT` 被定义，将支持重复发送按键。按住某键会重复发送其 shift 状态，你可以通过 `AUTO_SHIFT_NO_AUTO_REPEAT` 来禁用。如果你想重复正常状态，按下一次之后再马上按住（在 `TAPPING_TERM` 时间内）（如果 auto-repeat 被禁用，这也可以作用于 shift 状态后的值）。

这里还提供了两个函数来进行更细粒度的控制，`get_auto_shift_repeat`  和  `get_auto_shift_no_auto_repeat`。只有当 `AUTO_SHIFT_REPEAT_PER_KEY` 或 `AUTO_SHIFT_NO_AUTO_REPEAT_PER_KEY` 被定义时才能起作用。

## Auto shift 有什么局限性吗？

很遗憾，有。

1. 你可能得到某些字符的 shift 状态，但你不想要，或者某些字符你想要它们的 shift 状态，但是没有得到。这可以简单地归结为多练习。有时候着急，感觉已经按下了足够长的时间可以得到 shift 状态，其实没有。另一方面，我们感觉只是点按了一下键，但实际上已经按下超过预期的时间了。
2. 另外，在键重复时，可能搞混 shift 状态。它总是取决于最后按下的键。比如，重复发送一个大写字母，然后按下一个小写的键（无论是否为 Auto Shift 键）都会使那个大写字母的键仍被按住，但不是 shift 状态。
3. Auto Shift 不支持 Tap Hold 键。如果要自动 shift Tap Hold 键，可以查看 [Retro Shift](#retro-shift)。

## 如何启用 Auto Shift？

在 keymap 目录 `rules.mk` 中添加：

    AUTO_SHIFT_ENABLE = yes

如果 `rules.mk` 不存在，可以创建一个新的。

然后编译和安装带有 Auto Shift 的新固件！就是这样！

## 修饰键

默认情况下，Auto Shift 伴随一个或多个修饰键时，是禁用的。就是说，Ctrl+A 你按下了一个很长的时间也不等同于 Ctrl+Shift+A。

你可以重启修饰键的 Auto Shift 通过在 `config.h` 增加如下定义：

```c
#define AUTO_SHIFT_MODIFIERS
```

这样，Ctrl+A 按下 `AUTO_SHIFT_TIMEOUT` 时间，会被发送为 Ctrl+Shift+A


## 配置 Auto Shift

必要时，这里有一些配置项可以改变 Auto Shift的行为。通过配置在 keymap 目录下的 `config.h` 文件中的一系列变量来完成。如果没有 `config.h` 文件，你可以新建一个。

一个样例：

```c
#pragma once

#define AUTO_SHIFT_TIMEOUT 150
#define NO_AUTO_SHIFT_SPECIAL
```

### AUTO_SHIFT_TIMEOUT （单位为 ms）

它控制在得到一个 shift 状态前，你最多可以按下一个键多久。显然，这个值因人而异。对大多数人，设置 135-150 比较适宜。然而，一开始的值应该至少是 175，这也是默认值。然后从此值慢慢减小。我们的想法是获取最短的能够得到 shift 状态的时间，并且不出错。

调整这个值直到一切变得完美。许多人发现在给定值的情况下所有键工作正常，但某些时候总有一两个键（错误的）发送 shift 状态。这是习惯造成的，按下某些键比其他键时间稍长一些。当你发现时，你可以比平时更快的按下这些出问题的键，这将会被设置好。

?> Auto Shift 有三个特殊键可以帮助你快速设置正确的值。详见“Auto Shift Setup”！

你可以在 `config.h` 添加如下配置，获取更细粒度的控制：

```c
#define AUTO_SHIFT_TIMEOUT_PER_KEY
```

你可以接着在 keymap 中添加下面的函数：

```c
uint16_t get_autoshift_timeout(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case AUTO_SHIFT_NUMERIC:
            return 2 * get_generic_autoshift_timeout();
        case AUTO_SHIFT_SPECIAL:
            return get_generic_autoshift_timeout() + 50;
        case AUTO_SHIFT_ALPHA:
        default:
            return get_generic_autoshift_timeout();
    }
}
```

注意，你不能覆盖存在于其中任何一个你正在使用的组中的个别键。比如在上面例子中，增加 `KC_A` 将不会编译，因为存在 `AUTO_SHIFT_ALPHA`。一个可行的解决方法是，在上面增加第二个 switch 来承载这些个别键，但不要定义 default 块，而且只能引用下方 switch 中 fallback 中的组（译注：fallback 应该指的是 default 块中处理的部分）。

### NO_AUTO_SHIFT_SPECIAL（简单定义）

特殊键不设置 Auto Shift，它们包括 -\_, =+, [{, ]}, ;:, '", ,<, .>,
and /?

### NO_AUTO_SHIFT_NUMERIC（简单定义）

数字键不设置 Auto Shift，包括0 到 9。

### NO_AUTO_SHIFT_ALPHA（简单定义）

字母键不设置 Auto Shift，包括 A 到 Z。

### Auto Shift 每个键

这里有几个函数允许你决定哪些键可以设置 Auto Shift，很像 tap-hold 键。

第一个函数 `get_custom_auto_shifted_key` 用来简单添加一个键 Auto Shift：

```c
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
            return true;
        default:
            return false;
    }
}
```

`get_auto_shifted_key` 提供更细粒度支持。默认函数如下：

```c
bool get_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#    ifndef NO_AUTO_SHIFT_ALPHA
        case KC_A ... KC_Z:
#    endif
#    ifndef NO_AUTO_SHIFT_NUMERIC
        case KC_1 ... KC_0:
#    endif
#    ifndef NO_AUTO_SHIFT_SPECIAL
        case KC_TAB:
        case KC_MINUS ... KC_SLASH:
        case KC_NONUS_BACKSLASH:
#    endif
            return true;
    }
    return get_custom_auto_shifted_key(keycode, record);
}
```

这些功能默认可用，无需额外定义。

### AUTO_SHIFT_REPEAT（简单定义）

启用键重复

### AUTO_SHIFT_NO_AUTO_REPEAT（简单定义）

超过 `AUTO_SHIFT_TIMEOUT` 但不启用按键重复。

## 自定义 Shift 值

特别是在一些小键盘上，默认的 shift 值在很多键上表现不好。为了提供更多的定制化，这里有两个用户可定义函数，`autoshift_press/release_user`。它们为传递的键注册或取消注册正确的值。下面是一个例子，添加句号为 Auto Shift 然后使它的 shift 状态为感叹号。确保使用 weak mods，设置为 real 将使得任何追加的键使用他们的 shift 值，只要你按住这个键。清除修饰键是由 Auto Shift 处理的，如果你重复按了多个键，操作系统总是发送最后按下的键的 shift 值（无论是否为 Auto Shift 键）。

只要你不设置 shift 修饰键，你也可以得到非 shift 键的 shift 值（甚至得到非 shift 值）。

```c
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
            return true;
        default:
            return false;
    }
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
            register_code16((!shifted) ? KC_DOT : KC_EXLM);
            break;
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF 获取 Tap Holds 中的 Tap 键，使用 Retro Shift 时需要
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
            unregister_code16((!shifted) ? KC_DOT : KC_EXLM);
            break;
        default:
            // & 0xFF 获取 Tap Holds 中的 Tap 键，使用 Retro Shift 时需要
            // IS_RETRO 检查在这里并不是必须的，全部替换为 keycode & 0xFF 也可以。
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}
```

## Retro Shift

按住然后释放一个 Tap Hold 键，并且没有按下其他键，通常结果只有按住（触发的行为）。通过启用 `retro shift` ，这个行为将会在键释放的时候替换为它的 shift 值。

它不依赖 [Retro Tapping](tap_hold.md#retro-tapping) 被启用，如果两者都启用，`retro tapping` 的状态仅适用于按下的键不是 Auto Shift。`RETRO_TAPPING_PER_KEY` 和它相应的函数在 `retro shift` 生效之前被检查。

在 `config.h` 中添加如下配置启用 `retro shift`：

```c
#define RETRO_SHIFT
```

如果 `RETRO_SHIFT` 被赋值，按住时间超过这个值，对于 Mod Tap 将不处理为按下并释放，而是替换触发为它的按住行为。它使得被按住的修饰键可以组合鼠标点击，而不是释放之后产生按键。比如：

```c
#define RETRO_SHIFT 500
```

这个值（如果设置过）必须大于 `TAPPING_TERM`，按键被 `process_tapping` 认定为“按住”状态必须在发送为修饰键之前。对于普通键的 `AUTO_SHIFT_TIMEOUT` 则无此限制。

### Retro Shift 和 Tap Hold 配置项

Tap Hold 配置项在使用 Retro Shift 时有一点不同。引用 `TAPPING_TERM` 没有多大意义，因为按住超过这个时间将得到一个键的 shift 状态结果。

`IGNORE_MOD_TAP_INTERRUPT` 仅当 mod tap 时改变（要先释放），发送两个键，而不是修饰键加第二个键。它在嵌套点击被忽略时生效。

嵌套点击会被更改为如同 `PERMISSIVE_HOLD` 被设置，除非 `IGNORE_MOD_TAP_INTERRUPT` 在 Retro Shift 范围外，并且 Retro Shift 忽略 `IGNORE_MOD_TAP_INTERRUPT`， `PERMISSIVE_HOLD` 对 Mod Tap 没有影响。

在 Mod 和 Layer Tap 键中嵌套点击，总是表现的像是超过了 `TAPPING_TERM`。

## 使用 Auto Shift Setup

这将允许你定义三个键来临时增加、减少以及打印你的 `AUTO_SHIFT_TIMEOUT`。

### Setup

在你的 keymap 中临时定义三个键：

| 键名称   | 描述                               |
| -------- | ---------------------------------- |
| KC_ASDN  | 减小 Auto Shift 超时时间参数（下） |
| KC_ASUP  | 增加 Auto Shift 超时时间参数（上） |
| KC_ASRP  | 打印当前 Auto Shift 超时时间数值   |
| KC_ASON  | 打开 Auto Shift 函数               |
| KC_ASOFF | 关闭 Auto Shift 函数               |
| KC_ASTG  | 切换 Auto Shift 特性的状态         |

编译以及上传你的新固件。

### 使用

请注意，在进行下面测试时，你应该非常自然的点击，并且没有意图触发按键的 shift 状态。

1. 在字母表字母范围内输出多行句子。
2. 留意所有的大写字母。
3. 如果没有，按下你设置为 `KC_ASDN` 的按键来减少 Auto Shift 的超时时间的值，然后返回步骤1。
4. 如果有一些大写字母，请自己决定你应该在按这些键时，减少超时时间还是增加超时时间。
5. 如果你决定增加超时时间，按下你设置为 `KC_ASUP` 的按键，然后返回步骤1。
6. 当你满意自己的设置，按下你设置为 `KC_ASRP` 的键。键盘将打印你设置的 `AUTO_SHIFT_TIMEOUT`。
7. 在 `config.h` 中更新 `AUTO_SHIFT_TIMEOUT` 为刚才打印的时间。
8. 在 `config.h` 中添加 `AUTO_SHIFT_NO_SETUP`。
9. 移除绑定了 `KC_ASDN`， `KC_ASUP` 和 `KC_ASRP` 的按键。
10. 编译以及上传你的新固件。

#### 一个测试例子

    hello world. my name is john doe. i am a computer programmer playing with
    keyboards right now.
    
    [按下 KC_ASDN 一段时间]
    
    heLLo woRLd. mY nAMe is JOHn dOE. i AM A compUTeR proGRaMMER PlAYiNG witH
    KEYboArDS RiGHT NOw.
    
    [按下 KC_ASUP 一段时间]
    
    hello world. my name is john Doe. i am a computer programmer playing with
    keyboarDs right now.
    
    [按下 KC_ASRP]
    
    115

键盘打印 `115`，代表你当前的 `AUTO_SHIFT_TIMEOUT` 值。你现在可以设置它！稍微练习一下在测试中展示的 D 键（译注：应该指 KC_ASDN 键），你会成功的！
