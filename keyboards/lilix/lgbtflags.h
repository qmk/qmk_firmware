//custom LGBT+ flags for backlight LEDs
#ifdef RGBLIGHT_ENABLE

//Define variables for LGBT flags
static uint8_t LGBT_flag_tracker = 0;
static uint8_t LGBT_flags_total = 3;  // Put the total number of enabled flags here


//Rainbow LGBT+ pride flag
#define LGBT_FLAGS_PRIDE

//Gender flags
//#define LGBT_FLAGS_TRANSGENDER
//#define LGBT_FLAGS_NON_BINARY
#define LGBT_FLAGS_NON_BINARY_VERTICAL
//#define LGBT_FLAGS_AGENDER
//#define LGBT_FLAGS_GENDERFLUID
//#define LGBT_FLAGS_GENDERQUEER
#define LGBT_FLAGS_DEMIBOY
//#define LGBT_FLAGS_DEMIGIRL

//Sexuality
//#define LGBT_FLAGS_ACE
//#define LGBT_FLAGS_PAN
//#define LGBT_FLAGS_POLY
//#define LGBT_FLAGS_LESBIAN
//#define LGBT_FLAGS_BI



#ifdef LGBT_FLAGS_PRIDE
const rgblight_segment_t PROGMEM lgbt_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {5,  2, HSV_PURPLE},                      {17, 2, HSV_PURPLE},                      {31, 1, HSV_PURPLE},
    {4,  1, HSV_BLUE},   {7,  1, HSV_BLUE},   {16, 1, HSV_BLUE},   {19, 1, HSV_BLUE},   {30, 1, HSV_BLUE},
    {3,  1, HSV_GREEN},  {8,  1, HSV_GREEN},  {15, 1, HSV_GREEN},  {20, 1, HSV_GREEN},  {29, 1, HSV_GREEN},
    {2,  1, HSV_YELLOW}, {9,  1, HSV_YELLOW}, {14, 1, HSV_YELLOW}, {21, 1, HSV_YELLOW}, {28, 1, HSV_YELLOW},
    {1,  1, HSV_ORANGE}, {10, 1, HSV_ORANGE}, {13, 1, HSV_ORANGE}, {22, 1, HSV_ORANGE}, {27, 1, HSV_ORANGE},
    {0,  1, HSV_RED},    {11, 2, HSV_RED},                         {23, 1, HSV_RED},    {26, 1, HSV_RED},
                                                                   {24, 2, 0, 0, 0}
);
#endif


// Gender flags
#ifdef LGBT_FLAGS_TRANSGENDER
const rgblight_segment_t PROGMEM trans_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,  6, 128, 200, 255}, //hsv blue
    {6,  6, 220, 200, 255}, //hsv pink
    {12, 6, HSV_WHITE},
    {18, 7, 220, 200, 255}, //hsv pink
    {25, 7, 128, 200, 255}  //hsv blue
);
#endif


#ifdef LGBT_FLAGS_NON_BINARY
const rgblight_segment_t PROGMEM enby_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, 0, 0, 0},    //18..25 should stay off (black)
    {6,  6, HSV_ORANGE},
    {12, 6, HSV_WHITE},
    {18, 6, HSV_PURPLE},
    {25, 7, 0, 0, 0}    //18..25 should stay off (black)
    /*{25, 1, HSV_ORANGE},
    {26, 1, HSV_WHITE},
    {27, 1, HSV_PURPLE},
    {28, 1, 0, 0, 0},
    {29, 1, HSV_PURPLE},
    {30, 1, HSV_WHITE},
    {31, 1, HSV_ORANGE}*/
);
#endif


#ifdef LGBT_FLAGS_NON_BINARY_VERTICAL
const rgblight_segment_t PROGMEM vert_enby_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {4,  2, HSV_ORANGE}, {6,  2, HSV_ORANGE}, {16, 2, HSV_ORANGE}, {18, 2, HSV_ORANGE}, {30, 2, HSV_ORANGE},
    {2,  2, HSV_WHITE},  {8,  2, HSV_WHITE},  {14, 2, HSV_WHITE},  {20, 2, HSV_WHITE},  {28, 2, HSV_WHITE},
    {0,  2, HSV_PURPLE}, {10, 2, HSV_PURPLE}, {12, 2, HSV_PURPLE}, {22, 2, HSV_PURPLE}, {26, 2, HSV_PURPLE},
                                                                   {24, 2, 0, 0, 0}
);
#endif


#ifdef LGBT_FLAGS_GENDERFLUID
const rgblight_segment_t PROGMEM genderfluid_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,  6, 220, 240, 255}, //hsv pink
    {6,  6, HSV_WHITE},
    {12, 6, 186, 255, 255}, // hsv purple/magenta
    {18, 7, 0, 0, 0},       // black (off)
    {25, 7, 170, 250, 255}  //hsv blue
);
#endif


#ifdef LGBT_FLAGS_AGENDER
const rgblight_segment_t PROGMEM vert_split_agender_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {4,  2, 0, 0, 20},     {6,  2, 0, 0, 20},     {16, 2, 0, 0, 20},     {18, 2, 0, 0, 20},     {30, 2, 0, 0, 20},
    {2,  2, 0, 0, 255},    {8,  2, 0, 0, 255},    {14, 2, 0, 0, 255},    {20, 2, 0, 0, 255},    {28, 2, 0, 0, 255},
    {0,  2, 68, 200, 255}, {10, 2, 68, 200, 255}, {12, 2, 68, 200, 255}, {22, 2, 68, 200, 255}, {26, 2, 68, 200, 255},
                                                                         {24, 2, 0, 0, 0}
);
#endif


#ifdef LGBT_FLAGS_GENDERQUEER
const rgblight_segment_t PROGMEM vert_genderqueer_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {4,  2, 186, 200, 255}, {6,  2, 186, 200, 255}, {16, 2, 186, 200, 255}, {18, 2, 186, 200, 255}, {30, 2, 186, 200, 255},
    {2,  2, 0, 0, 255},     {8,  2, 0, 0, 255},     {14, 2, 0, 0, 255},     {20, 2, 0, 0, 255},     {28, 2, 0, 0, 255},
    {0,  2, 78, 240, 255},  {10, 2, 78, 240, 255},  {12, 2, 78, 240, 255},  {22, 2, 78, 240, 255},  {26, 2, 78, 240, 255},
                                                                            {24, 2, 0, 0, 0}
);
#endif


#ifdef LGBT_FLAGS_DEMIBOY
const rgblight_segment_t PROGMEM vert_split_demiboy_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {4,  2, 0, 0, 4},       {6,  2, 0, 0, 4},       {16, 2, 0, 0, 4},       {18, 2, 0, 0, 4},       {30, 2, 0, 0, 4},
    {2,  2, 0, 0, 32},      {8,  2, 0, 0, 32},      {14, 2, 0, 0, 32},      {20, 2, 0, 0, 32},      {28, 2, 0, 0, 32},
    {0,  2, 128, 200, 255}, {10, 2, 128, 200, 255}, {12, 2, 128, 200, 255}, {22, 2, 128, 200, 255}, {26, 2, 128, 200, 255},
                                                                            {24, 2, 0, 0, 128}
);
#endif


#ifdef LGBT_FLAGS_DEMIGIRL
const rgblight_segment_t PROGMEM vert_split_demigirl_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {4,  2, 0, 0, 4},       {6,  2, 0, 0, 4},       {16, 2, 0, 0, 4},       {18, 2, 0, 0, 4},       {30, 2, 0, 0, 4},
    {2,  2, 0, 0, 32},      {8,  2, 0, 0, 32},      {14, 2, 0, 0, 32},      {20, 2, 0, 0, 32},      {28, 2, 0, 0, 32},
    {0,  2, 228, 200, 255}, {10, 2, 228, 200, 255}, {12, 2, 228, 200, 255}, {22, 2, 228, 200, 255}, {26, 2, 228, 200, 255},
                                                                            {24, 2, 0, 0, 128}
);
#endif


#ifdef LGBT_FLAGS_ACE
const rgblight_segment_t PROGMEM vert_ace_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {4,  2, 0, 0, 20},      {6,  2, 0, 0, 20},      {16, 2, 0, 0, 20},      {18, 2, 0, 0, 20},      {30, 2, 0, 0, 20},
    {2,  2, 0, 0, 255},     {8,  2, 0, 0, 255},     {14, 2, 0, 0, 255},     {20, 2, 0, 0, 255},     {28, 2, 0, 0, 255},
    {0,  2, 186, 255, 200}, {10, 2, 186, 255, 200}, {12, 2, 186, 255, 200}, {22, 2, 186, 255, 200}, {26, 2, 186, 255, 200},
                                                                            {24, 2, 0, 0, 0}
);
#endif


// Sexuality flags
#ifdef LGBT_FLAGS_PAN
const rgblight_segment_t PROGMEM pan_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {4,  2, HSV_CYAN},    {6,  2, HSV_CYAN},    {16, 2, HSV_CYAN},    {18, 2, HSV_CYAN},    {30, 2, HSV_CYAN},
    {2,  2, HSV_GOLD},    {8,  2, HSV_GOLD},    {14, 2, HSV_GOLD},    {20, 2, HSV_GOLD},    {28, 2, HSV_GOLD},
    {0,  2, HSV_MAGENTA}, {10, 2, HSV_MAGENTA}, {12, 2, HSV_MAGENTA}, {22, 2, HSV_MAGENTA}, {26, 2, HSV_MAGENTA},
                                                                      {24, 2, 0, 0, 0}
);
#endif

// Sexuality flags
#ifdef LGBT_FLAGS_POLY
const rgblight_segment_t PROGMEM poly_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {4,  2, 155, 255, 255}, {6,  2, 155, 255, 255}, {16, 2, 155, 255, 255}, {18, 2, 155, 255, 255}, {30, 2, 155, 255, 255},
    {2,  2, 85, 240, 255},  {8,  2, 85, 240, 255},  {14, 2, 85, 240, 255},  {20, 2, 85, 240, 255},  {28, 2, 85, 240, 255},
    {0,  2, 198, 255, 255}, {10, 2, 198, 255, 255}, {12, 2, 198, 255, 255}, {22, 2, 198, 255, 255}, {26, 2, 198, 255, 255},
                                                                            {24, 2, 0, 0, 0}
);
#endif


#ifdef LGBT_FLAGS_LESBIAN
const rgblight_segment_t PROGMEM five_stripe_lesbian_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,  6, 8, 255, 230},   //hsv orange
    {6,  6, 20, 240, 255},  // hsv light orange
    {12, 6, HSV_WHITE},
    {18, 7, 212, 200, 255}, // hsv light pink
    {25, 7, 238, 255, 230}  // hsv pink
);
#endif


#ifdef LGBT_FLAGS_BI
const rgblight_segment_t PROGMEM bi_flag[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, 201, 255, 230}, //hsv magenta
    {12, 6, 180, 200, 200}, // hsv purple
    {18, 14, 170, 250, 255} // black (off)
);
#endif


// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM lgbt_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    #ifdef LGBT_FLAGS_PRIDE
        lgbt_flag
    #endif

    #ifdef LGBT_FLAGS_TRANSGENDER
        , trans_flag
    #endif
    #ifdef LGBT_FLAGS_NON_BINARY
        , enby_flag
    #endif
    #ifdef LGBT_FLAGS_NON_BINARY_VERTICAL
        , vert_enby_flag
    #endif
    #ifdef LGBT_FLAGS_AGENDER
        , vert_split_agender_flag
    #endif
    #ifdef LGBT_FLAGS_GENDERFLUID
        , genderfluid_flag
    #endif
    #ifdef LGBT_FLAGS_GENDERQUEER
        , vert_genderqueer_flag
    #endif
    #ifdef LGBT_FLAGS_DEMIBOY
        , vert_split_demiboy_flag
    #endif
    #ifdef LGBT_FLAGS_DEMIGIRL
        , vert_split_demigirl_flag
    #endif

    #ifdef LGBT_FLAGS_ACE
        , vert_ace_flag
    #endif
    #ifdef LGBT_FLAGS_PAN
        , pan_flag
    #endif
    #ifdef LGBT_FLAGS_POLY
        , poly_flag
    #endif
    #ifdef LGBT_FLAGS_LESBIAN
        , five_stripe_lesbian_flag
    #endif
    #ifdef LGBT_FLAGS_BI
        , bi_flag
    #endif
);


#endif
