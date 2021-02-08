# Manibus keyboard

A 5x7 split ergonomic keyboard designed and sold by [Blank Tehnologii](https://blank.computer/).

Keyboard Maintainer: [Alex Paulescu/SamuraiKek](https://github.com/SamuraiKek)

Hardware Supported: [ATmega32u4](https://www.digikey.com/en/products/detail/microchip-technology/ATMEGA32U4-AU/1914602)

Hardware Availability: [Blank Tehnologii](https://blank.computer/)

Make example for this keyboard (after setting up your build environment):

```make blank_tehnologii/manibus:default```

Example of flashing this keyboard:

Left half: 
```make blank_tehnologii/manibus:default:dfu-split-left```

Right half:
```make blank_tehnologii/manibus:default:dfu-split-right```

See [build environment setup](https://docs.qmk.fm/#/newbs_getting_started?id=_5-configure-your-build-environment-optional) and [handedness by EEPROM](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom) for more information.

