// fontconvert -f~/repos/noto-sans/NotoSans-Regular.ttf -s14 -v _GreekTonos_ 0x384 0x385 
// Visualize your font via https://tchapi.github.io/Adafruit-GFX-Font-Customiser

const uint8_t NotoSans_Regular_GreekTonos_14pt16bBitmaps[] PROGMEM = {
  0x76, 0x6C, 0x0E, 0x33, 0x6E, 0xDD, 0x62 };

const GFXglyph NotoSans_Regular_GreekTonos_14pt16bGlyphs[] PROGMEM = {
// bmpOff,   w,   h,xAdv, xOff, yOff      range 0 (0x384 - 0x385)
  {     0,   4,   4,   6,    1,  -20 },   // 0x384 tonos  (#0)
  {     2,  10,   4,  18,    4,  -20 } }; // 0x385 dieresistonos  (#1)

const GFXfont NotoSans_Regular_GreekTonos_14pt16b PROGMEM = {
  (uint8_t  *)NotoSans_Regular_GreekTonos_14pt16bBitmaps,
  (GFXglyph *)NotoSans_Regular_GreekTonos_14pt16bGlyphs,
  0x384, // first
  0x385, // last
  37   //height
 };

// Approx. 28 bytes
