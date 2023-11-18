#include "hmc_87.h"
#define XX 255
led_config_t g_led_config = {
	{
        { 0,   XX,   XX,   XX,   XX,   XX,   XX,   XX,   XX,   XX,  XX,  XX,  XX,  XX,  XX,  XX, XX},
        { XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX },
        { XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX },
        { XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX },
        { XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX},
        { XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,   XX,  XX,  XX,  XX,  XX }
   },
   {
        { 12*1,  60},{ 12*0,  60}
        
   },
   {
       1,1
   }
};


void keyboard_pre_init_user(void)
{

}
void rgb_matrix_indicators_kb(void)
{


}

const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {5};
const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {30};
const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {31};
const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {20};
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {20};
