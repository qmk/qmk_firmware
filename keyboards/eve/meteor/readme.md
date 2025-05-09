# EVE Meteor

60% PCB with Function Row

* Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)
* Hardware Supported: EVE Meteor
* Hardware Availability: [zFrontier](https://en.zfrontier.com/products/eve-meteor)

Make example for this keyboard (after setting up your build environment):

    make eve/meteor:default

Flashing example for this keyboard:

    make eve/meteor:default:flash

**Reset Key:** Short the two holes labeled `FW_JP` underneath the PCB, beside the Tab key while plugging in the keyboard. 

Do not confuse this with the LED holes of the switch in the `Tab` position. `FW_JP` is not reachable from the top as the plate blocks access to it.

If your PCB does not have this circuit exposed, you must hold down the key corresponding to pins A0 and B0 on the MCU. On at least the red EVE PCB, this is the **+/= key** (second row, 13th column).

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
