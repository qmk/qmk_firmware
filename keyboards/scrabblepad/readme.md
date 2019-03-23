# ScrabblePad

The ScrabblePad is a 15x15 ortholinear keyboard designed for use with
the XDA Scrabble Board sold by [Novelkeys](https://novelkeys.xyz).

It uses a [Teensy++ 2.0](https://www.pjrc.com/store/teensypp.html) 
featuring an at90usb1286 8 bit microcontroller. Usage requires modifying the Teensy by removing the LED on pin D6.

Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin), [Donut Cables](https://donutcables.com/)  
Hardware Supported: Teensy++ 2.0 and ScrabblePad PCB  
Hardware Availability: [Donut Cables](https://donutcables.com/)

Make example for this keyboard (after setting up your build environment):

    make scrabblepad:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
