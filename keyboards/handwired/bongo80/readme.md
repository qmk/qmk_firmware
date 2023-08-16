# Bongo80

![Bongo80](https://i.imgur.com/bL6ZGjVh.jpg?1)
![Wiring](https://i.imgur.com/iivkFWsh.jpg)
*Note that I messed up the matrix on mine (seen above), and had to hook up (1, 1) to be in column 12, as I started soldering before fully planning the keymap 😅. However, this keymap follows the below wiring spec.*
![Wiring Diagram](https://i.imgur.com/d7epIFMh.png)

Based on a KBDfans tiger80 lite chassis and plate, this custom handwired board uses an RP2040 (pi pico) and an oled screen with a typing speed reactive bongo cat animation.

* Keyboard Maintainer: [sam kelly](https://github.com/samkellu)
* Hardware Supported: 
  - 84x Cherry MX style switches
  - 84x 1N148 diodes
  - Raspberry Pi Pico microcontroller
  - SSD1306 OLED 128x64
  - KBDfans tiger80 lite case, plate, gasket socks

* Hardware Availability: 
  - [Case](https://kbdfans.com/collections/tiger-lite/products/kbdfans-tiger-lite-abs-plastic-case)
  - [Plate + Gasket Socks](https://kbdfans.com/products/tiger-lite-keyboard-accessories?pr_prod_strat=copurchase&pr_rec_id=faa28a205&pr_rec_pid=6944675233931&pr_ref_pid=6944669532299&pr_seq=uniform)
  - [Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/)

Make example for this keyboard (after setting up your build environment):

    make handwired/bongo80:default

Flashing example for this keyboard:

    make handwired/bongo80:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Press down the bootsel button on the pico
* **Keycode in layout**: Hold down FN (5, 12) and press ESC (0, 0)
