# Data Driven Configuration

This page describes how QMK's data driven JSON configuration system works. It is aimed at developers who want to work on QMK itself.

## History

Historically QMK has been configured through a combination of two mechanisms- `rules.mk` and `config.h`. While this worked well when QMK was only a handful of keyboards we've grown to encompass nearly 1500 supported keyboards. That extrapolates out to 6000 configuration files under `keyboards/` alone! The freeform nature of these files and the unique patterns people have used to avoid duplication have made ongoing maintenance a challenge, and a large number of our keyboards follow patterns that are outdated and sometimes harder to understand.

We have also been working on bringing the power of QMK to people who aren't comformable with a CLI, and other projects such as VIA are working to make using QMK as easy as installing a program. These tools need information about how a keyboard is laid out or what pins and features are available so that users can take full advantage of QMK. We introduced `info.json` as a first step towards this. The QMK API is an effort to combine these 3 sources of information- `config.h`, `rules.mk`, and `info.json`- into a single source of truth that end-user tools can use.

Now we have support for generating `rules.mk` and `config.h` values from `info.json`, allowing us to have a single source of truth. This will allow us to use automated tooling to maintain keyboards saving a lot of time and maintenance work.

## Overview

On the C side of things nothing changes. When you need to create a new rule or define you follow the same process:

1. Add it to `docs/config_options.md`
1. Set a default in the appropriate core file
1. Add your ifdef statements as needed

You will then need to add support for your new configuration to `info.json`. The basic process is:

1. Add it to the schema in `data/schemas/keyboards.jsonschema`
1. Add a mapping in `data/maps`
1. (optional and discouraged) Add code to extract/generate it to:
  * `lib/python/qmk/info.py`
  * `lib/python/qmk/cli/generate/config_h.py`
  * `lib/python/qmk/cli/generate/rules_mk.py`

## Adding an option to info.json

This section describes adding support for a `config.h`/`rules.mk` value to info.json.

### Add it to the schema

QMK maintains [jsonschema](https://json-schema.org/) files in `data/schemas`. The values that go into keyboard-specific `info.json` files are kept in `keyboard.jsonschema`. Any value you want to make available to end users to edit must go in here.

In some cases you can simply add a new top-level key. Some examples to follow are `keyboard_name`, `maintainer`, `processor`, and `url`. This is appropriate when your option is self-contained and not directly related to other options.

In other cases you should group like options together in an `object`. This is particularly true when adding support for a feature. Some examples to follow for this are `indicators`, `matrix_pins`, and `rgblight`. If you are not sure how to integrate your new option(s) [open an issue](https://github.com/qmk/qmk_firmware/issues/new?assignees=&labels=cli%2C+python&template=other_issues.md&title=) or [join #cli on Discord](https://discord.gg/heQPAgy) and start a conversation there.

### Add a mapping

In most cases you can add a simple mapping. These are maintained as JSON files in `data/mappings/info_config.hjson` and `data/mappings/info_rules.hjson`, and control mapping for `config.h` and `rules.mk`, respectively. Each mapping is keyed by the `config.h` or `rules.mk` variable, and the value is a hash with the following keys:

* `info_key`: (required) The location within `info.json` for this value. See below.
* `value_type`: (optional) Default `raw`. The format for this variable's value. See below.
* `to_json`: (optional) Default `true`. Set to `false` to exclude this mapping from info.json
* `to_c`: (optional) Default `true`. Set to `false` to exclude this mapping from config.h
* `warn_duplicate`: (optional) Default `true`. Set to `false` to turn off warning when a value exists in both places

#### Info Key

We use JSON dot notation to address variables within info.json. For example, to access `info_json["rgblight"]["split_count"]` I would specify `rgblight.split_count`. This allows you to address deeply nested keys with a simple string.

Under the hood we use [Dotty Dict](https://dotty-dict.readthedocs.io/en/latest/), you can refer to that documentation for how these strings are converted to object access.

#### Value Types

By default we treat all values as unquoted "raw" data. If your value is more complex you can use one of these types to intelligently parse the data:

* `array`: A comma separated array of strings
* `array.int`: A comma separated array of integers
* `int`: An integer
* `hex`: A number formatted as hex
* `list`: A space separate array of strings
* `mapping`: A hash of key/value pairs
* `str`: A quoted string literal

### Add code to extract it

Most use cases can be solved by the mapping files described above. If yours can't you can instead write code to extract your config values.

Whenever QMK generates a complete `info.json` it extracts information from `config.h` and `rules.mk`. You will need to add code for your new config value to `lib/python/qmk/info.py`. Typically this means adding a new `_extract_<feature>()` function and then calling your function in either `_extract_config_h()` or `_extract_rules_mk()`.

If you are not sure how to edit this file or are not comfortable with Python [open an issue](https://github.com/qmk/qmk_firmware/issues/new?assignees=&labels=cli%2C+python&template=other_issues.md&title=) or [join #cli on Discord](https://discord.gg/heQPAgy) and someone can help you with this part.

### Add code to generate it :id=add-code-to-generate-it

The final piece of the puzzle is providing your new option to the build system. This is done by generating two files:

* `.build/obj_<keyboard>_<keymap>/src/info_config.h`
* `.build/obj_<keyboard>_<keymap>/src/rules.mk`

These two files are generated by the code here:

* `lib/python/qmk/cli/generate/config_h.py`
* `lib/python/qmk/cli/generate/rules_mk.py`

For `config.h` values you'll need to write a function for your rule(s) and call that function in `generate_config_h()`.

If you have a new top-level `info.json` key for `rules.mk` you can simply add your keys to `info_to_rules` at the top of `lib/python/qmk/cli/generate/rules_mk.py`. Otherwise you'll need to create a new if block for your feature in `generate_rules_mk()`.
