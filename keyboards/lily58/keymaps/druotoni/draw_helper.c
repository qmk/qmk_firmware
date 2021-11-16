#include QMK_KEYBOARD_H

#include "draw_helper.h"
#include "fast_random.h"

//  //
//   // Easing Functions - inspired from http://gizma.com/easing/
//   // only considering the t value for the range [0, 1] => [0, 1]
//  //
// EasingFunctions = {
//   // no easing, no acceleration
//   linear: t => t,
//   // accelerating from zero velocity
//   easeInQuad: t => t*t,
//   // decelerating to zero velocity
//   easeOutQuad: t => t*(2-t),
//   // acceleration until halfway, then deceleration
//   easeInOutQuad: t => t<.5 ? 2*t*t : -1+(4-2*t)*t,
//   // accelerating from zero velocity
//   easeInCubic: t => t*t*t,
//   // decelerating to zero velocity
//   easeOutCubic: t => (--t)*t*t+1,
//   // acceleration until halfway, then deceleration
//   easeInOutCubic: t => t<.5 ? 4*t*t*t : (t-1)*(2*t-2)*(2*t-2)+1,
//   // accelerating from zero velocity
//   easeInQuart: t => t*t*t*t,
//   // decelerating to zero velocity
//   easeOutQuart: t => 1-(--t)*t*t*t,
//   // acceleration until halfway, then deceleration
//   easeInOutQuart: t => t<.5 ? 8*t*t*t*t : 1-8*(--t)*t*t*t,
//   // accelerating from zero velocity
//   easeInQuint: t => t*t*t*t*t,
//   // decelerating to zero velocity
//   easeOutQuint: t => 1+(--t)*t*t*t*t,
//   // acceleration until halfway, then deceleration
//   easeInOutQuint: t => t<.5 ? 16*t*t*t*t*t : 1+16*(--t)*t*t*t*t
// }


// void clip_value(long *value, int min, int max){
//   if (*value < min){
//       *value = min;
//       return;
//   } 

//     if (*value > max) *value = max;
// }


void drawline(uint8_t x, uint8_t y, uint8_t width, bool bHorizontal, bool bPositiveDirection, uint8_t color) {
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

    // if (width % 2 == 0) {
    //     // pair
    //     yMois  = (width / 2) - 1;
    //     yPlus  = (width / 2);
    //     nbtour = (width / 4) + 1;

    // } else {
    //     // impair
    //     yMois  = (width / 2);
    //     yPlus  = (width / 2);
    //     nbtour = (width / 4) + 1;
    // }


    if (width % 2 == 0) {
        // pair
        yMois  = (width / 2) - 1;
    } else {
        // impair
        yMois  = (width / 2);
    }

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

void drawline_vb(uint8_t x, uint8_t y, uint8_t width, uint8_t color) { drawline(x, y, width, false, true, color); }

void drawline_vt(uint8_t x, uint8_t y, uint8_t width, uint8_t color) { drawline(x, y, width, false, false, color); }

void drawline_hr(uint8_t x, uint8_t y, uint8_t width, uint8_t color) { drawline(x, y, width, true, true, color); }

void drawline_hl(uint8_t x, uint8_t y, uint8_t width, uint8_t color) { drawline(x, y, width, true, false, color); }

void draw_rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, uint8_t color) {
    drawline_hr(x, y, width, color);
    drawline_hr(x, y + heigth - 1, width, color);
    drawline_vb(x, y, heigth, color);
    drawline_vb(x + width - 1, y, heigth, color);
}

void draw_rectangle_fill(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, uint8_t color) {
    for (uint8_t i = 0; i < heigth; i++) {
        drawline_hr(x, y + i, width, color);
    }
}

void drawline_hr_heigth(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, uint8_t color) {
    for (int i = 0; i < heigth; i++) {
        drawline_hr(x, y - i, width, color);
        drawline_hr(x, y + i, width, color);
    }
}

void drawline_point_hr(short x, short y, short x1, uint8_t color) {
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

void draw_circle(uint8_t x, uint8_t y, uint8_t radius, uint8_t color) {
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
    px = x + b;
    py = y;
    oled_write_pixel(px, py, color);
    px = x - b;
    py = y;
    oled_write_pixel(px, py, color);
    do {
        px = x + a;
        py = y + b;
        oled_write_pixel(px, py, color);
        px = x + a;
        py = y - b;
        oled_write_pixel(px, py, color);
        px = x + b;
        py = y + a;
        oled_write_pixel(px, py, color);
        px = x - b;
        py = y + a;
        oled_write_pixel(px, py, color);
        px = x - a;
        py = y + b;
        oled_write_pixel(px, py, color);
        px = x - a;
        py = y - b;
        oled_write_pixel(px, py, color);
        px = x + b;
        py = y - a;
        oled_write_pixel(px, py, color);
        px = x - b;
        py = y - a;
        oled_write_pixel(px, py, color);
        if (P < 0)
            P += 3 + 2 * a++;
        else
            P += 5 + 2 * (a++ - b--);
    } while (a < b);
    px = x + a;
    py = y + b;
    oled_write_pixel(px, py, color);
    px = x + a;
    py = y - b;
    oled_write_pixel(px, py, color);
    px = x - a;
    py = y + b;
    oled_write_pixel(px, py, color);
    px = x - a;
    py = y - b;
    oled_write_pixel(px, py, color);
}

void draw_ellipse(uint8_t x, uint8_t y, uint8_t a, uint8_t b, uint8_t color) {
    int dx, dy;
    int a2, b2;
    int err, e2;

    short py, px;
    // Calculate intermediates
    dx  = 0;
    dy  = b;
    a2  = a * a;
    b2  = b * b;
    err = b2 - (2 * b - 1) * a2;

    // Away we go using Bresenham's ellipse algorithm
    do {
        px = x + dx;
        py = y + dy;
        oled_write_pixel(px, py, color);
        px = x - dx;
        py = y + dy;
        oled_write_pixel(px, py, color);
        px = x - dx;
        py = y - dy;
        oled_write_pixel(px, py, color);
        px = x + dx;
        py = y - dy;
        oled_write_pixel(px, py, color);

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

void draw_ellipse_fill(uint8_t x, uint8_t y, uint8_t a, uint8_t b, uint8_t color) { return; }
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
void draw_fill_circle(short x, short y, uint8_t radius, uint8_t color) {
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
        py  = y + a;
        px  = x - b;
        px1 = x + b;
        drawline_point_hr(px, py, px1, color);
        py  = y - a;
        px  = x - b;
        px1 = x + b;
        drawline_point_hr(px, py, px1, color);
        if (P < 0) {
            P += 3 + 2 * a++;
        } else {
            py  = y + b;
            px  = x - a;
            px1 = x + a;
            drawline_point_hr(px, py, px1, color);
            py  = y - b;
            px  = x - a;
            px1 = x + a;
            drawline_point_hr(px, py, px1, color);
            P += 5 + 2 * (a++ - b--);
        }
    } while (a < b);
    py  = y + a;
    px  = x - b;
    px1 = x + b;
    drawline_point_hr(px, py, px1, color);
    py  = y - a;
    px  = x - b;
    px1 = x + b;
    drawline_point_hr(px, py, px1, color);
}

#if IS_RIGHT
bool apres_moitie(int a, int b) { return (a > b / 2); }
bool arrive_moitie(int a, int b) { return (a > b / 2); }
bool avant_moitie(int a, int b) { return (a <= b / 2 && !apres_moitie(a, b)); }

void draw_arc_sector(uint8_t x, uint8_t y, uint8_t radius, unsigned char sectors, unsigned char half, int color) {
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

#endif
void draw_static(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, int color, uint8_t density) {
    unsigned long rx        = fastrand_long();
    unsigned long ry        = fastrand_long();
    unsigned long maskx     = 1;
    unsigned long masky     = 1;
    unsigned long mask_base = 1;

    for (int r = 0; r < density; r++) {
        rx &= fastrand_long();
        ry &= fastrand_long();
    }

    color = ((rx >> 1) % 2) == 0;

    for (uint8_t i = 0; i < width; i++) {
        for (uint8_t j = 0; j < heigth; j++) {
            maskx = (mask_base << i);
            masky = (mask_base << j);

            if (((rx & maskx) == maskx) && ((ry & masky) == masky)) {
                oled_write_pixel(x + i, y + j, color);
            }
        }
    }
}



 void copy_pixel(int from, int shift, unsigned char mask) {

    if(shift == 0) return;

    char c_from  = get_oled_char(from);
    char extract = c_from & mask;

    char c_from_shift = get_oled_char(from + shift);
    c_from_shift &= ~(mask);
    c_from_shift |= extract;
    oled_write_raw_byte(c_from_shift, from + shift);

    // fill blank with black
    c_from &= ~(mask);
    oled_write_raw_byte(c_from, from);
}



void draw_glitch_comb(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t iSize, bool odd) {
   // char c = 0;
    // size for
    // int iSize = 1;

    uint8_t y_start = (y / 8) * 32;
    uint8_t nb_h    = height / 8;

    uint8_t  w_max = width;  // 32
    uint16_t index = y_start + x;

 //  char c_other = 0;

    int mask_1 = 85;
    int mask_2 = 170;

    if (!odd) {
        mask_1 = 170;
        mask_2 = 85;
    }

    //  wobble
    uint16_t pos = 0;
    for (uint16_t j = 0; j < nb_h; j++) {
        index += j * 32;

        for (uint16_t i = 0; i < w_max; i++) {
            if (i + iSize < w_max) {
                pos = index + i;

                copy_pixel(pos + iSize, iSize * -1, mask_1);
                // c   = get_oled_char(pos + iSize);
                // c   = c & mask_1;

                // c_other = get_oled_char(pos);
                // c_other &= ~(mask_1);
                // c_other = c_other | c;
                // oled_write_raw_byte(c_other, pos);
            }

            if (w_max - 1 - i - iSize >= 0) {
                pos = (index + w_max - 1) - i;

 copy_pixel(pos - iSize, iSize , mask_2);
                // c = get_oled_char(pos - iSize);
                // c = c & mask_2;

                // c_other = get_oled_char(pos);
                // c_other &= ~(mask_2);
                // c_other = c_other | c;

                // oled_write_raw_byte(c_other, pos);
            }
        }
    }
}

void draw_random_char(uint8_t column, uint8_t row, char final_char, int value, uint8_t style) {
    if (value < 0) return;

    if (value >= 100) {
        oled_set_cursor(column, row);
        oled_write_char(final_char, false);
        return;
    }

    int  r = fastrand();
    char c = ((r % 15) + 1);
    oled_set_cursor(column, row);
    oled_write_char(c, false);
}

void draw_progress(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, int value, uint8_t style, uint8_t color) {
    int lenght = (width * value) / 100;
    for (uint8_t i = 0; i < lenght; i++) {
        switch (style) {
            case 0:
                drawline_vb(x + i, y, heigth - 1, color);
                break;

            case 1:
                drawline_vb(x + i, y + 1, heigth - 3, ((i % 3) < 2));
                break;
            case 2:
                // . . . . .
                drawline_vb(x + i, y + 3, 2, ((i % 2) == 0));
                break;
        }
    }
}

void draw_label(const char *data, uint8_t len, uint8_t row, int value) {
    if (value < 0) return;
    if (row >= 16 || row < 0) return;

    oled_set_cursor(0, row);
    oled_write(data, false);
}

void draw_box(const char *data, uint8_t len, uint8_t row, long value, uint8_t style) {
    if (value < 0) return;
    if (row >= 16 || row < 0) return;

    oled_set_cursor(0, row);
    oled_write(data, false);

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


  

// void render_monochrome_ordered4x4() {
// 	reset_pixels();

// 	int bayer[] = { 1,  9,  3,  11,
// 					13, 5,  15, 7,
// 					4,  12, 2,  10,
// 					16, 8,  14, 6 };

// 	int i, x, y;
// 	RGB rgb;
// 	for (i = 0; i < imgw * imgh; i++) {
// 		x = i%imgw; y = i/imgw;
// 		rgb = getRGB(pixels, x, y);
// 		rgb = divRGB(rgb, 10);
// 		rgb = mulRGB(rgb, bayer[((y%4)*4) + (x%4)]);

// 		double lum = 0.2126*rgb.r + 0.7152*rgb.g + 0.0722*rgb.b;
// 		pixels[i] = (lum > 128) ? 0xffffffff : 0x00000000;
// 	}

// 	render();
// }

// static int interpo_couleur(int min, int max, int v) {
//     float x0 = min;
//     float x1 = max;
//     float y0 = 0;
//     float y1 = 255;
//     float xp = v;
//     float yp = y0 + ((y1 - y0) / (x1 - x0)) * (xp - x0);

//     return (int)yp;
// }

// unsigned int BAYER_PATTERN_4[4][4] = {{1, 9, 3, 11}, {13, 5, 15, 7}, {4, 12, 2, 10}, {16, 8, 14, 6}};

// void draw_gradient(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, uint8_t color_start, uint8_t color_end, uint8_t tres) {
//     for (uint8_t i = 0; i < width; i++) {
//         int   position = interpo_pourcent(0, width, i);
//         float color    = (1 * position) / 100.0;

//         for (uint8_t j = 0; j < heigth; j++) {
//             unsigned int m = BAYER_PATTERN_4[i % 4][j % 4];

//             bool  closestColor       = (color < 0.5) ? 0 : 1;
//             bool  secondClosestColor = 1 - closestColor;
//             float d                  = (m - 1) / 16.0;
//             float distance           = fabs(closestColor - color);

//             bool color_d = (distance < d) ? closestColor : secondClosestColor;
//             oled_write_pixel(x + i, y + j, color_d);
//         }
//     }
// }

uint8_t BAYER_PATTERN_4[4][4] = {{15, 135, 45, 165}, {195, 75, 225, 105}, {60, 180, 30, 150}, {240, 120, 210, 90}};

int interpo_pourcent(int min, int max, int v) {
    float x0 = min;
    float x1 = max;
    float y0 = 0;
    float y1 = 100;
    float xp = v;
    float yp = y0 + ((y1 - y0) / (x1 - x0)) * (xp - x0);

    return (int)yp;
}

void draw_gradient(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, uint8_t color_start, uint8_t color_end, uint8_t tres) {
    bool invert  = color_start > color_end;

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
        color       = ((int)(color / step))  * step_minus  ;
       // color       = color * step_minus;

        color = color_start + ((distance * color) / 100);

        for (uint8_t j = 0; j < heigth; j++) {
            uint8_t m = BAYER_PATTERN_4[i % 4][j % 4];
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
            oled_write_pixel(xCenter - 13, yCenter, true);
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
            oled_write_pixel(xCenter - 11, yCenter, true);
            oled_write_pixel(xCenter + 12, yCenter, true);
            oled_write_pixel(xCenter + 14, yCenter, true);
            break;

        case 9:
            // central line
            drawline_hr(xCenter, yCenter, 2, true);
            break;
    }
}



 void render_tv_animation_opti(uint8_t frame_number, uint8_t x, uint8_t y, uint8_t width, uint8_t heigth) {
    uint8_t xCenter = x + (width / 2);
    uint8_t yCenter = y + (heigth / 2);


if(frame_number <=  4 ){
   drawline_hr_heigth(x, yCenter, width, 17 - (5 * frame_number), true);

}

if(frame_number >=  6 && frame_number < 9){
 // cross
            drawline_hr(xCenter, yCenter + 1, 2, true);
            drawline_hr(xCenter, yCenter - 1, 2, true);

}


if(frame_number >=  5){


   // central line
  drawline_hr(xCenter - ((frame_number - 9) * 3), yCenter, 2 + ((frame_number - 9) * 3), true);
}

if(frame_number == 4 || frame_number == 5  ){
    draw_fill_circle(xCenter, yCenter, frame_number - 1, true);
}


    switch (frame_number) {
    
        // case 4:
        //   //  drawline_hr_heigth(x, yCenter, width, 2, true);
        //     draw_fill_circle(xCenter, yCenter, 3, true);
        //     break;

        // case 5:
        //     // central line
        //  //  drawline_hr(x, yCenter, width, true);
        //     draw_fill_circle(xCenter, yCenter, 2, true);
        //     break;

     //   case 6:
            

            // central line
        //    drawline_hr(x, yCenter, width, true);
       //     break;

        case 7:
          
            // central line
         //   drawline_hr(xCenter - 8, yCenter, 18, true);
            // static
            oled_write_pixel(xCenter - 13, yCenter, true);
            oled_write_pixel(xCenter + 12, yCenter, true);
            break;

        case 8:
         
            // central line
          //  drawline_hr(xCenter - 2, yCenter, 4, true);
            // static
            drawline_hr(xCenter - 7, yCenter, 2, true);
            drawline_hr(xCenter + 6, yCenter, 3, true);

          //  oled_write_pixel(xCenter - 11, yCenter, true);
            oled_write_pixel(xCenter - 11, yCenter, true);
            oled_write_pixel(xCenter + 12, yCenter, true);
            oled_write_pixel(xCenter + 14, yCenter, true);
            break;

    //    case 9:
            // central line
          //  drawline_hr(xCenter, yCenter, 2, true);
        //    break;
    }
}


// in float color;
// out vec4 frag_color;

// const int indexMatrix4x4[16] = int[](0,  8,  2,  10,
//                                      12, 4,  14, 6,
//                                      3,  11, 1,  9,
//                                      15, 7,  13, 5);

// float indexValue() {
//     int x = int(mod(gl_FragCoord.x, 4));
//     int y = int(mod(gl_FragCoord.y, 4));
//     return indexMatrix4x4[(x + y * 4)] / 16.0;
// }

// float dither(float color) {
//     float closestColor = (color < 0.5) ? 0 : 1;
//     float secondClosestColor = 1 - closestColor;
//     float d = indexValue();
//     float distance = abs(closestColor - color);
//     return (distance < d) ? closestColor : secondClosestColor;
// }

// void main () {
//     fragColor = vec4(vec3(dither(color)), 1);
// }

// void    makeDitherBayer16( BYTE* pixels, int width, int height )
// {
//     int    col    = 0;
//     int    row    = 0;

//     for( int y = 0; y < height; y++ )
//     {
//         row    = y & 15;    //    y % 16

//         for( int x = 0; x < width; x++ )
//         {
//             col    = x & 15;    //    x % 16

//             const pixel blue    = pixels[x * 3 + 0];
//             const pixel green   = pixels[x * 3 + 1];
//             const pixel red     = pixels[x * 3 + 2];

//             pixel color  = ((red + green + blue)/3 < BAYER_PATTERN_4[col][row] ? 0 : 255);

//             pixels[x * 3 + 0]    = color;    //    blue
//             pixels[x * 3 + 1]    = color;    //    green
//             pixels[x * 3 + 2]    = color;    //    red
//         }

//         pixels += width * 3;
//     }
// }

// void draw_dither(uint8_t x, uint8_t y, uint8_t d)
// {
// // 4x4
// switch (d)
// {
// case 0:
//     // noir
//     draw_rectangle_fill(x, y, 4, 4, false);
//     break;

//     case 1:
//     // noir
//       oled_write_pixel(x, y, true);
//        oled_write_pixel(x + 2, y +2, true);
//     break;

//         case 2:
//     // noir
//       oled_write_pixel(x, y + 2, true);
//        oled_write_pixel(x + 2, y, true);
//     break;

//         case 3:
//     // noir
//       oled_write_pixel(x + 1, y + 1, true);
//        oled_write_pixel(x + 3, y + 3, true);
//     break;

//         case 4:
//     // noir
//       oled_write_pixel(x + 3, y + 1, true);
//        oled_write_pixel(x + 1, y + 3, true);
//     break;

// default:
//     break;
// }

// }

// 	void draw_arc_sector( uint8_t x, uint8_t y, uint8_t radius, unsigned char sectors, int color) {

//  short a, b, P;
//     short py, px;
// 		// Calculate intermediates
// 		a = 1;              // x in many explanations
// 		b = radius;         // y in many explanations
// 		P = 4 - radius;

// 		// Away we go using Bresenham's circle algorithm
// 		// Optimized to prevent double drawing
// 		if (sectors & 0x06) {px = x; py = y - b; oled_write_pixel(px, py, color); }				// Upper upper
// 		if (sectors & 0x60) {px = x; py = y + b; oled_write_pixel(px, py, color); }				// Lower lower
// 		if (sectors & 0x81) {px = x + b; py = y; oled_write_pixel(px, py, color); }				// Right right
// 		if (sectors & 0x18) {px = x - b; py = y; oled_write_pixel(px, py, color); }				// Left left

// 		do {
// 			if (sectors & 0x01) {px = x + b; py = y - a; oled_write_pixel(px, py, color); }		// Upper right right
// 			if (sectors & 0x02) {px = x + a; py = y - b; oled_write_pixel(px, py, color); }		// Upper upper right
// 			if (sectors & 0x04) {px = x - a; py = y - b; oled_write_pixel(px, py, color); }		// Upper upper left
// 			if (sectors & 0x08) {px = x - b; py = y - a; oled_write_pixel(px, py, color); }		// Upper left  left
// 			if (sectors & 0x10) {px = x - b; py = y + a; oled_write_pixel(px, py, color); }		// Lower left  left
// 			if (sectors & 0x20) {px = x - a; py = y + b; oled_write_pixel(px, py, color); }		// Lower lower left
// 			if (sectors & 0x40) {px = x + a; py = y + b; oled_write_pixel(px, py, color); }		// Lower lower right
// 			if (sectors & 0x80) {px = x + b; py = y + a; oled_write_pixel(px, py, color); }		// Lower right right
// 			if (P < 0)
// 				P += 3 + 2*a++;
// 			else
// 				P += 5 + 2*(a++ - b--);
// 		} while(a < b);

// 		if (sectors & 0xC0) {px = x + a; py = y + b; oled_write_pixel(px, py, color); }			// Lower right
// 		if (sectors & 0x03) {px = x + a; py = y - b; oled_write_pixel(px, py, color); }			// Upper right
// 		if (sectors & 0x30) {px = x - a; py = y + b; oled_write_pixel(px, py, color); }			// Lower left
// 		if (sectors & 0x0C) {px = x - a; py = y - b; oled_write_pixel(px, py, color); }			// Upper left

// 	}

/*

        void draw_arc(uint8_t x, uint8_t y, uint8_t radius, uint8_t start, uint8_t end, int color) {
        uint8_t a, b, P, sedge, eedge;
        unsigned char	full, sbit, ebit, tbit;

short py, px;

        // Normalize the angles
        if (start < 0)
            start -= (start/360-1)*360;
        else if (start >= 360)
            start %= 360;
        if (end < 0)
            end -= (end/360-1)*360;
        else if (end >= 360)
            end %= 360;

        sbit = 1<<(start/45);
        ebit = 1<<(end/45);
        full = 0;
        if (start == end) {
            full = 0xFF;
        } else if (end < start) {
            for(tbit=sbit<<1; tbit; tbit<<=1) full |= tbit;
            for(tbit=ebit>>1; tbit; tbit>>=1) full |= tbit;
        } else if (sbit < 0x80) {
            for(tbit=sbit<<1; tbit < ebit; tbit<<=1) full |= tbit;
        }
        tbit = start%45 == 0 ? sbit : 0;



        if (full) {
            // Draw full sectors
            // Optimized to prevent double drawing
            a = 1;
            b = radius;
            P = 4 - radius;
            if (full & 0x60) { py = y+b; px = x; oled_write_pixel(px, py, color); }
            if (full & 0x06) { py = y-b; px = x; oled_write_pixel(px, py, color); }
            if (full & 0x81) { py = y; px = x+b; oled_write_pixel(px, py, color); }
            if (full & 0x18) { py = y; px = x-b; oled_write_pixel(px, py, color); }
            do {
                if (full & 0x01) { px = x+b; py = y-a; oled_write_pixel(px, py, color); }
                if (full & 0x02) { px = x+a; py = y-b; oled_write_pixel(px, py, color); }
                if (full & 0x04) { px = x-a; py = y-b; oled_write_pixel(px, py, color); }
                if (full & 0x08) { px = x-b; py = y-a; oled_write_pixel(px, py, color); }
                if (full & 0x10) { px = x-b; py = y+a; oled_write_pixel(px, py, color); }
                if (full & 0x20) { px = x-a; py = y+b; oled_write_pixel(px, py, color); }
                if (full & 0x40) { px = x+a; py = y+b; oled_write_pixel(px, py, color); }
                if (full & 0x80) { px = x+b; py = y+a; oled_write_pixel(px, py, color); }
                if (P < 0)
                    P += 3 + 2*a++;
                else
                    P += 5 + 2*(a++ - b--);
            } while(a < b);
            if (full & 0xC0) { px = x+a; py = y+b; oled_write_pixel(px, py, color); }
            if (full & 0x0C) { px = x-a; py = y-b; oled_write_pixel(px, py, color); }
            if (full & 0x03) { px = x+a; py = y-b; oled_write_pixel(px, py, color); }
            if (full & 0x30) { px = x-a; py = y+b; oled_write_pixel(px, py, color); }
            if (full == 0xFF) {

                return;
            }
        }

            sedge = floor(radius * ((sbit & 0x99) ? sin(start*GFX_PI/180) : cos(start*GFX_PI/180)) + 0.5);
            eedge = floor(radius * ((ebit & 0x99) ? sin(end*GFX_PI/180) : cos(end*GFX_PI/180)) + 0.5);

        if (sbit & 0xB4) sedge = -sedge;
        if (ebit & 0xB4) eedge = -eedge;

        if (sbit != ebit) {
            // Draw start and end sectors
            // Optimized to prevent double drawing
            a = 1;
            b = radius;
            P = 4 - radius;
            if ((sbit & 0x20) || (tbit & 0x40) || (ebit & 0x40)) { px = x; py = y+b; oled_write_pixel(px, py, color); }
            if ((sbit & 0x02) || (tbit & 0x04) || (ebit & 0x04)) { px = x; py = y-b; oled_write_pixel(px, py, color); }
            if ((sbit & 0x80) || (tbit & 0x01) || (ebit & 0x01)) { px = x+b; py = y; oled_write_pixel(px, py, color); }
            if ((sbit & 0x08) || (tbit & 0x10) || (ebit & 0x10)) { px = x-b; py = y; oled_write_pixel(px, py, color); }
            do {
                if (((sbit & 0x01) && a >= sedge) || ((ebit & 0x01) && a <= eedge)) { px = x+b; py = y-a; oled_write_pixel(px, py, color); }
                if (((sbit & 0x02) && a <= sedge) || ((ebit & 0x02) && a >= eedge)) { px = x+a; py = y-b; oled_write_pixel(px, py, color); }
                if (((sbit & 0x04) && a >= sedge) || ((ebit & 0x04) && a <= eedge)) { px = x-a; py = y-b; oled_write_pixel(px, py, color); }
                if (((sbit & 0x08) && a <= sedge) || ((ebit & 0x08) && a >= eedge)) { px = x-b; py = y-a; oled_write_pixel(px, py, color); }
                if (((sbit & 0x10) && a >= sedge) || ((ebit & 0x10) && a <= eedge)) { px = x-b; py = y+a; oled_write_pixel(px, py, color); }
                if (((sbit & 0x20) && a <= sedge) || ((ebit & 0x20) && a >= eedge)) { px = x-a; py = y+b; oled_write_pixel(px, py, color); }
                if (((sbit & 0x40) && a >= sedge) || ((ebit & 0x40) && a <= eedge)) { px = x+a; py = y+b; oled_write_pixel(px, py, color); }
                if (((sbit & 0x80) && a <= sedge) || ((ebit & 0x80) && a >= eedge)) { px = x+b; py = y+a; oled_write_pixel(px, py, color); }
                if (P < 0)
                    P += 3 + 2*a++;
                else
                    P += 5 + 2*(a++ - b--);
            } while(a < b);
            if (((sbit & 0x40) && a >= sedge) || ((ebit & 0x40) && a <= eedge) || ((sbit & 0x80) && a <= sedge) || ((ebit & 0x80) && a >= eedge))
                { px = x+a; py = y+b; oled_write_pixel(px, py, color); }
            if (((sbit & 0x04) && a >= sedge) || ((ebit & 0x04) && a <= eedge) || ((sbit & 0x08) && a <= sedge) || ((ebit & 0x08) && a >= eedge))
                { px = x-a; py = y-b; oled_write_pixel(px, py, color); }
            if (((sbit & 0x01) && a >= sedge) || ((ebit & 0x01) && a <= eedge) || ((sbit & 0x02) && a <= sedge) || ((ebit & 0x02) && a >= eedge))
                { px = x+a; py = y-b; oled_write_pixel(px, py, color); }
            if (((sbit & 0x10) && a >= sedge) || ((ebit & 0x10) && a <= eedge) || ((sbit & 0x20) && a <= sedge) || ((ebit & 0x20) && a >= eedge))
                { px = x-a; py = y+b; oled_write_pixel(px, py, color); }
        } else if (end < start) {
            // Draw start/end sector where it is a non-internal angle
            // Optimized to prevent double drawing
            a = 1;
            b = radius;
            P = 4 - radius;
            if ((sbit & 0x60) || (tbit & 0xC0)) { px = x; py = y+b; oled_write_pixel(px, py, color); }
            if ((sbit & 0x06) || (tbit & 0x0C)) { px = x; py = y-b; oled_write_pixel(px, py, color); }
            if ((sbit & 0x81) || (tbit & 0x03)) { px = x+b; py = y; oled_write_pixel(px, py, color); }
            if ((sbit & 0x18) || (tbit & 0x30)) { px = x-b; py = y; oled_write_pixel(px, py, color); }
            do {
                if ((sbit & 0x01) && (a >= sedge || a <= eedge)) { px = x+b; py = y-a; oled_write_pixel(px, py, color); }
                if ((sbit & 0x02) && (a <= sedge || a >= eedge)) { px = x+a; py = y-b; oled_write_pixel(px, py, color); }
                if ((sbit & 0x04) && (a >= sedge || a <= eedge)) { px = x-a; py = y-b; oled_write_pixel(px, py, color); }
                if ((sbit & 0x08) && (a <= sedge || a >= eedge)) { px = x-b; py = y-a; oled_write_pixel(px, py, color); }
                if ((sbit & 0x10) && (a >= sedge || a <= eedge)) { px = x-b; py = y+a; oled_write_pixel(px, py, color); }
                if ((sbit & 0x20) && (a <= sedge || a >= eedge)) { px = x-a; py = y+b; oled_write_pixel(px, py, color); }
                if ((sbit & 0x40) && (a >= sedge || a <= eedge)) { px = x+a; py = y+b; oled_write_pixel(px, py, color); }
                if ((sbit & 0x80) && (a <= sedge || a >= eedge)) { px = x+b; py = y+a; oled_write_pixel(px, py, color); }
                if (P < 0)
                    P += 3 + 2*a++;
                else
                    P += 5 + 2*(a++ - b--);
            } while(a < b);
            if (((sbit & 0x04) && (a >= sedge || a <= eedge)) || ((sbit & 0x08) && (a <= sedge || a >= eedge)))
                { px = x-a; py = y-b; oled_write_pixel(px, py, color); }
            if (((sbit & 0x40) && (a >= sedge || a <= eedge)) || ((sbit & 0x80) && (a <= sedge || a >= eedge)))
                { px = x+a; py = y+b; oled_write_pixel(px, py, color); }
            if (((sbit & 0x01) && (a >= sedge || a <= eedge)) || ((sbit & 0x02) && (a <= sedge || a >= eedge)))
                { px = x+a; py = y-b; oled_write_pixel(px, py, color); }
            if (((sbit & 0x10) && (a >= sedge || a <= eedge)) || ((sbit & 0x20) && (a <= sedge || a >= eedge)))
                { px = x-a; py = y+b; oled_write_pixel(px, py, color); }
        } else {
            // Draw start/end sector where it is a internal angle
            // Optimized to prevent double drawing
            a = 1;
            b = radius;
            P = 4 - radius;
            if (((sbit & 0x20) && !eedge) || ((sbit & 0x40) && !sedge)) { px = x; py = y+b; oled_write_pixel(px, py, color); }
            if (((sbit & 0x02) && !eedge) || ((sbit & 0x04) && !sedge)) { px = x; py = y-b; oled_write_pixel(px, py, color); }
            if (((sbit & 0x80) && !eedge) || ((sbit & 0x01) && !sedge)) { px = x+b; py = y; oled_write_pixel(px, py, color); }
            if (((sbit & 0x08) && !eedge) || ((sbit & 0x10) && !sedge)) { px = x-b; py = y; oled_write_pixel(px, py, color); }
            do {
                if (((sbit & 0x01) && a >= sedge && a <= eedge)) { px = x+b; py = y-a; oled_write_pixel(px, py, color); }
                if (((sbit & 0x02) && a <= sedge && a >= eedge)) { px = x+a; py = y-b; oled_write_pixel(px, py, color); }
                if (((sbit & 0x04) && a >= sedge && a <= eedge)) { px = x-a; py = y-b; oled_write_pixel(px, py, color); }
                if (((sbit & 0x08) && a <= sedge && a >= eedge)) { px = x-b; py = y-a; oled_write_pixel(px, py, color); }
                if (((sbit & 0x10) && a >= sedge && a <= eedge)) { px = x-b; py = y+a; oled_write_pixel(px, py, color); }
                if (((sbit & 0x20) && a <= sedge && a >= eedge)) { px = x-a; py = y+b; oled_write_pixel(px, py, color); }
                if (((sbit & 0x40) && a >= sedge && a <= eedge)) { px = x+a; py = y+b; oled_write_pixel(px, py, color); }
                if (((sbit & 0x80) && a <= sedge && a >= eedge)) { px = x+b; py = y+a; oled_write_pixel(px, py, color); }
                if (P < 0)
                    P += 3 + 2*a++;
                else
                    P += 5 + 2*(a++ - b--);
            } while(a < b);
            if (((sbit & 0x04) && a >= sedge && a <= eedge) || ((sbit & 0x08) && a <= sedge && a >= eedge))
                { px = x-a; py = y-b; oled_write_pixel(px, py, color); }
            if (((sbit & 0x40) && a >= sedge && a <= eedge) || ((sbit & 0x80) && a <= sedge && a >= eedge))
                { px = x+a; py = y+b; oled_write_pixel(px, py, color); }
            if (((sbit & 0x01) && a >= sedge && a <= eedge) || ((sbit & 0x02) && a <= sedge && a >= eedge))
                { px = x+a; py = y-b; oled_write_pixel(px, py, color); }
            if (((sbit & 0x10) && a >= sedge && a <= eedge) || ((sbit & 0x20) && a <= sedge && a >= eedge))
                { px = x-a; py = y+b; oled_write_pixel(px, py, color); }
        }

    }
*/

// void generatic_static(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, uint8_t spray) {
//     unsigned long randInt = 0;
//     bool          bWhite  = false;
//     for (int yCurrent = 0; yCurrent < heigth; yCurrent++) {
//         randInt = fastrand_long();

//         for (int xCurrent = 0; xCurrent < width; xCurrent++) {
//             bWhite = ((randInt >> xCurrent) & 1) && ((randInt >> xCurrent) % spray == 0);

//             oled_write_pixel(x + xCurrent, y + yCurrent, bWhite);
//         }
//     }
// }