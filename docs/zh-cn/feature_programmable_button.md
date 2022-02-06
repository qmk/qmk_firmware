## 可编程按键

<!---
  original document: 0.15.20:docs/feature_programmable_button.md
  git diff 0.15.20 HEAD -- docs/feature_programmable_button.md | cat
-->

可编程按键功能可以发送未定义过的按键，这样可以在主机的定制化软件中响应这些点击事件，而不再需要借助操作系统进行处理。

这部分键码来源于 HID 应用表中的“电话设备页”（0x0B），“可编程按键应用”（0x07）。在 Linux（>5.15）系统内这些会被自动处理并转换成 `KEY_MACRO#` 键码。（最大至 `KEY_MACRO30`）

### 启用可编程按键

若要启用可编程按键功能，在 `rules.mk` 文件中添加该行：

```c
PROGRAMMABLE_BUTTON_ENABLE = yes
```

### 键映射

在键映射中可以使用如下键码将键动作映射到可编程按键：

|键                      |描述                   |
|------------------------|----------------------|
|`PROGRAMMABLE_BUTTON_1` |可编程键1              |
|`PROGRAMMABLE_BUTTON_2` |可编程键2              |
|`PROGRAMMABLE_BUTTON_3` |可编程键3              |
|`PROGRAMMABLE_BUTTON_4` |可编程键4              |
|`PROGRAMMABLE_BUTTON_5` |可编程键5              |
|`PROGRAMMABLE_BUTTON_6` |可编程键6              |
|`PROGRAMMABLE_BUTTON_7` |可编程键7              |
|`PROGRAMMABLE_BUTTON_8` |可编程键8              |
|`PROGRAMMABLE_BUTTON_9` |可编程键9              |
|`PROGRAMMABLE_BUTTON_10`|可编程键10             |
|`PROGRAMMABLE_BUTTON_11`|可编程键11             |
|`PROGRAMMABLE_BUTTON_12`|可编程键12             |
|`PROGRAMMABLE_BUTTON_13`|可编程键13             |
|`PROGRAMMABLE_BUTTON_14`|可编程键14             |
|`PROGRAMMABLE_BUTTON_15`|可编程键15             |
|`PROGRAMMABLE_BUTTON_16`|可编程键16             |
|`PROGRAMMABLE_BUTTON_17`|可编程键17             |
|`PROGRAMMABLE_BUTTON_18`|可编程键18             |
|`PROGRAMMABLE_BUTTON_19`|可编程键19             |
|`PROGRAMMABLE_BUTTON_20`|可编程键20             |
|`PROGRAMMABLE_BUTTON_21`|可编程键21             |
|`PROGRAMMABLE_BUTTON_22`|可编程键22             |
|`PROGRAMMABLE_BUTTON_23`|可编程键23             |
|`PROGRAMMABLE_BUTTON_24`|可编程键24             |
|`PROGRAMMABLE_BUTTON_25`|可编程键25             |
|`PROGRAMMABLE_BUTTON_26`|可编程键26             |
|`PROGRAMMABLE_BUTTON_27`|可编程键27             |
|`PROGRAMMABLE_BUTTON_28`|可编程键28             |
|`PROGRAMMABLE_BUTTON_29`|可编程键29             |
|`PROGRAMMABLE_BUTTON_30`|可编程键30             |
|`PROGRAMMABLE_BUTTON_31`|可编程键31             |
|`PROGRAMMABLE_BUTTON_32`|可编程键32             |
|`PB_1` 至 `PB_32`       |可用于键映射的别名       |

### API

`programmable_button.h` 中定义了专用于可以与可编程按键交互的API：

```
void programmable_button_clear(void);
void programmable_button_send(void);
void programmable_button_on(uint8_t code);
void programmable_button_off(uint8_t code);
bool programmable_button_is_on(uint8_t code);
uint32_t programmable_button_get_report(void);
void programmable_button_set_report(uint32_t report);
```
