JM60
========

A compact 60% keyboard with full RGB led support.

Keyboard Maintainer: QMK Community  
Hardware Supported: JM60  
Hardware Availability: https://kbdfans.myshopify.com/ (is no longer sold)

Make example for this keyboard (after setting up your build environment):

    make jm60:default:bin

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Flashing Instructions

1) from the `qmk_firmware` directory run:
```
$ make jm60:default:bin
```

2) rename 'jm60_default.bin' to 'jm60_default.firmware'

3) Press 'R' and reconnect the keyboard.

4) Start the original Configuration Tool and flash 'jm60_default.bin'
