#define OPENRGB_ZONES_COUNT 1
#define OPENRGB_ZONES { \
    {"Keyboard", OPENRGB_ZONE_TYPE_MATRIX, 105} \
}

#define OPENRGB_MATRIX_COLUMNS 17
#define OPENRGB_MATRIX_ROWS 7
#define OPENRGB_MATRIX_MAP { \
    { 100,  99,  98,  97,  96,  95,  NA,  94,  NA,  93,  92,  91,  90,  89,  88,  87,  86 }, \
    { 101,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  85 }, \
    { 102,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  84 }, \
    { 103,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  NA,  42,  43,  83 }, \
    { 104,  44,  NA,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  82 }, \
    {  NA,  58,  59,  60,  NA,  NA,  NA,  61,  NA,  NA,  NA,  62,  63,  64,  65,  66,  NA }, \
    {  67,  68,  69,  70,  71,  72,  NA,  73,  NA,  74,  75,  76,  77,  78,  79,  80,  81 }  \
}
#define OPENRGB_SWITCH_MATRIX_TO_PHYSICAL_POS_MAP { \
    { NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA }, \
    { NA,  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  NA }, \
    { NA,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  NA }, \
    { NA,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  NA,  43,  44,  NA }, \
    { NA,  45,  NA,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  NA }, \
    { NA,  60,  61,  62,  NA,  NA,  NA,  66,  NA,  NA,  NA,  70,  71,  72,  73,  74,  NA }, \
    { NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA,  NA }  \
}
