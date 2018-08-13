TADA68
======

A compact 65% keyboard.

Keyboard Maintainer: QMK Community  
Hardware Supported: TADA68 PCB  
Hardware Availability: [kbdfans](https://kbdfans.myshopify.com/products/tada68-mechanical-keyboard-gateron-swtich-65-layout-dye-sub-keycaps-cherry-profils?variant=34710238797), [kbdist](http://www.kbdist.com/)

Make example for this keyboard (after setting up your build environment):

    make tada68:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Firmware Format

Out of the box the tada68 uses a .bin firmware file instead of a .hex like other custom keyboards. By default QMK will build and copy the correct .bin file for you. If for some reason you need a hex file instead, you can add `:hex` to your make command, or look inside `qmk_firmware/.build` to find the hex file.

## Flashing Instructions (Win)

*Read all the instructions, there are a few warnings of things to avoid doing to avoid bricking your Tada68. __It is much too easy to do!__*

1) from the `qmk_firmware\` directory run:
```
$ make tada68:default:flashbin
```

2) Connect your keyboard to Windows computer, hit the reset button on the TADA, the lights will start flashing.

3) You'll see a new drive on your computer called TADA68. Backup the original factory `FLASH.BIN` file thats inside it.

4) Delete `FLASH.BIN` from the TADA drive and copy `tada68_default.bin` that was generated at the root of the qmk directory into the TADA drive.

5) *Do not eject the USB device.* Hit ESC on the keyboard. The lights will stop flashing and your firmware is loaded!

## Flashing Instructions (Mac)

*When flashing the keyboard from a Mac, you must delete some files that are automatically created by the operating system in order to prevent bricking your keyboard.  Original information from /u/pawlwall from https://www.reddit.com/r/MechanicalKeyboards/comments/520cov/using_an_originative_tada86_on_a_mac/*

1) from the `qmk_firmware\` directory run:
```
$ make tada68:default:flashbin
```

2) Connect your keyboard to your Mac, hit the reset button on the bottom of the TADA, the lights will start flashing.

3) You'll see a new drive on your computer called TADA68. Backup the original factory `FLASH.BIN` file that's inside it.

4) Open the terminal and cd to the folder where the keyboard has been mounted

`cd /Volumes/TADA68\ /`

5) Copy over your new firmware to the keyboard

`cp -r <path to your qmk_firmware folder>/FLASH.bin .`

6) Remove files that MacOS automatically created which interfere with the keyboard

`rm -fr .Trashes/ .fseventsd/ ._.Trashes ._FLASH.bin`

7) Eject the USB device or hit ESC on the keyboard. The lights will stop flashing and your firmware is loaded!

## Flashing Instructions (Linux)

*Use these instructions at your own risk. Mount settings originally found at https://www.reddit.com/r/MechanicalKeyboards/comments/8e2nnp/help_problems_flashing_firmware_on_tada68_from/*

1) from the `qmk_firmware\` directory run:
```
$ make tada68:default:flashbin
```

2) Connect your keyboard to Windows computer, hit the reset button on the TADA, the lights will start flashing.

3) A new entry should appear at `/dev/sd*`. Mount the board using this command:

```
mount -t vfat -o rw,nosuid,nodev,relatime,uid=1000,gid=1000,fmask=0022,dmask=0022,codepage=437,iocharset=iso8859-1,shortname=mixed,showexec,utf8,flush,errors=remount-ro,uhelper=udisks2 <path to device> /mnt/tada68
```

4) Back up the original firmware

`mv /mnt/tada68/FLASH.BIN ~`

5) Copy over your new firmware to the keybaord

`cp <path to your qmk_firmware folder>/FLASH.bin /mnt/tada68`

5) *Do not eject the USB device.* Hit ESC on the keyboard. The lights will stop flashing and your firmware is loaded!
