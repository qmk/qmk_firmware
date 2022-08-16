# BareDev (rev1)

![PCB](https://i.imgur.com/byquO5u.png)
![Prototype Build](https://i.imgur.com/fkizunN.png)

An open-source, ABNT2-based 70% keyboard, focusing in a smaller footprint while retaining all the functions found on a TKL (Del and arrow keys doubling as the navigational cluster)

* Keyboard Maintainer: [Fernando "ManoShu" Rodrigues](https://github.com/ManoShu)
* Hardware Supported: BareDev rev1 PCB
* Hardware Availability: Files available on [GitHub](https://github.com/ManoShu/BareDev)

Make example for this keyboard (after setting up your build environment):

    make handwired/baredev/rev1:default

Flashing example for this keyboard:

    make handwired/baredev/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available