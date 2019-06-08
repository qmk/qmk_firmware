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
  NG_Q = SAFE_RANGE, // 薙刀式シフトキー
  NG_W,
  NG_E,
  NG_R,
  NG_T,
  NG_Y,
  NG_U,
  NG_I,
  NG_O,
  NG_P,

  NG_A,
  NG_S,
  NG_D,
  NG_F,
  NG_G,
  NG_H,
  NG_J,
  NG_K,
  NG_L,
  NG_SCLN,

  NG_Z,
  NG_X,
  NG_C,
  NG_V,
  NG_B,
  NG_N,
  NG_M,
  NG_COMM,
  NG_DOT,
  NG_SLSH,

  NGSHFT,
  CHR10,
  CHR20,
  CHR30,
  UP5,
  DOWN5,
  UP10,
  DOWN10,
  LEFT5,
  RGHT5,
} NGKEYS;

#define NG_SAFE_RANGE SAFE_RANGE+43

#define KC_NGSHFT NGSHFT
#define KC_CHR10 CHR10
#define KC_CHR20 CHR20
#define KC_CHR30 CHR30
#define KC_UP5 UP5
#define KC_DOWN5 DOWN5
#define KC_UP10 UP10
#define KC_DOWN10 DOWN10
#define KC_LEFT5 LEFT5
#define KC_RGHT5 RGHT5

