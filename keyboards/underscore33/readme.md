# underscore33 (stylized as "_33")

![_33](https://i.imgur.com/0Wuf8aT.png)

A little bitty 30% (10x4) ortholinear keyboard designed by tominabox1.  The R1 version of the board supports an RGB LED strip with DI on port B6. There is an error on the initial 25 PCBs that incorrectly indicates PF0 for the RGB. The R2 version is correctly labeled for RGB on D6. The appropriate port is commented out in config.h for proper LED support. 

* Keyboard Maintainer: [TJ Campie](https://github.com/tominabox1)
* Hardware Supported: [_33 r1 and r2 PCBs](https://github.com/tominabox1/_33-Keyboard)
* Hardware Availability: [3D printed open sourced](https://github.com/tominabox1/_33-Keyboard)

Make example for this keyboard (after setting up your build environment):

    make underscore33/rev2:default

Flashing example for this keyboard:

    make underscore33/rev2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
