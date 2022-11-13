# QMK CLI 配置

<!---
  original document: 0.15.12:docs/cli_configuration.md
  git diff 0.15.12 HEAD -- docs/cli_configuration.md | cat
-->

本文详述了 `qmk config` 功能及作用。

# 介绍

QMK CLI的配置系统是一套键/值（key/value）数据系统，每个键由一个子指令和一个参数名组成，通过点号（英文句号）分隔。这使得配置项可以简单直接地映射到命令行参数上。

## 简单示例

作为一个示例，对于指令 `qmk compile --keyboard clueboard/66/rev4 --keymap default`

其存在两个命令行参数，可以通过如下方式从配置中读取：

* `compile.keyboard`
* `compile.keymap`

可以这样设置：

```
$ qmk config compile.keyboard=clueboard/66/rev4 compile.keymap=default
compile.keyboard: None -> clueboard/66/rev4
compile.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

现在每次执行 `qmk compile` 时都不需要指定键盘及键映射参数了。

## 设置用户级的默认配置

当你需要在多个命令中使用一致的配置项时，比如很多命令都需要的 `--keyboard` 参数，相比于每次执行命令都去指定该参数值，你可以直接设置用户级的配置值，即可将该配置用于所有的命令。

示例：

```
$ qmk config user.keyboard=clueboard/66/rev4 user.keymap=default
user.keyboard: None -> clueboard/66/rev4
user.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

# CLI文档 (`qmk config`)

`qmk config` 命令可以管理配置数据。当不带额外参数执行时，会输出所有已有配置。存在参数时这些参数将被视为配置项参数，其格式须满足如下形式且无空格分隔：

    <subcommand|general|default>[.<key>][=<value>]

## 设置配置值

在配置项的键后加 = 号进行值的设置，配置项的键必须是 `<section>.<key>` 的完整形式。

举例：

```
$ qmk config default.keymap=default
default.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

## 读取配置值

可以读取整个配置文件、单独配置键或是一整个配置系列，也可以同时指定读取多个配置项。

### 全量配置读取示例

    qmk config

### 单系列配置读取示例

    qmk config compile

### 单配置项读取示例

    qmk config compile.keyboard

### 多配置项读取示例

    qmk config user compile.keyboard compile.keymap

## 删除配置值

将配置值设置为 `None` 即可删除该配置值。

示例：

```
$ qmk config default.keymap=None
default.keymap: default -> None
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

## 批量操作

一个指令中可以合并执行多个读写操作，将依序进行执行输出：

```
$ qmk config compile default.keymap=default compile.keymap=None
compile.keymap=skully
compile.keyboard=clueboard/66_hotswap/gen1
default.keymap: None -> default
compile.keymap: skully -> None
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

# 用户配置相关的配置项

| 配置项 | 默认值 | 描述 |
|-------|-------|------|
| user.keyboard | None | 键盘路径（举例：`clueboard/66/rev4`） |
| user.keymap | None | 键盘名称（举例：`default`） |
| user.name | None | 用户的Github用户名 |

# 所有配置项

| 配置项 | 默认值 | 描述 |
|-------|-------|------|
| compile.keyboard | None | 键盘路径（举例：`clueboard/66/rev4`） |
| compile.keymap | None | 键盘名称（举例：`default`） |
| hello.name | None | 执行时展示的欢迎信息 |
| new_keyboard.keyboard | None | 键盘路径（举例：`clueboard/66/rev4`） |
| new_keyboard.keymap | None | 键盘名称（举例：`default`） |
