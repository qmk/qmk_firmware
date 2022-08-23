# Office60

A handwired 60 percent keyboard project using the bluepill microcontroller. It is a no-frills build with no LED lighting or rotary encoder, designed for typing in an office environment. A project for those who want to get started with handwiring a bluepill-based board with a common 60% layout. 

* Keyboard Maintainer: [Jia Geng](https://github.com/JiaGengChang)
* Hardware Supported: STM32F103C8T6 (aka the Blue Pill)
* Hardware Availability: Search "bluepill stm32" on aliexpress, and choose the unwelded version if possible since we will be soldering wires directly onto the board

Make example for this keyboard (after setting up your build environment):

    make handwired/justageng/office60:default

Flashing example for this keyboard:

    make handwired/justageng/office60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader the following 2 ways:
* **Bootmagic**: Hold down the escape key, or the key at the top left corner
* **Physical reset button**: Briefly press the reset button on the bluepill 


## Windows 10 instructions for flashing firmware:
Tools needed:
1. *st-link* command line utility (v1.7.0)
2. *dfu-util* command line utility (dfu-util 0.11)
After installation, add their executable paths to your environment variables for the commands below to work.

### Flashing the stm32duino bootloader:
Obtain the bootloader ``.bin`` file from this wonderful github repository: https://github.com/rogerclarkmelbourne/STM32duino-bootloader

Navigation: bootloader-only-binaries -> generic_boot20_pc13.bin -> Download raw

Hook up the bluepill to the ST-LINK. Set BOOT0 jumper to 1, and remove the BOOT1 jumper. The BOOT1 jumper does not need to be inserted in anywhere, from start to finish.

Flash the bootloader using ST-LINK. First connect ST-LINK to your computer, and type the following command
```
st-info --probe
```
to verify that ST-LINK is connected. To flash bootloader, use the command:
```
st-flash --reset --format binary write /path/to/bootloader/file 0x8000000
```
where you replace ``/path/to/bootloader/file`` with the path of your downloaded bootloader file e.g. ``C:\Users\Jia Geng\Downloads\generic_boot20_pc13.bin``

After success, set BOOT0 jumper to 0, and unplug the ST-LINK from your computer (order does not matter). BOOT1 jumper is disconnected througout.

Similar instructions up to this stage available at https://github.com/rogerclarkmelbourne/Arduino_STM32/wiki/Flashing-Bootloader-for-BluePill-Boards. Also see the 'wrong pull-up resistor issue' for some bluepill variations.

### Flashing qmk firmware:
Connect USB port on the blue pill to your computer. It should show up under device manager as "Maple 003" under USB devices.
Running ``lsusb`` in the command prompt should show a device with the vendor id/product id of ``1eaf:0003``. If so, you are good to move on.

To check that dfu-util can detect dfu-capable device, run the following in command prompt:
```
dfu-util -l
```
to list available devices. There should be *three* options with the name "1eaf:0003", corresponding to the main, legacy, and protected version provided by the bootloader, shown below. 

```
C:\Users\Jia Geng>dfu-util -l
dfu-util 0.11

Copyright 2005-2009 Weston Schmidt, Harald Welte and OpenMoko Inc.
Copyright 2010-2021 Tormod Volden and Stefan Schmidt
This program is Free Software and has ABSOLUTELY NO WARRANTY
Please report bugs to http://sourceforge.net/p/dfu-util/tickets/

Found DFU: [1eaf:0003] ver=0201, devnum=36, cfg=1, intf=0, path="1-1", alt=2, name="STM32duino bootloader v1.0  Upload to Flash 0x8002000", serial="LLM 003"
Found DFU: [1eaf:0003] ver=0201, devnum=36, cfg=1, intf=0, path="1-1", alt=1, name="STM32duino bootloader v1.0  Upload to Flash 0x8005000", serial="LLM 003"
Found DFU: [1eaf:0003] ver=0201, devnum=36, cfg=1, intf=0, path="1-1", alt=0, name="STM32duino bootloader v1.0  ERROR. Upload to RAM not supported.", serial="LLM 003"
```

We will flash bootloader into main version of the device, with alternate=2.

```
dfu-util -d 1eaf:0003 -a 2 -D /path/to/qmk/firmware/file 
```
where ``/path/to/qmk/firmware/file`` is the path to the Office60 keyboard firmware ``.bin`` file (e.g. ``/c/msys64/home/Jia_Geng/qmk_firmware/handwired_justageng_office60_default.bin``).

If it works, press the reset button on the blue pill, or reconnect the USB. Running ``lsusb`` should show a device with the vid/pid "0FF1:CE60". This will show up as a keyboard in device manager. 

## Potential issues
If you get an error like "LIBUSB_ERROR_IO" when running the last dfu-util command, then your bluepill is not compatible. Example error message shown below:
```
C:\Users\Jia Geng>dfu-util -d 1eaf:0003 -a 2 -D ..\..\msys64\home\Jia_Geng\qmk_firmware\handwired_justageng_office60_default.bin
dfu-util 0.11

Copyright 2005-2009 Weston Schmidt, Harald Welte and OpenMoko Inc.
Copyright 2010-2021 Tormod Volden and Stefan Schmidt
This program is Free Software and has ABSOLUTELY NO WARRANTY
Please report bugs to http://sourceforge.net/p/dfu-util/tickets/

Failed to retrieve language identifiers
Failed to retrieve language identifiers
Opening DFU capable USB device...
Device ID 1eaf:0003
Device DFU version 0110
Claiming USB DFU Interface...
Setting Alternate Interface #2 ...
Cannot set alternate interface: LIBUSB_ERROR_IO
```
You probably got a defective unit from the manufacturer, and I do not know how to fix this apart from buying a new bluepill and praying that it does not come with the incompatible version. This defective bluepill also gives a strange output for dfu-util list when the BOOT1 jumper is disconnected (if BOOT1 jumper is connected, the --list output is identical to the compatible bluepill - qmk firmware will not be flashed successfully even if command prompt says its successful):

```
C:\Users\Jia Geng>dfu-util -l
dfu-util 0.11

Copyright 2005-2009 Weston Schmidt, Harald Welte and OpenMoko Inc.
Copyright 2010-2021 Tormod Volden and Stefan Schmidt
This program is Free Software and has ABSOLUTELY NO WARRANTY
Please report bugs to http://sourceforge.net/p/dfu-util/tickets/

Failed to retrieve language identifiers
Failed to retrieve language identifiers
Failed to retrieve language identifiers
Failed to retrieve language identifiers
Failed to retrieve language identifiers
Failed to retrieve language identifiers
Found DFU: [1eaf:0003] ver=0201, devnum=27, cfg=1, intf=0, path="1-1", alt=2, name="UNKNOWN", serial="UNKNOWN"
Found DFU: [1eaf:0003] ver=0201, devnum=27, cfg=1, intf=0, path="1-1", alt=1, name="UNKNOWN", serial="UNKNOWN"
Found DFU: [1eaf:0003] ver=0201, devnum=27, cfg=1, intf=0, path="1-1", alt=0, name="UNKNOWN", serial="UNKNOWN"
```
