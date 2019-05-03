# Stowaway Serial keyboard  to USB  protocol converter

A converter for Palm Pilot era Stowaway serial keyboards. 

Makes extensive use of the code from [cy384](https://github.com/cy384/ppk_usb). Ported to QMK by [milestogo](https://github.com/milestogo).

Hardware Supported: See hardware section below  
Hardware Availability: self-built

Make example for this keyboard (after setting up your build environment):

    make converter/palm_usb/stowaway:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Hardware

Target MCU is ATMega32u4 but other USB capable AVRs should also work. 

cy843 has a very specific way of wiring in order to fit all pins in sequence. It breaks
qmk because  the Arduino softserial library uses different pins from QMK. 

I've wired the pro micro  hardware as follows. 

Label| TX0,RX1,GND,GND,2  ,3  ,4  ,5  ,6  ,7
Palm |    ,   , * ,GND,VCC,RX ,NC ,RTS,nc ,DCD
MCU  |                ,D1 ,D0 ,   ,C6 ,   ,E6

\* The RX line from the keyboard should be conected to a ~10K ohm pull down resistor to ground.
RX --|--3
    10K
     |
    GND


Power management is not implemented yet, this just reboots the keyboard frequently. 

### Keyboards: 

Think Outside Stowaway Keyboards
There are at least 5 different versions of these keyboards out there. 

Group 1: Palm 3, Palm 5 & HP Journada 540, and Compaq iPaq keyboards. These share
the same RTS protocol, but with different pinouts for each device. 

Group 2: Handspring keyboards. These don't do handshaking protocol, and use TTL signal. 
Set HANDSPRING to 1 in config.h

Group 3: IRDA models. Untested but theoretically serial.

### Connectors

See https://github.com/cy384/ppk_usb for wiring & sample 3d printable sockets.

Only Palm3 wiring has been tested.  
RXD pin is output from keyboard to MCU's RX. 

Viewed from left to right with the keyboard in typing position. 

Palm3: [NC, VCC, RXD, RTS, NC, NC, DCD, NC, NC, GND]
Palm5: [NC, VCC, RXD, RTS, NC, NC, DCD, NC, NC, GND] (same order, different connector)
Handspring: [VCC/TXD, NC, NC, NC, GND, NC, NC, RXD]
Journada: [NC, NC, NC, GND, NC, RTS, NC, DTR/VCC, RXD, DCD, NC]   [GND-IN, VCC-IN]
Ipaq:  [NC, NC, DTR/VCC, NC, NC, RTS, NC, RXD, DCD, GND, NC, NC]

### Protocol

    Signal: Asynchronous, Negative logic, 9600baud, No Flow control
    Frame format: 1-Start bit, 8-Data bits, No-Parity, 1-Stop bit

    AVR USART engine expects positive logic while stowaway keyboard signal is negative.
    To use AVR UART engine you need external inverter in front of RX and TX pin.
    Otherwise you can software serial routine to communicate the keyboard.

This converter uses software method, you doesn't need any inverter part.


Commands From System To Keyboard
    none

Commands From Keyboard To System

    0xFA Reset/Ready Response(followed by 0xFD)
     
References

* http://www.splorp.com/pdf/stowawayhwref.pdf

### Todo
- Test on anything but a palm 3 model keyboard. 
- Change all of the soft serial to match the new Helix based code so that it is easier
to switch pins. 
- The driver should check for a keyboard that pressed the delete key then disconnected. 
Check every MAXDROP scans that the keyboard is there, and if not, clear the matrix. 
Not implemented yet, since matrix scan is so much faster than serial. 
