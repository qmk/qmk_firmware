/*
 * (c) 2015 flabberast <s3+flabbergast@sdfeu.org>
 *
 * Based on the following work:
 *  - Guillaume Duc's raw hid example (MIT License)
 *    https://github.com/guiduc/usb-hid-chibios-example
 *  - PJRC Teensy examples (MIT License)
 *    https://www.pjrc.com/teensy/usb_keyboard.html
 *  - hasu's TMK keyboard code (GPL v2 and some code Modified BSD)
 *    https://github.com/tmk/tmk_keyboard/
 *  - ChibiOS demo code (Apache 2.0 License)
 *    http://www.chibios.org
 *
 * Since some GPL'd code is used, this work is licensed under
 * GPL v2 or later.
 */

/*
 * Implementation notes:
 *
 * USBEndpointConfig - Configured using explicit order instead of struct member name.
 *   This is due to ChibiOS hal LLD differences, which is dependent on hardware,
 *   "USBv1" devices have `ep_buffers` and "OTGv1" have `in_multiplier`.
 *   Given `USBv1/hal_usb_lld.h` marks the field as "not currently used" this code file
 *   makes the assumption this is safe to avoid littering with preprocessor directives.
 */

#include "ch.h"
#include "hal.h"

#include "usb_main.h"

#include "host.h"
#include "debug.h"
#include "suspend.h"
#ifdef SLEEP_LED_ENABLE
#    include "sleep_led.h"
#    include "led.h"
#endif
#include "wait.h"
#include "usb_descriptor.h"
#include "usb_driver.h"

#ifdef NKRO_ENABLE
#    include "keycode_config.h"

extern keymap_config_t keymap_config;
#endif

/* ---------------------------------------------------------
 *       Global interface variables and declarations
 * ---------------------------------------------------------
 */

#ifndef usb_lld_connect_bus
#    define usb_lld_connect_bus(usbp)
#endif

#ifndef usb_lld_disconnect_bus
#    define usb_lld_disconnect_bus(usbp)
#endif

uint8_t                keyboard_idle __attribute__((aligned(2)))     = 0;
uint8_t                keyboard_protocol __attribute__((aligned(2))) = 1;
uint8_t                keyboard_led_stats                            = 0;
volatile uint16_t      keyboard_idle_count                           = 0;
static virtual_timer_t keyboard_idle_timer;
static void            keyboard_idle_timer_cb(void *arg);

report_keyboard_t keyboard_report_sent = {{0}};
#ifdef MOUSE_ENABLE
report_mouse_t mouse_report_blank = {0};
#endif /* MOUSE_ENABLE */
#ifdef EXTRAKEY_ENABLE
uint8_t extra_report_blank[3] = {0};
#endif /* EXTRAKEY_ENABLE */

/* ---------------------------------------------------------
 *            Descriptors and USB driver objects
 * ---------------------------------------------------------
 */

/* HID specific constants */
#define HID_GET_REPORT 0x01
#define HID_GET_IDLE 0x02
#define HID_GET_PROTOCOL 0x03
#define HID_SET_REPORT 0x09
#define HID_SET_IDLE 0x0A
#define HID_SET_PROTOCOL 0x0B

/*
 * Handles the GET_DESCRIPTOR callback
 *
 * Returns the proper descriptor
 */
static const USBDescriptor *usb_get_descriptor_cb(USBDriver *usbp, uint8_t dtype, uint8_t dindex, uint16_t wIndex) {
    (void)usbp;
    static USBDescriptor desc;
    uint16_t             wValue = ((uint16_t)dtype << 8) | dindex;
    desc.ud_string              = NULL;
    desc.ud_size                = get_usb_descriptor(wValue, wIndex, (const void **const) & desc.ud_string);
    if (desc.ud_string == NULL)
        return NULL;
    else
        return &desc;
}

#ifndef KEYBOARD_SHARED_EP
/* keyboard endpoint state structure */
static USBInEndpointState kbd_ep_state;
/* keyboard endpoint initialization structure (IN) - see USBEndpointConfig comment at top of file */
static const USBEndpointConfig kbd_ep_config = {
    USB_EP_MODE_TYPE_INTR, /* Interrupt EP */
    NULL,                  /* SETUP packet notification callback */
    kbd_in_cb,             /* IN notification callback */
    NULL,                  /* OUT notification callback */
    KEYBOARD_EPSIZE,       /* IN maximum packet size */
    0,                     /* OUT maximum packet size */
    &kbd_ep_state,         /* IN Endpoint state */
    NULL,                  /* OUT endpoint state */
    2,                     /* IN multiplier */
    NULL                   /* SETUP buffer (not a SETUP endpoint) */
};
#endif

#if defined(MOUSE_ENABLE) && !defined(MOUSE_SHARED_EP)
/* mouse endpoint state structure */
static USBInEndpointState mouse_ep_state;

/* mouse endpoint initialization structure (IN) - see USBEndpointConfig comment at top of file */
static const USBEndpointConfig mouse_ep_config = {
    USB_EP_MODE_TYPE_INTR, /* Interrupt EP */
    NULL,                  /* SETUP packet notification callback */
    mouse_in_cb,           /* IN notification callback */
    NULL,                  /* OUT notification callback */
    MOUSE_EPSIZE,          /* IN maximum packet size */
    0,                     /* OUT maximum packet size */
    &mouse_ep_state,       /* IN Endpoint state */
    NULL,                  /* OUT endpoint state */
    2,                     /* IN multiplier */
    NULL                   /* SETUP buffer (not a SETUP endpoint) */
};
#endif

#ifdef SHARED_EP_ENABLE
/* shared endpoint state structure */
static USBInEndpointState shared_ep_state;

/* shared endpoint initialization structure (IN) - see USBEndpointConfig comment at top of file */
static const USBEndpointConfig shared_ep_config = {
    USB_EP_MODE_TYPE_INTR, /* Interrupt EP */
    NULL,                  /* SETUP packet notification callback */
    shared_in_cb,          /* IN notification callback */
    NULL,                  /* OUT notification callback */
    SHARED_EPSIZE,         /* IN maximum packet size */
    0,                     /* OUT maximum packet size */
    &shared_ep_state,      /* IN Endpoint state */
    NULL,                  /* OUT endpoint state */
    2,                     /* IN multiplier */
    NULL                   /* SETUP buffer (not a SETUP endpoint) */
};
#endif

typedef struct {
    size_t              queue_capacity_in;
    size_t              queue_capacity_out;
    USBInEndpointState  in_ep_state;
    USBOutEndpointState out_ep_state;
    USBInEndpointState  int_ep_state;
    USBEndpointConfig   in_ep_config;
    USBEndpointConfig   out_ep_config;
    USBEndpointConfig   int_ep_config;
    const QMKUSBConfig  config;
    QMKUSBDriver        driver;
} usb_driver_config_t;

/* Reusable initialization structure - see USBEndpointConfig comment at top of file */
#define QMK_USB_DRIVER_CONFIG(stream, notification, fixedsize)                                                              \
    {                                                                                                                       \
        .queue_capacity_in = stream##_IN_CAPACITY, .queue_capacity_out = stream##_OUT_CAPACITY,                             \
        .in_ep_config =                                                                                                     \
            {                                                                                                               \
                stream##_IN_MODE,      /* Interrupt EP */                                                                   \
                NULL,                  /* SETUP packet notification callback */                                             \
                qmkusbDataTransmitted, /* IN notification callback */                                                       \
                NULL,                  /* OUT notification callback */                                                      \
                stream##_EPSIZE,       /* IN maximum packet size */                                                         \
                0,                     /* OUT maximum packet size */                                                        \
                NULL,                  /* IN Endpoint state */                                                              \
                NULL,                  /* OUT endpoint state */                                                             \
                2,                     /* IN multiplier */                                                                  \
                NULL                   /* SETUP buffer (not a SETUP endpoint) */                                            \
            },                                                                                                              \
        .out_ep_config =                                                                                                    \
            {                                                                                                               \
                stream##_OUT_MODE,  /* Interrupt EP */                                                                      \
                NULL,               /* SETUP packet notification callback */                                                \
                NULL,               /* IN notification callback */                                                          \
                qmkusbDataReceived, /* OUT notification callback */                                                         \
                0,                  /* IN maximum packet size */                                                            \
                stream##_EPSIZE,    /* OUT maximum packet size */                                                           \
                NULL,               /* IN Endpoint state */                                                                 \
                NULL,               /* OUT endpoint state */                                                                \
                2,                  /* IN multiplier */                                                                     \
                NULL,               /* SETUP buffer (not a SETUP endpoint) */                                               \
            },                                                                                                              \
        .int_ep_config =                                                                                                    \
            {                                                                                                               \
                USB_EP_MODE_TYPE_INTR,      /* Interrupt EP */                                                              \
                NULL,                       /* SETUP packet notification callback */                                        \
                qmkusbInterruptTransmitted, /* IN notification callback */                                                  \
                NULL,                       /* OUT notification callback */                                                 \
                CDC_NOTIFICATION_EPSIZE,    /* IN maximum packet size */                                                    \
                0,                          /* OUT maximum packet size */                                                   \
                NULL,                       /* IN Endpoint state */                                                         \
                NULL,                       /* OUT endpoint state */                                                        \
                2,                          /* IN multiplier */                                                             \
                NULL,                       /* SETUP buffer (not a SETUP endpoint) */                                       \
            },                                                                                                              \
        .config = {                                                                                                         \
            .usbp        = &USB_DRIVER,                                                                                     \
            .bulk_in     = stream##_IN_EPNUM,                                                                               \
            .bulk_out    = stream##_OUT_EPNUM,                                                                              \
            .int_in      = notification,                                                                                    \
            .in_buffers  = stream##_IN_CAPACITY,                                                                            \
            .out_buffers = stream##_OUT_CAPACITY,                                                                           \
            .in_size     = stream##_EPSIZE,                                                                                 \
            .out_size    = stream##_EPSIZE,                                                                                 \
            .fixed_size  = fixedsize,                                                                                       \
            .ib          = (__attribute__((aligned(4))) uint8_t[BQ_BUFFER_SIZE(stream##_IN_CAPACITY, stream##_EPSIZE)]){},  \
            .ob          = (__attribute__((aligned(4))) uint8_t[BQ_BUFFER_SIZE(stream##_OUT_CAPACITY, stream##_EPSIZE)]){}, \
        }                                                                                                                   \
    }

typedef struct {
    union {
        struct {
#ifdef CONSOLE_ENABLE
            usb_driver_config_t console_driver;
#endif
#ifdef RAW_ENABLE
            usb_driver_config_t raw_driver;
#endif
#ifdef MIDI_ENABLE
            usb_driver_config_t midi_driver;
#endif
#ifdef VIRTSER_ENABLE
            usb_driver_config_t serial_driver;
#endif
        };
        usb_driver_config_t array[0];
    };
} usb_driver_configs_t;

static usb_driver_configs_t drivers = {
#ifdef CONSOLE_ENABLE
#    define CONSOLE_IN_CAPACITY 4
#    define CONSOLE_OUT_CAPACITY 4
#    define CONSOLE_IN_MODE USB_EP_MODE_TYPE_INTR
#    define CONSOLE_OUT_MODE USB_EP_MODE_TYPE_INTR
    .console_driver = QMK_USB_DRIVER_CONFIG(CONSOLE, 0, true),
#endif
#ifdef RAW_ENABLE
#    define RAW_IN_CAPACITY 4
#    define RAW_OUT_CAPACITY 4
#    define RAW_IN_MODE USB_EP_MODE_TYPE_INTR
#    define RAW_OUT_MODE USB_EP_MODE_TYPE_INTR
    .raw_driver = QMK_USB_DRIVER_CONFIG(RAW, 0, false),
#endif

#ifdef MIDI_ENABLE
#    define MIDI_STREAM_IN_CAPACITY 4
#    define MIDI_STREAM_OUT_CAPACITY 4
#    define MIDI_STREAM_IN_MODE USB_EP_MODE_TYPE_BULK
#    define MIDI_STREAM_OUT_MODE USB_EP_MODE_TYPE_BULK
    .midi_driver = QMK_USB_DRIVER_CONFIG(MIDI_STREAM, 0, false),
#endif

#ifdef VIRTSER_ENABLE
#    define CDC_IN_CAPACITY 4
#    define CDC_OUT_CAPACITY 4
#    define CDC_IN_MODE USB_EP_MODE_TYPE_BULK
#    define CDC_OUT_MODE USB_EP_MODE_TYPE_BULK
    .serial_driver = QMK_USB_DRIVER_CONFIG(CDC, CDC_NOTIFICATION_EPNUM, false),
#endif
};

#define NUM_USB_DRIVERS (sizeof(drivers) / sizeof(usb_driver_config_t))

/* ---------------------------------------------------------
 *                  USB driver functions
 * ---------------------------------------------------------
 */

/* Handles the USB driver global events
 * TODO: maybe disable some things when connection is lost? */
static void usb_event_cb(USBDriver *usbp, usbevent_t event) {
    switch (event) {
        case USB_EVENT_ADDRESS:
            return;

        case USB_EVENT_CONFIGURED:
            osalSysLockFromISR();
            /* Enable the endpoints specified into the configuration. */
#ifndef KEYBOARD_SHARED_EP
            usbInitEndpointI(usbp, KEYBOARD_IN_EPNUM, &kbd_ep_config);
#endif
#if defined(MOUSE_ENABLE) && !defined(MOUSE_SHARED_EP)
            usbInitEndpointI(usbp, MOUSE_IN_EPNUM, &mouse_ep_config);
#endif
#ifdef SHARED_EP_ENABLE
            usbInitEndpointI(usbp, SHARED_IN_EPNUM, &shared_ep_config);
#endif
            for (int i = 0; i < NUM_USB_DRIVERS; i++) {
                usbInitEndpointI(usbp, drivers.array[i].config.bulk_in, &drivers.array[i].in_ep_config);
                usbInitEndpointI(usbp, drivers.array[i].config.bulk_out, &drivers.array[i].out_ep_config);
                if (drivers.array[i].config.int_in) {
                    usbInitEndpointI(usbp, drivers.array[i].config.int_in, &drivers.array[i].int_ep_config);
                }
                qmkusbConfigureHookI(&drivers.array[i].driver);
            }
            osalSysUnlockFromISR();
            return;
        case USB_EVENT_SUSPEND:
#ifdef SLEEP_LED_ENABLE
            sleep_led_enable();
#endif /* SLEEP_LED_ENABLE */
            /* Falls into.*/
        case USB_EVENT_UNCONFIGURED:
            /* Falls into.*/
        case USB_EVENT_RESET:
            for (int i = 0; i < NUM_USB_DRIVERS; i++) {
                chSysLockFromISR();
                /* Disconnection event on suspend.*/
                qmkusbSuspendHookI(&drivers.array[i].driver);
                chSysUnlockFromISR();
            }
            return;

        case USB_EVENT_WAKEUP:
            // TODO: from ISR! print("[W]");
            for (int i = 0; i < NUM_USB_DRIVERS; i++) {
                chSysLockFromISR();
                /* Disconnection event on suspend.*/
                qmkusbWakeupHookI(&drivers.array[i].driver);
                chSysUnlockFromISR();
            }
            suspend_wakeup_init();
#ifdef SLEEP_LED_ENABLE
            sleep_led_disable();
            // NOTE: converters may not accept this
            led_set(host_keyboard_leds());
#endif /* SLEEP_LED_ENABLE */
            return;

        case USB_EVENT_STALLED:
            return;
    }
}

/* Function used locally in os/hal/src/usb.c for getting descriptors
 * need it here for HID descriptor */
static uint16_t get_hword(uint8_t *p) {
    uint16_t hw;

    hw = (uint16_t)*p++;
    hw |= (uint16_t)*p << 8U;
    return hw;
}

/*
 * Appendix G: HID Request Support Requirements
 *
 * The following table enumerates the requests that need to be supported by various types of HID class devices.
 * Device type     GetReport   SetReport   GetIdle     SetIdle     GetProtocol SetProtocol
 * ------------------------------------------------------------------------------------------
 * Boot Mouse      Required    Optional    Optional    Optional    Required    Required
 * Non-Boot Mouse  Required    Optional    Optional    Optional    Optional    Optional
 * Boot Keyboard   Required    Optional    Required    Required    Required    Required
 * Non-Boot Keybrd Required    Optional    Required    Required    Optional    Optional
 * Other Device    Required    Optional    Optional    Optional    Optional    Optional
 */

static uint8_t set_report_buf[2] __attribute__((aligned(2)));
static void    set_led_transfer_cb(USBDriver *usbp) {
    if (usbp->setup[6] == 2) { /* LSB(wLength) */
        uint8_t report_id = set_report_buf[0];
        if ((report_id == REPORT_ID_KEYBOARD) || (report_id == REPORT_ID_NKRO)) {
            keyboard_led_stats = set_report_buf[1];
        }
    } else {
        keyboard_led_stats = set_report_buf[0];
    }
}

/* Callback for SETUP request on the endpoint 0 (control) */
static bool usb_request_hook_cb(USBDriver *usbp) {
    const USBDescriptor *dp;

    /* usbp->setup fields:
     *  0:   bmRequestType (bitmask)
     *  1:   bRequest
     *  2,3: (LSB,MSB) wValue
     *  4,5: (LSB,MSB) wIndex
     *  6,7: (LSB,MSB) wLength (number of bytes to transfer if there is a data phase) */

    /* Handle HID class specific requests */
    if (((usbp->setup[0] & USB_RTYPE_TYPE_MASK) == USB_RTYPE_TYPE_CLASS) && ((usbp->setup[0] & USB_RTYPE_RECIPIENT_MASK) == USB_RTYPE_RECIPIENT_INTERFACE)) {
        switch (usbp->setup[0] & USB_RTYPE_DIR_MASK) {
            case USB_RTYPE_DIR_DEV2HOST:
                switch (usbp->setup[1]) { /* bRequest */
                    case HID_GET_REPORT:
                        switch (usbp->setup[4]) { /* LSB(wIndex) (check MSB==0?) */
                            case KEYBOARD_INTERFACE:
                                usbSetupTransfer(usbp, (uint8_t *)&keyboard_report_sent, sizeof(keyboard_report_sent), NULL);
                                return TRUE;
                                break;

#if defined(MOUSE_ENABLE) && !defined(MOUSE_SHARED_EP)
                            case MOUSE_INTERFACE:
                                usbSetupTransfer(usbp, (uint8_t *)&mouse_report_blank, sizeof(mouse_report_blank), NULL);
                                return TRUE;
                                break;
#endif

                            default:
                                usbSetupTransfer(usbp, NULL, 0, NULL);
                                return TRUE;
                                break;
                        }
                        break;

                    case HID_GET_PROTOCOL:
                        if ((usbp->setup[4] == KEYBOARD_INTERFACE) && (usbp->setup[5] == 0)) { /* wIndex */
                            usbSetupTransfer(usbp, &keyboard_protocol, 1, NULL);
                            return TRUE;
                        }
                        break;

                    case HID_GET_IDLE:
                        usbSetupTransfer(usbp, &keyboard_idle, 1, NULL);
                        return TRUE;
                        break;
                }
                break;

            case USB_RTYPE_DIR_HOST2DEV:
                switch (usbp->setup[1]) { /* bRequest */
                    case HID_SET_REPORT:
                        switch (usbp->setup[4]) { /* LSB(wIndex) (check MSB==0?) */
                            case KEYBOARD_INTERFACE:
#if defined(SHARED_EP_ENABLE) && !defined(KEYBOARD_SHARED_EP)
                            case SHARED_INTERFACE:
#endif
                                usbSetupTransfer(usbp, set_report_buf, sizeof(set_report_buf), set_led_transfer_cb);
                                return TRUE;
                                break;
                        }
                        break;

                    case HID_SET_PROTOCOL:
                        if ((usbp->setup[4] == KEYBOARD_INTERFACE) && (usbp->setup[5] == 0)) { /* wIndex */
                            keyboard_protocol = ((usbp->setup[2]) != 0x00);                    /* LSB(wValue) */
#ifdef NKRO_ENABLE
                            keymap_config.nkro = !!keyboard_protocol;
                            if (!keymap_config.nkro && keyboard_idle) {
#else  /* NKRO_ENABLE */
                            if (keyboard_idle) {
#endif /* NKRO_ENABLE */
                                /* arm the idle timer if boot protocol & idle */
                                osalSysLockFromISR();
                                chVTSetI(&keyboard_idle_timer, 4 * TIME_MS2I(keyboard_idle), keyboard_idle_timer_cb, (void *)usbp);
                                osalSysUnlockFromISR();
                            }
                        }
                        usbSetupTransfer(usbp, NULL, 0, NULL);
                        return TRUE;
                        break;

                    case HID_SET_IDLE:
                        keyboard_idle = usbp->setup[3]; /* MSB(wValue) */
                                                        /* arm the timer */
#ifdef NKRO_ENABLE
                        if (!keymap_config.nkro && keyboard_idle) {
#else  /* NKRO_ENABLE */
                        if (keyboard_idle) {
#endif /* NKRO_ENABLE */
                            osalSysLockFromISR();
                            chVTSetI(&keyboard_idle_timer, 4 * TIME_MS2I(keyboard_idle), keyboard_idle_timer_cb, (void *)usbp);
                            osalSysUnlockFromISR();
                        }
                        usbSetupTransfer(usbp, NULL, 0, NULL);
                        return TRUE;
                        break;
                }
                break;
        }
    }

    /* Handle the Get_Descriptor Request for HID class (not handled by the default hook) */
    if ((usbp->setup[0] == 0x81) && (usbp->setup[1] == USB_REQ_GET_DESCRIPTOR)) {
        dp = usbp->config->get_descriptor_cb(usbp, usbp->setup[3], usbp->setup[2], get_hword(&usbp->setup[4]));
        if (dp == NULL) return FALSE;
        usbSetupTransfer(usbp, (uint8_t *)dp->ud_string, dp->ud_size, NULL);
        return TRUE;
    }

    for (int i = 0; i < NUM_USB_DRIVERS; i++) {
        if (drivers.array[i].config.int_in) {
            // NOTE: Assumes that we only have one serial driver
            return qmkusbRequestsHook(usbp);
        }
    }

    return FALSE;
}

/* Start-of-frame callback */
static void usb_sof_cb(USBDriver *usbp) {
    kbd_sof_cb(usbp);
    osalSysLockFromISR();
    for (int i = 0; i < NUM_USB_DRIVERS; i++) {
        qmkusbSOFHookI(&drivers.array[i].driver);
    }
    osalSysUnlockFromISR();
}

/* USB driver configuration */
static const USBConfig usbcfg = {
    usb_event_cb,          /* USB events callback */
    usb_get_descriptor_cb, /* Device GET_DESCRIPTOR request callback */
    usb_request_hook_cb,   /* Requests hook callback */
    usb_sof_cb             /* Start Of Frame callback */
};

/*
 * Initialize the USB driver
 */
void init_usb_driver(USBDriver *usbp) {
    for (int i = 0; i < NUM_USB_DRIVERS; i++) {
        QMKUSBDriver *driver                     = &drivers.array[i].driver;
        drivers.array[i].in_ep_config.in_state   = &drivers.array[i].in_ep_state;
        drivers.array[i].out_ep_config.out_state = &drivers.array[i].out_ep_state;
        drivers.array[i].int_ep_config.in_state  = &drivers.array[i].int_ep_state;
        qmkusbObjectInit(driver, &drivers.array[i].config);
        qmkusbStart(driver, &drivers.array[i].config);
    }

    /*
     * Activates the USB driver and then the USB bus pull-up on D+.
     * Note, a delay is inserted in order to not have to disconnect the cable
     * after a reset.
     */
    usbDisconnectBus(usbp);
    wait_ms(1500);
    usbStart(usbp, &usbcfg);
    usbConnectBus(usbp);

    chVTObjectInit(&keyboard_idle_timer);
}

/* ---------------------------------------------------------
 *                  Keyboard functions
 * ---------------------------------------------------------
 */
/* keyboard IN callback hander (a kbd report has made it IN) */
#ifndef KEYBOARD_SHARED_EP
void kbd_in_cb(USBDriver *usbp, usbep_t ep) {
    /* STUB */
    (void)usbp;
    (void)ep;
}
#endif

/* start-of-frame handler
 * TODO: i guess it would be better to re-implement using timers,
 *  so that this is not going to have to be checked every 1ms */
void kbd_sof_cb(USBDriver *usbp) { (void)usbp; }

/* Idle requests timer code
 * callback (called from ISR, unlocked state) */
static void keyboard_idle_timer_cb(void *arg) {
    USBDriver *usbp = (USBDriver *)arg;

    osalSysLockFromISR();

    /* check that the states of things are as they're supposed to */
    if (usbGetDriverStateI(usbp) != USB_ACTIVE) {
        /* do not rearm the timer, should be enabled on IDLE request */
        osalSysUnlockFromISR();
        return;
    }

#ifdef NKRO_ENABLE
    if (!keymap_config.nkro && keyboard_idle && keyboard_protocol) {
#else  /* NKRO_ENABLE */
    if (keyboard_idle && keyboard_protocol) {
#endif /* NKRO_ENABLE */
        /* TODO: are we sure we want the KBD_ENDPOINT? */
        if (!usbGetTransmitStatusI(usbp, KEYBOARD_IN_EPNUM)) {
            usbStartTransmitI(usbp, KEYBOARD_IN_EPNUM, (uint8_t *)&keyboard_report_sent, KEYBOARD_EPSIZE);
        }
        /* rearm the timer */
        chVTSetI(&keyboard_idle_timer, 4 * TIME_MS2I(keyboard_idle), keyboard_idle_timer_cb, (void *)usbp);
    }

    /* do not rearm the timer if the condition above fails
     * it should be enabled again on either IDLE or SET_PROTOCOL requests */
    osalSysUnlockFromISR();
}

/* LED status */
uint8_t keyboard_leds(void) { return keyboard_led_stats; }

/* prepare and start sending a report IN
 * not callable from ISR or locked state */
void send_keyboard(report_keyboard_t *report) {
    osalSysLock();
    if (usbGetDriverStateI(&USB_DRIVER) != USB_ACTIVE) {
        goto unlock;
    }

#ifdef NKRO_ENABLE
    if (keymap_config.nkro && keyboard_protocol) { /* NKRO protocol */
        /* need to wait until the previous packet has made it through */
        /* can rewrite this using the synchronous API, then would wait
         * until *after* the packet has been transmitted. I think
         * this is more efficient */
        /* busy wait, should be short and not very common */
        if (usbGetTransmitStatusI(&USB_DRIVER, SHARED_IN_EPNUM)) {
            /* Need to either suspend, or loop and call unlock/lock during
             * every iteration - otherwise the system will remain locked,
             * no interrupts served, so USB not going through as well.
             * Note: for suspend, need USB_USE_WAIT == TRUE in halconf.h */
            osalThreadSuspendS(&(&USB_DRIVER)->epc[SHARED_IN_EPNUM]->in_state->thread);

            /* after osalThreadSuspendS returns USB status might have changed */
            if (usbGetDriverStateI(&USB_DRIVER) != USB_ACTIVE) {
                goto unlock;
            }
        }
        usbStartTransmitI(&USB_DRIVER, SHARED_IN_EPNUM, (uint8_t *)report, sizeof(struct nkro_report));
    } else
#endif /* NKRO_ENABLE */
    {  /* regular protocol */
        /* need to wait until the previous packet has made it through */
        /* busy wait, should be short and not very common */
        if (usbGetTransmitStatusI(&USB_DRIVER, KEYBOARD_IN_EPNUM)) {
            /* Need to either suspend, or loop and call unlock/lock during
             * every iteration - otherwise the system will remain locked,
             * no interrupts served, so USB not going through as well.
             * Note: for suspend, need USB_USE_WAIT == TRUE in halconf.h */
            osalThreadSuspendS(&(&USB_DRIVER)->epc[KEYBOARD_IN_EPNUM]->in_state->thread);

            /* after osalThreadSuspendS returns USB status might have changed */
            if (usbGetDriverStateI(&USB_DRIVER) != USB_ACTIVE) {
                goto unlock;
            }
        }
        uint8_t *data, size;
        if (keyboard_protocol) {
            data = (uint8_t *)report;
            size = KEYBOARD_REPORT_SIZE;
        } else { /* boot protocol */
            data = &report->mods;
            size = 8;
        }
        usbStartTransmitI(&USB_DRIVER, KEYBOARD_IN_EPNUM, data, size);
    }
    keyboard_report_sent = *report;

unlock:
    osalSysUnlock();
}

/* ---------------------------------------------------------
 *                     Mouse functions
 * ---------------------------------------------------------
 */

#ifdef MOUSE_ENABLE

#    ifndef MOUSE_SHARED_EP
/* mouse IN callback hander (a mouse report has made it IN) */
void mouse_in_cb(USBDriver *usbp, usbep_t ep) {
    (void)usbp;
    (void)ep;
}
#    endif

void send_mouse(report_mouse_t *report) {
    osalSysLock();
    if (usbGetDriverStateI(&USB_DRIVER) != USB_ACTIVE) {
        osalSysUnlock();
        return;
    }

    if (usbGetTransmitStatusI(&USB_DRIVER, MOUSE_IN_EPNUM)) {
        /* Need to either suspend, or loop and call unlock/lock during
         * every iteration - otherwise the system will remain locked,
         * no interrupts served, so USB not going through as well.
         * Note: for suspend, need USB_USE_WAIT == TRUE in halconf.h */
        if (osalThreadSuspendTimeoutS(&(&USB_DRIVER)->epc[MOUSE_IN_EPNUM]->in_state->thread, TIME_MS2I(10)) == MSG_TIMEOUT) {
            osalSysUnlock();
            return;
        }
    }
    usbStartTransmitI(&USB_DRIVER, MOUSE_IN_EPNUM, (uint8_t *)report, sizeof(report_mouse_t));
    osalSysUnlock();
}

#else  /* MOUSE_ENABLE */
void send_mouse(report_mouse_t *report) { (void)report; }
#endif /* MOUSE_ENABLE */

/* ---------------------------------------------------------
 *                   Shared EP functions
 * ---------------------------------------------------------
 */
#ifdef SHARED_EP_ENABLE
/* shared IN callback hander */
void shared_in_cb(USBDriver *usbp, usbep_t ep) {
    /* STUB */
    (void)usbp;
    (void)ep;
}
#endif

/* ---------------------------------------------------------
 *                   Extrakey functions
 * ---------------------------------------------------------
 */

#ifdef EXTRAKEY_ENABLE
static void send_extra(uint8_t report_id, uint16_t data) {
    osalSysLock();
    if (usbGetDriverStateI(&USB_DRIVER) != USB_ACTIVE) {
        osalSysUnlock();
        return;
    }

    report_extra_t report = {.report_id = report_id, .usage = data};

    usbStartTransmitI(&USB_DRIVER, SHARED_IN_EPNUM, (uint8_t *)&report, sizeof(report_extra_t));
    osalSysUnlock();
}
#endif

void send_system(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
    send_extra(REPORT_ID_SYSTEM, data);
#endif
}

void send_consumer(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
    send_extra(REPORT_ID_CONSUMER, data);
#endif
}

/* ---------------------------------------------------------
 *                   Console functions
 * ---------------------------------------------------------
 */

#ifdef CONSOLE_ENABLE

int8_t sendchar(uint8_t c) {
    // The previous implmentation had timeouts, but I think it's better to just slow down
    // and make sure that everything is transferred, rather than dropping stuff
    return chnWrite(&drivers.console_driver.driver, &c, 1);
}

// Just a dummy function for now, this could be exposed as a weak function
// Or connected to the actual QMK console
static void console_receive(uint8_t *data, uint8_t length) {
    (void)data;
    (void)length;
}

void console_task(void) {
    uint8_t buffer[CONSOLE_EPSIZE];
    size_t  size = 0;
    do {
        size_t size = chnReadTimeout(&drivers.console_driver.driver, buffer, sizeof(buffer), TIME_IMMEDIATE);
        if (size > 0) {
            console_receive(buffer, size);
        }
    } while (size > 0);
}

#else  /* CONSOLE_ENABLE */
int8_t sendchar(uint8_t c) {
    (void)c;
    return 0;
}
#endif /* CONSOLE_ENABLE */

void _putchar(char character) {
    sendchar(character);
}

#ifdef RAW_ENABLE
void raw_hid_send(uint8_t *data, uint8_t length) {
    // TODO: implement variable size packet
    if (length != RAW_EPSIZE) {
        return;
    }
    chnWrite(&drivers.raw_driver.driver, data, length);
}

__attribute__((weak)) void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Users should #include "raw_hid.h" in their own code
    // and implement this function there. Leave this as weak linkage
    // so users can opt to not handle data coming in.
}

void raw_hid_task(void) {
    uint8_t buffer[RAW_EPSIZE];
    size_t  size = 0;
    do {
        size_t size = chnReadTimeout(&drivers.raw_driver.driver, buffer, sizeof(buffer), TIME_IMMEDIATE);
        if (size > 0) {
            raw_hid_receive(buffer, size);
        }
    } while (size > 0);
}

#endif

#ifdef MIDI_ENABLE

void send_midi_packet(MIDI_EventPacket_t *event) { chnWrite(&drivers.midi_driver.driver, (uint8_t *)event, sizeof(MIDI_EventPacket_t)); }

bool recv_midi_packet(MIDI_EventPacket_t *const event) {
    size_t size = chnReadTimeout(&drivers.midi_driver.driver, (uint8_t *)event, sizeof(MIDI_EventPacket_t), TIME_IMMEDIATE);
    return size == sizeof(MIDI_EventPacket_t);
}
void midi_ep_task(void) {
    uint8_t buffer[MIDI_STREAM_EPSIZE];
    size_t  size = 0;
    do {
        size_t size = chnReadTimeout(&drivers.midi_driver.driver, buffer, sizeof(buffer), TIME_IMMEDIATE);
        if (size > 0) {
            MIDI_EventPacket_t event;
            recv_midi_packet(&event);
        }
    } while (size > 0);
}
#endif

#ifdef VIRTSER_ENABLE

void virtser_send(const uint8_t byte) { chnWrite(&drivers.serial_driver.driver, &byte, 1); }

__attribute__((weak)) void virtser_recv(uint8_t c) {
    // Ignore by default
}

void virtser_task(void) {
    uint8_t numBytesReceived = 0;
    uint8_t buffer[16];
    do {
        numBytesReceived = chnReadTimeout(&drivers.serial_driver.driver, buffer, sizeof(buffer), TIME_IMMEDIATE);
        for (int i = 0; i < numBytesReceived; i++) {
            virtser_recv(buffer[i]);
        }
    } while (numBytesReceived > 0);
}

#endif
