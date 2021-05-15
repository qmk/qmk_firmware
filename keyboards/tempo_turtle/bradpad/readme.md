# bradpad

![bradpad]()

The QMK firmware for the bradpad a music production inspired macropad.

Keyboard Maintainer: [wxyangf](https://github.com/wxyangf)  
Hardware Supported: bradpad pcbs  
Hardware Availability: [1UP Keyboards](https://1upkeyboards.com/)

[Album of Prototype of Integrated MCU Version(v1.5.x)]()
[Album of Elite-C Version (v1)](https://imgur.com/a/xjocnNo)


How to reset production version into bootloader mode:

  1. Locate the reset button on the underside of the pcb.
  2. Press the reset button for a few seconds using a paperclip or other similar object.
  3. Release the reset button.
  4. Your bradpad should now be in bootloader mode.

Make example for this keyboard (after setting up your build environment):

    make tempo_turtle/bradpad:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.