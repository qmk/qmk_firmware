# KB16-01

#### This keyboard have 2 revision, so before you need to write your own firmware code. Please read it carefully, or you could accident bricked your keeb after that.

- **Revision 1**: Using ATMEGA32U4.

When you try to go bootloader mode, QMK Toolbox will showing this message `Atmel DFU device connected (libusb0): Atmel Corp. ATmega32U4 (03EB:2FF4:0000)`. So please compile Revision 1 and flash after that.

Oh, and one more thing. As for the Bongo Cat on OLED screen, due to small flash size that ATMEGA32U4 support. It need to be disable Mouse key support.

- **Revision 2**: Using APM32F103CBT6 (clone STM32F103CBT6).

When you try to go bootloader mode, QMK Toolbox will showing this message `STM32Duino device connected: LeafLabs Maple 003 (1EAF:0003:0201)`. So please compile Revision 2 and flash after that.
