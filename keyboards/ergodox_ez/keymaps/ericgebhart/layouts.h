/********************************************************************/
/* Ergodox EZ                                                       */
/********************************************************************/
// This one is is set up to pass in the number row.
// Beakl and bepo both change the number row.
// Left, middle, right, bottom, and thumbs all stay the same.
#define Base_dox(                                                       \
                 K01, K02, K03, K04, K05,                               \
                 K06, K07, K08, K09, K0A,                               \
                 K11, K12, K13, K14, K15,                               \
                 K16, K17, K18, K19, K1A,                               \
                 K21, K22, K23, K24, K25,                               \
                 K26, K27, K28, K29, K2A,                               \
                 K31, K32, K33, K34, K35,                               \
                 K36, K37, K38, K39, K3A                                \
                                                                        ) \
  LVARG_edox(                                                           \
             ROW0_LEFT(K01, K02, K03, K04, K05),                        \
             ___2_MIDDLE_1___,                                          \
             ROW0_RIGHT(K06, K07, K08, K09, K0A),                       \
                                                                        \
             ROW1_LEFT(K11, K12, K13, K14, K15),                        \
             ___2_MIDDLE_2___,                                          \
             ROW1_RIGHT(K16, K17, K18, K19, K1A),                       \
                                                                        \
             ROW2_LEFT(K21, K22, K23, K24, K25),                        \
             ROW2_RIGHT(K26, K27, K28, K29, K2A),                       \
                                                                        \
             ROW3_LEFT(K31, K32, K33, K34, K35),                        \
             ___2_MIDDLE_3___,                                          \
             ROW3_RIGHT(K36, K37, K38, K39, K3A),                       \
             ___5_BOTTOM_LEFT___,   ___5_BOTTOM_RIGHT___,               \
             ___12_DOX_ALL_THUMBS___                                    \
                                                                        )

#define Base_dox_bepo(                                                  \
                      K01, K02, K03, K04, K05,                          \
                      K06, K07, K08, K09, K0A,                          \
                      K11, K12, K13, K14, K15,                          \
                      K16, K17, K18, K19, K1A,                          \
                      K21, K22, K23, K24, K25,                          \
                      K26, K27, K28, K29, K2A,                          \
                      K31, K32, K33, K34, K35,                          \
                      K36, K37, K38, K39, K3A                           \
                                                                        ) \
  LVARG_edox(                                                           \
             ROW0_LEFT(K01, K02, K03, K04, K05),                        \
             ___2_MIDDLE_1___,                                          \
             ROW0_RIGHT(K06, K07, K08, K09, K0A),                       \
                                                                        \
             ROW1_LEFT(K11, K12, K13, K14, K15),                        \
             ___2_MIDDLE_2___,                                          \
             ROW1_RIGHT(K16, K17, K18, K19, K1A),                       \
                                                                        \
             ROW2_LEFT(K21, K22, K23, K24, K25),                        \
             ROW2_RIGHT(K26, K27, K28, K29, K2A),                       \
                                                                        \
             ROW3_LEFT(K31, K32, K33, K34, K35),                        \
             ___2_MIDDLE_3___,                                          \
             ROW3_RIGHT(K36, K37, K38, K39, K3A),                       \
             ___5_BOTTOM_LEFT___, ___5_BOTTOM_RIGHT___,                 \
             ___12_DOX_ALL_THUMBS_BP___                                 \
                                                                        )


#define Base_dox_bepo6(                                                 \
                       K01, K02, K03, K04, K05, K06,                    \
                       K07, K08, K09, K0A, K0B, K0C,                    \
                       K11, K12, K13, K14, K15, K16,                    \
                       K17, K18, K19, K1A, K1B, K1C,                    \
                       K21, K22, K23, K24, K25, K26,                    \
                       K27, K28, K29, K2A, K2B, K2C                     \
                                                                        ) \
  LVARG_edox(                                                           \
             ___6SYMBOL_BEPO_L___,                                      \
             ___2_MIDDLE_T_BP___,                                       \
             ___6SYMBOL_BEPO_R___,                                      \
             ROW1_LEFT_BP6(K01, K02, K03, K04, K05, K06),               \
             ___2_MIDDLE_2_BP___,                                       \
             ROW1_RIGHT_BP6(K07, K08, K09, K0A, K0B, K0C),              \
                                                                        \
             ROW2_LEFT_BP6(K11, K12, K13, K14, K15, K16),               \
             ROW2_RIGHT_BP6(K17, K18, K19, K1A, K1B, K1C),              \
                                                                        \
             ROW3_LEFT_BP6(K21, K22, K23, K24, K25, K26),               \
             ___2_MIDDLE_3_BP___,                                       \
             ROW3_RIGHT_BP6(K27, K28, K29, K2A, K2B, K2C),              \
                                                                        \
             ___5_BOTTOM_LEFT_BP___, ___5_BOTTOM_RIGHT_BP___,           \
             ___12_DOX_ALL_THUMBS_BP___                                 \
                                                                        )

#define Transient_dox6(                                                 \
                       K01, K02, K03, K04, K05, K06,                    \
                       K07, K08, K09, K0A, K0B, K0C,                    \
                       K11, K12, K13, K14, K15, K16,                    \
                       K17, K18, K19, K1A, K1B, K1C,                    \
                       K21, K22, K23, K24, K25, K26,                    \
                       K27, K28, K29, K2A, K2B, K2C,                    \
                       K31, K32, K33, K34, K35, K36,                    \
                       K37, K38, K39, K3A, K3B, K3C                     \
                                                                        ) \
  LVARG_edox(                                                           \
             K01, K02, K03, K04, K05, K06,                              \
             ___2___,                                                   \
             K07, K08, K09, K0A, K0B, K0C,                              \
             K11, K12, K13, K14, K15, K16,                              \
             ___2___,                                                   \
             K17, K18, K19, K1A, K1B, K1C,                              \
             K21, K22, K23, K24, K25, K26,                              \
             K27, K28, K29, K2A, K2B, K2C,                              \
             K31, K32, K33, K34, K35, K36,                              \
             ___2___,                                                   \
             K37, K38, K39, K3A, K3B, K3C,                              \
             ___5___, ___5___,                                          \
             ___12___                                                   \
                                                                        )

#define Dox_base(...)        Base_dox(__VA_ARGS__)
#define Dox_bepo_base(...)   Base_dox_bepo(__VA_ARGS__)
#define Dox_bepo_base6(...)  Base_dox_bepo6(__VA_ARGS__)
#define Dox_transient(...)   Transient_dox6(__VA_ARGS__)
