# Testen und Debuggen

Nachdem Du deine Tastatur mit deiner angepassten Firmware geflasht hast, ist es nun an der Zeit sie auszuprobieren. Mit ein bisschen Glück sollte alles ohne Probleme funktionieren, wenn dies nicht der Fall ist, soll dieses Dokument dir dabei helfen, herauszufinden wo das Problem liegt.

## Testen

Die Tastatur zu testen ist relativ selbsterklärend. Drücke jede der Tasten um dich zu versichern, dass der gesendete Keyode der ist, den du erwarten würdest. Dafür gibt es sogar ein paar Programme die helfen sollen, dass keine Taste ausgelassen wurde.

Anmerkung: Diese Programme werden weder von QMK bereitgestellt oder gutgeheißen.

* [Switch Hitter](https://elitekeyboards.com/switchhitter.php) (Nur für Windows)
* [Keyboard Viewer](https://www.imore.com/how-use-keyboard-viewer-your-mac) (Nur für Mac)
* [Keyboard Tester](http://www.keyboardtester.com) (Web basiert)
* [Keyboard Checker](http://keyboardchecker.com) (Web basiert)

## Debuggen

Deine Tastatur wird Debug Informationen liefern wenn Du `CONSOLE_ENABLE = yes` in deiner `rules.mk` gesetzt hast. Die default-Ausgabe ist sehr beschränkt und kann wenn nötig durch die Aktivierung des Debug-Modes erhöht werden. Benutze dafür entweder den `DEBUG` Keycode in deiner Tastaturbelegung, das [Command](de/feature_command.md)-Feature oder füge den folgenden Code zu deiner Tastaturbelegung hinzu.

```c
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```

### Debuggen mit der QMK Toolbox

Für kompatible Plattformen kann die [QMK Toolbox](https://github.com/qmk/qmk_toolbox) benutzt werden um Debug-Nachrichten deiner Tastatur anzuzeigen.

### Debuggen mit hid_listen

Bevorzugst Du es lieber auf der Befehlszeile zu debuggen? Dafür eignet sich das Programm [hid_listen](https://www.pjrc.com/teensy/hid_listen.html) von PJRC. Binaries sind für Windows, Linux und MacOS verfügbar.

<!-- FIXME: Describe the debugging messages here. -->

## Eigene Debug-Nachrichten senden

Manchmal ist es hilfreich Debug-Nachrichten innerhalb deines eigenen [Custom Codes](de/custom_quantum_functions.md) zu drucken. Das ist ziemlich einfach. Beginne damit `print.h` am Anfang deiner Datei zu inkludieren:

    #include <print.h>

Danach stehen dir verschiedene Druck-Funktionen zur Verfügung:

* `print("string")`: Druckt einen simplen String
* `uprintf("%s string", var)`: Druckt einen formatierten String
* `dprint("string")` Druckt einen simplen String, aber nur wenn der Debug-Mode aktiviert ist
* `dprintf("%s string", var)`: Druckt einen formatierten String, aber nur wenn der Debug-Mode aktiviert ist

## Debug Beispiele

Anbei findest Du eine Sammlung von hilfreichen Beispielen. Für weitere Informationen Informationen sei an dieser Stelle auf [Debugging/Troubleshooting QMK](de/faq_debug.md) verwiesen.

### Which matrix position is this keypress?
### Welche Matrix Position hat dieser Tastenanschlag

Beim Portieren, oder bei der Fehlerdiagnose von PCB Problemen, ist es nützlich sich anzeigen zu lassen ob ein Tastenanschlag richtig erkannt wurde. Um die Protokollierung für diesen Fall zu aktivieren, füge bitte folgenden Code zu deiner Tastaturbelegung `keymap.c` hinzu.

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Wenn 'console' aktiviert ist wird die Matrix-Position und der Status jedes Tastenanschlags ausgegeben 
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
  return true;
}
```

Beispiel Ausgabe:
```text
Waiting for device:.......
Listening:
KL: kc: 169, col: 0, row: 0, pressed: 1
KL: kc: 169, col: 0, row: 0, pressed: 0
KL: kc: 174, col: 1, row: 0, pressed: 1
KL: kc: 174, col: 1, row: 0, pressed: 0
KL: kc: 172, col: 2, row: 0, pressed: 1
KL: kc: 172, col: 2, row: 0, pressed: 0
```

### Wieviel Zeit wurde benötigt um einen Tastenanschlag zu detektieren?

Wenn Performance-Probleme auftreten ist es hilfreich die Frequenz, mit der die Matrix gescannt wird, zu wissen. Um dies in diesem Fall zu aktiveren füge, den folgenden Code zu deiner Tastaturbelegung in `config.h` hinzu.

```c
#define DEBUG_MATRIX_SCAN_RATE
```

Beispiel Ausgabe
```text
  > matrix scan frequency: 315
  > matrix scan frequency: 313
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
```
