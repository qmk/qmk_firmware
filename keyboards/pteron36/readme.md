# Pteron36

![Pteron36](https://i.imgur.com/PuXPWYfh.jpg)

A 36 key keyboard with a bit more natural thumb cluster.

* Keyboard Maintainer: [Harshit Goel](https://github.com/harshitgoel96)
* Hardware Supported: Pteron36 using promicro.
* Hardware Availability: Hardware is opensource, you can simply send the gerber to a PCB manufacturere and them made. File are availalbe in [pteron36 repository](https://github.com/harshitgoel96/pteron36-split-keyboard/releases/tag/v1.2.0)

Make example for this keyboard (after setting up your build environment):

    make pteron36:default

Flashing example for this keyboard:

    make pteron36:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Default Keymap and Miryoku Layout support

The keyboard was designed with miryoku layout in mind. The default layout is very basic and does not have much use. I will be opening a pr to make the keyboard available with miryoku layout soon. Currently to build the keyboard with miryoku you will have to checkout latest miryoku qmk repo, and add the keyboard folder there manually. After copying the folder run the following command

  make pteron36:manna-harbour_miryoku 
  
Add miryoku params as required.

## OLED and RotaryEncoder

I am working on adding OLED and RotaryEncoder support in keyboard config. 
