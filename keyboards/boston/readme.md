# Boston

![3D-printed/FR4 version](https://github.com/bluepylons/Boston/raw/master/graphics/3D-printed-prototype.JPG)

A compact 120% keyboard. 

This keyboard is currently in IC - [Geekhack IC thread is here](https://geekhack.org/index.php?topic=106501.0). Group buy details will be posted once it is ready.

* Keyboard Maintainer: [Bluepylons](https://github.com/bluepylons)
* Hardware Supported: Boston PCB (STM32F072)
* Hardware Availability: PCB and 3D-printing files are available on [Github](https://github.com/bluepylons/Boston).

Make example for this keyboard (after setting up your build environment):

    make boston:default
	
Flashing example for this keyboard:

    make boston:default:flash
	
To reset the board, use a pin to press the reset button on the underside of the keyboard, above the numlock key. 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
