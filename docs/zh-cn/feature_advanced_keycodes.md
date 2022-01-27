# 修饰键 :id=modifier-keys

以下这些可以让你通过一个键码来组合一个修饰键。当按下时，触发修饰键keydown，然后 `kc` 会被发送。释放后，触发 `kc` 的keyup事件，然后修饰键被发送。

| 键         | 别名                               | 描述                                                  |
| ---------- | ---------------------------------- | ----------------------------------------------------- |
| `LCTL(kc)` | `C(kc)`                            | 按住左 Control 以及 按下 `kc`                      |
| `LSFT(kc)` | `S(kc)`                            | 按住左 Shift 以及 按下 `kc`                        |
| `LALT(kc)` | `A(kc)`, `LOPT(kc)`                | 按住左 Alt 以及 按下 `kc`                          |
| `LGUI(kc)` | `G(kc)`, `LCMD(kc)`, `LWIN(kc)`    | 按住左 GUI 以及 按下 `kc`                          |
| `RCTL(kc)` |                                    | 按住右 Control 以及 按下 `kc`                     |
| `RSFT(kc)` |                                    | 按住右 Shift 以及 按下 `kc`                       |
| `RALT(kc)` | `ROPT(kc)`, `ALGR(kc)`             | 按住右 Alt 以及 按下 `kc`                         |
| `RGUI(kc)` | `RCMD(kc)`, `LWIN(kc)`             | 按住右 GUI 以及 按下 `kc`                         |
| `LSG(kc)`  | `SGUI(kc)`, `SCMD(kc)`, `SWIN(kc)` | 按住左 Shift 和 GUI 以及 按下 `kc`                |
| `LAG(kc)`  |                                    | 按住左 Alt 和 Left GUI 以及 按下 `kc`             |
| `RSG(kc)`  |                                    | 按住右 Shift 和 Right GUI 以及 按下 `kc`         |
| `RAG(kc)`  |                                    | 按住右 Alt 和 Right GUI 以及 按下 `kc`           |
| `LCA(kc)`  |                                    | 按住左 Control 和 Alt 以及 按下 `kc`              |
| `LSA(kc)`  |                                    | 按住左 Shift 和 Left Alt 以及 按下 `kc`           |
| `RSA(kc)`  | `SAGR(kc)`                         | 按住右 Shift 和 Right Alt (AltGr) 以及 按下 `kc` |
| `RCS(kc)`  |                                    | 按住右 Control 和 Right Shift 以及 按下 `kc`     |
| `LCAG(kc)` |                                    | 按住左 Control, Alt 和 GUI 以及 按下 `kc`         |
| `MEH(kc)`  |                                    | 按住左 Control, Shift 和 Alt 以及 按下 `kc`       |
| `HYPR(kc)` |                                    | 按住左 Control, Shift, Alt 和 GUI 以及 按下 `kc`  |

你还可以叠加它们，比如 `LCTL(LALT(KC_DEL))` 或 `C(A(KC_DEL))` 使得一个按键发送 Control+Alt+Delete 以及一个单键按下。

# 检查修饰键状态 :id=checking-modifier-state

当前修饰键的状态主要通过两个函数来获取：普通修饰键和 modtaps 通过 `get_mods()` 获取，粘滞（one-shot）修饰键（在按住时，它就像普通修饰键）通过 `get_oneshot_mods()` 获取。

一个或多个特定的修饰键在当前修饰键状态中呈现什么状态，可以通过叠加修饰键状态来查看。之所以使用位运算是因为修饰键状态被存储为一个字节，格式是(GASC)<sub>R</sub>(GASC)<sub>L</sub>。

这样，举个例子， `01000010` 在内部表示 LShift + RAlt。

获取更多C语言位运算的信息，可以点击[这里](https://en.wikipedia.org/wiki/Bitwise_operations_in_C)的这个话题的 Wiki 页面。

事实上，这意味着你可以通过 `get_mods() & MOD_BIT(KC_<modifier>)` （了解更多 [修饰键键码列表](keycodes_basic.md#modifiers)）来查看任何给定的修饰键，或者通过 `get_mods() & MOD_MASK_<modifier>` 当左右两边的修饰键区别不重要，你想同时匹配两者时。如果是粘滞修饰键，你可以替换 `get_mods()` 为 `get_oneshot_mods()` 达到相同目的。

当一次仅检查一组特定的修饰键是否有效时，可以对修饰键状态和上面解释过的你期望的 mod mask 进行与运算，然后对比这个结果和 mod mask 本身： `get_mods() & <mod mask> == <mod mask>`。

举个例子，假设你想当左 control 粘滞键和左 shift 粘滞键有效，但是其他所有粘滞键无效时，触发一段自定义代码。这么做，你可以通过组合左 control 和左 shift 的 mod bits 获得你期望的 mod mask，即 `(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT))` ，然后合并为： `get_oneshot_mods & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT)) == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT))`。使用 `MOD_MASK_CS` 指定 mod bitmask 将强制你按下了四个修饰键（左右 control和shift）作为满足条件。

mod masks 完整列表如下：

| Mod Mask 名称    | 匹配修饰键                                     |
| ---------------- | ---------------------------------------------- |
| `MOD_MASK_CTRL`  | LCTRL       , RCTRL                            |
| `MOD_MASK_SHIFT` | LSHIFT      , RSHIFT                           |
| `MOD_MASK_ALT`   | LALT        , RALT                             |
| `MOD_MASK_GUI`   | LGUI        , RGUI                             |
| `MOD_MASK_CS`    | CTRL        , SHIFT                            |
| `MOD_MASK_CA`    | (L/R)CTRL   , (L/R)ALT                         |
| `MOD_MASK_CG`    | (L/R)CTRL   , (L/R)GUI                         |
| `MOD_MASK_SA`    | (L/R)SHIFT  , (L/R)ALT                         |
| `MOD_MASK_SG`    | (L/R)SHIFT  , (L/R)GUI                         |
| `MOD_MASK_AG`    | (L/R)ALT    , (L/R)GUI                         |
| `MOD_MASK_CSA`   | (L/R)CTRL   , (L/R)SHIFT , (L/R)ALT            |
| `MOD_MASK_CSG`   | (L/R)CTRL   , (L/R)SHIFT , (L/R)GUI            |
| `MOD_MASK_CAG`   | (L/R)CTRL   , (L/R)ALT   , (L/R)GUI            |
| `MOD_MASK_SAG`   | (L/R)SHIFT  , (L/R)ALT   , (L/R)GUI            |
| `MOD_MASK_CSAG`  | (L/R)CTRL   , (L/R)SHIFT , (L/R)ALT , (L/R)GUI |

除了使用 `get_mods()` 获取当前有效修饰键外，这里还有一些其他函数你可以使用，来修改修饰键状态，其中 `mods` 参数表示修饰键的 bitmask。

* `add_mods(mods)`: 使 `mods` 生效，不影响其他修饰键
* `register_mods(mods)`: 类似 `add_mods` 但会立刻发送键码报告
* `del_mods(mods)`: 使 `mods` 失效，不影响其他修饰键
* `unregister_mods(mods)`: 类似 `del_mods` 但会立刻发送键码报告
* `set_mods(mods)`: 通过 `mods` 覆盖当前修饰键状态
* `clear_mods()`: 重置所有修饰键状态为失效

相似的，除了 `get_oneshot_mods()`，这里也存在一些函数供粘滞修饰键使用：

* `add_oneshot_mods(mods)`: 使 `mods` 生效，不影响其他粘滞修饰键
* `del_oneshot_mods(mods)`: 使 `mods` 失效，不影响其他粘滞修饰键
* `set_oneshot_mods(mods)`: 通过 `mods` 覆盖当前粘滞修饰键状态
* `clear_oneshot_mods()`: 重置所有粘滞修饰键状态为失效

## 举例 :id=examples

下面的例子使用了 [进阶宏函数](feature_macros.md#advanced-macro-functions) ，还可以通过 [文档页：宏](feature_macros.md) 了解更多。

### Alt + Escape 转换为 Alt + Tab :id=alt-escape-for-alt-tab

一个简单的例子，在应用中将左 Alt +  `KC_ESC` 的行为改变为像 Alt +  `KC_TAB` 一样。这个例子中严格检查是否只有左 Alt 有效，意思是你无法在应用使用相反的顺序（译注：其实并非反序，强调要不多不少且顺序相同），去转换 Alt+Shift+Esc。同时请记住，这里会将触发实际 Alt+Escape 键盘快捷键的效果移除，取而代之为 AltGr+Escape。

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

    case KC_ESC:
        // 仅检查左 alt 键是否激活
        if ((get_mods() & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
            if (record->event.pressed) {
                // 因为 KC_LALT 已经激活，无需注册
                // Alt 修饰键将应用在 KC_TAB 上
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            // 不让 QMK 进一步处理键码
            return false;
        }
        // 或者，让QMK像通常那样处理 KC_ESC 
        return true;

    }
    return true;
};
```

### Shift + Backspace 转换为 Delete :id=shift-backspace-for-delete

一个进阶的例子，将 shift 的默认行为消除，当它和 `KC_BSPC` 一起双击时，整体替换为 `KC_DEL`。引入两个主要变量来实现这一效果： `mod_state` 和 `delkey_registered`。第一个变量存储修饰键状态用在注册  `KC_DEL` 之后。第二个变量是一个布尔变量（true 或 false）它会持续跟踪 `KC_DEL` 的状态，来管理整个 Backspace/Delete 键正确的释放。

和上一个例子相反，这里不使用严格修饰键检查。当一或两个shift有效时按下 `KC_BSPC` 足矣触发如下自定义代码，不用管其他修饰键状态。这带来了一些好处：Ctrl+Shift+Backspace 让我们可以删除下一个字 (Ctrl+Delete) 以及 Ctrl+Alt+Shift+Backspace 让我们执行 Ctrl+Alt+Del 键盘快捷键。

```c
// 初始化变量，代表修饰键二进制状态
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // 存储当前修饰键状态，后面引用
    mod_state = get_mods();
    switch (keycode) {

    case KC_BSPC:
        {
        // 初始化布尔变量，持续跟踪 delete 键状态：注册还是没有？
        static bool delkey_registered;
        if (record->event.pressed) {
            // 检查任意 shift 键状态
            if (mod_state & MOD_MASK_SHIFT) {
                // 首先临时取消两个 shift，所以 shift 不会应用在 KC_DEL 键码上
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                // 更新布尔变量来表示 KC_DEL 状态
                delkey_registered = true;
                // 恢复修饰键状态，因此点击完 Backspace/Delete 键后，shift 键的按下状态仍然可以工作
                set_mods(mod_state);
                return false;
            }
        } else { // KC_BSPC 释放
            // 以防 KC_BSPC 释放后 KC_DEL 仍然被发送
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        // 没有shift时，让QMK像通常那样处理 KC_BSPC
        return true;
    }

    }
    return true;
};
```

# 遗留内容 :id=legacy-content

本页曾经包含很多特性。我们将很多以前在本页的章节迁移到他们独自的页面。下方的所有内容是一个简单的重定向，这样通过旧链接过来的人可以找到他们想要的内容。

## 层 Layers :id=switching-and-toggling-layers

* [Layers](feature_layers.md)

## Mod-Tap :id=mod-tap

* [Mod-Tap](mod_tap.md)

## 粘滞键 One Shot Keys :id=one-shot-keys

* [One Shot Keys](one_shot_keys.md)

## Tap-Hold Configuration Options :id=tap-hold-configuration-options

* [Tap-Hold Configuration Options](tap_hold.md)
