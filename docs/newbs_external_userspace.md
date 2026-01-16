# External QMK Userspace

QMK Firmware now officially supports storing user keymaps outside of the normal QMK Firmware repository, allowing users to maintain their own keymaps without having to fork, modify, and maintain a copy of QMK Firmware themselves.

External Userspace mirrors the structure of the main QMK Firmware repository, but only contains the keymaps that you wish to build. You can still use `keyboards/<my keyboard>/keymaps/<my keymap>` to store your keymaps, or you can use the `layouts/<my layout>/<my keymap>` system as before -- they're just stored external to QMK Firmware.

The build system will still honor the use of `users/<my keymap>` if you rely on the traditional QMK Firmware [userspace feature](feature_userspace) -- it's now supported externally too, using the same location inside the External Userspace directory.

Additionally, there is first-class support for using GitHub Actions to build your keymaps, allowing you to automatically compile your keymaps whenever you push changes to your External Userspace repository.

::: warning
External Userspace is new functionality and may have issues. Tighter integration with the `qmk` command will occur over time.
:::

::: tip
Historical keymap.json and GitHub-based firmware build instructions can be found [here](newbs_building_firmware_workflow). This document supersedes those instructions, but they should still function correctly.
:::

## Setting up QMK Locally

If you wish to build on your local machine, you will need to set up QMK locally. This is a one-time process, and is documented in the [newbs setup guide](newbs).

::: warning
If you wish to use any QMK CLI commands related to manipulating External Userspace definitions, you will currently need a copy of QMK Firmware as well.
:::

::: warning
Building locally has a much shorter turnaround time than waiting for GitHub Actions to complete.
:::

## External Userspace Repository Setup (forked on GitHub)

A basic skeleton External Userspace repository can be found [here](https://github.com/qmk/qmk_userspace). If you wish to keep your keymaps on GitHub (strongly recommended!), you can fork the repository and use it as a base:

![Userspace Fork](/hcegguh.png)

Going ahead with your fork will copy it to your account, at which point you can clone it to your local machine and begin adding your keymaps:

![Userspace Clone](/CWYmsk8.png)

```sh
cd $HOME
git clone https://github.com/{myusername}/qmk_userspace.git
qmk config user.overlay_dir="$(realpath qmk_userspace)"
```

## External Userspace Setup (locally stored only)

If you don't want to use GitHub and prefer to keep everything local, you can clone a copy of the default External Userspace locally instead:

```sh
cd $HOME
git clone https://github.com/qmk/qmk_userspace.git
qmk config user.overlay_dir="$(realpath qmk_userspace)"
```

## Adding a Keymap

_These instructions assume you have already set up QMK locally, and have a copy of the QMK Firmware repository on your machine._

Keymaps within External Userspace are defined in the same way as they are in the main QMK repository. You can either use the `qmk new-keymap` command to create a new keymap, or manually create a new directory in the `keyboards` directory.

Alternatively, you can use the `layouts` directory to store your keymaps, using the same layout system as the main QMK repository -- if you choose to do so you'll want to use the path `layouts/<layout name>/<keymap name>/keymap.*` to store your keymap files, where `layout name` matches an existing layout in QMK, such as `tkl_ansi`.

After creating your new keymap, building the keymap matches normal QMK usage:

```sh
qmk compile -kb <keyboard> -km <keymap>
```

::: warning
The `qmk config user.overlay_dir=...` command must have been run when cloning the External Userspace repository for this to work correctly.
:::

## Adding the keymap to External Userspace build targets

Once you have created your keymap, if you want to use GitHub Actions to build your firmware, you will need to add it to the External Userspace build targets. This is done using the `qmk userspace-add` command:

```sh
# for a keyboard/keymap combo:
qmk userspace-add -kb <keyboard> -km <keymap>
# or, for a json-based keymap (if kept "loose"):
qmk userspace-add <relative/path/to/my/keymap.json>
```

This updates the `qmk.json` file in the root of your External Userspace directory. If you're using a git repository to store your keymaps, now is a great time to commit and push to your own fork.

## Compiling External Userspace build targets

Once you have added your keymaps to the External Userspace build targets, you can compile all of them at once using the `qmk userspace-compile` command:

```sh
qmk userspace-compile
```

All firmware builds you've added to the External Userspace build targets will be built, and the resulting firmware files will be placed in the root of your External Userspace directory.

## Using GitHub Actions

GitHub Actions can be used to automatically build your keymaps whenever you push changes to your External Userspace repository. If you have set up your list of build targets, this is as simple as enabling workflows in the GitHub repository settings:

![Repo Settings](/EVkxOt1.png)

Any push will result in compilation of all configured builds, and once completed a new release containing the newly-minted firmware files will be created on GitHub, which you can subsequently download and flash to your keyboard:

![Releases](/zmwOL5P.png)
