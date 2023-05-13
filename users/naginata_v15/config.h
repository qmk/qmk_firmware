// LinuxでUNICODE入力を安定化
// #define USB_POLLING_INTERVAL_MS 8
// 入力が遅くなるのでunicode.cにwaitを入れるべき

// UNICODE入力を安定化
#define UNICODE_TYPE_DELAY 32

// 編集モードが不要ならコメントアウト
#define NG_HENSHU
// 固有名詞が不要ならコメントアウト
#define NG_KOYUMEISHI
