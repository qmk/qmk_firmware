PS/2 to USB keyboard converter
==============================
This is a port of TMK's converter/ps2_usb to QMK.

This firmware converts PS/2 keyboard protocol to USB. (It supports Scan Code Set 2.)

Hardware
--------
- [Hasu PS/2-USB converter](https://geekhack.org/index.php?topic=14618.0)
- Pro Micro 5V 16MHz
- Teensy 2.0

Wiring
-------------
I have only tested *Interrupt* mode so far.
1. Connect **VCC** and *GND*.
2. Connect **Clock** and **Data** line.
    - *Interrupt*:   **Clock** is on `PD1` (pin 2 on Pro Micro) and **Data** on `PD0` (pin 3 on Pro Micro). (Recommended. Soarer's converter compatible)
3. You need two pull-up resistors for **Clock** and **Data** lines. 1K-10K Ohm would be fine.

Build Firmware
--------------
Make example for this converter (after setting up your build environment):

    make converter/ps2_usb:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Keymaps
-------
All available scancodes are organized in 8x32 matrix, so you can treat them like physical key matrix. Physical layouts are defined in `ps2_usb.h`:

- `LAYOUT_ALL`: sample layout with most scancodes including F13-F24, JIS and media keys.
- `LAYOUT_104_ansi`: ANSI 104 keys layout
- `LAYOUT_105_iso`: ISO 105 keys layout
- `LAYOUT_ibm_f_at`: IBM Model F AT keyboard (including hidden pads for ANSI mod)

Logical layouts (keymaps) are stored in *keymaps* directory.

PS/2 signal handling implementations
------------------------------------
Following three methods can be used to implement PS/2 signal handling.

### Simple and stupid busy-wait(ps2_busywait.c)
    This is expected to implemented with portable C code for reference.
### Interrupt driven(ps2_interrupt.c)
    Uses pin interrupt to detect falling edge of clock line.
### USART hardware module(ps2_usart.c)
    Uses AVR USART engine to receive PS/2 signal.

To select method edit `rules.mk`.
