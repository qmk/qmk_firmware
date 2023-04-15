#define I2C_DRIVER I2CD0
//using raw pin values, blok converter doesn't catch this
#define I2C0_SDA_PIN 17U
#define I2C0_SCL_PIN 16U
#define I2C0_CLOCK_SPEED  400000

#define SERIAL_USE_MULTI_TRANSACTION
#define SPLIT_MODS_ENABLE
#define SPLIT_TRANSPORT_MIRROR