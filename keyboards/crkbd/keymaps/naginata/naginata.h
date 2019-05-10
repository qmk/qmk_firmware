#define NGBUFFER 5 // バッファのサイズ

void naginata_type(void);
void ng_clear(void);
void ng_output(char[NGBUFFER][29][5], uint16_t, int);
bool process_naginata(uint16_t, keyrecord_t *, uint16_t, uint8_t, uint16_t[3]);