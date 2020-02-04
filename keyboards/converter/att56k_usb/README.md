# AT&T 56K 122 key terminal keyboard converter

A USB converter for AT&T 56K series keyboards.
* Keyboard Maintainer: [engicoder](https://github.com/engicoder)
* Hardware Supported: 
  - Converter: Pro Micro 5V, Teensy 2.0, ATmega32u4
  - Keyboards: 
    - AT&T 56K 460 ACW - 122 key magnetic separation
    - AT&T 56K 560 AGA - 122 key buckling spring


## Interfacing

The 56k keyboards use a 16 bit data packet. Depending on the keyboard the 
transmission maybe synchronous with a 9.6Kz clock frequency or ansynchronous
using one start bit and 9600 baud. In the synchronous version the data line read on the falling edge of the clock line.

### Pinout
The connector is a 6P6C modular jack with the following pinout:

| Pin | Function | Direction | Pro Micro | 32u4 Pin |
| --- | -------- | --------- | --------- | -------- |
| 1   | CLOCK    | out       | 3         | PD0      |
| 2   | PIEZO    | in        | 5         | PC6      |
| 3   | DATA     | out       | 2         | PD1      |
| 4   | VCC      | in        | RAW       |          |
| 5   | ENABLE   | in        | 4         | PD4      |
| 6   | GND      | in        | GND       |          |
The Pro Micro and 32u4 pins are give for the code in this repository.

VCC to GND is 5 volts.  
CLOCK is not used in all keyboards. When it does exist, the clock 
frequency is 9.6 kHz.  
PIEZO is active low and drives an electronic buzzer. The buzzer is not directly driven by this line. Buzzer activation requires a ~0.3ms low pulse.  
DATA is pulled high while idle. Its value is read on the falling edge of CLOCK.  
ENABLE is active low. If not pulled low, the keyboard will not generate any output. Note: Some keyboards seem
to require ENABLE be shorted to GND at the PCB.  

### Data Frame
The data frame is 16 bits of which the top 8 bits are always 0x7F.
The lower 8 bits contain the scan code. MAKE or BREAK is indicated in the 
most significant bit (bit 7), a value of 1 indicating a MAKE
```
 |            Header             |           Scan Code           |
 +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 |              0x7F             | M | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 ```

### Timing Diagram
Timing diagram for the press (MAKE) of the A key which has a scan code of 0x35.
```
     _____   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _____________
CLOCK     \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/
     ____    _______________________________     _______     ___     _________________
DATA     \__/                               \___/       \___/   \___/
     _____________________________________________________________________          __
Click                                                                     \________/
```
DATA transitions low half a clock cycle before CLOCK to ensure the leading 0 bit value. 
## Build

From the root qmk_firmware directory execute:

    $ make converter/att56k_usb

To specify a custom keymap in the folder <custom_keymap>, execute

    $ make converter/att56k_usb:custom_keymap

## Keymap
The default keymap is based on the standard PC 122 key layout.

The F24 key has been mapped to cycle through the clicker modes:
    OFF -> MAKE -> MAKE/BREAK
