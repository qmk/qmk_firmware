# The etch-a-sketch keymap for Ergomax

The ProMicro used on Ergomax rev1 has 2 pins free that can be used for anything. In this keymap, we wire them to a rotary encoder, one on each side. The rest of the keymap is based on the default keymap.

The 2 encoders are mapped to mouse directions, making it work just like an etch-a-sketch.

**This is currently buggy**. The rotary encoder on the slave side is not refreshing properly. I opened [a ticket](https://github.com/qmk/qmk_firmware/issues/6813) in QMK repo but didn't get any helpful answers. I don't know how to debug this, sadly.

## Layout

Based off the default layout:

![ergomax-default -layout](https://user-images.githubusercontent.com/2750789/68823557-fd947b80-0648-11ea-90b9-089e7ddc1ec6.PNG)