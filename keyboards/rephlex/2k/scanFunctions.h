void update_extremum(key_t *key);
void register_key(matrix_row_t *current_row, uint8_t current_col);
void deregister_key(matrix_row_t *current_row, uint8_t current_col);
void recalibrate(uint16_t rest_adc_value);

void matrix_read_cols_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, key_t *key);
void matrix_read_cols_continuous_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, key_t *key);
void matrix_read_cols_static_actuation(matrix_row_t *current_row, uint8_t current_col, key_t *key);