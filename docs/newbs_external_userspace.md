# External QMK Userspace

QMK Firmware can now be built using an external userspace git repository, optionally coupled with GitHub actions so that users don't need to build firmware locally.

Using external userspace allows you to create your firmware without having to modify your QMK installation. Additionally, it drastically simplifies the process of keeping up to date with QMK Firmware, especially when leveraging GitHub actions to automatically perform builds for you.

!> External QMK Userspace is new functionality and may have issues. Tighter integration with the `qmk` command will occur over time.

?> Legacy GitHub-based firmware build instructions can be found [here](newbs_building_firmware_workflow.md). This document supersedes those instructions, but they should still correctly function.

## Repository Setup (on GitHub)

A basic skeleton External Userspace repository can be found [here](https://github.com/qmk/qmk_userspace). If you with to keep your keymaps on GitHub (strongly recommended!), you can fork the repository and use it as a base:

![Userspace Fork](https://i.imgur.com/hcegguh.png)

Going ahead with your fork will copy it to your account, at which point you can clone it to your local machine and begin adding your keymaps:

![Userspace Clone](https://i.imgur.com/CWYmsk8.png)

```sh
git clone https://github.com/myusername/qmk_userspace.git
qmk config user.overlay_dir="$(realpath qmk_userspace)"
```

## Repository Setup (local-only)

If you don't want to use GitHub and prefer to keep everything local, you can clone a copy of the default userspace repository locally instead:

```sh
git clone https://github.com/qmk/qmk_userspace.git
qmk config user.overlay_dir="$(realpath qmk_userspace)"
```

## Setting up QMK Locally

If you wish to build on your local machine, you will need to set up QMK locally. This is a one-time process, and is documented in the [QMK Docs](https://docs.qmk.fm/#/newbs).

!> If you want to use any QMK CLI commands related to manipulating userspace definitions, you will currently need a copy of QMK Firmware as well.

!> Building locally has a much shorter turnaround time than waiting for GitHub actions to complete.

## Adding a Keymap

_These instructions assume you have already set up QMK locally, and have a copy of the QMK Firmware repository on your machine._

Keymaps within external userspace are defined in the same way as they are in the main QMK repository. You can either use the `qmk new-keymap` command to create a new keymap, or manually create a new directory in the `keyboards` directory.

After creating your new keymap, building the keymap matches normal QMK usage:

```sh
qmk compile -kb <keyboard> -km <keymap>
```

!> The `qmk config user.overlay_dir=...` command must have been run when cloning the userspace repository for this to work correctly.

## Adding the keymap to userspace build targets

Once you have created your keymap, you will need to add it to the userspace build targets. This is done using the `qmk userspace-add` command:

```sh
# for a keyboard/keymap combo:
qmk userspace-add -kb <keyboard> -km <keymap>
# or, for a json-based keymap (if kept "loose"):
qmk userspace-add <relative/path/to/my/keymap.json>
```

This updates the `qmk.json` file in the root of your userspace repository.

## Compiling userspace build targets

Once you have added your keymaps to the userspace build targets, you can compile all of them at once using the `qmk userspace-compile` command:

```sh
qmk userspace-compile
```

## Using GitHub Actions

GitHub Actions can be used to automatically build your keymaps whenever you push changes to your repository. If you have set up your list of build targets, this is as simple as enabling workflows in the GitHub repository settings:


![Repo Settings](https://i.imgur.com/EVkxOt1.png)

Any push will result in a build occurring, and once complete a new release containing the newly-minted firmware files:

![Releases](https://i.imgur.com/zmwOL5P.png)
