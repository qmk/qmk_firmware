# Bootloader Treiber Installation mit Zadig

QMK erscheint für den Host als normales HID Eingabegerät und benötigt deshalb keine zusätzlichen Treiber. Der Bootloader, den Du für das Flashen der Firmware benötigst, jedoch meistens schon.

Hierzu gibt es zwei Ausnahmen: den Caterina Bootloader, meistens auf Pro Micros, sowie den HalfKay Bootloader auf PJRC Teensys. Diese erscheinen als serieller Port und als generisches HID Gerät und benötigen keine Treiber.

Wir empfehlen deshalb [Zadig](https://zadig.akeo.ie/). Wenn Du die Entwicklungsumgebung mit MSYS2 oder WSL installiert hast, wird dich dass `qmk_install.sh` Skript gefragt haben, ob es die Treiber für dich installieren sollte.

## Installation

Versetze deine Tastatur in den Bootloader-Modus, entweder durch Betätigung des physischen `RESET` Schalters - meist auf der Unterseite der Platine - oder durch das Auslösen des Key-Codes `RESET` bzw. `KC_RESET` (sollte in der zur Tastatur gehörigen `keycode.c` zu entnehmen sein). Sollte deine Tastatur weder noch besitzen, versuche es damit die `Escape`-Taste oder `Leertaste + B` zu halten während Du die Tastatur mit dem PC verbindest (Siehe auch [Bootmagic](de/feature_bootmagic.md) für weitere Details). Ein paar Tastaturen benutzen das [Command](de/feature_command.md)-Feature an Stelle von Bootmagic; in diesem Fall kannst du mit den Tastenkombinationen `linkes Shift + rechtes Shift + B` oder `linkes Shift + rechtes Shift + Escape` zu jeder Zeit in den Bootloader wechseln solange die Tastatur verbunden ist.

Eingie Tastaturen haben u.U. spezielle Anweisungen um in den Bootloader-Modus zu gelangen. Zum Beispiel kann die [Bootmagic-Lite](de/feature_bootmagic.md#bootmagic-lite)-Taste (default: Escape) auf eine andere Taste gemappt sein; oder die magische Kombination (default: linkes Shift+rechtes Shift) verwendet anstatt Shift die STRG-Tasten. Die zur Tastatur gehörige README sollte dir Aufschluss darüber geben wie der Bootloader-Modus ausgelöst werden kann wenn Du unsicher bist.

Um ein Gerät mit USBaspLoader in den Bootloader-Modus zu versetzen, halte `BOOT` gedrückt während Du den `RESET`-Knopf drückst.
Alternativ, halte `BOOT` gedrückt während Du das USB-Kabel einsteckst.

Zadig sollte das Bootloader-Gerät automatisch erkennen. Manchmal musst Du zusätzlich noch **Options → List All Devices** auswählen.

 - Tastaturen mit Atmel AVR MCUs sollten als `ATm32U4DFU` (oder ähnlich) angezeigt werden, mit der Vendor ID `03EB`.
 - USBasp werden als `USBasp` angezeigt, mit VID/PID `16C0:05DC`.
 - Tastaturen AVR controller und dem QMK-DFU Bootloader haben den namen `<Tastatur Name> Bootloader` und die VID `03EB`.
 - Die meisten ARM Tastaturen werden als `STM32 BOOTLOADER` angezeigt, mit VID/PID `0483:DF11`.

!> Sollte Zadig ein oder mehrere Geräte mit `HidUsb`-Treiber anzeigen, dann ist deine Tastatur wahrscheinlich nicht im Bootloader-Modus. Der Pfeil wird orange eingefärbt sein und Du wirst nach einer Bestätigung gefragt um Veränderungen am System vorzunehmen. In diesem Fall **fahre nicht fort**!

Wenn der Pfeil grün angezeigt wird, wähle den Treiber aus und klicke auf **Treiber installieren**. Der  `libusb-win32`-Treiber sollte gewöhnlich für AVR verwendet werden und `WinUSB` für ARM. Sollte es danach noch nicht möglich sein die Tastatur zu flashen, versuche es mit einem anderen Treiber. Für USBaspLoader Geräte, die über die Befehlszeile mit MSYS2 geflasht werden, wird der `libusbk`-Treiber empfohlen. Ansonsten sollte `libusb-win32` funktionieren wenn die QMK Toolbox verwendet wird.

![Zadig mit Bootloader-Treiber korrekt installiert](https://i.imgur.com/b8VgXzx.png)

Entferne nun deine Tastatur und verbinde sie erneut um sicherzugehen dass der neue Treiber erfolgreich installiert wurde. Wenn Du QMK Toolbox benutzt, starte die Anwendung zur Sicherheit einmal neu, da Veränderungen am Treiber manchmal nicht richtig erkannt werden. Wenn dies immer noch nicht erfolgreich war hilft es an dieser Stelle manchmal ein Neustart des Computers.

## Wiederherstellung einer Installation für ein falsches Gerät

Wenn Du feststellst dass Du anschließend auf deiner Tastatur nicht mehr tippen kannst, ist etwas bei der Installation schief gelaufen. Ein häufiger Fehler ist es dass die Tastatur nicht im Bootloader-Modus war und stattdessen der Treiber für das HID-Gerät ersetzt wurde. Dies kannst Du einfach mit Zadig überprüfen, eine funktionierende Tastatur verwendet als Treiber `HidUsb` auf allen Interfaces .

![Eine funktionierende Tastatur aus Zadigs Sicht](https://i.imgur.com/Hx0E5kC.png)

Öffne den Geräte-Manager und suche nach einem Gerät das wie deine Tastatur aussieht.

![Die Tastatur mit dem falschen Treiber installiert, im Geräte-Manager](https://i.imgur.com/L3wvX8f.png)

Rechtsklick und **Gerät deinstallieren** anklicken. Bitte gehe sicher dass in diesem Schritt auch **Treibersoftware für dieses Gerät löschen** markiert ist.

![Der "Gerät deinstallieren"-Dialog, mit "Treibersoftware für dieses Gerät entfernen" markiert](https://i.imgur.com/aEs2RuA.png)

Klick **Aktion → Suche nach veränderter Hardware**. Nun solltest Du wieder in der Lage sein normal zu tippen. Vergewissere dich mit Hilfe von Zadig dass die Tastatur nun `HidUsb` als Treiber verwendet. Wenn dies der Fall ist sollte wieder alles funktionieren.
