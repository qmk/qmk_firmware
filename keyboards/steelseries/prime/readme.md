# SteelSeries Prime

![Prime](https://i.imgur.com/rPIKok3.jpeg)

Erase with an stlink and flash this [uf2boot bootloader](https://github.com/daskygit/uf2-prime-plus), this is a a one way procedure voiding any warranty so be sure you don't want to use the original manufacturers firmware.

you may need to remove write protection to flash, e.g. with openocd in linux

```sh
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "init; reset halt; stm32f1x unlock 0; flash protect 0 0 last off; reset halt; exit"

```

and write the new bootloader

```sh

openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program build/PRIME_PLUS/uf2boot.bin  verify reset exit 0x8000000"

```

* Keyboard Maintainer: [Dasky](https://github.com/daskygit)
* Hardware Supported: SteelSeries Prime
* Hardware Availability: https://steelseries.com/gaming-mice/prime

Make example for this keyboard (after setting up your build environment):

    make steelseries/prime:default

Flashing example for this keyboard:

    make steelseries/prime:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down left mouse button and plug in.
* **Bootloader entry**: Hold the underneath button while plugging in.
