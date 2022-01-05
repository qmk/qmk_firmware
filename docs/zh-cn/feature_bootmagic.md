#Magic引导 (精简版)

<!---
  original document: 0.15.12:docs/feature_bootmagic.md
  git diff 0.15.12 HEAD -- docs/feature_bootmagic.md | cat
-->

Magic引导 (精简版)的功能只局限于如何进入引导模式。如果您键盘的PCB上面没有重置按钮(reset)，这能让您更简单的进入引导模式。

但是，在有些键盘的固件中，这一项属性是默认被禁用的。如果您的键盘符合这种情况，那么您必须在您的 `rules.mk` 文件中进行如下设置：

```makefile
BOOTMAGIC_ENABLE = yes
```


或许，您想指定进入引导模式的按键。这对于使用非一般布局的键盘非常的友好。您需要指定所需按键的行标和列标，依次添加这些预处理指令(#define)到 `config.h` 文件中:

```c

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1

```

默认情况下，行标和列标被依次设置为0和1。他们在大多数的键盘中代表ESC键。

如果您想要进入引导模式，则需要在插入键盘的同时按住这个键。

!> 每次使用Magic引导时都会清空EEPROM，因此所有未被保存的设置都会被抹除。

#分离式键盘

当您根据惯用手定义了一个属性 `SPLIT_HAND_PIN` 时，你可能需要在各半部分键盘设定不同的键。添加这些预处理指令(#define)到 `config.h` 文件中:

```c

#define BOOTMAGIC_LITE_ROW_RIGHT 4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 1

```

默认情况下，这两个值是不会预先定义的。

#高级Magic引导

`bootmagic_lite` 方法是使用 `__attribute__((weak))` 来定义的，因此如果有必要的话您可以用代码来代替它。最典型的例子就是Zeal60键盘需要这种额外调整。

您需要用以下代码格式来代替 `bootmagic_lite` 的原有方法：

```c

void bootmagic_lite(void) {
    matrix_scan();
    wait_ms(DEBOUNCE * 2);
    matrix_scan();

    if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1 << BOOTMAGIC_LITE_COLUMN)) {
      // 转跳到bootloader.
      bootloader_jump();
    }
}

```

您可以添加更多的功能。例如，重置EEPROM时或者同时按住多个键来启用Magic引导。但是需要注意的是，固件中大部分的功能会在 `bootmagic_lite` 函数之前初始化。

#附加

如果您想调整之前那些通过完整版Magic引导功能才能控制的设置时，更多信息参见[Magic Keycodes](zh-cn/keycodes_magic.md)。

Command功能（之前叫做Magic）也允许您控制键盘的多种功能。虽然它和Magic键码共用一些功能，但是它也允许您做magic键码做不到的事情。例如，在控制台上生成版本信息。更多信息参见[Command](zh-cn/feature_command.md)。


