#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include QMK_KEYBOARD_CONFIG_H

#define PREVENT_STUCK_MODIFIERS
#define SPACE_COUNT 3

#define TEMPLATE_TKL( \
  KESC,       KF01, KF02, KF03, KF04, KF05, KF06, KF07, KF08, KF09, KF10, KF11, KF12,   KSCL, KPRS, KADJ, \
  KGRV, K_1 , K_2 , K_3 , K_4 , K_5 , K_6 , K_7 , K_8 , K_9 , K_0 , KMIN, KEQL, KBSP,   KINS, KHOM, KPUP, \
  KTAB, K_Q , K_W , K_E , K_R , K_T , K_Y , K_U , K_I , K_O , K_P , KLBR, KRBR, KBLS,   KDEL, KEND, LPDN, \
  KCAP, K_A , K_S , K_D , K_F , K_G , K_H , K_J , K_K , K_L , KSMI, KQUO,       KENT,                     \
  KLSH, K_Z , K_X , K_C , K_V , K_B , K_N , K_M , KCMA, KDOT, KSLS,             KRSH,         K_UP,       \
  KLCT, KLOS, KLAL,             KSP3, KSP2, KSP1,             KRAL, KROS, KRCT, KPTT,   K_LT, K_DN, K_RT  \
) LAYOUT( \
  K_Q , K_W , K_E , K_R , K_T ,             K_Y , K_U , K_I , K_O , K_P , \
  K_A , K_S , K_D , K_F , K_G ,             K_H , K_J , K_K , K_L , KSMI, \
  K_Z , K_X , K_C , K_V , K_B ,             K_N , K_M , KCMA, KDOT, KSLS, \
  KTAB, KLOS, KLAL, KLSH, KSP3, KSP2, KCAP, KSP1, KRSH, KBLS, KQUO, KADJ \
)

#define TEMPLATE_NUM( \
  KGRV, K_1 , K_2 , K_3 , K_4 , K_5 , K_6 , K_7 , K_8 , K_9 , K_0 , KMIN, KEQL, KBSL, KESC, \
  KTAB, K_Q , K_W , K_E , K_R , K_T , K_Y , K_U , K_I , K_O , K_P , KLBR, KRBR,       KBSP, \
  KCAP, K_A , K_S , K_D , K_F , K_G , K_H , K_J , K_K , K_L , KSMI, KQUO,             KENT, \
  KLSH, K_Z , K_X , K_C , K_V , K_B , K_N , K_M , KCMA, KDOT, KSLS,             KRSH, KADJ, \
  KLCT, KLOS, KLAL,             KSP3, KSP2, KSP1,             KRAL, KROS, KRCT, KPTT        \
) LAYOUT( \
  K_Q , K_W , K_E , K_R , K_T ,             K_Y , K_U , K_I , K_O , K_P , \
  K_A , K_S , K_D , K_F , K_G ,             K_H , K_J , K_K , K_L , KSMI, \
  K_Z , K_X , K_C , K_V , K_B ,             K_N , K_M , KCMA, KDOT, KSLS, \
  KTAB, KLOS, KLAL, KLSH, KSP3, KSP2, KCAP, KSP1, KRAL, KROS, KQUO, KADJ \
)

#define TEMPLATE_RESET LAYOUT( \
  RESET  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  RESET  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
)
#endif
