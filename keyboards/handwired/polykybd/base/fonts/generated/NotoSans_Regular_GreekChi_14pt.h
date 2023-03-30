// fontconvert -f~/repos/noto-sans/NotoSans-Regular.ttf -s14 -v _GreekChi_ 0x2c7 0x2c7 
// Visualize your font via https://tchapi.github.io/Adafruit-GFX-Font-Customiser

const uint8_t NotoSans_Regular_GreekChi_14pt16bBitmaps[] PROGMEM = {
  0xC1, 0xB9, 0x8F, 0x83, 0xC0 };

const GFXglyph NotoSans_Regular_GreekChi_14pt16bGlyphs[] PROGMEM = {
// bmpOff,   w,   h,xAdv, xOff, yOff      range 0 (0x2c7 - 0x2c7)
  {     0,   9,   4,  11,    1,  -20 } }; // 0x2C7 caron  (#0)

const GFXfont NotoSans_Regular_GreekChi_14pt16b PROGMEM = {
  (uint8_t  *)NotoSans_Regular_GreekChi_14pt16bBitmaps,
  (GFXglyph *)NotoSans_Regular_GreekChi_14pt16bGlyphs,
  0x2C7, // first
  0x2C7, // last
  37   //height
 };

// Approx. 19 bytes
