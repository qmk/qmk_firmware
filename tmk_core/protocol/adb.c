/*
Copyright 2011-19 Jun WAKO <wakojun@gmail.com>
Copyright 2013 Shay Green <gblargg@gmail.com>

This software is licensed with a Modified BSD License.
All of this is supposed to be Free Software, Open Source, DFSG-free,
GPL-compatible, and OK to use in both free and proprietary applications.
Additions and corrections to this file are welcome.


Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in
  the documentation and/or other materials provided with the
  distribution.

* Neither the name of the copyright holders nor the names of
  contributors may be used to endorse or promote products derived
  from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "adb.h"
#include "print.h"

// GCC doesn't inline functions normally
#define data_lo() (ADB_DDR |= (1 << ADB_DATA_BIT))
#define data_hi() (ADB_DDR &= ~(1 << ADB_DATA_BIT))
#define data_in() (ADB_PIN & (1 << ADB_DATA_BIT))

#ifdef ADB_PSW_BIT
static inline void psw_lo(void);
static inline void psw_hi(void);
static inline bool psw_in(void);
#endif

static inline void     attention(void);
static inline void     place_bit0(void);
static inline void     place_bit1(void);
static inline void     send_byte(uint8_t data);
static inline uint16_t wait_data_lo(uint16_t us);
static inline uint16_t wait_data_hi(uint16_t us);

void adb_host_init(void) {
    ADB_PORT &= ~(1 << ADB_DATA_BIT);
    data_hi();
#ifdef ADB_PSW_BIT
    psw_hi();
#endif
}

#ifdef ADB_PSW_BIT
bool adb_host_psw(void) { return psw_in(); }
#endif

/*
 * Don't call this in a row without the delay, otherwise it makes some of poor controllers
 * overloaded and misses strokes. Recommended interval is 12ms.
 *
 * Thanks a lot, blargg!
 * <http://geekhack.org/index.php?topic=14290.msg1068919#msg1068919>
 * <http://geekhack.org/index.php?topic=14290.msg1070139#msg1070139>
 */
uint16_t adb_host_kbd_recv(void) { return adb_host_talk(ADB_ADDR_KEYBOARD, ADB_REG_0); }

#ifdef ADB_MOUSE_ENABLE
__attribute__((weak)) void adb_mouse_init(void) { return; }

__attribute__((weak)) void adb_mouse_task(void) { return; }

uint16_t adb_host_mouse_recv(void) { return adb_host_talk(ADB_ADDR_MOUSE, ADB_REG_0); }
#endif

// This sends Talk command to read data from register and returns length of the data.
uint8_t adb_host_talk_buf(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t len) {
    for (int8_t i = 0; i < len; i++) buf[i] = 0;

    cli();
    attention();
    send_byte((addr << 4) | ADB_CMD_TALK | reg);
    place_bit0();  // Stopbit(0)
    // TODO: Service Request(Srq):
    // Device holds low part of comannd stopbit for 140-260us
    //
    // Command:
    // ......._     ______________________    ___ ............_     -------
    //         |   |                      |  |   |             |   |
    // Command |   |                      |  |   | Data bytes  |   |
    // ........|___|  |     140-260       |__|   |_............|___|
    //         |stop0 | Tlt Stop-to-Start |start1|             |stop0 |
    //
    // Command without data:
    // ......._     __________________________
    //         |   |
    // Command |   |
    // ........|___|  |     140-260       |
    //         |stop0 | Tlt Stop-to-Start |
    //
    // Service Request:
    // ......._                     ______    ___ ............_     -------
    //         |     140-260       |      |  |   |             |   |
    // Command |  Service Request  |      |  |   | Data bytes  |   |
    // ........|___________________|      |__|   |_............|___|
    //         |stop0 |                   |start1|             |stop0 |
    // ......._                     __________
    //         |     140-260       |
    // Command |  Service Request  |
    // ........|___________________|
    //         |stop0 |
    // This can be happened?
    // ......._     ______________________    ___ ............_                   -----
    //         |   |                      |  |   |             |    140-260      |
    // Command |   |                      |  |   | Data bytes  | Service Request |
    // ........|___|  |     140-260       |__|   |_............|_________________|
    //         |stop0 | Tlt Stop-to-Start |start1|             |stop0 |
    //
    // "Service requests are issued by the devices during a very specific time at the
    // end of the reception of the command packet.
    // If a device in need of service issues a service request, it must do so within
    // the 65 µs of the Stop Bit’s low time and maintain the line low for a total of 300 µs."
    //
    // "A device sends a Service Request signal by holding the bus low during the low
    // portion of the stop bit of any command or data transaction. The device must lengthen
    // the stop by a minimum of 140 J.lS beyond its normal duration, as shown in Figure 8-15."
    // http://ww1.microchip.com/downloads/en/AppNotes/00591b.pdf
    if (!wait_data_hi(500)) {  // Service Request(310us Adjustable Keyboard): just ignored
        xprintf("R");
        sei();
        return 0;
    }
    if (!wait_data_lo(500)) {  // Tlt/Stop to Start(140-260us)
        sei();
        return 0;  // No data from device(not error);
    }

    // start bit(1)
    if (!wait_data_hi(40)) {
        xprintf("S");
        sei();
        return 0;
    }
    if (!wait_data_lo(100)) {
        xprintf("s");
        sei();
        return 0;
    }

    uint8_t n = 0;  // bit count
    do {
        //
        // |<- bit_cell_max(130) ->|
        // |        |<-   lo     ->|
        // |        |       |<-hi->|
        //           _______
        // |        |       |
        // | 130-lo | lo-hi |
        // |________|       |
        //
        uint8_t lo = (uint8_t)wait_data_hi(130);
        if (!lo) goto error;  // no more bit or after stop bit

        uint8_t hi = (uint8_t)wait_data_lo(lo);
        if (!hi) goto error;  // stop bit extedned by Srq?

        if (n / 8 >= len) continue;  // can't store in buf

        buf[n / 8] <<= 1;
        if ((130 - lo) < (lo - hi)) {
            buf[n / 8] |= 1;
        }
    } while (++n);

error:
    sei();
    return n / 8;
}

uint16_t adb_host_talk(uint8_t addr, uint8_t reg) {
    uint8_t len;
    uint8_t buf[8];
    len = adb_host_talk_buf(addr, reg, buf, 8);
    if (len != 2) return 0;
    return (buf[0] << 8 | buf[1]);
}

void adb_host_listen_buf(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t len) {
    cli();
    attention();
    send_byte((addr << 4) | ADB_CMD_LISTEN | reg);
    place_bit0();  // Stopbit(0)
    // TODO: Service Request
    _delay_us(200);  // Tlt/Stop to Start
    place_bit1();    // Startbit(1)
    for (int8_t i = 0; i < len; i++) {
        send_byte(buf[i]);
        // xprintf("%02X ", buf[i]);
    }
    place_bit0();  // Stopbit(0);
    sei();
}

void adb_host_listen(uint8_t addr, uint8_t reg, uint8_t data_h, uint8_t data_l) {
    uint8_t buf[2] = {data_h, data_l};
    adb_host_listen_buf(addr, reg, buf, 2);
}

void adb_host_flush(uint8_t addr) {
    cli();
    attention();
    send_byte((addr << 4) | ADB_CMD_FLUSH);
    place_bit0();    // Stopbit(0)
    _delay_us(200);  // Tlt/Stop to Start
    sei();
}

// send state of LEDs
void adb_host_kbd_led(uint8_t led) {
    // Listen Register2
    //  upper byte: not used
    //  lower byte: bit2=ScrollLock, bit1=CapsLock, bit0=NumLock
    adb_host_listen(ADB_ADDR_KEYBOARD, ADB_REG_2, 0, led & 0x07);
}

#ifdef ADB_PSW_BIT
static inline void psw_lo() {
    ADB_DDR |= (1 << ADB_PSW_BIT);
    ADB_PORT &= ~(1 << ADB_PSW_BIT);
}
static inline void psw_hi() {
    ADB_PORT |= (1 << ADB_PSW_BIT);
    ADB_DDR &= ~(1 << ADB_PSW_BIT);
}
static inline bool psw_in() {
    ADB_PORT |= (1 << ADB_PSW_BIT);
    ADB_DDR &= ~(1 << ADB_PSW_BIT);
    return ADB_PIN & (1 << ADB_PSW_BIT);
}
#endif

static inline void attention(void) {
    data_lo();
    _delay_us(800 - 35);  // bit1 holds lo for 35 more
    place_bit1();
}

static inline void place_bit0(void) {
    data_lo();
    _delay_us(65);
    data_hi();
    _delay_us(35);
}

static inline void place_bit1(void) {
    data_lo();
    _delay_us(35);
    data_hi();
    _delay_us(65);
}

static inline void send_byte(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        if (data & (0x80 >> i))
            place_bit1();
        else
            place_bit0();
    }
}

// These are carefully coded to take 6 cycles of overhead.
// inline asm approach became too convoluted
static inline uint16_t wait_data_lo(uint16_t us) {
    do {
        if (!data_in()) break;
        _delay_us(1 - (6 * 1000000.0 / F_CPU));
    } while (--us);
    return us;
}

static inline uint16_t wait_data_hi(uint16_t us) {
    do {
        if (data_in()) break;
        _delay_us(1 - (6 * 1000000.0 / F_CPU));
    } while (--us);
    return us;
}

/*
ADB Protocol
============

Resources
---------
ADB - The Untold Story: Space Aliens Ate My Mouse
    http://developer.apple.com/legacy/mac/library/#technotes/hw/hw_01.html
ADB Manager
    http://developer.apple.com/legacy/mac/library/documentation/mac/pdf/Devices/ADB_Manager.pdf
    Service request(5-17)
Apple IIgs Hardware Reference Second Edition [Chapter6 p121]
    ftp://ftp.apple.asimov.net/pub/apple_II/documentation/Apple%20IIgs%20Hardware%20Reference.pdf
ADB Keycode
    http://72.0.193.250/Documentation/macppc/adbkeycodes/
    http://m0115.web.fc2.com/m0115.jpg
    [Inside Macintosh volume V, pages 191-192]
    http://www.opensource.apple.com/source/IOHIDFamily/IOHIDFamily-421.18.3/IOHIDFamily/Cosmo_USB2ADB.c
ADB Signaling
    http://kbdbabel.sourceforge.net/doc/kbd_signaling_pcxt_ps2_adb.pdf
ADB Overview & History
    http://en.wikipedia.org/wiki/Apple_Desktop_Bus
Microchip Application Note: ADB device(with code for PIC16C)
    http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1824&appnote=en011062
AVR ATtiny2131 ADB to PS/2 converter(Japanese)
    http://hp.vector.co.jp/authors/VA000177/html/KeyBoardA5DEA5CBA5A2II.html


Pinouts
-------
    ADB female socket from the front:
    __________
    |        | <--- top
    | 4o  o3 |
    |2o    o1|
    |   ==   |
    |________| <--- bottom
      |    |   <--- 4pins


    ADB female socket from bottom:

    ========== <--- front
    |        |
    |        |
    |2o    o1|
    |4o    o3|
    ---------- <--- back

    1: Data
    2: Power SW(low when press Power key)
    3: Vcc(5V)
    4: GND


Commands
--------
    ADB command is 1byte and consists of 4bit-address, 2bit-command
    type and 2bit-register. The commands are always sent by Host.

    Command format:
    7 6 5 4 3 2 1 0
    | | | |------------ address
            | |-------- command type
                | |---- register

    bits                commands
    ------------------------------------------------------
    - - - - 0 0 0 0     Send Reset(reset all devices)
    A A A A 0 0 0 1     Flush(reset a device)
    - - - - 0 0 1 0     Reserved
    - - - - 0 0 1 1     Reserved
    - - - - 0 1 - -     Reserved
    A A A A 1 0 R R     Listen(write to a device)
    A A A A 1 1 R R     Talk(read from a device)

    The command to read keycodes from keyboard is 0x2C which
    consist of keyboard address 2 and Talk against register 0.

    Address:
    2:  keyboard
    3:  mice

    Registers:
    0: application(keyboard uses this to store its data.)
    1: application
    2: application(keyboard uses this for LEDs and state of modifiers)
    3: status and command


Communication
-------------
    This is a minimum information for keyboard communication.
    See "Resources" for detail.

    Signaling:

    ~~~~____________~~||||||||||||__~~~~~_~~|||||||||||||||__~~~~

        |800us     |  |7 Command 0|  |   |  |15-64  Data  0|Stopbit(0)
        +Attention |              |  |   +Startbit(1)
                   +Startbit(1)   |  +Tlt(140-260us)
                                  +stopbit(0)

    Bit cells:

    bit0: ______~~~
          65    :35us

    bit1: ___~~~~~~
          35 :65us

    bit0 low time: 60-70% of bit cell(42-91us)
    bit1 low time: 30-40% of bit cell(21-52us)
    bit cell time: 70-130us
    [from Apple IIgs Hardware Reference Second Edition]

    Criterion for bit0/1:
    After 55us if line is low/high then bit is 0/1.

    Attention & start bit:
    Host asserts low in 560-1040us then places start bit(1).

    Tlt(Stop to Start):
    Bus stays high in 140-260us then device places start bit(1).

    Global reset:
    Host asserts low in 2.8-5.2ms. All devices are forced to reset.

    Service request from device(Srq):
    Device can request to send at commad(Global only?) stop bit.
    Requesting device keeps low for 140-260us at stop bit of command.


Keyboard Data(Register0)
    This 16bit data can contains two keycodes and two released flags.
    First keycode is palced in upper byte. When one keyocode is sent,
    lower byte is 0xFF.
    Release flag is 1 when key is released.

    1514 . . . . . 8 7 6 . . . . . 0
     | | | | | | | | | +-+-+-+-+-+-+-   Keycode2
     | | | | | | | | +---------------   Released2(1 when the key is released)
     | +-+-+-+-+-+-+-----------------   Keycode1
     +-------------------------------   Released1(1 when the key is released)

    Keycodes:
    Scancode consists of 7bit keycode and 1bit release flag.
    Device can send two keycodes at once. If just one keycode is sent
    keycode1 contains it and keyocode2 is 0xFF.

    Power switch:
    You can read the state from PSW line(active low) however
    the switch has a special scancode 0x7F7F, so you can
    also read from Data line. It uses 0xFFFF for release scancode.

Keyboard LEDs & state of keys(Register2)
    This register hold current state of three LEDs and nine keys.
    The state of LEDs can be changed by sending Listen command.

    1514 . . . . . . 7 6 5 . 3 2 1 0
     | | | | | | | | | | | | | | | +-   LED1(NumLock)
     | | | | | | | | | | | | | | +---   LED2(CapsLock)
     | | | | | | | | | | | | | +-----   LED3(ScrollLock)
     | | | | | | | | | | +-+-+-------   Reserved
     | | | | | | | | | +-------------   ScrollLock
     | | | | | | | | +---------------   NumLock
     | | | | | | | +-----------------   Apple/Command
     | | | | | | +-------------------   Option
     | | | | | +---------------------   Shift
     | | | | +-----------------------   Control
     | | | +-------------------------   Reset/Power
     | | +---------------------------   CapsLock
     | +-----------------------------   Delete
     +-------------------------------   Reserved

Address, Handler ID and bits(Register3)
    1514131211 . . 8 7 . . . . . . 0
     | | | | | | | | | | | | | | | |
     | | | | | | | | +-+-+-+-+-+-+-+-   Handler ID
     | | | | +-+-+-+-----------------   Address
     | | | +-------------------------   0
     | | +---------------------------   Service request enable(1 = enabled)
     | +-----------------------------   Exceptional event(alwyas 1 if not used)
     +-------------------------------   0

ADB Bit Cells
    bit cell time: 70-130us
    low part of bit0: 60-70% of bit cell
    low part of bit1: 30-40% of bit cell

       bit cell time         70us        130us
       --------------------------------------------
       low  part of bit0     42-49       78-91
       high part of bit0     21-28       39-52
       low  part of bit1     21-28       39-52
       high part of bit1     42-49       78-91


    bit0:
       70us bit cell:
         ____________~~~~~~
         42-49        21-28

       130us bit cell:
         ____________~~~~~~
         78-91        39-52

    bit1:
       70us bit cell:
         ______~~~~~~~~~~~~
         21-28        42-49

       130us bit cell:
         ______~~~~~~~~~~~~
         39-52        78-91

    [from Apple IIgs Hardware Reference Second Edition]

Keyboard Handle ID
    Apple Standard Keyboard M0116:      0x01
    Apple Extended Keyboard M0115:      0x02
    Apple Extended Keyboard II M3501:   0x02
    Apple Adjustable Keybaord:          0x10

    http://lxr.free-electrons.com/source/drivers/macintosh/adbhid.c?v=4.4#L802

END_OF_ADB
*/
