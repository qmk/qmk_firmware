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
Before starting, you will want to make sure that you have all of the build tools set up, and QMK Firmware cloned. Head to the [Newbs Getting Started Guide](newbs_getting_started.md) to get things set up, if you haven't already.

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

?> If you installed MSYS2 to a different folder, then you'll need to change the path for `terminal.integrated.shell.windows` to the correct path for your system. 

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

1. Run `qmk generate-compilation-database -kb <keyboard> -km <keymap>` to generate the `compile_commands.json`.
1. Inside VS code, press <kbd><kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd></kbd> (macOS: <kbd><kbd>Command</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd></kbd>) to open the command palette.
1. Start typing `clangd: Download Language Server` and select it when it appears. Note that this only needs to be done once on clangd extension installation, if it didn't already ask to do so.
1. Inside VS code, press <kbd><kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd></kbd> (macOS: <kbd><kbd>Command</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd></kbd>) to open the command palette.
1. Start typing `clangd: Restart Language Server` and select it when it appears.

Now you're ready to code QMK Firmware in VS Code!
