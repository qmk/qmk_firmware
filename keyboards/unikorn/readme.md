# Unikorn 60

60% PCB made for the TGR x SINGA Unikorn60. 


Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)  
Hardware Supported: Unikorn 60 PCB  
Hardware Availability: [Geekhack GB](https://geekhack.org/index.php?topic=98350.0)


Make example for this keyboard (after setting up your build environment):

    make unikorn:default

This PCB can support RGB underglow. There are pads on the bottom of the PCB for the LED controller chip and for 17 RGB underglow LEDs. The Unikorn 60 case does not have acrylic pieces to properly display underglow effects. 

To enable RGB lighting support, install the necessary components and set RGBLIGHT features in `rules.mk` like so:

```
RGBLIGHT_ENABLE = yes
```


Flashing

ps2avr(GB) boards use an atmega32a microcontroller and a different bootloader. It is not flashable using the regular QMK methods. 

**Reset Key:** Short the two holes labeled `FW_JP` underneath the PCB, beside the Tab key while plugging in the keyboard. 

Do not confuse this with the LED holes of the switch in the `Tab` position. `FW_JP` is not reachable from the top as the plate blocks access to it. 

It is recommended to program a `RESET` key in your keymap.   

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
