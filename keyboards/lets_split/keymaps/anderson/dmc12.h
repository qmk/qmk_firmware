// Sexy LED animation.
#include "lets_split.h"

#define LED_INTERVAL 100
#define LED_RADIUS 5

uint32_t dmc12_color;
uint16_t dmc12_timer;
int8_t dmc12_current;
uint8_t dmc12_direction;

void dmc12_start(uint32_t color);
void dmc12_process(void);

