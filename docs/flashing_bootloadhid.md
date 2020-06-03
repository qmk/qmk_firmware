# BootloadHID Flashing Instructions and Bootloader Information

ps2avr(GB) boards use an ATmega32A microcontroller and a different bootloader. It is not flashable using the regular QMK methods.

General flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `RESET` keycode (may not work on all devices)
    * Hold the salt key while plugging the keyboard in (usually documented within keyboard readme) 
2. Wait for the OS to detect the device
3. Flash a .hex file
4. Reset the device into application mode (may be done automatically)

## bootloadHID Flashing Target

?> Using the QMK installation script, detailed [here](newbs_getting_started.md), the required bootloadHID tools should be automatically installed.

To flash via the command line, use the target `:bootloadHID` by executing the following command:

    make <keyboard>:<keymap>:bootloadHID

## GUI Flashing

### Windows
1. Download [HIDBootFlash](http://vusb.wikidot.com/project:hidbootflash).
2. Place your keyboard into reset. 
3. Ensure the configured VendorID is `16c0` and ProductID is `05df`
4. Press the `Find Device` button and ensure that your keyboard is found.
5. Press the `Open .hex File` button and locate the `.hex` file you created.
6. Press the `Flash Device` button and wait for the process to complete.

## Command Line Flashing

1. Place your keyboard into reset. 
2. Flash the board by typing `bootloadHID -r` followed by the path to your `.hex` file.

### Windows Manual Installation
For MSYS2:
1. Download the BootloadHID firmware package from https://www.obdev.at/downloads/vusb/bootloadHID.2012-12-08.tar.gz.
2. Extract contents using a compatible tool, for example 7-Zip.
3. Add to the MSYS path by copying `commandline/bootloadHID.exe` from the extracted archive to your MSYS2 installation, typically `C:\msys64\usr\bin`.

For native Windows flashing, the `bootloadHID.exe` can be used outside of the MSYS2 environment.

### Linux Manual Installation
1. Install libusb development dependency:
    ```bash
    # This depends on OS - for Debian the following works
    sudo apt-get install libusb-dev
    ```
2. Download the BootloadHID firmware package:
    ```
    wget https://www.obdev.at/downloads/vusb/bootloadHID.2012-12-08.tar.gz -O - | tar -xz -C /tmp
    ```
3. Build the bootloadHID executable:
    ```
    cd /tmp/bootloadHID.2012-12-08/commandline/
    make
    sudo cp bootloadHID /usr/local/bin
    ```

### MacOS Manual Installation
1. Install Homebrew by typing the following:
    ```
    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    ```
2. Install the following packages:
    ```
    brew install --HEAD https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb
    ```
