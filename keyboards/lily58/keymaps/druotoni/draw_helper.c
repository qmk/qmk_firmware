// Copyright 2021 Nicolas Druoton (druotoni)
// Copyright 2021 ugfx
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "draw_helper.h"
#include "fast_random.h"

void drawline(uint8_t x, uint8_t y, uint8_t width, bool bHorizontal, bool bPositiveDirection, bool color) {
    if (width <= 0) return;
    uint8_t yPlus  = 0;
    uint8_t yMois  = 0;
    uint8_t nbtour = 0;

    if (!bPositiveDirection) {
        if (bHorizontal) {
            x -= width;
        } else {
            y -= width;
        }
    }

    yMois = (width / 2) - 1 + (width % 2);

    yPlus  = (width / 2);
    nbtour = (width / 4) + 1;

    bool bWhite = color;

    if (bHorizontal) {
        for (uint8_t i = 0; i < nbtour; i++) {
            oled_write_pixel(x + yPlus + i, y, bWhite);
            oled_write_pixel(x + yMois - i, y, bWhite);

            oled_write_pixel(x + i, y, bWhite);
            oled_write_pixel(x + width - 1 - i, y, bWhite);
        }
    } else {
        for (uint8_t i = 0; i < nbtour; i++) {
            oled_write_pixel(x, y + yPlus + i, bWhite);
            oled_write_pixel(x, y + yMois - i, bWhite);

            oled_write_pixel(x, y + i, bWhite);

            oled_write_pixel(x, y + width - 1 - i, bWhite);
        }
    }
}

void drawline_vb(uint8_t x, uint8_t y, uint8_t width, bool color) { drawline(x, y, width, false, true, color); }

void drawline_vt(uint8_t x, uint8_t y, uint8_t width, bool color) { drawline(x, y, width, false, false, color); }

void drawline_hr(uint8_t x, uint8_t y, uint8_t width, bool color) { drawline(x, y, width, true, true, color); }

void drawline_hl(uint8_t x, uint8_t y, uint8_t width, bool color) { drawline(x, y, width, true, false, color); }

void draw_rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, bool color) {
    drawline_hr(x, y, width, color);
    drawline_hr(x, y + heigth - 1, width, color);
    drawline_vb(x, y, heigth, color);
    drawline_vb(x + width - 1, y, heigth, color);
}

void draw_rectangle_fill(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, bool color) {
    for (uint8_t i = 0; i < heigth; i++) {
        drawline_hr(x, y + i, width, color);
    }
}

void drawline_hr_heigth(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, bool color) {
    for (int i = 0; i < heigth; i++) {
        drawline_hr(x, y - i, width, color);
        drawline_hr(x, y + i, width, color);
    }
}

void drawline_point_hr(short x, short y, short x1, bool color) {
    if (y < 0 || y > 127) return;

    if (x1 < x) {
        short iTemp = x;
        x           = x1;
        x1          = iTemp;
    }

    if (x1 > 31) x1 = 31;
    if (x < 0) x = 0;
    if (x > 31) x = 31;

    drawline(x, y, x1 - x, true, true, color);
}

void flip_flap_x(short px, short py, uint8_t val, bool color) {
    oled_write_pixel(px + val, py, color);
    oled_write_pixel(px - val, py, color);
}

void draw_circle(uint8_t x, uint8_t y, uint8_t radius, bool color) {
    short a, b, P;

    // Calculate intermediates
    a = 1;
    b = radius;
    P = 4 - radius;

    short py, px;

    // Away we go using Bresenham's circle algorithm
    // Optimized to prevent double drawing
    px = x;
    py = y + b;
    oled_write_pixel(px, py, color);
    px = x;
    py = y - b;
    oled_write_pixel(px, py, color);

    flip_flap_x(x, y, b, color);

    do {
        flip_flap_x(x, y + b, a, color);
        flip_flap_x(x, y - b, a, color);
        flip_flap_x(x, y + a, b, color);
        flip_flap_x(x, y - a, b, color);

        if (P < 0)
            P += 3 + 2 * a++;
        else
            P += 5 + 2 * (a++ - b--);
    } while (a < b);

    flip_flap_x(x, y + b, a, color);
    flip_flap_x(x, y - b, a, color);
}

void draw_ellipse(uint8_t x, uint8_t y, uint8_t a, uint8_t b, bool color) {
    int dx, dy;
    int a2, b2;
    int err, e2;

    //  short py, px;
    // Calculate intermediates
    dx  = 0;
    dy  = b;
    a2  = a * a;
    b2  = b * b;
    err = b2 - (2 * b - 1) * a2;

    // Away we go using Bresenham's ellipse algorithm
    do {
        flip_flap_x(x, y + dy, dx, color);
        flip_flap_x(x, y - dy, dx, color);

        e2 = 2 * err;
        if (e2 < (2 * dx + 1) * b2) {
            dx++;
            err += (2 * dx + 1) * b2;
        }
        if (e2 > -(2 * dy - 1) * a2) {
            dy--;
            err -= (2 * dy - 1) * a2;
        }
    } while (dy >= 0);
}

void draw_ellipse_fill(uint8_t x, uint8_t y, uint8_t a, uint8_t b, bool color) { return; }
// void draw_ellipse_fill(uint8_t x, uint8_t y, uint8_t a, uint8_t b, uint8_t color) {
//     int dx, dy;
//     int a2, b2;
//     int err, e2;

//     // Calculate intermediates
//     dx  = 0;
//     dy  = b;
//     a2  = a * a;
//     b2  = b * b;
//     err = b2 - (2 * b - 1) * a2;

//     short py, px, px1;

//     // Away we go using Bresenham's ellipse algorithm
//     // This is optimized to prevent overdrawing by drawing a line only when a y is about to change value
//     do {
//         e2 = 2 * err;
//         if (e2 < (2 * dx + 1) * b2) {
//             dx++;
//             err += (2 * dx + 1) * b2;
//         }
//         if (e2 > -(2 * dy - 1) * a2) {
//             py  = y + dy;
//             px  = x - dx;
//             px1 = x + dx;
//             drawline_point_hr(px, py, px1, color);
//             if (y) {
//                 py  = y - dy;
//                 px  = x - dx;
//                 px1 = x + dx;
//                 drawline_point_hr(px, py, px1, color);
//             }
//             dy--;
//             err -= (2 * dy - 1) * a2;
//         }
//     } while (dy >= 0);
// }

bool test_limit(short x, short y) { return !(y < 0 || y > 127 || x < 0 || x > 31); }

void flip_flap_y_point(short px, short py, short px1, uint8_t val, bool color) {
    // firmware size optimisation : one fonction for 2 lines of code
    drawline_point_hr(px, py + val, px1, color);
    drawline_point_hr(px, py - val, px1, color);
}

void draw_fill_circle(short x, short y, uint8_t radius, bool color) {
    short a, b, P;

    // Calculate intermediates
    a = 1;
    b = radius;
    P = 4 - radius;

    // Away we go using Bresenham's circle algorithm
    // This is optimized to prevent overdrawing by drawing a line only when a variable is about to change value
    short py, px, px1;

    py  = y;
    px  = x - b;
    px1 = x + b;
    drawline_point_hr(px, py, px1, color);

    py = y + b;
    px = x;
    if (test_limit(px, py)) oled_write_pixel(px, py, color);
    py = y - b;
    px = x;
    if (test_limit(px, py)) oled_write_pixel(px, py, color);
    do {
        flip_flap_y_point(x - b, y, x + b, a, color);

        if (P < 0) {
            P += 3 + 2 * a++;
        } else {
            flip_flap_y_point(x - a, y, x + a, b, color);

            P += 5 + 2 * (a++ - b--);
        }
    } while (a < b);

    flip_flap_y_point(x - b, y, x + b, a, color);
}

bool apres_moitie(int a, int b) { return (a > b / 2); }
bool arrive_moitie(int a, int b) { return (a > b / 2); }
bool avant_moitie(int a, int b) { return (a <= b / 2 && !apres_moitie(a, b)); }

void draw_arc_sector(uint8_t x, uint8_t y, uint8_t radius, unsigned char sectors, unsigned char half, bool color) {
    short a, b, P;
    short py, px;
    // Calculate intermediates
    a = 1;       // x in many explanations
    b = radius;  // y in many explanations
    P = 4 - radius;

    if (half != 2) {
        // Away we go using Bresenham's circle algorithm
        // Optimized to prevent double drawing
        if (sectors & 0x06) {
            px = x;
            py = y - b;
            oled_write_pixel(px, py, color);
        }  // Upper upper
        if (sectors & 0x60) {
            px = x;
            py = y + b;
            oled_write_pixel(px, py, color);
        }  // Lower lower
        if (sectors & 0x81) {
            px = x + b;
            py = y;
            oled_write_pixel(px, py, color);
        }  // Right right
        if (sectors & 0x18) {
            px = x - b;
            py = y;
            oled_write_pixel(px, py, color);
        }  // Left left
    }

    bool dessiner = false;

    do {
        if (half == 1 && arrive_moitie(a, b)) break;

        if (half == 2 && avant_moitie(a, b)) {
            dessiner = false;
        } else {
            dessiner = true;
        }

        if (dessiner) {
            if (sectors & 0x01) {
                px = x + b;
                py = y - a;
                oled_write_pixel(px, py, color);
            }  // Upper right right
            if (sectors & 0x02) {
                px = x + a;
                py = y - b;
                oled_write_pixel(px, py, color);
            }  // Upper upper right
            if (sectors & 0x04) {
                px = x - a;
                py = y - b;
                oled_write_pixel(px, py, color);
            }  // Upper upper left
            if (sectors & 0x08) {
                px = x - b;
                py = y - a;
                oled_write_pixel(px, py, color);
            }  // Upper left  left
            if (sectors & 0x10) {
                px = x - b;
                py = y + a;
                oled_write_pixel(px, py, color);
            }  // Lower left  left
            if (sectors & 0x20) {
                px = x - a;
                py = y + b;
                oled_write_pixel(px, py, color);
            }  // Lower lower left
            if (sectors & 0x40) {
                px = x + a;
                py = y + b;
                oled_write_pixel(px, py, color);
            }  // Lower lower right
            if (sectors & 0x80) {
                px = x + b;
                py = y + a;
                oled_write_pixel(px, py, color);
            }  // Lower right right
        }

        if (P < 0)
            P += 3 + 2 * a++;
        else
            P += 5 + 2 * (a++ - b--);
    } while (a < b);

    if (half != 1) {
        if (sectors & 0xC0) {
            px = x + a;
            py = y + b;
            oled_write_pixel(px, py, color);
        }  // Lower right
        if (sectors & 0x03) {
            px = x + a;
            py = y - b;
            oled_write_pixel(px, py, color);
        }  // Upper right
        if (sectors & 0x30) {
            px = x - a;
            py = y + b;
            oled_write_pixel(px, py, color);
        }  // Lower left
        if (sectors & 0x0C) {
            px = x - a;
            py = y - b;
            oled_write_pixel(px, py, color);
        }  // Upper left
    }
}

void draw_static(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, int color, uint8_t density) {
    unsigned long rx        = fastrand_long();
    unsigned long ry        = fastrand_long();
    unsigned long maskx     = 1;
    unsigned long masky     = 1;
    unsigned long mask_base = 1;

    // more 1 in the octet
    for (int r = 0; r < density; r++) {
        rx &= fastrand_long();
        ry &= fastrand_long();
    }

    color = ((rx >> 1) % 2) == 0;

    for (uint8_t i = 0; i < width; i++) {
        for (uint8_t j = 0; j < heigth; j++) {
            // new mask based on ij loop
            maskx = (mask_base << i);
            masky = (mask_base << j);

            // logic AND with the masks
            if (((rx & maskx) == maskx) && ((ry & masky) == masky)) {
                oled_write_pixel(x + i, y + j, color);
            }
        }
    }
}

void copy_pixel(int from, int shift, unsigned char mask) {
    if (shift == 0) return;

    // pixel cluster from
    char c_from  = get_oled_char(from);
    char extract = c_from & mask;

    // pixel cluster shift
    char c_from_shift = get_oled_char(from + shift);
    c_from_shift &= ~(mask);
    c_from_shift |= extract;
    oled_write_raw_byte(c_from_shift, from + shift);

    // fill blank with black
    c_from &= ~(mask);
    oled_write_raw_byte(c_from, from);
}

void draw_glitch_comb(uint8_t x, uint8_t y, uint8_t width, uint16_t height, uint8_t iSize, bool odd) {
    // work only on row
    uint16_t y_start = (y / 8) * 32;
    uint8_t  nb_h    = height / 8;

    uint8_t  w_max = width;
    uint16_t index = y_start + x;

    // shift pair even pixel
    int mask_1 = 85;
    int mask_2 = 170;

    if (!odd) {
        // shift odd pixel
        mask_1 = 170;
        mask_2 = 85;
    }

    //  wobble
    uint16_t pos = 0;
    for (uint16_t j = 0; j < nb_h; j++) {
        // next line
        index = (y_start + x) + (j * 32);

        for (uint16_t i = 0; i < w_max; i++) {
            if (i + iSize < w_max) {
                pos = index + i;
                copy_pixel(pos + iSize, iSize * -1, mask_1);
            }

            if (w_max - 1 - i - iSize >= 0) {
                pos = (index + w_max - 1) - i;
                copy_pixel(pos - iSize, iSize, mask_2);
            }
        }
    }
}

void draw_random_char(uint8_t column, uint8_t row, char final_char, int value, uint8_t style) {
    if (value < 0) return;

    char c = final_char;

    if (value < 100) {
        c = ((fastrand() % 15) + 1);
    }

    oled_set_cursor(column, row);
    oled_write_char(c, false);
}

void get_glitch_index_new(uint16_t *glitch_timer, uint8_t *current_glitch_scope_time, uint8_t *glitch_index, uint8_t min_time, uint16_t max_time, uint8_t glitch_probobility, uint8_t glitch_frame_number) {
    if (timer_elapsed(*glitch_timer) > *current_glitch_scope_time) {
        // end of the last glitch period
        *glitch_timer = timer_read();

        // new random glich period
        *current_glitch_scope_time = min_time + fastrand() % (max_time - min_time);

        bool bGenerateGlitch = (fastrand() % 100) < glitch_probobility;
        if (!bGenerateGlitch) {
            // no glitch
            *glitch_index = 0;
            return;
        }

        // get a new glitch index
        *glitch_index = fastrand() % glitch_frame_number;
    }
}

uint8_t get_glitch_frame_index(uint8_t glitch_probobility, uint8_t glitch_frame_number) {
    bool bGenerateGlitch = (fastrand() % 100) < glitch_probobility;
    if (!bGenerateGlitch) {
        // no glitch
        return 0;
    }

    // get a new glitch index
    return fastrand() % glitch_frame_number;
}

uint8_t get_glitch_duration(uint8_t min_time, uint16_t max_time) { return min_time + fastrand() % (max_time - min_time); }

void get_glitch_index(uint32_t *glitch_timer, int *current_glitch_scope_time, uint8_t *glitch_index, uint8_t min_time, uint16_t max_time, uint8_t glitch_probobility, uint8_t glitch_frame_number) {
    if (timer_elapsed32(*glitch_timer) > *current_glitch_scope_time) {
        // end of the last glitch period
        *glitch_timer = timer_read32();

        // new random glich period
        *current_glitch_scope_time = min_time + fastrand() % (max_time - min_time);

        bool bGenerateGlitch = (fastrand() % 100) < glitch_probobility;
        if (!bGenerateGlitch) {
            // no glitch
            *glitch_index = 0;
            return;
        }

        // get a new glitch index
        *glitch_index = fastrand() % glitch_frame_number;
    }
}

void draw_progress(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, int value, uint8_t style, bool color) {
    if (value > 100) {
        value = 100;
    }
    int lenght = (width * value) / 100;
    for (uint8_t i = 0; i < lenght; i++) {
        switch (style) {
            case 0:
                drawline_vb(x + i, y, heigth - 1, color);
                break;

                // case 1:
                //     drawline_vb(x + i, y + 1, heigth - 3, ((i % 3) < 2));
                //     break;
                // case 2:
                //     // . . . . .
                //     drawline_vb(x + i, y + 3, 2, ((i % 2) == 0));
                //     break;
        }
    }
}

void oled_write_raw_P_cursor(uint8_t col, uint8_t line, const char *data, uint16_t size) {
    // raw_P at cursor position
    oled_set_cursor(col, line);
    oled_write_raw_P(data, size);
}

void oled_write_cursor(uint8_t col, uint8_t line, const char *data, bool invert) {
    // write at cursor position
    oled_set_cursor(col, line);
    oled_write(data, invert);
}

void draw_label(const char *data, uint8_t len, uint8_t row, int value) {
    if (value < 0) return;
    if (row >= 16 || row < 0) return;
    oled_write_cursor(0, row, data, false);
}

void draw_box(const char *data, uint8_t len, uint8_t row, long value, uint8_t style) {
    if (value < 0) return;
    if (row >= 16 || row < 0) return;

    oled_write_cursor(0, row, data, false);

    uint8_t y = row * 8;

    uint8_t x = 6 * len;
    uint8_t w = 32 - x;

    if (value < 0) value = 0;
    if (value > 100) value = 100;
    draw_progress(x, y, w, 7, value, style, 1);
}

char get_oled_char(uint16_t start_index) {
    oled_buffer_reader_t reader;
    reader = oled_read_raw(start_index);
    return *reader.current_element;
}

static int get_index_first_block(uint8_t y) { return ((y / 8) * 32); }

void move_block(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, int shift) {
    // clip
    if (x >= 31) return;
    if (y >= 127) return;

    int max_screen = 32 - 1;
    if ((width + x) > max_screen + 1) width = max_screen + 1 - x;

    if (width <= 1) return;

    if ((heigth + y) > 127) heigth = 127 - y;
    if (heigth <= 1) return;

    // [-32 & +32]
    if (shift > max_screen) shift = max_screen;
    if (shift < -1 * max_screen) shift = -1 * max_screen;

    if ((width + x + shift) > max_screen) width = width - shift;

    int pixelTop    = 8 - (y % 8);
    int pixelBottom = (y + heigth) % 8;

    unsigned char cMastTop    = ~((unsigned)255 >> (pixelTop));
    unsigned char cMastBottom = ~((unsigned)255 << (pixelBottom));

    int indexFirstBloc     = get_index_first_block(y) + x;
    int indexFirstBlocFull = get_index_first_block(y + pixelTop) + x;
    int indexFirstBlocEnd  = get_index_first_block(y + heigth) + x;

    int nbBlockHeigth = (heigth - pixelTop - pixelBottom) / 8;

    if (nbBlockHeigth < 0) {
        // just single row
        nbBlockHeigth = 0;
        cMastBottom   = 0;
    }

    if (shift < 0) {
        for (uint16_t i = 0; i < width; i++) {
            copy_pixel(indexFirstBloc + i, shift, cMastTop);
            copy_pixel(indexFirstBlocEnd + i, shift, cMastBottom);

            for (uint16_t j = 0; j < nbBlockHeigth; j++) {
                copy_pixel(indexFirstBlocFull + i + (j * 32), shift, 255);
            }
        }

    } else {
        for (int i = width - 1; i >= 0; i--) {
            copy_pixel(indexFirstBloc + i, shift, cMastTop);
            copy_pixel(indexFirstBlocEnd + i, shift, cMastBottom);

            for (uint16_t j = 0; j < nbBlockHeigth; j++) {
                copy_pixel(indexFirstBlocFull + i + (j * 32), shift, 255);
            }
        }
    }
}

int interpo_pourcent(int min, int max, int v) {
    // interpolation
    float x0 = min;
    float x1 = max;
    float y0 = 0;
    float y1 = 100;
    float xp = v;
    float yp = y0 + ((y1 - y0) / (x1 - x0)) * (xp - x0);

    return (int)yp;
}

uint8_t BAYER_PATTERN_4[4][4] = {{15, 135, 45, 165}, {195, 75, 225, 105}, {60, 180, 30, 150}, {240, 120, 210, 90}};

void draw_gradient(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, uint8_t color_start, uint8_t color_end, uint8_t tres) {
    bool invert = color_start > color_end;

    if (invert) {
        color_start = 255 - color_start;
        color_end   = 255 - color_end;
    }

    int step       = (100 / tres);
    int step_minus = (100 / (tres - 1));
    int distance   = color_end - color_start;

    for (uint8_t i = 0; i < width; i++) {
        int position = interpo_pourcent(0, width, i);

        float color = position;
        color       = ((int)(color / step)) * step_minus;

        color = color_start + ((distance * color) / 100);

        for (uint8_t j = 0; j < heigth; j++) {
            uint8_t       m       = BAYER_PATTERN_4[i % 4][j % 4];
            unsigned char color_d = (color > m) ? !invert : invert;

            oled_write_pixel(x + i, y + j, color_d);
        }
    }
}

void render_tv_animation(uint8_t frame_number, uint8_t x, uint8_t y, uint8_t width, uint8_t heigth) {
    uint8_t xCenter = x + (width / 2);
    uint8_t yCenter = y + (heigth / 2);

    switch (frame_number) {
        case 0:
            // a fond : allume
            drawline_hr_heigth(x, yCenter, width, 17, true);
            break;

        case 1:
            drawline_hr_heigth(x, yCenter, width, 12, true);
            draw_ellipse_fill(xCenter, yCenter, 7, 15, true);
            break;

        case 2:
            drawline_hr_heigth(x, yCenter, width, 5, true);
            draw_ellipse_fill(xCenter, yCenter, 5, 8, true);
            break;

        case 3:
            drawline_hr_heigth(x, yCenter, width, 3, true);
            draw_ellipse_fill(xCenter, yCenter, 3, 4, true);
            break;

        case 4:
            drawline_hr_heigth(x, yCenter, width, 2, true);
            draw_fill_circle(xCenter, yCenter, 3, true);
            break;

        case 5:
            // central line
            drawline_hr(x, yCenter, width, true);
            draw_fill_circle(xCenter, yCenter, 2, true);
            break;

        case 6:
            // cross
            drawline_hr(xCenter, yCenter + 1, 2, true);
            drawline_hr(xCenter, yCenter - 1, 2, true);

            // central line
            drawline_hr(x, yCenter, width, true);
            break;

        case 7:
            // cross
            drawline_hr(xCenter, yCenter + 1, 2, true);
            drawline_hr(xCenter, yCenter - 1, 2, true);
            // central line
            drawline_hr(xCenter - 8, yCenter, 18, true);
            // static
            oled_write_pixel(xCenter - 11, yCenter, true);
            oled_write_pixel(xCenter + 12, yCenter, true);
            break;

        case 8:
            // cross
            drawline_hr(xCenter, yCenter + 1, 2, true);
            drawline_hr(xCenter, yCenter - 1, 2, true);
            // central line
            drawline_hr(xCenter - 2, yCenter, 4, true);
            // static
            drawline_hr(xCenter - 7, yCenter, 2, true);
            drawline_hr(xCenter + 6, yCenter, 3, true);

            //  oled_write_pixel(xCenter - 11, yCenter, true);
            oled_write_pixel(xCenter - 9, yCenter, true);
            oled_write_pixel(xCenter + 12, yCenter, true);
            oled_write_pixel(xCenter + 14, yCenter, true);
            break;

        case 9:
            // central line
            drawline_hr(xCenter, yCenter, 2, true);
            break;
    }
}