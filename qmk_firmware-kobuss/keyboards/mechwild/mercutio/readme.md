# Mercutio

![Mercutio](https://i.imgur.com/23J9GqXl.jpg)

A through-hole 40% keyboard kit featuring an encoder and oled display.

* Keyboard Maintainer: [Kyle McCreery](https://github.com/kylemccreery)
* Hardware Supported: Mercutio v1.0
* Hardware Availability: [Mercutio on MechWild](https://mechwild.com/product/mercutio/)

Make example for this keyboard (after setting up your build environment):

    make mechwild/mercutio:default
    
## Bootloader
Uses usbasploader, which has been preflashed on the atmega328p before being shipped to you. The usbasploader build available on [hsgw's repository](https://github.com/hsgw/USBaspLoader/tree/plaid) will work if you need to flash a new and unprepared replacement microcontroller. To flash this onto your fresh atmega328p, you will need to use the provided ISP headers and an external ISP programmer.

In order to put the board into bootloader mode you must first hold the boot button (labeled BOOT) and while holding the boot button, press the reset button (labeled RESET) and release it. Wait for another second, then release the boot button as well. The microcontroller will now be in bootloader mode if the bootloader is present and prepared correctly. Continue to flash as you normally would from this point (ie. QMK Toolbox). If you have autoflash enabled on QMK Toolbox, it will do it automatically now. Reset the board once more in order to use the new firmware (you can do this by unplugging and replugging it or by pressing and releasing the reset button.)

By default, Mercutio firmware has bootmagic enabled (lite). This means that instead of holding or pressing either of the small buttons, you are able to unplug the Mercutio, hold the top left button (tab), plug the Mercutio back in, and then release the top left button (tab). This will work the same to put the Mercutio into bootloader mode. For more information, see the [bootmagic feature page](https://beta.docs.qmk.fm/using-qmk/hardware-features/feature_bootmagic). Reset the board once more in order to use the new firmware (you can do this by unplugging and replugging it or by pressing and releasing the reset button.)



See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
