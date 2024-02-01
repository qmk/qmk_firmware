#include "melody96rgb.h"
#ifdef RGB_MATRIX_ENABLE

#define XX NO_LED
led_config_t g_led_config = {  
    {
        // Key Matrix to LED Index
        {0,  1,   2,  3,  4,  5,  6,  7,  8},
		{9,  XX, 10, 11, 12, 13, 14, 15, 16},
		{17, 18, 19, 20, 21, 22, 23, 24, 25},
		{26, 27, 28, 29, 30, 31, 32, 33, 34}, 
		{35, 36, 37, 38, 39, 40, 41, 42, 43},
		{44, 45, 46, 47, 48, 49, 50, 51, 52},
		{53, 54, 55, 56, 57, XX, 58, XX, XX},
		{XX, 59, 60, 61, 62, 63, 64, 65, 66},
		{67, 68, 69, XX, 70, 71, 72, 73, 74},
		{XX, 75, 76, 77, 78, 79, 80, 81, 82},
		{83, 84, 85, XX, 86, 87, 88, 89, 90},
		{91, 92, 93, 94, 95, 96, 97, 98, 99},
       
    },
    {
        // LED Index to Physical Position
 
        {1, 1},   {12, 1},   {24, 1},   {37, 1},   {49, 1},   {61, 1},   {73, 1},   {85, 1},   {97, 1},    {109, 1},   {123, 1},   {136, 1},   {148, 1},  {160, 1},  {172, 1},   {184, 1},   {196, 1},   {210, 1},   {224, 1},                                 // row0
        {1, 13},  {14, 13},  {25, 13},  {38, 13},  {50, 13},  {63, 13},  {75, 13},  {88, 13},  {100, 13},  {113, 13},  {125, 13},  {138, 13},  {150, 13},    {166, 13},          {184, 13},  {196, 13},  {210, 13},  {224, 13},                                       // row1
        {5, 25},  {18, 25},  {30, 25},  {43, 25},  {55, 25},  {68, 25},  {80, 25},  {93, 25},  {105, 25},  {118, 25},  {130, 25},  {143, 25},  {155, 25},    {169, 25},           {187, 25}, {199, 25},  {211, 25},  {224, 31},               // row2
        {8, 37},  {24, 37},  {36, 37},  {49, 37},  {61, 37},  {74, 37},  {86, 37},  {99, 37},  {111, 37},  {124, 37},  {136, 37},  {155, 37},        {167, 37},                    {187, 37},  {199, 37},  {211, 37},                                                                                                                                                                                             // row3
        {10, 49}, {24, 49},  {36, 49},  {49, 49},  {61, 49},  {74, 49},  {86, 49},  {99, 49},  {111, 49},  {124, 49},  {136, 49},  {155, 49},        {170, 49},                    {187, 49},  {199, 49},  {211, 49}, {224, 55},                                                                                                                                                                                      // row4
        {2, 60},  {28, 60},  {31, 60},  {80, 60},  {120, 60}, {138, 60}, {154, 60},  {170, 63},  {183, 63},  {195, 63},  {211, 60},  {211, 60},
        {2, 1}, {15, 1},  {25, 1},  {38, 1},  {52, 1},  {65, 1}, {78, 1}, {92, 1}, {105, 1}, {119, 1},  {132, 1}, {145, 1}, {158, 1}, {172, 1},  {185,1}, {198, 1}, {211, 1},  {224, 1},// Last 18 for backlight.
     },   

    {
                                           //
        4, 4, 4, 4, 4, 4, 4, 4, 4, 
        4, 4, 4, 4, 4, 4, 4, 4,     //
        4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 
        4, 4, 4, 4, 4, 4, 4, 4, 4,         //
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4,    //             
        4, 4, 4, 4, 4, 4, 4, 4, 
        4, 4, 4, 4, 4, 4, 4, 4,        //
        4, 4, 4, 4, 4, 4, 4, 4, 
        4, 4, 4, 4, 4, 4, 4, 4, 4,           //
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,2, 2,

    }};

#endif
