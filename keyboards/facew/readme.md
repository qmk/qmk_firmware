# FaceW

A 60% no frills keyboard.

The FaceW is a special run of the WKL B.Face sourced from Sprit that doesn't have underglow RGB LEDs but does have in switch LEDs. Also unlike the B.Face, it is based on ps2avru instead of ps2avrGB. It is designed and manufactured in Korea. 

Keyboard Maintainer: [MechMerlin](www.github.com/mechmerlin)  
Hardware Supported: FaceW Sprit Edition PCB  
Hardware Availability: https://mechanicalkeyboards.com/shop/index.php?l=product_detail&p=1352

Make example for this keyboard (after setting up your build environment):

    make facew:default

Flashing

ps2avr(GB) boards use an atmega32a microcontroller and a different bootloader. It is not flashable using the regular QMK methods. 

**Reset Key:** To put the FaceW into reset, hold `q` (`K01`) while plugging in.

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
    brew install python3
    pip3 install pyusb
    brew install --HEAD https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb

4. Place your keyboard into reset. 
5. Flash the board by typing `bootloadHID -r` followed by the path to your `.hex` file. 


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
