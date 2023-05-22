# model_M_122

![IBM Model M 122](https://i.imgur.com/Oo3Ozqzh.jpg)

This is a replacement controller for the IBM Model M 122 key terminal keyboard running on a STM32F411 BlackPill.

The code is based on the work by Jay Maynard (https://github.com/jmaynard), but differs in that this driver
aims only for PC integration (i.e. 3270 compatibility is not present). It assumes the original layout for
the keys (i.e. how this keyboard is always found in the wild) but assumes a modern mapping for the keys.

If you want to use the ANSI layout, please use the model_m_122_ansi driver instead.

* Keyboard Maintainer: [Ferry Hendrikx](https://github.com/fhendrikx)
* Hardware Supported: BlackPill STM32F411
* Hardware Availability: [BlackPill](https://www.adafruit.com/product/4877)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb ibm/model_m122/blackpill -km default

Flashing example for this keyboard:

    qmk flash -kb ibm/model_m122/blackpill -km default


## Bootloader

Enter the bootloader in this way:

* **Physical reset buttons**: Press and hold the BOOT0 button, then press and release RESET. Then release BOOT0.


## Parts List

* 1x Board (as per the notes below)
* 1x BlackPill (you can use the units found on AliExpress)
* 1x 4.7k resister
* 1x  8Pin FPC 2.54 Connector
* 1x 20Pin FPC 2.54 Connector

A schematic and Gerber files are publicly available for those wishing to have carrier boards made
professionally instead of handwiring things. The matrix connectors plug right into it. It can be
found at https://github.com/jmaynard/tronguylabs-m122-blackpill

