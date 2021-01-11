# The YMDK "Bface" PCB

![ymdk_bface](https://i.imgur.com/qhFxN0g.jpg)

A 60% keyboard that runs ps2avrgb natively and fits the popular GH60 form factor. Another "bfake" or clone of the original B.face PCB by [Winkeyless](https://winkeyless.kr/product/b-face-x2-pcb/). This PCB has slightly different switch matrix than the origninal B.face, and is also different than the bfake. It commonly comes as the PCB in 60% keyboard kits sold by YMDK on Aliexpress.

Keyboard Maintainer: QMK Community  
Hardware Supported: White Bface Mini USB PCB with no RGB.  
Hardware Availability: [Shenzhen YMD Tech Co. (YMDK) on Aliexpress](https://www.aliexpress.com/item/32799437588.html)  

Make example for this keyboard (after setting up your build environment):

    make ymdk/bface:default

Flashing:

ps2avr(GB) boards use an atmega32a microcontroller and a different bootloader. It is not flashable using the regular QMK methods. 

This board has a pair of jumper holes on the left edge of the PCB marked "Jb", near TAB and CAPS LOCK. If you short the contacts with tweezers or wire the board will enter into the bootloader and you can flash it.

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
    pip3 install pyusb
    brew install --HEAD`https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb
    ```

4. Place your keyboard into reset by shorting the jumper on the left edge of the PCB.. 
5. Flash the board by typing `bootloadHID -r` followed by the path to your `.hex` file. 

Another method for Mac or Linux:
After installing `bootloadHID`, you can use the `./util/atmega32a_program.py` program included in QMK. You will need to have `python` and the `pyusb` library installed.

Then you can run this to compile the firmware and flash the board without using the jumper:
```
make ymdk/bface:default:program
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
