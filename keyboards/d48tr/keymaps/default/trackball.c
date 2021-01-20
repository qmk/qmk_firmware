#include "pointing_device.h"
#include "wait.h"
#include "i2c.h"
#include <print.h>
#include <avr/wdt.h>

//Parameter of trackball sensitivity [ms]
#define DELAY_TIME 24

#define TBcountMAX DELAY_TIME/4

bool mouse_btn1;
bool mouse_btn2;
bool wheel;
bool tb_btn1;
bool tb_btn2;
int tbcount = 0;

enum MOTION_REG_ADDR
{
  MOTION_REG_UP = 0X00,
  MOTION_REG_DOWN,
  MOTION_REG_LEFT,
  MOTION_REG_RIGHT,
  MOTION_REG_CONFIRM,
  MOTION_REG_NUM
};

enum CONFIG_REG_ADDR
{
  CONFIG_REG_VALID = MOTION_REG_NUM,
  CONFIG_REG_I2C_ADDR = CONFIG_REG_VALID + 4,
  CONFIG_REG_I2C_SPEED,
  CONFIG_REG_LED_MODE = CONFIG_REG_I2C_SPEED + 2,
  CONFIG_REG_LED_FLASH_TIME,
  CONFIG_REG_DATA_CLEAR_TIME = CONFIG_REG_LED_FLASH_TIME + 2,
  CONFIG_REG_DATA_READ_TIME = CONFIG_REG_DATA_CLEAR_TIME + 2,
  CONFIG_REG_NUM = CONFIG_REG_DATA_READ_TIME + 2
};

enum LED_MODE
{
  LED_FLASH_1 = 0X00,
  LED_FLASH_2,
  LED_FLASH_TOGGLE,
  LED_FLASH_ALL,
  LED_ALWAYS_ON_1,
  LED_ALWAYS_ON_2, 
  LED_ALWAYS_ON_ALL,
  LED_ALWAYS_OFF,
  LED_BREATHING_1,
  LED_BREATHING_2,
  LED_BREATHING_ALL,
  LED_MOVE_FLASH,
  LED_MODE_NUM
};

uint8_t i_read(uint8_t reg) {
  
  if(i2c_start_write(TRACBALL_ADDR)) {
      goto i2c_error;
  }
  if(i2c_master_write(0x00)){
      goto i2c_error;
  }
  if(i2c_master_write(reg)) {
      goto i2c_error;
  }
  if(i2c_master_write(0x01)){
      goto i2c_error;
  }
  if(i2c_start_read(TRACBALL_ADDR)) {
      goto i2c_error;
  }
  uint8_t data = i2c_master_read(I2C_ACK);
  i2c_master_read(I2C_NACK);
  i2c_master_stop();
  

  return data;

i2c_error:
  println("i2c_error");
  i2c_reset_state();
  return 0;
}

void pointing_device_init(void) {
  i2c_master_init();
  i2c_start_write(TRACBALL_ADDR);
  i2c_master_write(0x01);
  i2c_master_write(CONFIG_REG_VALID);
  i2c_master_write(0);
  i2c_master_write(0);
  i2c_master_write(0);
  i2c_master_write(0);
  i2c_master_stop();

  wait_ms(100);
  i2c_start_write(TRACBALL_ADDR);
  i2c_master_write(0x01);
  i2c_master_write(CONFIG_REG_I2C_SPEED);
  i2c_master_write(0X64);
  i2c_master_write(0X0);
  i2c_master_stop();

  wait_ms(100);
  i2c_start_write(TRACBALL_ADDR);
  i2c_master_write(0x01);
  i2c_master_write(CONFIG_REG_LED_MODE);
  i2c_master_write(0X10);
  i2c_master_stop();	

  wait_ms(100);
  i2c_start_write(TRACBALL_ADDR);
  i2c_master_write(0x01);
  i2c_master_write(CONFIG_REG_LED_FLASH_TIME);
  i2c_master_write(0Xc8);
  i2c_master_write(0);
  i2c_master_stop();

  wait_ms(100);
  i2c_start_write(TRACBALL_ADDR);
  i2c_master_write(0x01);
  i2c_master_write(CONFIG_REG_DATA_CLEAR_TIME);
  i2c_master_write(0X0);
  i2c_master_write(0X0);
  i2c_master_stop();

  wait_ms(100);
  i2c_start_write(TRACBALL_ADDR);
  i2c_master_write(0x01);
  i2c_master_write(CONFIG_REG_DATA_READ_TIME);
  i2c_master_write(0X22);
  i2c_master_write(0X05);
  i2c_master_stop();
	
  wait_ms(1000);

}

uint8_t trackball_read(uint8_t reg) {
  
  if(i2c_start_write(TRACBALL_ADDR)) {
      goto i2c_error;
  }
  if(i2c_master_write(0x00)){
      goto i2c_error;
  }
  if(i2c_master_write(reg)) {
      goto i2c_error;
  }
  if(i2c_master_write(0x01)){
      goto i2c_error;
  }
  if(i2c_start_read(TRACBALL_ADDR)) {
      goto i2c_error;
  }
  uint8_t trackdata = i2c_master_read(I2C_ACK);
  i2c_master_read(I2C_NACK);
  i2c_master_stop();
  

  return trackdata;

i2c_error:
  println("i2c_error");
  i2c_reset_state();
  return 0;
}

void pointing_device_task() {

  report_mouse_t currentReport = pointing_device_get_report();

  if (tbcount == TBcountMAX){
    uint8_t right = trackball_read(MOTION_REG_UP);
    uint8_t left = trackball_read(MOTION_REG_DOWN);
    uint8_t up = trackball_read(MOTION_REG_LEFT);
    uint8_t down = trackball_read(MOTION_REG_RIGHT);
    uint8_t button = trackball_read(MOTION_REG_CONFIRM);

    if (wheel == true){

      currentReport.v = down-up;

    }else{

      //Parameter of trackball sensitivity
      currentReport.x = abs(left-right) * (left-right);
      currentReport.y = abs(up-down) * (up-down);

    }

  	
    //Trackball click action
    if (button == 0x01){
      tb_btn1 = true;   //left click
      //tb_btn2 = true;     //right click

    }
    else {
      tb_btn1 = false;   //left click
      //tb_btn2 = false;     //right click

    }

    if ((mouse_btn1 == true) || (tb_btn1 == true)){
      currentReport.buttons |= MOUSE_BTN1;
    }else{
      currentReport.buttons &= ~MOUSE_BTN1;
    }

    if ((mouse_btn2 == true) || (tb_btn2 == true)){
      currentReport.buttons |= MOUSE_BTN2;
    }else{
      currentReport.buttons &= ~MOUSE_BTN2;
    }

    pointing_device_set_report(currentReport);
    pointing_device_send();
    
    tbcount = 0;
  	
  } else {

    if ((mouse_btn1 == true) || (tb_btn1 == true)){
      currentReport.buttons |= MOUSE_BTN1;
    }else{
      currentReport.buttons &= ~MOUSE_BTN1;
    }

    if ((mouse_btn2 == true) || (tb_btn2 == true)){
      currentReport.buttons |= MOUSE_BTN2;
    }else{
      currentReport.buttons &= ~MOUSE_BTN2;
    }

    pointing_device_set_report(currentReport);
    pointing_device_send();
  }

  wait_ms(4);
  tbcount++;
  
return;

}

void led_mode ( uint8_t led_mode ){
  i2c_start_write(TRACBALL_ADDR);
  i2c_master_write(0x01);
  i2c_master_write(CONFIG_REG_LED_MODE);
  i2c_master_write(led_mode);
  i2c_master_stop();

}
