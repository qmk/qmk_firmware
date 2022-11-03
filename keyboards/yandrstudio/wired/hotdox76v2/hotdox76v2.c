#include "hotdox76v2.h"
#include <string.h>
#include <transactions.h>
// #include "oled_font_lib/logo.h"
#include "oled_font_lib/logo2.h"
#include "oled_font_lib/ext_font.h"




bool is_keyboard_left(void) {

#ifdef I_AM_LEFT
    return true;
#else
    return false;
#endif

}


#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        { NO_LED, 34, 33, 32, 35, 37, 36     },
        { 27, 28, 29, 30, 31, NO_LED, NO_LED },
        { 26, 25, 24, 23, 22, 21, 20         },
        { 14, 15, 16, 17, 18, 19, NO_LED     },
        { 13, 12, 11, 10,  9,  8,  7         },
        {   0, 1,  2,   3, 4,  5,  6         },
        /*right*/
        { NO_LED, 72, 71, 70, 73, 75, 74     },
        { 65, 66, 67, 68, 69, NO_LED, NO_LED },
        { 64, 63, 62, 61, 60, 59, 58         },
        { 52, 53, 54, 55, 56, 57, NO_LED     },
        { 51, 50, 49, 48, 47, 46, 45         },
        { 38, 39, 40, 41, 42, 43, 44         }
    },
    {
        // LED Index to Physical Position
        {0,0},    {17,0},  {34,0},  {52,0},  {69,0},  {86,0},  {103,0}, \
        {103,13}, {86,13}, {69,13}, {52,13}, {34,13}, {17,13}, {0,13}, \
        {0,26},   {17,26}, {34,26}, {52,26}, {69,26}, {86,26}, \
        {103,38}, {86,38}, {69,38}, {52,38}, {34,38}, {17,38}, {0,38}, \
        {0,51},   {17,51}, {34,51}, {52,51}, {69,51},  \
                  {86,64}, {69,64}, {52,64}, {34,64}, {17,64}, {0,64}, \
                  {69,64}, {52,64}, {34,64}, {17,64}, {0,64}, \

                                                                                    \
        {224,0},  {207,0},  {190,0},  {172,0},  {155,0},  {138,0},  {121,0}, \
        {121,13}, {138,13}, {155,13}, {172,13}, {190,13}, {207,13}, {224,13}, \
        {224,26}, {207,26}, {190,26}, {172,26}, {155,26}, {138,26}, \
        {121,38}, {138,38}, {155,38}, {172,38}, {190,38}, {207,38}, {224,38}, \
        {224,51}, {207,51}, {190,51}, {172,51}, {155,51},  \
                  {138,64}, {155,64}, {172,64}, {190,64}, {207,64}, {224,64}, \
                  {155,64}, {172,64}, {190,64}, {207,64}, {224,64}\


    },
    {
      // LED Index to Flag
      4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,\
      2,2,2,2,2,\
      4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,\
      2,2,2,2,2
    }
};


#endif



#ifdef OLED_ENABLE

#   define UNC (94+0x21)
typedef struct _master_to_slave_t {
    int cur_alp_index;
    char current_alp[7];
} master_to_slave_t;
master_to_slave_t m2s;

typedef struct _slave_to_master_t {
    int cur_alp_index;
    char current_alp[7];
} slave_to_master_t;
slave_to_master_t s2m;

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    strcpy((char *)(m2s.current_alp), "[    ]");
    m2s.current_alp[1] = UNC;
    m2s.current_alp[2] = UNC;
    m2s.current_alp[3] = UNC;
    m2s.current_alp[4] = UNC;

    m2s.cur_alp_index = 1;

    strcpy((char *)(s2m.current_alp), "[    ]");
    s2m.current_alp[1] = UNC;
    s2m.current_alp[2] = UNC;
    s2m.current_alp[3] = UNC;
    s2m.current_alp[4] = UNC;

    s2m.cur_alp_index = 1;

#   ifdef I_AM_LEFT
        return OLED_ROTATION_180;
#   else
        return OLED_ROTATION_0;
#   endif
}


void render_logo(void) {
    uint8_t i = 0, j = 0;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 32; ++j) {
#   ifdef I_AM_LEFT
            oled_write_raw_byte(pgm_read_byte(&logo_mouse[i*32+j]), i*128+j);
#   else
            oled_write_raw_byte(pgm_read_byte(&logo_mouse[i*32+j]), i*128+j+96);
#   endif
        }
    }
}

#   ifdef I_AM_LEFT
void render_layer_helper_fun(uint8_t start_line, const char * data, uint8_t gap_w, uint8_t l) {
    uint8_t j = 0, k = 0;
    for (j = 0; j < l; ++j) { // font index
        for (k = 0; k < 12; ++k) { // font byte index
            //                                        base + logo_w(32) + gap_w(12) +l*font_w(12)+current_byte_index
            oled_write_raw_byte(pgm_read_byte(&ext_big_font[pgm_read_byte(&data[j])-0x21][k]), start_line*2*128 + 32 + gap_w + j*12+k);
            oled_write_raw_byte(pgm_read_byte(&ext_big_font[pgm_read_byte(&data[j])-0x21][k+12]), start_line*2*128+128 + 32 + gap_w + j*12+k);
        }
    }
    for (j = 0; j < gap_w; ++j) {
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line*2*128 + 32 + j);
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line*2*128 + 32 + gap_w + l*12 + j);

        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line*2*128+128 + 32 + j);
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line*2*128+128 + 32 + gap_w + l*12 + j);

    }
}
void render_layer(uint8_t layer) {
    render_layer_helper_fun(0, PSTR("LAYER:"), 12, 6);
    switch (layer) {
    case 0:
        render_layer_helper_fun(1, PSTR("1:HOME"), 12, 6);
        break;
    case 1:
        render_layer_helper_fun(1, PSTR("2:CODE"), 12, 6);
        break;
    case 2:
        render_layer_helper_fun(1, PSTR("3:OFFICE"), 0, 8);
        break;
    case 3:
    default:
        render_layer_helper_fun(1, PSTR("4:OTHERS"), 0, 8);
        break;
    }
}

# endif

#   ifndef I_AM_LEFT

void render_cur_input_helper_fun(uint8_t start_line, const char * data, uint8_t gap_w, uint8_t l) {
    uint8_t j = 0, k = 0;
    for (j = 0; j < l; ++j) { // font index
        for (k = 0; k < 12; ++k) { // font byte index
            //                                        base + logo_w(0) + gap_w(12) +l*font_w(12)+current_byte_index
            oled_write_raw_byte(pgm_read_byte(&ext_big_font[data[j]-0x21][k]), start_line*2*128 + gap_w + j*12+k);
            oled_write_raw_byte(pgm_read_byte(&ext_big_font[data[j]-0x21][12+k]), start_line*2*128+128 + gap_w + j*12+k);
        }
    }
    for (j = 0; j < gap_w; ++j) {
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line*2*128 + j);
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line*2*128 + gap_w + l*12 + j);

        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line*2*128+128 + j);
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line*2*128+128 + gap_w + l*12 + j);
    }
}

void render_cur_input(void) {
    render_cur_input_helper_fun(0, "INPUTS:", 6, 7);
    if (is_keyboard_master()) {
        render_cur_input_helper_fun(1, (const char *)(m2s.current_alp), 12, 6);
    } else {
        render_cur_input_helper_fun(1, (const char *)(s2m.current_alp), 12, 6);
    }
    return;
}
#endif


bool oled_task_kb(void) {
    render_logo();
#   ifdef I_AM_LEFT
    render_layer(biton32(layer_state));
#   else
    render_cur_input();
#   endif
    return false;
}



static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    UNC,        UNC,        UNC,        UNC,        'a',        'b',        'c',        'd',        'e',        'f',        'g',        'h',        'i',        'j',        'k',        'l',         // 0x
    'm',        'n',        'o',        'p',        'q',        'r',        's',        't',        'u',        'v',        'w',        'x',        'y',        'z',        '1',        '2',         // 1x
    '3',        '4',        '5',        '6',        '7',        '8',        '9',        '0',        UNC,        UNC,        UNC,        UNC,        UNC,        '-',        '=',        '[',         // 2x
    ']',       '\\',        '#',        ';',       '\'',        '`',        ',',        '.',        '/',        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // 3x
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // 4x
    UNC,        UNC,        UNC,        UNC,        '/',        '*',        '-',        '+',        UNC,        '1',        '2',        '3',        '4',        '5',        '6',        '7',         // 5x
    '8',        '9',        '0',        '.',        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // 6x
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // 7x
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // 8x
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // 9x
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // Ax
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // Bx
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // Cx
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // Dx
    UNC,        UNC,        'A',        'W',        UNC,        'S',        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // Ex
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC        // Fx
};




void get_cur_alp_hook(uint16_t keycode) {
    if (keycode >= 0xF0) {
        keycode = 0xF0;
    }
    if (m2s.cur_alp_index < 4) {
        m2s.current_alp[m2s.cur_alp_index] = pgm_read_byte(&code_to_name[keycode]);
        if (m2s.cur_alp_index == 1) {
            m2s.current_alp[2] = m2s.current_alp[3] = m2s.current_alp[4]  = UNC;
        }
        m2s.cur_alp_index++;
    } else {
        for (uint8_t i = 2; i <= 4; ++i) {
            m2s.current_alp[i-1] = m2s.current_alp[i];
        }
        m2s.current_alp[m2s.cur_alp_index] = pgm_read_byte(&code_to_name[keycode]);
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        get_cur_alp_hook(keycode);
    }
    switch(keycode) {
        case TOG_OLED:
            if (record->event.pressed) {
                if (is_oled_on()) {
                    oled_off();
                } else {
                    oled_on();
                }
            }
            return false;
        default:
            return true;
    }
    return true;

}


void matrix_scan_kb(void) {
    if(!is_oled_on()) {
        m2s.cur_alp_index = 1;
    }
}



void user_sync_alpa_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const master_to_slave_t *m2s_p = (const master_to_slave_t*)in_data;
    s2m.cur_alp_index = m2s_p->cur_alp_index;
    for (size_t i = 0; i < 7; i++)
    {
        s2m.current_alp[i] = m2s_p->current_alp[i];
    }
}

void keyboard_post_init_kb(void) {
    transaction_register_rpc(KEYBOARD_CURRENT_ALPA_SYNC, user_sync_alpa_slave_handler);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 200ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 200) {
            if(transaction_rpc_exec(KEYBOARD_CURRENT_ALPA_SYNC, sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
                last_sync = timer_read32();
                dprint("Slave sync successed!\n");
            } else {
                dprint("Slave sync failed!\n");
            }
        }
    }
}


#endif



// void keyboard_post_init_kb(void) {
//     // eeconfig_init();
//     // Customise these values to desired behaviour
//     // debug_enable=true;
//     // debug_matrix=false;
//     // debug_keyboard=true;
//     //debug_mouse=true;
// }
