#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>
#include "adb.h"


static inline void data_lo(void);
static inline void data_hi(void);
static inline bool data_in(void);
#ifdef ADB_PSW_BIT
static inline void psw_lo(void);
static inline void psw_hi(void);
static inline bool psw_in(void);
#endif

static inline void attention(void);
static inline void place_bit0(void);
static inline void place_bit1(void);
static inline void send_byte(uint8_t data);
static inline bool read_bit(void);
static inline uint8_t read_byte(void);
static inline uint8_t wait_data_lo(uint8_t us);
static inline uint8_t wait_data_hi(uint8_t us);


void adb_host_init(void)
{
    data_hi();
#ifdef ADB_PSW_BIT
    psw_hi();
#endif
}

#ifdef ADB_PSW_BIT
bool adb_host_psw(void)
{
    return psw_in();
}
#endif

uint16_t adb_host_kbd_recv(void)
{
    uint16_t data = 0;
    attention();
    send_byte(0x2C);            // Addr:2, Cmd:talk(11), Reg:0(00)
    place_bit0();               // Stopbit
    if (!wait_data_lo(0xFF))    // Stop to Start(140-260us)
        return 0;               // No data to send
    if (!read_bit())            // Startbit(1)
        return -2;
    data = read_byte();
    data = (data<<8) | read_byte();
    if (read_bit())             // Stopbit(0)
        return -3;
    return data;
}


static inline void data_lo()
{
    ADB_DDR  |=  (1<<ADB_DATA_BIT);
    ADB_PORT &= ~(1<<ADB_DATA_BIT);
}
static inline void data_hi()
{
    ADB_PORT |=  (1<<ADB_DATA_BIT);
    ADB_DDR  &= ~(1<<ADB_DATA_BIT);
}
static inline bool data_in()
{
    ADB_PORT |=  (1<<ADB_DATA_BIT);
    ADB_DDR  &= ~(1<<ADB_DATA_BIT);
    return ADB_PIN&(1<<ADB_DATA_BIT);
}

#ifdef ADB_PSW_BIT
static inline void psw_lo()
{
    ADB_DDR  |=  (1<<ADB_PSW_BIT);
    ADB_PORT &= ~(1<<ADB_PSW_BIT);
}
static inline void psw_hi()
{
    ADB_PORT |=  (1<<ADB_PSW_BIT);
    ADB_DDR  &= ~(1<<ADB_PSW_BIT);
}
static inline bool psw_in()
{
    ADB_PORT |=  (1<<ADB_PSW_BIT);
    ADB_DDR  &= ~(1<<ADB_PSW_BIT);
    return ADB_PIN&(1<<ADB_PSW_BIT);
}
#endif

static inline void attention(void)
{
    data_lo();
    _delay_us(700);
    place_bit1();
}

static inline void place_bit0(void)
{
    data_lo();
    _delay_us(65);
    data_hi();
    _delay_us(35);
}

static inline void place_bit1(void)
{
    data_lo();
    _delay_us(35);
    data_hi();
    _delay_us(65);
}

static inline void send_byte(uint8_t data)
{
    for (int i = 0; i < 8; i++) {
        if (data&(0x80>>i))
            place_bit1();
        else
            place_bit0();
    }
}

static inline bool read_bit(void)
{
    // ADB Bit Cells
    //
    // bit0: ______~~~
    //       65    :35us
    //
    // bit1: ___~~~~~~
    //       35 :65us
    //
    // bit0 low time: 60-70% of bit cell(42-91us)
    // bit1 low time: 30-40% of bit cell(21-52us)
    // bit cell time: 70-130us
    // [from Apple IIgs Hardware Reference Second Edition]
    //
    // After 55us if data line is low/high then bit is 0/1.
    // Too simple to rely on?
    bool bit;
    wait_data_lo(75);   // wait the beginning of bit cell
    _delay_us(55);
    bit = data_in();
    wait_data_hi(36);   // wait high part of bit cell
    return bit;
}

static inline uint8_t read_byte(void)
{
    uint8_t data = 0;
    for (int i = 0; i < 8; i++) {
        data <<= 1;
        if (read_bit())
            data = data | 1;
    }
    return data;
}

static inline uint8_t wait_data_lo(uint8_t us)
{
    while (data_in() && us) {
        _delay_us(1);
        us--;
    }
    return us;
}

static inline uint8_t wait_data_hi(uint8_t us)
{
    while (!data_in() && us) {
        _delay_us(1);
        us--;
    }
    return us;
}
