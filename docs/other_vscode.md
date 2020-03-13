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
Before starting, you will want to make sure that you have all of the build tools set up, and QMK Firmware cloned. Head to the the [Newbs Getting Started Guide](newbs_getting_started.md) to get things set up, if you haven't already.

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

### Configuring VS Code

First, we need to set up IntelliSense. This isn't strictly required, but it will make your life a LOT easier. To do this, we need to create the `.vscode/c_cpp_properies.json` file in the QMK Firmware folder, You can do this all manually, but I've done most of the work already. 

Grab [this file](https://gist.github.com/drashna/48e2c49ce877be592a1650f91f8473e8) and save it.  You may need to edit this file, if you didn't install MSYS2 to the default location, or are using WSL/LxSS.  

Once you have saved this file, you will need to reload VS Code, if it was already running. 

?> You should see an `extensions.json` and `settings.json` file in the `.vscode` folder, as well.


Now, we will set up the MSYS2 window to show up in VSCode as the integrated terminal.  This has a number of advantages. Mostly, you can control+click on errors and jump to those files.  This makes debugging much easier.  It's also nice, in that you don't have to jump to another window. 

1. Click <kbd><kbd>File</kbd> > <kbd>Preferences ></kbd> > <kbd>Settings</kbd> </kbd>
2. Click on the <kbd>{}</kbd> button, in the top right to open the `settings.json` file. 
3. Set the file's content to: 

   ```json
   {
        "terminal.integrated.shell.windows": "C:\\msys64\\usr\\bin\\bash.exe",
        "terminal.integrated.env.windows": {
            "MSYSTEM": "MINGW64",
            "CHERE_INVOKING": "1"
        },
        "terminal.integrated.shellArgs.windows": [
            "--login"
        ],
        "terminal.integrated.cursorStyle": "line"
    }
    ```

   If there are settings here already, then just add everything between the first and last curly brackets.  

?> If you installed MSYS2 to a different folder, then you'll need to change the path for `terminal.integrated.shell.windows` to the correct path for your system. 

4. Hit Ctrl-` (grave) to bring up the terminal.  

   This should start the terminal in the workspace's folder (so the `qmk_firmware` folder), and then you can compile your keyboard. 


## Every other Operating System

1. Head to [VS Code](https://code.visualstudio.com/) and download the installer
2. Run the installer
3. That's it

No, really, that's it.  The paths needed are already included when installing the packages, and it is much better about detecting the current workspace files and parsing them for IntelliSense. 

## Plugins

There are a number of extensions that you may want to install:

* [Git Extension Pack](https://marketplace.visualstudio.com/items?itemName=donjayamanne.git-extension-pack) - 
This installs a bunch of Git related tools that may make using Git with QMK Firmware easier.
* [EditorConfig for VS Code](https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig) - _[Optional]_ -  Helps to keep the code to the QMK Coding Conventions.
* [Bracket Pair Colorizer 2](https://marketplace.visualstudio.com/items?itemName=CoenraadS.bracket-pair-colorizer-2) - _[Optional]_ - This color codes the brackets in your code, to make it easier to reference nested code.
* [Github Markdown Preview](https://marketplace.visualstudio.com/items?itemName=bierner.github-markdown-preview) - _[Optional]_ - Makes the markdown preview in VS Code more like GitHub's.
* [VS Live Share Extension Pack](https://marketplace.visualstudio.com/items?itemName=MS-vsliveshare.vsliveshare-pack) - _[Optional]_ - This extension allows somebody else to access your workspace (or you to access somebody else's workspace) and help out.  This is great if you're having issues and need some help from somebody.
* [VIM Keymap](https://marketplace.visualstudio.com/items?itemName=GiuseppeCesarano.vim-keymap) - _[Optional]_ - For those that prefer VIM style keybindings. There are other options for this, too. 
* [Travis CI Status](https://marketplace.visualstudio.com/items?itemName=felixrieseberg.vsc-travis-ci-status) - _[Optional]_ - This shows the current Travis CI status, if you have it set up.

Restart once you've installed any extensions

# Configure VS Code for QMK
1. Click <kbd><kbd>File</kbd> > <kbd>Open Folder</kbd></kbd>
2. Open the QMK Firmware folder that you cloned from GitHub. 
3. Click <kbd><kbd>File</kbd> > <kbd>Save Workspace As...</kbd></kbd>

And now you're ready to code QMK Firmware in VS Code
