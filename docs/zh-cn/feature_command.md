#指令

指令，曾经被称为Magic，是一种无需刷机或者拔掉键盘进入[magic引导](zh-cn/feature_bootmagic.md)模式。但是这个功能和[Magic Keycodes](zh-cn/keycodes_magic.md)功能之间有很大的相似性。如果条件允许，我们推荐您使用[Magic Keycodes](zh-cn/keycodes_magic.md)，而不是指令功能。

对于一些键盘指令功能是默认被禁用的。如果您的键盘符合这种情况，您可以通过添加以下代码到您的 `rules.mk` 文件中来开启指令功能。

```mk
COMMAND_ENABLE = yes
```

#使用

您可以通过组合键的方式来启用指令模式，组合键是由 `IS_COMMAND()` 方法来定义的。 默认情况下，设定的是同时按住左`shift` 和 右 `shift` 进入指令模式。之后，您只需要按下所需功能对应的按键即可。例如，如果您想要在QMK工具箱控制台中显示当前QMK的版本信息，请按下左 `shift` 、`shift` 和 `V` 。

#配置

如果您想要指令模式下的按键绑定，可以通过在键盘级或者键盘布局级的 `config.h` 文件中添加 `#define` 命更改按键绑定。此处使用的所有键码分配必须具有 `KC_` 前缀。

|设定项                               |默认                             |描述                                             |
|------------------------------------|--------------------------------|------------------------------------------------|
|`IS_COMMAND()`                      |`(get_mods() == MOD_MASK_SHIFT)`|激活指令模式的组合键                                |
|`MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS` |`true`                          |用功能键行设置默认键盘布局层                         |
|`MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS` |`true`                          |用数字键行设置默认键盘布局层                         |
|`MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM`|`false`                         |通过 `MAGIC_KEY_LAYER0..9` 设置默认键盘布局层       |
|`MAGIC_KEY_DEBUG`                   |`D`                             |开关串行调试                                      |
|`MAGIC_KEY_DEBUG_MATRIX`            |`X`                             |开关键矩阵调试                                    |
|`MAGIC_KEY_DEBUG_KBD`               |`K`                             |开关键盘调试                                      |
|`MAGIC_KEY_DEBUG_MOUSE`             |`M`                             |开关鼠标调试                                      |
|`MAGIC_KEY_CONSOLE`                 |`C`                             |开启按键控制台                                     |
|`MAGIC_KEY_VERSION`                 |`V`                             |在控制台上显示当前QMK版本信息                        |
|`MAGIC_KEY_STATUS`                  |`S`                             |在控制台上显示当前键盘状态                           |
|`MAGIC_KEY_HELP`                    |`H`                             |在控制台上显示指令帮助信息                           |
|`MAGIC_KEY_HELP_ALT`                |`SLASH`                         |在控制台上显示指令帮助信息 (备用)                     |
|`MAGIC_KEY_LAYER0`                  |`0`                             |设定第0层为默认层                                  |
|`MAGIC_KEY_LAYER0_ALT`              |`GRAVE`                         |设定第0层为默认层 (备用)                            |
|`MAGIC_KEY_LAYER1`                  |`1`                             |设定第1层为默认层                                  |
|`MAGIC_KEY_LAYER2`                  |`2`                             |设定第2层为默认层                                  |
|`MAGIC_KEY_LAYER3`                  |`3`                             |设定第3层为默认层                                  |
|`MAGIC_KEY_LAYER4`                  |`4`                             |设定第4层为默认层                                  |
|`MAGIC_KEY_LAYER5`                  |`5`                             |设定第5层为默认层                                  |
|`MAGIC_KEY_LAYER6`                  |`6`                             |设定第6层为默认层                                  |
|`MAGIC_KEY_LAYER7`                  |`7`                             |设定第7层为默认层                                  |
|`MAGIC_KEY_LAYER8`                  |`8`                             |设定第8层为默认层                                  |
|`MAGIC_KEY_LAYER9`                  |`9`                             |设定第9层为默认层                                  |
|`MAGIC_KEY_BOOTLOADER`              |`B`                             |转跳到引导模式                                     |
|`MAGIC_KEY_BOOTLOADER_ALT`          |`ESC`                           |转跳到引导模式 (备用)                              |
|`MAGIC_KEY_LOCK`                    |`CAPS`                          |锁定键盘，因此不输出按下的任何东西                    |
|`MAGIC_KEY_EEPROM`                  |`E`                             |将EEPROM存储的设置 到控制台                         |
|`MAGIC_KEY_EEPROM_CLEAR`            |`BSPACE`                        |清空EEPROM                                       |
|`MAGIC_KEY_NKRO`                    |`N`                             |开关N键无冲 (NKRO)                                |
|`MAGIC_KEY_SLEEP_LED`               |`Z`                             |开关电脑睡眠的时的LED                              |