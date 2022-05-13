# LFK78/68

A 65% keyboard similar to the MagicForce68 or VA68M. Optional function key block on left side.

* Keyboard Maintainer: [LFKeyboards](https://github.com/lfkeyboards)
* Hardware Supported: LFK78/68 RevB - RevJ, SMK78/68
* Hardware Availability: [LFKeyboards.com](https://www.lfkeyboards.com/)

## Revisions

* `revb`: First public release, uses ATmega32U4, has audio, ISSI matrix split between RGB and backlight
* `revc`: Revisions C through H, uses AT90USB1286, no audio, ISSI device 0 is backlight, 4 is RGB
* `revj`: Audio on pin C6, uses AT90USB646

---

Make example for this keyboard (after setting up your build environment):

    make lfkeyboards/lfk78:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
