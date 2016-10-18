#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"
#include "matrix_types.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define DEVICE_VER      0x0001
#define MANUFACTURER    IBNobody
#define PRODUCT         Vision Division
#define DESCRIPTION     Full / Split Keyboard

#define MATRIX_ROWS     6
#define MATRIX_ROW_PINS { C2, C3, F4, F5, F6, F7 }

// !!! MAKE SURE THAT THE LEFT/RIGHT PCB DEFINES MATCH ON ALL OF THESE COLUMNS

//                                               **LEFT**                 **RIGHT**
#define PRODUCT_ID      GET_PID(                 NUMERIC_NORMAL,          NUMERIC_MAX_TEENSY)
#define MATRIX_COLS     GET_MATRIX_COLS(         NUMERIC_NORMAL,          NUMERIC_MAX_TEENSY)
#define MATRIX_COL_PINS GET_MATRIX_COL_PINS(     NUMERIC_NORMAL,          NUMERIC_MAX_TEENSY)

#define KEYMAP(MATRIX_LAYER, \
      k101, k102, k103, k104,       k105, k106, k107, k108, k109, k10A,               k111, k112, k113, k114, k115, k116, k117, k118,       k119, k11A, k11B, k11C, \
      k201, k202, k203, k204,       k205, k206, k207, k208, k209, k20A,               k211, k212, k213, k214, k215, k216, k217, k218,       k219, k21A, k21B, k21C, \
      k301, k302, k303, k304,       k305, k306, k307, k308, k309, k30A,               k311, k312, k313, k314, k315, k316, k317, k318,       k319, k31A, k31B, k31C, \
      k401, k402, k403, k404,       k405, k406, k407, k408, k409, k40A,               k411, k412, k413, k414, k415, k416, k417, k418,       k419, k41A, k41B, k41C, \
      k501, k502, k503, k504,       k505, k506, k507, k508, k509, k50A,               k511, k512, k513, k514, k515, k516, k517, k518,       k519, k51A, k51B, k51C, \
      k601, k602, k603, k604,       k605, k606, k607, k608, k609, k60A,               k611, k612, k613, k614, k615, k616, k617, k618,       k619, k61A, k61B, k61C  \
) \
KEYMAP_MASTER(MATRIX_LAYER,                      NUMERIC_NORMAL,          NUMERIC_MAX_TEENSY, \
      k101, k102, k103, k104,       k105, k106, k107, k108, k109, k10A, KC_NO, KC_NO, k111, k112, k113, k114, k115, k116, k117, k118,       k119, k11A, k11B, k11C, \
      k201, k202, k203, k204,       k205, k206, k207, k208, k209, k20A, KC_NO, KC_NO, k211, k212, k213, k214, k215, k216, k217, k218,       k219, k21A, k21B, k21C, \
      k301, k302, k303, k304,       k305, k306, k307, k308, k309, k30A, KC_NO, KC_NO, k311, k312, k313, k314, k315, k316, k317, k318,       k319, k31A, k31B, k31C, \
      k401, k402, k403, k404,       k405, k406, k407, k408, k409, k40A, KC_NO, KC_NO, k411, k412, k413, k414, k415, k416, k417, k418,       k419, k41A, k41B, k41C, \
      k501, k502, k503, k504,       k505, k506, k507, k508, k509, k50A, KC_NO, KC_NO, k511, k512, k513, k514, k515, k516, k517, k518,       k519, k51A, k51B, k51C, \
      k601, k602, k603, k604,       k605, k606, k607, k608, k609, k60A, KC_NO, KC_NO, k611, k612, k613, k614, k615, k616, k617, k618,       k619, k61A, k61B, k61C  \
)

// Example Keymap Macros

/*
#define KEYMAP(MATRIX_LAYER, \
      k101, k102, k103, k104,       k105, k106, k107, k108, k109, k10A, k10B, k10C, k111, k112, k113, k114, k115, k116, k117, k118,       k119, k11A, k11B, k11C, \
      k201, k202, k203, k204,       k205, k206, k207, k208, k209, k20A, k20B, k20C, k211, k212, k213, k214, k215, k216, k217, k218,       k219, k21A, k21B, k21C, \
      k301, k302, k303, k304,       k305, k306, k307, k308, k309, k30A, k30B, k30C, k311, k312, k313, k314, k315, k316, k317, k318,       k319, k31A, k31B, k31C, \
      k401, k402, k403, k404,       k405, k406, k407, k408, k409, k40A, k40B, k40C, k411, k412, k413, k414, k415, k416, k417, k418,       k419, k41A, k41B, k41C, \
      k501, k502, k503, k504,       k505, k506, k507, k508, k509, k50A, k50B, k50C, k511, k512, k513, k514, k515, k516, k517, k518,       k519, k51A, k51B, k51C, \
      k601, k602, k603, k604,       k605, k606, k607, k608, k609, k60A, k60B, k60C, k611, k612, k613, k614, k615, k616, k617, k618,       k619, k61A, k61B, k61C  \
) \
KEYMAP_MASTER(MATRIX_LAYER,                      NUMERIC_MAX_TEENSY,      NUMERIC_MAX, \
      k101, k102, k103, k104, k105, k106, k107, k108, k109, k10A, k10B, k10C, k111, k112, k113, k114, k115, k116, k117, k118, k119, k11A, k11B, k11C, \
      k201, k202, k203, k204, k205, k206, k207, k208, k209, k20A, k20B, k20C, k211, k212, k213, k214, k215, k216, k217, k218, k219, k21A, k21B, k21C, \
      k301, k302, k303, k304, k305, k306, k307, k308, k309, k30A, k30B, k30C, k311, k312, k313, k314, k315, k316, k317, k318, k319, k31A, k31B, k31C, \
      k401, k402, k403, k404, k405, k406, k407, k408, k409, k40A, k40B, k40C, k411, k412, k413, k414, k415, k416, k417, k418, k419, k41A, k41B, k41C, \
      k501, k502, k503, k504, k505, k506, k507, k508, k509, k50A, k50B, k50C, k511, k512, k513, k514, k515, k516, k517, k518, k519, k51A, k51B, k51C, \
      k601, k602, k603, k604, k605, k606, k607, k608, k609, k60A, k60B, k60C, k611, k612, k613, k614, k615, k616, k617, k618, k619, k61A, k61B, k61C  \
)
*/

/*
#define KEYMAP(MATRIX_LAYER, \
      k101, k102, k103, k104,       k105, k106, k107, k108, k109, k10A, k111, k112, k113, k114, k115, k116, k117, k118,       k119, k11A, k11B, \
      k201, k202, k203, k204,       k205, k206, k207, k208, k209, k20A, k211, k212, k213, k214, k215, k216, k217, k218,       k219, k21A, k21B, \
      k301, k302, k303, k304,       k305, k306, k307, k308, k309, k30A, k311, k312, k313, k314, k315, k316, k317, k318,       k319, k31A, k31B, \
      k401, k402, k403, k404,       k405, k406, k407, k408, k409, k40A, k411, k412, k413, k414, k415, k416, k417, k418,       k419, k41A, k41B, \
      k501, k502, k503, k504,       k505, k506, k507, k508, k509, k50A, k511, k512, k513, k514, k515, k516, k517, k518,       k519, k51A, k51B, \
      k601, k602, k603, k604,       k605, k606, k607, k608, k609, k60A, k611, k612, k613, k614, k615, k616, k617, k618,       k619, k61A, k61B  \
) \
KEYMAP_MASTER(MATRIX_LAYER,                      NUMERIC_NORMAL,          HOMING_MAX_TEENSY, \
      k101, k102, k103, k104, k105, k106, k107, k108, k109, k10A, KC_NO, KC_NO, k111, k112, k113, k114, k115, k116, k117, k118, k119, k11A, k11B, KC_NO, \
      k201, k202, k203, k204, k205, k206, k207, k208, k209, k20A, KC_NO, KC_NO, k211, k212, k213, k214, k215, k216, k217, k218, k219, k21A, k21B, KC_NO, \
      k301, k302, k303, k304, k305, k306, k307, k308, k309, k30A, KC_NO, KC_NO, k311, k312, k313, k314, k315, k316, k317, k318, k319, k31A, k31B, KC_NO, \
      k401, k402, k403, k404, k405, k406, k407, k408, k409, k40A, KC_NO, KC_NO, k411, k412, k413, k414, k415, k416, k417, k418, k419, k41A, k41B, KC_NO, \
      k501, k502, k503, k504, k505, k506, k507, k508, k509, k50A, KC_NO, KC_NO, k511, k512, k513, k514, k515, k516, k517, k518, k519, k51A, k51B, KC_NO, \
      k601, k602, k603, k604, k605, k606, k607, k608, k609, k60A, KC_NO, KC_NO, k611, k612, k613, k614, k615, k616, k617, k618, k619, k61A, k61B, KC_NO  \
)
*/

#endif