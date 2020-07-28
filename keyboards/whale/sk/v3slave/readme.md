# Splite Keyboard v3 slave

![Split Keyboard Default Layout](https://github.com/ncwhale/Keyboard_Design/raw/master/Splite-Keyboard-v3/Keyboar-layout.png)

This is the slave(default: right side) keyboard firmware of Splite Keyboard.


    !IMPORTANT!
    
    This firmware can flash on both side of keyboard parts!
    BUT it will be detected as a SERIAL PORT by host instead of a KEYBOARD!
    NEVER flash it to the master side you choice!
    OR you may lost ALL your EEPROM settings!
    
* Keyboard Maintainer: [Whale Mo](https://github.com/ncwhale)
* Hardware Supported:  [Opensource Design](https://github.com/ncwhale/Keyboard_Design), Sparkfun Micro Pro
* Hardware Availability: On the way.

Make example for this keyboard (after setting up your build environment):

    make whale/sk/v3slave:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
