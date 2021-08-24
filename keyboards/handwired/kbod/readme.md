# KBOD

![KBOD](https://f4.fudanchii.net/shx/2017/02/IMG_20170212_224547.jpg)

KBOD is a 60% Keyboard kit, hand-wired, with Arduino Micro as its controller. It utilizes an 8x8 matrix and has layout similar to GH60. [More info](https://github.com/fudanchii/keyboard_of_disapproval)

Keyboard Maintainer: [The QMK Community](https://github.com/qmk)  
Hardware Supported: Arduino Micro  

Make example for this keyboard (after setting up your build environment):

    make handwired/kbod:default

Flashing your firmware may be done with avrdude. The command should be something along this line:

    avrdude -p m32u4 -c avr109 -P <COM PORT> -C <avrdude conf file> -e -u flash:w:handwired_kbod_default.hex

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
