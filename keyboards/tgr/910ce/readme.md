# TGR 910 CE

A 65% Bootmapper Client based keyboard with blocker and 910 logo on the top right. 

* Keyboard Maintainer: [mechmerlin](https://github.com/mechmerlin)
* Hardware Supported: TGR 910 CE PCB labeled TGR-Unicorn PCB v1.2
* Hardware Availability: [Geekhack GB](https://geekhack.org/index.php?topic=91498.0)

Make example for this keyboard (after setting up your build environment):

    make tgr/910ce:default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make tgr/910ce:default:flash

**Reset Key**: Short the pins labeled `FW_JP` underneath the tab key. This can only be done from the back of the board. 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
