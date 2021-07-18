# ogurec

![ogurec](https://imgur.com/gallery/OFF1Vyp)

ogurec is a reversible 12u x 3u ortholinear keyboard that offers left-sided and right-sided PM placement

* Keyboard Maintainer: [H. Bond](https://github.com/drhigsby)
* Hardware Supported: ogurec (https://github.com/drhigsby/ogurec)
* Hardware Availability: open source 3DP case available here https://github.com/drhigsby (case creator: https://github.com/dpalka15)

Make example for this keyboard (after setting up your build environment):

    make ogurec:default_right
    make ogurec:default_left

To place the keyboard into bootloader mode, solder a reset switch onto the PCB and press it OR short the GND and RST pins on the pro micro. 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
