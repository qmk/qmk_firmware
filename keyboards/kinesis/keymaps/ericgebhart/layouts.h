/********************************************************************/
/* Kinesis*/
/********************************************************************/
// Basically an ergodox ez without the 3 pairs of middle keys.
// Left, right, bottom, and thumbs all stay the same.
#define Base_kinesis(                                                   \
                     K01, K02, K03, K04, K05,                           \
                     K06, K07, K08, K09, K0A,                           \
                     K11, K12, K13, K14, K15,                           \
                     K16, K17, K18, K19, K1A,                           \
                     K21, K22, K23, K24, K25,                           \
                     K26, K27, K28, K29, K2A,                           \
                     K31, K32, K33, K34, K35,                           \
                     K36, K37, K38, K39, K3A                            \
                                                                        ) \
  LAYOUT_PVARG(                                                         \
               ___KINTFUNC_L___, ___KINTFUNC_R___,                      \
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
               ___4_BOTTOM_LEFT___, ___4_BOTTOM_RIGHT___,               \
               ___12_DOX_ALL_THUMBS___                                  \
                                                                        )

#define Base_kinesis_bepo(                                              \
                          K01, K02, K03, K04, K05,                      \
                          K06, K07, K08, K09, K0A,                      \
                          K11, K12, K13, K14, K15,                      \
                          K16, K17, K18, K19, K1A,                      \
                          K21, K22, K23, K24, K25,                      \
                          K26, K27, K28, K29, K2A,                      \
                          K31, K32, K33, K34, K35,                      \
                          K36, K37, K38, K39, K3A                       \
                                                                        ) \
  LAYOUT_PVARG(                                                         \
               ___KINTFUNC_L___, ___KINTFUNC_R___,                      \
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
               ___4_BOTTOM_LEFT___, ___4_BOTTOM_RIGHT___,               \
               ___12_DOX_ALL_THUMBS_BP___                               \
                                                                        )


// So 3 pairs of 6 keys, left and right.
#define Base_kinesis_bepo6(                                             \
                           K01, K02, K03, K04, K05, K06,                \
                           K07, K08, K09, K0A, K0B, K0C,                \
                           K11, K12, K13, K14, K15, K16,                \
                           K17, K18, K19, K1A, K1B, K1C,                \
                           K21, K22, K23, K24, K25, K26,                \
                           K27, K28, K29, K2A, K2B, K2C                 \
                                                                        ) \
  LAYOUT_PVARG(                                                         \
               ___KINTFUNC_L___, ___KINTFUNC_R___,                      \
               ___6SYMBOL_BEPO_L___,                                    \
               ___6SYMBOL_BEPO_R___,                                    \
               ROW1_LEFT_BP6(K01, K02, K03, K04, K05, K06),             \
               ROW1_RIGHT_BP6(K07, K08, K09, K0A, K0B, K0C),            \
                                                                        \
               ROW2_LEFT_BP6(K11, K12, K13, K14, K15, K16),             \
               ROW2_RIGHT_BP6(K17, K18, K19, K1A, K1B, K1C),            \
                                                                        \
               ROW3_LEFT_BP6(K21, K22, K23, K24, K25, K26),             \
               ROW3_RIGHT_BP6(K27, K28, K29, K2A, K2B, K2C),            \
               ___4_BOTTOM_LEFT_BP___, ___4_BOTTOM_RIGHT_BP___,         \
               ___12_DOX_ALL_THUMBS_BP___                               \
                                                                        )

#define Transient_kinesis(                                              \
                          K01, K02, K03, K04, K05, K06,                 \
                          K07, K08, K09, K0A, K0B, K0C,                 \
                          K11, K12, K13, K14, K15, K16,                 \
                          K17, K18, K19, K1A, K1B, K1C,                 \
                          K21, K22, K23, K24, K25, K26,                 \
                          K27, K28, K29, K2A, K2B, K2C,                 \
                          K31, K32, K33, K34, K35, K36,                 \
                          K37, K38, K39, K3A, K3B, K3C                  \
                                                                       ) \
  LAYOUT_PVARG(                                                         \
               ___KINTFUNC_L___, ___KINTFUNC_R___,                      \
               K01, K02, K03, K04, K05, K06,                            \
               K07, K08, K09, K0A, K0B, K0C,                            \
               K11, K12, K13, K14, K15, K16,                            \
               K17, K18, K19, K1A, K1B, K1C,                            \
               K21, K22, K23, K24, K25, K26,                            \
               K27, K28, K29, K2A, K2B, K2C,                            \
               K31, K32, K33, K34, K35, K36,                            \
               K37, K38, K39, K3A, K3B, K3C,                            \
               ___4___, ___4___,                                        \
               ___12___                                                 \
                                                                        )

#define Kinesis_base(...)        Base_kinesis(__VA_ARGS__)
#define Kinesis_bepo_base(...)   Base_kinesis_bepo(__VA_ARGS__)
#define Kinesis_bepo_base6(...)  Base_kinesis_bepo6(__VA_ARGS__)
#define Kinesis_transient(...)   Transient_kinesis(__VA_ARGS__)
