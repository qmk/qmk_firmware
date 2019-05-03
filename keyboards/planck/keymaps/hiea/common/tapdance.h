
// tap dance keys
enum tap_dance {
  _CAPS = 0
 ,_COLN
 ,_COMM
 ,_DOT
 ,_DQOT
 ,_ENT
 ,_EQL
 ,_GRV
 ,_GT
 ,_LBRC
 ,_LCBR
 ,_LPRN
 ,_LT
 ,_PRIV
 ,_QUOT
 ,_RBRC
 ,_RCBR
 ,_RNGL
 ,_RPRN
 ,_SEND
 ,_SPC
 ,_TILD
};

#define TD_CAPS TD(_CAPS)
#define TD_COLN TD(_COLN)
#define TD_COMM TD(_COMM)
#define TD_DOT  TD(_DOT)
#define TD_DQOT TD(_DQOT)
#define TD_ENT  TD(_ENT)
#define TD_EQL  TD(_EQL)
#define TD_GRV  TD(_GRV)
#define TD_GT   TD(_GT)
#define TD_LBRC TD(_LBRC)
#define TD_LCBR TD(_LCBR)
#define TD_LPRN TD(_LPRN)
#define TD_LT   TD(_LT)
#define TD_PRIV TD(_PRIV)                   // compile time macro string, provided in private_string.h
#define TD_QUOT TD(_QUOT)
#define TD_RBRC TD(_RBRC)
#define TD_RCBR TD(_RCBR)
#define TD_RNGL TD(_RNGL)
#define TD_RPRN TD(_RPRN)
#define TD_SEND TD(_SEND)                   // config.h defined macro string
#define TD_SPC  TD(_SPC)                    // see process_record_user() for extended handling of Spc
#define TD_TILD TD(_TILD)
