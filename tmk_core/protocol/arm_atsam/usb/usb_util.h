#ifndef _USB_UTIL_H_
#define _USB_UTIL_H_

int UTIL_ltoa_radix(int64_t value, char *dest, int radix);
int UTIL_ltoa(int64_t value, char *dest);
int UTIL_itoa(int value, char *dest);
int UTIL_utoa(uint32_t value, char *dest);

#endif //_USB_UTIL_H_

