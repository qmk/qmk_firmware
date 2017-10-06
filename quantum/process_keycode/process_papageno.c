/* Copyright 2017 Florian Fleissner
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "process_papageno.h"

#include "quantum.h"
#include "tmk_core/common/action.h"
#include "tmk_core/common/action_tapping.h"

#define PPG_IMMEDIATE_EVENT_PROCESSING

#ifndef PPG_IMMEDIATE_EVENT_PROCESSING
static PPG_Event ppg_qmk_flush_queue[30];
static uint8_t ppg_qmk_flush_queue_end;
#endif

#ifdef PPG_QMK_ERGODOX_EZ
#include "ergodox_ez.h"

typedef struct {
   uint8_t DDRD__;
   uint8_t DDRB__;
   uint8_t PORTD__;
   uint8_t PORTB__;
} Led_Registers;

static Led_Registers led_registers;

#define SAFE_REG(S) led_registers.S##__ = S;
#define RESTORE_REG(S) S = led_registers.S##__;

static void ff_safe_led_state(void)
{
   SAFE_REG(DDRD)
   SAFE_REG(DDRB)
   SAFE_REG(PORTD)
   SAFE_REG(PORTB)
}

static void ff_restore_led_state(void)
{
   RESTORE_REG(DDRD)
   RESTORE_REG(DDRB)
   RESTORE_REG(PORTD)
   RESTORE_REG(PORTB)
}

void ppg_qmk_led_signal(void)
{
   ff_safe_led_state();
   
   wait_ms(100);
   
   ergodox_led_all_on();
   
   wait_ms(100);
   
   ff_restore_led_state();
}

#define FF_LED_FLASH(LED_ID) \
   ergodox_right_led_##LED_ID##_on(); \
   wait_ms(100);  \
   ergodox_right_led_##LED_ID##_off();

void ppg_qmk_led_flash(void)
{
   ff_safe_led_state();
   
   ergodox_led_all_off();
   
   FF_LED_FLASH(1)
   FF_LED_FLASH(2)
   FF_LED_FLASH(3)
   
   ff_restore_led_state();
}

void ppg_qmk_led_superflash(void)
{
   ppg_qmk_led_flash();
   wait_ms(200);
   ppg_qmk_led_flash();
   wait_ms(200);
   ppg_qmk_led_flash();
}

void ppg_qmk_code_key_considered(void)
{
   ff_safe_led_state();
   
   ergodox_led_all_off();
   ergodox_right_led_2_on();
   
   wait_ms(100);
   
   ff_restore_led_state();
}

void ppg_qmk_code_key_flushed(void)
{
   ff_safe_led_state();
   
   ergodox_led_all_off();
   ergodox_right_led_3_on();
   
   wait_ms(100);
   
   ff_restore_led_state();
}

void ppg_qmk_code_key_blocked(void)
{
   ff_safe_led_state();
   
   ergodox_led_all_off();
   ergodox_right_led_1_on();
   
   wait_ms(100);
   
   ff_restore_led_state();
}

#endif // PPG_QMK_ERGODOX_EZ

/* This function is defined in quantum/keymap_common.c 
 */

action_t action_for_configured_keycode(uint16_t keycode);

static void ppg_qmk_enter_keycode(uint16_t keycode, 
                                  bool pressed,
                                  uint16_t time,
                                  bool synthesized
                                 )
{
   /* Construct a dummy record
   */
   keyrecord_t record; 
      record.event.key.row = 0;
      record.event.key.col = 0;
      record.event.pressed = pressed;
      record.event.time = time;
      record.tap.count = 1;
      
   /* Use the quantum/tmk system to trigger the action
      * thereby using a fictituous key (0, 0) with which the action 
      * keycode is associated. We pretend that the respective key
      * was hit and released to make sure that any action that
      * requires both events is correctly processed.
      * Unfortunatelly this means that some actions that
      * require keys to be held do not make sense, e.g.
      * modifier keys or MO(...), etc.
      */
   
//    uprintf("keycode: %d, active: %d\n", keycode, pressed);
   
   uint16_t configured_keycode = keycode_config(keycode);
   
   action_t action = action_for_configured_keycode(configured_keycode); 
   
   process_action(&record, action);
   
//    dprintf("keycode = %d\n", keycode);
}

static void ppg_qmk_flush_event(PPG_Event *event)
{
   #ifdef PPG_QMK_ERGODOX_EZ
   ppg_qmk_code_key_flushed();
   #endif
   
   uint16_t keycode = 0;
   
   int16_t highest_keypos = ppg_qmk_highest_keypos_input();

   // Note: Input-IDs are assigned contiguously
   //
   //       Input ids assigned to keypos-inputs are {0..PPG_Highest_Keypos_Input}
   //       
   //       Input ids assigned to keycode-inputs are {PPG_Highest_Keypos_Input + 1..PPG_Highest_Keycode_Input}

   if(event->input > highest_keypos) {
      
      // Map the input to a range starting from zero to be suitable
      // for lookup in the ppg_qmk_keycode_lookup array
      //
      keycode = ppg_qmk_keycode_lookup[event->input - highest_keypos - 1];
      
      ppg_qmk_enter_keycode(keycode, 
                        event->flags & PPG_Event_Active, 
                        event->time,
                        false /* not synthesized, i.e. already 
                        partially processed by the qmk system */
                     );
   }
   else {
   
      // Keypos input-IDs already start from zero
      //
      keyevent_t k_event = {
         .key = ppg_qmk_keypos_lookup[event->input],
         .pressed = event->flags & PPG_Event_Active,
         .time = event->time
      };
      
      // Let the qmk system process the event just as if it
      // had just been detected during matrix scan
      //
      action_exec(k_event);
   }
}

#ifndef PPG_IMMEDIATE_EVENT_PROCESSING
static void ppg_qmk_delayed_flush_events(void)
{
   if(ppg_qmk_flush_queue_end == 0) { return; }
   
   uint8_t fqe = ppg_qmk_flush_queue_end;
   ppg_qmk_flush_queue_end = 0;
   
   for(uint8_t i = 0; i < fqe; ++i) {

      PPG_Event *event = ppg_qmk_flush_queue + i;
      
      ppg_qmk_flush_event(event);
   }
}
#endif

void ppg_qmk_process_event_callback(   
                              PPG_Event *event,
                              void *user_data)
{
   // Ignore events that were considered
   //
   if(event->flags & PPG_Event_Considered) {
      
      #ifdef PPG_QMK_ERGODOX_EZ
      ppg_qmk_code_key_blocked();
      #endif
      
      return; 
   }
   
   #ifdef PPG_IMMEDIATE_EVENT_PROCESSING
   ppg_qmk_flush_event(event);
   #else
   ppg_qmk_flush_queue[ppg_qmk_flush_queue_end] = *event;
   ++ppg_qmk_flush_queue_end;
   #endif
}

void ppg_qmk_flush_events(void)
{  
   ppg_event_buffer_iterate(
      ppg_qmk_process_event_callback,
      NULL
   );
}

void ppg_qmk_process_keycode(bool activation, void *user_data) {
   
   uint16_t keycode = (uint16_t)user_data;
      
//    uprintf("keycode %u\n", keycode);
   
   if(keycode != 0) {
      
      ppg_qmk_enter_keycode(keycode, 
                            activation, 
                            timer_read(), 
                            true /* is synthesized */);
   }
}

void ppg_qmk_process_event(keyevent_t event)
{   
   uint16_t keycode = keymap_key_to_keycode(layer_switch_get_layer(event.key), event.key);
   
   #define PPG_QMK_INPUT_CHECK_A \
__NL__   ppg_qmk_input_id_from_keypos( \
__NL__                        event.key.row, \
__NL__                        event.key.col)

   #define PPG_QMK_INPUT_CHECK_B \
         ppg_qmk_input_id_from_keycode(keycode)
         
   // The default behavior is to first check it an 
   // input is defined through the keypos of a key.
   // If not then we check the assigned keycode.
   //
   // By defining PPG_QMK_REVERSE_KEYPOS_TO_KEYCODE_PRECEDENCE
   // this order can be reversed.
   //
   #ifndef PPG_QMK_REVERSE_KEYPOS_TO_KEYCODE_PRECEDENCE
      #define PPG_QMK_INPUT_CHECK_1 PPG_QMK_INPUT_CHECK_A
      #define PPG_QMK_INPUT_CHECK_2 PPG_QMK_INPUT_CHECK_B
   #else // PPG_QMK_REVERSE_KEYPOS_TO_KEYCODE_PRECEDENCE
      #define PPG_QMK_INPUT_CHECK_1 PPG_QMK_INPUT_CHECK_B
      #define PPG_QMK_INPUT_CHECK_2 PPG_QMK_INPUT_CHECK_A
   #endif // PPG_QMK_REVERSE_KEYPOS_TO_KEYCODE_PRECEDENCE
         
   uint8_t input = PPG_QMK_INPUT_CHECK_1;
   
   if(input == PPG_QMK_Not_An_Input) { 
      
      input = PPG_QMK_INPUT_CHECK_2;
      
      if(input == PPG_QMK_Not_An_Input) { 
         
         PPG_LOG("not an input\n");

         // Whenever a key occurs that is not an input,
         // we immediately abort pattern matching
         //
         ppg_global_abort_pattern_matching();
         
         // Let qmk process the key in a regular way
         //
         action_exec(event);
         
         return;
      }
      else {
         PPG_LOG("input %u, keycode %d\n", input, keycode);
      }
   }
// else {
//    uprintf("input %u, row %u, col %u\n", input, record->event.key.row, 
//                         record->event.key.col);
//   }
   
   #ifdef PPG_QMK_ERGODOX_EZ
   ppg_qmk_code_key_considered();
   #endif
   
   PPG_Event p_event = {
      .input = input,
      .time = (PPG_Time)event.time,
      .flags = (event.pressed) 
                     ? PPG_Event_Active : PPG_Event_Flags_Empty
   };
   
   uint8_t cur_layer = biton32(layer_state);
   
   ppg_global_set_layer(cur_layer);
   
   ppg_event_process(&p_event);
}

void ppg_qmk_time(PPG_Time *time)
{
   uint16_t time_tmp = timer_read();
   *time = *((PPG_Time*)&time_tmp);
}

void  ppg_qmk_time_difference(PPG_Time time1, PPG_Time time2, PPG_Time *delta)
{
   uint16_t *delta_t = (uint16_t *)delta;
   
   *delta_t = (uint16_t)time2 - (uint16_t)time1; 
}

int8_t ppg_qmk_time_comparison(
                        PPG_Time time1,
                        PPG_Time time2)
{
   if((uint16_t)time1 > (uint16_t)time2) {
      return 1;
   }
   else if((uint16_t)time1 == (uint16_t)time2) {
      return 0;
   }
    
   return -1;
}

void ppg_qmk_signal_callback(PPG_Signal_Id signal_id, void *user_data)
{
//    uprintf("signal %u\n", signal_id  );
   
   switch(signal_id) {
      case PPG_On_Abort:
         ppg_qmk_flush_events();
         break;
      case PPG_On_Timeout:
         ppg_qmk_flush_events();
         break;
      case PPG_On_Match_Failed:
         break;      
      case PPG_On_Flush_Events:
         ppg_qmk_flush_events();
         break;
      default:
         return;
   }
   #ifdef PPG_QMK_ERGODOX_EZ
   ppg_qmk_code_key_blocked();
   #endif
}

// void ppg_qmk_set_timeout_ms(uint16_t timeout)
// {
//    printf("ppg_qmk_set_timeout_ms: %d\n", (int)timeout);
//    ppg_global_set_timeout((PPG_Time)timeout);
// }

void ppg_qmk_matrix_scan(void)
{
   #ifndef PPG_IMMEDIATE_EVENT_PROCESSING
   ppg_qmk_delayed_flush_events();
   #endif
   
   ppg_timeout_check();
}
