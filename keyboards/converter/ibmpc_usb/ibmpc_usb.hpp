#ifndef IBMPC_USB_HPP
#define IBMPC_USB_HPP

#include <avr/pgmspace.h>
#include "matrix.h"
#include "unimap_trans.h"
#include "ibmpc_usb.h"



#define ID_STR(id)  (id == 0xFFFE ? "_????" : \
                    (id == 0xFFFD ? "_Z150" : \
                    (id == 0x0000 ? "_AT84" : \
                     "")))

#define ROW(code)      ((code>>4)&0x07)
#define COL(code)      (code&0x0F)


class IBMPCConverter {
    public:
    static matrix_row_t matrix[MATRIX_ROWS];

    IBMPC &ibmpc;

    IBMPCConverter(IBMPC &_ibmpc) : ibmpc(_ibmpc), keyboard_id(0), keyboard_kind(NONE), current_protocol(0) {
        matrix_clear();
    }

    void init(void) {
        ibmpc.host_init();
    }

    uint8_t process_interface(void);

    void set_led(uint8_t usb_led);

    static inline void matrix_clear(void) {
        for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;
    }

    static inline matrix_row_t matrix_get_row(uint8_t row) {
        return matrix[row];
    }


    private:
    uint16_t keyboard_id = 0x0000;
    keyboard_kind_t keyboard_kind = NONE;
    uint8_t current_protocol = 0;
    uint16_t init_time;

    enum Converter_state {
        INIT,
        WAIT_SETTLE,
        AT_RESET,
        XT_RESET,
        XT_RESET_WAIT,
        XT_RESET_DONE,
        WAIT_AA,
        WAIT_AABF,
        WAIT_AABFBF,
        READ_ID,
        SETUP,
        LOOP,
        ERROR,
    } state = INIT;

    enum CS1_state {
        CS1_INIT,
        CS1_E0,
        // Pause: E1 1D 45, E1 9D C5 [a]
        CS1_E1,
        CS1_E1_1D,
        CS1_E1_9D,
    } state_cs1 = CS1_INIT;

    enum CS2_state {
        CS2_INIT,
        CS2_F0,
        CS2_E0,
        CS2_E0_F0,
        // Pause
        CS2_E1,
        CS2_E1_14,
        CS2_E1_F0,
        CS2_E1_F0_14,
        CS2_E1_F0_14_F0,
    } state_cs2 = CS2_INIT;

    enum CS3_state {
        CS3_READY,
        CS3_F0,
#ifdef G80_2551_SUPPORT
        // G80-2551 four extra keys around cursor keys
        CS3_G80,
        CS3_G80_F0,
#endif
    } state_cs3 = CS3_READY;

    int8_t process_cs1(uint8_t code);
    int8_t process_cs2(uint8_t code);
    int8_t process_cs3(uint8_t code);
    uint8_t cs1_e0code(uint8_t code);
    uint8_t cs2_e0code(uint8_t code);
    uint8_t translate_5576_cs2(uint8_t code);
    uint8_t translate_5576_cs2_e0(uint8_t code);
    uint8_t translate_5576_cs3(uint8_t code);

    int16_t read_wait(uint16_t wait_ms);
    uint16_t read_keyboard_id(void);

    // translate to Unimap before storing in matrix
    inline void matrix_make(uint8_t code) {
        uint8_t u = to_unimap(code);
        if (u > 0x7F) return;
        if (!matrix_is_on(ROW(u), COL(u))) {
            matrix[ROW(u)] |= 1<<COL(u);
        }
    }
    inline void matrix_break(uint8_t code) {
        uint8_t u = to_unimap(code);
        if (u > 0x7F) return;
        if (matrix_is_on(ROW(u), COL(u))) {
            matrix[ROW(u)] &= ~(1<<COL(u));
        }
    }
    uint8_t to_unimap(uint8_t code) {
        uint8_t row = ROW(code);
        uint8_t col = COL(code);
        switch (keyboard_kind) {
            case PC_XT:
                return pgm_read_byte(&unimap_cs1[row][col]);
            case PC_AT:
                return pgm_read_byte(&unimap_cs2[row][col]);
            case PC_TERMINAL:
                return pgm_read_byte(&unimap_cs3[row][col]);
            default:
                return UNIMAP_NO;
        }
    }

#ifdef IBMPC_MOUSE_ENABLE
    enum {
        MOUSE_DEFAULT  = 0, // Default three-button
        MOUSE_INTELLI  = 3, // Intellimouse Explorer 3-button & wheel
        MOUSE_EXPLORER = 4, // Intellimouse Explorer 5-button & wheel
        MOUSE_LOGITECH = 9  // Logitech PS/2++
    } mouse_id = MOUSE_DEFAULT;
    uint8_t mouse_btn = 0;

    void mouse_read_status(uint8_t *s) {
        ibmpc.host_send(0xE9);
        s[0] = ibmpc.host_recv_response();
        s[1] = ibmpc.host_recv_response();
        s[2] = ibmpc.host_recv_response();
        xprintf("S[%02X %02X %02X] ", s[0], s[1], s[2]);
    }
#endif
};

matrix_row_t IBMPCConverter::matrix[MATRIX_ROWS];

#endif
