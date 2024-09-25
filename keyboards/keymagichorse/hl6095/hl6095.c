/* Copyright 2024 keymagichorse
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
#include "quantum.h"

#if defined(BLUETOOTH_BHQ)
#   include "bhq.h"
#   include "battery.h"
#   include "km_printf.h"
#endif


void board_init(void) 
{
#if defined(BLUETOOTH_BHQ)
    battery_init();
    km_printf_init();
    km_printf("hello rtt log1111111\r\n");
#endif
}


void housekeeping_task_kb(void) {
#if defined(BLUETOOTH_BHQ)
    battery_task();
#endif
}

// After initializing the peripheral
void keyboard_post_init_kb(void)
{
#if defined(BLUETOOTH_BHQ)
    bhkDevConfigInfo_t model_parma = {
        .vendor_id_source   = 1,
        .verndor_id         = VENDOR_ID,
        .product_id         = PRODUCT_ID,

        .le_connection_interval_min = 6,
        .le_connection_interval_max = 10,
        .le_connection_interval_timeout = 500,
        .tx_poweer = 0x3D,    

#if BHQ_READ_VOLTAGE_ENABLED == TRUE
        .mk_is_read_battery_voltage = TRUE,
        .mk_adc_pga = 1,
        .mk_rvd_r1 = BHQ_R_UPPER,
        .mk_rvd_r2 = BHQ_R_LOWER,
#else
        .mk_is_read_battery_voltage = FALSE,
        .mk_adc_pga = 1,
        .mk_rvd_r1 = 0,
        .mk_rvd_r2 = 0,
#endif
        .bleNameStrLength = strlen(PRODUCT),
        .bleNameStr = PRODUCT
    };

    bhq_ConfigRunParam(model_parma);
#endif
}
