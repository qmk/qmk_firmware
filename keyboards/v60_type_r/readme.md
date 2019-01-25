KBParadise V60 Type R
======================

Released in 2017, the KBP V60 Type R is KB Paradise's first foray into the world of fully programmable keyboards. It utilizes an atmega32u4, Cherry MX switches, standard layout plate, Cherry style stabilizers, and plastic 60% case.

The keyboard comes in two flavors:
1. V60 Type R
2. V60 Type R Polestar

The Polestar comes with both in switch and underglow lighting, while the regular Type R has neither.

Please note that other variants of the KBP V60 are not fully programmable.

Backlight and RGB Underglow are both supported.

To use the backlight and/or RGB underglow:
* Create a new keymap
* Create a rules.mk file in the keymap
* Add RGBLIGHT_ENABLE = yes and/or BACKLIGHT_ENABLE = yes to the rules.mk
* Setup your keymap to your preference.  Use [the `vimouse` keymap](keymaps/vimouse/keymap.c) as a starting point
* Some extra keys are defined to allow you to set the red, green and blue values of the underglow directly, rather than using the HSV spectrum.  These are RGB_RI, RGB_RD, RGB_GI, RGB_GD, RGB_BI, RGB_BD for increase and decrease of the red, green and blue channels respectively.

The provided `default` keymap pretty closely matches the default V60 Type R keymap, minus the backlight and underglow control keys.  The `vimouse` keymap is completely customised and makes use of many of the possibilities, including mouse keys, backlighting, RGB underglow, etc.

Note for those customising: The configuration used in the `vimouse` keymap results in about 93% of the available flash being utilised.  Keep that in mind if you're adding functionality.

Note: By default the V60 Type R uses TMK.  You should know what you're doing and none of this is guaranteed to work.  If you want to stick with the TMK default, then the KB Paradise preferred way of creating the hex file is by using https://tkg.io/, selecting Fantastic60 and then defining your keymap.

You will then have to use tkg-toolkit to finish the flashing

Keyboard Maintainer:  QMK Community  
Hardware Supported:  KBP V60 Type R PCB  
Hardware Availability: [mechanicalkeyboards.com](https://mechanicalkeyboards.com/search.php?keyword=kbp+v60+type+r), [Massdrop](https://www.massdrop.com/buy/kbparadise-v60-type-r-mechanical-keyboard)

Make example for this keyboard (after setting up your build environment):

    make v60_type_r:default

or

    make v60_type_r:vimouse

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.



