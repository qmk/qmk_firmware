# Aplx6

![Front](https://i.imgur.com/flhSvAG.png)  
![Back](https://i.imgur.com/PXqNmUh.png)
   
A stylish (2x3) 6-key MediaPad for your music and browser shortcuts. Designed to be assembled as a sandwich with a blank PCB, using M2.5 screws and spacers, your choice of MX- or Alps-compatible switches, and 1N4148 diodes.


## RGB Underglow (WS2812)

Just wire them to any of the unused ProMicro pins. Don't forget to edit-uncomment the `config.h` and the `rules.mk` for RGB underglow support, or even add your own functions and modes. Used pins can be found in `config.h` or in the [KiCad Schematic](https://github.com/Aplyard/Aplx6/blob/master/kiCad/xd6.sch). All ProMicro pins can be found [here](https://golem.hu/article/pro-micro-pinout/) along with the +2 pins mod.

* Keyboard Maintainer: Aplyard
* Hardware Supported: Aplx6 PCB, Pro Micro (ATmega32U4)
* Hardware Availability: Aplyard

Make example for this keyboard (after setting up your build environment):

     make aplx6:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

---  
****Designed in**:**  
[KiCad](https://github.com/KiCad)  

**Components Footprints & Libraries :**  
[keebs.pretty](https://github.com/egladman/keebs.pretty)  
[keyboard_parts.pretty
](https://github.com/tmk/keyboard_parts.pretty)  
[ProMicro KiCad](https://github.com/Biacco42/ProMicroKiCad)  

**Usefull Links:**  
[Qmk Online Configurator](https://config.qmk.fm/#)  

**Alternatives of qmk that worked for me:**  
[Keyboard Layout Editor](http://www.keyboard-layout-editor.com/#/)   
[Keyboard Plate & Case Builder](http://builder.swillkb.com/)  
[Firmware Builder](https://kbfirmware.com/)      

---   