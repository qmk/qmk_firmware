# Practice 60

A Blue Pill STM32F103C8T6-based 60% ANSI board.

Keyboard Maintainer: [Andrew Kannan](https://github.com/awkannan1)  
Hardware Supported: Blue Pill STM32F103C8T6  

Make example for this keyboard (after setting up your build environment):

    make cannonkeys/practice60:default

Flashing example for this keyboard:

    make cannonkeys/practice60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Build guide available at: https://docs.cannonkeys.com/bluepill-build/
Blue Pill flashing guide at: https://docs.cannonkeys.com/flashing/
Flash using dfu-util:

    dfu-util.exe -d 1eaf:0003 -a 2 -D "\path\to\firmware.bin"

Note: If using MSYS2 and getting gcc-arm-none-eabi errors try running the command below and restarting MSYS2.

    echo "source ~/qmk_utils/activate_msys2.sh" >> ~/.bashrc
