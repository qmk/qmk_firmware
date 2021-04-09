# Let's Split Vitamins Included

![Let's Split Vitamins included, assmebled in 3D printed case](https://i.imgur.com/btl0vNQ.jpg)

This readme and most of the code are from the lets split readme

## Quick links

[REV1](./rev1/readme.md)  
[REV2](./rev2/readme.md)

## Hardware

Hardware files for the Let's Split vitamins included are stored [here](https://git.io/vita-inc)

## Features

Some features supported by the firmware:

* Either half can connect to the computer via USB, or both halves can be used independently.
* Optional support for I2C connection between the two halves if for some
  reason you require a faster connection between the two halves. Note that this requires 4 conductors between halves, and as such requires a TRRS cable.

## Required Hardware

|Amount| Description |
|--|--|
| 1 | PCB kit from novelkeys |
| 48 | MX compatible switches |
| 48 | 1U keycaps
| 1 | Mini-usb-B cable or USB-C cable for rev2. Keep in mind rev2.0 doesn't work with USB-C <> USB-C cables|
| 1 | TRS / TRRS cable

## Optional Hardware

A speaker can be hooked-up to the footprint on the PCBs. It is already enabled in the default firmware.

WS2812 LEDs can be added to the board. Check the different revision readme for specifics.

## Using I2C

On  the left half PCB, there's two pads labled ***I2C Pullup*** if you want to use I2C, you need to bridge those two solder jumpers with a soldering iron.

You can change your configuration between serial and i2c by modifying your `config.h` file.
