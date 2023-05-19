# DT40

![DT40](https://github.com/NaturalZh/qmk_map/blob/main/dt40%20layout05192023.jpg)

The PCB features:
* QMK & VIA compatibility
* RGB Matrix backlight


** Keylout Special Usage Function Note(VIA keymap)

*** For combine with the left G6+ key :
**** ESC ---->  RGB matix ON/OFF;
**** Q   ---->  Static mode;
**** W   ---->  Full gradient scrolling left to right;
**** E   ---->  Breathing animation mode;
**** R   ---->  Full gradient spinning pinwheel around center of keyboard;
**** O   ---->  Key " = + " ;
**** I   ---->  Key " -_  " ;
**** K   ---->  Key " [{ " ;
**** L   ---->  Key " ]} " ;
**** up  ---->  Increase brightness;
**** DOWN --->  Decrease brightness;
**** LEFT --->  Cycle through modes in reverse;
**** RGHT --->  Cycle through modes

*** For combine with the right G6+ key :
**** CAPS --->  Key " Tab " ;
**** A   ---->  Key " `~ " ;
**** Q   ---->  Key " 1! " ;
**** W   ---->  Key " 2@ " ;
**** E   ---->  Key " 3# " ;
**** R   ---->  Key " 4$ " ;
**** T   ---->  Key " 5% " ;
**** Y   ---->  Key " 6^ " ;
**** U   ---->  Key " 7& " ;
**** I   ---->  Key " 8* " ;
**** O   ---->  Key " 9( " ;
**** P   ---->  Key " 0) " ;
**** J   ---->  Key " ;: " ;
**** K   ---->  Key " '" " ;
**** N   ---->  Key " ,< " ;
**** M   ---->  Key " .> " ;

*** For combine with the Fn key :
**** Q   ---->  Key " F1 " ;
**** W   ---->  Key " F2 " ;
**** E   ---->  Key " F3 " ;
**** R   ---->  Key " F4 " ;
**** T   ---->  Key " F5 " ;
**** Y   ---->  Key " F6 " ;
**** U   ---->  Key " F7 " ;
**** I   ---->  Key " F8 " ;
**** O   ---->  Key " F9 " ;
**** P   ---->  Key " F10 " ;
**** K   ---->  Key " F11 " ;
**** L   ---->  Key " F12 " ;




The following is the QMK Firmware for the Destop 40% keylayout -  designed in Dongguan Jizhi Electronic Technology Co., Ltd
* Keyboard Maintainer: [JZ-Skyloong](https://github.com/JZ-Skyloong)
* Hardware Supported: DestopPCB for Skyloong keylayout 40%, STM32F103C8T6
* Hardware Availability: http://www.skyloong.com.cn

Make example for this keyboard (after setting up your build environment):

    make skyloong/dt40:default
    make skyloong/dt40:via

Flashing example for this keyboard:

    make skyloong/dt40:default:flash
    make skyloong/dt40:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
