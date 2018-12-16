B.fake
========

A 60% keyboard with RGB. The B.fake pcb is a copy of the B.face PCB sold by [winkeyless](https://winkeyless.kr/). However, the switch matrix is actually the same as the [FaceW](https://github.com/qmk/qmk_firmware/tree/master/keyboards/facew), a ps2avr PCB sold on [mechanicalkeyboards.com](https://mechanicalkeyboards.com/). 

Keyboard Maintainer: QMK Community  
Hardware Supported: B.fake PCB  
Hardware Availability: https://www.aliexpress.com/store/product/bface-60-RGB-underground-copy-pcb-from-china-gh60-pcb-Customize-keyboard-PCB/2230037_32731084597.html

Make example for this keyboard (after setting up your build environment):

    make bfake:default

Flashing

ps2avr(GB) boards use an atmega32a microcontroller and a different bootloader. It is not flashable using the regular QMK methods. 

Windows: 
1. Download [HIDBootFlash](http://vusb.wikidot.com/project:hidbootflash).
2. Place your keyboard into reset. 
3. Press the `Find Device` button and ensure that your keyboard is found.
4. Press the `Open .hex File` button and locate the `.hex` file you created.
5. Press the `Flash Device` button and wait for the process to complete. 

macOS:
1. Install homebrew by typing the following:   
    ```
    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    ```
2. Install `crosspack-avr`.  
    ```
    brew cask install crosspack-avr
    ```
3. Install the following packages:
    ```
    brew install python
    brew install pyusb
    brew install --HEAD`https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb

4. Place your keyboard into reset. 
5. Flash the board by typing `bootloadHID -r` followed by the path to your `.hex` file. 


See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.
