

#include "report_descriptor_parser.h"
#include "report_descriptor_tags.h"

#include <stddef.h>
#include <string.h> // memset

#ifdef __AVR__
#    define NO_PRINT
#endif

#include "debug.h"
#include "print.h"

#define LEN(x) (sizeof(x) / sizeof(x[0]))

hid_device_t hid_device_collection[HID_DEVICE_COUNT];
hid_id_collection_t hid_id_collections[HID_ID_COLLECTION_COUNT];
hid_report_member_t hid_report_definitions[HID_REPORT_MEMBER_COUNT];

hid_device_t const *get_hid_device_def(uint8_t interface) {
  for (int idx = 0; idx < LEN(hid_device_collection); idx++) {
    if (hid_device_collection[idx].interface == interface) {
      return &hid_device_collection[idx];
    }
  }

  return NULL;
}

static hid_device_t *find_empty_device(void) {
  for (int idx = 0; idx < LEN(hid_device_collection); idx++) {
    if (hid_device_collection[idx].id_collection == NULL) {
      return &hid_device_collection[idx];
    }
  }

  // full
  return NULL;
}

static hid_id_collection_t *find_empty_id_idx_begin(void) {
  for (int idx = 0; idx < LEN(hid_id_collections); idx++) {
    if (hid_id_collections[idx].report_def_start == NULL) {
      return &hid_id_collections[idx];
    }
  }

  // full
  return NULL;
}

static hid_report_member_t *find_empty_report_def(void) {
  for (int idx = 0; idx < LEN(hid_report_definitions); idx++) {
    if (hid_report_definitions[idx].global.report_size == 0) {
      return &hid_report_definitions[idx];
    }
  }

  // full
  return NULL;
}

static void delete_hid_id_collection(hid_id_collection_t *collection) {

  // delete report defs
  hid_report_member_t *next = collection->report_def_start;
  while (next != NULL) {
    hid_report_member_t *del = next;
    next = del->next;
    memset(del, 0, sizeof(*del));
  }

  memset(collection, 0, sizeof(*collection));
}

static void delete_hid_device(uint8_t interface) {
  for (int idx = 0; idx < LEN(hid_device_collection); idx++) {
    if (hid_device_collection[idx].interface == interface) {
      if (hid_device_collection[idx].id_collection == NULL) {
        return;
      }

      hid_id_collection_t *next = hid_device_collection[idx].id_collection;
      while (next != NULL) {
        hid_id_collection_t *del = next;
        next = next->next;
        delete_hid_id_collection(del);
      }

      memset(&hid_device_collection[idx], 0,
             sizeof(hid_device_collection[idx]));
    }
  }
}

static bool get_next_item(uint8_t const **buf, uint16_t *const len,
                          hid_report_item_t *const item) {
  uint8_t const *data = *buf;

  item->prefix = data[0];
  item->tag = (data[0] >> 4) & 0x0F;
  item->type = (data[0] >> 2) & 0x03;
  item->size = (data[0]) & 0x03;

  (*buf)++;

  if (item->tag == 0x0F) {
    // Long item
    item->size = data[1];
    item->data = 0;
    item->raw = 0;
    *buf += item->size;
  } else {
    // short item

    // set initial data value
    item->raw = 0;
    switch (item->size) {
    case 2:
      item->raw |= ((uint16_t)data[2]) << 8;
    // no-break
    case 1:
      item->raw |= data[1];
    // no-break
    case 0:
      *buf += item->size;
      break;
    default:
      // error
      return false;
      break;
    }
  }

  // padding sign bits
  item->data = item->raw;
  if (item->size == 2 && (item->raw & 0x8000)) {
    item->data |= 0xFFFF0000;
  } else if (item->size == 1 && (item->raw & 0x80)) {
    item->data |= 0xFFFFFF00;
  }

  if (*buf - data > *len) {
    *len = 0;
    return false;
  } else {
    *len = *len - (*buf - data);
    return true;
  }
}

bool parse_report_descriptor(uint8_t interface, uint8_t const *desc,
                             uint16_t len) {
  uint8_t const *buf = desc;
  uint16_t remain_len = len;

  hid_report_item_t item = {0};
  hid_report_member_t member = {0};

  delete_hid_device(interface);

  hid_device_t *hid_device = find_empty_device();

  if (hid_device == NULL) {
    dprintln("No empty hid device table");
    return false;
  }

  hid_device->interface = interface;
  hid_device->id_collection = NULL;

  // Initialize first collection
  hid_report_member_t *current_member = NULL;
  hid_id_collection_t *current_collection = NULL;
  int8_t level = 0;
  uint16_t usage_table[HID_USAGE_COUNT] = {0};
  uint16_t usage_table_idx = 0;
  uint16_t top_usage_page = 0;
  uint16_t top_usage = 0;

  while (get_next_item(&buf, &remain_len, &item)) {
    for (int idx = 0; idx < level; idx++) {
      dprintf("  ");
    }
    dprintf("0x%02X 0x%02X\t\t\t", item.prefix, item.data);

    switch (item.prefix & (HID_RI_TYPE_MASK | HID_RI_TAG_MASK)) {
    case HID_RI_COLLECTION(0):
      dprintln("Start collection");

      if (level == 0) {
        current_collection = find_empty_id_idx_begin();
        if (current_collection == NULL) {
          dprintln("No empty collection");
          break;
        } else {
          dprintf("Register to collection 0x%08X\n", current_collection);
        }

        current_collection->usage = top_usage;
        current_collection->usage_page = top_usage_page;
        current_member = NULL;
      }
      usage_table_idx = 0;
      level++;

      break;

    case HID_RI_END_COLLECTION(0):
      dprintln("End collection");

      if (level == 1) {
        if (current_collection != NULL &&
            current_collection->report_def_start != NULL) {
          dprintf("New collection defined 0x%08X\n", current_collection);

          if (hid_device->id_collection == NULL) {
            hid_device->id_collection = current_collection;
          } else {
            hid_id_collection_t *tail = hid_device->id_collection;
            while (tail->next != NULL) {
              tail = tail->next;
            }
            tail->next = current_collection;
          }
        }
        current_collection = NULL;
        current_member = NULL;
        usage_table_idx = 0;
      }

      level--;
      break;

    case HID_RI_REPORT_ID(0):
      dprintf("Report id %d\n", item.raw);

      if (current_collection != NULL) {
        current_collection->id = item.raw;
      }
      break;

    case HID_RI_USAGE_PAGE(0):
      dprintf("Usage Page %d\n", item.raw);
      if (level == 0) {
        top_usage_page = item.raw;
      } else {
        member.global.usage_page = item.raw;
      }
      break;

    case HID_RI_USAGE(0):
      dprintf("Usage %d\n", item.raw);

      if (usage_table_idx >= LEN(usage_table)) {
        dprintln("Error");
        break;
      }

      if (level == 0) {
        top_usage = item.raw;
      } else {
        usage_table[usage_table_idx] = item.raw;
        usage_table_idx++;
      }

      break;

    case HID_RI_USAGE_MINIMUM(0):
      dprintf("Usage minimum %d\n", item.data);

      member.local.usage_minimum = item.data;
      break;

    case HID_RI_USAGE_MAXIMUM(0):
      dprintf("Usage maximum %d\n", item.data);

      member.local.usage_maximum = item.data;
      break;

    case HID_RI_LOGICAL_MINIMUM(0):
      dprintf("Logical minimum %d\n", item.data);

      member.global.logical_minimum = item.data;
      break;

    case HID_RI_LOGICAL_MAXIMUM(0):
      dprintf("Logical maximum %d\n", item.data);

      member.global.logical_maximum = item.data;
      break;

    case HID_RI_REPORT_SIZE(0):
      dprintf("Report size %d\n", item.raw);

      member.global.report_size = item.raw;
      break;

    case HID_RI_REPORT_COUNT(0):
      dprintf("Report count %d\n", item.raw);

      member.global.report_count = item.raw;
      break;

    case HID_RI_INPUT(0):
      dprintf("Input %d\n", item.raw);
      // apply member
      usage_table_idx = usage_table_idx > 0 ? usage_table_idx : 1;
      member.global.report_count /= usage_table_idx;

      for (int idx = 0; idx < usage_table_idx; idx++) {
        hid_report_member_t *new_member = find_empty_report_def();

        if (new_member == NULL) {
          dprintln("No empty table");
          break;
        } else {
          dprintf("Register to report table 0x%04X\n", new_member);
        }

        member.local.usage = usage_table[idx];
        *new_member = member;

        dprintln("Apply new member");

        if (current_member != NULL) {
          current_member->next = new_member;
        } else if (current_collection != NULL &&
                   current_collection->report_def_start == NULL) {
          current_collection->report_def_start = new_member;
        }

        current_member = new_member;
      }

      // reset_local_member
      hid_report_local_member_t local_member = {0};
      member.local = local_member;
      usage_table_idx = 0;
      memset(usage_table, 0, sizeof(usage_table));

      break;

    case HID_RI_OUTPUT(0):
      dprintf("Output %d\n", item.raw);
      break;

    default:
      dprintln("Not implemented");
      break;
    }
  }

  //
  // Compress collections
  //
  if (hid_device == NULL || hid_device->id_collection == NULL) {
    return false;
  }

  hid_id_collection_t *base = hid_device->id_collection;
  hid_id_collection_t *collection = hid_device->id_collection->next;

  while (collection != NULL) {
    if (collection->id == 0) {
      hid_report_member_t *tail = base->report_def_start;

      if (tail == NULL)
        break;

      while (tail->next != NULL) {
        tail = tail->next;
      }
      tail->next = collection->report_def_start;

      hid_id_collection_t *del = collection;
      collection = collection->next;
      base->next = collection;
      memset(del, 0, sizeof(*del));
    } else {
      base = collection;
      collection = base->next;
    }
  }

  dprintln("New HID is defined");

  return true;
}

void print_hid_report_member(hid_report_member_t const *member) {
  // clang-format off
  dprintf("{"
         "\tSize:%d Count:%d\n"
         "\tUsagePage:%d Usage:%d\n"
         "\tLogicalMin:%d Max:%d\n"
         "\tUsageMin:%d Max:%d\n"
         "}",
         member->global.report_size, member->global.report_count,
         member->global.usage_page, member->local.usage,
         member->global.logical_minimum, member->global.logical_maximum,
         member->local.usage_minimum, member->local.usage_maximum
        );
  // clang-format on
}

void print_collection(hid_id_collection_t const *collection) {
  dprintf("ID:%u, USAGE_PAGE:%u, USAGE:%u\n", collection->id,
          collection->usage_page, collection->usage);
  hid_report_member_t const *member = collection->report_def_start;

  while (member != NULL) {
    print_hid_report_member(member);
    member = member->next;
  }
  dprintf("\n");
}

void print_hid_device(uint8_t interface) {
  dprintf("Print interface:%d\n", interface);

  for (int idx = 0; idx < LEN(hid_device_collection); idx++) {
    hid_device_t const *device = &hid_device_collection[idx];
    if (device->interface == interface) {
      hid_id_collection_t const *collection = device->id_collection;
      if (collection == NULL) {
        dprintln("Invalid data");
      }
      while (collection != NULL) {
        print_collection(collection);
        collection = collection->next;
      }
    }
  }

  dprintf("\n");
  dprintf("\n");
}
