# Frame 48
![frame](https://i.imgur.com/GnOZPsu.jpg)


A short description of the keyboard/project

* Keyboard Maintainer: [Greg Mathews](https://github.com/gregsqueeb)
* Hardware Supported: Adafruit KB2040

Make example for this keyboard (after setting up your build environment):

    make handwired/frame_48:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).



# %Frame 48%

![frame_48](https://via.placeholder.com/150)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Greg Mathews](https://github.com/gregsqueeb)
* Hardware Supported: Adafruit KB2040
* Hardware Availability:
  * 56 diodes (tme.eu [link](https://www.tme.eu/ro/en/details/1n4148-dio/tht-universal-diodes/diotec-semiconductor/1n4148/)/aliexpress [link](https://www.aliexpress.com/item/32729204179.html))
  * [Work Louder Keycaps](https://worklouder.cc/shop/wrk-legend/). This build was designed with these keycaps in mind.
  * 54/56 choc switches [link](https://mechanicalkeyboards.com/shop/index.php?l=product_detail&p=6337)
  * 24 AWG (0.2 mm2) wire
  * 2 × [Adafruit KB2040](https://www.adafruit.com/product/5302)
  * 1 × [Copper Wire](https://www.amazon.com/dp/B00XHD03EA) for switch connections
  * 2 × EC11 Rotary Encoder (optional/aliexpress [link](https://www.aliexpress.com/item/32872039030.html) mounted to the plate using [this adapter](https://www.thingiverse.com/thing:3770166))
  * 10 × M2×12 allen head screws (aliexpress [link](https://www.aliexpress.com/item/32966941844.html), 14mm overall length, 4mm diameter head)
  * 10 × M2 brass inserts (aliexpress [link](https://www.aliexpress.com/item/4000585933306.html), 3.5mm outer diameter)
  * 2 × PJ320A 3.5mm female audio connectors (aliexpress [link](https://www.aliexpress.com/item/32368285821.html))
  * hot glue for securing the KB2040 to the bottom case (optional, but recommended), the audio connectors, and the switches.

Make example for this keyboard (after setting up your build environment):

    make handwired/frame_48:default

Flashing example for this keyboard:

    make handwired/frame_48:default:flash

## Bootloader

Enter the bootloader:
    Press and hold the BOOT button down.
    Press and release the Reset button.
    Continue holding the BOOT button until you see the RPI-RP2 drive appear.
    You can now release but BOOT button.