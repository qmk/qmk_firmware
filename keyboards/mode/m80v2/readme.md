# Mode Eighty V2 PCB QMK firmware

![MODE80](https://i.imgur.com/26uzM3yl.jpg)\
[Image Gallery](https://imgur.com/t/mechanicalkeyboards/8Uf6c2m?nc=1)

The Mode80 is a tenkeyless high-end keyboard sold by [Mode Designs](https://shop.modedesigns.com/).

* Keyboard Maintainer: [Gondolindrim](https://github.com/gondolindrim)
* Hardware Supported: proprietary PCB using STM32F072 controller
* Hardware Availability: you can get a Mode Eighty as of today (dec. 2021) through the in stock sales or special groupbuy editions at https://shop.modedesigns.com/

## How to flash

### Enter bootloader

The DFU state in the bootloader can be accessed in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: press the button on the front of the PCB, next to caps lock, for at least five seconds
* **Keycode in layout**: Press the key mapped to `RESET` if it is available (ESC key at layer 1 in the default layout)

## Compile firmware

After accessing the DFU state in your PCB, build the default layout using:

    make mode/m80v2/m80v2h:default # Hotswap
    make mode/m80v2/m80v2s:default # Soldered

Then download the resulting binary `*bin` file using `dfu-util` or QMK Toolbox.

## Compile and flash

After accessing the DFU state in your PCB, you can compile-and-flash automatically usind `dfu-util` through

    make mode/m80v2/m80v2h:default:flash # Hotswap
    make mode/m80v2/m80v2s:default:flash # Soldered

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
