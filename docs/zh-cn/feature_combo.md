# 组合（Combos）

组合（Combo）特性是用于添加自定义操作的和弦（chord）类型解决方案。它可以让你通过一次点击多个键，来生成不同的效果。打个比方，在一个 combo 周期内，点击 `A` 和 `S` 将替换为点击 `ESC`，或者替换为其他更加复杂的操作。（译注：[chord keyboard](https://en.wikipedia.org/wiki/Chorded_keyboard)，这种键盘，通过很少的按键，组合输出字符或命令，如同乐器中的和弦操作。这里“和弦类型”也是指的这种类似的解决方案。）

你可以在 `rules.mk` 添加 `COMBO_ENABLE = yes` 来启用这一特性。

此外，在 `config.h` 中，你需要通过 `#define COMBO_COUNT 1`（将 1 替换为你需要的数字）指定你使用的 combo 的（按键）个数。也可以不定义它，而是通过指定 `COMBO_LEN` 变量。有一个技巧可以让我们忽略这些变量，稍后揭晓。

然后，在你的 `keymap.c` 文件中，你需要定义一个按键序列，通过 `COMBO_END` 结尾，和一个结构体来列出这些组合键以及他们要执行的结果。

```c
const uint16_t PROGMEM test_combo1[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM test_combo2[] = {KC_C, KC_D, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(test_combo1, KC_ESC),
    COMBO(test_combo2, LCTL(KC_Z)), // 修饰键 keycodes 也支持！
};
```

如果你按 A 和 B 键，将发送“Escape”，按 C 和 D 键发送 Ctrl+Z。

从 [PR#8591](https://github.com/qmk/qmk_firmware/pull/8591/) 后，可以通过 ModTap 键或 LayerTap 键发送 combos。所以在上面的例子中，你可以使用 `LSFT_T(KC_A)` 和 `LT(_LAYER, KC_B)` 也可以正常工作。所以 Home Row 修饰键和 Home Row Combos 同时成为一件事。

现在也可以支持重叠的 combo 了。在以前，你同时按下三个键，会让下面两个 combo 的例子都激活。现在只会激活三个键的那个 combo。

```c
const uint16_t PROGMEM test_combo1[] = {LSFT_T(KC_A), LT(_LAYER, KC_B), COMBO_END};
const uint16_t PROGMEM test_combo2[] = {LSFT_T(KC_A), LT(_LAYER, KC_B), KC_C, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(test_combo1, KC_ESC)
    COMBO(test_combo2, KC_TAB)
};
```

执行更复杂的 keycode 比如 ModTap 或者 LayerTap 现在也支持。

## 例子

如果你想添加一个列表，你可以这样：

```c
enum combos {
  AB_ESC,
  JK_TAB,
  QW_SFT,
  SD_LAYER,
};

const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [AB_ESC] = COMBO(ab_combo, KC_ESC),
  [JK_TAB] = COMBO(jk_combo, KC_TAB),
  [QW_SFT] = COMBO(qw_combo, KC_LSFT)
  [SD_LAYER] = COMBO(sd_combo, MO(_LAYER)),
};
```

为了更复杂的实现，你可以使用 `process_combo_event` 函数增加自定义处理。

另外，这个例子展示了如何不使用 `COMBO_COUNT` 定义。

```c
enum combo_events {
  EM_EMAIL,
  BSPC_LSFT_CLEAR,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // 通过这个替换 COMBO_COUNT 定义！

const uint16_t PROGMEM email_combo[] = {KC_E, KC_M, COMBO_END};
const uint16_t PROGMEM clear_line_combo[] = {KC_BSPC, KC_LSFT, COMBO_END};

combo_t key_combos[] = {
  [EM_EMAIL] = COMBO_ACTION(email_combo),
  [BSPC_LSFT_CLEAR] = COMBO_ACTION(clear_line_combo),
};
/* COMBO_ACTION(x) 等价于 COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case EM_EMAIL:
      if (pressed) {
        SEND_STRING("john.doe@example.com");
      }
      break;
    case BSPC_LSFT_CLEAR:
      if (pressed) {
        tap_code16(KC_END);
        tap_code16(S(KC_HOME));
        tap_code16(KC_BSPC);
      }
      break;
  }
}
```

如果你同时点击 E 和 M 将发送”john.doe@example.com“，以及通过”Backspace“和“左Shift”来清除当前行。你可以通过修改它来做些事情，比如播放歌曲或者修改设置。

值得注意的是，现在 `COMBO_ACTION` 已经不再必须。请看 [PR#8591](https://github.com/qmk/qmk_firmware/pull/8591/)，现在可以通过 combos 来运行你的自定义 keycode。只需要定义自定义 keycode，将其编写在 `process_record_user`，然后通过 `COMBO(<key_array>, <your_custom_keycode>)` 定义 combo 即可。查看 [Macros](feature_macros.md) 中第一个例子。

## 键码（Keycodes）
你可以在使用时启用，禁用以及切换 Combo 特性。对于你需要临时关闭他们的时候很有用，比如玩游戏的时候。下面列出的 keycode 可以在你的 `keymap.c` 中使用。

| keycode   | 描述                      |
| --------- | ------------------------- |
| `CMB_ON`  | 打开 Combo 特性           |
| `CMB_OFF` | 关闭 Combo 特性           |
| `CMB_TOG` | 切换 Combo 特性打开或关闭 |

# 高级配置
These configuration settings can be set in your `config.h` file.

这些配置可以在你的 `config.h` 文件中设置。

## Combo 周期
默认情况，Combo 被识别的超时时间被设置为 50ms。如果 combo 偶尔发生失效，或者你同一时间按下一些键有困难，那你可以改变这个值。举例，`#define COMBO_TERM 40` 将设置 combo 的超时时间为 40ms。

## 缓冲区（Buffer）和状态大小
如果你使用的是很长的 combo，或者你有很多重合的 combo，你可能会遇到缓冲区不够大的问题。在这种情况下，你需要配置缓冲区的大小。请注意，更大的 combo 以及更大的缓冲区，将增加内存的使用。

要定义一个 combo 可以由多少个键组成，可以更改：

| 键数 | 更改项                            |
| ---- | --------------------------------- |
| 6    | `#define EXTRA_SHORT_COMBOS`      |
| 8    | QMK 默认                          |
| 16   | `#define EXTRA_LONG_COMBOS`       |
| 32   | `#define EXTRA_EXTRA_LONG_COMBOS` |

定义 `EXTRA_SHORT_COMBOS` 组合 combo 的内部状态到一个字节中。在某些情况下，这可以节省一些内存。如果不需要，就不要使用它。如果你这么做了，你必须确保没有定义超过 6 个键的 combo。

处理 combo 有两个缓冲区，一个用于按键，另一个用于激活 combo。使用下面的选项来配置这些缓冲区的大小：

| 定义                                | 默认                                            |
| ----------------------------------- | ----------------------------------------------- |
| `#define COMBO_KEY_BUFFER_LENGTH 8` | 8 （ `(EXTRA_)EXTRA_LONG_COMBOS` 给出的键数量） |
| `#define COMBO_BUFFER_LENGTH 4`     | 4                                               |

## 修饰键 Combo
如果一个 combo 被指定为一个修饰键，处理 combo 的时间窗口可以单独延长，区别于一般 combo。默认是关闭的，但是可以通过 `#define COMBO_MUST_HOLD_MODS` 开启，时间窗口可以通过 `#define COMBO_HOLD_TERM 150`（默认：`TAPPING_TERM`）设置。通过 `COMBO_MUST_HOLD_MODS`，你无法点击 combo，这样可以少出错。

## Combo 周期，按住和点击
对每个 combo，当需要按下，或者需要点击时，都可以设置按下触发的时间窗口。

举个例子，当部分（或者所有）的下层键都是 Mod-Tap 或 Layer-Tap 键时，tap-only 的 combo 就很有用。当你点击一个 combo，你得到 combo 的结果。当你按下 combo 并且按住时，combo 不会激活。如同 combo 不存在那样，这些键会分别被处理。

为了使用这些特性，如下的配置项和函数需要被定义。如何得到合适的时间和配置项，留给读者去练习。

| 配置                        | 函数                                                      | 描述                                                         |
| --------------------------- | --------------------------------------------------------- | ------------------------------------------------------------ |
| `COMBO_TERM_PER_COMBO`      | uint16_t get_combo_term(uint16_t index, combo_t \*combo)  | 配置每个 combo 超时窗口（默认： `COMBO_TERM`）               |
| `COMBO_MUST_HOLD_PER_COMBO` | bool get_combo_must_hold(uint16_t index, combo_t \*combo) | 控制一个 combo 应该点击后立刻生效还是需要被按住（默认： `false`） |
| `COMBO_MUST_TAP_PER_COMBO`  | bool get_combo_must_tap(uint16_t index, combo_t \*combo)  | 控制一个 combo 应该在一个 `COMBO_HOLD_TERM` 内只有被按下后生效（默认： `false`） |

举例：
```c
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    // 由 combo->keycode 决定
    switch (combo->keycode) {
        case KC_X:
            return 50;
    }

    // 或者 combo 序号，即，它在枚举中的name
    switch (index) {
        case COMBO_NAME_HERE:
            return 9001;
    }

    // 如果你觉得上面这些有点陌生，你可以通过 chord 中的键来定义，也就是你定义 combo 的那个键数组。
    // 当你的一些 combo 中有相同的键，你还想让他们都有相同的 combo 周期，这样会很有用。
    if (combo->keys[0] == KC_ENT) { // 如果数组中第一个键是 Enter
        return 150;
    }

    return COMBO_TERM;
}

bool get_combo_must_hold(uint16_t index, combo_t *combo) {
    // 和上面一样，通过 keycode，combo 序号，或者 chord 中的键来定义

    if (KEYCODE_IS_MOD(combo->keycode) || 
        (combo->keycode >= QK_MOMENTARY && combo->keycode <= QK_MOMENTARY_MAX) // MO(kc) keycodes
        ) {
        return true;
    }

    switch (index) {
        case COMBO_NAME_HERE:
            return true;
    }

    return false;
}

bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    // 如果你想让所有的 combo 都是 tap-only 的，只需要取消下面一行的注释
    // return true

    // 如果你想所有包含 Mod-Tap/Layer-Tap/Momentary 键在 chord 中的 combo 都是 tap-only 的，可以这样：
    uint16_t key;
    uint8_t idx = 0;
    while ((key = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
        switch (key) {
            case QK_MOD_TAP...QK_MOD_TAP_MAX:
            case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
            case QK_MOMENTARY...QK_MOMENTARY_MAX:
                return true;
        }
        idx += 1;
    }
    return false;

}
```

## 可变长度 Combo
如果你在 `config.h` 中没有定义 `COMBO_COUNT`，这将允许你以编程的方式定义 Combo 数据结构的大小，避免通过 `COMBO_COUNT` 来定义。`COMBO_LEN` 作为取代的变量则必须被赋值。可以被设置类似于 `keymap.c`: `uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(key_combos[0]);` 或者可以在 combo 枚举的最后添加 `COMBO_LENGTH` 然后 `uint16_t COMBO_LEN = COMBO_LENGTH;`，像这样：

```c
enum myCombos {
    ...,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
```
无论方法中是否定义 `COMBO_LEN`，都需要将 `combo_t key_combos[COMBO_COUNT] = {...};` 转换为 `combo_t key_combos[] = {...};`。


## Combo 计时器

通常，计数器会在第一个键按下后开始计时，并在间隔在一个 `COMBO_TERM` 内，按下的随后的键时进行重新计时。像这样输入 Combo 是轻松的，但也比较容易出现失败。

后面的两个选项，可供修改计时器的行为。

### `#define COMBO_STRICT_TIMER`

通过 `COMBO_STRICT_TIMER`，计时器仅在第一个键按下后开始计时。

现在输入 combo 没那么轻松了，你需要确保在一个 `COMBO_TERM` 内按下全部的和弦键。通常错误会减少一些，但如果你快速按下多组 combo，那么后面的 combo 可能不被正确激活。

### `#define COMBO_NO_TIMER`

通过 `COMBO_NO_TIMER`，计时器完全被禁用，combo 在第一个键释放后被激活。这将同时禁用 "must hold" 功能，因为他们根本没有工作。

## 定制化键释放

通过定义 `COMBO_PROCESS_KEY_RELEASE` 以及实现函数 `bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode)`，你可以在 combo 激活后，在任意键上运行你自己的定制化代码。比如，你可以改变 RGB 颜色，激活触觉反馈，以及修改修饰键。

你还可以在函数中，通过 return true 来更早的释放 combo。

下面是一个例子，它将 combo 作为两个修饰键，在不同键释放后，相应的修饰键会被注销掉。

```c
enum combos {
  AB_MODS,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};

combo_t key_combos[] = {
  [AB_MODS] = COMBO(ab_combo, LCTL(KC_LSFT)),
};

bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    switch (combo_index) {
        case AB_MODS:
            switch(keycode) {
                case KC_A:
                    unregister_mods(MOD_MASK_CTRL);
                    break;
                case KC_B:
                    unregister_mods(MOD_MASK_SHIFT);
                    break;
            }
            return false; // 别释放 combo
    }
    return false;
}
```
## 按层区分 combo

假如你使用多个基础层来表示不同的键盘布局，一个用于 QWERTY，另一个用于 Colemak，你可能希望你的 combo 可以在所有层中使用相同的按键位置。定义相同的 combo 在不同的层很冗余，而且消耗更多的内存。解决方案是仅检查一个层的 keycode。

通过 `#define COMBO_ONLY_FROM_LAYER _LAYER_A`，combo 会只检查 `_LAYER_A` 的 keycode，即使当前是  `_LAYER_B` 层。

## 用户回调

除了 keycode，这里有一些函数可以让你设置或者检查一些状态：

|函数   |描述                                                         |
|-----------|--------------------------------------------------------------------|
| `combo_enable()`     | 启用 combo 功能                             |
| `combo_disable()`    | 禁用 combo 功能，并清空 combo 缓冲区 |
| `combo_toggle()`     | 切换 combo 功能的状态   |
| `is_combo_enabled()` | 返回 combo 功能当前状态（true 或 false） |


# 字典管理

当你有很多 combo，在 3 个地方更新你的新 combo 或者修改老的 combo 显得很笨重。我们可以通过一些魔法减轻一些！……如果你认同 C 的宏是魔法。

首先，你需要在 `rules.mk` 中添加 `VPATH += keyboards/gboards`。然后，在 `keymap.c` 文件中添加 `g/keymap_combo.h`。

!> 这个功能使用同一个 `process_combo_event` 函数，就像 `COMBO_ACTION` 那样。所以你不能在你的 keymap 中使用这个函数。作为替代，你需要在 `inject.h` 中自行定义 switch 语句的 case。 `g/keymap_combo.h` 将引用这些函数。

然后，通过如下方式在 `combos.def` 文件中写你的 combo：

```c
//   名称     结果    和弦键
COMB(AB_ESC,   KC_ESC,   KC_A, KC_B)
COMB(JK_TAB,   KC_TAB,   KC_J, KC_K)
COMB(JKL_SPC,  KC_SPC,   KC_J, KC_K, KC_L)
COMB(BSSL_CLR, KC_NO,    KC_BSPC, KC_LSFT) // 使用 KC_NO 作为结果 keycode，和在 COMBO_ACTION 中一样
COMB(QW_UNDO,  C(KC_Z),  KC_Q, KC_W)
SUBS(TH_THE,   "the",    KC_T, KC_H) // SUBS 使用 SEND_STRING 来输出给定字符串
...
```

现在，你可以添加或者修改 combo 仅在一个地方更新了。你甚至不需要更新 `COMBO_COUNT` 或者 `COMBO_LEN` 变量。一切都要小心。魔法！

对于从小到大的已经准备好的 combo 字典，可以参考 http://combos.gboards.ca/。
