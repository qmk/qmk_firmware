# bt66tech60 

A Blue Pill STM32F103C8T6-based 60% ANSI board.

Keyboard Maintainer: [Andrew Kannan](https://github.com/bt66)  
Hardware Supported: Blue Pill STM32F103C8T6  

Make example for this keyboard (after setting up your build environment):

    make bt66tech/bt66tech60:default
    
Flashing example for this keyboard:

    make bt66tech/bt66tech60:default:flash

    flashing command with dfu-util :
    dfu-util.exe -d 1eaf:0003 -a 2 -D "\path\to\firmware.bin", replacing \path\to\firmware.bin with your firmware directory
    example :
    dfu-util -d 1eaf:0003 -a 2 -D /root/qmk_firmware/bt66tech_bt66tech60_default.bin

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


