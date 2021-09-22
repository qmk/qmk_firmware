# mekanist keymap instructions

## Dev Environment setup (macOS)

1. Install Homebrew by copy pasting the following into a terminal:
    ```
    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    ```

2. Refer to the [QMK macOS Instructions](https://github.com/qmk/qmk_firmware/blob/master/docs/getting_started_build_tools.md#macos) and install the list of tools using the `brew` command in terminal. 

3. While in terminal, issue the following command within the directory you wish to clone qmk_firmware in. 

    ```
    git clone https://github.com/qmk/qmk_firmware.git
    ```

## Creating the mekanist dz60rgb firmware file

1. While in the `qmk_firmware` directory, issue the following command

    ```
    make git-submodule
    ```

    This will download the chibi-os submoduled needed to create firmware for ARM based boards such as the dz60rgb. 

2. While in the `qmk_firmware` directory, issue the followng command

    ```
    make dztech/dz60rgb:mekanist
    ```

    This will result in a file called `dztech_dz60rgb_mekanist.bin` that you can flash onto your board using QMK Toolbox. 
