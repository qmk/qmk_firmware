# QMK CLI (Kommandozeile)

Diese Seite beschreibt die Einrichtung und den Umgang mit dem QMK CLI (Kommandozeile).

# Übersicht

Die QMK CLI vereinfacht das Zusammenbauen und Arbeiten mit QMK Tastaturen. Hier findest Du wichtige Befehle, um beispielsweise das Herunterladen und Kompilieren der QMK Firmware oder das Erstellen von Tastaturbelegungen (und vieles mehr) zu erleichtern.

* [Globale CLI](#globale-cli)
* [Lokale CLI](#lokale-cli)
* [CLI-Befehle](#cli-befehle)

# System-Anforderungen

Die CLI benötigt Python 3.5 oder höher. Außerdem ist es nötig, die Packages laut [`requirements.txt`](https://github.com/qmk/qmk_firmware/blob/master/requirements.txt) zu installieren.

# Globale CLI

QMK bietet ein installierbares CLI, das Du zum Einrichten Deiner QMK Build-Umgebung verwenden kannst. Dieses ermöglicht Dir das Arbeiten mit QMK, und erleichtert das Arbeiten mit mehreren Kopien der `qmk_firmware`. Wir empfehlen, dieses CLI zu installieren und regelmäßig upzudaten.

## Installation mit Homebrew (macOS, manche Linux)

Solltest Du [Homebrew](https://brew.sh) installiert haben, kannst Du QMK per tap installieren:

```
brew tap qmk/qmk
brew install qmk
export QMK_HOME='~/qmk_firmware' # Optional: setzt den Installationsort für `qmk_firmware`
qmk setup  # Dies klont `qmk/qmk_firmware` und richtet optional auch Deine Build-Umgebung ein
```

## Installation mit easy_install oder pip

Falls Du kein Homebrew hast, kannst Du QMK auch manuell installieren. Zuerst musst Du sicherstellen, dass Python 3.5 (oder höher) und pip installiert ist. Dann installiere QMK mit diesem Befehl:

```
pip3 install qmk
export QMK_HOME='~/qmk_firmware' # Optional: setzt den Installationsort für `qmk_firmware`
qmk setup  # Dies klont `qmk/qmk_firmware` und richtet optional auch Deine Build-Umgebung ein
```
## Installation mit git Repo

`git clone https://github.com/qmk/qmk_cli.git && cd qmk_cli && python3 setup.py install`

## Packaging für andere Betriebssysteme

Wir suchen nach Freiwilligen, die ein `qmk`-Package für weitere Betriebssysteme erstellen und pflegen. Falls Du ein Package für Dein OS erstellen möchtest, bitte befolge diese Richtlinien:

* Verwende "Best Practices" für Dein OS, sollten sie mit diesen Richtlinien in Konflikt stehen.
    * Dokumentiere den Grund in einem Kommentar, wenn Du abweichen musstest.
* Installiere mit einem [virtualenv](https://virtualenv.pypa.io/en/latest/).
* Weise den User an, die Umgebungs-Variable `QMK_HOME` zu setzen, um die Firmware-Quelle anders einzustellen als `~/qmk_firmware`.

# Lokale CLI

Wenn Du die globale CLI nicht verwenden möchtest, beinhaltet `qmk_firmware` auch eine lokale CLI. Du kannst sie hier finden: `qmk_firmware/bin/qmk`. Du kannst den `qmk`-Befehl aus irgendeinem Datei-Verzeichnis ausführen und es wird immer auf dieser Kopie von `qmk_firmware` arbeiten.

**Beispiel**:

```
$ ~/qmk_firmware/bin/qmk hello
Ψ Hello, World!
```

## Einschränkungen der lokalen CLI

Hier ein Vergleich mit der globalen CLI:

* Die lokale CLI unterstützt kein `qmk setup` oder `qmk clone`.
* Die lokale CLI arbeitet immer innerhalb der selben `qmk_firmware`-Verzeichnisstruktur, auch wenn Du mehrere Repositories geklont hast.
* Die lokale CLI läuft nicht in einer virtualenv. Daher ist es möglich, dass Abhängigkeiten (dependencies) miteinander in Konflikt kommen/stehen.

# CLI-Befehle

## `qmk compile`

Dieser Befehl erlaubt es dir, die Firmware - aus egal welchem Datei-Verzeichnis - zu compilen. Du kannst JSON-Exporte von <https://config.qmk.fm> oder Keymaps in der Repo kompilen.

**Anwendung für Konfigurations-Exports**:

```
qmk compile <configuratorExport.json>
```

**Anwendung für Keymaps**:

```
qmk compile -kb <keyboard_name> -km <keymap_name>
```

## `qmk format-c`

Dieser Befehl formatiert C-Code im clang-Format. Benutze ihn ohne Argumente, um den core-Code zu formatieren, oder benutze Namen von Dateien in der CLI, um den Befehl auf bestimmte Dateien anzuwenden.

**Anwendung**:

```
qmk format-c [file1] [file2] [...] [fileN]
```

## `qmk config`

Dieser Befehl konfiguriert das Verhalten von QMK. Für die volle `qmk config`-Dokumentation gehe zu [CLI-Konfiguration](cli_configuration.md).

**Anwendung**:

```
qmk config [-ro] [config_token1] [config_token2] [...] [config_tokenN]
```

## `qmk docs`

Dieser Befehl startet einen lokalen HTTP-Server, den Du zum Browsen oder Verbessern der Dokumentation verwenden kannst. Der Default-Port ist 8936.

**Anwendung**:

```
qmk docs [-p PORT]
```

## `qmk doctor`

Dieser Befehl untersucht Deine Umgebung und warnt Dich vor potentiellen Build- oder Flash-Problemen.

**Anwendung**:

```
qmk doctor
```

## `qmk list-keyboards`

Dieser Befehl listet alle zurzeit in `qmk_firmware` definierten Tastaturen/Keyboards auf.

**Anwendung**:

```
qmk list-keyboards
```

## `qmk new-keymap`

Dieser Befehl erstellt eine neue Keymap basierend auf einer existierenden Standard-Keymap eines bestimmten Keyboards.

**Anwendung**:

```
qmk new-keymap [-kb KEYBOARD] [-km KEYMAP]
```

## `qmk format-py`

Dieser Befehl formatiert Python-Code in `qmk_firmware`.

**Anwendung**:

```
qmk format-py
```

## `qmk pytest`

Dieser Befehl führt die Python Test Suite aus. Wenn Du Python-Code veränderst, solltest Du sicherstellen, dass der Test erfolgreich ausgeführt wurde.

**Anwendung**:

```
qmk pytest
```
