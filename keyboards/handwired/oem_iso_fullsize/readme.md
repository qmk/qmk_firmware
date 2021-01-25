# oem_iso_fullsize

Backlight pins  A1, A2, A7, B5, E3, E4
space led negative -|> R88 Pin A7
B led negative R91 Pin E5
F1 led negative R109 Pin A1
P led negative R103 Pin E4
0 led negative R106 Pin B5
Ñ led negative R94 Pin A2

fila respectiva a cable y pin

*Row 0, resistor R132, Pin A1
*Row 1, R131, Pin B5
*Row 2, R130, Pin E4
*Row 3, R129, Pin A2
*Row 4, R128, Pin E5
*Row 5, R127, Pin A7

#define DIODE_DIRECTION ROW2COL
#define LED_CAPS_LOCK_PIN C7
#define LED_SCROLL_LOCK_PIN A3
#define LED_NUM_LOCK_PIN C6
#define BACKLIGHT_PINS { B5, E5, E4, A7, A1, A2 }
#define BACKLIGHT_LEVELS 1