# Setting up Visual Studio Code for QMK Development

[Visual Studio Code](https://code.visualstudio.com/) (VS Code) is an open-source code editor that supports many different programming languages. 

Using a full-featured editor such as VS Code provides many advantages over a plain text editor, such as:
* intelligent code completion
* convenient navigation in the code
* refactoring tools
* build automation (no need for the command-line)
* a graphical front end for GIT
* many other tools such as debugging, code formatting, showing call hierarchies etc.

The purpose of this page is to document how to set up VS Code for developing QMK Firmware.

This guide covers how to configure everything needed on Windows and Ubuntu 18.04

# Set up VS Code
Before starting, you will want to make sure that you have all of the build tools set up, and QMK Firmware cloned. Head to the [Newbs Getting Started Guide](newbs_getting_started) to get things set up, if you haven't already.

## Windows

### Prerequisites

* [Git for Windows](https://git-scm.com/download/win) (This link will prompt to save/run the installer)
  
  1. Disable all of the options but `Git LFS (Large File Support)` and `Check daily for Git for Windows updates`. 
  2. Set the default editor to `Use Visual Studio Code as Git's default editor`
  3. Select the `Use Git from Git Bash only` option, since that's the option that you should use here.
  4. For the `Choosing HTTPS transport backend`, either option should be fine.
  5. Select the `Checkout as-is, commit Unix-style line endings` option. QMK Firmware uses Unix style commits.
  6. For the extra options, leave the default options as is. 

  This software is needed for Git support in VS Code. It may be possible to not include this, but it is much simpler to just use this. 

* [Git Credential Manager for Windows](https://github.com/Microsoft/Git-Credential-Manager-for-Windows/releases) (Optional) 

  This software provides better support for Git by providing secure storage for git credentials, MFA and personal access token generation. 
  
  This isn't strictly needed, but we would recommend it. 


### Installing VS Code

1. Head to [VS Code](https://code.visualstudio.com/) and download the installer
2. Run the installer

This part is super simple.  However, there is some configuration that we need to do to ensure things are configured correctly.

#### MSYS2 Setup

Now, we will set up the MSYS2 window to show up in VSCode as the integrated terminal.  This has a number of advantages. Mostly, you can control+click on errors and jump to those files.  This makes debugging much easier.  It's also nice, in that you don't have to jump to another window. 

1. Click <kbd><kbd>File</kbd> > <kbd>Preferences ></kbd> > <kbd>Settings</kbd> </kbd>
2. Click on the <kbd>{}</kbd> button, in the top right to open the `settings.json` file. 
3. Set the file's content to: 

   ```json
   {
        "terminal.integrated.profiles.windows": {
            "QMK_MSYS": {
                "path": "C:/QMK_MSYS/usr/bin/bash.exe",
                "env": {
                    "MSYSTEM": "MINGW64",
                    "CHERE_INVOKING": "1"
                },
                "args": ["--login"]
            }
        },

        "terminal.integrated.cursorStyle": "line"
    }
    ```

   If there are settings here already, then just add everything between the first and last curly brackets and separate the existing settings with a comma from the newly added ones.

::: tip
If you installed MSYS2 to a different folder, then you'll need to change the path for `terminal.integrated.shell.windows` to the correct path for your system. 
:::

4. Hit Ctrl-<code>&#96;</code> (Grave) to bring up the terminal or go to <kbd><kbd>View</kbd> > <kbd>Terminal</kbd></kbd> (command `workbench.action.terminal.toggleTerminal`). A new terminal will be opened if there isn‘t one already.

   This should start the terminal in the workspace's folder (so the `qmk_firmware` folder), and then you can compile your keyboard. 


## Every other Operating System

1. Head to [VS Code](https://code.visualstudio.com/) and download the installer
2. Run the installer
3. That's it

No, really, that's it.  The paths needed are already included when installing the packages, and it is much better about detecting the current workspace files and parsing them for IntelliSense. 

## Extensions

There are a number of extensions that you may want to install:

* [Git Extension Pack](https://marketplace.visualstudio.com/items?itemName=donjayamanne.git-extension-pack) - This installs a bunch of Git related tools that may make using Git with QMK Firmware easier.
* [clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd) - _[Optional]_ -  This is the language server for C/C++ that VS Code uses.  It provides IntelliSense and other features.
* [EditorConfig for VS Code](https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig) - _[Optional]_ -  Helps to keep the code to the QMK Coding Conventions.
* [GitHub Markdown Preview](https://marketplace.visualstudio.com/items?itemName=bierner.github-markdown-preview) - _[Optional]_ - Makes the markdown preview in VS Code more like GitHub's.
* [VS Live Share Extension Pack](https://marketplace.visualstudio.com/items?itemName=MS-vsliveshare.vsliveshare) - _[Optional]_ - This extension allows somebody else to access your workspace (or you to access somebody else's workspace) and help out.  This is great if you're having issues and need some help from somebody.

Restart once you've installed any extensions.

# Configure VS Code for QMK

1. Click <kbd><kbd>File</kbd> > <kbd>Open Folder</kbd></kbd>
2. Open the QMK Firmware folder that you cloned from GitHub.
3. Click <kbd><kbd>File</kbd> > <kbd>Save Workspace As...</kbd></kbd>

## Configuring VS Code

Using the [standard `compile_commands.json` database](https://clang.llvm.org/docs/JSONCompilationDatabase.html), we can get the VS code _clangd_ extension to use the correct includes and defines used for your keyboard and keymap.

1. Run `qmk compile -kb <keyboard> -km <keymap> --compiledb` to generate the `compile_commands.json`.
1. Inside VS code, press <kbd><kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd></kbd> (macOS: <kbd><kbd>Command</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd></kbd>) to open the command palette.
1. Start typing `clangd: Download Language Server` and select it when it appears. Note that this only needs to be done once on clangd extension installation, if it didn't already ask to do so.
1. Inside VS code, press <kbd><kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd></kbd> (macOS: <kbd><kbd>Command</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd></kbd>) to open the command palette.
1. Start typing `clangd: Restart Language Server` and select it when it appears.

Now you're ready to code QMK Firmware in VS Code!

# Debugging ARM MCUs with Visual Studio Code

**...and a Black Magic Probe.**

Visual Studio Code has the ability to debug applications, but requires some configuration in order to get it to be able to do so for ARM targets.

This documentation describes a known-working configuration for setting up the use of a Black Magic Probe to debug using VS Code.

It is assumed that you've correctly set up the electrical connectivity of the Black Magic Probe with your MCU. Wiring up `NRST`, `SWDIO`, `SWCLK`, and `GND` should be enough.

Install the following plugin into VS Code:

* [Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug) - 
  This adds debugger support for ARM Cortex targets to VS Code.

A debugging target for the MCU for your board needs to be defined, and can be done so by adding the following to a `.vscode/launch.json` file:

```json
{
  // Use IntelliSense to learn about possible attributes.
  // Hover to view descriptions of existing attributes.
  // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Black Magic Probe (OneKey Proton-C)",
      "type": "cortex-debug",
      "request": "launch",
      "cwd": "${workspaceRoot}",
      "executable": "${workspaceRoot}/.build/handwired_onekey_proton_c_default.elf",
      "servertype": "bmp",
      "BMPGDBSerialPort": "COM4",
      "svdFile": "Q:\\svd\\STM32F303.svd",
      "device": "STM32F303",
      "v1": false,
      "windows": {
        "armToolchainPath": "C:\\QMK_MSYS\\mingw64\\bin"
      }
    }
  ]
}
```

You'll need to perform some modifications to the file above in order to target your specific device:

* `"name"`: Can be anything, but if you're debugging multiple targets you'll want something descriptive here.
* `"cwd"`: The path to the QMK Firmware repository root directory -- _if using the `.vscode` directory existing in the `qmk_firmware` git repository, the default above should be correct_
* `"executable"`: The path to the `elf` file generated as part of the build for your keyboard -- _exists in `<qmk_firmware>/.build`_
* `"BMPGDBSerialPort"`: The `COM` port under Windows, or the `/dev/...` path for Linux/macOS. Two serial port devices will be created -- the Black Magic Probe debug port is *usually* the first. If it doesn't work, try the second.
* `"svdFile"`: _[Optional]_ The path to the SVD file that defines the register layout for the MCU -- the appropriate file can be downloaded from the [cmsis-svd repository](https://github.com/posborne/cmsis-svd/tree/master/data/STMicro)
* `"device"`: The name of the MCU, which matches the `<name>` tag at the top of the downloaded `svd` file.
* `"armToolchainPath"`: _[Optional]_ The path to the ARM toolchain installation location on Windows -- under normal circumstances Linux/macOS will auto-detect this correctly and will not need to be specified. 

::: warning
Windows builds of QMK Firmware are generally compiled using QMK MSYS, and the path to gdb's location (`C:\\QMK_MSYS\\mingw64\\bin`) needs to be specified under `armToolchainPath` for it to be detected. You may also need to change the GDB path to point at `C:\\QMK_MSYS\\mingw64\\bin\\gdb-multiarch.exe` in the VSCode Cortex-Debug user settings: ![VSCode Settings](https://i.imgur.com/EGrPM1L.png)
:::

The following modifications must be made to the keyboard's `rules.mk` file to enable debug information and disable optimisations -- this will ensure breakpoints and variable viewing works correctly:
```makefile
# Enable debug information in the final binaries
DEBUG_ENABLE = yes
# Disable optimisations for debugging purposes
LTO_ENABLE = no
OPT = g
```

At this point, you should build and flash your firmware through normal methods (`qmk compile ...` and `qmk flash ...`).

Once completed, you can:
* Switch to the debug view in VS Code (in the sidebar, the Play button with a bug next to it)
* Select the newly-created debug target in the dropdown at the top of the sidebar
* Click the green play button next to the dropdown

VS Code's debugger will then start executing the compiled firmware on the MCU.

At this stage, you should have full debugging set up, with breakpoints and variable listings working!
