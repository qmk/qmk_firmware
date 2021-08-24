# 5x5

![5x5](https://3.bp.blogspot.com/-bKOfUyMtdrE/WqGA_03kGZI/AAAAAAACPtY/DsHDTQS0IlMD3ie8HHlf1ATRUAwpZdcSgCLcBGAs/s1600/c.jpg)  
===  

**Modular Keypad/Keyboard**  
The basic unit is a 5x5 matrix with 25 keys. Up to 3 of these can be connected to each other side by side.  
5x5, 5x10, and 5x15 matrices are possible.  
There are pads for header pins on each side that complete the circuits from board to board. These can be permanently connected with solder bridges or temporarily with pin headers and shunt jumpers.  
**_All configurations are powered by a SINGLE Arduino Micro or clone (NOT a Pro Micro)._**  

* [The original TMK firmware](https://github.com/di0ib/tmk_keyboard/tree/master/keyboard/5x5)

Keyboard Maintainer: QMK Community  
Hardware Supported: 5x5 PCB   
Hardware Availability: [5x5 project on 40% Keyboards](http://www.40percent.club/2018/04/5x5.html)  

Make example for this keyboard (after setting up your build environment):

    make 40percentclub/5x5:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

First pass at adding support for the 4x4 keyboard. Compiles but completely untested. Intended to kick-start development.  
