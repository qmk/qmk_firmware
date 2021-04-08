#ifndef SOLENOID_H
#define SOLENOID_H

#include <timer.h>


#define SOLENOID_DEFAULT_DWELL 12
#define SOLENOID_MAX_DWELL 100
#define SOLENOID_MIN_DWELL 4
#ifndef SOLENOID_ACTIVE
  #define SOLENOID_ACTIVE false
#endif
#ifndef SOLENOID_PIN
  #define SOLENOID_PIN F6
#endif


bool solenoid_enabled = SOLENOID_ACTIVE;
bool solenoid_on = false;
bool solenoid_buzz = false;
bool solenoid_buzzing = false;
uint16_t solenoid_start = 0;
uint8_t solenoid_dwell = SOLENOID_DEFAULT_DWELL;


void solenoid_buzz_on(void) {
  solenoid_buzz = true;
}

void solenoid_buzz_off(void) {
  solenoid_buzz = false;
}

void solenoid_dwell_minus(void) {
  if (solenoid_dwell > 0) solenoid_dwell--;
}

void solenoid_dwell_plus(void) {
  if (solenoid_dwell < SOLENOID_MAX_DWELL) solenoid_dwell++;
}

void solenoid_toggle(void) {
  solenoid_enabled = !solenoid_enabled;
}

void solenoid_stop(void) {
  writePinLow(SOLENOID_PIN);
  solenoid_on = false;
  solenoid_buzzing = false;
}

void solenoid_fire(void) {
  if (!solenoid_enabled) return;

  if (!solenoid_buzz && solenoid_on) return;
  if (solenoid_buzz && solenoid_buzzing) return;

  solenoid_on = true;
  solenoid_buzzing = true;
  solenoid_start = timer_read();
  writePinHigh(SOLENOID_PIN);
}

void solenoid_check(void) {
  uint16_t elapsed = 0;

  if (!solenoid_on) return;

  elapsed = timer_elapsed(solenoid_start);

  //Check if it's time to finish this solenoid click cycle
  if (elapsed > solenoid_dwell) {
    solenoid_stop();
    return;
  }

  //Check whether to buzz the solenoid on and off
  if (solenoid_buzz) {
    if (elapsed / SOLENOID_MIN_DWELL % 2 == 0){
      if (!solenoid_buzzing) {
        solenoid_buzzing = true;
        writePinHigh(SOLENOID_PIN);
      }
    }
    else {
      if (solenoid_buzzing) {
        solenoid_buzzing = false;
        writePinLow(SOLENOID_PIN);
      }
    }
  }
}

void solenoid_setup(void) {
  setPinOutput(SOLENOID_PIN);
}

#endif
