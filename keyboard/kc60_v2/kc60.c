#include "kc60.h"

__attribute__ ((weak))
  void matrix_init_user(void) {
    // leave this function blank - it can be defined in a keymap file
  };

__attribute__ ((weak))
  void matrix_scan_user(void) {
    // leave this function blank - it can be defined in a keymap file
  }

__attribute__ ((weak))
  bool process_action_user(keyrecord_t *record) {
    // leave this function blank - it can be defined in a keymap file
    return true;
  }

__attribute__ ((weak))
  void led_set_user(uint8_t usb_led) {
    // leave this function blank - it can be defined in a keymap file
  }

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up

  matrix_init_user();
}

void matrix_scan_kb(void) {
  // put your looping keyboard code here
  // runs every cycle (a lot)

  matrix_scan_user();
}

bool process_action_kb(keyrecord_t *record) {
  // put your per-action keyboard code here
  // runs for every action, just before processing by the firmware

  return process_action_user(record);
}

void led_set_kb(uint8_t usb_led) {
  // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

  led_set_user(usb_led);
}

#ifdef BACKLIGHT_ENABLE

#define DEFAULT_ACCURACY  256
#define PWM_LED_TIMER_TOP F_CPU/(256*64)

static const uint8_t breathing_table[][256] PROGMEM = {{0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,17,18,20,21,23,25,27,29,31,33,35,37,40,42,44,47,49,52,54,57,59,62,65,67,70,73,76,79,82,85,88,90,93,97,100,103,106,109,112,115,118,121,124,127,131,134,137,140,143,146,149,152,155,158,162,165,167,170,173,176,179,182,185,188,190,193,196,198,201,203,206,208,211,213,215,218,220,222,224,226,228,230,232,234,235,237,238,240,241,243,244,245,246,248,249,250,250,251,252,253,253,254,254,254,255,255,255,255,255,255,255,254,254,254,253,253,252,251,250,250,249,248,246,245,244,243,241,240,238,237,235,234,232,230,228,226,224,222,220,218,215,213,211,208,206,203,201,198,196,193,190,188,185,182,179,176,173,170,167,165,162,158,155,152,149,146,143,140,137,134,131,128,124,121,118,115,112,109,106,103,100,97,93,90,88,85,82,79,76,73,70,67,65,62,59,57,54,52,49,47,44,42,40,37,35,33,31,29,27,25,23,21,20,18,17,15,14,12,11,10,9,7,6,5,5,4,3,2,2,1,1,1,0,0,0
}};



uint8_t acc = 0;
bool is_init = false;
uint8_t accuracy = 0xff;
uint8_t speed = 1;
uint8_t current_level = 0;
uint8_t duty_cycle = 0;
uint8_t pos = 0;


void pwm_led_init(void)
{
  if(is_init){
    return;
  }
  is_init = true;
  /* Timer1 setup */
  /* CTC mode */
  TCCR1B |= _BV(WGM12);
  /* Clock selelct: clk/1 */
  TCCR1B |= _BV(CS10);
  /* Set TOP value */
  uint8_t sreg = SREG;
  OCR1AH = (PWM_LED_TIMER_TOP>>8)&0xff;
  OCR1AL = PWM_LED_TIMER_TOP&0xff;
  SREG = sreg;
}
void open_led(void)
{
  PORTB |= (1<<6);
}
void close_led(void)
{
  PORTB &= ~(1<<6);
}
void pwm_led_enable(void)
{
  /* Enable Compare Match Interrupt */
  TIMSK1 |= _BV(OCIE1A);
}

void pwm_led_disable(void)
{
  /* Disable Compare Match Interrupt */
  TIMSK1 &= ~_BV(OCIE1A);
}
void pwm_led_toggle(void)
{
  /* Disable Compare Match Interrupt */
  TIMSK1 ^= _BV(OCIE1A);
}
void backlight_set(uint8_t level)
{
  //uart_transmit(level);
  current_level = level;
  DDRB |= (1<<6);
  //PORTB |= (1<<6);
  //pwm_led_init();
  // pwm_led_enable();

  if(level > 0)
  {
    pwm_led_init();
    pwm_led_enable();
  }
  else
  {

    pwm_led_disable();
    close_led();
  }

}


void tick(void)
{
  if(current_level == 1)
  {
    duty_cycle = 85;
  }
  else if(current_level == 2)
  {
    pos++;
    duty_cycle = pgm_read_byte(&breathing_table[0][pos]);
    if(pos >= 0xff){
      pos = 0;
    }
  }
  else if(current_level == 3)
  {
    duty_cycle = 255;
  }
}

ISR(TIMER1_COMPA_vect)
{
  acc++;
  if(acc == accuracy)
  {
    acc=0;
    open_led();
    tick();
  }
  if (acc == duty_cycle) 
  {
    close_led();
  }
}

#endif
