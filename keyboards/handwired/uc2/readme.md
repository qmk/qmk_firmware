# Universal-Century 2

![UC2](https://i.imgur.com/sl2A7q3l.jpeg)

The Universal-Century 2 (UC2) is a 86-key split keyboard, TKL size with 3-key thumb cluster and encoders. 

The Layout base on [Willow Layout](https://github.com/hanachi-ap/willow64-doc), CC BY-SA 4.0 by Hanachi. Thank you so much Mr. Hanachi!

![FDM PCB Board](https://imgur.com/Obr9v1yl.jpeg)

PCB using FDM 3D printer and hand wiring, Non-factory PCB, Layout design using [Keyboard-layout-editor.com (KLE)](http://www.keyboard-layout-editor.com/) web application, 3D file(.STL) build using [hotswap_pcb_generator](https://github.com/AndyChiu/hotswap_pcb_generator) OpenSCAD script.

![Left Hand](https://i.imgur.com/FnKEIS4l.jpeg)
![Right Hand](https://i.imgur.com/pPTj6vCl.jpeg)

* Keyboard Maintainer: [AndyChiu](https://github.com/AndyChiu)
* Hardware Supported: Hand wired
* Hardware Availability: [Open-source](https://github.com/AndyChiu/UC2)

Make example for this keyboard (after setting up your build environment):

    make handwired/uc2:default

Enable VIA feature in QMK

    make handwired/uc2:via

Flashing example for this keyboard:

    make handwired/uc2:via:flash


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
