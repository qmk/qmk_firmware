

#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint16_t usage;
  int32_t usage_maximum;
  int32_t usage_minimum;
} hid_report_local_member_t;

typedef struct struct_hid_report_member {
  struct {
    uint16_t usage_page;
    int16_t logical_maximum;
    int16_t logical_minimum;
    uint8_t report_size;
    uint8_t report_count;
  } global;

  hid_report_local_member_t local;

  struct struct_hid_report_member *next;
} hid_report_member_t;

typedef struct {
  uint8_t prefix;
  uint8_t tag;
  uint8_t type;
  uint8_t size;
  int16_t data;
  uint16_t raw;
} hid_report_item_t;

typedef struct struct_hid_id_collection {
  uint8_t id;
  uint16_t usage_page;
  uint16_t usage;
  hid_report_member_t *report_def_start;
  struct struct_hid_id_collection *next;
} hid_id_collection_t;

typedef struct {
  uint8_t interface;
  hid_id_collection_t *id_collection;
} hid_device_t;

#define HID_DEVICE_COUNT 8
#define HID_ID_COLLECTION_COUNT 16
#define HID_REPORT_MEMBER_COUNT 32
#define HID_USAGE_COUNT 32

bool parse_report_descriptor(uint8_t interface,
                             uint8_t const *desc, uint16_t len);
void print_hid_device(uint8_t interface);

hid_device_t const * get_hid_device_def(uint8_t interface);
