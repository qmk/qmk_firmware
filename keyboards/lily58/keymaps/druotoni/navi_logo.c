#include QMK_KEYBOARD_H
#include "gui_state.h"

#include "navi_logo.h"
#include "fast_random.h"
#include "draw_helper.h"

uint8_t  current_glitch_index = 0;
int      current_glitch_time  = 150;
uint32_t glitch_timer         = 0;

static const char PROGMEM get_logo_array[] = {
    0, 0, 0, 0, 0, 0, 128, 128, 0, 0, 128, 128, 192, 192, 204, 222, 222, 204, 192, 192, 128, 0, 0, 0, 128, 128, 0, 0, 0, 0, 0, 0, 192, 240, 248, 28, 14, 7, 3, 249, 252, 255, 15, 7, 3, 225, 241, 241, 241, 241, 225, 3, 7, 15, 255, 252, 249, 3, 7, 14, 28, 248, 240, 192, 192, 227, 231, 206, 28, 56, 112, 99, 15, 31, 60, 120, 240, 225, 227, 3, 3, 227, 225, 240, 120, 60, 31, 15, 103, 112, 56, 28, 206, 231, 227, 192, 0, 1, 1, 0, 0, 0, 56, 120, 96, 192, 192, 192, 96, 127, 63, 0, 0, 63, 127, 96, 192, 192, 192, 96, 120, 56, 0, 0, 0, 1, 1, 0,
};

//  static const unsigned char  frameData[] = {187, 0x00, 0x06, 0x80, 0x02, 0x00, 0x02, 0x80, 0x02, 0xc0, 0x02, 0xcc, 0x01, 0xde, 0x02, 0xcc, 0x01, 0xc0, 0x02, 0x80, 0x01, 0x00, 0x03, 0x80, 0x02, 0x00, 0x06, 0xc0, 0x01, 0xf0, 0x01, 0xf8, 0x01, 0x1c, 0x01, 0x0e, 0x01, 0x07, 0x01, 0x03, 0x01, 0xf9, 0x01, 0xfc, 0x01, 0xff, 0x01, 0x0f, 0x01, 0x07, 0x01, 0x03, 0x01, 0xe1, 0x01, 0xf1, 0x04, 0xe1, 0x01, 0x03, 0x01, 0x07, 0x01, 0x0f, 0x01, 0xff, 0x01, 0xfc, 0x01, 0xf9, 0x01, 0x03, 0x01, 0x07, 0x01, 0x0e, 0x01, 0x1c, 0x01, 0xf8, 0x01, 0xf0, 0x01, 0xc0, 0x02, 0xe3, 0x01, 0xe7, 0x01, 0xce, 0x01, 0x1c, 0x01, 0x38, 0x01, 0x70, 0x01, 0x63, 0x01, 0x0f, 0x01, 0x1f, 0x01, 0x3c, 0x01, 0x78, 0x01, 0xf0, 0x01, 0xe1, 0x01, 0xe3, 0x01, 0x03, 0x02, 0xe3, 0x01, 0xe1, 0x01, 0xf0, 0x01, 0x78, 0x01, 0x3c, 0x01, 0x1f, 0x01, 0x0f, 0x01, 0x67, 0x01, 0x70, 0x01, 0x38, 0x01, 0x1c, 0x01, 0xce, 0x01, 0xe7, 0x01, 0xe3, 0x01, 0xc0, 0x01, 0x00, 0x01, 0x01, 0x02, 0x00, 0x03, 0x38, 0x01, 0x78, 0x01, 0x60, 0x01, 0xc0, 0x03,
//  0x60, 0x01, 0x7f, 0x01, 0x3f, 0x01, 0x00, 0x02, 0x3f, 0x01, 0x7f, 0x01, 0x60, 0x01, 0xc0, 0x03, 0x60, 0x01, 0x78, 0x01, 0x38, 0x01, 0x00, 0x03, 0x01, 0x02, 0x00, 0x01}

static void render_logo_clean(void) {
    // simple logo
    oled_write_raw_P(get_logo_array, sizeof(get_logo_array));
}

static void generer_glitch_bar(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t iProb, uint8_t iProbWhite) {
    for (uint8_t i = 0; i < height; i++) {
        bool bGenerateGlitch = (fastrand() % 100) < iProb;
        if (bGenerateGlitch) {
            bool bWhite = (fastrand() % 100) < iProbWhite;
            drawline_hr(x, y + i, width, bWhite);
        }
    }
}

// void generer_glitch_static_oblic(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, uint8_t iProb, uint8_t iProbWhite) {
//     for (int yCurrent = 0; yCurrent < heigth; yCurrent++) {
//         for (int xCurrent = 0; xCurrent < width; xCurrent++) {
//             // bool bGenerateGlitch = (rand() % 100) < iProb;
//             bool bGenerateGlitch = true;
//             if (bGenerateGlitch) {
//                 // bool bWhite = (rand() % 100) < iProbWhite;
//                 bool bWhite = (timer_read32() % 2) == 0;
//                 oled_write_pixel(x + xCurrent, y + yCurrent, bWhite);
//             }
//         }
//     }
// }

static void render_truc(uint8_t algo) {
    char c = 0;
    // size for
    int iSize = 1;

    // char c_other = 0;

    switch (algo) {
        case 7:
            // invert
            for (uint16_t i = 0; i < LOGO_SIZE; i++) {
                c = get_oled_char(i);
                // c = ~(c);

                oled_write_raw_byte(~(c), i);
            }

            break;
        case 8:

            //  wobble

            for (uint16_t i = 0; i < LOGO_SIZE; i++) {
                if (i < LOGO_SIZE - iSize) {
                    copy_pixel(i + iSize, iSize * -1, 85);

                    copy_pixel(LOGO_SIZE - 1 - iSize - i, iSize, 170);
                }
            }
            break;

        default:
            break;
    }
}

// static void render_logo_block(uint8_t glitch_index) {
//     switch (glitch_index) {
//         case 1:
//             move_block(1, 11, 24, 3, 5);
//             move_block(2, 19, 14, 3, 4);
//             move_block(9, 22, 7, 4, 4);
//             break;

//         case 3:
//             move_block(3, 7, 27, 4, -3);
//             move_block(13, 23, 19, 4, -4);
//             break;

//         case 2:
//             move_block(6, 25, 20, 7, 4);
//             move_block(0, 8, 32, 8, 7);
//             break;
//     }
// }

static void render_logo_glitch(void) {
    get_glitch_index(&glitch_timer, &current_glitch_time, &current_glitch_index, 0, 150, GLITCH_PROBALITY, GLITCH_FRAME_NUMBER);

    // if (timer_elapsed32(glitch_timer) > current_glitch_time) {
    //     glitch_timer = timer_read32();

    //     bool bGenerateGlitch = (fastrand() % 100) < GLITCH_PROBALITY;
    //     if (bGenerateGlitch) {
    //         current_glitch_index = fastrand() % GLITCH_FRAME_NUMBER;
    //     } else {
    //         // logo clean
    //         current_glitch_index = 10;
    //     }

    //     current_glitch_time = fastrand() % 150;
    // }

    if (current_glitch_index <= 3) {
        render_logo_clean();
        return;
    }

    switch (current_glitch_index) {
        case 4:
            move_block(1, 11, 24, 3, 5);
            move_block(2, 19, 14, 3, 4);
            move_block(9, 22, 7, 4, 4);
            return;

        case 5:
            move_block(6, 25, 20, 7, 4);
            move_block(0, 8, 32, 8, 7);
            return;
            
        case 6:
            move_block(3, 7, 27, 4, -3);
            move_block(13, 23, 19, 4, -4);
            return;

        case 7:
        case 8:
            render_truc(current_glitch_index);
            return;

        case 9:
            generer_glitch_bar(0, 0, 32, 32, 25, 100);
            return;

        case 10:
            draw_static(0, 0, 32, 32, true, 0);
            return;
    }
}

void render_logo(gui_state_t t) {
    if (t == _IDLE) {
        render_logo_glitch();
        return;
    }
    render_logo_clean();
}
