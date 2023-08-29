# group `raw_hid` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`raw_hid_receive`](#group__raw__hid_1ga6a488515569aeaf57f34773af17ddfd8)`(uint8_t * data,uint8_t length)`            | Callback, invoked when a raw HID report has been received from the host.
`public void `[`raw_hid_send`](#group__raw__hid_1ga8656eabd043e44d73472af72bf7b107f)`(uint8_t * data,uint8_t length)`            | Send an HID report.

## Members

#### `public void `[`raw_hid_receive`](#group__raw__hid_1ga6a488515569aeaf57f34773af17ddfd8)`(uint8_t * data,uint8_t length)` 

Callback, invoked when a raw HID report has been received from the host.

#### Parameters
* `data` A pointer to the received data. Always 32 bytes in length. 

* `length` The length of the buffer. Always 32.

#### `public void `[`raw_hid_send`](#group__raw__hid_1ga8656eabd043e44d73472af72bf7b107f)`(uint8_t * data,uint8_t length)` 

Send an HID report.

#### Parameters
* `data` A pointer to the data to send. Must always be 32 bytes in length. 

* `length` The length of the buffer. Must always be 32.

