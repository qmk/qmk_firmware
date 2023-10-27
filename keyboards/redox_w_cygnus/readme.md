Redox wireless Cygnus
=======

![Redox wireless Cygnus](https://i.imgur.com/jDlgLBN.jpg)

Make example for this keyboard (after setting up your build environment):

```sh
make redox_w_cygnus:default
```

Example of flashing this keyboard:

```sh
make redox_w_cygnus:default:avrdude
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

For nRF51822 firmware upload instruction and development see [the Redox wireless firmware repository](https://github.com/mattdibi/redox-w-firmware).

## Redox-w-cygnus Notes

This keyboard configuration is a direct replica of the [redox_w](https://github.com/qmk/qmk_firmware/tree/master/keyboards/redox_w) keyboard, but with the layout of the Cygnus keyboard. The original configuration for the Cygnus keyboard was based on ZMK, and this configuration was created in QMK based on the [ZMK configuration](https://github.com/Eloy98/zmk-for-cygnus).
