// Sexy LED animation.

#include "quantum.h"

#define LED_INTERVAL 160
#define LED_RADIUS 6

void dmc12_start(uint32_t color, bool reset);
void dmc12_process(void);
