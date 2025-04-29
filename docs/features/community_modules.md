# Community Modules

Community Modules are a feature within QMK which allows code to be implemented by third parties, making it available for other people to import into their own builds.

These modules can provide implementations which override or enhance normal QMK processing; initialization, key processing, suspend, and shutdown are some of the provided hooks which modules may implement.

## Adding a Community Module to your build

Community Modules have first-class support for [External Userspace](/newbs_external_userspace), and QMK strongly recommends using External Userspace for hosting keymaps and Community Modules together.

Modules must live in either of two locations:

* `<QMK_USERSPACE>/modules/`
* `<QMK_FIRMWARE>/modules/`

A basic module is provided within QMK itself -- `qmk/hello_world` -- which prints out a notification over [HID console](/faq_debug) after 10 seconds, and adds a new keycode, `COMMUNITY_MODULE_HELLO` (aliased to `CM_HELO`) which types `Hello there.` to the active application when the corresponding key is pressed.

To add this module to your build, in your keymap's directory create a `keymap.json` with the following content:

```json
{
    "modules": [
        "qmk/hello_world"
    ]
}
```

If you already have a `keymap.json`, you'll need to manually merge the `modules` section into your keymap.

::: warning
Community Modules are not supported by QMK Configurator. If you wish to use Community Modules, you must build your own firmware.
:::

## Adding a Community Module to your External Userspace

Module authors are encouraged to provide a git repository on GitHub which may be imported into a user's external userspace. If a user wishes to import a module repository, they can do the following:

```sh
cd /path/to/your/external/userspace
mkdir -p modules
# Replace the following {user} and {repo} with the author's community module repository
git submodule add https://github.com/{user}/{repo}.git modules/{user}
git submodule update --init --recursive
```

This will ensure the copy of the module is made in your userspace.

Add a new entry into your `keymap.json` with the desired modules, replacing `{user}` and `{module_name}` as appropriate:

```json
{
    "modules": [
        "qmk/hello_world",
        "{user}/{module_name}"
    ]
}
```

::: info
The module listed in `keymap.json` is the relative path within the `modules/` directory. So long as the module is present _somewhere_ under `modules/`, then the `keymap.json` can refer to that path.
:::

## Writing a QMK Community Module

As stated earlier, Community Module authors are strongly encouraged to provide their modules through git, allowing users to leverage submodules to import functionality.

### `qmk_module.json`

A Community Module is denoted by a `qmk_module.json` file such as the following:

```json
{
    "module_name": "Hello World",
    "maintainer": "QMK Maintainers",
    "features": {
        "deferred_exec": true
    },
    "keycodes": [
        {
            "key": "COMMUNITY_MODULE_HELLO",
            "aliases": ["CM_HELO"]
        }
    ]
}
```

At minimum, the module must provide the `module_name` and `maintainer` fields.

The use of `features` matches the definition normally provided within `keyboard.json` and `info.json`, allowing a module to signal to the build system that it has its own dependencies. In the example above, it enables the _deferred executor_ feature whenever the above module is used in a build.

The `keycodes` array allows a module to provide new keycodes (as well as corresponding aliases) to a keymap.

### `rules.mk` / `post_rules.mk`

These two files follows standard QMK build system logic, allowing for `Makefile`-style customisation as if it were present in the keyboard or keymap.

### `<module>.c`

This file will be automatically added to the build if the filename matches the directory name. For example, the `qmk/hello_world` module contains a `hello_world.c` file, which is automatically added to the build.

::: info
Other files intended to be included must use the normal method of `SRC += my_file.c` inside `rules.mk`.
:::

::: tip
This file should use `ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1,0,0);` to enforce a minimum version of the API that it requires, ensuring the Community Module is built with a compatible version of QMK. The list of APIs and corresponding version is given at the bottom of this document. Note the use of commas instead of periods.
:::

### `introspection.c` / `introspection.h`

These two files hook into the keymap introspection logic -- the header is prepended before the user keymap, and the C source file is appended after the user keymap.

The header may provide definitions which are useful to the user's `keymap.c`.

The source file may provide functions which allow access to information specified in the user's `keymap.c`.

::: warning
Introspection is a relatively advanced topic within QMK, and existing patterns should be followed. If you need help please [open an issue](https://github.com/qmk/qmk_firmware/issues/new) or [chat with us on Discord](https://discord.gg/qmk).
:::

### Compatible APIs

Community Modules may provide specializations for the following APIs:

| Base API                   | API Format                          | Example (`hello_world` module)         | API Version |
|----------------------------|-------------------------------------|----------------------------------------|-------------|
| `keyboard_pre_init`        | `keyboard_pre_init_<module>`        | `keyboard_pre_init_hello_world`        | `0.1.0`     |
| `keyboard_post_init`       | `keyboard_post_init_<module>`       | `keyboard_post_init_hello_world`       | `0.1.0`     |
| `pre_process_record`       | `pre_process_record_<module>`       | `pre_process_record_hello_world`       | `0.1.0`     |
| `process_record`           | `process_record_<module>`           | `process_record_hello_world`           | `0.1.0`     |
| `post_process_record`      | `post_process_record_<module>`      | `post_process_record_hello_world`      | `0.1.0`     |
| `housekeeping_task`        | `housekeeping_task_<module>`        | `housekeeping_task_hello_world`        | `1.0.0`     |
| `suspend_power_down`       | `suspend_power_down_<module>`       | `suspend_power_down_hello_world`       | `1.0.0`     |
| `suspend_wakeup_init`      | `suspend_wakeup_init_<module>`      | `suspend_wakeup_init_hello_world`      | `1.0.0`     |
| `shutdown`                 | `shutdown_<module>`                 | `shutdown_hello_world`                 | `1.0.0`     |
| `process_detected_host_os` | `process_detected_host_os_<module>` | `process_detected_host_os_hello_world` | `1.0.0`     |

::: info
An unspecified API is disregarded if a Community Module does not provide a specialization for it.
:::

Each API has an equivalent `_<module>_kb()` and `_<module>_user()` hook, as per the normal QMK [`_quantum`, `_kb`, and `_user` functions](/custom_quantum_functions#a-word-on-core-vs-keyboards-vs-keymap).
