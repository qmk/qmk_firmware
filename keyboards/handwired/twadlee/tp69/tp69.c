/* Copyright 2020 Tracy Wadleigh
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "tp69.h"
#include "ps2.h"

#define FIX(pin) setPinOutput(PS2_##pin)
#define FLOAT(pin) setPinInputHigh(PS2_##pin)
#define SET(pin) writePinHigh(PS2_##pin)
#define CLEAR(pin) writePinLow(PS2_##pin)
#define READ(pin) readPin(PS2_##pin)
#define ISR_SYS_LOCK osalSysLockFromISR
#define ISR_SYS_UNLOCK osalSysUnlockFromISR
#define SYS_LOCK osalSysLock
#define SYS_UNLOCK osalSysUnlock

#define TIME_T systime_t
#define TIME_T_DEFAULT 0
#define NOW() osalOsGetSystemTimeX()
#define DIFF_US(t, t0) TIME_I2US(t - t0)

#define ISR_DEFN() OSAL_IRQ_HANDLER(KINETIS_PORTC_IRQ_VECTOR)
#define ISR_PROLOGUE OSAL_IRQ_PROLOGUE
#define ISR_EPILOGUE OSAL_IRQ_EPILOGUE

#define INIT_ISR() do {                                                 \
        nvicEnableVector(PINCD_IRQn, 3);                                \
        PORTC->PCR[TEENSY_PIN23] &= ~PORTx_PCRn_IRQC_MASK;              \
        PORTC->PCR[TEENSY_PIN23] |= PORTx_PCRn_IRQC(0xA);               \
    } while (0)


#define PBUF_SIZE 32
static uint8_t     pbuf[PBUF_SIZE];
static uint8_t     pbuf_head = 0;
static uint8_t     pbuf_tail = 0;
static inline void pbuf_enqueue(uint8_t data) {
    ISR_SYS_LOCK();
    uint8_t next = (pbuf_head + 1) % PBUF_SIZE;
    if (next != pbuf_tail) {
        pbuf[pbuf_head] = data;
        pbuf_head       = next;
    } else {
        print("pbuf: full\n");
    }
    ISR_SYS_UNLOCK();
}
static inline uint8_t pbuf_dequeue(void) {
    uint8_t val = 0;

    SYS_LOCK();
    if (pbuf_head != pbuf_tail) {
        val       = pbuf[pbuf_tail];
        pbuf_tail = (pbuf_tail + 1) % PBUF_SIZE;
    }
    SYS_UNLOCK();

    return val;
}
static inline bool pbuf_has_data(void) {
    SYS_LOCK();
    bool has_data = (pbuf_head != pbuf_tail);
    SYS_UNLOCK();
    return has_data;
}
static inline void pbuf_clear(void) {
    SYS_LOCK();
    pbuf_head = pbuf_tail = 0;
    SYS_UNLOCK();
}

uint8_t ps2_error;

// state for communicating tx to ISR without disabling it
volatile bool g_ps2_tx_commanded;
volatile uint8_t g_ps2_tx_data;

void ps2_host_init(void) {
    // idle - allow device to send
    FIX(CLOCK);
    FIX(DATA);
    SET(CLOCK);
    SET(DATA);

    // Initialize and enable IRQ for rising clock edge.
    // Enabling for rising & falling clock edges is suboptimal
    // but acceptable because the ISR will explicitly ignore
    // rising edges.
    INIT_ISR();

    // pin state for rx - data & clock: input high
    // setting clock for input effectively starts the ISR
    FLOAT(CLOCK);
    FLOAT(DATA);
}

uint8_t ps2_host_recv_response(void) {
    // Command may take 25ms/20ms at most([5]p.46, [3]p.21)
    uint8_t retry = 25;
    while (retry-- && !pbuf_has_data()) {
        wait_ms(1);
    }
    return pbuf_dequeue();
}

uint8_t ps2_host_recv(void) {
    if (pbuf_has_data()) {
        ps2_error = PS2_ERR_NONE;
        return pbuf_dequeue();
    } else {
        ps2_error = PS2_ERR_NODATA;
        return 0;
    }
}

void ps2_host_set_led(uint8_t led) {
    ps2_host_send(0xED);
    ps2_host_send(led);
}

uint8_t ps2_host_send(uint8_t data) {
    // inihibit receive - suspends ISR
    FIX(CLOCK);
    FIX(DATA);
    CLEAR(CLOCK);
    SET(DATA);
    wait_us(100);

    // request to send
    // ISR ignores rising clock edge even if it is triggered
    SET(CLOCK);
    CLEAR(DATA);

    // notify the ISR of send
    g_ps2_tx_data = data;
    g_ps2_tx_commanded = true;

    // free the clock - resumes the ISR
    FLOAT(CLOCK);

    // pin state for tx - data: output; clock: input high
    // wait for ISR to finish
    while (g_ps2_tx_commanded) wait_us(1);
    if (ps2_error) return 0;
    return ps2_host_recv_response();
}

ISR_DEFN() {
    ISR_PROLOGUE();

    static enum {
        INIT,
        START,
        BIT0,
        BIT1,
        BIT2,
        BIT3,
        BIT4,
        BIT5,
        BIT6,
        BIT7,
        PARITY,
        STOP,
        ACK
    } state               = INIT;
    static uint8_t data   = 0;
    static uint8_t parity = 1;
    static bool    rx     = true;
    static TIME_T  prev   = TIME_T_DEFAULT;
    TIME_T now;

    // rising edge? skip.
    if (READ(CLOCK)) {
        goto SKIP;
    }

    // get current system time
    now = NOW();
    // if in the middle of tx/rx and more than 100 us have elapsed, raise error.
    if (INIT != state && DIFF_US(now, prev) > 100) {
        goto ERROR;
    }

    if (g_ps2_tx_commanded) {
        // tx
        if (rx) { // reset state for tx
            rx = false;
            state = INIT;
            data = g_ps2_tx_data;
            parity = 1;
        }
        ++state;
        switch (state) {
            case START:
                SET(DATA);
                break;
            case BIT0:
            case BIT1:
            case BIT2:
            case BIT3:
            case BIT4:
            case BIT5:
            case BIT6:
            case BIT7:
                if(data & 0x01) {
                    SET(DATA);
                    ++parity;
                } else {
                    CLEAR(DATA);
                }
                data >>= 1;
                break;
            case PARITY:
                if(parity & 0x01) {
                    SET(DATA);
                } else {
                    CLEAR(DATA);
                }
                break;
            case STOP:
                SET(DATA);
                // return pin state to input/input
                FLOAT(DATA);
                break;
            case ACK:
                // return ISR state to rx
                rx = true;
                g_ps2_tx_commanded = false;
                if (READ(DATA)) {
                    goto RESET;
                } else {
                    goto ERROR;
                }
                break;
            default:
                goto ERROR;
        }
        goto RETURN;
    } else {
        // rx
        state++;
        switch (state) {
            case START:
                if (READ(DATA)) goto ERROR;
                break;
            case BIT0:
            case BIT1:
            case BIT2:
            case BIT3:
            case BIT4:
            case BIT5:
            case BIT6:
            case BIT7:
                data >>= 1;
                if (READ(DATA)) {
                    data |= 0x80;
                    ++parity;
                }
                break;
            case PARITY:
                if (READ(DATA)) {
                    if (!(parity & 0x01)) goto ERROR;
                } else {
                    if (parity & 0x01) goto ERROR;
                }
                break;
            case STOP:
                if (!READ(DATA)) goto ERROR;
                pbuf_enqueue(data);
                goto RESET;
                break;
            default:
                goto ERROR;
        }
        goto RETURN;
    }
ERROR:
    ps2_error = state;
RESET:
    state = INIT;
    data  = 0;
    parity = 1;
RETURN:
    prev = now;
SKIP:
    ISR_EPILOGUE();
    return;
}
