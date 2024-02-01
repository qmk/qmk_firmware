# Mod-Tap

<!---
  original document: 0.15.12:docs/mod_tap.md
  git diff 0.15.12 HEAD -- docs/mod_tap.md | cat
-->

Mod-Tap键 `MT(mod, kc)` 在按住时功能为修饰键，在点击时则是常规键码。举例来讲，可以设计出一个按键，当点击时发送Escape，按下时则作为Control或Shift

修饰键码及`OSM()`将会被缀以`MOD_`前缀，而非`KC_`

|修饰键码  |描述                                        |
|----------|------------------------------------------|
|`MOD_LCTL`|左Control                                 |
|`MOD_LSFT`|左Shift                                   |
|`MOD_LALT`|左Alt                                     |
|`MOD_LGUI`|左GUI (Windows/Command/Meta键)          |
|`MOD_RCTL`|右Control                                 |
|`MOD_RSFT`|右Shift                                   |
|`MOD_RALT`|右Alt (AltGr)                             |
|`MOD_RGUI`|右GUI (Windows/Command/Meta键)          |
|`MOD_HYPR`|Hyper (左Control, Shift, Alt 及 GUI同时按下)|
|`MOD_MEH` |Meh (左Control, Shift, 及 Alt同时按下)      |

可以通过逻辑或进行组合：

```c
MT(MOD_LCTL | MOD_LSFT, KC_ESC)
```

此时按住该键将触发左Control及左Shift，点击将发送Escape。

为了方便配列，QMK已包含一些常见的Mod-Tap：

|键          |别名                                                              |描述                                         |
|------------|-----------------------------------------------------------------|---------------------------------------------|
|`LCTL_T(kc)`|`CTL_T(kc)`                                                      |按住时为左Control，点击时为 `kc`                |
|`LSFT_T(kc)`|`SFT_T(kc)`                                                      |按住时为左Shift，点击时为 `kc`                  |
|`LALT_T(kc)`|`LOPT_T(kc)`, `ALT_T(kc)`, `OPT_T(kc)`                           |按住时为左Alt，点击时为 `kc`                    |
|`LGUI_T(kc)`|`LCMD_T(kc)`, `LWIN_T(kc)`, `GUI_T(kc)`, `CMD_T(kc)`, `WIN_T(kc)`|按住时为左GUI，点击时为 `kc`                    |
|`RCTL_T(kc)`|                                                                 |按住时为右 Control，点击时为 `kc`               |
|`RSFT_T(kc)`|                                                                 |按住时为右 Shift，点击时为 `kc`                 |
|`RALT_T(kc)`|`ROPT_T(kc)`, `ALGR_T(kc)`                                       |按住时为右 Alt，点击时为 `kc`                   |
|`RGUI_T(kc)`|`RCMD_T(kc)`, `RWIN_T(kc)`                                       |按住时为右 GUI，点击时为 `kc`                   |
|`LSG_T(kc)` |`SGUI_T(kc)`, `SCMD_T(kc)`, `SWIN_T(kc)`                         |按住时为左Shift及GUI，点击时为 `kc`             |
|`LAG_T(kc)` |                                                                 |按住时为左Alt及GUI，点击时为 `kc`               |
|`RSG_T(kc)` |                                                                 |按住时为右 Shift及GUI，点击时为 `kc`            |
|`RAG_T(kc)` |                                                                 |按住时为右 Alt及GUI，点击时为 `kc`              |
|`LCA_T(kc)` |                                                                 |按住时为左Control及Alt，点击时为 `kc`           |
|`LSA_T(kc)` |                                                                 |按住时为左Shift及Alt，点击时为 `kc`             |
|`RSA_T(kc)` |`SAGR_T(kc)`                                                     |按住时为右 Shift及右 Alt (AltGr)，点击时为 `kc`  |
|`RCS_T(kc)` |                                                                 |按住时为右 Control及右 Shift，点击时为 `kc`      |
|`LCAG_T(kc)`|                                                                 |按住时为左Control，Alt及GUI，点击时为 `kc`       |
|`RCAG_T(kc)`|                                                                 |按住时为右 Control，Alt及GUI，点击时为 `kc`      |
|`C_S_T(kc)` |                                                                 |按住时为左Control及Shift，点击时为 `kc`          |
|`MEH_T(kc)` |                                                                 |按住时为左Control，Shift及Alt，点击时为 `kc`     |
|`HYPR_T(kc)`|`ALL_T(kc)`                                                      |按住时为左Control，Shift，Alt及GUI，点击时为 `kc` - 更多[参见这里](https://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)|

## 注意

目前 `MT()` 的 `kc`参数限制在[基础键码集](zh-cn/keycodes_basic.md)中，因此不能使用 `LCTL()`，`KC_TILD` 及其它大于 `0xFF` 的键码。原因是，QMK使用16位的键码，其中3位是功能标记，1位标记左右修饰键，4位存储修饰键码，仅剩8位存储键码。当一次Mod-Tap触发时，只要有一个右修饰键被激发，其它的修饰键也都被视为右修饰键，因此无法混搭形如左Control+右Shift的形式，会被视为右Control+右Shift

若展开讲就比较复杂了。迁移到32位的键码可以很大程度解决这个问题，但同时会招致配列矩阵大小翻倍，也可能会有其它未知问题。若是想用修饰键配合按键，可以考虑使用[Tap Dance/多击键](zh-cn/feature_tap_dance.md#example-5-using-tap-dance-for-advanced-mod-tap-and-layer-tap-keys)

在使用Windows远程桌面时你可能会发现有些问题，这是因为远程桌面对键码响应过快。若要修复，可以打开远程桌面的“配置”，在“本地资源”页中的键盘属性，调整为“本地计算器”，此时功能即可恢复正常。另一个办法是加大[`TAP_CODE_DELAY`](zh-cn/config_options.md#behaviors-that-can-be-configured)。

## 截获Mod-Taps

### 改变点击功能

若要在Mod-Tap中突破基础键码的限制，可以在 `process_record_user` 中实现。如，上档键码 `KC_DQUO` 无法与 `MT()` 共用，因为它实际上是 `LSFT(KC_QUOT)` 的别名，`KC_DQUO` 上的修饰键码会被 `MT()` 覆盖。但可以使用如下代码截获点击，手动发送 `KC_DQUO`：

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_DQUO):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_DQUO); // 点击时发送 KC_DQUO
                return false;        // 通过返回false阻止对该键的其它处理
            }
            break;
    }
    return true;
}
```

### 改变按住功能

类似地，同样可以使用这段自定义代码改变按住功能。下面的例子会在 `LT(0, kc)` （layer-tap键无实际意义，因为layer 0默认被激活）按住时对X，C和V键附加剪切，复制和粘贴功能：

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(0,KC_X):
            if (record->tap.count && record->event.pressed) {
                return true;         // 返回true来发送常规键码
            } else if (record->event.pressed) {
                tap_code16(C(KC_X)); // 截获按住功能来发送Ctrl-X
            }
            return false;
        case LT(0,KC_C):
            if (record->tap.count && record->event.pressed) {
                return true;         // 返回true来发送常规键码
            } else if (record->event.pressed) {
                tap_code16(C(KC_C)); // 截获按住功能来发送Ctrl-C
            }
            return false;
        case LT(0,KC_V):
            if (record->tap.count && record->event.pressed) {
                return true;         // 返回true来发送常规键码
            } else if (record->event.pressed) {
                tap_code16(C(KC_V)); // 截获按住功能来发送Ctrl-V
            }
            return false;
    }
    return true;
}
```

### 同时改变点击和按住功能

最后一个例子通过 `LT(0,KC_NO)` 实现了点击复制，按住粘贴的功能：

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(0,KC_NO):
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_C)); // 截获点击来发送Ctrl-C
            } else if (record->event.pressed) {
                tap_code16(C(KC_V)); // 截获按住功能来发送Ctrl-V
            }
            return false;
    }
    return true;
}
```

## 其它信息

在[点按配置](zh-cn/tap_hold.md)中描述了影响Mod-Tap行为的标记。
