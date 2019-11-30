
// tap dance keys
enum tap_dance {
  _ASTR = 0
 ,_COMM
 ,_DOT
 ,_ENT
 ,_PRIV
 ,_SEND
 ,_SPC
 ,_SCLN
 ,_TILD
#ifdef HASKELL
 ,_COLN
 ,_LT
 ,_GT
 ,_EQL
#endif
};

#define TD_ASTR TD(_ASTR)
#define TD_COMM TD(_COMM)
#define TD_DOT  TD(_DOT)
#define TD_ENT  TD(_ENT)
#define TD_PRIV TD(_PRIV)                   // compile time macro string, provided in private_string.h
#define TD_SEND TD(_SEND)                   // config.h defined macro string
#define TD_SPC  TD(_SPC)                    // see process_record_user() for extended handling of Spc
#define TD_SCLN TD(_SCLN)
#define TD_TILD TD(_TILD)
#ifdef HASKELL
#define TD_COLN TD(_COLN)
#define TD_LT   TD(_LT)
#define TD_GT   TD(_GT)
#define TD_EQL  TD(_EQL)
#endif
