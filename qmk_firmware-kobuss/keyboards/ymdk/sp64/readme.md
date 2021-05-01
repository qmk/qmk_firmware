# YMDK SP64

* Keyboard Maintainer: [Nathan Walston](https://github.com/walston)
* Hardware Supported: YMDK SP64 with the ATmega32a chip.
* Hardware Availability: [Aliexpress](https://www.aliexpress.com/item/4000074426801.html?spm=a2g0o.productlist.0.0.13a043a4NuWRUc&algo_pvid=d2e1c7f2-710a-47be-98be-c2ee4c35e205&algo_expid=d2e1c7f2-710a-47be-98be-c2ee4c35e205-1&btsid=7eeb6dd6-e91f-4ecc-b94c-0ce4b1d089e0&ws_ab_test=searchweb0_0,searchweb201602_9,searchweb201603_53)

Make example for this keyboard (after setting up your build environment):

    make ymdk/sp64:default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make ymdk/sp64:default:flash

**Reset Key**: Hold down the key located at top left on the left hand board, commonly programmed as _ESC_ while plugging in the keyboard.  (NOTE:  If this doesn't work, try the lower left key on the lower left board, commonly programmed as _Control_.  There might be a different version of the board that uses that key as the reset.)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
