# 动态宏：实时记录宏并回放

<!---
  original document: 0.15.12:docs/feature_dynamic_macros.md
  git diff 0.15.12 HEAD -- docs/feature_dynamic_macros.md | cat
-->

QMK支持动态地创建临时宏，我们称之为动态宏功能。宏将由键盘使用者创建，并在键盘拔出或重启后失效。

你可以创建一或两条宏记录，他们须共享最多128个键的操作记录数上限限制。通过增加内存占用，可以扩大该上限。

要启用该功能，首先在 `rules.mk` 文件中添加 `DYNAMIC_MACRO_ENABLE = yes`，之后在你的键映射中添加如下键：

|键                |别名      |描述                   |
|------------------|----------|---------------------|
|`DYN_REC_START1`  |`DM_REC1` |开始录制1号宏          |
|`DYN_REC_START2`  |`DM_REC2` |开始录制2号宏          |
|`DYN_MACRO_PLAY1` |`DM_PLY1` |重放1号宏             |
|`DYN_MACRO_PLAY2` |`DM_PLY2` |重放2号宏             |
|`DYN_REC_STOP`    |`DM_RSTP` |结束当前宏的录制       |

以上是所有的所需项。

要开始录制宏，点击 `DYN_REC_START1` 或 `DYN_REC_START2`。

要结束宏的录制，点击 `DYN_REC_STOP` 按钮，也可以再次点击 `DYN_REC_START1` 或 `DYN_REC_START2` 来结束录制。

要回放宏，点击 `DYN_MACRO_PLAY1` 或 `DYN_MACRO_PLAY2`。

一段宏允许作为另一段宏的一部分（宏嵌套），你可以在录制1号宏时回放2号宏，反之亦可，但不要让宏记录形成死循环，如在1号宏中回放1号宏。死循环的宏记录将导致键盘不再响应任何操作，这时需重新插拔一下键盘。可以通过在 `config.h` 中定义 `DYNAMIC_MACRO_NO_NESTING` 来完全禁用宏嵌套功能。

?> 若想了解关于动态宏更深入的信息，请阅读 `process_dynamic_macro.h` 及 `process_dynamic_pacro.c` 文件中的注释内容。

## 定制化

我们添加了一些可选项，使得该功能可以在更多的角度上定制化

|定义                        |默认值            |描述                                                         |
|----------------------------|----------------|-------------------------------------------------------------|
|`DYNAMIC_MACRO_SIZE`        |128             |设置动态宏可用的最大内存量。内存空间受限于控制器型号。               |
|`DYNAMIC_MACRO_USER_CALL`   |*未定义*         |通过定义该宏，使得宏行为转为使用用户的 `keymap.c` 文件进行处理。     |
|`DYNAMIC_MACRO_NO_NESTING`  |*未定义*         |通过定义该宏，禁止在一个宏内调用另一个宏（宏嵌套）。                 | 


若录制宏的途中点击按键时LED闪烁，就是在提示宏可用的内存缓存已耗尽。要让宏能成功录制，可以让另一个录制的宏短一些（两者共享一份缓存），或者将 `config.h` 中的 `DYNAMIC_MACRO_SIZE` 值增大（默认值：128；请先阅读头文件中关于它的注释）。


### DYNAMIC_MACRO_USER_CALL

针对于使用更早期的动态宏的使用者：现在仍然可以像以前那样使用层修饰键来作为动态宏键，而无需额外的 `DYN_REC_STOP` 键。若依旧希望使用该功能，在 `config.h` 中添加 `#define DYNAMIC_MACRO_USER_CALL` 并在函数 `process_record_user()` 的起始处添加如下代码段：

```c
	uint16_t macro_kc = (keycode == MO(_DYN) ? DYN_REC_STOP : keycode);

	if (!process_record_dynamic_macro(macro_kc, record)) {
		return false;
	}
```

### 用户态钩子

动态宏功能提供了一些钩子来进行功能定制化以及选项反馈，允许在更多的角度上进行功能定制。

需注意 `direction` 参数的指代意义，`1` 代表1号宏，`-1` 代表2号宏，而 0 表示没有对应的宏。

* `dynamic_macro_record_start_user(void)` - 在开始宏录制时触发。
* `dynamic_macro_play_user(int8_t direction)` - 在回放宏时触发。
* `dynamic_macro_record_key_user(int8_t direction, keyrecord_t *record)` - 录制宏过程中每次点击时触发。
* `dynamic_macro_record_end_user(int8_t direction)` - 宏录制结束时触发。

最后，如果背光功能可用，可以通过调用 `dynamic_macro_led_blink()` 来让其闪烁。
