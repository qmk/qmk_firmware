# Flashing Your Keyboard

Now that you've built a custom firmware file you'll want to flash your keyboard.

## Put Your Keyboard into DFU (Bootloader) Mode

In order to flash your custom firmware you must first put your keyboard into a special flashing mode. While it is in this mode you will not be able to type or otherwise use your keyboard. It is very important that you do not unplug the keyboard or otherwise interrupt the flashing process while the firmware is being written.

Different keyboards have different ways to enter this special mode. If your PCB currently runs QMK, TMK, or PS2AVRGB (Bootmapper Client) and you have not been given specific instructions, try the following, in order:

* Hold down both shift keys and press `Pause`
* Hold down both shift keys and press `B`
* Unplug your keyboard, hold down the Spacebar and `B` at the same time, plug in your keyboard and wait a second before releasing the keys
* Unplug your keyboard, hold down the top or bottom left key (usually Escape or Left Control) and plug in your keyboard
* Press the physical `RESET` button, usually located on the underside of the PCB
* Locate header pins on the PCB labeled `RESET` and `GND`, and short them together while plugging your PCB in

If you've attempted all of the above to no avail, and the main chip on the board says `STM32` on it, this may be a bit more complicated. Generally your best bet is to ask on [Discord](https://discord.gg/Uq7gcHh) for assistance. It's likely some photos of the board will be asked for -- if you can get them ready beforehand it'll help move things along!

Otherwise, you should see a message in yellow, similar to this in QMK Toolbox:

```
*** DFU device connected: Atmel Corp. ATmega32U4 (03EB:2FF4:0000)
```

and this bootloader device will also be present in Device Manager, System Information.app, or `lsusb`.

## Flashing Your Keyboard with QMK Toolbox

The simplest way to flash your keyboard will be with the [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases).

However, the Toolbox is currently only available for Windows and macOS. If you're using Linux (or just wish to flash the firmware from the command line), skip to the [Flash your Keyboard from the Command Line](#flash-your-keyboard-from-the-command-line) section.

### Load the File into QMK Toolbox

Begin by opening the QMK Toolbox application. You'll want to locate the firmware file in Finder or Explorer. Your keyboard firmware may be in one of two formats- `.hex` or `.bin`. QMK tries to copy the appropriate one for your keyboard into the root `qmk_firmware` directory.

If you are on Windows or macOS, there are commands you can use to easily open the current folder in Explorer or Finder.

<!-- tabs:start -->

#### ** Windows **

```
start .
```

#### ** macOS **

```
open .
```

<!-- tabs:end -->

The firmware file always follows this naming format:

```
<keyboard_name>_<keymap_name>.{bin,hex}
```

For example, the `planck/rev5` with a `default` keymap will have this filename:

```
planck_rev5_default.hex
```

Once you have located your firmware file, drag it into the "Local file" box in QMK Toolbox, or click "Open" and navigate to where your firmware file is stored.

### Flash Your Keyboard

Click the `Flash` button in QMK Toolbox. You will see output similar to the following:

```
*** DFU device connected: Atmel Corp. ATmega32U4 (03EB:2FF4:0000)
*** Attempting to flash, please don't remove device
>>> dfu-programmer.exe atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer.exe atmega32u4 flash "D:\Git\qmk_firmware\gh60_satan_default.hex"
    Checking memory from 0x0 to 0x3F7F...  Empty.
    0%                            100%  Programming 0x3F80 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x3F80 bytes written into 0x7000 bytes memory (56.70%).
>>> dfu-programmer.exe atmega32u4 reset
    
*** DFU device disconnected: Atmel Corp: ATmega32U4 (03EB:2FF4:0000)
```

## Flash your Keyboard from the Command Line

This has been made pretty simple compared to what it used to be. When you are ready to compile and flash your firmware, open up your terminal window and run the flash command:

    qmk flash

If you did not configure your keyboard/keymap name in the CLI according to the [Configure your build environment](newbs_getting_started.md) section, or you have multiple keyboards, you can specify the keyboard and keymap:

    qmk flash -kb <my_keyboard> -km <my_keymap>

This will check the keyboard's configuration, and then attempt to flash it based on the specified bootloader. This means that you don't need to know which bootloader that your keyboard uses. Just run the command, and let the command do the heavy lifting.

However, this does rely on the bootloader being set by the keyboard. If this information is not configured, or you're using a board that doesn't have a supported target to flash it, you will see this error:

    WARNING: This board's bootloader is not specified or is not supported by the ":flash" target at this time.

In this case, you'll have to fall back on specifying the bootloader. See the [Flashing Firmware](flashing.md) Guide for more details.

!> If your bootloader is not detected by `qmk flash`, try running `qmk doctor` for suggestions on how to fix common problems.

## Test It Out!

Congrats! Your custom firmware has been programmed to your keyboard and you're ready to test it out!

With a little bit of luck everything will work perfectly, but if not there are steps that will help you figure out what's wrong.
Testing your keyboard is usually pretty straightforward. Press every single key and make sure it sends the keys you expect. You can use [QMK Configurator](https://config.qmk.fm/#/test/)'s test mode to check your keyboard, even if it doesn't run QMK.

Still not working? Browse the FAQ topics for more information, or [chat with us on Discord](https://discord.gg/Uq7gcHh).
