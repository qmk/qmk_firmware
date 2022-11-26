#define fnTimeout 500


layer_state_t layer_state_set_user(layer_state_t state);

bool printSqlVerbs(uint16_t keycode, keyrecord_t *record);

bool updateLayerState(uint16_t keycode, keyrecord_t *record);

bool process_record_user(uint16_t keycode, keyrecord_t *record);
