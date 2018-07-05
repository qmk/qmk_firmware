#include "ch.h"
#include "hal.h"

static PWMConfig pwmcfg = {
   200000,
   1000,
   NULL,
   {
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL}
   },
   0,
   0
};

int main(void) {
   halInit();
   chSysInit();

   palSetPadMode(GPIOE, 8, PAL_MODE_ALTERNATE(2));
   palSetPadMode(GPIOE, 9, PAL_MODE_ALTERNATE(2));

   pwmStart(&PWMD1, &pwmcfg);

   while (1) {
      pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 1000));   // 10% duty cycle
                chThdSleepMilliseconds(2000);
      pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 9000));   // 90% duty cycle
                chThdSleepMilliseconds(2000);
   }

   return 0;
}