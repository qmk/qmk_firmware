// fontconvert -f~/repos/noto-sans-jp/NotoSansJP-Regular.otf -s16 -v _PunctSupl_ 0x30fb 0x30fc 
// Visualize your font via https://tchapi.github.io/Adafruit-GFX-Font-Customiser

const uint8_t NotoSansJP_Regular_PunctSupl_16pt16bBitmaps[] PROGMEM = {
  0x10, 0xF9, 0xFF, 0xFF, 0xEF, 0x8E, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xE0 };

const GFXglyph NotoSansJP_Regular_PunctSupl_16pt16bGlyphs[] PROGMEM = {
// bmpOff,   w,   h,xAdv, xOff, yOff      range 0 (0x30fb - 0x30fc)
  {     0,   7,   7,  31,   12,  -15 },   // 0x30FB   (#0)
  {     7,  25,   3,  31,    3,  -13 } }; // 0x30FC   (#1)

const GFXfont NotoSansJP_Regular_PunctSupl_16pt16b PROGMEM = {
  (uint8_t  *)NotoSansJP_Regular_PunctSupl_16pt16bBitmaps,
  (GFXglyph *)NotoSansJP_Regular_PunctSupl_16pt16bGlyphs,
  0x30FB, // first
  0x30FC, // last
  45  // height
 };

// Approx. 38 bytes
