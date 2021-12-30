/********************************************************************/
/* CRKBD  Corne                                                     */
/*    The Corne has  3x6 matrix on both sides with 6 thumbs total   */
/* This Macro takes 2x3x5 and gives it pinkies, and thumbs.         */
/* Arg chunks are in the middle with the passthrough modifiers as   */
/* needed.  Sama Sama apres cette fois.                             */
/********************************************************************/
#define Base_crkbd(                                                     \
                   K01, K02, K03, K04, K05,                             \
                   K06, K07, K08, K09, K0A,                             \
                   K11, K12, K13, K14, K15,                             \
                   K16, K17, K18, K19, K1A,                             \
                   K21, K22, K23, K24, K25,                             \
                   K26, K27, K28, K29, K2A)                             \
  LAYOUT_VARG(                                                          \
              ROW1_LEFT(K01, K02, K03, K04, K05),                       \
              ROW1_RIGHT(K06, K07, K08, K09, K0A),                      \
                                                                        \
              ROW2_LEFT(K11, K12, K13, K14, K15),                       \
              ROW2_RIGHT(K16, K17, K18, K19, K1A),                      \
                                                                        \
              ROW3_LEFT(K21, K22, K23, K24, K25),                       \
              ROW3_RIGHT(K26, K27, K28, K29, K2A),                      \
              ___6_CRKBD_THUMBS___                                      \
                                                                        )

// So we can have different transient layers for symbols and numbers on bepo.
// for layouts like dvorak on bepo.
#define Base_crkbd_bepo(                                                \
                        K01, K02, K03, K04, K05,                        \
                        K06, K07, K08, K09, K0A,                        \
                        K11, K12, K13, K14, K15,                        \
                        K16, K17, K18, K19, K1A,                        \
                        K21, K22, K23, K24, K25,                        \
                        K26, K27, K28, K29, K2A                         \
                                                                    )   \
  LAYOUT_VARG(                                                          \
              ROW1_LEFT_BP(K01, K02, K03, K04, K05),                    \
              ROW1_RIGHT_BP(K06, K07, K08, K09, K0A),                   \
                                                                        \
              ROW2_LEFT_BP(K11, K12, K13, K14, K15),                    \
              ROW2_RIGHT_BP(K16, K17, K18, K19, K1A),                   \
                                                                        \
              ROW3_LEFT_BP(K21, K22, K23, K24, K25),                    \
              ROW3_RIGHT_BP(K26, K27, K28, K29, K2A),                   \
              ___6_CRKBD_THUMBS_BP___                                   \
                                                                        )

// No room for pinkies.
// Just for bepo because it's a 3x6 matrix on each side.
// So 3 pairs of 6 keys, And we lose our left and right.
// Except it keeps the layer toggles along with the keycode
// on the bottom.
#define Base_crkbd_bepo6(                                               \
                         K01, K02, K03, K04, K05, K06,                  \
                         K07, K08, K09, K0A, K0B, K0C,                  \
                         K11, K12, K13, K14, K15, K16,                  \
                         K17, K18, K19, K1A, K1B, K1C,                  \
                         K21, K22, K23, K24, K25, K26,                  \
                         K27, K28, K29, K2A, K2B, K2C                   \
                                                                )       \
  LAYOUT_VARG(                                                          \
              ROW1_LEFT_BP6(K01, K02, K03, K04, K05, K06),              \
              ROW1_RIGHT_BP6(K07, K08, K09, K0A, K0B, K0C),             \
                                                                        \
              ROW2_LEFT_BP6(K11, K12, K13, K14, K15, K16),              \
              ROW2_RIGHT_BP6(K17, K18, K19, K1A, K1B, K1C),             \
                                                                        \
              ROW3_LEFT_BP6(K21, K22, K23, K24, K25, K26),              \
              ROW3_RIGHT_BP6(K27, K28, K29, K2A, K2B, K2C),             \
              ___6_CRKBD_THUMBS_BP___                                   \
                                                                       )

// All we really need is to add the see through thumbs to the end.
#define Base_crkbd_transient(                                   \
                             K01, K02, K03, K04, K05, K06,      \
                             K07, K08, K09, K0A, K0B, K0C,      \
                             K11, K12, K13, K14, K15, K16,      \
                             K17, K18, K19, K1A, K1B, K1C,      \
                             K21, K22, K23, K24, K25, K26,      \
                             K27, K28, K29, K2A, K2B, K2C       \
                                            )                   \
  LAYOUT_VARG(                                                  \
              K01, K02, K03, K04, K05, K06,                     \
              K07, K08, K09, K0A, K0B, K0C,                     \
              K11, K12, K13, K14, K15, K16,                     \
              K17, K18, K19, K1A, K1B, K1C,                     \
              K21, K22, K23, K24, K25, K26,                     \
              K27, K28, K29, K2A, K2B, K2C,                     \
              ___6___)

#define Crkbd_base(...)        Base_crkbd(__VA_ARGS__)
#define Crkbd_bepo(...)        Base_crkbd_bepo(__VA_ARGS__)
#define Crkbd_bepo6(...)       Base_crkbd_bepo6(__VA_ARGS__)
#define Crkbd_transient(...)   Base_crkbd_transient(__VA_ARGS__)
