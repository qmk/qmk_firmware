#ifndef MATRIX_TYPES_H
#define MATRIX_TYPES_H

// Because the vision/division keyboard allows for multiple PCB configurations, the configuration
// can get tricky. The PCB itself has 12 columns, but to achieve a full sized 14-column keyboard
// with a 4-column numeric pad on the left and a 3-column homing key cluster on the right, the
// right PCB must have its rightmost column cut off. Also either the rightmost two columns on the
// left PCB or the leftmost two columns on the right PCB need to be cut away.
//
//                          _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
// Left Numeric Max       = 1 2 3 4 _ 5 6 7 8 9 0 A B C
// Left Homing Max        =   2 3 4 _ 5 6 7 8 9 0 A B C
// Left Numeric Extended  = 1 2 3 4 _ 5 6 7 8 9 0 A B
// Left Homing Extended   =   2 3 4 _ 5 6 7 8 9 0 A B
// Left Numeric Normal    = 1 2 3 4 _ 5 6 7 8 9 0 A
// Left Homing Normal     =   2 3 4 _ 5 6 7 8 9 0 A
// Right Numeric Max      =                             1 2 3 4 5 6 7 8 _ 9 A B C
// Right Homing Max       =                             1 2 3 4 5 6 7 8 _ 9 A B
// Right Numeric Extended =                               2 3 4 5 6 7 8 _ 9 A B C
// Right Homing Extended  =                               2 3 4 5 6 7 8 _ 9 A B
// Right Numeric Normal   =                                 3 4 5 6 7 8 _ 9 A B C
// Right Homing Normal    =                                 3 4 5 6 7 8 _ 9 A B
//
//
// A full keyboard would look like this:
//
// _Left_Numeric_Max__________|_Right_Homing_Normal
// 1 2 3 4 _ 5 6 7 8 9 0 A B C|3 4 5 6 7 8 _ 9 A B
//
// The ideal full keyboard would use a normal and max rather than two extended because the max
// size allows for a centered 2U space key.


#define MATRIX_TYPE_ABSENT                      0
#define MATRIX_TYPE_NUMERIC_MAX                 1
#define MATRIX_TYPE_HOMING_MAX                  2
#define MATRIX_TYPE_NUMERIC_EXTENDED            3
#define MATRIX_TYPE_HOMING_EXTENDED             4
#define MATRIX_TYPE_NUMERIC_NORMAL              5
#define MATRIX_TYPE_HOMING_NORMAL               6
#define MATRIX_TYPE_NUMERIC_MAX_TEENSY          7
#define MATRIX_TYPE_HOMING_MAX_TEENSY           8
#define MATRIX_TYPE_NUMERIC_EXTENDED_TEENSY     9
#define MATRIX_TYPE_HOMING_EXTENDED_TEENSY      10
#define MATRIX_TYPE_NUMERIC_NORMAL_TEENSY       11
#define MATRIX_TYPE_HOMING_NORMAL_TEENSY        12


// Column Length

#define MATRIX_COLS_ABSENT                       0
#define MATRIX_COLS_NUMERIC_MAX                 12
#define MATRIX_COLS_HOMING_MAX                  11
#define MATRIX_COLS_NUMERIC_EXTENDED            11
#define MATRIX_COLS_HOMING_EXTENDED             10
#define MATRIX_COLS_NUMERIC_NORMAL              10
#define MATRIX_COLS_HOMING_NORMAL                9
#define MATRIX_COLS_NUMERIC_MAX_TEENSY          12
#define MATRIX_COLS_HOMING_MAX_TEENSY           11
#define MATRIX_COLS_NUMERIC_EXTENDED_TEENSY     11
#define MATRIX_COLS_HOMING_EXTENDED_TEENSY      10
#define MATRIX_COLS_NUMERIC_NORMAL_TEENSY       10
#define MATRIX_COLS_HOMING_NORMAL_TEENSY         9

// Left PCB Pin assignments

#define MATRIX_COL_PINS_LEFT_ABSENT

#define MATRIX_COL_PINS_LEFT_NUMERIC_MAX                 C7, C5, C4, A7, A3, A6, A2, A5, A1, A0, A4, E6
#define MATRIX_COL_PINS_LEFT_HOMING_MAX                      C5, C4, A7, A3, A6, A2, A5, A1, A0, A4, E6
#define MATRIX_COL_PINS_LEFT_NUMERIC_EXTENDED            C7, C5, C4, A7, A3, A6, A2, A5, A1, A0, A4
#define MATRIX_COL_PINS_LEFT_HOMING_EXTENDED                 C5, C4, A7, A3, A6, A2, A5, A1, A0, A4
#define MATRIX_COL_PINS_LEFT_NUMERIC_NORMAL              C7, C5, C4, A7, A3, A6, A2, A5, A1, A0
#define MATRIX_COL_PINS_LEFT_HOMING_NORMAL                   C5, C4, A7, A3, A6, A2, A5, A1, A0

#define MATRIX_COL_PINS_LEFT_NUMERIC_MAX_TEENSY          C1, C0, E1, E0, F3, F2, F1, F0, B0, B1, B2, B3
#define MATRIX_COL_PINS_LEFT_HOMING_MAX_TEENSY               C0, E1, E0, F3, F2, F1, F0, B0, B1, B2, B3
#define MATRIX_COL_PINS_LEFT_NUMERIC_EXTENDED_TEENSY     C1, C0, E1, E0, F3, F2, F1, F0, B0, B1, B2
#define MATRIX_COL_PINS_LEFT_HOMING_EXTENDED_TEENSY          C0, E1, E0, F3, F2, F1, F0, B0, B1, B2
#define MATRIX_COL_PINS_LEFT_NUMERIC_NORMAL_TEENSY       C1, C0, E1, E0, F3, F2, F1, F0, B0, B1
#define MATRIX_COL_PINS_LEFT_HOMING_NORMAL_TEENSY            C0, E1, E0, F3, F2, F1, F0, B0, B1

// Right PCB Pin assignments

#define MATRIX_COL_PINS_RIGHT_ABSENT

#define MATRIX_COL_PINS_RIGHT_NUMERIC_MAX                 E6, A4, A0, A1, A5, A2, A6, A3, A7, C4, C5, C7
#define MATRIX_COL_PINS_RIGHT_HOMING_MAX                  E6, A4, A0, A1, A5, A2, A6, A3, A7, C4, C5
#define MATRIX_COL_PINS_RIGHT_NUMERIC_EXTENDED                A4, A0, A1, A5, A2, A6, A3, A7, C4, C5, C7
#define MATRIX_COL_PINS_RIGHT_HOMING_EXTENDED                 A4, A0, A1, A5, A2, A6, A3, A7, C4, C5
#define MATRIX_COL_PINS_RIGHT_NUMERIC_NORMAL                      A0, A1, A5, A2, A6, A3, A7, C4, C5, C7
#define MATRIX_COL_PINS_RIGHT_HOMING_NORMAL                       A0, A1, A5, A2, A6, A3, A7, C4, C5

#define MATRIX_COL_PINS_RIGHT_NUMERIC_MAX_TEENSY          B3, B2, B1, B0, F0, F1, F2, F3, E0, E1, C0, C1
#define MATRIX_COL_PINS_RIGHT_HOMING_MAX_TEENSY           B3, B2, B1, B0, F0, F1, F2, F3, E0, E1, C0
#define MATRIX_COL_PINS_RIGHT_NUMERIC_EXTENDED_TEENSY         B2, B1, B0, F0, F1, F2, F3, E0, E1, C0, C1
#define MATRIX_COL_PINS_RIGHT_HOMING_EXTENDED_TEENSY          B2, B1, B0, F0, F1, F2, F3, E0, E1, C0
#define MATRIX_COL_PINS_RIGHT_NUMERIC_NORMAL_TEENSY               B1, B0, F0, F1, F2, F3, E0, E1, C0, C1
#define MATRIX_COL_PINS_RIGHT_HOMING_NORMAL_TEENSY                B1, B0, F0, F1, F2, F3, E0, E1, C0

// Fetch Macros

#define GET_PID(LEFT_TYPE, RIGHT_TYPE) ( ( ( MATRIX_TYPE_ ## LEFT_TYPE ) << 8 ) + ( MATRIX_TYPE_ ## RIGHT_TYPE ) )
#define GET_MATRIX_COL(TYPE) MATRIX_COLS_ ## TYPE
#define GET_MATRIX_COLS(LEFT_TYPE, RIGHT_TYPE) ( ( GET_MATRIX_COL(LEFT_TYPE) ) + ( GET_MATRIX_COL(RIGHT_TYPE) ) )
#define GET_MATRIX_COL_PINS(LEFT_TYPE, RIGHT_TYPE) { MATRIX_COL_PINS_LEFT_ ## LEFT_TYPE, MATRIX_COL_PINS_RIGHT_ ## RIGHT_TYPE }

// Specialized Row Macros

#define LAYOUT_ROW_LEFT_ABSENT(                   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)

#define LAYOUT_ROW_LEFT_NUMERIC_MAX(              k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C
#define LAYOUT_ROW_LEFT_HOMING_MAX(               k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)        k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C
#define LAYOUT_ROW_LEFT_NUMERIC_EXTENDED(         k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B
#define LAYOUT_ROW_LEFT_HOMING_EXTENDED(          k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)        k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B
#define LAYOUT_ROW_LEFT_NUMERIC_NORMAL(           k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A
#define LAYOUT_ROW_LEFT_HOMING_NORMAL(            k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)        k02, k03, k04, k05, k06, k07, k08, k09, k0A
#define LAYOUT_ROW_LEFT_NUMERIC_MAX_TEENSY(       k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C
#define LAYOUT_ROW_LEFT_HOMING_MAX_TEENSY(        k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)        k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C
#define LAYOUT_ROW_LEFT_NUMERIC_EXTENDED_TEENSY(  k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B
#define LAYOUT_ROW_LEFT_HOMING_EXTENDED_TEENSY(   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)        k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B
#define LAYOUT_ROW_LEFT_NUMERIC_NORMAL_TEENSY(    k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A
#define LAYOUT_ROW_LEFT_HOMING_NORMAL_TEENSY(     k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)        k02, k03, k04, k05, k06, k07, k08, k09, k0A

#define LAYOUT_ROW_RIGHT_ABSENT(                  k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)

#define LAYOUT_ROW_RIGHT_NUMERIC_MAX(             k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C
#define LAYOUT_ROW_RIGHT_HOMING_MAX(              k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B
#define LAYOUT_ROW_RIGHT_NUMERIC_EXTENDED(        k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)        k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C
#define LAYOUT_ROW_RIGHT_HOMING_EXTENDED(         k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)        k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B
#define LAYOUT_ROW_RIGHT_NUMERIC_NORMAL(          k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)             k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C
#define LAYOUT_ROW_RIGHT_HOMING_NORMAL(           k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)             k03, k04, k05, k06, k07, k08, k09, k0A, k0B
#define LAYOUT_ROW_RIGHT_NUMERIC_MAX_TEENSY(      k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C
#define LAYOUT_ROW_RIGHT_HOMING_MAX_TEENSY(       k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B
#define LAYOUT_ROW_RIGHT_NUMERIC_EXTENDED_TEENSY( k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)        k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C
#define LAYOUT_ROW_RIGHT_HOMING_EXTENDED_TEENSY(  k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)        k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B
#define LAYOUT_ROW_RIGHT_NUMERIC_NORMAL_TEENSY(   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)             k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C
#define LAYOUT_ROW_RIGHT_HOMING_NORMAL_TEENSY(    k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C)             k03, k04, k05, k06, k07, k08, k09, k0A, k0B

// Changable Row Macro

#define _LAYOUT_ROW( _LEFT_TYPE, _RIGHT_TYPE, \
  k001, k002, k003, k004, k005, k006, k007, k008, k009, k00A, k00B, k00C, k011, k012, k013, k014, k015, k016, k017, k018, k019, k01A, k01B, k01C \
) \
LAYOUT_ROW_LEFT_ ## _LEFT_TYPE(   k001, k002, k003, k004, k005, k006, k007, k008, k009, k00A, k00B, k00C ), \
LAYOUT_ROW_RIGHT_ ## _RIGHT_TYPE( k011, k012, k013, k014, k015, k016, k017, k018, k019, k01A, k01B, k01C )

// Changable Master Macro

#define LAYOUT_MASTER(_MATRIX_LAYER, _LEFT_TYPE, _RIGHT_TYPE, \
                                            k001, k002, k003, k004,       k005, k006, k007, k008, k009, k00A, k00B, k00C,       k011, k012, k013, k014, k015, k016, k017, k018,       k019, k01A, k01B, k01C, \
                                            k101, k102, k103, k104,       k105, k106, k107, k108, k109, k10A, k10B, k10C,       k111, k112, k113, k114, k115, k116, k117, k118,       k119, k11A, k11B, k11C, \
                                            k201, k202, k203, k204,       k205, k206, k207, k208, k209, k20A, k20B, k20C,       k211, k212, k213, k214, k215, k216, k217, k218,       k219, k21A, k21B, k21C, \
                                            k301, k302, k303, k304,       k305, k306, k307, k308, k309, k30A, k30B, k30C,       k311, k312, k313, k314, k315, k316, k317, k318,       k319, k31A, k31B, k31C, \
                                            k401, k402, k403, k404,       k405, k406, k407, k408, k409, k40A, k40B, k40C,       k411, k412, k413, k414, k415, k416, k417, k418,       k419, k41A, k41B, k41C, \
                                            k501, k502, k503, k504,       k505, k506, k507, k508, k509, k50A, k50B, k50C,       k511, k512, k513, k514, k515, k516, k517, k518,       k519, k51A, k51B, k51C  \
) \
[_MATRIX_LAYER] = { \
    { _LAYOUT_ROW( _LEFT_TYPE, _RIGHT_TYPE, k001, k002, k003, k004,       k005, k006, k007, k008, k009, k00A, k00B, k00C,       k011, k012, k013, k014, k015, k016, k017, k018,       k019, k01A, k01B, k01C ) },\
    { _LAYOUT_ROW( _LEFT_TYPE, _RIGHT_TYPE, k101, k102, k103, k104,       k105, k106, k107, k108, k109, k10A, k10B, k10C,       k111, k112, k113, k114, k115, k116, k117, k118,       k119, k11A, k11B, k11C ) },\
    { _LAYOUT_ROW( _LEFT_TYPE, _RIGHT_TYPE, k201, k202, k203, k204,       k205, k206, k207, k208, k209, k20A, k20B, k20C,       k211, k212, k213, k214, k215, k216, k217, k218,       k219, k21A, k21B, k21C ) },\
    { _LAYOUT_ROW( _LEFT_TYPE, _RIGHT_TYPE, k301, k302, k303, k304,       k305, k306, k307, k308, k309, k30A, k30B, k30C,       k311, k312, k313, k314, k315, k316, k317, k318,       k319, k31A, k31B, k31C ) },\
    { _LAYOUT_ROW( _LEFT_TYPE, _RIGHT_TYPE, k401, k402, k403, k404,       k405, k406, k407, k408, k409, k40A, k40B, k40C,       k411, k412, k413, k414, k415, k416, k417, k418,       k419, k41A, k41B, k41C ) },\
    { _LAYOUT_ROW( _LEFT_TYPE, _RIGHT_TYPE, k501, k502, k503, k504,       k505, k506, k507, k508, k509, k50A, k50B, k50C,       k511, k512, k513, k514, k515, k516, k517, k518,       k519, k51A, k51B, k51C ) },\
}


#endif // MATRIX_TYPES_H
