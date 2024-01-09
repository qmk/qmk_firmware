# LampArray

Implements the open Human Interface Devices (HID) Lighting and Illumination standard.

> LampArray devices have one or more Lamps (i.e. lights/LEDs/bulbs, etc…) that can be directly manipulated; setting state (on/off), brightness and color (RGB).

Windows provides support for devices under [Dynamic Lighting](https://support.microsoft.com/en-us/windows/control-your-dynamic-lighting-devices-in-windows-8e8f22e3-e820-476c-8f9d-9ffc7b6ffcd2).

## Overview

Supported lighting frameworks:

* [RGB Matrix](feature_rgb_matrix.md)

Currently unsupported:

* Split keyboard
* VUSB

## Basic Configuration :id=basic-configuration

To enable this feature, add the following to your `rules.mk`:

    LAMPARRAY_ENABLE = yes

This should provide an out of the box experience, inferred from the existing keyboard and lighting framework configuration.

## Advanced Configuration :id=advanced-configuration

To change the default behavior, you can use the following defines in your `config.h`

|Define         |Default      |Description    |
|---------------|-------------|---------------|
|`X`            |*Not defined*|               |
|`Y`            |*Not defined*|               |
|`Z`            |`7`          |               |
