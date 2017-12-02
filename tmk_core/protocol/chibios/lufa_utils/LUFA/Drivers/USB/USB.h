#define __INCLUDE_FROM_USB_DRIVER
#define __INCLUDE_FROM_HID_DRIVER
#include "progmem.h"
#include "stddef.h"

#define ATTR_PACKED                      __attribute__ ((packed))
/** Concatenates the given input into a single token, via the C Preprocessor.
 *
 *  \param[in] x  First item to concatenate.
 *  \param[in] y  Second item to concatenate.
 *
 *  \return Concatenated version of the input.
 */
#define CONCAT(x, y)            x ## y

/** CConcatenates the given input into a single token after macro expansion, via the C Preprocessor.
 *
 *  \param[in] x  First item to concatenate.
 *  \param[in] y  Second item to concatenate.
 *
 *  \return Concatenated version of the expanded input.
 */
#define CONCAT_EXPANDED(x, y)   CONCAT(x, y)
#define CPU_TO_LE16(x)           (x)

/** Endpoint address direction mask for an IN direction (Device to Host) endpoint. This may be ORed with
 *  the index of the address within a device to obtain the full endpoint address.
 */
#define ENDPOINT_DIR_IN                    0x80

#include "Class/Common/HIDClassCommon.h"
#include "Core/StdDescriptors.h"
#include "Class/Common/HIDReportData.h"
#include "Core/USBController.h"


