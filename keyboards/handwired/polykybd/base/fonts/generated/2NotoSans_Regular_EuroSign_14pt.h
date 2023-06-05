// fontconvert -f~/repos/noto-sans/NotoSans-Regular.ttf -s14 -v _EuroSign_ 0x20ac 0x20ac 
// Visualize your font via https://tchapi.github.io/Adafruit-GFX-Font-Customiser

const uint8_t NotoSans_Regular_EuroSign_14pt16bBitmaps[] PROGMEM = {
  0x01, 0xF0, 0x1F, 0xF0, 0xF1, 0xC7, 0x00, 0x18, 0x00, 0xE0, 0x03, 0x00,
  0x0C, 0x00, 0xFF, 0xE0, 0xC0, 0x03, 0x00, 0x3F, 0xF0, 0xFF, 0xC0, 0xC0,
  0x03, 0x80, 0x0E, 0x00, 0x1C, 0x00, 0x38, 0x10, 0xFF, 0xC0, 0xFE };

const GFXglyph NotoSans_Regular_EuroSign_14pt16bGlyphs[] PROGMEM = {
// bmpOff,   w,   h,xAdv, xOff, yOff      range 0 (0x20ac - 0x20ac)
  {     0,  14,  20,  16,    1,  -19 } }; // 0x20AC Euro  (#0)

const GFXfont NotoSans_Regular_EuroSign_14pt16b PROGMEM = {
  (uint8_t  *)NotoSans_Regular_EuroSign_14pt16bBitmaps,
  (GFXglyph *)NotoSans_Regular_EuroSign_14pt16bGlyphs,
  0x20AC, // first
  0x20AC, // last
  37   //height
 };

// Approx. 49 bytes
