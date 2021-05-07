#pragma once

enum userspace_custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // Can always be here
  FAT_ARROW, // =>
  SKINNY_ARROW, // ->
  REVERSE_ARROW, // <-
  CONCAT, // <>
  MAP, // <$>
  MAP_FLIPPED, // <#>
  FLAP, // <@>
  PIPE, // |>
  ALT, // <|>
  APPLY, // <*>
  AND, // &&
  OR, // ||
  BIND, // >>=
  BIND_FLIPPED, // =<<
  VOID_LEFT, // <$
  VOID_RIGHT, // $>
  DOUBLE_COLON, // ::
  FLASH // Handle keyboard flashing
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
