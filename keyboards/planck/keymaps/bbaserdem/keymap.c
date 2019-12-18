/*
 * Most of the code is in the "user" directory.
 * Check qmk_firmware/users/bbaserdem for the main part of the code
 */

#include "planck.h"
#include "bbaserdem.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main layer
    [_BA] = LAYOUT_planck_wrapper(BASE),
    // Gaming layer
    [_GA] = LAYOUT_planck_wrapper(GAME),
    // Numbers layer
    [_NU] = LAYOUT_planck_wrapper(NUMBERS),
    // Settings layer
    [_SE] = LAYOUT_planck_wrapper(SETTINGS),
    // Mouse emulation layer
    [_MO] = LAYOUT_planck_wrapper(MOUSE),
    // Music mode
    [_MU] = LAYOUT_planck_wrapper(MUSIC),
};

#ifdef RGB_MATRIX_ENABLE
// Planck specific per-key lighting options

// GAME: Arrow keys and WASD cluster as purple
void rgb_matrix_game(void) {
    // First color is purple (HSV 285,255,255)
    uint8_t r1 = 0xBF, g1 = 0x00, b1 = 0xFF;

    // WASD, IJKL
    int k1[8] = { 2, 13, 14, 15, 9, 20, 21, 22 };
    for ( int i = 0; i < 8; i++ ) {
        rgb_matrix_set_color( k1[i], r1, g1, b1 );
    }
}

// NUMBER: Numbers vs characters
void rgb_matrix_number(void) {
    int i;
    // First color is blue (HSV 200,255/192,255/192)
    uint8_t r1 = 0xBF, g1 = 0xAA, b1 = 0xFF;
    uint8_t r1f = 0x30, g1f = 0x8B, b1f = 0xBF;
    // Numbers and shifted numbers
    int k1[10] = { 1, 2, 3, 13, 14, 15, 25, 26, 27, 28 };
    int k1s[10]= { 6, 7, 8, 18, 19, 20, 30, 31, 32, 33 };
    for ( i = 0; i < 10; i++ ) {
        rgb_matrix_set_color( k1[i], r1, g1, b1 );
        rgb_matrix_set_color( k1s[i], r1f, g1f, b1f );
    }

    // Second color is turquoise (HSV 170,100/192,100/192)
    uint8_t r2 = 0x00, g2 = 0xFF, b2 = 0xD5;
    uint8_t r2f = 0x30, g2f = 0xBF, b2f = 0xA7;
    // Characters
    int k2[7] = { 0, 4, 5, 16, 17, 29, 23 };
    int k2s[6]= { 12, 9, 10, 21, 22, 34 };
    for ( i = 0; i < 7; i++ ) {
        rgb_matrix_set_color( k2[i], r2, g2, b2 );
    }
    for ( i = 0; i < 6; i++ ) {
        rgb_matrix_set_color( k2s[i], r2f, g2f, b2f );
    }

    // Third color is indigo (HSV 220,255,255)
    uint8_t r3 = 0x00, g3 = 0x55, b3 = 0xFF;
    // Modifiers
    int k3[6] = { 11, 35, 44, 45, 46, 47};
    for ( i = 0; i < 6; i++ ) {
        rgb_matrix_set_color( k3[i], r3, g3, b3 );
    }

    // Capslock is cyan (HSV 180,255,255)
    rgb_matrix_set_color( 43, 0x00, 0xFF, 0xFF );

    // Layer button is violet-ish (HSV 260,255,255)
    rgb_matrix_set_color( 40, 0x55, 0x00, 0xFF );
}

// SETTINGS: Fn keys vs RGB vs Media vs Other
void rgb_matrix_settings(void) {

    int i;

    // First color is red (HSV 0,255,255)
    uint8_t r1 = 0xFF, g1 = 0x00, b1 = 0x0;
    // Function keys
    int k1[12] = { 1, 2, 3, 4, 13, 14, 15, 16, 25, 26, 27, 28 };
    for ( i = 0; i < 12; i++ ) {
        rgb_matrix_set_color( k1[i], r1, g1, b1 );
    }

    // Second color is orange (HSV 30,100,100)
    uint8_t r2 = 0xFF, g2 = 0x80, b2 = 0x00;
    // RGB light change
    int k2[9] = { 8, 9, 10, 20, 21, 22, 32, 33, 34 };
    for ( i = 0; i < 9; i++ ) {
        rgb_matrix_set_color( k2[i], r2, g2, b2 );
    }

    // Third color is pinkish (HSV 330,255,255)
    uint8_t r3 = 0xFF, g3 = 0x00, b3 = 0x80;
    // Modifiers
    int k3[7] = { 5, 6, 17, 18, 19, 31, 11 };
    for ( i = 0; i < 7; i++ ) {
        rgb_matrix_set_color( k3[i], r3, g3, b3 );
    }

    // Fourt color is faded red (HSV 0,192,192)
    uint8_t r4 = 0xBF, g4 = 0x30, b4 = 0x30;
    // Music modifiers
    int k4[8] = { 29, 30, 41, 42, 44, 45, 46, 47};
    for ( i = 0; i < 8; i++ ) {
        rgb_matrix_set_color( k4[i], r4, g4, b4 );
    }

    // Music is yellow (HSV 60,255,255)
    rgb_matrix_set_color( 40, 0xFF, 0xFF, 0x00 );

    // Mouse is green (HSV 90,255,255)
    rgb_matrix_set_color( 43, 0x80, 0xFF, 0x00 );
}

// MOUSE: Arrow vs Scroll vs Click vs Other
void rgb_matrix_mouse(void) {

    int i;

    // Direction is dark green (HSV 120,192,192)
    uint8_t r1 = 0x30, g1 = 0xBF, b1 = 0x30;
    int k1[8] = { 1, 2, 3, 13, 15, 25, 26, 27 };
    for ( i = 0; i < 8; i++ ) {
        rgb_matrix_set_color( k1[i], r1, g1, b1 );
    }

    // Scroll is green (HSV 100,192,192)
    uint8_t r2 = 0x60, g2 = 0xBF, b2 = 0x30;
    // RGB light change
    int k2[8] = { 8, 9, 10, 20, 22, 32, 33, 34 };
    for ( i = 0; i < 8; i++ ) {
        rgb_matrix_set_color( k2[i], r2, g2, b2 );
    }

    // Third color is green (HSV 120,255,255)
    uint8_t r3 = 0x00, g3 = 0xFF, b3 = 0x00;
    // Modifiers
    int k3[6] = { 16, 17, 18, 19, 41, 42 };
    for ( i = 0; i < 6; i++ ) {
        rgb_matrix_set_color( k3[i], r3, g3, b3 );
    }

    // Fourt color is for secrets (HSV 150,192,192)
    uint8_t r4 = 0x30, g4 = 0xBF, b4 = 0x78;
    // Modifiers
    int k4[4] = { 4, 5, 6, 7 };
    for ( i = 0; i < 4; i++ ) {
        rgb_matrix_set_color( k4[i], r4, g4, b4 );
    }

    // Fifth color is for speed (HSV 90,192,192)
    uint8_t r5 = 0x78, g5 = 0xBF, b5 = 0x30;
    // Modifiers
    int k5[3] = { 44, 45, 46 };
    for ( i = 0; i < 3; i++ ) {
        rgb_matrix_set_color( k5[i], r5, g5, b5 );
    }

    // Sixth color is for locking (HSV 110,128,255)
    uint8_t r6 = 0x95, g6 = 0xFF, b6 = 0x80;
    // Modifiers
    int k6[2] = { 40, 43 };
    for ( i = 0; i < 2; i++ ) {
        rgb_matrix_set_color( k6[i], r6, g6, b6 );
    }
}

// MUSIC: Modifiers
void rgb_matrix_music(void) {

    int i;

    // Color is yellow (HSV 50,255,255)
    uint8_t r1 = 0xFF, g1 = 0xD5, b1 = 0x00;
    int k1[7] = { 36, 37, 38, 39, 41, 42, 43};
    for ( i = 0; i < 7; i++ ) {
        rgb_matrix_set_color( k1[i], r1, g1, b1 );
    }

    // Unlock is bright yellow (HSV 60,255,255)
    rgb_matrix_set_color( 40, 0xFF, 0xFF, 0x00 );

}
#endif // RGB_MATRIX_ENABLE
