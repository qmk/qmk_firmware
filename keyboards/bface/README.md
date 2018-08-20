# B.face

A 60% keyboard with RGB that runs ps2avrgb natively. Please note that the B.face and B.fake have different switch matrices. Firmware on one, will not work on the other. 

Keyboard Maintainer: QMK Community  
Hardware Supported: B.face PCB   
Hardware Availability: [Winkeyless](https://winkeyless.kr/product/b-face-x2-pcb/)   

Make example for this keyboard (after setting up your build environment):

    make bface:default

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
    ```

4. Place your keyboard into reset. 
5. Flash the board by typing `bootloadHID -r` followed by the path to your `.hex` file. 


See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.
