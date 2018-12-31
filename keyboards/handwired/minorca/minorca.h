#ifndef MINORCA_H
#define MINORCA_H

#include "quantum.h"

#define LAYOUT( \
    KA00, KA01, KA02, KA03, KA04, KA05, KA06, KA07, KA08, KA09, KA10, KA11, \
    KB00,  KB01, KB02, KB03, KB04, KB05, KB06, KB07, KB08, KB09,    KB11,   \
    KC00,    KC02, KC03, KC04, KC05, KC06, KC07, KC08, KC09, KC10,   KC11,  \
    KD00,  KD02,  KD03,          KD04, KD07,           KD09,  KD10,  KD11   \
) { \
  {  KA00,  KA01,   KA02,  KA03,  KA04,  KA05,   KA06,   KA07,  KA08,   KA09,  KA10,   KA11  }, \
  {  KB00,  KB01,   KB02,  KB03,  KB04,  KB05,   KB06,   KB07,  KB08,   KB09,  KC_NO,  KB11  }, \
  {  KC00,  KC_NO,  KC02,  KC03,  KC04,  KC05,   KC06,   KC07,  KC08,   KC09,  KC10,   KC11  }, \
  {  KD00,  KC_NO,  KD02,  KD03,  KD04,  KC_NO,  KC_NO,  KD07,  KC_NO,  KD09,  KD10,   KD11  } \
}

#endif
