// fontconvert -f~/repos/noto-sans-jp/NotoSansJP-Regular.otf -s15 -v _Punct_ 0x3001 0x3002 0x300c 0x300d 
// Visualize your font via https://tchapi.github.io/Adafruit-GFX-Font-Customiser

const uint8_t NotoSansJP_Regular_Punct_15pt16bBitmaps[] PROGMEM = {
  0x40, 0xE0, 0xF0, 0x38, 0x1C, 0x0E, 0x0F, 0x06, 0x3F, 0x31, 0xB0, 0x78,
  0x1C, 0x0E, 0x0D, 0x8C, 0x7E, 0x00, 0x00, 0xFF, 0xFF, 0xF0, 0x18, 0x0C,
  0x06, 0x03, 0x01, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01,
  0x80, 0xC0, 0x60, 0x30, 0x18, 0x00, 0x01, 0x80, 0xC0, 0x60, 0x30, 0x18,
  0x0C, 0x06, 0x03, 0x01, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03,
  0x01, 0x80, 0xFF, 0xFF, 0xF0 };

const GFXglyph NotoSansJP_Regular_Punct_15pt16bGlyphs[] PROGMEM = {
// bmpOff,   w,   h,xAdv, xOff, yOff      range 0 (0x3001 - 0x3002)
  {     0,   8,   8,  29,    2,   -5 },   // 0x3001   (#0)
  {     8,   9,   9,  29,    1,   -5 },   // 0x3002   (#1)
  {     0,   0,   0,   0,    0,    0 },   // 0x3003 (skip)
  {     0,   0,   0,   0,    0,    0 },   // 0x3004 (skip)
  {     0,   0,   0,   0,    0,    0 },   // 0x3005 (skip)
  {     0,   0,   0,   0,    0,    0 },   // 0x3006 (skip)
  {     0,   0,   0,   0,    0,    0 },   // 0x3007 (skip)
  {     0,   0,   0,   0,    0,    0 },   // 0x3008 (skip)
  {     0,   0,   0,   0,    0,    0 },   // 0x3009 (skip)
  {     0,   0,   0,   0,    0,    0 },   // 0x300A (skip)
  {     0,   0,   0,   0,    0,    0 },   // 0x300B (skip)
// bmpOff,   w,   h,xAdv, xOff, yOff      range 1 (0x300c - 0x300d)
  {    19,   9,  20,  29,   19,  -24 },   // 0x300C   (#2)
  {    42,   9,  20,  29,    1,  -16 } }; // 0x300D   (#3)

const GFXfont NotoSansJP_Regular_Punct_15pt16b PROGMEM = {
  (uint8_t  *)NotoSansJP_Regular_Punct_15pt16bBitmaps,
  (GFXglyph *)NotoSansJP_Regular_Punct_15pt16bGlyphs,
  0x3001, // first
  0x300D, // last
  43  // height
 };

// Approx. 163 bytes
