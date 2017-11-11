# Glossary of QMK terms

## ARM
A line of 32-bit MCU's produced by a number of companies, such as Atmel, Cypress, Kinetis, NXP, ST, and TI.

## AVR
A line of 8-bit MCU's produced by [Atmel](http://atmel.com). AVR was the original platform that TMK supported.

## AZERTY
The standard Français (French) keyboard layout. Named for the first 6 keys on the keyboard.

## Backlight
A generic term for lighting on a keyboard. The backlight is typically, but not always, an array of LED's that shine through keycaps and/or switches.

## Bluetooth
A short range peer to peer wireless protocol. Most common wireless protocol for a keyboard.

## Bootloader
A special program that is written to a protected area of your MCU that allows the MCU to upgrade its own firmware, typically over USB.

## Bootmagic
A feature that allows for various keyboard behavior changes to happen on the fly, such as swapping or disabling common keys.

## C
A low-level programming language suitable for system code. Most QMK code is written in C.

## Colemak
An alternative keyboard layout that is gaining in popularity.

## Compile
The process of turning human readable code into machine code your MCU can run.

## Dvorak
An alternative keyboard layout developed by Dr. August Dvorak in the 1930's. A shortened form of the Dvorak Simplified Keyboard.

## Dynamic Macro
A macro which has been recorded on the keyboard and which will be lost when the keyboard is unplugged or the computer rebooted.

* [Dynamic Macro Documentation](feature_dynamic_macros.md)

## Eclipse
An IDE that is popular with many C developers.

* [Eclipse Setup Instructions](eclipse.html)

## Firmware
The software that controls your MCU.

## FLIP
Software provided by Atmel for flashing AVR devices. We generally recommend [QMK Flasher](https://github.com/qmk/qmk_flasher) instead, but for some advanced use cases FLIP is required.

## git
Versioning software used at the commandline

## GitHub
The website that hosts most of the QMK project. It provides integration with git, issue tracking, and other features that help us run QMK.

## ISP
In-system programming, a method of programming an AVR chip using external hardware and the JTAG pins.

## hid_listen
An interface for receiving debugging messages from your keyboard. You can view these messages using [QMK Flasher](https://github.com/qmk/qmk_flasher) or [PJRC's hid_listen](https://www.pjrc.com/teensy/hid_listen.html)

## Keycode
A 2-byte number that represents a particular key. `0x00`-`0xFF` are used for [Basic Keycodes](keycodes_basic.html) while `0x100`-`0xFFFF` are used for [Quantum Keycodes](quantum_keycodes.html).

## Key Down
An event that happens when a key is pressed down, but is completed before a key is released.

## Key Up
An event that happens when a key is released.

## Keymap
An array of keycodes mapped to a physical keyboard layout, which are processed on key presses and releases

## Layer
An abstraction used to allow a key to serve multiple purposes. The highest active layer takes precedence.

## Leader Key
A feature that allows you to tap the leader key followed by a sequence of 1, 2, or 3 keys to activate key presses or other quantum features.

* [Leader Key Documentation](feature_leader_key.html)

## LED
Light Emitting Diode, the most common device used for indicators on a keyboard.

## Make
Software package that is used to compile all the source files. You run `make` with various options to compile your keyboard firmware.

## Matrix
A wiring pattern of columns and rows that enables the MCU to detect keypresses with a fewer number of pins. The matrix often incorporates diodes to allow for NKRO.

## Macro
A feature that lets you send muiltple keypress events (hid reports) after having pressed only a single key.

* [Macro Documentation](feature_macros.md)

## MCU
Microcontrol Unit, the processor that powers your keyboard.

## Modifier
A key that is held down while typing another key to modify the action of that key. Examples include Ctrl, Alt, and Shift.

## Mousekeys
A feature that lets you control your mouse cursor and click from your keyboard.

* [Mousekeys Documentation](feature_mouse_keys.html)

## N-Key Rollover (NKRO)
A term that applies to keyboards that are capable of reporting any number of key-presses at once.

## Oneshot Modifier
A modifier that acts as if it is held down until another key is released, so you can press the mod and then press the key, rather than holding the mod while pressing the key.

## ProMicro
A low cost AVR development board. Clones of this device are often found on ebay very inexpensively (under $5) but people often struggle with flashing their pro micros.

## Pull Request
A request to submit code to QMK. We encourage all users to submit Pull Requests for their personal keymaps.

## QWERTY
The standard English keyboard layout, and often a shortcut for other language's standard layouts. Named for the first 6 letters on the keyboard.

## QWERTZ
The standard Deutsche (German) keyboard layout. Named for the first 6 letters on the keyboard.

## Rollover
The term for pressing a key while a key is already held down. Variants include 2KRO, 6KRO, and NKRO.

## Scancode
A 1 byte number that is sent as part of a HID report over USB that represents a single key. These numbers are documented in the [HID Usage Tables](http://www.usb.org/developers/hidpage/Hut1_12v2.pdf) published by the [USB-IF](http://www.usb.org/).

## Space Cadet Shift
A special set of shift keys which allow you to type various types of braces by tapping the left or right shift one or more times.

* [Space Cadet Shift Documentation](feature_space_cadet.html)

## Tap
Pressing and releasing a key. In some situations you will need to distinguish between a key down and a key up event, and Tap always refers to both at once.

## Tap Dance
A feature that lets you assign muiltple keycodes to the same key based on how many times you press it.

* [Tap Dance Documentation](feature_tap_dance.md)

## Teensy
A low-cost AVR development board that is commonly used for hand-wired builds. A teensy is often chosen despite costing a few dollors more due to its halfkay bootloader, which makes flashing very simple.

## Underlight
A generic term for LEDs that light the underside of the board. These LED's typically shine away from the bottom of the PCB and towards the surface the keyboard rests on.

## Unicode
In the larger computer world Unicode is a set of encoding schemes for representing characters in any language. As it relates to QMK it means using various OS schemes to send unicode codepoints instead of scancodes.

* [Unicode Documentation](feature_unicode.md)

## Unit Testing
A framework for running automated tests against QMK. Unit testing helps us be confident that our changes do not break anything.

* [Unit Testing Documentation](unit_testing.md)

## USB
Universal Serial Bus, the most common wired interface for a keyboard.

## USB Host (or simply Host)
The USB Host is your computer, or whatever device your keyboard is plugged into.

# Couldn't find the term you're looking for?

[Open an issue](https://github.com/qmk/qmk_firmware/issues) with your question and the term in question could be added here. Better still, open a pull request with the definition. :)  
