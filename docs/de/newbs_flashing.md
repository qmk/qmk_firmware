# Deine Tastatur flashen

Nachdem deine Firmware nun fertig ist musst Du Sie noch auf deine Tastatur flashen.

## Flash-Vorgang mit QMK Toolbox

Der einfachste Weg deine Tastatur zu flashen ist mit Hilfe der [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases)

Leider ist die QMK Toolbox derzeit nur für Windows und macOS verfügbar. Wenn Du Linux benutzt (oder es vorziehst die Firmware mit der Kommandozeile zu flashen) solltest Du die Methode benutzen die [hier](de/newbs_flashing.md#tastatur-mit-der-befehlszeile-flashen) beschrieben wird.

### Lade die Datei in QMK Toolbox

Beginne damit die Datei in der QMK Toolbox Anwendung zu laden. Versichere dich dass Du die Firmware-Datei im Finder oder Explorer findest. Deine Tastatur-Firmware sollte entweder vom Typ `.hex` oder `.bin` sein sein. QMK sollte die für deine Tastatur entsprechende Datei automatisch in das Root-Verzeichnis (normalerweise `qmk_firmware`) kopieren.

?> Wenn Du Windows oder macOS benutzt kannst Du mit folgenden Befehlen ganz einfach das aktuelle Firmware-Verzeichnis im Explorer oder Finder öffnen.

#### Windows:

``` start . ```

#### macOS:

``` open . ```

Die Firmware-Dateien folgen dabei immer folgendem Schema:

    <meine_Tastatur>_<meine_Tastaturbelegung>.{bin,hex}

Zum Beispiel würde ein `planck/rev5` mit der `default` Tastaturbelegung folgenden Dateinamen haben:

    planck_rev5_default.hex

Wenn Du die Firmware-Datei gefunden hast kannst Du sie in das "Local file" ("Lokale Datei") Feld in der QMK Toolbox ziehen, alternativ kannst Du auf "Öffnen" klicken und in das Verzeichnis navigieren indem sich die Firmware-Datei befindet.

### Die Tastatur in den DFU (Bootloader) Modus versetzen

Um deine angepasste Firmware auf deine Tastatur zu flashen musst Du diese erst in einen speziellen "flashing"-Modus versetzen. Während die Tastatur in diesem Modus ist kannst Du nicht auf ihr tippen oder sie wie gewohnt als Tastatur benutzen. Es ist wichtig dass der flashing-Prozesses nicht unterbrochen oder die Tastatur ausstöpselst wird, da der Vorgang ansonst wiederholt werden muss.

Verschiedene Tastaturen verwenden unterschiedliche Methoden um in den Bootloader-Modus zu gelangen. Wenn dein PCB im Moment QMK oder TMK verwendet und Du keine spezifischen Anweisungen erhalten hast probiere die folgenden Methoden in dieser Reihenfolge:

* Halte beide Shift-Tasten und drücke `Pause`
* Halte beide Shift-Tasten und drücke `B`
* Entferne deine Tastatur vom Computer, drücke gleichzeitig `Leertaste` und `B`, verbinde die Tastatur wieder mit dem Computer und warte eine Sekunde bevor Du die Tasten wieder loslässt.
* Drücke den physischen `RESET`-Knopf auf der Unterseite des PCBs
* Suche auf dem PCB den Pin mit dem Label `RESET`, verbinde diesen mit deinem GND-Pin
* Suche auf dem PCB den Pin mit dem Label `BOOT0`, verbinde diesen mit GND und schließe die Tastatur wieder an den PC an TODO: DIS IS DANGEROUS!!

Wenn Du damit erfolgreich warst solltest Du in der QMK Toolbox eine Nachricht sehen die ungefähr so aussieht:

```
*** Clueboard - Clueboard 66% HotSwap disconnected -- 0xC1ED:0x2390
*** DFU device connected
```

### Tastatur flashen

Klicke auf den `Flash`-Knopf in der QMK Toolbox. Die Ausgabe wird ungefähr so aussehen:

```
*** Clueboard - Clueboard 66% HotSwap disconnected -- 0xC1ED:0x2390
*** DFU device connected
*** Attempting to flash, please don't remove device
>>> dfu-programmer atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer atmega32u4 flash qmk_firmware/clueboard_66_hotswap_skully.hex
    Checking memory from 0x0 to 0x55FF...  Empty.
    0%                            100%  Programming 0x5600 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x5600 bytes written into 0x7000 bytes memory (76.79%).
>>> dfu-programmer atmega32u4 reset
   
*** DFU device disconnected
*** Clueboard - Clueboard 66% HotSwap connected -- 0xC1ED:0x2390
```

## Tastatur mit der Befehlszeile flashen

Zunächst solltest Du versuchen herauszufinden welchen Bootlader deine Tastatur benutzt. Diese vier Bootloader sind am Weitesten verbreitet:

| MCU | Bootloader |
| --- | --- |
| Pro-Micro und Klone | CATERINA |
| Teensy | Halfkay |
| OLKB Boards | QMK-DFU |
| sonstige atmega32u4 | DFU |

Auf der Seite [Flash Anleitung und Bootloader Informationen](de/flashing.md) kannst Du mehr über das Thema erfahren.

Wenn Du weißt welchen Bootloader deine Tastaur verwendet, kannst Du diese Information bei der Kompilation hinzufügen um den Flash-Vorgang mit dem `make`-Befehl zu automatisieren.
```rules.mk
...
BOOTLOADER = caterina
...
```

### DFU

Wenn Du den DFU-Bootloader verwendest und Du bereit bist deine Firmware zu kompilieren und zu flashen, öffne ein Befehlszeile und führe folgenden Befehl aus:

    make <meine_Tastatur>:<meine_Tastaturbelegung>:dfu

Wenn deine Tastaturbelegung z.B den Namen "xzverz" trägt und Du ein rev5 planck flashen möchtest sähe der Befehl wie folgt aus:

    make planck/rev5:xyverz:dfu


Nachdem der Vorgang abgeschlossen ist sollte die Ausgabe ungefähr so aussehen:

```
Linking: .build/planck_rev5_xyverz.elf                                [OK]
Creating load file for flashing: .build/planck_rev5_xyverz.hex        [OK]
Copying planck_rev5_xyverz.hex to qmk_firmware folder                 [OK]
Checking file size of planck_rev5_xyverz.hex
 * File size is fine - 18574/28672
 ```

Wenn dieser Punkt erreicht ist wird das Build-Skript alle 5 Sekunden nach einem DFU Bootloader suchen. Dieser Vorgang wird wiederholt bis er erfolgreich ist oder abgebrochen wird.

    dfu-programmer: no device present.
    Error: Bootloader not found. Trying again in 5s.

Wenn diese Nachricht erscheint konnte das Build-Skript den Controller nicht eigenständig in den DFU Modus versetzen (z.B. weil der Modus in rules.mk falsch gesetzt wurde oder ein Problem mit der Hardware besteht), wenn dies eintritt musst Du die oben beschrieben Schritte benutzen um den Controller in den DFU Modus zu versetzen. Danach sollte die Ausgabe ungefähr so aussehen:

```
*** Attempting to flash, please don't remove device
>>> dfu-programmer atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer atmega32u4 flash qmk_firmware/clueboard_66_hotswap_skully.hex
    Checking memory from 0x0 to 0x55FF...  Empty.
    0%                            100%  Programming 0x5600 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x5600 bytes written into 0x7000 bytes memory (76.79%).
>>> dfu-programmer atmega32u4 reset
```

?> Wenn Du mit diesem Schritt Probleme hast (z.B. `dfu-programmer: no device present`) hilft dir hoffentlich der Abschnitt [Häufig gestellte Fragen (Build/Kompilieren)](de/faq_build.md).

#### DFU Befehle

Es gibt verschiedene DFU Befehle um die Firmware auf ein DFU Gerät zu flashen:

* `:dfu` - Dies ist die default Option. Es wird gecheckt ob ein DFU Gerät verfügbar ist, ist dies der Fall wird die Firmware geflasht. Dieser Check wird alle 5 Sekunden ausgeführt bis ein DFU Gerät erkannt wird.
* `:dfu-ee` - Der Flash-Vorgang benutzt eine `.eep` Datei anstatt einer `.hex` Datei. Dies ist eher unüblich.
* `:dfu-split-left` - Dies flasht die Firmware wie gewohnt (`:dfu`). Allerdings nur die "linke Seite" der EEPROM für geteilte Tastaturen. _Dies ist ideal für auf Elite C basierenden geteilten Tastaturen._
* `:dfu-split-right` - Dies flasht die Firmware wie gewohnt (`:dfu`). Allerdings nur die "rechte Seite" der EEPROM für geteilte Tastaturen. _Dies ist ideal für auf Elite C basierenden geteilten Tastaturen._


### Caterina
Für Arduinos und andere ProMicro Klone (z.B. SparkFun ProMicro), wenn Du bereit bist zu kompilieren und die Tastatur zu flashen, öffne ein Befehlszeilen-Fenster und führe den Build-Befehl aus:

    make <meine_Tastatur>:<meine_Tastaturbelegung>:avrdude

Wenn deine Tastaturbelegung zum Beispiel den Namen "xyverz" hat und Du eine Tastaturbelegung für ein "rev2 Lets Split" erzeugen möchtest, lautet der Befehl dafür:

    make lets_split/rev2:xyverz:avrdude

Nachdem die Kompilation abgeschlossen ist sollte die Ausgabe ungefähr so aussehen:

```
Linking: .build/lets_split_rev2_xyverz.elf                                [OK]
Creating load file for flashing: .build/lets_split_rev2_xyverz.hex        [OK]
Checking file size of lets_split_rev2_xyverz.hex                          [OK]
 * File size is fine - 27938/28672
Detecting USB port, reset your controller now..............
```

Nun wird die Tastatur automatisch zurückgesetzt und das Skript wird die Firmware flashen sobald es den Bootloader erkennt. Die Ausgabe sollte ungefähr so aussehen:

```
Detected controller on USB port at /dev/ttyS15

Connecting to programmer: .
Found programmer: Id = "CATERIN"; type = S
    Software Version = 1.0; No Hardware Version given.
Programmer supports auto addr increment.
Programmer supports buffered memory access with buffersize=128 bytes.

Programmer supports the following devices:
    Device code: 0x44

avrdude.exe: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude.exe: Device signature = 0x1e9587 (probably m32u4)
avrdude.exe: NOTE: "flash" memory has been specified, an erase cycle will be performed
             To disable this feature, specify the -D option.
avrdude.exe: erasing chip
avrdude.exe: reading input file "./.build/lets_split_rev2_xyverz.hex"
avrdude.exe: input file ./.build/lets_split_rev2_xyverz.hex auto detected as Intel Hex
avrdude.exe: writing flash (27938 bytes):

Writing | ################################################## | 100% 2.40s

avrdude.exe: 27938 bytes of flash written
avrdude.exe: verifying flash memory against ./.build/lets_split_rev2_xyverz.hex:
avrdude.exe: load data flash data from input file ./.build/lets_split_rev2_xyverz.hex:
avrdude.exe: input file ./.build/lets_split_rev2_xyverz.hex auto detected as Intel Hex
avrdude.exe: input file ./.build/lets_split_rev2_xyverz.hex contains 27938 bytes
avrdude.exe: reading on-chip flash data:

Reading | ################################################## | 100% 0.43s

avrdude.exe: verifying ...
avrdude.exe: 27938 bytes of flash verified

avrdude.exe: safemode: Fuses OK (E:CB, H:D8, L:FF)

avrdude.exe done.  Thank you.
```
Sollten dabei Probleme auftreten (z.B. "Zugriff verweigert" / "Permission denied") muss der Make-Befehl mit privilegierten Berechtigungen ausgeführt werden:

    sudo make <meine_Tastatur>:<meine_Tastaturbelegung>:avrdude

Zusätzlich ist es möglich mehrere Tastaturen in einem Vorgang zu flashen:

    make <keyboard>:<keymap>:avrdude-loop

Du kannst den Loop mit STRG + C unterbrechen sobald der Vorgang abgeschlossen ist. Die korrekte Tastenkombination kann abweichen und hängt vom Betriebssystem ab.


### HalfKay

Für Tastaturen mit PJRC Controllern (Teensy's), wenn Du bereit bist zu kompilieren und die Tastatur zu flashen, öffne ein Befehlszeilen-Fenster und führe den Build-Befehl aus:

    make <meine_Tastatur>:<meine_Tastaturbelegung>:teensy

Wenn deine Tastaturbelegung zum Beispiel den Namen "xyverz" hat und Du eine Tastaturbelegung für ein Ergodox oder Ergodox EZ erzeugen möchtest, lautet der Befehl dafür:

    make ergodox_ez:xyverz:teensy

Nachdem die Kompilation abgeschlossen ist sollte die Ausgabe ungefähr so aussehen:

```
Linking: .build/ergodox_ez_xyverz.elf                                [OK]
Creating load file for flashing: .build/ergodox_ez_xyverz.hex        [OK]
Checking file size of ergodox_ez_xyverz.hex                          [OK]
 * File size is fine - 25584/32256
 Teensy Loader, Command Line, Version 2.1
Read "./.build/ergodox_ez_xyverz.hex": 25584 bytes, 79.3% usage
Waiting for Teensy device...
 (hint: press the reset button)
 ```

An diesem Punkt solltest Du die Tastatur zurücksetzen um den Flash-Vorgang auszulösen. Wenn dies abgeschlossen ist sollte die Ausgabe ungefähr so aussehen:

 ```
Found HalfKay Bootloader
Read "./.build/ergodox_ez_xyverz.hex": 28532 bytes, 88.5% usage
Programming.............................................................
...................................................
Booting
```

### BootloadHID

Für auf Bootmapper Client(BMC)/bootloaderHID/ATmega32A basierende Tastaturen, wenn Du bereit bist zu kompilieren und die Tastatur zu flashen, öffne ein Befehlszeilen-Fenster und führe den Build-Befehl aus:

    make <meine_Tastatur>:<meine_Tastaturbelegung>:bootloaderHID

Wenn deine Tastaturbelegung zum Beispiel den Namen "xyverz" hat und Du eine Tastaturbelegung für ein jj40 erzeugen möchtest, lautet der Befehl dafür:

    make jj40:xyverz:bootloaderHID

Nachdem die Kompilation abgeschlossen ist sollte die Ausgabe ungefähr so aussehen:

```
Linking: .build/jj40_default.elf                                 [OK]
Creating load file for flashing: .build/jj40_default.hex         [OK]
Copying jj40_default.hex to qmk_firmware folder                  [OK]
Checking file size of jj40_default.hex                           [OK]
 * The firmware size is fine - 21920/28672 (6752 bytes free)
```

Wenn dieser Punkt erreicht ist wird das Build-Skript alle 5 Sekunden nach einem DFU Bootloader suchen. Dieser Vorgang wird wiederholt bis er erfolgreich ist oder abgebrochen wird.

```
Error opening HIDBoot device: The specified device was not found
Trying again in 5s.
```

An diesem Punkt solltest Du die Tastatur zurücksetzen um den Flash-Vorgang auszulösen. Wenn dies abgeschlossen ist sollte die Ausgabe ungefähr so aussehen:

```
Page size   = 128 (0x80)
Device size = 32768 (0x8000); 30720 bytes remaining
Uploading 22016 (0x5600) bytes starting at 0 (0x0)
0x05580 ... 0x05600
```

### STM32 (ARM)

Für die meisten ARM Tastaturen (inkl. Proton C, Planck Rev 6 und Preonic Rev 3), wenn Du bereit bist zu kompilieren und die Tastatur zu flashen, öffne ein Befehlszeilen-Fenster und führe den Build-Befehl aus:

    make <meine_Tastatur>:<meine_Tastaturbelegung>:dfu-util

Wenn deine Tastaturbelegung zum Beispiel den Namen "xyverz" hat und Du eine Tastaturbelegung für ein Planck Revision 6 erzeugen möchtest, benutze dafür den folgenden Befehl und reboote die Tastatur in den Bootloader (kurz bevor der Kompiliervorgang abgeschlossen ist):

    make planck/rev6:xyverz:dfu-util

Nachdem der Kompiliervorgang abgeschlossen ist sollte die Ausgabe ungefähr so aussehen:

Für auf Bootmapper Client(BMC)/bootloaderHID/ATmega32A basierende Tastaturen, wenn Du bereit bist zu kompilieren und die Tastatur zu flashen, öffne ein Befehlszeilen-Fenster und führe den Build-Befehl aus:

    make <meine_Tastatur>:<meine_Tastaturbelegung>:bootloaderHID

Wenn deine Tastaturbelegung zum Beispiel den Namen "xyverz" hat und Du eine Tastaturbelegung für ein jj40 erzeugen möchtest, lautet der Befehl dafür:
```
Linking: .build/planck_rev6_xyverz.elf                                       [OK]
Creating binary load file for flashing: .build/planck_rev6_xyverz.bin        [OK]
Creating load file for flashing: .build/planck_rev6_xyverz.hex               [OK]

Size after:
   text    data     bss     dec     hex filename
      0   41820       0   41820    a35c .build/planck_rev6_xyverz.hex

Copying planck_rev6_xyverz.bin to qmk_firmware folder                        [OK]
dfu-util 0.9

Copyright 2005-2009 Weston Schmidt, Harald Welte and OpenMoko Inc.
Copyright 2010-2016 Tormod Volden and Stefan Schmidt
This program is Free Software and has ABSOLUTELY NO WARRANTY
Please report bugs to http://sourceforge.net/p/dfu-util/tickets/

Invalid DFU suffix signature
A valid DFU suffix will be required in a future dfu-util release!!!
Opening DFU capable USB device...
ID 0483:df11
Run-time device DFU version 011a
Claiming USB DFU Interface...
Setting Alternate Setting #0 ...
Determining device status: state = dfuERROR, status = 10
dfuERROR, clearing status
Determining device status: state = dfuIDLE, status = 0
dfuIDLE, continuing
DFU mode device DFU version 011a
Device returned transfer size 2048
DfuSe interface name: "Internal Flash  "
Downloading to address = 0x08000000, size = 41824
Download        [=========================] 100%        41824 bytes
Download done.
File downloaded successfully
Transitioning to dfuMANIFEST state
```

#### STM32 Befehle

Für Tastaturen mit STM32 Controller sind die DFU Befehle wie folgt:

* `:dfu-util` - The default command for flashing to STM32 devices.
* `:dfu-util` - Der Standard-Befehl für STM32 Geräte.
* `:dfu-util-wait` - Funktioniert wie der Standard-Befehl, aber mit einem 10 Sekunden Timeout bevor erneut versucht wird die Firmware zu flashen. Mit dem Parameter `TIME_DELAY=20` auf der Befehlszeile kann der Timeout beeinflusst werden.
   * z.B.: `make <meine_Tastatur>:<meine_Tastaturbelegung>:dfu-util TIME_DELAY=5`
* `:dfu-util-split-left` - Gleiche Funktionsweise wie `dfu-util`, jedoch wird zusätzlich das EEPROM Setting "linke Seite" für geteilte Tastaturen gesetzt.
* `:dfu-util-split-right` - Gleiche Funktionsweise wie `dfu-util`, jedoch wird zusätzlich das EEPROM Setting "rechte Seite" für geteilte Tastaturen gesetzt.

## Probier's aus!

Herzlichen Glückwunsch! Deine individuell angepasst Firmware wurde auf deine Tastatur übertragen!

 Probiere deine neue Tastatur aus und gehe sicher dass alles wie gewünscht funktioniert. Wir haben einen weiteren Artikel zum Thema [Testen und Debuggen](de/newbs_testing_debugging.md) verfasst der sich mit Problembeseitigung beschäftigt um den Beginnger-Guide abzuschließen.
