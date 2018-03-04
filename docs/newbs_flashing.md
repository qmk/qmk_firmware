# Flashing Your Keyboard With QMK Toolbox

Now that you've built a custom firmware file you'll want to flash your keyboard. 

## Load The File Into QMK Toolbox

Begin by opening the QMK Toolbox application. You'll want to locate the firmware file in Finder or Explorer. Your keyboard firmware may be in one of two formats- `.hex` or `.bin`. QMK tries to copy the appropriate one for your keyboard into the root `qmk_firmware` directory.

{% hint style='info' %}
If you are on Windows or macOS there are commands you can use to easily open the current firmware folder in Explorer or Finder.

Windows:

    start .

macOS:

    open .
{% endhint %}

The firmware file always follows this naming format:

    <keyboard_name>_<keymap_name>.{bin,hex}

For example, the `plank/rev5` with a `default` keymap will have this filename:

    planck_rev5_default.hex

Once you have located your firmware file drag it into the "Local file" box in QMK Toolbox, or click "Open" and navigate to where your firmware file is stored. 

## Put Your Keyboard Into DFU (Bootloader) Mode

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

## Flash Your Keyboard

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

## Test It Out!

Congrats! Your custom firmware has been programmed to your keyboard!

Give it a try and make sure everything works the way you want it to. We've written [Testing and Debugging](newbs_testing_debugging.md) to round out this Newbie Guide, so head over there to learn about how to troubleshoot your custom functionality.
