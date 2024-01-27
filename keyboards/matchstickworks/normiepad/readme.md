# NormiePad

# UPDATE THIS THO OKAY?!?!
![Southpad](https://i.imgur.com/Wl71thnh.jpg)

This is a standard layout numberpad with USB-C connection and Kailh hotswap sockets, built on the RP2040 MCU.

Default layout is such:

# UPDATE THIS THO OKAY?!?!
![NormiePad Layout](https://i.imgur.com/jc7T2jl.jpg)

* Keyboard Maintainer: [Logan Butler](https://github.com/MatchstickWorks)
* Hardware Supported: NormiePad PCB
* Hardware Availability: Either via [my storefront](https://matchstick.works), [my Etsy Store](https://www.etsy.com/shop/MatchstickWorksShop), or by messaging directly

Getting the board into bootloader mode:

In order to flash the firmware to this board, simply press both the RESET and BOOT buttons on the back of the PCB. You will hear a reconnect sound on your computer and a file explorer window should open where you can drag and drop the compiled UF2 into.

Make example for this keyboard (after setting up your build environment):

    make matchstickworks/normiepad:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
