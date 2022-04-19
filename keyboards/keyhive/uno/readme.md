# Uno

![Uno](https://i.imgur.com/OqPyWbbl.jpg)

A 1-key, in-USB "board" for the lulz

* Keyboard Maintainer: [Snipeye](https://github.com/Snipeye)
* Hardware Availability: [keyhive.xyz](https://keyhive.xyz/shop/uno-single-key-keyboard)

There are two revisions of Uno. If your Uno supports a rotary encoder, use rev2.
If it *does not* support a rotary encoder, use rev1. The following examples use
`rev2` &mdash; be sure to change this if you are using `rev1`.

Make example for this keyboard (after setting up your build environment; make
sure to change `rev2` to your Uno's version):

    make keyhive/uno/rev2:default

Flashing example for this keyboard (change `rev2` to `rev1` if needed):

    make keyhive/uno/rev2:default:flash

If you prefer to use the `qmk` tool:

    qmk compile -kb keyhive/uno/rev2 -km default

Create your own keymap with:

    qmk new-keymap -kb keyhive/uno/rev2

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Credits
+ Everything by Snipeye
