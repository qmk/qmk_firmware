KBParadise V60 Type R
======================

Released in 2017, the KBP V60 Type R is KB Paradise's first foray into the world of fully programmable keyboards. It utilizes an atmega32u4, Cherry MX switches, standard layout plate, Cherry style stabilizers, and plastic 60% case.

The keyboard comes in two flavors:
1. V60 Type R
2. V60 Type R Polestar

The Polestar comes with both in switch and underglow lighting, while the regular Type R has neither.

Please note that other variants of the KBP V60 are not fully programmable.

Backlight and RGB Underglow are both supported.

Note: By default the V60 Type R uses TMK.  You should know what you're doing and none of this is guaranteed to work.  If you want to stick with the TMK default, then the KB Paradise preferred way of creating the hex file is by using https://tkg.io/, selecting Fantastic60 and then defining your keymap.

You will then have to use tkg-toolkit to finish the flashing

Keyboard Maintainer:  QMK Community  
Hardware Supported:  KBP V60 Type R PCB  
Hardware Availability: [mechanicalkeyboards.com](https://mechanicalkeyboards.com/search.php?keyword=kbp+v60+type+r), [Massdrop](https://www.massdrop.com/buy/kbparadise-v60-type-r-mechanical-keyboard)

Make example for this keyboard (after setting up your build environment):

    make v60_type_r:default

or

    make v60_type_r:vimouse

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
