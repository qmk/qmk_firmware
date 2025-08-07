# MariOrion v2.5

![mariorion_v25_1](https://i.imgur.com/PFb6AGo.jpg)
![mariorion_v25_2](https://i.imgur.com/Fgdm2fx.jpg)

This project was a revival of the Duck Orion v2.5, where we don't have very many PCBs with modern features, and
especially Alps support as well. This PCB has both Alps and MX support as well as universal layout support! It also
features a 3u/1u/3u split spacebar variant for fun :)

The prototype version is for use only by Maria, and it's the r0 run in essence. Please do use prod unless otherwise
stated (prod me if you're confused, @mawiaa on Discord)!

* Keyboard Maintainer: [Maria](https://github.com/toril940)
* Hardware Supported: MariOrion v2.5 PCB
* Hardware Availability: Link coming soon, through Hineybush :)

Make example for this keyboard (after setting up your build environment):

    make mariorion_v25/prod:default
    make mariorion_v25/proto:default

Flashing example for this keyboard:

    make mariorion_v25/prod:default:flash
    make mariorion_v25/proto:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Hold the reset button on the back of the PCB for 4-10 seconds or so -
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
