# Le Chiffre

![Le Chiffre](https://i.imgur.com/X1WsUmdl.png)

Le Chiffre (ironically, "the number" in French) is a 30% keyboard designed by tominabox1.  The purpose of the board is to provide a platform for MX and Choc ergo in one package for when ones wrists need a break. The board supports an RGB LED strip with DI on port F0. The board is also fitted with support for run-of-the-mill .91" OLED and EC11 rotary encoder.  

There are 3 PCB revisions: Rev 1 (Original), Rev 2 (P3D version sold with the Le Chiffre Plus), and HE (Hotswap Edition from Checkerboards.xyz).

By default the OLED is **disabled**. This is to prevent issues with operation when one is not installed. Be sure to enable the OLED in the rules.mk file if you have one installed!
 
* Keyboard Maintainer: [TJ Campie](https://github.com/tominabox1)
* Hardware Supported: [Le Chiffre](https://github.com/tominabox1/Le-Chiffre-Keyboard)
* Hardware Availability: Bring your own case.

Make example for this keyboard (after setting up your build environment):

    make tominabox1/le_chiffre/rev1:default
    make tominabox1/le_chiffre/rev2:default
    make tominabox1/le_chiffre/he:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
