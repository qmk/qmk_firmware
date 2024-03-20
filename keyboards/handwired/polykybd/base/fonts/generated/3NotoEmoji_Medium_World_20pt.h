// fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf -s20 -r50 -v _World_ -n0x11000 0x1F310 0x1F310 
// Visualize your font via https://tchapi.github.io/Adafruit-GFX-Font-Customiser

const uint8_t NotoEmoji_Medium_World_20pt16bBitmaps[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x00, 0x1F,
  0xFF, 0xF8, 0x00, 0x00, 0x7B, 0x99, 0xDE, 0x00, 0x00, 0xE7, 0x18, 0xE7,
  0x00, 0x01, 0x8C, 0x18, 0x31, 0x80, 0x03, 0x18, 0x18, 0x18, 0xC0, 0x06,
  0x30, 0x18, 0x0C, 0x60, 0x0C, 0x70, 0x18, 0x0E, 0x30, 0x18, 0x60, 0x18,
  0x06, 0x18, 0x3F, 0xFF, 0xFF, 0xFF, 0xF8, 0x30, 0x80, 0x18, 0x03, 0x0C,
  0x61, 0x80, 0x18, 0x01, 0x84, 0x61, 0x80, 0x18, 0x01, 0x86, 0x61, 0x80,
  0x18, 0x01, 0x86, 0xC3, 0x00, 0x18, 0x00, 0xC2, 0xC3, 0x00, 0x18, 0x00,
  0xC3, 0xC3, 0x00, 0x18, 0x00, 0xC3, 0xC3, 0x00, 0x18, 0x00, 0xC3, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0x00, 0x18, 0x00, 0xC3, 0xC3, 0x00, 0x18,
  0x00, 0xC3, 0xC3, 0x00, 0x18, 0x00, 0xC3, 0xC3, 0x00, 0x18, 0x00, 0xC3,
  0xC3, 0x00, 0x18, 0x00, 0xC2, 0x61, 0x80, 0x18, 0x01, 0x86, 0x61, 0x80,
  0x18, 0x01, 0x86, 0x61, 0x80, 0x18, 0x01, 0x84, 0x30, 0x80, 0x18, 0x01,
  0x0C, 0x3F, 0xFF, 0xFF, 0xFF, 0xF8, 0x18, 0x60, 0x18, 0x06, 0x18, 0x0C,
  0x70, 0x18, 0x0E, 0x30, 0x06, 0x30, 0x18, 0x0C, 0x60, 0x07, 0x18, 0x18,
  0x18, 0xC0, 0x01, 0x8C, 0x18, 0x31, 0x80, 0x00, 0xE7, 0x18, 0xE7, 0x00,
  0x00, 0x7B, 0x99, 0xDE, 0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x07,
  0xFF, 0xE0, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00 };

const GFXglyph NotoEmoji_Medium_World_20pt16bGlyphs[] PROGMEM = {
// bmpOff,   w,   h,xAdv, xOff, yOff      range 0 (0x1f310 - 0x1f310)
  {     0,  40,  40,  50,    5,  -32 } }; // 0x1F310 globeWithMeridians  (#0)

const GFXfont NotoEmoji_Medium_World_20pt16b PROGMEM = {
  (uint8_t  *)NotoEmoji_Medium_World_20pt16bBitmaps,
  (GFXglyph *)NotoEmoji_Medium_World_20pt16bGlyphs,
  0xE310, // first
  0xE310, // last
  50   //height
 };

// Approx. 214 bytes