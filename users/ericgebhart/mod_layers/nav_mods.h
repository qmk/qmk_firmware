// RIGHT.
#define ROW0R_5_hrs_nav(K01, K02, K03, K04, K05)    \
  K01, K02, K03, K04, K05

// Take and put an extra column in front.
#define ROW0R_6_hrs_nav(K01, K02, K03, K04, K05, K06) \
  ROW0R_5_hrs_nav(K01, K02, K03, K04, K05),\
  K06

// 5 into 6, derivitive of the first two.
#define ROW0R_5_6_hrs_nav(K01, K02, K03, K04, K05) \
  ROW0R_6_hrs_nav(K01, K02, K03, K04, K05, RIGHT_0)
