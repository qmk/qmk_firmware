# Flashing Your Keyboard 

Now that you've built a custom firmware file you'll want to flash your keyboard. 

## Flashing Your Keyboard with QMK Toolbox

The simplest way to flash your keyboard will be with the [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases). 

However, the QMK Toolbox is only available for Windows and macOS currently.  If you're using Linux (or just wish to flash the firmware from the command line), you'll have to use the [method outlined below](newbs_flashing.md#flash-your-keyboard-from-the-command-line).

### Load The File Into QMK Toolbox

Begin by opening the QMK Toolbox application. You'll want to locate the firmware file in Finder or Explorer. Your keyboard firmware may be in one of two formats- `.hex` or `.bin`. QMK tries to copy the appropriate one for your keyboard into the root `qmk_firmware` directory.

If you are on Windows or macOS there are commands you can use to easily open the current firmware folder in Explorer or Finder.

#### Windows

```
start .
```

#### macOS

```
open .
```

The firmware file always follows this naming format:

```
<keyboard_name>_<keymap_name>.{bin,hex}
```

For example, the `planck/rev5` with a `default` keymap will have this filename:

```
planck_rev5_default.hex
```

Once you have located your firmware file drag it into the "Local file" box in QMK Toolbox, or click "Open" and navigate to where your firmware file is stored. 

### Put Your Keyboard Into DFU (Bootloader) Mode

In order to flash your custom firmware you have to put your keyboard into a special flashing mode. While it is in this mode you will not be able to type or otherwise use your keyboard. It is very important that you do not unplug your keyboard or otherwise interrupt the flashing process while the firmware is being written.

Different keyboards have different ways to enter this special mode. If your PCB currently runs QMK or TMK and you have not been given specific instructions try the following, in order:

* Hold down both shift keys and press `Pause`
* Hold down both shift keys and press `B`
* Unplug your keyboard, hold down the Spacebar and `B` at the same time, plug in your keyboard and wait a second before releasing the keys
* Press the physical `RESET` button on the bottom of the PCB
* Locate header pins on the PCB labeled `BOOT0` or `RESET`, short those together while plugging your PCB in

When you are successful you will see a message similar to this in QMK Toolbox:

```
*** Clueboard - Clueboard 66% HotSwap disconnected -- 0xC1ED:0x2390
*** DFU device connected
```

### Flash Your Keyboard

Click the `Flash` button in QMK Toolbox. You will see output similar to the following:

```
*** Clueboard - Clueboard 66% HotSwap disconnected -- 0xC1ED:0x2390
*** DFU device connected
*** Attempting to flash, please don't remove device
>>> dfu-programmer atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer atmega32u4 flash /Users/skully/qmk_firmware/clueboard_66_hotswap_gen1_skully.hex
    Checking memory from 0x0 to 0x55FF...  Empty.
    0%                            100%  Programming 0x5600 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x5600 bytes written into 0x7000 bytes memory (76.79%).
>>> dfu-programmer atmega32u4 reset
    
*** DFU device disconnected
*** Clueboard - Clueboard 66% HotSwap connected -- 0xC1ED:0x2390
```

## Flash your Keyboard from the Command Line

This has been made pretty simple compared to what it used to be.  When you are ready to compile and flash your firmware, open up your terminal window and run the flash command: 

    qmk flash

If you have not configured your keyboard/keymap name, or you have multiple keyboards, you can specify the keyboard and keymap:

    qmk flash -kb <my_keyboard> -km <my_keymap>

This will check the keyboard's configuration, and then attempt to flash it based on the specified bootloader.  This means that you don't need to know which bootloader that your keyboard uses.  Just run the command, and let the command do the heavy lifting.

However, this does rely on the bootloader being set by the keyboard.  If this information is not configured, or you're using a board that doesn't have a supported target to flash it, you will see this error:

    WARNING: This board's bootloader is not specified or is not supported by the ":flash" target at this time.

In this case, you'll have to fall back on specifying the bootloader.

There are five main bootloaders that are used. Pro Micro and clones use Caterina, Teensys use HalfKay, OLKB's AVR boards use QMK-DFU, other ATmega32U4 boards use DFU, and most ARM boards use ARM DFU.

You can find more information about the bootloaders in the [Flashing Instructions and Bootloader Information](flashing.md) page. 

If you know what bootloader that you're using you can specify that in your flash command:

    qmk flash -bl <bootloader>

Run this command to get a list of valid bootloaders:

    qmk flash --bootloaders

### More information

See the Flashing documentation for more information on esoteric flashing situations.

## Test It Out!

Congrats! Your custom firmware has been programmed to your keyboard!

Give it a try and make sure everything works the way you want it to. We've written [Testing and Debugging](newbs_testing_debugging.md) to round out this Newbie Guide, so head over there to learn about validating your firmware and how to troubleshoot your custom functionality.
