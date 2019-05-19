void naginata_type(void);
void naginata_clear(void);

void naginata_mode(uint16_t, keyrecord_t *);

void naginata_on(void);
void naginata_off(void);
bool naginata_state(void);

void naginata_edit_left_on(void);
void naginata_edit_right_on(void);
void naginata_edit_off(void);
bool naginata_edit_state(void);

bool process_naginata(uint16_t, keyrecord_t *);
void set_naginata(uint8_t);

#ifdef NAGINATA_EDIT_MODE
bool process_naginata_edit(uint16_t, keyrecord_t *);
void set_naginata_edit(uint8_t, uint8_t);
#endif

typedef enum naginata_keycodes {
  NGSHFT = SAFE_RANGE, // 薙刀式シフトキー
  CHR10,
  CHR20,
  CHR30,
  UP5,
  DOWN5,
  LEFT5,
  RGHT5,
} NGKEYS;

#define NG_SAFE_RANGE SAFE_RANGE+8