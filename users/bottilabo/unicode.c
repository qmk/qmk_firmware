// https://nacl-ltd.github.io/2018/01/23/japanese-input-by-qmk.html
void unicode_input_start(void);
void unicode_input_finish(void);
void register_hex(uint16_t hex);

static void tap_unicode(uint16_t ch) {
  unicode_input_start();
  register_hex(ch);
  unicode_input_finish();
}
