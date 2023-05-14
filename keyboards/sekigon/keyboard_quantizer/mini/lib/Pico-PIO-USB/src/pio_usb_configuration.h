
#pragma once

typedef struct {
    uint8_t pin_dp;
    uint8_t pio_tx_num;
    uint8_t sm_tx;
    uint8_t tx_ch;
    uint8_t pio_rx_num;
    uint8_t sm_rx;
    uint8_t sm_eop;
    void* alarm_pool;
    int8_t debug_pin_rx;
    int8_t debug_pin_eop;
    uint8_t extra_error_retry_count;
} pio_usb_configuration_t;

#ifndef PIO_USB_DP_PIN_DEFAULT
#define PIO_USB_DP_PIN_DEFAULT 0
#endif

#define PIO_USB_DM_PIN_DEFAULT (PIO_USB_DP_PIN_DEFAULT + 1)

#define PIO_USB_TX_DEFAULT 0
#define PIO_SM_USB_TX_DEFAULT 0
#define PIO_USB_DMA_TX_DEFAULT 0

#define PIO_USB_RX_DEFAULT 1
#define PIO_SM_USB_RX_DEFAULT 0
#define PIO_SM_USB_EOP_DEFAULT 1

#define PIO_USB_DEBUG_PIN_NONE (-1)

// Newly added retry count, in addition to the retry defined by the
// specification.
#define PIO_USB_EXTRA_ERROR_RETRY_COUNT_DEFAULT 0

#define PIO_USB_DEFAULT_CONFIG                                                 \
    {                                                                          \
        PIO_USB_DP_PIN_DEFAULT, PIO_USB_TX_DEFAULT, PIO_SM_USB_TX_DEFAULT,     \
            PIO_USB_DMA_TX_DEFAULT, PIO_USB_RX_DEFAULT, PIO_SM_USB_RX_DEFAULT, \
            PIO_SM_USB_EOP_DEFAULT, NULL, PIO_USB_DEBUG_PIN_NONE,              \
            PIO_USB_DEBUG_PIN_NONE, PIO_USB_EXTRA_ERROR_RETRY_COUNT_DEFAULT,   \
    }

#define PIO_USB_EP_POOL_CNT 32
#define PIO_USB_DEV_EP_CNT 16
#define PIO_USB_DEVICE_CNT 4
#define PIO_USB_HUB_PORT_CNT 8
#define PIO_USB_ROOT_PORT_CNT 2

#define PIO_USB_EP_SIZE 64
