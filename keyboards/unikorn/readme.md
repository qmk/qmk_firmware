# Unikorn 60

60% PCB made for the TGR x SINGA Unikorn60. 

* Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)
* Hardware Supported: Unikorn 60 PCB
* Hardware Availability: [Geekhack GB](https://geekhack.org/index.php?topic=98350.0)

Make example for this keyboard (after setting up your build environment):

    make unikorn:default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make unikorn:default:flash

**Reset Key**: Short the two holes labeled `FW_JP` underneath the PCB, beside the Tab key while plugging in the keyboard. 

Do not confuse this with the LED holes of the switch in the `Tab` position. `FW_JP` is not reachable from the top as the plate blocks access to it. 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## RGB Underglow
This PCB can support RGB underglow. There are pads on the bottom of the PCB for the LED controller chip and for 17 RGB underglow LEDs. The Unikorn 60 case does not have acrylic pieces to properly display underglow effects. 

To enable RGB lighting support, install the necessary components and set RGBLIGHT features in `rules.mk` like so:

```makefile
RGBLIGHT_ENABLE = yes
```
