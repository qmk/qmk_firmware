char keylog[40] = {};
int keylogs_idx = 0;

char code_to_name[][4] = {
    {"NO"},{" "},{" "},{" "},{"A"},{"B"},{"C"},{"D"},{"E"},{"F"},{"G"},{"H"},
    {"I"},{"J"},{"K"},{"L"},{"M"},{"N"},{"O"},{"P"},{"Q"},{"R"},{"S"},{"T"},
    {"U"},{"V"},{"W"},{"X"},{"Y"},{"Z"},{"1"},{"2"},{"3"},{"4"},{"5"},{"6"},
    {"7"},{"8"},{"9"},{"0"},{"ENT"},{"ESC"},{"BSPC"},{"TAB"},{"SPC"},{"MINS"},
    {"EQL"},{"LBRC"},{"RBRC"},{"BSLS"},{"NUHS"},{"SCLN"},{"QUOT"},{"GRV"},
    {"COMM"},{"DOT"},{"SLSH"},{"CAPS"},{"F1"},{"F2"},{"F3"},{"F4"},{"F5"},
    {"F6"},{"F7"},{"F8"},{"F9"},{"F10"},{"F11"},{"F12"},{"PSCR"},{"SLCK"},
    {"PAUS"},{"INS"},{"HOME"},{"PGUP"},{"DEL"},{"END"},{"PGDN"},{"RGHT"},
    {"LEFT"},{"DOWN"},{"UP"},{"NLCK"},{"PSLS"},{"PAST"},{"PMNS"},{"PPLS"},
    {"PENT"},{"P1"},{"P2"},{"P3"},{"P4"},{"P5"},{"P6"},{"P7"},{"P8"},{"P9"},
    {"P0"},{"PDOT"},{"NUBS"},{"APP"},{"POW"},{"PEQL"},{"F13"},{"F14"},{"F15"},
    {"F16"},{"F17"},{"F18"},{"F19"},{"F20"},{"F21"},{"F22"},{"F23"},{"F24"},
    };

void set_keylog(uint16_t keycode, keyrecord_t *record)
{
  char name[4] = "?";
  if (keycode < 117)
  {
    for (int i = 0; i < 4; i++)
    {
      name[i] = code_to_name[keycode][i];
    }
  }

  // update keylog
  snprintf(keylog, sizeof(keylog), "KC_%s (ID %d)",
           name,
           keycode);
}

char *read_keylog(void) {
  return keylog;
}
