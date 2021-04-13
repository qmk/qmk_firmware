#define OPENRGB_ZONES_COUNT 1
#define OPENRGB_ZONES { \
    {"Keyboard", OPENRGB_ZONE_TYPE_MATRIX, 119} \
}

#define OPENRGB_MATRIX_COLUMNS 20
#define OPENRGB_MATRIX_ROWS 8
#define OPENRGB_MATRIX_MAP { \
    { NO_LED,  103 ,   104  ,  105  ,  NO_LED,   106  ,  107  ,  NO_LED,   108  ,   109  , NO_LED,  110  , 111   , NO_LED,  112  ,  NO_LED,  113  ,   114  ,    115   ,NO_LED}, \
    { NO_LED,  0   ,  NO_LED,    1  ,     2  ,     3  ,    4  ,     5  ,     6  ,     7  ,    8  ,    9  ,  10   ,   11  ,   12  ,  NO_LED,   13  ,    14  ,     15   ,NO_LED}, \
    { NO_LED,  16  ,   17   ,   18  ,    19  ,    20  ,   21  ,    22  ,    23  ,    24  ,   25  ,   26  ,  27   ,   28  ,   29  ,  NO_LED,   30  ,    31  ,     32   ,NO_LED}, \
    { 102   ,  33  ,   34   ,   35  ,    36  ,    37  ,   38  ,    39  ,    40  ,    41  ,   42  ,   43  ,  44   ,   45  ,   46  ,  NO_LED,   47  ,    48  ,     49   ,116   }, \
    { 101   ,  50  ,  NO_LED,   51  ,    52  ,    53  ,   54  ,    55  ,    56  ,    57  ,   58  ,   59  ,  60   ,   61  ,   62  ,  NO_LED, NO_LED,  NO_LED,   NO_LED ,117   }, \
    { 100   ,  63  ,  NO_LED,   64  ,    65  ,    66  ,   67  ,    68  ,    69  ,    70  ,   71  ,   72  ,  73   ,   74  , NO_LED,  NO_LED, NO_LED,    75  ,   NO_LED ,118   }, \
    { NO_LED,  76  ,    77  ,   78  ,  NO_LED,  NO_LED, NO_LED,    79  ,  NO_LED,  NO_LED, NO_LED,   80  ,  81   ,   82  ,   83  ,  NO_LED,   84  ,    85  ,     86   ,NO_LED}, \
    { NO_LED,  99  ,    98  ,   97  ,  NO_LED,    96  ,   95  ,  NO_LED,    94  ,    93  , NO_LED,   92  ,  91   , NO_LED,   90  ,  NO_LED,   89  ,    88  ,     87   ,NO_LED}  \
}
#define OPENRGB_SWITCH_MATRIX_TO_PHYSICAL_POS_MAP { \
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,  NO_LED, NO_LED, NO_LED,  NO_LED,  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED }, \
    { NO_LED,   0   , NO_LED,    1  ,    2  ,     3  ,    4  ,   5   ,     6  ,     7  ,   48  ,  49   ,   50  ,   51  ,   52  , NO_LED,    53  ,    54  ,    55  ,  NO_LED }, \
    { NO_LED,   8   ,    9  ,   10  ,   11  ,    12  ,   13  ,  14   ,    15  ,    56  ,   57  ,  58   ,   59  ,   60  ,   61  , NO_LED,    62  ,    63  ,    79  ,  NO_LED }, \
    { NO_LED,   16  ,   17  ,   18  ,   19  ,    20  ,   21  ,  22   ,    23  ,    64  ,   65  ,  66   ,   67  ,   68  ,   69  , NO_LED,    70  ,    71  ,    78  ,  NO_LED }, \
    { NO_LED,   24  , NO_LED,   25  ,   26  ,    27  ,   28  ,  29   ,    30  ,    31  ,   72  ,  73   ,   74  ,   75  ,   76  , NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED }, \
    { NO_LED,   32  , NO_LED,   33  ,   34  ,    35  ,   36  ,  37   ,    38  ,    39  ,   80  ,  81   ,   82  ,   83  , NO_LED, NO_LED,  NO_LED,   77   ,  NO_LED,  NO_LED }, \
    { NO_LED,   40  ,   41  ,   42  , NO_LED,  NO_LED, NO_LED,  43   ,  NO_LED,  NO_LED, NO_LED,  44   ,   45  ,   46  ,   47  , NO_LED,    84  ,   85   ,    86  ,  NO_LED }, \
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,  NO_LED, NO_LED, NO_LED,  NO_LED,  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED }  \
}
