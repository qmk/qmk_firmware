# Georgi

![Georgi](https://i.imgur.com/3kUpRrj.jpg)

A compact 20% (12x2) Split Keyboard for steno and QWERTY. 

[More info on qmk.fm](http://qmk.fm/georgi/)

Keyboard Maintainer: [Jeremy Bernhardt](https://github.com/germ)  
Hardware Supported: Georgi   
Hardware Availability: [gboards.ca](http://gboards.ca)  

## Firmware building
After cloning the QMK repo and installing dfu-programmer build and flash with. Be sure to reset your keyboard!

    make georgi:default:dfu

To just test your build with the default keymap
   
    make georgi:default

Build options can be enabled/disabled in keyboards/georgi/keymaps/default/rules.mk . Copy the default directory and make any changes to your layout, if you think they're worth sharing submit a PR!

# Space
The stock firmware uses nearly all of the flash avalible. For custom dictionary modifications, disable mousekeys in your keymaps rules.mk (4K of space) and remove the Gaming layers. I've done this already in the provided keymap 'template'.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Have an idea?  [Reach out to me!](mailto:bernhardtjeremy@gmail.com)
