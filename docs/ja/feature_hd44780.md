# HD44780 LCD ディスプレイ

<!---
  original document: 0.9.43:docs/feature_hd44780.md
  git diff 0.9.43 HEAD -- docs/feature_hd44780.md | cat
-->

これは Peter Fleury の LCD ライブラリの統合です。このページは基本について説明します。[詳細なドキュメントについてはこのページをご覧ください](http://www.peterfleury.epizy.com/doxygen/avr-gcc-libraries/group__pfleury__lcd.html)

HD44780 ディスプレイのサポートを有効にするには、キーボードの `rules.mk` の `HD44780_ENABLE` フラグを yes に設定します。

## 設定

ディスプレイで使用されるピンとディスプレイの行と列の数を、キーボードの `config.h` に設定する必要があります。


HD44780 のラベルが付いたセクションのコメントを外し、必要に応じてパラメータを変更します。
````
/*
 * HD44780 LCD ディスプレイ設定
 */

#define LCD_LINES           2     //< ディスプレイの表示行数
#define LCD_DISP_LENGTH    16     //< ディスプレイの行ごとの表示文字数
#define LCD_IO_MODE      1            //< 0: メモリマップモード 1: IO ポートモード
#if LCD_IO_MODE
#define LCD_PORT         PORTB        //< LCD 行のためのポート
#define LCD_DATA0_PORT   LCD_PORT     //< 4ビットデータビット 0 のポート
#define LCD_DATA1_PORT   LCD_PORT     //< 4ビットデータビット 1 のポート
#define LCD_DATA2_PORT   LCD_PORT     //< 4ビットデータビット 2 のポート
#define LCD_DATA3_PORT   LCD_PORT     //< 4ビットデータビット 3 のポート
#define LCD_DATA0_PIN    4            //< 4ビットデータビット 0 のピン
#define LCD_DATA1_PIN    5            //< 4ビットデータビット 1 のピン
#define LCD_DATA2_PIN    6            //< 4ビットデータビット 2 のピン
#define LCD_DATA3_PIN    7            //< 4ビットデータビット 3 のピン
#define LCD_RS_PORT      LCD_PORT     //< RS 線のためのポート
#define LCD_RS_PIN       3            //< RS 線のためのピン
#define LCD_RW_PORT      LCD_PORT     //< RW 線のためのポート
#define LCD_RW_PIN       2            //< RW 線のためのピン
#define LCD_E_PORT       LCD_PORT     //< Enable 線のためのポート
#define LCD_E_PIN        1            //< Enable 線のためのピン
#endif
````

他のプロパティを設定する必要がある場合は、それらを `quantum/hd44780.h` からコピーし、`config.h` に設定することができます。（訳注）`quantum/hd44780.h` は `drivers/avr/hd44780.h` の間違いではないかと思われます。

## 使用法

ディスプレイを初期化するには、以下のパラメータのうちの1つを使って `lcd_init()` を呼び出します:
````
LCD_DISP_OFF             : ディスプレイオフ
LCD_DISP_ON              : ディスプレイオン、カーソルオフ
LCD_DISP_ON_CURSOR       : ディスプレイオン、カーソルオン
LCD_DISP_ON_CURSOR_BLINK : ディスプレイオン、点滅カーソル
````
これはキーボードの `matrix_init_kb` またはキーマップの `matrix_init_user` で行うのが最適です。
使用前にディスプレイをクリアすることをお勧めします。
そのためには、`lcd_clrscr()` を呼びます。

ディスプレイに何かを表示するには、最初に `lcd_gotoxy(column, line)` を呼びます。最初の行の先頭に移動するには、`lcd_gotoxy(0, 0)` を呼び出し、その後 `lcd_puts("example string")` を使って文字列を出力します。

ディスプレイを制御することができる、より多くのメソッドがあります。[詳細なドキュメントについてはリンクされたページをご覧ください](http://www.peterfleury.epizy.com/doxygen/avr-gcc-libraries/group__pfleury__lcd.html)
