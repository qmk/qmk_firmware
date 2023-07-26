#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>

/* Board identifiers. */
#define k70_vengeance_rgb
#define BOARD_NAME "Corsair K70 Vengeance RGB"

#define LPC11U35

/*  Board frequencies. */
#define LPC_SYSOSC_FREQUENCY    12000000UL

/* Pin mapping
 * Idealy would have used PIOx_y however that conflicts with LPC_IOCON_Type struct
 */

/* USB */
#define USBCONN         PAL_LINE(IOPORT0, 6)
#define USBVBUS         PAL_LINE(IOPORT0, 3)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif

#endif
