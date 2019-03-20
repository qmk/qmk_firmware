#include <stdio.h>
#include <string.h>
#include "switches.h"

static const char *BRAND_NAMES[] = {
  "Kailh",
  "Kailh Low Profile Choc",
  "Gateron",
  "Cherry MX",
  "Cherry ML",
  "Outemu",
  "Greetech",
  "Varmilo",
  "MOD",
  "Hako"
};

static const char *COLOR_NAMES[] = {
  "",
  "White",
  "Black",
  "Blue",
  "Red",
  "Yellow",
  "Brown",
  "Green",
  "Clear",
  "Silver",
  "Nature White",
  "Grey",
  "Jade",
  "Navy",
  "Burnt Orange",
  "Pale Blue",
  "Dark Yellow",
  "Gold",
  "Chocolate White",
  "Burgundy",
  "Purple",
  "Light Green",
  "True",
  "Berry",
  "Plum",
  "Sage",
  "Violet",
  "L",
  "M",
  "H",
  "SH"
};

static const char *VARIANT_NAMES[] = {
  "",
  "BOX",
  "BOX Thick",
  "BOX Heavy",
  "Silent",
  "Tactile",
  "Linear",
  "Speed",
  "Speed Heavy",
  "Speed Thick Click",
  "Pro",
  "Pro Heavy",
  "Royal",
  "Thick Click",
  "Heavy"
};

const char *brand_name(struct mechswitch ms) {
  return BRAND_NAMES[ms.brand - 1];
}

const char *variant_name(struct mechswitch ms) {
  return VARIANT_NAMES[ms.variant];
}

const char *color_name(struct mechswitch ms) {
  return COLOR_NAMES[ms.color];
}

void switch_name(struct mechswitch ms, char *buf) {
  const char *v_name = variant_name(ms);
  const char *c_name = color_name(ms);

  snprintf(buf, MAX_SWITCH_NAME_LENGTH, "%s", brand_name(ms));
  strncat(buf, " ", MAX_SWITCH_NAME_LENGTH - strlen(buf));
  if (strlen(v_name) > 0) {
    strncat(buf, v_name, MAX_SWITCH_NAME_LENGTH - strlen(buf));
    strncat(buf, " ", MAX_SWITCH_NAME_LENGTH - strlen(buf));
  }
  if (strlen(c_name) > 0) {
    strncat(buf, c_name, MAX_SWITCH_NAME_LENGTH - strlen(buf));
  }
}

int bitfieldtoi(struct mechswitch ms) {
  return ((ms.brand << 9) | (ms.variant << 5) | ms.color);
}
