# Einleitung
Genau wie in einem Computer befindet sich auch in einer Tastatur ein Prozessor.

Dieser Prozessor führt Software aus, die registriert wenn Tasten gedrückt bzw. wieder losgelassen werden und leitet die entsprechenden Signale an den Computer weiter.

QMK übernimmt die Rolle dieser Software und teilt dem Host-Computer den aktuellen Zustand der Tastatur mit. Wenn Du eine Tastaturbelegung definierst, ist dies äquivalent zu einem ausführbarem Programm, das auf deiner Tastatur läuft.

QMK möchte seine BenutzerInnen in die Lage versetzen, simple Aufgaben möglichst einfach zu gestalten und gleichzeitig komplexe Dinge zu ermöglichen, die mit normalen Tastaturen ohne zusätzliche Software undenkbar wären. Du musst nicht programmieren können, um abgefahrene Tastaturbelegungen zu gestalten - es reicht wenn Du eine Idee hast und ein paar einfache syntaktische Regeln verstehen kannst.

# Los geht's!
Bevor Du damit loslegen kannst, deine Tastaturbelegung zu erstellen, musst Du ein wenig Software installieren und Dir eine Entwicklungsumgebung aufsetzen. Die gute Nachricht ist, dass das nur einmal erledigt werden muss, egal für wie viele verschiedene Tastaturen Du hinterher Firmware entwickeln willst.

Wenn Du es vorziehst mit einer grafischen Oberfläche zu entwickeln kannst Du auch dazu gerne direkt mit dem online [QMK Konfigurator](https://config.qmk.fm) loslegen. Siehe auch: [Firmware mit der Online GUI erzeugen](de/newbs_building_firmware_configurator.md)

## Software herunterladen

### Text Editor

Du wirst ein Programm benötigen, mit dem Du **plain text** (= reiner Text) Dateien bearbeiten und speichern kannst. Wenn Du Windows benutzt, reicht dafür schon das normale `Notepad` und für Linux z.B. `gedit` oder `leafpad`. Beide sind sehr rudimentäre Editoren deren Funktionsumfang aber vollkommen ausreicht. Für macOS' standard `TextEdit` muss man ein bisschen vorsichtig sein und darauf achten, beim Speichern explizit unter _Format_ die Option _Reiner Text_ auszuwählen.

Ansonsten ist es empfehlenswert, einen Editor herunterzuladen der für die Programmierung und das Bearbeiten von Code ausgelegt ist wie z.b [Notepad++](http://notepad-plus-plus.org/), [Sublime Text](https://www.sublimetext.com/) oder [VS Code](https://code.visualstudio.com/).

?> Immer noch unsicher, welcher Text Editor der Richtige für Dich ist? Laurence Bradford hat eine hervorragende [Einleitung](https://learntocodewith.me/programming/basics/text-editors/) zu dem Thema geschrieben (auf Englisch).

### QMK Toolbox

QMK Toolbox ist ein optionales grafisches Programm für Windows und macOS, das es erleichtern soll, deine Tastatur zu programmieren und zu debuggen. Du wirst es höchstwahrscheinlich früher oder später als unverzichtbar ansehen, wenn es darum geht eine Tastatur einfach zu flashen oder zu debuggen, da es ermöglicht, sich debug-Nachrichten direkt anzeigen zu lassen.

[Hier kannst Du die aktuelle Version herunterladen.](https://github.com/qmk/qmk_toolbox/releases/latest)

* Für Windows: `qmk_toolbox.exe` (portable) oder `qmk_toolbox_install.exe` (installer)
* Für macOS: `QMK.Toolbox.app.zip` (portable) oder `QMK.Toolbox.pkg` (installer)

## Die Entwicklungsumgebung aufsetzen


Wir haben versucht, die Installation der Entwicklungsumgebung für QMK so einfach wie möglich zu gestalten. Alles, was Du tun musst, ist eine Linux oder Unix Umgebung aufzusetzen, danach macht QMK den Rest.

?> Wenn Du das erste Mal mit der Linux/Unix Befehlszeile arbeitest, schadet es nicht, sich mit ein paar Grundlagen und Befehlen vertraut zu machen. Diese Ressourcen sollten ausreichen, um sich das Nötigste anzueignen um mit QMK arbeiten zu können:<br>
[Erforderliche Linux Grundlagen](https://www.guru99.com/must-know-linux-commands.html)<br>
[Noch ein paar Linux Befehle](https://www.tjhsst.edu/~dhyatt/superap/unixcmd.html)

### Windows

Du wirst MSYS2 (o.Ä.) und Git benötigen.

* Befolge die Installationsanleitung auf der [MSYS2 Homepage](http://www.msys2.org)
* Schließe alle offenen MSYS2 Fenster und öffne ein neues MSYS2 MinGW 64-bit Terminal
* Installiere Git mit dem Kommando: `pacman -S git`

### macOS

Du wirst Homebrew benötigen. Folge dafür den Anweisungen auf der [Homebrew homepage](https://brew.sh).

Nachdem Homebrew erfolgreich installiert ist, kannst Du mit _QMK aufsetzen_ fortfahren. 

### Linux

Du benötigst Git, aber es ist ziemlich wahrscheinlich, dass es bereits installiert ist. Sollte dies nicht der Fall sein, kannst Du es mit dem folgenden Aufruf installieren:

* Debian / Ubuntu / Devuan: `apt-get install git`
* Fedora / Red Hat / CentOS: `yum install git`
* Arch Linux: `pacman -S git`

?> Docker ist ebenfalls eine Option für alle Plattformen. [Hier](de/getting_started_build_tools.md#docker) kannst Du dazu weitere Informationen finden.

## QMK aufsetzen
Wenn Du damit fertig bist, deine Linux/Unix Umgebung zu installieren, kannst Du damit fortfahren QMK herunterzuladen. Dafür werden wir mit Git das QMK Repository "klonen". Öffne ein Terminal oder ein MSYS2 MinGW Fenster, dies wirst Du für den Rest der Anleitung benötigen. In diesem Fenster rufst Du nun die beiden folgenden Kommandos auf:

```shell
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
```
?> Wenn Du bereits weißt, [wie man GitHub benutzt](de/getting_started_github.md), empfehlen wir, dass Du Dir ein eigenen Fork erstellst. Wenn Du nicht weißt, was das bedeuten soll, kannst Du diesen Ratschlag getrost ignorieren.

QMK liefert ein Script mit, das helfen soll, Dir alles Weitere abzunehmen. Du kannst es mit dem folgenden Befehl aufrufen:

    util/qmk_install.sh

## Die Build-Umgebung testen

Nun sollte hoffentlich alles Nötige für eine funktionierende QMK Build-Umgebung installiert sein und Du solltest in der Lage sein, die QMK-Firmware zu kompilieren. Um dies mit einer `default` Tastaturbelegung zu testen, kannst Du den folgenden Befehl ausprobieren:

    make <keyboard>:default

Der Befehl um z.B. die Firmware für ein _Clueboard 66%_ zu erzeugen lautet:

    make clueboard/66/rev3:default

Wenn es fertig ist, sollte der Output ungefähr so ähnlich wie das Folgende aussehen:

```
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

# Eine eigene Tastaturbelegung erstellen
Du bist nun fertig mit dem Setup der Entwicklungsumgebung und solltest somit in der Lage sein, deine eigenen Tastaturbelegungen zu erstellen. Um fortzufahren, folge bitte der nächsten Anleitung unter [Die erste Firmware](de/newbs_building_firmware.md).
