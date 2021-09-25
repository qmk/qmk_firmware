

#include "report_parser.h"
#include "report_descriptor_parser.h"

#include <stddef.h>
#include "print.h"

#define LEN(x) (sizeof(x) / sizeof(x[0]))

typedef struct {
  uint8_t usage_page;
  uint8_t usage;
  void (*parser)(hid_report_member_t const *member, uint8_t const *data,
                 uint8_t len);
} report_parser_table_t;

void keyboard_report_parser(hid_report_member_t const *member,
                            uint8_t const *data, uint8_t len);
void mouse_report_parser(hid_report_member_t const *member, uint8_t const *data,
                         uint8_t len);
void system_report_parser(hid_report_member_t const *member,
                          uint8_t const *data, uint8_t len);
void consumer_report_parser(hid_report_member_t const *member,
                            uint8_t const *data, uint8_t len);
__attribute__((weak)) void
vendor_report_parser(uint16_t usage_page, hid_report_member_t const *member, uint8_t const *data,
                     uint8_t len);

bool parse_report(uint8_t interface,
                  uint8_t const *report, uint8_t len) {
  hid_device_t const *device = get_hid_device_def(interface);

  if (device == NULL) {
    return false;
  }

  hid_id_collection_t const *collection = device->id_collection;

  if (collection->id != 0) {
    while (collection != NULL && report[0] != collection->id) {
      collection = collection->next;
    }

    if (collection != NULL) {
      report = &report[1];
      len--;
    }
  }

  if (collection == NULL) {
    return false;
  }

  hid_report_member_t const *member = collection->report_def_start;

  if (member == NULL) {
    return false;
  }

  uint16_t usage_id = (collection->usage_page << 8) | collection->usage;
  typedef void (*parser_func_t)(hid_report_member_t const *, uint8_t const *,
                 uint8_t);
  parser_func_t func;

  switch (usage_id) {
    case 0x0106:
      func = keyboard_report_parser;
    break;
    case 0x0102:
      func = mouse_report_parser;
    break;
    case 0x0180:
      func = system_report_parser;
    break;
    case 0x0C01:
      func = consumer_report_parser;
    break;
  default:
    vendor_report_parser(collection->usage_page, member, report, len);
    return false;
    break;
  }

  func(member, report, len);

  return true;
}

void keyboard_report_parser(hid_report_member_t const *member,
                            uint8_t const *data, uint8_t len) {
  keyboard_parse_result_t result = {0};

  while (member != NULL) {
    uint16_t bit_idx = 0;
    if (member->global.usage_page == 0x07) {
      if (member->global.report_size == 1) {
        for (int idx = 0; idx < member->global.report_count; idx++) {
          if (*data & (1 << (bit_idx & 0x07))) {
            uint8_t keycode = bit_idx + member->local.usage_minimum;
            result.bits[keycode >> 3] |= (1 << (keycode & 0x07));
          }

          bit_idx++;

          if ((bit_idx & 0x7) == 0) {
            data++;
            len--;
          }
        }
      } else if (member->global.report_size == 8) {
        for (int idx = 0; idx < member->global.report_count; idx++) {
          if (*data != 0) {
            uint8_t keycode = *data + member->local.usage_minimum;
            result.bits[keycode >> 3] |= (1 << (keycode & 0x07));
          }
          data++;
          len--;
        }
      }
    }

    member = member->next;
  }

  keyboard_report_hook(&result);
}

static int16_t parse_value(hid_report_member_t const *member, uint8_t const *data,
                    uint16_t *bit_idx) {
  int16_t result = 0;

  uint8_t const *b = &data[*bit_idx / 8];
  uint8_t local_bit_idx = *bit_idx % 8;
  uint8_t offset = 0;

  if (member != NULL) {
    for (uint8_t idx = 0; idx < member->global.report_count; idx++) {
      for (uint8_t dst_bit_idx = 0; dst_bit_idx < member->global.report_size;
           dst_bit_idx++) {
        if (*b & (1 << local_bit_idx)) {
          result |= (1 << offset);
        }
        offset++;
        (*bit_idx)++;

        if (++local_bit_idx == 8) {
          local_bit_idx = 0;
          b++;
        }
      }
    }

    if (member->global.report_size != 1) {
      if (result & (1 << (member->global.report_size - 1))) {
        result |= ~((1 << member->global.report_size) - 1);
      }

      if (member->local.usage_maximum != 0) {
        result += member->local.usage_minimum - member->global.logical_minimum;
      }
      // TODO: physical min, max
    }
  }

  return result;
}

void mouse_report_parser(hid_report_member_t const *member, uint8_t const *data,
                         uint8_t len) {
  mouse_parse_result_t result = {0};

  uint16_t bit_idx = 0;
  while (member != NULL) {
    uint32_t usage_id =
        (((uint32_t)member->global.usage_page) << 16) | member->local.usage;

    uint16_t bit_idx_cur = bit_idx;
    int16_t val = parse_value(member, data, &bit_idx);

    switch (usage_id) {
    case 0x00090000 ... 0x00090001: // Pointer, Buttons
      result.button |= (val << (bit_idx_cur & 0x07));
      break;

    case 0x00010030: // Generic, X
      result.x = val;
      break;

    case 0x00010031: // Generic, Y
      result.y = val;
      break;

    case 0x00010038: // Generic, Wheel
      result.v = val;
      break;

    case 0x000C0238: // Consumer, AC Pan
      result.h = val;
      break;

    case 0xFF000000: // SlimBlade, Button 3,4
      result.button |= (val << ((bit_idx_cur + 2) & 0x0F));
      break;

    default:
      result.undefined |= (val << (bit_idx_cur & 0x0F));
      break;
    }

    member = member->next;
  }

  mouse_report_hook(&result);
}

void system_report_parser(hid_report_member_t const *member,
                          uint8_t const *data, uint8_t len) {
  uint16_t result = 0;
  uint16_t bit_idx = 0;

  while (member != NULL) {
    result = parse_value(member, data, &bit_idx);

    if (result != 0) {
      if (member->global.report_size == 1) {
        system_report_hook(member->local.usage);
      } else {
        system_report_hook(result);
      }
    }

    member = member->next;
  }
}

void consumer_report_parser(hid_report_member_t const *member,
                            uint8_t const *data, uint8_t len) {
  uint16_t result;
  uint16_t bit_idx = 0;

  while (member != NULL) {
    result = parse_value(member, data, &bit_idx);

    if (result != 0) {
      if (member->global.report_size == 1) {
        consumer_report_hook(member->local.usage);
      } else {
        consumer_report_hook(result);
      }
    }

    member = member->next;
  }
}
