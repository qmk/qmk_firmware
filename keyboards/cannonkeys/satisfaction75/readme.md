# Satisfaction75

Satisfaction75 Keyboard

* Keyboard Maintainer: [Andrew Kannan](https://github.com/awkannan)
* Hardware Supported: STM32F072CBT6

## Revisions

Please be advised that there are many revisions of Satisfaction75 PCBs.

- Prototype revisions do not really exist in the wild, unless you are one of very few people who have an early pre-production Satisfaction75
- Rev1 was the PCB sold with Round 1 and Round 2 of the Satisfaction75 keyboard group buy, as well as any extra PCBs sold before 2023.
- Rev2 is the PCB sold with the late 2023/early 2024 Injection molded Satisfaction75, and any extra PCBs sold after that. These PCBs also have extra edge cuts to support the injection molded Satisfaction75. It was redesigned from scratch and has a little less layout support compared to Rev1.

Revision 2 PCBs will have Revision 2 printed on the PCBs.

Revisions _are_ backwards compatible, so you can use a Rev2 PCB in a board that originally had a Rev1 PCB in it. They are _not_ forwards compatible - Rev 1 PCBs will not work in the injection molded Satisfaction75.

Change the below commands to reflect the revision you need!

## Building and Flashing

Make example for this keyboard (after setting up your build environment):

    make cannonkeys/satisfaction75/rev1:default
    
Flashing example for this keyboard:

    make cannonkeys/satisfaction75/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Toggle the switch on the back of the pcb to "1" and briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available