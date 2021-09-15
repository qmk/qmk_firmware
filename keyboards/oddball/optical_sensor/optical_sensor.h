/* Copyright 2020 Alexander Tulloh
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

/* common interface for opitcal sensors */

#if defined ADNS_9800
    #include "drivers/sensors/adns9800.h"
    #define config_optical_sensor_t config_adns_t
    #define report_optical_sensor_t report_adns_t
    #define optical_sensor_init adns_init
    #define optical_sensor_get_config adns_get_config
    #define optical_sensor_set_config adns_set_config
    #define optical_sensor_get_report adns_get_report
#elif defined PMW_3360
    #include "../pmw/pmw.h"
    #define config_optical_sensor_t config_pmw_t
    #define report_optical_sensor_t report_pmw_t
    #define optical_sensor_init pmw_init
    #define optical_sensor_get_config pmw_get_config
    #define optical_sensor_set_config pmw_set_config
    #define optical_sensor_get_report pmw_get_report
#else
    /* fallback stub */

    #include <stdint.h>

    typedef struct {
        uint16_t cpi;
    } config_optical_sensor_t;

    typedef struct {
        int16_t x;
        int16_t y;
    } report_optical_sensor_t;

    #define optical_sensor_init(){ }
    #define optical_sensor_get_config() (config_optical_sensor_t){ }
    #define optical_sensor_set_config(config_optical_sensor_t){ }
    #define optical_sensor_get_report() (report_optical_sensor_t){ }
#endif
