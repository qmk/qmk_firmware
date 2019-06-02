#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {   0,   1,   2,   3,   4,   5,   6 },
    {   7,   8,   9,  10,  11,  12,  13 },
    {  14,  15,  16,  17,  18,  19,  20 },
    {  21,  22,  23,  24,  25,  26,  27 },
    {  28,  29,  30,  31,  32,  33,  34 },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,  33,  34 },
    {  35,  36,  37,  38,  39,  40,  41 },
    {  42,  43,  44,  45,  46,  47,  48 },
    {  49,  50,  51,  52,  53,  54,  55 },
    {  56,  57,  58,  59,  60,  61,  62 },
    {  63,  64,  65,  66,  67,  68,  68 },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,  68,  68 }
}, {
	// Left Hand Mapped Left to Right
    {   0,   0 }, {  21,   0 }, {  38,   0 }, {  56,   0 }, {  73,   0 }, {  91,   0 }, { 112,   0 },
    {   0,  18 }, {  21,  18 }, {  38,  18 }, {  56,  18 }, {  73,  18 }, {  91,  18 }, { 108,  13 },
    {   0,  35 }, {  21,  35 }, {  38,  35 }, {  56,  35 }, {  73,  35 }, {  91,  35 }, { 108,  31 },
    {   0,  52 }, {  21,  52 }, {  38,  52 }, {  56,  52 }, {  73,  52 }, {  91,  52 }, { 108,  48 },
    {   0,  70 }, {  21,  70 }, {  38,  70 }, {  56,  70 }, {  73,  70 }, {  89,  91 }, { 101, 103 },
	// Left Hand Mapped Right to Left
    { 224,   0 }, { 203,   0 }, { 186,   0 }, { 168,   0 }, { 151,   0 }, { 133,   0 }, { 112,   0 },
    { 224,  18 }, { 203,  18 }, { 186,  18 }, { 168,  18 }, { 151,  18 }, { 133,  18 }, { 116,  13 },
    { 224,  35 }, { 203,  35 }, { 186,  35 }, { 168,  35 }, { 151,  35 }, { 133,  35 }, { 116,  31 },
    { 224,  52 }, { 203,  52 }, { 186,  52 }, { 168,  52 }, { 151,  52 }, { 133,  52 }, { 116,  48 },
    { 224,  70 }, { 203,  70 }, { 186,  70 }, { 168,  70 }, { 151,  70 }, { 135,  91 }, { 123, 103 },
}, {
	// Left Hand Mapped Left to Right
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1,
	// Left Hand Mapped Right to Left
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1
} };

#endif

