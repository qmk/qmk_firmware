// RIGHT.
#define ROW0R_5_miryoku_hrm_gacs(K01, K02, K03, K04, K05)       \
  K01, K02, K03, K04, K05

// Take and put an extra column in front.
// Mod K01 how you want it.
#define ROW0R_6_miryoku_hrm_gacs(K01, K02, K03, K04, K05, K06) \
   ROW0R_5_miryoku_hrm_gacs(K01, K02, K03, K04, K05),          \
   K06

// 5 into 6, derivitive of the first two.
#define ROW0R_5_6_miryoku_hrm_gacs(K01, K02, K03, K04, K05)    \
   ROW0R_6_miryoku_hrm_gacs(K01, K02, K03, K04, K05, RIGHT_0)
