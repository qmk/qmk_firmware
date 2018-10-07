// Rainbow LED colors.
#include "lets_split.h"

#define RAINBOW_INTERVAL 10
#define RAINBOW_SPEED 2
#define RAINBOW_STEP 30

uint32_t rainbow_phase;
uint32_t rainbow_timer;

void rainbow_start(void);
void rainbow_process(void);

