# 108 Key with TrackPoint

![wiring](https://raw.githubusercontent.com/qmk/qmk.fm/gh-pages/keyboards/handwired/108key_trackpoint/wiring.JPG)

This is based off the handwired/trackpoint keyboard and generated code from [Keyboard Firmware Builder](https://kbfirmware.com/).

Keyboard Maintainer: [mkem114](https://github.com/mkem114)  
Hardware Supported (tested): Teensy++ 2.0

Make example for this keyboard (after setting up your build environment):

    make handwired/108keyTrackpoint:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

You may have to modify the source code to suit 104 keys, RGB back-lights, different micro-controllers, or big ass enter.

There are three keymaps:
* qwerty with the four extra keys being: mute, media prev, media next, and media play
* dvorak with the four extra keys being: mute, media prev, media next, and media play
* dvorak_media with the caps lock being media play and the four extra keys being: mute, volume down, volume up, and media next

To figure out how to wire your specific TrackPoint have a look out: [How to integrate a trackpoint in a mechanical keyboard](https://github.com/alonswartz/trackpoint).
