#include "brett.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case FAT_ARROW:
      if (record->event.pressed) {
        SEND_STRING("=>");
      }
      return false;
      break;
    case SKINNY_ARROW:
      if (record->event.pressed) {
        SEND_STRING("->");
      }
      return false;
      break;
    case REVERSE_ARROW:
      if (record->event.pressed) {
        SEND_STRING("<-");
      }
      return false;
      break;
    case CONCAT:
      if (record->event.pressed) {
        SEND_STRING("<>");
      }
      return false;
      break;
    case MAP:
      if (record->event.pressed) {
        SEND_STRING("<$>");
      }
      return false;
      break;
    case MAP_FLIPPED:
      if (record->event.pressed) {
        SEND_STRING("<#>");
      }
      return false;
      break;
    case FLAP:
      if (record->event.pressed) {
        SEND_STRING("<@>");
      }
      return false;
      break;
    case PIPE:
      if (record->event.pressed) {
        SEND_STRING("|>");
      }
      return false;
      break;
    case ALT:
      if (record->event.pressed) {
        SEND_STRING("<|>");
      }
      return false;
      break;
    case APPLY:
      if (record->event.pressed) {
        SEND_STRING("<*>");
      }
      return false;
      break;
    case AND:
      if (record->event.pressed) {
        SEND_STRING("&&");
      }
      return false;
      break;
    case OR:
      if (record->event.pressed) {
        SEND_STRING("||");
      }
      return false;
      break;
    case BIND:
      if (record->event.pressed) {
        SEND_STRING(">>=");
      }
      return false;
      break;
    case BIND_FLIPPED:
      if (record->event.pressed) {
        SEND_STRING("=<<");
      }
      return false;
      break;
    case DOUBLE_COLON:
      if (record->event.pressed) {
        SEND_STRING("::");
      }
      return false;
      break;
    case VOID_LEFT:
      if (record->event.pressed) {
        SEND_STRING("<$");
      }
      return false;
      break;
    case VOID_RIGHT:
      if (record->event.pressed) {
        SEND_STRING("$>");
      }
      return false;
      break;
  }
  return true;
}
