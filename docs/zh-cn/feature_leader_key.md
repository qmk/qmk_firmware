# 前导键：一种新的修饰键

<!---
  original document: 0.15.16:docs/feature_leader_key.md
  git diff 0.15.16 HEAD -- docs/feature_leader_key.md | cat
-->

如果你有 Vim 的使用经验，应当已经知道什么是前导键（前缀键）了，否则，你将会了解到一个新奇的概念。:) 在你想（同时）按下 Alt+Shift+W 的时候，如果可以改为依次 _按序_ 点击是不是挺好？那么你就需要我们特有的修饰键（前导键）了，依次（快速连续地）按下 W 和 C，神奇的事情就会发生。

这就是 `KC_LEAD` 的功用，这里有一个例子：

1. 在键盘上选择一个键作为前导键，将其键码配置为 `KC_LEAD`。此时该键将专用于此功能 -- 此键将只有该功能，无法用于其他目的。
2. 在 `config.h` 中添加一行 `#define LEADER_TIMEOUT 300`，作为 `KC_LEAD` 超时值的配置。特别地，在点击了 `KC_LEAD` 后，只有特定长度的时间可用于输入前导键序列。值 `300` 表示300毫秒，将该值调大即可增加输入键序列的时间限制。但由于这段时间内的所有键输入都会被拦截掉，因此应该让该值尽量低一些。
   * 默认情况下，该超时是从点击 `KC_LEAD` 之后开始计时，可能对部分人来讲时间有点太短了，因此你可能想延长一下该超时值。另外一个可选的方案是，可以启用 `LEADER_PER_KEY_TIMING` 配置，以允许每次点击都可以重置超时值，既可以让该超时值足够低，又确保可以输入足够长的键序列。在 `config.h` 文件中添加 `#define LEADER_PER_KEY_TIMING` 即可启用该功能。
3. 在 `matrix_scan_user` 函数中，按照如下示例添加代码：

```c
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_F) {
      // 这里可以做你任何想做的事情
      SEND_STRING("QMK is awesome.");
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https://start.duckduckgo.com\n");
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }
}
```

如上所示，有一些可使用的函数，`SEQ_ONE_KEY` 用于单键序列（前导键后仅再输入一个键），而 `SEQ_TWO_KEYS`，`SEQ_THREE_KEYS`，往上到 `SEQ_FIVE_KEYS` 用于更长的序列。

每个函数接受 1 至多个参数。还有一个重点：你可以使用 **键盘上任一层** 的键码，显而易见地是，在前导宏中能捕获这些键码的前提是对应的层需要先处于活跃态。

## 在 `rules.mk` 中添加前导键功能

在 `rules.mk` 中添加如下代码即可简单地启用前导键功能：

```make
LEADER_ENABLE = yes
```

## 单键超时式前导键

相比于设置一个超大的超时时间来应对长序列的前导键序列，同时也为了顾及我们这类没有 200wpm 输入速度能力的人，我们可以将前导键设置为单键超时模式来让每次键输入能有更多的时间窗口来完成键序列的输入。这在利用 tap dance（即：点击一个键多次，如C, C, C）去模拟前导键时特别有用。

要启用该特性，在 `config.h` 中添加如下内容：
```c
#define LEADER_PER_KEY_TIMING
```

之后，建议将 `LEADER_TIMEOUT` 值调整至 300 毫秒或更低。

```c
#define LEADER_TIMEOUT 250
```

此时，下面的情况在即使不到 1000 毫秒的情况下也不会那么难以做到了：

```c
SEQ_THREE_KEYS(KC_C, KC_C, KC_C) {
  SEND_STRING("Per key timing is great!!!");
}
```

## 不会超时的前导键

有时前导键的位置会与你接下来要敲击的键不那么顺手。想象一下你的前导键在键盘外圈上的右上角处，因此你不得不挪动右手才能够到前导键，这会导致即便是你能快速输入剩余序列的绝大部分，在时限内全部顺利输入完成也是有难度的。例如，如果你要输入 `前导键 + asd`，即便因为 `asd` 在主行上因此输入会非常快，但你在抬手去点击前导键后计时便开始，手再放回来去输入就不那么快了。
要想消除这种情况下双手的压力，可以将前导键的超时值设置为无限。此时，在你点击前导键后，等待下一个键输入的时间是无限的，也就可以允许你将手妥当地放置到能够轻松地点击剩下的键的位置上了。
这个无限的超时值仅对前导键生效，因此前例中的 `前导键 + asd` 在点击前导键后到点击 `a` 之前，时限是无限，但在开始输入键序列时超时值（整体或单键）就会再次生效。
这样，你就可以在很短的 `LEADER_TIMEOUT` 时限情况下，拥有充足的时间去摆正手的位置了。

要启用该特性，在 `config.h` 中添加如下内容：
```c
#define LEADER_NO_TIMEOUT
```

## 严格式键处理

默认情况下，记录前导键序列时会过滤处理 [`Mod-Tap`](zh-cn/mod_tap.md) 以及 [`Layer Tap`](zh-cn/feature_layers.md#switching-and-toggling-layers) 功能的键码。即，在你使用 `LT(3, KC_A)` 时，实际会视为 `KC_A` ，这样的逻辑更符合新手用户的心理预期。

同时，这虽然在大部分情况下没有问题，但如果你确实是想在前导序列中使用完整的键码（如上例中的 `LT(3, KC_A)`），可以在 `config.h` 文件中添加 `#define LEADER_KEY_STRICT_KEY_PROCESSING`，即可以不使用过滤策略，之后须提供完整的键码。

## 定制化

前导键额外的还有一些功能流程上的定制化支持，在处理流程中，函数 `leader_start()` 及 `leader_end()` 会在特定时刻被调用。

`leader_start()` 函数会在点击 `KC_LEAD` 键时被调用，`leader_end()` 函数会在前导序列完成时或超时时间到达时被调用。

你可以添加这些函数到代码中（通常为 `keymap.c`）来实现前导键序列的反馈（比如蜂鸣一声或播放一段音乐）。

```c
void leader_start(void) {
  // 开始录制序列
}

void leader_end(void) {
  // 序列录制结束（未检查录制成功与否）
}
```

### 示例

本例会在点击 `KC_LEAD` 时播放（超级）马里奥的”奖命“（one up）音效，在成功完成时播放“全星”（all star）音效，在失败时播放“失败”（rick roll）音效。

```c
bool did_leader_succeed;
#ifdef AUDIO_ENABLE
float leader_start[][2] = SONG(ONE_UP_SOUND );
float leader_succeed[][2] = SONG(ALL_STAR);
float leader_fail[][2] = SONG(RICK_ROLL);
#endif
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    did_leader_succeed = leading = false;

    SEQ_ONE_KEY(KC_E) {
      // Anything you can do in a macro.
      SEND_STRING(SS_LCTL(SS_LSFT("t")));
      did_leader_succeed = true;
    } else 
    SEQ_TWO_KEYS(KC_E, KC_D) {
      SEND_STRING(SS_LGUI("r") "cmd\n" SS_LCTL("c"));
      did_leader_succeed = true;
    }
    leader_end();
  }
}

void leader_start(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_start);
#endif
}

void leader_end(void) {
  if (did_leader_succeed) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_succeed);
#endif
  } else {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_fail);
#endif
  }
}
```
