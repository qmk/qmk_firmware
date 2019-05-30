#define fnTimeout 500
#define randadd 59239
#define randmul 41149
#define randmod 60899

uint32_t layer_state_set_user(uint32_t state);

bool printSqlVerbs(uint16_t keycode, keyrecord_t *record);

bool updateLayerState(uint16_t keycode, keyrecord_t *record);

bool process_record_user(uint16_t keycode, keyrecord_t *record);
