In rare circumstances, your keyboard/device can become unwritable, and `dfu-programmer` will give you an error like this:  

    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
    Checking memory from 0x0 to 0x607F...  Empty.
    0%                            100%  Programming 0x6080 bytes...
    [ X  ERROR
    Memory write error, use debug for more info.

Currently the only way to solve this is to [reprogram the chip via ISP](https://www.reddit.com/r/olkb/comments/4rjzen/flashing_error_on_mac_os_x/d52rj8o/). This requires another device to be hooked up to a couple of exposed pins on the PCB. There is a guide on how to do this [here](https://learn.sparkfun.com/tutorials/installing-an-arduino-bootloader), and [this is where things are on the Planck PCB](http://imgur.com/lvbxbHt).

An example command to flash the board once things are hooked up is:

    avrdude -c usbtiny -p m32u4 -U flash:w:planck_default_rev4.hex

Research is still being done on why this happens, but here are some cases:

* [`make -f Makefile.rn42 dfu` and not the dfu-programmer commands worked for @tybenz](https://github.com/tmk/tmk_keyboard/issues/316) - also see [the hhkb keyboard on tmk](https://github.com/tmk/tmk_keyboard/tree/master/keyboard/hhkb)
* [Doing a force erase works here](https://geekhack.org/index.php?topic=12047.msg1520147#msg1520147)
* [`dfu-programmer atmega32u4 erase --force` works here as well](https://forum.fhem.de/index.php?topic=29777.0) [DE]
* [Unresolved, but some data dumps](https://github.com/dfu-programmer/dfu-programmer/issues/29)