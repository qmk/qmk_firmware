#include "matrix.h"
#include "i2c_master.h"
#include "led_matrix.h"
#include "suspend.h"

/** \brief Suspend idle
 *
 * FIXME: needs doc
 */
void suspend_idle(uint8_t time) {
    /* Note: Not used anywhere currently */
}

/** \brief Run user level Power down
 *
 * FIXME: needs doc
 */
__attribute__ ((weak))
void suspend_power_down_user (void) {

}

/** \brief Run keyboard level Power down
 *
 * FIXME: needs doc
 */
__attribute__ ((weak))
void suspend_power_down_kb(void) {
    suspend_power_down_user();
}

/** \brief Suspend power down
 *
 * FIXME: needs doc
 */
void suspend_power_down(void)
{
#ifdef RGB_MATRIX_ENABLE
    I2C3733_Control_Set(0); //Disable LED driver
#endif

    suspend_power_down_kb();
}

__attribute__ ((weak)) void matrix_power_up(void) {}
__attribute__ ((weak)) void matrix_power_down(void) {}
bool suspend_wakeup_condition(void) {
    matrix_power_up();
    matrix_scan();
    matrix_power_down();
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        if (matrix_get_row(r)) return true;
    }
    return false;
}

/** \brief run user level code immediately after wakeup
 *
 * FIXME: needs doc
 */
__attribute__ ((weak))
void suspend_wakeup_init_user(void) {

}

/** \brief run keyboard level code immediately after wakeup
 *
 * FIXME: needs doc
 */
__attribute__ ((weak))
void suspend_wakeup_init_kb(void) {
    suspend_wakeup_init_user();
}

/** \brief run immediately after wakeup
 *
 * FIXME: needs doc
 */
void suspend_wakeup_init(void) {
#ifdef RGB_MATRIX_ENABLE
    I2C3733_Control_Set(1);
#endif

    suspend_wakeup_init_kb();
}

