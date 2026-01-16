# posey_split_v5

![posey_split_v5](https://i.imgur.com/g3yf6al.png)

The Posey split keyboard was designed from the gournd up for gaming. By pushing the left half of your split keyboard out of the way, you'll be able to game with better posture and increase mouse movement. PMK's have additional keys on the right half to make sure you don't need to reach for your other half while gaming. 

Version Changes from v4:
-Changed bottom row on the left half to use standard modifier key sizes

* Keyboard Maintainer: [Javier Oliver](https://github.com/joliverMI)
* Hardware Supported: posey_split_v5 and logic_module_v1
* Hardware Availability: poseysmechanicalkeyboards.com

Make example for this keyboard (after setting up your build environment):

    make pmk/posey_split/v5:default

Flashing example for this keyboard:

    make pmk/posey_split/v5:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key Escape and plug in the keyboard
* **Physical reset button**: Hold the button on the bottom of the keyboard while you plug in the USB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
