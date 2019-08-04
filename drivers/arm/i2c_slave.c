#include "i2c_slave.h"
#include "quantum.h"
#include <string.h>
#include <hal.h>
#include "hal_i2cslave.h"

#ifndef I2C_SLAVE_TIMEOUT
  #define I2C_SLAVE_TIMEOUT 500
#endif

volatile uint8_t i2c_slave_reg[I2C_SLAVE_REG_COUNT];

static const I2CConfig slaveI2Cconfig = {
#ifdef USE_I2CV1
  I2C1_OPMODE,
  I2C1_CLOCK_SPEED,
  I2C1_DUTY_CYCLE,
#else
  STM32_TIMINGR_PRESC(I2C1_TIMINGR_PRESC) |
  STM32_TIMINGR_SCLDEL(I2C1_TIMINGR_SCLDEL) | STM32_TIMINGR_SDADEL(I2C1_TIMINGR_SDADEL) |
  STM32_TIMINGR_SCLH(I2C1_TIMINGR_SCLH)  | STM32_TIMINGR_SCLL(I2C1_TIMINGR_SCLL),
  0,
  0
#endif
};

uint8_t slave_incoming_body[I2C_SLAVE_REG_COUNT] = {0};
uint8_t slave_outgoing_body[I2C_SLAVE_REG_COUNT] = {0};

// Forward declare callback funcs
void slave_catch_error(I2CDriver *i2cp);
void slave_incoming_message_process(I2CDriver * i2cp);
void slave_clear_after_send(I2CDriver *i2cp);

// Response to received messages
I2CSlaveMsg slave_outgoing_message = {
  sizeof(slave_outgoing_body),
  slave_outgoing_body,
  NULL,
  slave_clear_after_send,
  slave_catch_error
};

// Response to received messages
I2CSlaveMsg slave_incoming_message = {
  sizeof(slave_incoming_body),
  slave_incoming_body,
  NULL,
  slave_incoming_message_process,
  slave_catch_error
};

void slave_catch_error(I2CDriver *i2cp) {
  dprintf("i2c slave error:%d\n", i2cp->errors);
}

void slave_clear_after_send(I2CDriver *i2cp) {
  slave_outgoing_message.size = 0; // Clear receive message
}

void slave_incoming_message_process(I2CDriver * i2cp) {
  uint16_t len = i2cSlaveBytes(i2cp);
  uint8_t buffer_address = slave_incoming_body[0];
  if((len == 0) || (buffer_address >= I2C_SLAVE_REG_COUNT)) {
    // bad - we always expect at least an valid address within slave_incoming_body
    return;
  }

  dprintf("i2c slave addr:%d len:%d\n", buffer_address, len);

  bool isWrite = len > 1;
  if (isWrite) {
    uint8_t * addr =  (uint8_t*) &i2c_slave_reg[buffer_address];
    uint8_t * data =  (uint8_t*) &slave_incoming_body[1];
    uint16_t length = len - 1;

    memcpy(addr, data, length);
  } else {
    uint8_t * data =  (uint8_t*) &i2c_slave_reg[buffer_address]; // TODO: casting away volitile is a bit nasty....

    // TODO: somehow get request size instead of the following hacks

    // Hack v1 - sniff the requested offset and bodge a mapping to expected size
    //           this incorrectly couples i2c_slave to split transport
    // uint16_t length = 0;
    // if(buffer_address == 0) {
    //   #define ROWS_PER_HAND (MATRIX_ROWS / 2)
    //   //matrix_row_t smatrix[ROWS_PER_HAND];
    //   //length = sizeof(smatrix);
    //   length = sizeof(matrix_row_t) * ROWS_PER_HAND;
    // }

    // Hack v2 - very inefficiently just return the rest of the buffer
    //           ARM i2c_master seems to be happy enough getting extra data...
    uint16_t length = sizeof(i2c_slave_reg) - (buffer_address * sizeof(i2c_slave_reg[0]));

    dprintf("i2c slave read len:%d\n", length);

    memcpy(slave_outgoing_body, data, length);
    slave_outgoing_message.size = length;

    i2cSlaveReplyI(i2cp, &slave_outgoing_message);
  }
}

void i2c_slave_init(uint8_t address) {
  // Try releasing special pins for a short time
  palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_INPUT);
  palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_INPUT);

  chThdSleepMilliseconds(10);

#ifdef USE_I2CV1
  palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
  palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
#else
  palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_ALTERNATE(I2C1_SCL_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
  palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_ALTERNATE(I2C1_SDA_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
#endif

  i2cStart(&I2CD1, &slaveI2Cconfig);

  I2CD1.slaveTimeout = MS2ST(I2C_SLAVE_TIMEOUT);
  i2cSlaveConfigure(&I2CD1, &slave_incoming_message, &slave_outgoing_message);
  i2cMatchAddress(&I2CD1, (address >> 1));
}

void i2c_slave_stop(void){
  i2cUnmatchAll(&I2CD1);
  i2cStop(&I2CD1);
}