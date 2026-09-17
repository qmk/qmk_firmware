# recorev3

![recorev3](https://i.imgur.com/28fVsP3.jpeg)

The Posey Recore keyboard is an ortholinear keyboard designed from the gournd up for gaming. By pushing the left half of your split keyboard out of the way, you'll be able to game with better posture and increase mouse movement. The thumb cluster arc can be remapped to control and shift for use in gaming.

* Keyboard Maintainer: [Javier Oliver](https://github.com/joliverMI)
* Hardware Supported: recore_v3 and logic_module_v1
* Hardware Availability: [poseysmechanicalkeyboards.com](https://poseysmechanicalkeyboards.com/)

Make example for this keyboard (after setting up your build environment):

    make pmk/recore/v3:default
    
Flashing example for this keyboard:

    make pmk/recore/v3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key Escape and plug in the keyboard
* **Physical reset button**: Hold the button on the bottom of the keyboard while you plug in the USB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
