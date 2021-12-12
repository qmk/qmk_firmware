#include "isrpipe.h"
#include "isrpipe/read_timeout.h"

#include "usb/usbus.h"
#include "usb/usbus/hid.h"
#include "usb/usbus/hid_io.h"
#include "usb/usbus/control.h"

#include "usb_driver.h"
#include "report.h"

static uint8_t                keyboard_led_state                            = 0;
uint8_t usbdrv_keyboard_leds(void) { return keyboard_led_state; }

typedef struct comp_hid_device comp_hid_device_t;

typedef void (*comp_hid_cb_t)(comp_hid_device_t *hid, uint8_t *data, size_t len);

struct comp_hid_device {
    usbus_handler_t        handler_ctrl; /**< control handler */
    usbus_interface_t      iface;        /**< HID interface */
    usbus_endpoint_t *     ep_out;       /**< OUT endpoint */
    usbus_endpoint_t *     ep_in;        /**< IN  endpoint */
    usbus_descr_gen_t      hid_descr;    /**< HID descriptor generator */
    usbus_t *              usbus;        /**< USBUS reference */
    comp_hid_device_conf_t conf;         /**< stashed config */
    size_t                 occupied;     /**< Number of bytes for the host */
    comp_hid_cb_t          cb;           /**< Callback for data handlers */
    event_t                tx_ready;     /**< Transmit ready event */
    mutex_t                in_lock;      /**< mutex used for locking hid send */
};

static uint8_t   _hid_rx_buf_mem[CONFIG_USBUS_HID_INTERRUPT_EP_SIZE];
static isrpipe_t _hid_stdio_isrpipe = ISRPIPE_INIT(_hid_rx_buf_mem);

static void _hid_rx_pipe(comp_hid_device_t *dev, uint8_t *data, size_t len) {
    (void)dev;
    for (size_t i = 0; i < len; i++) {
        isrpipe_write_one(&_hid_stdio_isrpipe, data[i]);
    }

    // if (_rx_cb) {
    //     _rx_cb(_rx_cb_arg);
    // }
}

static size_t _gen_hid_descriptor(usbus_t *usbus, void *arg) {
    comp_hid_device_t *dev = arg;

    usb_desc_hid_t hid_desc;
    hid_desc.length        = sizeof(usb_desc_hid_t);
    hid_desc.desc_type     = USB_HID_DESCR_HID;
    hid_desc.bcd_hid       = USB_HID_VERSION_BCD; //0x1111;  // dev->conf.id == KEYBOARD_INTERFACE ? 0x0101 : 0x0111;
    hid_desc.country_code  = USB_HID_COUNTRY_CODE_NOTSUPPORTED;
    hid_desc.num_descrs    = 0x01;
    hid_desc.report_type   = USB_HID_DESCR_REPORT;
    hid_desc.report_length = dev->conf.report_desc_size;

    usbus_control_slicer_put_bytes(usbus, (uint8_t *)&hid_desc, sizeof(hid_desc));
    return sizeof(usb_desc_hid_t);
}

static const usbus_descr_gen_funcs_t _hid_descriptor = {
    .fmt_post_descriptor = _gen_hid_descriptor,                    //
    .len                 = {.fixed_len = sizeof(usb_desc_hid_t)},  //
    .len_type            = USBUS_DESCR_LEN_FIXED                   //
};

static void _handle_tx_ready(event_t *ev) {
    comp_hid_device_t *dev = container_of(ev, comp_hid_device_t, tx_ready);

    usbdev_ep_ready(dev->ep_in->ep, dev->occupied);
}

static void _init(usbus_t *usbus, usbus_handler_t *handler) {
    comp_hid_device_t *dev = container_of(handler, comp_hid_device_t, handler_ctrl);

    dev->tx_ready.handler = _handle_tx_ready;

    dev->hid_descr.next  = NULL;
    dev->hid_descr.funcs = &_hid_descriptor;
    dev->hid_descr.arg   = dev;

    /*
       Configure Interface as USB_HID interface, choosing NONE for subclass and
       protocol in order to represent a generic I/O device
     */
    dev->iface.class     = USB_CLASS_HID;
    dev->iface.subclass  = dev->conf.id == KEYBOARD_INTERFACE ? USB_HID_SUBCLASS_BOOT : USB_HID_SUBCLASS_NONE;
    dev->iface.protocol  = dev->conf.id == KEYBOARD_INTERFACE ? USB_HID_PROTOCOL_KEYBOARD : USB_HID_PROTOCOL_NONE;
    dev->iface.descr_gen = &dev->hid_descr;
    dev->iface.handler   = handler;

    /* IN endpoint to send data to host */
    dev->ep_in = usbus_add_endpoint(usbus, &dev->iface, USB_EP_TYPE_INTERRUPT, USB_EP_DIR_IN, dev->conf.ep_size);

    dev->ep_in->interval = dev->conf.interval;

    usbus_enable_endpoint(dev->ep_in);

    usbus_add_interface(usbus, &dev->iface);
    // usbus_handler_set_flag(handler, USBUS_HANDLER_FLAG_RESET);
}

static void _event_handler(usbus_t *usbus, usbus_handler_t *handler, usbus_event_usb_t event) {
    (void)usbus;
    (void)handler;

    switch (event) {
        default:
            break;
    }
}

report_keyboard_t keyboard_report_sent                          = {{0}};
uint8_t           keyboard_idle __attribute__((aligned(2)))     = 0;
uint8_t           keyboard_protocol __attribute__((aligned(2))) = 1;

static int _control_handler(usbus_t *usbus, usbus_handler_t *handler, usbus_control_request_state_t state, usb_setup_t *setup) {
    comp_hid_device_t *dev = (comp_hid_device_t *)handler;

    /* Requests defined in USB HID 1.11 spec section 7 */
    switch (setup->request) {
        case USB_SETUP_REQ_GET_DESCRIPTOR: {
            uint8_t desc_type = setup->value >> 8;
            if (desc_type == USB_HID_DESCR_REPORT) {
                usbus_control_slicer_put_bytes(usbus, dev->conf.report_desc, dev->conf.report_desc_size);
                // Bodge to get windows to get past "IRP USBD_STATUS: USBD_STATUS_CANCELED"
                uint8_t status[2] = {0};
                usbus_control_slicer_put_bytes(usbus, status, sizeof(status));
            }
            else if (desc_type == USB_HID_DESCR_HID) {
                _gen_hid_descriptor(usbus, dev);
            }
            break;
        }
        case USB_HID_REQUEST_GET_REPORT:
            usbus_control_slicer_put_bytes(usbus, (uint8_t *)&keyboard_report_sent, sizeof(keyboard_report_sent));
            break;
        case USB_HID_REQUEST_SET_REPORT:
            if ((state == USBUS_CONTROL_REQUEST_STATE_OUTDATA)) {
                size_t   size = 0;
                uint8_t *data = usbus_control_get_out_data(usbus, &size);
                if (setup->index == KEYBOARD_INTERFACE) {
                    if (size == 2) {
                        keyboard_led_state = data[1];
                    } else if (size == 1) {
                        keyboard_led_state = data[0];
                    }
                } else{
                    if (size > 0) {
                        dev->cb(dev, data, size);
                    }
                }
            }
            break;
        case USB_HID_REQUEST_GET_PROTOCOL:
            if (setup->index == KEYBOARD_INTERFACE) {
                usbus_control_slicer_put_bytes(usbus, &keyboard_protocol, sizeof(keyboard_protocol));
            }
            break;
        case USB_HID_REQUEST_SET_PROTOCOL:
            if (setup->index == KEYBOARD_INTERFACE) {
                keyboard_protocol = (setup->value & 0xFF);
            }
            break;
        case USB_HID_REQUEST_GET_IDLE:
            if (setup->index == KEYBOARD_INTERFACE) {
                usbus_control_slicer_put_bytes(usbus, &keyboard_idle, sizeof(keyboard_idle));
            }
            break;
        case USB_HID_REQUEST_SET_IDLE:
            if (setup->index == KEYBOARD_INTERFACE) {
                keyboard_idle = ((setup->value & 0xFF00) >> 8);
            }
            break;
        default:
            return -1;
    }
    return 1;
}

static void _transfer_handler(usbus_t *usbus, usbus_handler_t *handler, usbdev_ep_t *ep, usbus_event_transfer_t event) {
    (void)usbus;
    (void)event;

    comp_hid_device_t *dev = (comp_hid_device_t *)handler;

    if ((ep->dir == USB_EP_DIR_IN) && (ep->type == USB_EP_TYPE_INTERRUPT)) {
        mutex_unlock(&dev->in_lock);
        dev->occupied = 0;
    } else if ((ep->dir == USB_EP_DIR_OUT) && (ep->type == USB_EP_TYPE_INTERRUPT)) {
        size_t len;
        usbdev_ep_get(ep, USBOPT_EP_AVAILABLE, &len, sizeof(size_t));
        if (len > 0) {
            dev->cb(dev, ep->buf, len);
        }
        usbdev_ep_ready(ep, 0);
    }
}

static const usbus_handler_driver_t hid_driver = {
    .init             = _init,             //
    .event_handler    = _event_handler,    //
    .control_handler  = _control_handler,  //
    .transfer_handler = _transfer_handler  //
};

static comp_hid_device_t hid[TOTAL_INTERFACES];

void usbdrv_init_interface(usbus_t *usbus, comp_hid_device_conf_t *conf) {
    comp_hid_device_t *dev = &hid[conf->id];

    mutex_init(&dev->in_lock);
    dev->usbus               = usbus;
    dev->handler_ctrl.driver = &hid_driver;
    dev->cb                  = _hid_rx_pipe;

    memcpy(&dev->conf, conf, sizeof(comp_hid_device_conf_t));

    usbus_register_event_handler(usbus, &dev->handler_ctrl);
}

usbus_t g_usbus;

void usbdrv_init(comp_hid_device_conf_t *config, size_t len) {
    usbdev_t *usbdev = usbdev_get_ctx(0);

    usbus_init(&g_usbus, usbdev);

    for (uint8_t id = 0; id < len; id++) {
        usbdrv_init_interface(&g_usbus, &config[id]);
    }

    static char _stack[USBUS_STACKSIZE];
    usbus_create(_stack, USBUS_STACKSIZE, USBUS_PRIO, USBUS_TNAME, &g_usbus);
}

void usbdrv_write(uint8_t id, const void *buffer, size_t len) {
    comp_hid_device_t *dev = &hid[id];

    uint8_t *buffer_ep = dev->ep_in->ep->buf;
    uint16_t max_size  = dev->ep_in->maxpacketsize;
    size_t   offset    = 0;

    while (len) {
        mutex_lock(&dev->in_lock);
        //TODO: Implement timeout???
        // uint8_t locked = mutex_trylock(&dev->in_lock);
        // if(locked == 0)
        //     return;

        if (len > max_size) {
            memmove(buffer_ep + offset, (uint8_t *)buffer + offset, max_size);
            offset += max_size;
            dev->occupied = max_size;
            len -= max_size;
        } else {
            memmove(buffer_ep + offset, (uint8_t *)buffer + offset, len);
            offset += len;
            dev->occupied = len;
            len           = 0;
        }
        usbus_event_post(dev->usbus, &dev->tx_ready);
    }
}