/* Copyright 2020 grid
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


#define wdt_intr_enable_copy(value)   \
__asm__ __volatile__ (  \
    "in __tmp_reg__,__SREG__" "\n\t"    \
    "cli" "\n\t"    \
    "wdr" "\n\t"    \
    "sts %0,%1" "\n\t"  \
    "out __SREG__,__tmp_reg__" "\n\t"   \
    "sts %0,%2" "\n\t" \
    : /* no outputs */  \
    : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)), \
    "r" (_BV(_WD_CHANGE_BIT) | _BV(WDE)), \
    "r" ((uint8_t) ((value & 0x08 ? _WD_PS3_MASK : 0x00) | \
        _BV(WDIE) | (value & 0x07)) ) \
    : "r0"  \
)

#ifdef BLE_ENABLE
#define ENABLE_SLEEP
#define BATTERY_LEVEL
#define LED_CONTROL
// #define FAKE_BAT_LEVEL
#define BAT_LEVEL_STEP_10




#endif

#include "grid_650.h"



// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

bool i2c_initialized = 0;
i2c_status_t mcp23018_status = 0x20;
// bool ble_pwr_on = true;
int batt_level = 50;
 

enum LED_STAT {
  NONE,
  RED_BLINK,
  WHITE_BREATHING,
  WHITE_ON,  
  BLE_ON,
  ORANGE_ON  
};

#ifdef LED_CONTROL
enum LED_STAT curr_stat = NONE;
#endif

void keyboard_pre_init_kb(void) {
  // Call the keyboard pre init code.

    //set orange led(PB7) for low
    setPinOutput(B7);
    writePinLow(B7);

    //set red led(PB5) for low
    setPinOutput(B5);
    writePinLow(B5);
    
    //set solenoid
    setPinOutput(C7);
    writePinLow(C7);
    
    #ifdef BLE_ENABLE
    //enable BLE_PWR(PD5)
    setPinOutput(D5);
    writePinHigh(D5);
    
    //enable BLE_OE(PD2)
    setPinOutput(D2);
    writePinLow(D2);

    //disable MCU_DFU(PC6)
    setPinOutput(C6);
    writePinLow(C6);
    #endif

    //set VBUS DET(PD7) input
    setPinInput(D7);
    // setPinInputLow(D7);

    //set CHG(PD3) input pullup
    setPinInput(D3);
    setPinInputHigh(D3);

    #ifndef BLE_ENABLE
    //set white LED high
    setPinOutput(B6);
    writePinHigh(B6);

    //set orange led low
    setPinOutput(B7);
    writePinLow(B7);


    #endif        

    keyboard_pre_init_user();
}


#ifdef LED_CONTROL

void set_status_led(enum LED_STAT led_stat,enum LED_STAT current_stat){
    static bool red_is_on = false;
    // xprintf("led stat = %d\n",led_stat);
    // xprintf("bklt_level = %d\n",get_backlight_level());
    // xprintf("is_breathing = %d\n",is_breathing());
    // if((led_stat == current_stat) && (led_stat != RED_BLINK)){
    if(led_stat == current_stat){
        //led stats not changed
        //stat not red blink
        //nothing to do

        //if stat is RED_BLINK
        if(led_stat == RED_BLINK){
            if(red_is_on){
                writePinLow(B5);
                red_is_on = false;
            }else{
                writePinHigh(B5);
                red_is_on = true;
            }
        }
        else if(led_stat == WHITE_BREATHING){
            if(is_breathing() && get_backlight_level()){
                //normal nothing to do

            }else{
                breathing_enable();
                backlight_level_noeeprom(1); 
            }
            
        }
        return;
    }else{
        //turn off currnt led
        switch(current_stat){
            case NONE:{
                //start up 
                writePinLow(B5); //set red low
                breathing_disable();
                backlight_level_noeeprom(0); //turn off white
                bluefruit_le_set_mode_leds(0);//turn off ble
            }
            case RED_BLINK:{
                //blink red
                writePinLow(B5); 
                red_is_on = false;

            }break;
            case WHITE_BREATHING:{
                //stop breathing
                //turn off white led
                breathing_disable();
                backlight_level_noeeprom(0);           
            }break;
            case WHITE_ON:{
                //stop breathing
                //turn off white led
                // breathing_disable();
                backlight_level_noeeprom(0);  
            }break;
            case BLE_ON:{
                //turn off ble led
                bluefruit_le_set_mode_leds(0);
            }break;
            case ORANGE_ON:{
                //turn off orange led
                writePinLow(B7); 
            }break;
            default:break;        
        }
        //turn on new led
        switch(led_stat){
            case NONE:{
                writePinLow(B5); 
                breathing_disable();
                backlight_level_noeeprom(0); //turn off white
                bluefruit_le_set_mode_leds(0);//turn off ble
            }break;
            case RED_BLINK:{
                //blink red
                writePinHigh(B5); 
                //how to blink?
                red_is_on = true;

            }break;
            case WHITE_BREATHING:{
                //enable breathing
                breathing_enable();
                backlight_level_noeeprom(1);  
            }break;
            case WHITE_ON:{
                //stop breathing
                //turn on white led
                breathing_disable();
                backlight_level_noeeprom(1);  
            }break;
            case BLE_ON:{
                //turn on ble led
                bluefruit_le_set_mode_leds(1);
            }break;
            case ORANGE_ON:{
                //turn on orange led
                writePinHigh(B7); 
            }break;
            default:break;        
        }
    }
    
}

#endif

#ifdef BLE_ENABLE
uint8_t battery_level(void) {

    // disable adc doesn't really help power consumption?    

    //get three times and get avg

    int16_t adc_raw = analogReadPin(D6);
    int16_t adc_raw1 = analogReadPin(D6);
    int16_t adc_raw2 = analogReadPin(D6);
    int16_t adc_raw3 = analogReadPin(D6);
    int16_t adc_raw4 = analogReadPin(D6);
    // int16_t adc_raw = 900;

    //debug
    // xprintf("adc raw = [ %d, %d, %d, %d, %d ]\n",adc_raw,adc_raw1,adc_raw2,adc_raw3,adc_raw4);    

    adc_raw = (adc_raw+adc_raw1+adc_raw2+adc_raw3+adc_raw4)/5;
    //xprintf("adc avg = %d\n",adc_raw);

    int level;
    // float voltage = adc_raw * 3.3 / 1023; //unit V
    float voltage = adc_raw * 3.3 / 1.023; //unit mV
    //xprintf("voltage = %d mV\n",(int)voltage);
    //linear level
    // level = (voltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE) * 100;
    // if (voltage < MIN_VOLTAGE) level = 0; 
    //battery curve leve
    if(voltage >= BAT_LEVEL_100) {
        int16_t dig1 = ((voltage - BAT_LEVEL_100) / (BAT_LEVEL_110 - BAT_LEVEL_100)) * 10;
        level = 100 + dig1;
        // level = 102; //to refresh the batlevel
    }else if(voltage >= BAT_LEVEL_90){
        int16_t dig1 = ((voltage - BAT_LEVEL_90) / (BAT_LEVEL_100 - BAT_LEVEL_90)) * 10;
        level = 90 + dig1;
    }else if(voltage >= BAT_LEVEL_80){
        int16_t dig1 = ((voltage - BAT_LEVEL_80) / (BAT_LEVEL_90 - BAT_LEVEL_80)) * 10;
        level = 80 + dig1;
    }else if(voltage >= BAT_LEVEL_70){
        int16_t dig1 = ((voltage - BAT_LEVEL_70) / (BAT_LEVEL_80 - BAT_LEVEL_70)) * 10;
        level = 70 + dig1;
    }else if(voltage >= BAT_LEVEL_60){
        int16_t dig1 = ((voltage - BAT_LEVEL_60) / (BAT_LEVEL_70 - BAT_LEVEL_60)) * 10;
        level = 60 + dig1;
    }else if(voltage >= BAT_LEVEL_50){
        int16_t dig1 = ((voltage - BAT_LEVEL_50) / (BAT_LEVEL_60 - BAT_LEVEL_50)) * 10;
        level = 50 + dig1;
    }else if(voltage >= BAT_LEVEL_40){
        int16_t dig1 = ((voltage - BAT_LEVEL_40) / (BAT_LEVEL_50 - BAT_LEVEL_40)) * 10;
        level = 40 + dig1;
    }else if(voltage >= BAT_LEVEL_30){
        int16_t dig1 = ((voltage - BAT_LEVEL_30) / (BAT_LEVEL_40 - BAT_LEVEL_30)) * 10;
        level = 30 + dig1;
    }else if(voltage >= BAT_LEVEL_20){
        int16_t dig1 = ((voltage - BAT_LEVEL_20) / (BAT_LEVEL_30 - BAT_LEVEL_20)) * 10;
        level = 20 + dig1;
    }else if(voltage >= BAT_LEVEL_10){
        int16_t dig1 = ((voltage - BAT_LEVEL_10) / (BAT_LEVEL_20 - BAT_LEVEL_10)) * 10;
        level = 10 + dig1;
    }else if(voltage >= BAT_LEVEL_0){
        int16_t dig1 = ((voltage - BAT_LEVEL_0) / (BAT_LEVEL_10 - BAT_LEVEL_0)) * 10;
        level = dig1;
    }else{
        level = 0;
    }
    
              
    
    // _delay_ms(100);
   
    #ifdef FAKE_BAT_LEVEL
    // fake bat level
    static bool bat_level_dir = false;
    static int8_t fake_bat_Level = 20;
    if(bat_level_dir){
        fake_bat_Level++;
        if(fake_bat_Level>=120) bat_level_dir = false;
    }else{
        fake_bat_Level--;
        if(fake_bat_Level<=-20) bat_level_dir = true;
    }
    level = fake_bat_Level;
    #endif

    //xprintf("Battery Level is %d\n",level);

    #ifdef BAT_LEVEL_STEP_10
    //change bat level step to 10%
    static int curr_bat_level = 50;
    static bool is_first_time = true;
    static bool not_charging = true; //charging state flag

    if(is_first_time || (not_charging != (PIND & 0b00001000))){
        is_first_time = false;
        not_charging = PIND & 0b00001000;
        curr_bat_level = level / 10 * 10;
        //curr_bat_level = level;
    // }else if( (level%10 >= 2) && (level%10 <= 7)){
    }else if( (level%10 >= 4) && (level%10 <= 6)){ //try to make it district to change batlevel 0304

        curr_bat_level = level / 10 * 10;
        //curr_bat_level = level;
    }

    //may junmp from 50% to 100%
    if(not_charging && (PIND & 0b10000000) && (curr_bat_level < 90)){
        //if not charging & usb is pluged & bat_level<90
        //battery is not set or has some problem
        curr_bat_level = 50;
        //xprintf("No Battery\n");
    }

    //xprintf("Battery Level 10 is %d\n",curr_bat_level);
    if (curr_bat_level>=100) curr_bat_level = 100;
    
    return curr_bat_level;

    #endif

    if (voltage > MAX_VOLTAGE) level = 100;
    return level;
}
#endif


void housekeeping_task_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

    #ifdef BLE_ENABLE
    // counter = 1500
    static uint16_t counter = BASIC_CNT - 500;
    #endif
    
    #ifdef ENABLE_SLEEP
    static uint8_t sleep_counter = 0;
    static uint8_t sleep_activated = 0;
    #endif

    
   
    #ifdef BATTERY_LEVEL
    static uint16_t bat_counter = BATTERY_POLL;
    // static uint8_t bat_level[5] = {}; //default bat level 50%
    // static uint8_t bat_level_index = 0;
    // static bool bat_level_buf_ready = 0;
    #endif

    #ifdef BLE_ENABLE
    counter++;
    
    // xprintf("B:%d\n",get_backlight_level());
    // if 1500++ > 20000
    if (counter > BASIC_CNT) {
        // restart counter
        counter = 0;
        #ifdef BATTERY_LEVEL        
        #ifdef ENABLE_SLEEP
        if(sleep_activated == 0) bat_counter++;
        #else
        bat_counter++;
        #endif
        #endif
        #ifdef ENABLE_SLEEP
        if(sleep_activated==0) sleep_counter++;
        //xprintf("Sleep Count = %d\n",sleep_counter);
        #endif
                        

        #ifdef BATTERY_LEVEL
        #ifdef ENABLE_SLEEP
        if(bat_counter >= BATTERY_POLL && sleep_activated == 0){
        #else
        if(bat_counter >= BATTERY_POLL){
        #endif
        // if(bat_counter >= 1){
            bat_counter = 0;
            // bat_level[bat_level_index] = battery_level();
            // xprintf("bat_level[%d] = %d\n",bat_level_index,bat_level[bat_level_index]);
            // bat_level_index++;
            // if(bat_level_index>=5){
            //     bat_level_index = 0;
            //     bat_level_buf_ready = 1;
            // }             
            // if(bat_level_buf_ready){
            //     uint16_t bat_level_sum = 0;
            //     for(uint8_t i=0;i<5;i++){                    
            //         bat_level_sum += bat_level[i]; 
            //     }
            //     xprintf("bat_level_sum is %d\n",bat_level_sum);
            //     bat_level_sum = bat_level_sum/5;
            //     xprintf("AVG bat_level = %d\n",bat_level_sum);
            //     bluefruit_le_send_batlevel(bat_level_sum);
            // }

            //xprintf("send bat level to BT\n");
            batt_level = battery_level();
            #ifdef BLE_BATTERY_REPORT
            bluefruit_le_send_batlevel(batt_level);
            #endif
        }
        #endif

        #ifdef LED_CONTROL

        // static enum LED_STAT curr_stat = NONE;  
        // xprintf("BLE PWR STAT:%d\n",ble_pwr_on);
       
        if((PIND & 0b00001000) == 0){
            //is charging
            //if batlevel over threthold white on
            //if batlevel not over threthold orange on
            set_status_led(ORANGE_ON,curr_stat);
            curr_stat = ORANGE_ON;
        }else{  
            #ifdef ENABLE_SLEEP
            if(sleep_activated){
                //sleeping turn off all leds
                set_status_led(NONE,curr_stat);
                curr_stat = NONE;
            } else 
            #endif
            //not charging                 
            // if((battery_level() <= 15) && ((PIND & 0b10000000) == 0)){
            if((batt_level <= 15) && ((PIND & 0b10000000) == 0)){                
                //if batlevel less than low battery threthold red blink
                //and usb is not connected (in case battery not connected)
                set_status_led(RED_BLINK,curr_stat);
                curr_stat = RED_BLINK;
            }else{
                //else batlevel ok               
                switch(where_to_send()){
                    case OUTPUT_USB: {
                        set_status_led(WHITE_ON,curr_stat);
                        curr_stat = WHITE_ON;                        
                    }break;                        
                    case OUTPUT_BLUETOOTH: {
                        if(bluefruit_le_is_connected()){
                            //ble connected enable white breathing
                            set_status_led(WHITE_BREATHING,curr_stat);
                            curr_stat = WHITE_BREATHING;
                        }else{
                            //ble not connected enable blue blink 
                            set_status_led(BLE_ON,curr_stat);
                            curr_stat = BLE_ON;                            
                        }                              
                    }
                    break;
                    default:break;
                }
            }            
        }
        #endif


    }
    #endif

    #ifdef ENABLE_SLEEP
    if (has_anykey(keyboard_report) || (PIND & 0b10000000)) {
    // if (has_anykey(keyboard_report)) {
        // has key press clr counter
        sleep_counter = 0;
        sleep_activated = 0;
        
        #ifdef ENABLE_DEEP_SLEEP
            ble_on();
        #endif

        // backlight_enable();
        // breathing_enable();
    } else if (sleep_counter <= SLEEP_WAIT) {
        // // always goto IDLE mode to save power
        
    } else if (sleep_counter > SLEEP_WAIT) {
        //when counter is big enough goto POWERDOWN mode
        // sleep_counter = SLEEP_WAIT;
        sleep_activated = 1;

        
        #ifdef ENABLE_DEEP_SLEEP
            ble_off();
        #endif
            // suspend_power_down(); //use qmk provided api not working properly

            // breathing_disable();
            // backlight_disable();     

            set_status_led(NONE,curr_stat);
            curr_stat = NONE;    

            // Watchdog Interrupt Mode
            wdt_intr_enable_copy(WDTO_60MS);

            // cli();
            
            // set_sleep_mode(SLEEP_MODE_IDLE);
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);//power down mode saves better but resets the system
            sleep_enable();
            // sleep_bod_disable(); //try to disable bod reset
            sei();
            
            sleep_cpu();
            sleep_disable();

            // Disable watchdog after sleep
            wdt_disable();
            //must have some delay or reset will occur(40ms is ok)
            wait_ms(10);

        //need to think about how to save energy
        //can key scan interval be changed?       
    }
    #endif

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // put your per-action keyboard code here
    // runs for every action, just before processing by the firmware

    return process_record_user(keycode, record);
}

void led_set_user(uint8_t usb_led) {
  #ifndef BLE_ENABLE

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    //set white led low
    writePinLow(B6);
    //set orange led high
    writePinHigh(B7);
  } else {
    //set orange led low
    writePinLow(B7);
    //set white led high
    writePinHigh(B6);
  }
  #endif
}

void suspend_power_down_kb(void)
{
    #ifndef BLE_ENABLE
    //set white led low
    writePinLow(B6);
    //set orange led low
    writePinLow(B7);
    #endif
}

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    // I2C subsystem

    // uint8_t sreg_prev;
    // sreg_prev=SREG;
    // cli();

    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        wait_ms(1000);
    }
    // i2c_init(); // on pins D(1,0)
    // _delay_ms(1000);

    // set pin direction  (all to input)
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA, I2C_TIMEOUT);            if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111, I2C_TIMEOUT);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111, I2C_TIMEOUT);        if (mcp23018_status) goto out;
    i2c_stop();

    // set pull-up   (all enable pullup)
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA, I2C_TIMEOUT);             if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111, I2C_TIMEOUT);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111, I2C_TIMEOUT);        if (mcp23018_status) goto out;

out:
    i2c_stop();

// #ifdef LEFT_LEDS
//     if (!mcp23018_status) mcp23018_status = ergodox_left_leds_update();
// #endif // LEFT_LEDS

    // SREG=sreg_prev;

    return mcp23018_status;
}