#ifndef C027_H
#define C027_H

#ifdef __cplusplus
extern "C" {
#endif

void c027_init(void);

void c027_mdm_powerOn(int usb);

void c027_mdm_powerOff(void);

void c027_gps_powerOn(void);

void c027_gps_powerOff(void);

#ifdef __cplusplus
}
#endif

#endif // C027_H
