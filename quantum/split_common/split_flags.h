#ifndef SPLIT_FLAGS_H
#define SPLIT_FLAGS_H

#include <stdbool.h>
#include <stdint.h>

/** 
* Global Flags
**/

//RGB Stuff
extern volatile bool RGB_DIRTY;


//Backlight Stuff
extern volatile bool BACKLIT_DIRTY;

/**
* Global vars
**/

extern volatile const uint8_t SET_TRIES;



#endif