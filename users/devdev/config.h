#pragma once

/* Disable unused and unneeded features to reduce on firmware size */
#if defined(LOCKING_SUPPORT_ENABLE)
#    undef LOCKING_SUPPORT_ENABLE
#endif

#if defined(OLED_FONT_H)
#    undef OLED_FONT_H
#endif


#define OLED_FONT_H "users/devdev/glcdfont.c"
