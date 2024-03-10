#include "action.h"
#include "left.h"
#include "wait.h"

bool i2c_initialized = false;

void left_config(void);
i2c_status_t left_write(uint8_t reg, uint8_t data);
i2c_status_t left_read(uint8_t reg, uint8_t *data);

uint8_t init_mcp23017(void)
{
    i2c_initialized = false;

    if (i2c_initialized == 0)
    {
        i2c_init();  // on pins D(1,0)
        _delay_ms(1000);
    }

    return 0;
}
void left_init(void)
{
    init_mcp23017();
    left_scan();
#if 0
    while (1)
    {
        print("wait\n");
        wait_us(1000000);
    }
#endif
}

void left_scan(void)
{
    
    i2c_status_t ret = i2c_ping_address(I2C_ADDR, HOTDOX_I2C_TIMEOUT);

    if (ret == I2C_STATUS_SUCCESS)
    {
        if (!i2c_initialized)
        {
            i2c_initialized = true;
            left_config();
            clear_keyboard();
            print("mcp23017 attached!!!\n");
        }
    }
    else
    {
        if (i2c_initialized)
        {
            i2c_initialized = false;
            clear_keyboard();
            print("mcp23017 deattached!!!\n");
        }
    }

    return;
}

uint8_t left_read_cols(void)
{
    uint8_t data = 0;

    left_read(MCP23017_B0_GPIOA, &data);

    return data;
}

void left_unselect_rows(void)
{
    left_write(MCP23017_B0_IODIRB, 0x3F);
}

void left_select_row(uint8_t row)
{
    left_write(MCP23017_B0_IODIRB, ~(1 << row));
}

void left_config(void)
{
  left_write(MCP23017_B0_IODIRA, 0x7F);
  left_write(MCP23017_B0_IPOLA,  0x7F);
  left_write(MCP23017_B0_GPPUA,  0x7F);

  left_write(MCP23017_B0_IODIRB, 0xFF);
  left_write(MCP23017_B0_GPIOB,  0xC0);
}

i2c_status_t left_write(uint8_t reg, uint8_t data)
{
  if (!i2c_initialized)
  {
    return 0;
  }

  i2c_status_t ret;

  ret = i2c_writeReg(I2C_ADDR, reg,  &data, sizeof(data), HOTDOX_I2C_TIMEOUT); 

  return ret;
}

i2c_status_t left_read(uint8_t reg, uint8_t *data)
{
  if (!i2c_initialized)
  {
    return 0;
  }

  i2c_status_t ret = 0;
  ret = i2c_readReg(I2C_ADDR, reg, data, 1, HOTDOX_I2C_TIMEOUT);

  return ret;
}
