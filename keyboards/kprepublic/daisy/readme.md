# Daisy

![Daisy](https://cdn.shopify.com/s/files/1/2711/4238/products/HTB1ahNecamgSKJjSsplq6yICpXaY_1024x1024.jpg?v=1515526190)

A 40% keyboard kit sold by KPRepublic.

Keyboard Maintainer: westfoxtrot (https://github.com/westfoxtrot)  
Hardware Supported: Daisy PCB Rev.1, Daisy PCB Rev.2  
Hardware Availability: https://kprepublic.com/collections/daisy-41/products/daisy-40-custom-keyboard-pcb

Make example for this keyboard (after setting up your build environment):

    make kprepublic/daisy:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.


# Other Keymaps

The "default" keymap included is the layout I personally use on the Daisy and the one I have found the most comfortable.

A printable picture showing this layout is available here: https://imgur.com/9mSF0yf


```
$ make kprepublic/daisy:[default|<name>]
```

# Bootloader

I personally had issues with the bootloader on my Daisy PCB and was unable to flash a firmware to the board after the first time. I replaced the bootloader with the one available in the repository at ../../util/bootloader_atmega32u4_1_0_0.hex
