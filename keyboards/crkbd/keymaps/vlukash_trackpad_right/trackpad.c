#include "trackpad.h"

// bool isScrollingMode = false;
bool isScrollMode = false;

void pointing_device_init(void){

  SPI_Init(SPI_SPEED_FCPU_DIV_8 | SPI_MODE_MASTER);

  // Set as output
  TP_RESET_INIT;
  TP_SHUTDOWN_INIT;
  TP_CS_INIT;
  LVL_SHIFT_EN_INIT;

  // Reset level shifter
  LVL_SHIFT_EN_LO;
  wait_ms(100);
  LVL_SHIFT_EN_HI;

  // Force a BB-8520 reset
  TP_RESET_HI;
  wait_ms(100);
  TP_RESET_LO;

  // Turn on BB-8520 trackpad
  TP_SHUTDOWN_LO;

  TP_CS_HI;
}

uint8_t readRegister(uint8_t address) {
  uint8_t data;

  TP_CS_LO;

  // Read the data
  SPI_TransferByte(address);
  data = SPI_TransferByte(0x00);

  TP_CS_HI;

  return data;
}

bool pointing_device_task(void){
  uint8_t motion = readRegister(0x02);

  // Motion has occurred on the trackpad
  if (motion > 127) {

  int8_t dx, dy;

  if(TRACKPAD_CONNECTOR_VER == 1) {
    dx = readRegister(0x03);
    dy = -readRegister(0x04);
  }
  else {
    dy = -readRegister(0x03);
    dx = -readRegister(0x04);
  }

    report_mouse_t currentReport = pointing_device_get_report();
    if (isScrollMode)
    {
      currentReport.h = dx/SCROLL_SPEED_DIVIDER;
      currentReport.v = dy/SCROLL_SPEED_DIVIDER;
    }
    else
    {
      currentReport.x = dx * POINTER_SPEED_MULTIPLIER;
      currentReport.y = dy * POINTER_SPEED_MULTIPLIER;
    }

    pointing_device_set_report(currentReport);
  }
  return pointing_device_send();
}
