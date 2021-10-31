
// tap dance keys
enum tap_dance {
  _ASTR = 0
 ,_BSPC
 ,_EMOJ
 ,_COMM
 ,_DOT
 ,_PASTE
 ,_PERC
 ,_PRIV
 ,_SEND
 ,_SPC
 ,_TILD
 ,_XPASTE
#ifdef HASKELL
 ,_COLN
 ,_LT
 ,_GT
#endif
};

#define TD_ASTR   TD(_ASTR)
#define TD_BSPC   TD(_BSPC)
#define TD_EMOJ   TD(_EMOJ)
#define TD_COMM   TD(_COMM)
#define TD_DOT    TD(_DOT)
#define TD_PASTE  TD(_PASTE)
#define TD_PERC   TD(_PERC)
#define TD_PRIV   TD(_PRIV)                 // compile time macro string, provided in private_string.h
#define TD_SEND   TD(_SEND)                 // config.h defined macro string
#define TD_SPC    TD(_SPC)                  // see process_record_user() for extended handling of Spc
#define TD_TILD   TD(_TILD)
#define TD_XPASTE TD(_XPASTE)
#ifdef HASKELL
#define TD_COLN   TD(_COLN)
#define TD_LT     TD(_LT)
#define TD_GT     TD(_GT)
#endif
