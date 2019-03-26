# edvorakjp

epaew's Enhanced Dvorak layout for Japanese Programmer

## Layout overview
This is a sample. You can swap any symbol keys and modifier keys.

- Basic layout (for ansi)
```
  //+----+----+----+----+----+----+----+----+----+----+----+----+----+---------+
      `  , !  , @  , #  , $  , %  , ^  , &  , *  , (  , )  , [  , ]  ,  BSPC   ,
  //+----+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+-------+
      TAB  , '  , ,  , .  , Y  , Q  , F  , G  , R  , W  , P  , /  , =  ,   \   ,
  //+------++---++---++---++---++---++---++---++---++---++---++---++---+-------+
      CAPS  , A  , O  , E  , I  , U  , D  , T  , N  , S  , M  , -  ,    ENT    ,
  //+-------+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-----------+
       LSFT   , :  , X  , C  , V  , Z  , H  , J  , K  , L  , B  ,     RSFT     ,
  //+------+--+---++----++---+----+----+----+----+-+--+---++----++------+------+
      LCTL , LGUI , LALT ,          SPACE          , RALT , RGUI , MENU , RCTL
  //+------+------+------+-------------------------+------+------+------+------+
```

 And you can see [my iris keyboard layout](../../keyboards/iris/keymaps/edvorakjp/keymap.c) for sample implementation, too.

## for Japanese

- 日本語入力用のキーを追加
  - IME 切り替えキー
    - 長押しでレイヤー切り替え、短押しでIME切り替え
    - macOS(かな/英数)、Windows(Alt+\`)の両方に対応
- Define some custom keys for typing Japanese
  - IME switching
    - act as LOWER/RAISE when hold, act as IME switching when tapped
    - for macOS(かな/英数), for Windows(Alt+\`)

## for Programmer

- Dvorak 配列をベースに、ショートカットでよく利用される XCV は QWERTY 配列の位置を維持
- 一部にVimユーザ用のキー配置を実施
    - HJKL キーを横並びで配置
    - Shift押下時と非押下時で、";"キーの挙動を入れ替え  
      （`config.h` 内で `#define SWAP_SCLN` の宣言が必要です）
- デフォルトレイヤーには、数字キーの代わりに記号 `!@#$%^&*()` を配置

- mainly based on Dvorak layout, but XCV is available in the same position of QWERTY layout
- for Vim users
    - HJKL is lining side by side
    - swap the ";" key behavior. i.e. send ":" normally and send ";" when you hold shift.  
      (need `#define SWAP_SCLN` in your `config.h`)
- we can type `!@#$%^&*()` keys without shift keys in base layer

## License

Copyright 2018 Ryo Maeda epaew.333@gmail.com @epaew

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
