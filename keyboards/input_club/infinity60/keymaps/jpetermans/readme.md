Backlight for Infinity60
========================

## Led Controller Specs

The Infinity60 (revision 1.1a) pcb uses the IS31FL3731C matrix LED driver from ISSI [(datasheet)](http://www.issi.com/WW/pdf/31FL3731C.pdf). The IS31 has the ability to control two led matrices (A & B), each matrix controlling 9 pins, each pin controlling 8 leds. The Infinity only utilizes matrix A.

Infinity60 LED Map:
digits mean "row" and "col", i.e. 45 means pin 4, column 5 in the IS31 datasheet
```c
  11 12 13 14 15 16 17 18 21 22 23 24 25  26 27*
   28 31 32 33 34 35 36 37 38 41 42 43 44 45
   46 47 48 51 52 53 54 55 56 57 58 61    62
   63 64 65 66 67 68 71 72 73 74 75      76 77*
   78  81  82       83         84  85  86  87
```
*Unused in Alphabet Layout

The IS31 includes 8 led pages (or frames) 0-7 than can be displayed, and each page consists of 144 bytes.
- **bytes 0 - 17** - LED control (on/off).
    * 18 bytes which alternate between A and B matrices (A1, B1, A2, B2, ..).
    * Each byte controls the 8 leds on that pin with bits (8 to 1).
- **bytes 8 - 35** - Blink control.
    * Same as LED control above, but sets blink on/off.
- **bytes 36 - 143** - PWM control.
    * One byte per LED, sets PWM from 0 to 255.
    * Same as above, the register alternates, every 8 *bytes* (not bits) between the A & B matrices.

## Led Controller Code
In the Infinity60 project folder, led_controller.c sets up ability to write led layers at startup or control leds on demand as part of fn_actions. By default led_controller.c assumes page 0 will be used for full on/off. The remaining 7 pages (1-7) are free for preset led maps or single led actions at init or on demand. Communication with the IS31 is primarily done through the led_mailbox using chMBPost described further below under "Sending messages in Keymap.c". This code is based on work matt3o and flabbergast did for tmk firmware on the [whitefox](https://github.com/tmk/whitefox).

One function is available to directly set leds without the mailbox:
```
write_led_page(page#, array of leds by address, # of addresses in array)
```
This function saves a full page to the controller using a supplied array of led locations such as:
```c
uint8_t led_numpad[16] =  {
  18,21,22,23,
  37,38,41,42,
  55,56,57,58,
  72,73,74,75
}
write_led_page(5, led_numpad, 16);
```

Remaining led control is done through the led mailbox using these message types:
- **SET_FULL_ROW** (3 bytes) - message type, 8-bit mask, and row#. Sets all leds on one pin per the bit mask.
- **OFF_LED, ON_LED, TOGGLE_LED** (3 bytes) - message type, led address, and page#. Off/on/toggle specific led.
- **BLINK_OFF_LED, BLINK_ON_LED, BLINK_TOGGLE_LED** (3 bytes) - message type, led address, and page#. Set blink Off/on/toggle for specific led.
- **TOGGLE_ALL** (1 byte) - Turn on/off full backlight.
- **TOGGLE_BACKLIGHT** (2 bytes) - message type, on/off. Sets backlight completely off, no leds will display.
- **DISPLAY_PAGE** (2 bytes) - message type, page to display. Switch to specific pre-set page.
- **RESET_PAGE** (2 bytes) - message type, page to reset. Reset/erase specific page.
- **TOGGLE_NUM_LOCK** (2 bytes) - message type, on/off (NUM_LOCK_LED_ADDRESS). Toggle numlock on/off. Usually run with the `set_leds` function to check state of numlock or capslock. If all leds are on (e.i. TOGGLE_ALL) then this sets numlock to blink instead (this is still a little buggy if toggling on/off quickly).
- **TOGGLE_CAPS_LOCK** (2 bytes) - message type, on/off (CAPS_LOCK_LED_ADDRESS). Same as numlock.
- **STEP_BRIGHTNESS** (2 bytes) - message type, and step up (1) or step down (0). Increase or decrease led brightness.

## Sending messages in Keymap.c
Sending an action to the led mailbox is done using chMBPost:
```
chMBPost(&led_mailbox, message, timeout);
```
- &led_mailbox - pointer to led mailbox
- message - up to 4 bytes but most messages use only 2. First byte (LSB) is the message type, the remaining three bytes are the message to process.
- timeout is TIME_IMMEDIATE

An example:
```c
//set the message to be sent. First byte (LSB) is the message type, and second is the led address
msg=(42 << 8) | ON_LED;

//send msg to the led mailbox
chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
```

Another:
```c
msg=(46 << 8) | BLINK_TOGGLE_LED;
chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
```

Finally, SET_FULL_ROW requires an extra byte with row information in the message so sending this message looks like:
```c
msg=(row<<16) | (led_pin_byte << 8) | SET_FULL_ROW;
chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
```
