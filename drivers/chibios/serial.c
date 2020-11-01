/*
 * WARNING: be careful changing this code, it is very timing dependent
 */

#include "quantum.h"
#include "serial.h"
#include "wait.h"

#include "hal.h"

// TODO: resolve/remove build warnings
#if defined(RGBLIGHT_ENABLE) && defined(RGBLED_SPLIT) && defined(PROTOCOL_CHIBIOS) && defined(WS2812_DRIVER_BITBANG)
#    warning "RGBLED_SPLIT not supported with bitbang WS2812 driver"
#endif

// default wait implementation cannot be called within interrupt
//   this method seems to be more accurate than GPT timers
#if PORT_SUPPORTS_RT == FALSE
#    error "chSysPolledDelayX method not supported on this platform"
#else
#    undef wait_us
#    define wait_us(x) chSysPolledDelayX(US2RTC(STM32_SYSCLK, x))
#endif

#ifndef SELECT_SOFT_SERIAL_SPEED
#    define SELECT_SOFT_SERIAL_SPEED 1
// TODO: correct speeds...
//  0: about 189kbps (Experimental only)
//  1: about 137kbps (default)
//  2: about 75kbps
//  3: about 39kbps
//  4: about 26kbps
//  5: about 20kbps
#endif

// Serial pulse period in microseconds. At the moment, going lower than 12 causes communication failure
#if SELECT_SOFT_SERIAL_SPEED == 0
#    define SERIAL_DELAY 12
#elif SELECT_SOFT_SERIAL_SPEED == 1
#    define SERIAL_DELAY 16
#elif SELECT_SOFT_SERIAL_SPEED == 2
#    define SERIAL_DELAY 24
#elif SELECT_SOFT_SERIAL_SPEED == 3
#    define SERIAL_DELAY 32
#elif SELECT_SOFT_SERIAL_SPEED == 4
#    define SERIAL_DELAY 48
#elif SELECT_SOFT_SERIAL_SPEED == 5
#    define SERIAL_DELAY 64
#else
#    error invalid SELECT_SOFT_SERIAL_SPEED value
#endif

inline static void serial_delay(void) { wait_us(SERIAL_DELAY); }
inline static void serial_delay_half(void) { wait_us(SERIAL_DELAY / 2); }
inline static void serial_delay_blip(void) { wait_us(1); }
inline static void serial_output(void) { setPinOutput(SOFT_SERIAL_PIN); }
inline static void serial_input(void) { setPinInputHigh(SOFT_SERIAL_PIN); }
inline static bool serial_read_pin(void) { return !!readPin(SOFT_SERIAL_PIN); }
inline static void serial_low(void) { writePinLow(SOFT_SERIAL_PIN); }
inline static void serial_high(void) { writePinHigh(SOFT_SERIAL_PIN); }

void interrupt_handler(void *arg);

// Use thread + palWaitLineTimeout instead of palSetLineCallback
//  - Methods like setPinOutput and palEnableLineEvent/palDisableLineEvent
//    cause the interrupt to lock up, which would limit to only receiving data...
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
    (void)arg;
    chRegSetThreadName("blinker");
    while (true) {
        palWaitLineTimeout(SOFT_SERIAL_PIN, TIME_INFINITE);
        interrupt_handler(NULL);
    }
}

static SSTD_t *Transaction_table      = NULL;
static uint8_t Transaction_table_size = 0;

void soft_serial_initiator_init(SSTD_t *sstd_table, int sstd_table_size) {
    Transaction_table      = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;

    serial_output();
    serial_high();
}

void soft_serial_target_init(SSTD_t *sstd_table, int sstd_table_size) {
    Transaction_table      = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;

    serial_input();

    palEnablePadEvent(PAL_PORT(SOFT_SERIAL_PIN), PAL_PAD(SOFT_SERIAL_PIN), PAL_EVENT_MODE_FALLING_EDGE);
    chThdCreateStatic(waThread1, sizeof(waThread1), HIGHPRIO, Thread1, NULL);
}

// Used by the master to synchronize timing with the slave.
static void __attribute__((noinline)) sync_recv(void) {
    serial_input();
    // This shouldn't hang if the slave disconnects because the
    // serial line will float to high if the slave does disconnect.
    while (!serial_read_pin()) {
    }

    serial_delay();
}

// Used by the slave to send a synchronization signal to the master.
static void __attribute__((noinline)) sync_send(void) {
    serial_output();

    serial_low();
    serial_delay();

    serial_high();
}

// Reads a byte from the serial line
static uint8_t __attribute__((noinline)) serial_read_byte(void) {
    uint8_t byte = 0;
    serial_input();
    for (uint8_t i = 0; i < 8; ++i) {
        byte = (byte << 1) | serial_read_pin();
        serial_delay();
    }

    return byte;
}

// Sends a byte with MSB ordering
static void __attribute__((noinline)) serial_write_byte(uint8_t data) {
    uint8_t b = 8;
    serial_output();
    while (b--) {
        if (data & (1 << b)) {
            serial_high();
        } else {
            serial_low();
        }
        serial_delay();
    }
}

// interrupt handle to be used by the slave device
void interrupt_handler(void *arg) {
    chSysLockFromISR();

    sync_send();

    // read mid pulses
    serial_delay_blip();

    uint8_t checksum_computed = 0;
    int     sstd_index        = 0;

#ifdef SERIAL_USE_MULTI_TRANSACTION
    sstd_index = serial_read_byte();
    sync_send();
#endif

    SSTD_t *trans = &Transaction_table[sstd_index];
    for (int i = 0; i < trans->initiator2target_buffer_size; ++i) {
        trans->initiator2target_buffer[i] = serial_read_byte();
        sync_send();
        checksum_computed += trans->initiator2target_buffer[i];
    }
    checksum_computed ^= 7;
    uint8_t checksum_received = serial_read_byte();
    sync_send();

    // wait for the sync to finish sending
    serial_delay();

    uint8_t checksum = 0;
    for (int i = 0; i < trans->target2initiator_buffer_size; ++i) {
        serial_write_byte(trans->target2initiator_buffer[i]);
        sync_send();
        serial_delay_half();
        checksum += trans->target2initiator_buffer[i];
    }
    serial_write_byte(checksum ^ 7);
    sync_send();

    // wait for the sync to finish sending
    serial_delay();

    *trans->status = (checksum_computed == checksum_received) ? TRANSACTION_ACCEPTED : TRANSACTION_DATA_ERROR;

    // end transaction
    serial_input();

    // TODO: remove extra delay between transactions
    serial_delay();

    chSysUnlockFromISR();
}

/////////
//  start transaction by initiator
//
// int  soft_serial_transaction(int sstd_index)
//
// Returns:
//    TRANSACTION_END
//    TRANSACTION_NO_RESPONSE
//    TRANSACTION_DATA_ERROR
// this code is very time dependent, so we need to disable interrupts
#ifndef SERIAL_USE_MULTI_TRANSACTION
int soft_serial_transaction(void) {
    int sstd_index = 0;
#else
int soft_serial_transaction(int sstd_index) {
#endif

    if (sstd_index > Transaction_table_size) return TRANSACTION_TYPE_ERROR;
    SSTD_t *trans = &Transaction_table[sstd_index];

    // TODO: remove extra delay between transactions
    serial_delay();

    // this code is very time dependent, so we need to disable interrupts
    chSysLock();

    // signal to the slave that we want to start a transaction
    serial_output();
    serial_low();
    serial_delay_blip();

    // wait for the slaves response
    serial_input();
    serial_high();
    serial_delay();

    // check if the slave is present
    if (serial_read_pin()) {
        // slave failed to pull the line low, assume not present
        dprintf("serial::NO_RESPONSE\n");
        chSysUnlock();
        return TRANSACTION_NO_RESPONSE;
    }

    // if the slave is present syncronize with it

    uint8_t checksum = 0;
    // send data to the slave
#ifdef SERIAL_USE_MULTI_TRANSACTION
    serial_write_byte(sstd_index);  // first chunk is transaction id
    sync_recv();
#endif
    for (int i = 0; i < trans->initiator2target_buffer_size; ++i) {
        serial_write_byte(trans->initiator2target_buffer[i]);
        sync_recv();
        checksum += trans->initiator2target_buffer[i];
    }
    serial_write_byte(checksum ^ 7);
    sync_recv();

    serial_delay();
    serial_delay();  // read mid pulses

    // receive data from the slave
    uint8_t checksum_computed = 0;
    for (int i = 0; i < trans->target2initiator_buffer_size; ++i) {
        trans->target2initiator_buffer[i] = serial_read_byte();
        sync_recv();
        checksum_computed += trans->target2initiator_buffer[i];
    }
    checksum_computed ^= 7;
    uint8_t checksum_received = serial_read_byte();

    sync_recv();
    serial_delay();

    if ((checksum_computed) != (checksum_received)) {
        dprintf("serial::FAIL[%u,%u,%u]\n", checksum_computed, checksum_received, sstd_index);
        serial_output();
        serial_high();

        chSysUnlock();
        return TRANSACTION_DATA_ERROR;
    }

    // always, release the line when not in use
    serial_high();
    serial_output();

    chSysUnlock();
    return TRANSACTION_END;
}
