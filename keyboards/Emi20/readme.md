# Emi20

![Emi20](https://i.imgur.com/Tt9ogmW.jpg)

A compact 20% (4x5) ortholinear keyboard made by Project Aqua and sold by .

* Keyboard Maintainer: [AquaCylinder](https://github.com/AquaCylinder)
* Hardware Supported: PCB, Atmega32u4

Make example for this keyboard (after setting up your build environment):

    make Emi20:default


For reset instruction, use the physical reset button on the back of the keyboard to enter bootloader mode or use the keycombo (on layer 1) with te most bottom left and the key second key from the top right diagonally. KC_MPLY and KC_NLCK. See: 

    KC_TRNS, 	KC_VOLD, 	KC_VOLU, 	KC_CALC, 
	KC_MPRV, 	KC_MSTP, 	KC_MPLY, 	KC_MNXT, 
	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 
	KC_NO, 		KC_NO, 		KC_UP, 		KC_NO,
	KC_NLCK, 	KC_LEFT, 	KC_DOWN, 	KC_RGHT),

The default keymap.c file has comments to help you on your journey,
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).