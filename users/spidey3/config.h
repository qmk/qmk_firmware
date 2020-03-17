#ifndef USERSPACE_CONFIG_H
#define USERSPACE_CONFIG_H

// Disable action_get_macro , since we don't use these
// and it saves on space in the firmware.
#define NO_ACTION_MACRO
#define LED_DISABLE_WHEN_USB_SUSPENDED true
#define RGB_DISABLE_WHEN_USB_SUSPENDED true

#endif
