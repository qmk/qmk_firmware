# Eine eigene Firmware erstellen 

Nachdem Du nun eine funktionierende Entwicklungsumgebung aufgesetzt hast, bist Du nun bereit, deine eigene Firmware zu erstellen. Dieses Sektion des Guides wird zwischen drei Programmen hin- und herwechseln: deinem Dateimanager, deinem Texteditor und der Befehlszeile. Lasse diese drei Fenster geöffnet, bis Du fertig und zufrieden mit deiner Tastatur-Firmware bist.

Solltest Du die Befehlszeile zwischenzeitlich geschlossen haben, vergiss nicht wieder in das richtige Verzeichnis zu navigieren, benutze dazu den Befehl `cd qmk_firmware`.

## Navigiere in deinen Keymap Ordner

Beginne damit, in das `keymaps` Verzeichnis für deine Tastatur zu navigieren.

Wenn Du macOS oder Windows benutzt, kannst Du einfach in das keymaps Verzeichnis wechseln.

?> macOS:<br>
    open keyboards/<keyboard_folder>/keymaps

?> Windows:<br>
    start .\\keyboards\\<keyboard_folder>\\keymaps

## Eine Kopie der `default`  Tastaturbelegung erstellen

Wenn Du den `keymaps` Ordner geöffnet hast, solltest Du zuerst eine Kopie des `default` Verzeichnisses erstellen. Wir empfehlen dafür deinen GitHub Benutzernamen zu verweden, aber Du kannst auch jeden anderen Namen verwenden solange er nur aus Kleinbuchstaben, Zahlen und Unterstrichen besteht.

Um den Prozess zu automatisieren kannst Du dazu auch das Skript `new_keymap.sh` verwenden.

Navigiere dazu in das `qmk_firmware/util` Verzeichnis und gib folgenden Befehl ein:

```
./new_keymap.sh <keyboard path> <username>
```

Um zum Beispiel den Benutzernamen John für die Tastaturbelegung eines 1up60hse zu verwenden, würdest Du Folgendes eingeben:

```
./new_keymap.sh 1upkeyboards/1up60hse john
```

## Öffne `keymap.c` in deinem bevorzugtem Text Editor

Öffne deine `keymap.c`. In dieser Datei findest Du die Strukturen, die das Verhalten deiner Tastatur bestimmen. Oben in der `keymap.c` befinden sich Definitionen (defines) und Aufzählungen (enums), die die Tastaturbelegung leserlicher machen sollen. Weiter unten wirst Du eine Zeile finden, die wie folgt aussieht:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

Diese Zeile markiert den Anfang der Liste der Ebenen (Layers). Darunter befinden sich Zeilen die entweder `LAYOUT` oder `KEYMAP` enthalten, das deutet auf den Start einer Ebene hin. Danach folgt eine Liste von Tasten, die dieser Ebene zugewiesen sind.

!> Beim Bearbeiten einer Tastaturbelegung solltest Du darauf achten, keine Kommata hinzuzufügen oder zu entfernen. Ansonsten kann dies dazu führen, dass deine Firmware nicht mehr kompiliert und es ist nicht immer einfach festzustellen, wo genau ein Komma zuviel oder zu wenig ist. Die letzte Zeile hat am Ende kein Komma, die Zeilen davor jedoch schon.

## Personalisiere die Tastaturbelegung nach deinen Wünschen

Wie Du diesen Schritt abschließt ist vollkommen Dir überlassen. Ändere die eine Sache die Dich stört oder verändere alles von Grund auf. Du kannst Ebenen entfernen die Du nicht brauchst oder Neue hinzufügen, bis zu 32 Stück. Die folgende Dokumentation verrät Dir was Du hier alles definieren kannst: 

* [Keycodes](de/keycodes.md)
* [Features](de/features.md)
* [FAQ](de/faq.md)

?> Während Du langsam ein Gefühl dafür kriegst wie Keymaps funktionieren, solltest Du darauf achten nicht zuviel auf einmal zu verändern. Größere Änderungen machen es schwieriger, Probleme zu debuggen.

## Deine Firmware erzeugen

Wenn Du damit fertig bist, deine Tastaturbelegung anzupassen, musst Du noch die Firmware erzeugen. Öffne dazu wieder die Befehlszeile und führe folgenden Befehl aus:

    make <my_keyboard>:<my_keymap>

Wenn deine Tastaturbelegung z.B. "xyverz" heißt und Du die Belegung für ein rev5 planck erzeugen möchtest, lautet der Befehl:

    make planck/rev5:xyverz

Während des Kompiliervorgangs wird viel Text auf dem Bildschirm ausgegeben. Es sollte am Ende mit etwas enden das ungefähr so aussieht:

```
Linking: .build/planck_rev5_xyverz.elf                                                              [OK]
Creating load file for flashing: .build/planck_rev5_xyverz.hex                                      [OK]
Copying planck_rev5_xyverz.hex to qmk_firmware folder                                               [OK]
Checking file size of planck_rev5_xyverz.hex                                                        [OK]
 * File size is fine - 18392/28672
```

## Deine Firmware flashen
Bitte fahre mit [Firmware flashen](de/newbs_flashing.md) fort, um zu erfahren, wie Du deine neue Firmware auf deine Tastatur flashen kannst.
