# IBM 4704 display terminal keyboard (Pingmaster)
![IBM 4704 display terminal keyboard (Pingmaster)](https://deskthority.net/wiki/images/d/da/6112884_1.jpg)

This is a port of TMK's converter/ibm4704_usb to QMK.

This firmware converts IBM 4704 keyboard protocol to USB HID.
Keyboard initialization process takes a few seconds at start up. You may need to plug USB cable after hooking up your keyboard to the converter.

Source code: https://github.com/qmk/qmk_firmware.git  
Article: https://geekhack.org/index.php?topic=72052.0

# Supported Keyboard

Alps SKCC (vintage Green) models:
5954339 Japanese 102-key http://deskthority.net/post87127.html#p87127
6112883 Japanese 102-key http://geekhack.org/index.php?topic=52888.msg1194489#msg1194489
6112884 Japanese 102-key http://geekhack.org/index.php?topic=50437.msg1193047#msg1193047
6341739 Chinese  102-key http://geekhack.org/index.php?topic=52888.msg1176566#msg1176566

# Connector

```
Keyboard Plug from front:

    DSUB-9
    -------------
    \ N 2 3 4 5 /
     \ N N N N /
      ---------
    2   GND
    3   VCC 5V
    4   DATA
    5   CLOCK
    N   No connection/No pin.

```

# Connection

In case of using ATMega32U4/U2

1. Supply power with VCC and GND.
2. Connect CLOCK to PD1 and DATA to PD0. You can change pin with config.h.
3. Optionally you may need pull-up register. 1KOhm probably work.

A detailed tutorial on how to prepare the external converter can be found [here](https://bitswamp.com/2018/08/27/hasu-converter-for-pingmaster/)

# Build

Make example for this keyboard (after setting up your build environment):

    make converter/ibm_pingmaster:default

Flashing example for this keyboard:

    make converter/ibm_pingmaster:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
