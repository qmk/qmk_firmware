# Building QMK with GitHub Userspace

This is an intermediate QMK tutorial to setup an out-of-tree build environment with a personal GitHub repository. It avoids using a fork of the QMK firmware to store and build your keymap within its source tree. Keymap files will instead be stored in your own personal GitHub repository, in [Userspace](https://docs.qmk.fm/#/feature_userspace) format, and built with an action workflow. Unlike the [default tutorial](https://docs.qmk.fm/#/newbs), this guide requires some familiarity with using Git.

?> **Is This Guide For Me?**<br>
This is a lean setup to avoid space-consuming local build environment in your computer. Troubleshooting compile-time errors will be slower with commit uploads to GitHub for the compiler workflow.


## Prerequisites

The following are required to get started:

* [GitHub Account](https://github.com/new)
  * A working account is required to setup and host your repository for GitHub Actions to build QMK firmware.
* [Text editor](newbs_learn_more_resources.md#text-editor-resources)
  * You’ll need a program that can edit and save plain text files. The default editor that comes with many OS's does not save plain text files, so you'll need to make sure that whatever editor you chose does.
* [Toolbox](https://github.com/qmk/qmk_toolbox)
  * A graphical program for Windows and macOS that allows you to both program and debug your custom keyboard.


## Environment Setup

?> If you are familiar with using [github.dev](https://docs.github.com/en/codespaces/the-githubdev-web-based-editor), you can skip to [step 2](#_2-create-github-repository) and commit the code files that follows directly on GitHub using the web-based VSCode editor.

### 1. Install Git

A working Git client is required for your local operating system to commit and push changes to GitHub.

<!-- tabs:start -->

### ** Windows **

QMK maintains a bundle of MSYS2, the CLI and all necessary dependencies including Git. Install [QMK MSYS](https://msys.qmk.fm/) with the latest release [here](https://github.com/qmk/qmk_distro_msys/releases/latest). Git will be part of the bundle.

### ** macOS **

Install Homebrew following the instructions on https://brew.sh. Git will be part of the bundle.

### ** Linux/WSL **

It's very likely that you already have Git installed. If not, use one of the following commands:

* Debian / Ubuntu / Devuan: `sudo apt install -y git`
* Fedora / Red Hat / CentOS: `sudo yum -y install git`
* Arch / Manjaro: `sudo pacman --needed --noconfirm -S git`
* Void: `sudo xbps-install -y git`
* Solus: `sudo eopkg -y install git`
* Sabayon: `sudo equo install dev-vcs/git`
* Gentoo: `sudo emerge dev-vcs/git`

<!-- tabs:end -->

### 2. GitHub authentication

If your GitHub account is not configured for [authenticated Git operations](https://github.blog/2020-12-15-token-authentication-requirements-for-git-operations/), you will need to setup at least one of the following:
* [Personal access token](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token)
* [Connecting with SSH](https://docs.github.com/en/authentication/connecting-to-github-with-ssh)

### 3. Create a repository

You will need a personal GitHub repository to host your QMK code. Follow [this guide](https://docs.github.com/en/get-started/quickstart/create-a-repo#create-a-repository) to create one named `qmk_keymap`. Do not proceed to commit any files just yet.


## Initial Code Commit

### Create template files

Run the following commands in your computer to create a folder with a few template files:
```
mkdir -p ~/qmk_keymap/.github/workflows
touch ~/qmk_keymap/.github/workflows/build.yml
touch ~/qmk_keymap/config.h
echo "SRC += source.c" > ~/qmk_keymap/rules.mk
echo "#include QMK_KEYBOARD_H" > ~/qmk_keymap/source.c
```

?> For Windows user running MSYS, those commands will create the folder `qmk_keymap/` and its content in the `C:\Users\<windows_username>\qmk_keymap\` path location.

### Add a JSON keymap

Visit the [QMK Configurator](https://config.qmk.fm/#/) to create a keymap file:

1. Select your keyboard from the drop-down list (and choose a layout if required).
2. Use your GitHub username for the **Keymap Name** field.
3. Customise the key layout according to your preference.
4. Select download next to **KEYMAP.JSON** and save the JSON file into the `~/qmk_keymap/` folder.

!> **Important:** Make sure that the GitHub username you use in step 2 is correct. If it is not, the build process will fail to locate your files in the right folder.

### Add a GitHub Action workflow

Open the file `~/qmk_keymap/.github/workflows/build.yml` with your favorite [text editor](newbs_learn_more_resources.md#text-editor-resources), paste the following workflow content, and save it:
```yml
name: Build QMK firmware
on: [push, workflow_dispatch]

jobs:
  build:
    runs-on: ubuntu-latest
    container: ghcr.io/qmk/qmk_cli
    strategy:
      fail-fast: false
      matrix:
# List of keymap json files to build
        file:
        - username.json
# End of json file list

    steps:

    - name: Disable git safe directory checks
      run : git config --global --add safe.directory '*'

    - name: Checkout QMK
      uses: actions/checkout@v3
      with:
        repository: qmk/qmk_firmware
        submodules: recursive

    - name: Checkout userspace
      uses: actions/checkout@v3
      with:
        path: users/${{ github.actor }}

    - name: Build firmware
      run: qmk compile "users/${{ github.actor }}/${{ matrix.file }}"

    - name: Archive firmware
      uses: actions/upload-artifact@v3
      continue-on-error: true
      with:
        name: ${{ matrix.file }}_${{ github.actor }}
        path: |
          *.hex
          *.bin
          *.uf2
```
Replace `username.json` with the JSON file name that was downloaded from [QMK Configurator](https://config.qmk.fm/#/) in the previous step.

!> Do note that the `build.yml` file requires ***proper indentation*** for every line. Incorrect spacing will trigger workflow syntax errors.

### Commit files to GitHub

If you have completed all steps correctly, the folder `qmk_keymap/` will contain the following files:
```
├── .github
│   └── workflows
│       └── build.yml
├── rules.mk
├── config.h
├── source.c
└── username.json
```

To commit and push them into GitHub, run the following commands (replacing `gh-username` with your GitHub user name):
```
cd ~/qmk_keymap
git init
git add -A
git commit -m "Initial QMK keymap commit"
git branch -M main
git remote add origin https://github.com/gh-username/qmk_keymap.git
git push -u origin main
```
?> Use your GitHub personal access token at the password prompt. If you have setup SSH access, replace `https://github.com/gh-username/qmk_keymap.git` with `git@github.com:gh-username/qmk_keymap.git` in the remote origin command above.

### Review workflow output

Files committed to GitHub in the previous step will automatically trigger the workflow to build the JSON file listed in `build.yml`. To review its output:
1. Visit your "**qmk_keymap**" repository page on [GitHub](https://github.com/).
2. Select **Actions** tab to display the "**Build QMK Firmware**" workflow.
3. Select that workflow to display its run from the last commit.
4. Successfully compiled firmware will be under the "**Artifacts**" section.
5. If there are build errors, review the job log for details.

Download and flash the firmware file into your keyboard using [QMK Toolbox](https://docs.qmk.fm/#/newbs_flashing?id=flashing-your-keyboard-with-qmk-toolbox).


## Customising your keymap

This setup and workflow relies on the QMK [Userspace](https://docs.qmk.fm/#/feature_userspace) feature. The build process will copy the QMK source codes and clone your repository into its `users/` folder in a container. You must adhere to the following guidelines when customising your keymaps:

* Keymap layout files must be retained in JSON format and cannot be converted to `keymap.c`.
* User callback and functions (e.g. `process_record_user()`) can be placed in the `source.c` file.
* Multiple keymap JSON files can be built in the same workflow. List them under `matrix.file:`, e.g.:
```yml
        file:
        - planck.json
        - crkbd.json
```
* Code changes will require Git commit into GitHub to trigger the build workflow.


?> See [GitHub Actions guide](https://docs.github.com/en/actions/learn-github-actions) to learn more about development workflow.
