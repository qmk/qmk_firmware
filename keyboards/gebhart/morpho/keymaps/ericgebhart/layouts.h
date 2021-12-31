#include QMK_KEYBOARD_H

#undef LAYOUT_PVARG

#define LAYOUT_PVARG(...)     LAYOUT_split_4x6_5_8(__VA_ARGS__)

/* This keyboard is a split, 4x6 + a row of 5 and a thumb cluster of 8. */
/* So We need Base_4x6_5_8 As a layout template to add mods, and fill */
/* out the perimeter keys of the keyboard. Perimeter keys being the */
/* number row, outside pinky keys, the 5th row, and thumbs. */

/********************************************************************/
/* Dactyl with 8 thumb keys*/
/********************************************************************/
// Basically an ergodox ez without the 3 pairs of middle keys.
// electrically 7 columns in the 5th row. 6 in the rest.
// Left, right, bottom, and thumbs all stay the same.

#define Base_4x6_5_8(                                                 \
                     K01, K02, K03, K04, K05,                         \
                     K06, K07, K08, K09, K0A,                           \
                     K11, K12, K13, K14, K15,                           \
                     K16, K17, K18, K19, K1A,                           \
                     K21, K22, K23, K24, K25,                           \
                     K26, K27, K28, K29, K2A,                           \
                     K31, K32, K33, K34, K35,                           \
                     K36, K37, K38, K39, K3A                            \
                                                                        ) \
  LAYOUT_PVARG(                                                         \
               ROW0_LEFT(K01, K02, K03, K04, K05),                      \
               ROW0_RIGHT(K06, K07, K08, K09, K0A),                     \
                                                                        \
               ROW1_LEFT(K11, K12, K13, K14, K15),                      \
               ROW1_RIGHT(K16, K17, K18, K19, K1A),                     \
                                                                        \
               ROW2_LEFT(K21, K22, K23, K24, K25),                      \
               ROW2_RIGHT(K26, K27, K28, K29, K2A),                     \
                                                                        \
               ROW3_LEFT(K31, K32, K33, K34, K35),                      \
               ROW3_RIGHT(K36, K37, K38, K39, K3A),                     \
               ___5_BOTTOM_LEFT___, ___5_BOTTOM_RIGHT___,               \
               ___16_ALL_THUMBSb___                                     \
                                                                        )

#define Base_bepo_4x6_5_8(                                         \
                          K01, K02, K03, K04, K05,                      \
                          K06, K07, K08, K09, K0A,                      \
                          K11, K12, K13, K14, K15,                      \
                          K16, K17, K18, K19, K1A,                      \
                          K21, K22, K23, K24, K25,                      \
                          K26, K27, K28, K29, K2A,                      \
                          K31, K32, K33, K34, K35,                    \
                          K36, K37, K38, K39, K3A                       \
                                                                        ) \
  LAYOUT_PVARG(                                                         \
               ROW0_LEFT_BP(K01, K02, K03, K04, K05),                   \
               ROW0_RIGHT_BP(K06, K07, K08, K09, K0A),                  \
                                                                        \
               ROW1_LEFT_BP(K11, K12, K13, K14, K15),                   \
               ROW1_RIGHT_BP(K16, K17, K18, K19, K1A),                  \
                                                                        \
               ROW2_LEFT_BP(K21, K22, K23, K24, K25),                   \
               ROW2_RIGHT_BP(K26, K27, K28, K29, K2A),                  \
                                                                        \
               ROW3_LEFT_BP(K31, K32, K33, K34, K35),                   \
               ROW3_RIGHT_BP(K36, K37, K38, K39, K3A),                  \
               ___5_BOTTOM_LEFT___, ___5_BOTTOM_RIGHT___,               \
               ___16_ALL_THUMBSb_BP___                                  \
                                                                        )


// so far no need for mods on the transient layers.
// switching to 3x5 transients. 10 column defines.
// I like 3x10 maps even on big keyboards.
# define Transient_4x6_5_8(                                        \
                           K01, K02, K03, K04, K05,                     \
                           K07, K08, K09, K0A, K0B,                     \
                           K11, K12, K13, K14, K15,                     \
                           K17, K18, K19, K1A, K1B,                     \
                           K21, K22, K23, K24, K25,                     \
                           K27, K28, K29, K2A, K2B                      \
                                                                        ) \
  LAYOUT_PVARG(                                                         \
               ___6___, ___6___,                                        \
               ___, K01, K02, K03, K04, K05,                            \
               K07, K08, K09, K0A, K0B, ___,                            \
               ___, K11, K12, K13, K14, K15,                            \
               K17, K18, K19, K1A, K1B, ___,                            \
               ___, K21, K22, K23, K24, K25,                            \
               K27, K28, K29, K2A, K2B, ___,                            \
               ___5___, ___5___,                                        \
               ___16___                                                 \
                                                                        )
