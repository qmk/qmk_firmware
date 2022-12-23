# QMK CLI 命令

<!---
  original document: 0.15.12:docs/cli_commands.md
  git diff 0.15.12 HEAD -- docs/cli_commands.md | cat
-->

# 用户命令

## `qmk compile`

该命令用于在指定目录下编译固件，可用于构建<https://config.qmk.fm>导出的JSON数据，代码库中的键映射，或是当前目录下的键盘。

该命令会尝试感知目录路径，当你在键盘或键映射目录下执行时，KEYBOARD及KEYMAP参数将被自动填入。

**用于配置器导出的数据时**：

```
qmk compile [-c] <configuratorExport.json>
```

**用于键映射时**：

```
qmk compile [-c] [-e <var>=<value>] [-j <num_jobs>] -kb <keyboard_name> -km <keymap_name>
```

**在键盘目录下时**：  

须在存在默认键映射的键盘目录下执行，或是在键盘的键映射子目录下，否则须指定参数 `--keymap <keymap_name>`
```
qmk compile
```

**构建所有支持该键映射的键盘时**：

```
qmk compile -kb all -km <keymap_name>
```

**示例**：
```
$ qmk config compile.keymap=default
$ cd ~/qmk_firmware/keyboards/planck/rev6
$ qmk compile
Ψ Compiling keymap with make planck/rev6:default
...
```
指定键映射参数时

```
$ cd ~/qmk_firmware/keyboards/clueboard/66/rev4 
$ qmk compile -km 66_iso
Ψ Compiling keymap with make clueboard/66/rev4:66_iso
...
```
位于键盘目录下时

```
$ cd ~/qmk_firmware/keyboards/gh60/satan/keymaps/colemak
$ qmk compile
Ψ Compiling keymap with make make gh60/satan:colemak
...
```

**在配列目录下时**：  

必须是在 `qmk_firmware/layouts/` 下的键映射目录下。
```
qmk compile -kb <keyboard_name>
```

**示例**：
```
$ cd ~/qmk_firmware/layouts/community/60_ansi/mechmerlin-ansi
$ qmk compile -kb dz60
Ψ Compiling keymap with make dz60:mechmerlin-ansi
...
```

**并行编译**：

在编译时添加 `-j`/`--parallel` 开关可能有助于加快编译速度。
```
qmk compile -j <num_jobs> -kb <keyboard_name>
```
`num_jobs` 用于指定并行的job上限，将其设置为0可以实现无限制的并行编译。
```
qmk compile -j 0 -kb <keyboard_name>
```

## `qmk flash` :id=qmk-flash

该命令与 `qmk compile` 类似，但额外地可以指定bootloader。bootloader参数是可选的，默认会指定为 `:flash`。可通过 `-bl <bootloader>` 来指定bootloader。请查阅[刷写固件](zh-cn/flashing.md)指引以深入了解可用的bootloader信息。

该命令会尝试感知目录路径，当你在键盘或键映射目录下执行时，KEYBOARD及KEYMAP参数将被自动填入。

**用于配置器导出的数据时**：

```
qmk flash [-bl <bootloader>] [-c] [-e <var>=<value>] [-j <num_jobs>] <configuratorExport.json>
```

**用于键映射时**：

```
qmk flash -kb <keyboard_name> -km <keymap_name> [-bl <bootloader>] [-c] [-e <var>=<value>] [-j <num_jobs>]
```

**列出所有bootloader**

```
qmk flash -b
```

## `qmk config`

该命令用于配置QMK功能，完整的 `qmk config` 文档参见[CLI配置](zh-cn/cli_configuration.md)。

**使用方法**：

```
qmk config [-ro] [config_token1] [config_token2] [...] [config_tokenN]
```

## `qmk cd`

该命令会启动一个新的 shell 会话并定位到 `qmk_firmware` 所在目录。

须留意如果你已经位于 `QMK_HOME` 下的某个位置（比如 `keyboards/` 目录中），该指令不会生效。

若要退回到原来的 shell 会话，只需要执行 `exit`。

**使用方法**:

```
qmk cd
```

## `qmk console`

该命令用于连接键盘终端并展示调试信息。仅当键盘固件通过 `CONSOLE_ENABLE=yes` 编译时有效。

**用法**：

```
qmk console [-d <pid>:<vid>[:<index>]] [-l] [-n] [-t] [-w <seconds>]
```

**示例**：

连接到所有可用的键盘并输出终端信息：

```
qmk console
```

列出所有设备：

```
qmk console -l
```

仅输出 clueboard/66/rev3 键盘的信息:

```
qmk console -d C1ED:2370
```

仅输出第二把 clueboard/66/rev3 键盘的信息:

```
qmk console -d C1ED:2370:2
```

输出时间戳及VID:PID以替代键盘名：

```
qmk console -n -t
```

屏蔽bootloader的消息：

```
qmk console --no-bootloaders
```

## `qmk doctor`

该命令用以检查你的开发环境并对发现的潜在的构建及刷写问题进行提醒，如果您乐意，它也可以修复其中大部分问题。

**用法**：

```
qmk doctor [-y] [-n]
```

**示例**：

检查开发环境中的问题并提示是否修复：

    qmk doctor

检查开发环境中的问题并自动进行修复：

    qmk doctor -y

检查开发环境中的问题，仅生成报告：

    qmk doctor -n

## `qmk format-json`

将JSON文件格式化为（尽量）便于阅读的形式。会自动分辨JSON结构类型（info.json还是keymap.json），必要时也可以通过 `--format` 指定。

**用法**：

```
qmk format-json [-f FORMAT] <json_file>
```

## `qmk info`

展示QMK中的键盘及键映射信息，该命令用来获取键盘信息，输出配列，展示底层按键矩阵，及格式化地输出键映射JSON数据。

**用法**：

```
qmk info [-f FORMAT] [-m] [-l] [-km KEYMAP] [-kb KEYBOARD]
```

该命令会尝试感知目录路径，当你在键盘或键映射目录下执行时，KEYBOARD及KEYMAP参数将被自动填入。

**示例**：

输出键盘的基础信息：

    qmk info -kb planck/rev5

输出键盘的矩阵信息：

    qmk info -kb ergodox_ez -m

输出键盘的键映射JSON数据：

    qmk info -kb clueboard/california -km default

## `qmk json2c`

从QMK配置器导出的数据中生成 keymap.c 文件
Creates a keymap.c from a QMK Configurator export.

**用法**：

```
qmk json2c [-o OUTPUT] filename
```

## `qmk c2json`

从 keymap.c 文件中生成 keymap.json
**注意：** 解析C代码文件并不容易，该命令有可能无法对你的键映射文件生效，不使用C预处理代码有时可以解决问题。

**用法**：

```
qmk c2json -km KEYMAP -kb KEYBOARD [-q] [--no-cpp] [-o OUTPUT] filename
```

## `qmk lint`

检查键盘及键映射数据并提示出常见错误与问题，以及不符合模板规范的地方。

**用法**：

```
qmk lint [-km KEYMAP] [-kb KEYBOARD] [--strict]
```

该命令会尝试感知目录路径，当你在键盘或键映射目录下执行时，KEYBOARD及KEYMAP参数将被自动填入。

**示例**：

基本的lint检查：

    qmk lint -kb rominronin/katana60/rev2

## `qmk list-keyboards`

该命令可以列出 `qmk_firmware` 中所有的键盘

**用法**：

```
qmk list-keyboards
```

## `qmk list-keymaps`

该命令可以列出指定键盘（及指定版本）下的所有键映射。

该命令会尝试感知目录路径，当你在键盘或键映射目录下执行时，KEYBOARD及KEYMAP参数将被自动填入。

**用法**：

```
qmk list-keymaps -kb planck/ez
```

## `qmk new-keyboard`

该命令可基于现有模板创建出新的键盘定义。

对于未给出的参数，会提示你输入，若未传入 `-u` 参数且 .gitconfig 中设置了 `user.name`，则会提示你使用该值作为默认用户名。

**用法**：

```
qmk new-keyboard [-kb KEYBOARD] [-t {avr,ps2avrgb}] -u USERNAME
```

## `qmk new-keymap`

该命令可基于键盘已有的默认键映射创建新的键映射。

该命令会尝试感知目录路径，当你在键盘或键映射目录下执行时，KEYBOARD及KEYMAP参数将被自动填入。

**用法**：

```
qmk new-keymap [-kb KEYBOARD] [-km KEYMAP]
```

## `qmk clean`

该命令会清理 `.build` 目录，若传入 `--all` 开关，在 `qmk_firmware` 下的所有.hex及.bin文件也会一并删除。

**用法**：

```
qmk clean [-a]
```

---

# 面向开发者的命令

## `qmk format-text`

该命令会重新格式化并统一文件的换行符。

代码库下所有的文件须使用Unix换行符（LF）。
若你在**Windows**下进行开发，必须确保文件中的换行符是正确的，才能让你的PR被允许合入。

```
qmk format-text
```

## `qmk format-c`

该命令会使用clang-format来格式化C代码。

不带参数地执行该命令以用来格式化核心代码相关的改动，默认会通过 `git diff` 来检查 `origin/master`， 可以通过 `-b <分支名>` 来改变检查的分支。

带着 `-a` 开关执行命令会格式化所有的核心代码，也可以在命令行中传入文件名来指定格式化某个文件。

**用以处理指定文件时**：

```
qmk format-c [file1] [file2] [...] [fileN]
```

**用以处理所有的核心代码时**：

```
qmk format-c -a
```

**用以处理 origin/master 下的所有改动时**：

```
qmk format-c
```

**用以处理指定分支下的所有改动时**：

```
qmk format-c -b branch_name
```

## `qmk generate-compilation-database`

**用法**:

```
qmk generate-compilation-database [-kb KEYBOARD] [-km KEYMAP]
```

创建新 `compile_commands.json` 文件。

你的IDE/编辑器是否使用了“编程语言本地服务器”（language server）且 _总是_ 无法找到全部的包含文件（include files）？是不是很讨厌红色的波浪线？想不想让你的编辑器看得懂 `#include QMK_KEYBOARD_H`？你需要的是一个[编译数据库](https://clang.llvm.org/docs/JSONCompilationDatabase.html)！而 QMK 可以帮助你构建出一个。

该命令需要知道你在构建的是哪个键盘及键映射，它使用与 `qmk compile` 命令一样的选项：参数、当前目录以及配置文件。

**示例：**

```
$ cd ~/qmk_firmware/keyboards/gh60/satan/keymaps/colemak
$ qmk generate-compilation-database
Ψ Making clean
Ψ Gathering build instructions from make -n gh60/satan:colemak
Ψ Found 50 compile commands
Ψ Writing build database to /Users/you/src/qmk_firmware/compile_commands.json
```

现在可以打开你的开发环境并享受没有波浪线的日子了。

## `qmk docs`

该命令会在本地启动一个HTTP服务，从而你可以浏览及改进文档，默认端口号为8936，使用 `-b`/`--browser` 开关可以让该命令自动通过默认浏览器打开链接地址。

**用法**：

```
qmk docs [-b] [-p PORT]
```

## `qmk generate-docs`

该命令可以在本地生成QMK文档，用以文档的常规浏览使用，或进行文档改进工作。可以使用类似[serve](https://www.npmjs.com/package/serve)这样的工具来浏览生成的文档文件。

**用法**：

```
qmk generate-docs
```

## `qmk generate-rgb-breathe-table`

该命令可以生成用于[RGB灯光](zh-cn/feature_rgblight.md)的呼吸效果的查询表（LUT）头文件。将该文件命名为 `rgblight_breathe_table.h` 并放入键盘或键映射目录下，可以覆盖替换 `quantum/rgblight/` 下的默认LUT。

**用法**：

```
qmk generate-rgb-breathe-table [-q] [-o OUTPUT] [-m MAX] [-c CENTER]
```

## `qmk kle2json`

该命令可以将KLE原始数据转换成QMK配置器的JSON数据，可接受的输入可以是文件绝对路径，或当前目录下的文件名。若 `info.json` 文件存在，默认不会进行覆盖，通过指定 `-f` 或 `--force` 开关可以允许覆盖。

**用法**：

```
qmk kle2json [-f] <filename>
```

**示例**：

```
$ qmk kle2json kle.txt 
☒ File info.json already exists, use -f or --force to overwrite.
```

```
$ qmk kle2json -f kle.txt -f
Ψ Wrote out to info.json
```

## `qmk format-python`

该命令可以对 `qmk_firmware` 下的python代码进行格式化。

**用法**：

```
qmk format-python
```

## `qmk pytest`

该命令会执行python测试框架，在你更改了python代码后，应确保该命令可以成功执行。

**用法**：

```
qmk pytest
```

**示例**:

执行全部的测试套件：

    qmk pytest

执行指定的测试用例组：

    qmk pytest -t qmk.tests.test_cli_commands

执行单个测试用例：

    qmk pytest -t qmk.tests.test_cli_commands.test_c2json
    qmk pytest -t qmk.tests.test_qmk_path
