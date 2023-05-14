
#pragma once

#include <stdint.h>

#include "pio_usb_configuration.h"

typedef enum {
  CONTROL_NONE,
  CONTROL_IN,
  CONTROL_OUT,
  CONTROL_COMPLETE,
  CONTROL_ERROR,
} control_transfer_operation_t;

typedef enum {
  EP_IN = 0x80,
  EP_OUT = 0x00,
} ep_type_t;

typedef enum {
  STAGE_SETUP,
  STAGE_DATA,
  STAGE_IN,
  STAGE_OUT,
  STAGE_STATUS,
  STAGE_COMPLETE,
  STAGE_ERROR
} setup_transfer_stage_t;

typedef enum {
  STAGE_IDLE,
  STAGE_DEVICE,
  STAGE_CONFIG,
  STAGE_CONFIG2,
  STAGE_INTERFACE,
  STAGE_ENDPOINT
} usb_enumeration_stage_t;

typedef struct {
  uint8_t *tx_address;
  uint8_t tx_length;
} packet_info_t;

typedef struct {
  volatile uint8_t data_in_num;
  volatile uint16_t buffer_idx;
  volatile uint8_t *rx_buffer;
  volatile packet_info_t setup_packet;
  volatile packet_info_t out_data_packet;
  volatile int16_t request_length;
  volatile control_transfer_operation_t operation;
  volatile setup_transfer_stage_t stage;
} control_pipe_t;

typedef struct {
  volatile uint8_t root_idx;
  volatile uint8_t dev_addr;
  bool need_pre;
  bool is_tx; // Host out or Device in

  volatile uint8_t ep_num;
  volatile uint16_t size;
  uint8_t buffer[64 + 4];
  volatile bool new_data_flag;
  volatile uint8_t attr;
  volatile uint8_t interval;
  volatile uint8_t interval_counter;
  volatile uint8_t data_id; // data0 or data1

  volatile bool stalled;
  volatile bool has_transfer;
  uint8_t *app_buf;
  uint16_t total_len;
  uint16_t actual_len;
  uint8_t error_count;
} endpoint_t;

typedef enum {
  EVENT_NONE,
  EVENT_CONNECT,
  EVENT_DISCONNECT,
  EVENT_HUB_PORT_CHANGE,
} usb_device_event_t;

typedef struct struct_usb_device_t usb_device_t;
typedef struct struct_root_port_t {
  volatile bool initialized;
  volatile bool addr0_exists;
  volatile uint8_t pin_dp;
  volatile uint8_t pin_dm;
  volatile usb_device_event_t event;
  usb_device_t *root_device;

  volatile bool is_fullspeed;
  volatile bool connected;
  volatile bool suspended;
  uint8_t mode;

  // register interface
  volatile uint32_t ints; // interrupt status
  volatile uint32_t ep_complete;
  volatile uint32_t ep_error;
  volatile uint32_t ep_stalled;

  // device only
  uint8_t dev_addr;
  uint8_t *setup_packet;
} root_port_t;

struct struct_usb_device_t {
  volatile bool connected;
  volatile bool enumerated;
  volatile usb_device_event_t event;
  volatile uint8_t address;
  volatile uint16_t vid;
  volatile uint16_t pid;
  volatile uint8_t device_class;
  volatile bool is_fullspeed;
  volatile bool is_root;
  control_pipe_t control_pipe;
  uint8_t endpoint_id[PIO_USB_DEV_EP_CNT];
  uint8_t child_devices[PIO_USB_HUB_PORT_CNT];
  struct struct_usb_device_t *parent_device;
  uint8_t parent_port;
  root_port_t *root;
};

enum {
  USB_SYNC = 0x80,
  USB_PID_OUT = 0xe1,
  USB_PID_IN = 0x69,
  USB_PID_SOF = 0xa5,
  USB_PID_SETUP = 0x2d,
  USB_PID_DATA0 = 0xc3,
  USB_PID_DATA1 = 0x4b,
  USB_PID_ACK = 0xd2,
  USB_PID_NAK = 0x5a,
  USB_PID_STALL = 0x1e,
  USB_PID_PRE = 0x3c,
  USB_CRC16_PLACE = 0,
};

enum {
  DESC_TYPE_DEVICE = 0x01,
  DESC_TYPE_CONFIG = 0x02,
  DESC_TYPE_STRING = 0x03,
  DESC_TYPE_INTERFACE = 0x04,
  DESC_TYPE_ENDPOINT = 0x05,
  DESC_TYPE_HID = 0x21,
  DESC_TYPE_HID_REPORT = 0x22,
};

enum {
  CLASS_HID = 0x03,
  CLASS_HUB = 0x09,
};

enum {
  EP_ATTR_CONTROL = 0x00,
  EP_ATTR_ISOCHRONOUS = 0x01,
  EP_ATTR_BULK = 0x02,
  EP_ATTR_INTERRUPT = 0x03,
  EP_ATTR_ENUMERATING = 0x80
};

typedef struct {
  //  uint8_t sync;
  //  uint8_t pid;
  uint8_t request_type;
  uint8_t request;
  uint8_t value_lsb;
  uint8_t value_msb;
  uint8_t index_lsb;
  uint8_t index_msb;
  uint8_t length_lsb;
  uint8_t length_msb;
  //  uint8_t crc16[2];
} usb_setup_packet_t;

typedef struct {
  uint8_t length;
  uint8_t type;
  uint8_t bcd_usb[2];
  uint8_t device_class;
  uint8_t subclass;
  uint8_t protocol;
  uint8_t max_packet_size;
  uint8_t vid[2];
  uint8_t pid[2];
  uint8_t bcd_device[2];
  uint8_t manufacture;
  uint8_t product;
  uint8_t serial;
  uint8_t num_configu;
} device_descriptor_t;

typedef struct {
  uint8_t length;
  uint8_t type;
  uint8_t string[62];
} __attribute__((aligned(2))) string_descriptor_t;

typedef struct {
  uint8_t length;
  uint8_t type;
  uint8_t inum;
  uint8_t altsetting;
  uint8_t numep;
  uint8_t iclass;
  uint8_t isubclass;
  uint8_t iprotocol;
  uint8_t iface;
} interface_descriptor_t;

typedef struct {
  uint8_t length;
  uint8_t type;
  uint8_t epaddr;
  uint8_t attr;
  uint8_t max_size[2];
  uint8_t interval;
} endpoint_descriptor_t;

typedef struct {
  uint8_t length;
  uint8_t type;
  uint8_t bcd_hid[2];
  uint8_t contry_code;
  uint8_t num_desc;
  uint8_t desc_type;
  uint8_t desc_len[2];
} hid_descriptor_t;

typedef struct configuration_descriptor_tag {
  uint8_t length;
  uint8_t type;
  uint8_t total_length_lsb;
  uint8_t total_length_msb;
  uint8_t num_interfaces;
  uint8_t configuration_value;
  uint8_t configuration;
  uint8_t attributes;
  uint8_t max_power;
} configuration_descriptor_t;

typedef struct {
  uint8_t lenght;
  uint8_t type;
  uint8_t port_num;
  uint8_t chara_lsb;
  uint8_t chara_msb;
  uint8_t pow_on_time;
  uint8_t current;
  uint8_t removable;
} hub_descriptor_t;

typedef struct {
  uint16_t port_status;
  uint16_t port_change;
} hub_port_status_t;

enum {
  HUB_SET_PORT_RESET = 4,
  HUB_SET_PORT_POWER = 8,
  HUB_CLR_PORT_CONNECTION = 16,
  HUB_CLR_PORT_ENABLE = 17,
  HUB_CLR_PORT_SUSPEND = 18,
  HUB_CLR_PORT_RESET = 20,
};

enum {
  HUB_STAT_PORT_CONNECTION = (1 << 0),
  HUB_STAT_PORT_ENABLE = (1 << 1),
  HUB_STAT_PORT_SUSPEND = (1 << 2),
  HUB_STAT_PORT_OC = (1 << 3),
  HUB_STAT_PORT_RESET = (1 << 4),
  HUB_STAT_PORT_POWER = (1 << 8),
  HUB_STAT_PORT_LOWSPEED = (1 << 9),
};

enum {
  HUB_CHANGE_PORT_CONNECTION = (1 << 0),
  HUB_CHANGE_PORT_ENABLE = (1 << 1),
  HUB_CHANGE_PORT_SUSPEND = (1 << 2),
  HUB_CHANGE_PORT_OC = (1 << 3),
  HUB_CHANGE_PORT_RESET = (1 << 4),
};

enum {
  USB_REQ_DIR_IN = 0x80,
  USB_REQ_DIR_OUT = 0x00,
  USB_REQ_TYP_STANDARD = 0x00,
  USB_REQ_TYP_CLASS = 0x20,
  USB_REQ_TYP_VENDOR = 0x40,
  USB_REQ_REC_DEVICE = 0x00,
  USB_REQ_REC_IFACE = 0x01,
  USB_REQ_REC_EP = 0x02,
  USB_REQ_REC_OTHER = 0x03,
};

#define GET_DEVICE_DESCRIPTOR_REQ_DEFAULT                                      \
  { USB_REQ_DIR_IN, 0x06, 0, 0x01, 0, 0, 0x12, 0 }
#define GET_CONFIGURATION_DESCRIPTOR_REQ_DEFAULT                               \
  { USB_REQ_DIR_IN, 0x06, 0, 0x02, 0, 0, 0x09, 0 }
#define SET_CONFIGURATION_REQ_DEFAULT                                          \
  { USB_REQ_DIR_OUT, 0x09, 0, 0, 0, 0, 0, 0 }
#define SET_ADDRESS_REQ_DEFAULT                                                \
  { USB_REQ_DIR_OUT, 0x5, 0x02, 0, 0, 0, 0, 0 }
#define SET_HID_IDLE_REQ_DEFAULT                                               \
  { USB_REQ_TYP_CLASS | USB_REQ_REC_IFACE, 0x0A, 0, 0, 0, 0, 0, 0 }
#define GET_HID_REPORT_DESCRIPTOR_DEFAULT                                      \
  { USB_REQ_DIR_IN | USB_REQ_REC_IFACE, 0x06, 0, 0x22, 0, 0, 0xff, 0 }
#define GET_HUB_DESCRPTOR_REQUEST                                              \
  {                                                                            \
    USB_REQ_DIR_IN | USB_REQ_TYP_CLASS | USB_REQ_REC_DEVICE, 0x06, 0, 0x29, 0, \
        0, 8, 0                                                                \
  }
#define GET_HUB_PORT_STATUS_REQUEST                                            \
  {                                                                            \
    USB_REQ_DIR_IN | USB_REQ_TYP_CLASS | USB_REQ_REC_OTHER, 0, 0, 0, 0, 0, 4,  \
        0                                                                      \
  }
#define SET_HUB_FEATURE_REQUEST                                                \
  {                                                                            \
    USB_REQ_DIR_OUT | USB_REQ_TYP_CLASS | USB_REQ_REC_OTHER, 0x03, 0, 0, 0, 0, \
        0, 0                                                                   \
  }
#define CLEAR_HUB_FEATURE_REQUEST                                              \
  {                                                                            \
    USB_REQ_DIR_OUT | USB_REQ_TYP_CLASS | USB_REQ_REC_OTHER, 0x01, 0, 0, 0, 0, \
        0, 0                                                                   \
  }

typedef struct {
  const uint8_t *device;
  const uint8_t *config;
  const uint8_t **hid_report;
  const string_descriptor_t *string;
} usb_descriptor_buffers_t;
