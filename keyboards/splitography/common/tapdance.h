// tap dance keys
enum tap_dance {
  _ASTR = 0
 ,_BSPC
 ,_COLM
 ,_COLN
 ,_COMM
 ,_DEL
 ,_DOT
 ,_DQOT
 ,_EMOJ
 ,_ENT
 ,_EQL
 ,_GRV
 ,_GT
 ,_LT
 ,_PASTE
 ,_PERC
 ,_QUOT
 ,_SCLN
 ,_SEND
 ,_SPC
 ,_TILD
 ,_XPASTE
};

#define TD_ASTR   TD(_ASTR)
#define TD_BSPC   TD(_BSPC)
#define TD_COMM   TD(_COMM)
#define TD_COLM   TD(_COLM)
#define TD_COLN   TD(_COLN)
#define TD_DEL    TD(_DEL)
#define TD_DOT    TD(_DOT)
#define TD_DQOT   TD(_DQOT)
#define TD_EMOJ   TD(_EMOJ)
#define TD_ENT    TD(_ENT)
#define TD_EQL    TD(_EQL)
#define TD_GRV    TD(_GRV)
#define TD_GT     TD(_GT)
#define TD_LT     TD(_LT)
#define TD_PASTE  TD(_PASTE)
#define TD_PERC   TD(_PERC)
#define TD_QUOT   TD(_QUOT)
#define TD_SCLN   TD(_SCLN)
#define TD_SEND   TD(_SEND) // config.h defined macro string
#define TD_SPC    TD(_SPC) // see process_record_user() for extended handling of Spc
#define TD_TILD   TD(_TILD)
#define TD_XPASTE TD(_XPASTE)
