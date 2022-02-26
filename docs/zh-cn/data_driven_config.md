# Data Driven Configuration

<!---
  original document: 0.16.0:docs/data_driven_config.md
  git diff 0.16.0 HEAD -- docs/data_driven_config.md | cat
-->

本文阐述了 QMK 是如何基于 JSON 配置来驱动系统工作的。目标读者为期望在 QMK 之上进行扩展开发的开发者们。

## 相关历史

QMK 历史上是由两套机制结合共同完成配置的 - `rules.mk` 以及 `config.h`。那时的 QMK 仅是一个趁手的键盘方案，这种方案很好地支撑着它的成长成长，支持了近 1500 个键盘。经过推算在 `keyboards/` 目录下就有 6000 个配置文件！但由于这些文件的格式自由以及人们为了避免冲突而使用的各种独特的模式，使得之后的维护工作非常有挑战，有大量的键盘遵循着已过时的模式，并且晦涩难懂。

我们也一直在努力将 QMK 的魅力带给那些不熟悉 CLI 的人们，也有着像 VIA 这样的工程致力于将 QMK 的使用体验变得像安装一个软件那么简单。这类工具需要键盘的形制、引脚以及可用的特性等信息来向使用者充分展现 QMK 的特质。因此我们引入了 `info.json` 文件来向着这些目标迈出第一步。QMK API 将结合这三种信息源 - `config.h`，`rules.mk`以及`info.json` - 生成一份最终的详细信息源以供终端工具使用。

现在我们已经支持通过 `info.json` 文件生成 `rules.mk` 以及 `config.h` 配置值，因此可以仅有一份配置信息。且可以通过自动化工具来维护键盘从而节省时间及维护工作量。

## 总览

在 C 语言视角看来没有发生过变化。若需要创建新的规则或定义时，都使用同样的流程：

1. 将其添加到 `docs/config_options.md`
1. 在正确的核心文件中设置默认值
1. 按需添加对应的 `#ifdef` 代码段

之后需要在 `info.json` 中添加对该新配置的支持，基本流程为：

1. 在 `data/schemas/keyboards.jsonschema` 添加其 schema
1. 在 `data/maps` 中添加映射
1. （非必要且不推荐的）在如下文件中添加对其进行提取/生成的代码：
  * `lib/python/qmk/info.py`
  * `lib/python/qmk/cli/generate/config_h.py`
  * `lib/python/qmk/cli/generate/rules_mk.py`

## 在 info.json 中添加选项

本节描述了如何在 `info.json` 中支持 `config.h`/`rules.mk` 中的配置值

### 添加 schema

QMK 在 `data/schemas` 之下维护 [jsonschema](https://json-schema.org/) 文件。键盘的 `info.json` 的 Schema 位于 `keyboard.jsonschema` 文件中。任何允许终端用户可配置的选项必须在这里定义。

通常可以直接在顶层添加新键，类似的示例有 `keyboard_name`，`maintainer`，`processor` 以及 `url`。这适用于那些独立且与其它选项不直接相关的选项。

另一种情况是需要将若干个相关的选项集中在一个 `object` 中。通常在添加新支持的特性时都属于这种情况，类似的示例有 `indicators`，`matrix_pins` 以及 `rgblight`。若你不是很确定如何添加新配置项，可以[创建一个 issue](https://github.com/qmk/qmk_firmware/issues/new?assignees=&labels=cli%2C+python&template=other_issues.md&title=) 或[在 Discord 中加入 #cli](https://discord.gg/heQPAgy) 进行探讨。

### 添加映射

大多数情况下添加简单的映射即可。映射信息维护在 `data/mappings/info_config.json` 和 `data/mappings/info_rules.json` JSON文件中，分别控制着 `config.h` 和 `rules.mk` 的映射。每个映射的 key 对应的是 `config.h` 或 `rules.mk` 内的变量，而 value 则是包含如下 key 的一个哈希表：

* `info_key`: （必须）该配置值对应在 `info.json` 中的位置。具体参见下方章节。
* `value_type`: （可选）默认为 `str`，为该配置值的变量类型，具体参见下方章节。
* `to_json`: （可选）默认为 `true`，设置为 `false` 则从 `info.json` 中排除该项。
* `to_c`: （可选）默认为 `true`，设置为 `false` 则从 `config.h` 中排除该项。
* `warn_duplicate`: （可选）默认为 `true`，设置为 `false` 后即使两个配置文件中都有该配置项也不会产生警告

#### Info 键

我们使用点号分隔的JSON路径来完成其到 `info.json` 的映射。例如，要访问 `info_json["rgblight"]["split_count"]` 时应设置为 `rgblight.split_count`。由此通过单个字符串就能定位到深度嵌套中的键。

在其背后我们使用的是 [Dotty Dict](https://dotty-dict.readthedocs.io/en/latest/)，参阅其文档可以了解到这些字符串是如何转换成实际对象的访问操作的。

#### 值类型

默认我们将所有的值视为简单的字符串类型。若该配置值相对复杂一些，可以使用以下类型以实现更智能的数据解析：

* `array`: 逗号分隔的字符串数组
* `array.int`: 逗号分隔的整数数组
* `int`: 单个整数
* `hex`: 单个十六进制整数
* `list`: 空格分隔的字符串数组
* `mapping`: 键/值对组成的哈希表

### 添加提取代码

大部分情况仅通过上述的映射文件即可。若你的新配置项无法通过上述方案实现，可以转为编写读取该配置项的提取代码。

QMK 从 `config.h` 和 `rules.mk` 中提取并生成完整的 `info.json` 文件。新配置值的提取代码须添加到 `lib/python/qmk/info.py` 中。通常的流程是添加一个新的 `_extract_<feature>()` 函数并在 `_extract_config_h()` 或 `_extract_rules_mk()` 中调用它。

若你不是很确定如何编辑这个文件，或者不是很适应 Python 编程，可以[创建一个 issue](https://github.com/qmk/qmk_firmware/issues/new?assignees=&labels=cli%2C+python&template=other_issues.md&title=) 或[在 Discord 中加入 #cli](https://discord.gg/heQPAgy) 寻找可以帮助你的人。

### 添加生成代码 :id=add-code-to-generate-it

拼图的最后一块，是在构建系统中添加这个新配置项。其最终会生成两个文件：

* `.build/obj_<keyboard>/src/info_config.h`
* `.build/obj_<keyboard>/src/rules.mk`

而这两个文件则由以下两个文件产生：

* `lib/python/qmk/cli/generate/config_h.py`
* `lib/python/qmk/cli/generate/rules_mk.py`

对于 `config.h` 内的值，需要编写一个函数来实现其构建规则并在 `generate_config_h()` 内调用此函数。

若你有一个用于 `rules.mk` 的新的 `info.json` 键，那么可以将键添加到 `lib/python/qmk/cli/generate/rules_mk.py` 顶部的 `info_to_rules` 中，否则需要在 `generate_rules_mk()` 中创建新的 if 块来处理你的特性。
