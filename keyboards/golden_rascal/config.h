#define MASTER_LEFT

#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP0     // USART TX pin
#define SERIAL_USART_RX_PIN GP1     // USART RX pin

#define MATRIX_ROW_PINS { GP8, GP9, GP10, GP19 }
#define MATRIX_COL_PINS { GP3, GP4, GP5, GP6, GP7 }
#define MATRIX_ROW_PINS_RIGHT { GP7, GP8, GP9, GP10 }
#define MATRIX_COL_PINS_RIGHT { GP2, GP3, GP4, GP5, GP6 }