# Aplx6

![Front](https://i.imgur.com/lUg9GAo.png)  
![Back](https://i.imgur.com/iAHtHV7.png)
   
A stylish (2x3) 6-key MediaPad for your music and browser shortcuts. Designed to be assembled as a sandwich with a blank PCB, using M2.5 screws and spacers, your choice of MX- or Alps-compatible switches, and 1N4148 diodes.


## RGB Underglow (WS2812)

Just wire them to any of the unused ProMicro pins.
Don't forget to edit-uncomment the [config.h](https://github.com/Aplyard/Aplx6/blob/master/qmk/config.h) and the [rules.mk](https://github.com/Aplyard/Aplx6/blob/master/qmk/rules.mk)
for RGB underglow support or even add your own functions and modes.
Used pins can be found in [config.h](https://github.com/Aplyard/Aplx6/blob/master/qmk/config.h) or in the [KiCad Schematic](https://github.com/Aplyard/Aplx6/blob/master/kiCad/xd6.sch)
All ProMicro pins can be found [here](https://golem.hu/article/pro-micro-pinout/) along with the +2 pins mod.

---

**Default Keymap Layout is [Media](https://github.com/Aplyard/Aplx6/blob/master/qmk/keymaps/Media/keymap.c)** (no RGB shortcuts)



|Default|Layer|(0)|
|--|--|--|
| Play|VolUp|Fn|
|Prev|VolDown|Next|

=========================
| Fn |Layer|(1)
|--|--|--|
|Calc|PgUp|KC_TRANS|
|MyPc|PgDown|RESET

---

Make example for this keyboard (after setting up your build environment):

     make aplx6:Media

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

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
Keyboard Maintainer: Aplyard  
Hardware Supported: Pro Micro ATmega32U4  
Hardware Availability: Aplyard
