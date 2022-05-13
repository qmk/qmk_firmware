# slash

![slash](https://i.imgur.com/MYEfSE0.jpg)

I found this project a while ago on [Reddit](https://www.reddit.com/r/MechanicalKeyboards/comments/6v3b6f/build_slash_keyboard_handwired_bluetooth/). This keyboard uses 61 keys in a 8x8 matrix. That bring the required pins to 16 which leaves 1 pin free. Unfortunately I couldn't get the firmware to compile on kbfirmware.com(the way [ND1BV](https://imgur.com/user/ND1BV) described it). So I decided to create the config myself and share it. I changed the wiring of the pins a little bit showed [here](https://i.imgur.com/WZ93xHx.png)

Keyboard Maintainer: [asdftemp](https://github.com/asdftemp)  
Hardware Supported: Adafruit Feather 32u4 Bluefruit LE  
Hardware Availability: [Adafruit shop](https://www.adafruit.com/product/2829)  

Make example for this keyboard (after setting up your build environment):

    make handwired/slash:default

Flashing should be done trough avrdude. Full make command is:

    make handwired/slash:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
