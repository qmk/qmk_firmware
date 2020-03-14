# idb 60 PCB

Firmware for the idb 60 PCB

* Keyboard Maintainer: [/u/omgitspngu](https://github.com/itspngu)
* Hardware Supported: idb 60 PCB
* Hardware Availability: [/u/omgitspngu](https://www.reddit.com/user/omgitspngu/)

Make example for this keyboard (after setting up your build environment):

    make idb/idb_60:default

Or to make and flash:

    make idb/idb_60:default:flash
	
To compile VIA firmware:

    make idb/idb_60:via
	
LAYOUT_* Macros:

 * *LAYOUT_default*: ANSI WKL with full Backspace
 * *LAYOUT_all*: All split keys are available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
