# Sun to USB keyboard protocol converter

A converter for using non-USB Sun keyboards.

Original code from the [TMK firmware](https://github.com/tmk/tmk_keyboard/tree/master/converter/sun_usb). Ported to QMK by [Yann Hodique](https://github.com/sigma).

Keyboard Maintainer: [Yann Hodique](https://github.com/sigma)  
Hardware Supported: See hardware section below  
Hardware Availability: self-built

Make example for this keyboard (after setting up your build environment):

    make converter/sun_usb/type5:default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.


## Hardware

Target MCU is ATMega32u4 but other USB capable AVR will also work. The maintainer mostly uses Teensy 2.0 boards.
Supported keyboards: Sun Type 3 and 5 Keyboards,

### Connector

8Pin mini DIN

       ___ ___
      /  |_|  \
     / 8  7  6 \
    | 5    4  3 |
     \_ 2   1 _/
       \_____/
    (receptacle)


Wiring:

    Pin mini DIN        MCU
    ----------------------------------
    1   GND             GND
    2   GND             GND
    3   5V
    4   RX/TX(Mouse)
    5   RX              PD3
    6   TX              PD2
    7   GND             GND
    8   5V              VCC


### Protocol

    Signal: Asynchronous, Negative logic, 1200baud, No Flow control
    Frame format: 1-Start bit, 8-Data bits, No-Parity, 1-Stop bit

    AVR USART engine expects positive logic while Sun keyboard signal is negative.
    To use AVR UART engine you need external inverter in front of RX and TX pin.
    Otherwise you can software serial routine to communicate the keyboard.

This converter uses software method, you doesn't need any inverter part.


Commands From System To Keyboard

    0x01 Reset
            Keyboard responds with following byte sequence:
            Success: 0xFF 0x04 0x7F
            Fail:    0x7E 0x01 0x7F
    0x02 Bell On
    0x03 Bell Off
    0x0A Click On
    0x0B Click Off
    0x0E LED
            followed by LED status byte:
            bit: 3       2       1       0
            LED: CapsLk  ScrLk   Compose NumLk
    0x0F Layout
            Keyboard responds with 'Layout Response' 0xFE 0xXX

Commands From Keyboard To System

    0x7F Idle
            means no keys pressed.
    0xFE Layout Response
    0xFF Reset Response(followed by 0x04)
     
References

* http://kentie.net/article/sunkbd/page2.htm
* http://kentie.net/article/sunkbd/KBD.pdf
