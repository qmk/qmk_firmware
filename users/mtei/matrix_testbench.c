//////////////// debug part for matrix_read_cols_on_row.c ////////////////
//#define DUMP_SCAN_DATA

#if defined(DEBUG_ON_TEST_BENCH) && defined(DEBUG_CONFIG)
#  define UPDATE_INTERVAL 4000

#ifndef CPP_EXPAND_TEST
#  include "timer.h"
#endif

#ifndef DEBUG_UART_LOG
#    define DEBUG_UART_LOG_INIT(x)
#    define DEBUG_UART_LOG(x)
#endif

#ifdef SPLIT_KEYBOARD
#    define ROWS_PER_HAND (MATRIX_ROWS / 2)
#else
#    define ROWS_PER_HAND (MATRIX_ROWS)
#endif

#define TX_LED_PORT D5  /* onboard TX LED */
#define RX_LED_PORT B0  /* onboard RX LED */

static bool show_input_port_list_done = false;

static void dump_pin_port_table(void) {
    uint8_t s;
    for(s = 0; s < NUM_SIDE; s++) {
        uprintf("PORT TABLE: number of input ports = %d\n",minfo[s].num_input_ports);
        for (uint8_t i = 0; i < MAX_NUM_INPUT_PORTS; i++) {
            uprintf("%d: port %X, mask 0x%X\n", i, minfo[s].iports[i].port, minfo[s].iports[i].mask);
        }
        uprintf("PIN TABLE: number of input pins = %d\n", minfo[s].num_input_pins);
        for (uint8_t i = 0; i < MAX_NUM_INPUT_PINS; i++) {
            //uprintf("%d: port_index %d, bit 0x%X\n", i, minfo[s].ipins[i].pindex, minfo[s].ipins[i].bit);
            uprintf("%d: port_index %d, smask,dmask %08b,%08b\n", i,
                    minfo[s].ipins[i].pindex, minfo[s].ipins[i].smask, minfo[s].ipins[i].dmask);
        }
    }
}

#define print_matrix_header() print("\nr/c 01234567\n")
#define print_matrix_row(row) print_bin_reverse8(matrix_get_row(row))

void test_scan(void) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    //DEBUG_PIN_ON();
    for (uint8_t current_row = 0; current_row < ROWS_PER_HAND; current_row++) {
        x_matrix_read_cols_on_row(curr_matrix, current_row);
    }
    //DEBUG_PIN_OFF();
#ifdef AVR_UART_TX
    DEBUG_PIN_ON();
    DEBUG_UART_LOG(curr_matrix[0]);
    DEBUG_UART_LOG(curr_matrix[1]);
    DEBUG_PIN_OFF(); // 2byte 送るのに、2μs程度
    for (uint8_t current_row = 2; current_row < ROWS_PER_HAND; current_row++) {
        DEBUG_PIN_ON(); // 以後、1byteごとに 10μs
        DEBUG_UART_LOG(curr_matrix[current_row]);
        DEBUG_PIN_OFF();
    }
#endif
#ifdef DUMP_SCAN_DATA
    print_matrix_header();
    for (uint8_t row = 0; row < ROWS_PER_HAND; row++) {
        print_hex8(row);
        print(": ");
        print_bin_reverse8(curr_matrix[row]);
        print("\n");
    }
#endif
}

// Helix connection
//                      ====
//              +-------====------+
// (debug print)| D3/TXO      RAW |
//   serial     | D2/RXI      GND |
//              | GND         RST |
//              | GND         Vcc |
//              | D1/SDA       F4 | Col0
//              | D0/SCL       F5 | Col1
//         Row0 | D4           F6 | Col2
//         Row1 | C6           F7 | Col3
//         Row2 | D7       SCK/B1 | Col4
//         Row3 | E6      MISO/B3 | Col5
//         Row4 | B4      MOSI/B2 | Col6
//    DEBUG_PIN | B5           B6 |
//              +-----------------+

void dump_ATmega32U4_gpio(void) {
#ifdef __AVR_ATmega32U4__
    uprintf("               DDR,      PORT,     PIN\n");
    // PORTB 0-7
    uprintf("%s: %08b, %08b, %08b\n", "PORTB 0-7    ",
            DDRx_ADDRESS(B0), PORTx_ADDRESS(B0), PINx_ADDRESS(B0));
    // PORTC 6,7
    uprintf("%s: %08b, %08b, %08b\n", "PORTC 6,7    ",
            DDRx_ADDRESS(C0), PORTx_ADDRESS(C0), PINx_ADDRESS(C0));
    // PORTD 0-7
    uprintf("%s: %08b, %08b, %08b\n", "PORTD 0-7    ",
            DDRx_ADDRESS(D0), PORTx_ADDRESS(D0), PINx_ADDRESS(D0));
    // PORTE 2, 6
    uprintf("%s: %08b, %08b, %08b\n", "PORTE 2,6    ",
            DDRx_ADDRESS(E0), PORTx_ADDRESS(E0), PINx_ADDRESS(E0));
    // PORTF 0,1,4,5,6,7
    uprintf("%s: %08b, %08b, %08b\n", "PORTF 0,1,4-7",
            DDRx_ADDRESS(F0), PORTx_ADDRESS(F0), PINx_ADDRESS(F0));
#endif
}

uint16_t disp_update_timeout = 0;
void housekeeping_task_user(void) {
    static int count = 0;
    //debug_enable = false;
    if (disp_update_timeout == 0) {
        DEBUG_PIN_INIT();
        DEBUG_PIN_OFF();
        disp_update_timeout = timer_read();
        x_matrix_init_pins();
        DEBUG_UART_LOG_INIT(0);
    }
    if ( timer_elapsed(disp_update_timeout) >= UPDATE_INTERVAL) {
        count ++;
        disp_update_timeout = timer_read();
        if (!show_input_port_list_done) {
            show_input_port_list_done = true;
            dump_pin_port_table();
            dump_ATmega32U4_gpio();
            //setPortBunchInput(minfo[0].iports[0].port, minfo[0].iports[0].mask);
            //setPortBunchInput(minfo[0].iports[1].port, minfo[0].iports[1].mask);
            //dump_ATmega32U4_gpio();
            x_matrix_init_pins();
            dump_ATmega32U4_gpio();
        }
        uprintf("scan %d\n",count);
        test_scan();
        //debug_enable = true;
    }
}
#endif // defined(DEBUG_ON_TEST_BENCH) && defined(DEBUG_CONFIG)
