# bandominedoni

![bandoMIneDonI](https://github.com/3araht/bandoMIneDonI/blob/main/pictures/bandoMIneDonI.jpg)

bandoMIneDonI keyboard is a MIDI split keyboard with bandoneon layout.
Close and Open of the bellow is emulated by either using a sustain pedal, or tapping a dedicated keys to alter the close and open status.

* Keyboard Maintainer: [3araht](https://github.com/3araht)
* Hardware Supported: bandoMIneDonI keyboard, a split keyboard mainly work as bandoneon MIDI keyboard.
* Hardware Availability: [BOOTH](https://3araht.booth.pm/).

Make example for this keyboard (after setting up your build environment):

    make bandominedoni:default

Flashing example for this keyboard:

    make bandominedoni:default:flash

Uncomment "PEDAL_NORMALLY_CLOSED" in bandominedoni.h when normally-on pedal is used for switching Open/Close state.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
