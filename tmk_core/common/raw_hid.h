#ifndef _RAW_HID_H_
#define _RAW_HID_H_

void raw_hid_receive(uint8_t *data, uint8_t length);

void raw_hid_send(uint8_t *data, uint8_t length);

#endif
