// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <hal.h>
#include "i2c_master.h"

#ifndef I2C_MULTI_BUS

#    ifndef I2C1_SCL_PIN
#        define I2C1_SCL_PIN B6
#    endif
#    ifndef I2C1_SDA_PIN
#        define I2C1_SDA_PIN B7
#    endif

#    ifdef USE_I2CV1
#        ifndef I2C1_OPMODE
#            define I2C1_OPMODE OPMODE_I2C
#        endif
#        ifndef I2C1_CLOCK_SPEED
#            define I2C1_CLOCK_SPEED 100000 /* 400000 */
#        endif
#        ifndef I2C1_DUTY_CYCLE
#            define I2C1_DUTY_CYCLE STD_DUTY_CYCLE /* FAST_DUTY_CYCLE_2 */
#        endif
#    else
// The default timing values below configures the I2C clock to 400khz assuming a 72Mhz clock
// For more info : https://www.st.com/en/embedded-software/stsw-stm32126.html
#        ifndef I2C1_TIMINGR_PRESC
#            define I2C1_TIMINGR_PRESC 0U
#        endif
#        ifndef I2C1_TIMINGR_SCLDEL
#            define I2C1_TIMINGR_SCLDEL 7U
#        endif
#        ifndef I2C1_TIMINGR_SDADEL
#            define I2C1_TIMINGR_SDADEL 0U
#        endif
#        ifndef I2C1_TIMINGR_SCLH
#            define I2C1_TIMINGR_SCLH 38U
#        endif
#        ifndef I2C1_TIMINGR_SCLL
#            define I2C1_TIMINGR_SCLL 129U
#        endif
#    endif

#    ifndef I2C_DRIVER
#        define I2C_DRIVER I2CD1
#    endif

#    ifdef USE_GPIOV1
#        ifndef I2C1_SCL_PAL_MODE
#            define I2C1_SCL_PAL_MODE PAL_MODE_ALTERNATE_OPENDRAIN
#        endif
#        ifndef I2C1_SDA_PAL_MODE
#            define I2C1_SDA_PAL_MODE PAL_MODE_ALTERNATE_OPENDRAIN
#        endif
#    else
// The default PAL alternate modes are used to signal that the pins are used for I2C
#        ifndef I2C1_SCL_PAL_MODE
#            define I2C1_SCL_PAL_MODE 4
#        endif
#        ifndef I2C1_SDA_PAL_MODE
#            define I2C1_SDA_PAL_MODE 4
#        endif
#    endif

#    define _I2Cx_DRIVER I2C_DRIVER
#    define _I2Cx_SCL_PIN I2C1_SCL_PIN
#    define _I2Cx_SDA_PIN I2C1_SDA_PIN
#    define _I2Cx_OPMODE I2C1_OPMODE
#    define _I2Cx_CLOCK_SPEED I2C1_CLOCK_SPEED
#    define _I2Cx_DUTY_CYCLE I2C1_DUTY_CYCLE
#    define _I2Cx_TIMINGR_PRESC I2C1_TIMINGR_PRESC
#    define _I2Cx_TIMINGR_SCLDEL I2C1_TIMINGR_SCLDEL
#    define _I2Cx_TIMINGR_SDADEL I2C1_TIMINGR_SDADEL
#    define _I2Cx_TIMINGR_SCLH I2C1_TIMINGR_SCLH
#    define _I2Cx_TIMINGR_SCLL I2C1_TIMINGR_SCLL
#    define _I2Cx_SCL_PAL_MODE I2C1_SCL_PAL_MODE
#    define _I2Cx_SDA_PAL_MODE I2C1_SDA_PAL_MODE

#    define _i2cx_config i2cconfig
#    define _i2cx_epilogue i2c_epilogue
#    define _i2cx_init i2c_init
#    define _i2cx_transmit i2c_transmit
#    define _i2cx_receive i2c_receive
#    define _i2cx_write_register i2c_write_register
#    define _i2cx_write_register16 i2c_write_register16
#    define _i2cx_read_register i2c_read_register
#    define _i2cx_read_register16 i2c_read_register16
#    define _i2cx_ping_address i2c_ping_address

#    include "i2c_master.impl.c"

#else // I2C_MULTI_BUS

// Ensure we aren't overriding I2C APIs with a default bus when we #include the impl
#    undef i2c_init
#    undef i2c_transmit
#    undef i2c_receive
#    undef i2c_write_register
#    undef i2c_write_register16
#    undef i2c_read_register
#    undef i2c_read_register16
#    undef i2c_ping_address

#    ifdef HAS_I2C0

#        undef _i2cx_config
#        undef _i2cx_epilogue
#        undef _i2cx_init
#        undef _i2cx_transmit
#        undef _i2cx_receive
#        undef _i2cx_write_register
#        undef _i2cx_write_register16
#        undef _i2cx_read_register
#        undef _i2cx_read_register16
#        undef _i2cx_ping_address

#        define _i2cx_config i2c0config
#        define _i2cx_epilogue i2c0_epilogue
#        define _i2cx_init i2c0_init
#        define _i2cx_transmit i2c0_transmit
#        define _i2cx_receive i2c0_receive
#        define _i2cx_write_register i2c0_write_register
#        define _i2cx_write_register16 i2c0_write_register16
#        define _i2cx_read_register i2c0_read_register
#        define _i2cx_read_register16 i2c0_read_register16
#        define _i2cx_ping_address i2c0_ping_address

#        undef _I2Cx_DRIVER
#        undef _I2Cx_SCL_PIN
#        undef _I2Cx_SDA_PIN
#        undef _I2Cx_OPMODE
#        undef _I2Cx_CLOCK_SPEED
#        undef _I2Cx_DUTY_CYCLE
#        undef _I2Cx_TIMINGR_PRESC
#        undef _I2Cx_TIMINGR_SCLDEL
#        undef _I2Cx_TIMINGR_SDADEL
#        undef _I2Cx_TIMINGR_SCLH
#        undef _I2Cx_TIMINGR_SCLL
#        undef _I2Cx_SCL_PAL_MODE
#        undef _I2Cx_SDA_PAL_MODE

#        define _I2Cx_DRIVER I2CD0
#        define _I2Cx_SCL_PIN I2C0_SCL_PIN
#        define _I2Cx_SDA_PIN I2C0_SDA_PIN
#        define _I2Cx_OPMODE I2C0_OPMODE
#        define _I2Cx_CLOCK_SPEED I2C0_CLOCK_SPEED
#        define _I2Cx_DUTY_CYCLE I2C0_DUTY_CYCLE
#        define _I2Cx_TIMINGR_PRESC I2C0_TIMINGR_PRESC
#        define _I2Cx_TIMINGR_SCLDEL I2C0_TIMINGR_SCLDEL
#        define _I2Cx_TIMINGR_SDADEL I2C0_TIMINGR_SDADEL
#        define _I2Cx_TIMINGR_SCLH I2C0_TIMINGR_SCLH
#        define _I2Cx_TIMINGR_SCLL I2C0_TIMINGR_SCLL
#        define _I2Cx_SCL_PAL_MODE I2C0_SCL_PAL_MODE
#        define _I2Cx_SDA_PAL_MODE I2C0_SDA_PAL_MODE

#        include "i2c_master.impl.c"

#    endif // HAS_I2C0

#    ifdef HAS_I2C1

#        undef _I2Cx_DRIVER
#        undef _i2cx_config
#        undef _i2cx_epilogue
#        undef _i2cx_init
#        undef _i2cx_transmit
#        undef _i2cx_receive
#        undef _i2cx_write_register
#        undef _i2cx_write_register16
#        undef _i2cx_read_register
#        undef _i2cx_read_register16
#        undef _i2cx_ping_address

#        define _i2cx_config i2c1config
#        define _i2cx_epilogue i2c1_epilogue
#        define _i2cx_init i2c1_init
#        define _i2cx_transmit i2c1_transmit
#        define _i2cx_receive i2c1_receive
#        define _i2cx_write_register i2c1_write_register
#        define _i2cx_write_register16 i2c1_write_register16
#        define _i2cx_read_register i2c1_read_register
#        define _i2cx_read_register16 i2c1_read_register16
#        define _i2cx_ping_address i2c1_ping_address

#        undef _I2Cx_DRIVER
#        undef _I2Cx_SCL_PIN
#        undef _I2Cx_SDA_PIN
#        undef _I2Cx_OPMODE
#        undef _I2Cx_CLOCK_SPEED
#        undef _I2Cx_DUTY_CYCLE
#        undef _I2Cx_TIMINGR_PRESC
#        undef _I2Cx_TIMINGR_SCLDEL
#        undef _I2Cx_TIMINGR_SDADEL
#        undef _I2Cx_TIMINGR_SCLH
#        undef _I2Cx_TIMINGR_SCLL
#        undef _I2Cx_SCL_PAL_MODE
#        undef _I2Cx_SDA_PAL_MODE

#        define _I2Cx_DRIVER I2CD1
#        define _I2Cx_SCL_PIN I2C1_SCL_PIN
#        define _I2Cx_SDA_PIN I2C1_SDA_PIN
#        define _I2Cx_OPMODE I2C1_OPMODE
#        define _I2Cx_CLOCK_SPEED I2C1_CLOCK_SPEED
#        define _I2Cx_DUTY_CYCLE I2C1_DUTY_CYCLE
#        define _I2Cx_TIMINGR_PRESC I2C1_TIMINGR_PRESC
#        define _I2Cx_TIMINGR_SCLDEL I2C1_TIMINGR_SCLDEL
#        define _I2Cx_TIMINGR_SDADEL I2C1_TIMINGR_SDADEL
#        define _I2Cx_TIMINGR_SCLH I2C1_TIMINGR_SCLH
#        define _I2Cx_TIMINGR_SCLL I2C1_TIMINGR_SCLL
#        define _I2Cx_SCL_PAL_MODE I2C1_SCL_PAL_MODE
#        define _I2Cx_SDA_PAL_MODE I2C1_SDA_PAL_MODE

#        include "i2c_master.impl.c"

#    endif // HAS_I2C1

#    ifdef HAS_I2C2

#        undef _I2Cx_DRIVER
#        undef _i2cx_config
#        undef _i2cx_epilogue
#        undef _i2cx_init
#        undef _i2cx_transmit
#        undef _i2cx_receive
#        undef _i2cx_write_register
#        undef _i2cx_write_register16
#        undef _i2cx_read_register
#        undef _i2cx_read_register16
#        undef _i2cx_ping_address

#        define _i2cx_config i2c2config
#        define _i2cx_epilogue i2c2_epilogue
#        define _i2cx_init i2c2_init
#        define _i2cx_transmit i2c2_transmit
#        define _i2cx_receive i2c2_receive
#        define _i2cx_write_register i2c2_write_register
#        define _i2cx_write_register16 i2c2_write_register16
#        define _i2cx_read_register i2c2_read_register
#        define _i2cx_read_register16 i2c2_read_register16
#        define _i2cx_ping_address i2c2_ping_address

#        undef _I2Cx_DRIVER
#        undef _I2Cx_SCL_PIN
#        undef _I2Cx_SDA_PIN
#        undef _I2Cx_OPMODE
#        undef _I2Cx_CLOCK_SPEED
#        undef _I2Cx_DUTY_CYCLE
#        undef _I2Cx_TIMINGR_PRESC
#        undef _I2Cx_TIMINGR_SCLDEL
#        undef _I2Cx_TIMINGR_SDADEL
#        undef _I2Cx_TIMINGR_SCLH
#        undef _I2Cx_TIMINGR_SCLL
#        undef _I2Cx_SCL_PAL_MODE
#        undef _I2Cx_SDA_PAL_MODE

#        define _I2Cx_DRIVER I2CD2
#        define _I2Cx_SCL_PIN I2C2_SCL_PIN
#        define _I2Cx_SDA_PIN I2C2_SDA_PIN
#        define _I2Cx_OPMODE I2C2_OPMODE
#        define _I2Cx_CLOCK_SPEED I2C2_CLOCK_SPEED
#        define _I2Cx_DUTY_CYCLE I2C2_DUTY_CYCLE
#        define _I2Cx_TIMINGR_PRESC I2C2_TIMINGR_PRESC
#        define _I2Cx_TIMINGR_SCLDEL I2C2_TIMINGR_SCLDEL
#        define _I2Cx_TIMINGR_SDADEL I2C2_TIMINGR_SDADEL
#        define _I2Cx_TIMINGR_SCLH I2C2_TIMINGR_SCLH
#        define _I2Cx_TIMINGR_SCLL I2C2_TIMINGR_SCLL
#        define _I2Cx_SCL_PAL_MODE I2C2_SCL_PAL_MODE
#        define _I2Cx_SDA_PAL_MODE I2C2_SDA_PAL_MODE

#        include "i2c_master.impl.c"

#    endif // HAS_I2C2

void i2c_init(void) {
#    ifdef HAS_I2C0
    i2c0_init();
#    endif // HAS_I2C0
#    ifdef HAS_I2C1
    i2c1_init();
#    endif // HAS_I2C1
#    ifdef HAS_I2C2
    i2c2_init();
#    endif // HAS_I2C2
}

#endif // I2C_MULTI_BUS
