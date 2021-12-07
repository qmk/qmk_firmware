# Cockpit custom layout

> This configuration is built around Lithuanian keyboard layout, but you can easily modify it to fit your needs

## Layers

### Default QWERTY

|           |        |        |        |        |        |        |        |        |        |        |           |
| :-------: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :-------: |
|  <br>Esc  | Q<br>q | W<br>w | E<br>e | R<br>r | T<br>t | Y<br>y | U<br>u | I<br>i | O<br>o | P<br>p | <br>Bksp  |
|  <br>Tab  | A<br>a | S<br>s | D<br>d | F<br>f | G<br>g | H<br>h | J<br>j | K<br>k | L<br>l | :<br>; |  "<br>'   |
| <br>Shift | Z<br>z | X<br>x | C<br>c | V<br>v | B<br>b | N<br>n | M<br>m | <<br>, | ><br>. | ?<br>/ | <br>Enter |
|   Ctrl    |   Fn   |  GUI   |  Alt   | Lower  |   Sp   |  ace   | Raise  |  Left  |  Down  |   Up   |   Right   |

### Lower

|           |        |        |        |           |        |        |        |        |        |         |          |
| :-------: | :----: | :----: | :----: | :-------: | :----: | :----: | :----: | :----: | :----: | :-----: | :------: |
|  ~<br>\`  | Ą<br>ą | Č<br>č | Ę<br>ę |  Ė<br>ė   | Į<br>į | Š<br>š | Ų<br>ų | Ū<br>ū | Ž<br>ž | \_<br>- | <br>Bksp |
|  <br>Tab  | <br>!  | <br>@  | <br>#  |  <br>\$   | <br>%  | <br>^  | <br>&  | <br>\* | <br>(  |  <br>)  | <br>Del  |
| <br>Shift | <br>=  | <br>+  | <br>-  |  <br>\|   | {<br>[ | }<br>] | <br><  | <br>>  | <br>{  |  <br>}  | <br>Ins  |
|   Ctrl    |        |        |  Alt   | **Lower** |   Sp   |  ace   |        |  Home  |  PgDn  |  PgUp   |   End    |

### Raise

|           |         |         |        |         |        |        |           |         |        |        |           |
| :-------: | :-----: | :-----: | :----: | :-----: | :----: | :----: | :-------: | :-----: | :----: | :----: | :-------: |
|  ~<br>\`  | !<br>1  | @<br>2  | #<br>3 | \$<br>4 | %<br>5 | ^<br>6 |  &<br>7   | \*<br>8 | (<br>9 | )<br>0 | <br>Bksp  |
|  <br>Tab  | \$<br>4 | %<br>5  | ^<br>6 |         |        |        |           |         |        |        | \|<br>\   |
| <br>Shift | &<br>7  | \*<br>8 | (<br>9 | )<br>0  |        |        |           | <<br>,  | ><br>. | ?<br>/ | <br>Enter |
|   Ctrl    |         |         |  Alt   |         |   Sp   |  ace   | **Raise** |  Left   |  Down  |   Up   |   Right   |

### Function

-   Backlight breathing does not work.
-   **Term** button is bound to `Calculator`. I have set this button as a shortcut to open a terminal.
-   **Lock** is a shortcut for `Alt + L`

|           |             |             |             |             |            |              |            |        |             |         |          |
| :-------: | :---------: | :---------: | :---------: | :---------: | :--------: | :----------: | :--------: | :----: | :---------: | :-----: | :------: |
|  <br>F1   |   <br>F2    |   <br>F3    |   <br>F4    |   <br>F5    |   <br>F6   |    <br>F7    |   <br>F8   | <br>F9 |   <br>F10   | <br>F11 | <br>F12  |
| <br>Caps  | RGB<br>Togl | RGB<br>Hue+ | RGB<br>Sat+ | RGB<br>Brt+ | BL<br>Togl | BL<br>Breath | BL<br>Brt+ |        | Scr<br>Brt+ |         | <br>Vol+ |
| <br>Shift |  <br>Term   | RGB<br>Hue- | RGB<br>Sat- | RGB<br>Brt- |  WWW<br><  |   WWW<br>>   | BL<br>Brt- |        | Scr<br>Brt- |  PrScr  | <br>Vol- |
|   Ctrl    |   **Fn**    | RGB<br>Mode |     Alt     |             |     Sp     |     ace      |   MPrev    | MStop  |    MNext    |  MPlay  |   Lock   |

## Usage

```bash
cd qmk_firmware
make kprepublic/jj40:cockpit
bootloadHID .build/kprepublic_jj40_cockpit.hex
```

_if you're getting permission errors use sudo_
