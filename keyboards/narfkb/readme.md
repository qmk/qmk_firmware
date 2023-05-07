# Narfkb

![NarfKb](https://i.imgur.com/mS8wlpZ.jpg)

Built using two Waveshare RP2040-Zero controllers, this custom split PCB based design isn't quite the typical 3x5_3 physical layout.

The finger keys use MX switches whilst the thumb cluster is composed of 2 rows; lower row has three choc switches and the higher row has three Omrom 6mm Tact switches, which are intended for key combos/shortcuts and macros.  
Fitted with a rotary encoder on each half, halves are joined with a TRRS/4-pole 3.5mm cable. Split body communication protocol is configured to USART Full-Duplex with PIO driver subsystem.

* Keyboard Maintainer: [Sebastian Stumpf](https://github.com/sebastian-stumpf)
* Hardware Supported: Waveshare RP2040-Zero controller, EC-11 Encoders
* Hardware Availability: [Bill of Materials](https://github.com/sebastian-stumpf/narfkb)

Make example for this keyboard (after setting up your build environment):

    make narfkb:default

Flashing example for this keyboard:

    make narfkb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press twice the key mapped to `QK_BOOT` if it is available 
