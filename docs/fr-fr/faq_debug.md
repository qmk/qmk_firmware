# FAQ Débugage

Cette page détaille diverses questions fréquemment posées par les utilisateurs sur le dépannage de leurs claviers.

# Console de débugage

## `hid_listen` ne reconnaît pas de périphérique

Lorsque la console de débugage sur votre périphérique n'est pas prêt, vous obtiendrez un message similaire :

```
Waiting for device:.........
```

Une fois le périphérique connecté, *hid_listen* le trouve et vous obtiendrez ce message :

```
Waiting for new device:.........................
Listening:
```

Si vous ne recevez pas ce message `Listening:`, essayez de compiler avec `CONSOLE_ENABLE=yes` dans le [Makefile]

Il se peut que vous ayez besoin de certains privilèges avancés pour accéder à des périphériques sur des OS comme Linux.

- Essayez `sudo hid_listen`

## Ne reçoit pas de messages sur la console

Vérifiez :

- *hid_listen* trouve votre périphérique. Voir ci-dessus.
- Activez le débugage en appuyant sur **Magic**+d. Voir [Commandes Magic](https://github.com/tmk/tmk_keyboard#magic-commands).
- Définissez `debug_enable=true` en général dans `matrix_init()` du fichier **matrix.c**.
- Essayez d'utiliser la fonction `print` à la place du debug print. Voir **common/print.h**.
- Déconnectez tous les autres périphériques qui utilisent la fonction console. Voir [Issue #97](https://github.com/tmk/tmk_keyboard/issues/97).

## Linux ou les systèmes UNIX nécessitent des privilèges super utilisateur

Utilisez `sudo` pour exécuter *hid_listen* avec des privilèges étendus.

```
$ sudo hid_listen
```

Ou ajoutez une *udev rule* pour les périphériques TMK en plaçant un fichier dans le répertoire rules. Le chemin vers ce répertoire peut varier en fonction du système.

Fichier: /etc/udev/rules.d/52-tmk-keyboard.rules(sous Ubuntu)
```
# tmk keyboard products     https://github.com/tmk/tmk_keyboard
SUBSYSTEMS=="usb", ATTRS{idVendor}=="feed", MODE:="0666"
```

***

# Divers

## Considérations de sécurité

Vous ne voulez probablement pas "briquer" votre clavier, rendre impossible d'écrire un firmware dessus. Il y a quelques paramètres qui montrent ce qui est (et n'est probablement pas) trop risqué.

- Si votre map de clavier n'inclut pas de RESET, pour entrer en mode DFU, vous devrez appuyer sur le bouton reset du PCB. Cela implique que vous devrez certainement dévisser certaines pièces de votre clavier pour y accéder.
- Modifier les fichiers tmk_core / common peut rendre le clavier inutilisable
- Si un fichier .hex trop large est la cause du problème : `make dfu` supprime le bloc puis teste la taille (il ne fait pas les choses dans le bon ordre), ce qui provoque une erreur. En résultat, le flash n’aura pas été fait et le clavier restera en mode DFU.
- Pour finir, notez que la taille maximale d'un fichier .hex sur un Plank est de 7000h (28672 decimal)

```
Linking: .build/planck_rev4_cbbrowne.elf                                                            [OK]
Creating load file for Flash: .build/planck_rev4_cbbrowne.hex                                       [OK]

Size after:
   text    data     bss     dec     hex filename
      0   22396       0   22396    577c planck_rev4_cbbrowne.hex
```

- La taille du fichier ci-dessus est de 22396/577ch, ce qui est en dessous de 28672/7000h
- Tant que vous avez un fichier .hex alternatif correct, vous pouvez réessayer en le chargeant
- Certaines options que vous pouvez spécifier dans votre Makefile consomme de la mémoire supplémentaire. Faites attention aux options BOOTMAGIC_ENABLE, MOUSEKEY_ENABLE, EXTRAKEY_ENABLE, CONSOLE_ENABLE, API_SYSEX_ENABLE.
- Les outils DFU **ne** vous permettent **pas** d'écrire dans le bootloader (à moins que vous n'ajoutiez des options spéciales), il n'y a donc peu de risque.
- Les EEPROM ont environ 100000 cycles d'écriture. Ne réécrivez pas le firmware de manière continue et répétée. Vous allez détruire définitivement l'EEPROM.

## NKRO ne fonctionne pas

Premièrement, vous devez compiler le firmware avec l'option de compilation `NKRO_ENABLE` dans le **Makefile**.

Essayez la commande `Magic` **N** (`LShift+RShift+N` par défaut) si **NKRO** ne fonctionne toujours pas. Vous pouvez utiliser cette commande pour basculer temporairement entre le mode **NKRO** et **6KRO**. Sous certaines conditions, **NKRO** ne fonctionnera pas et vous devrez basculer en **6KRO**, en particulier lorsque vous êtes dans le BIOS.

Si votre firmware est compilé avec `BOOTMAGIC_ENABLE` vous devrez l'activer avec la commande `BootMagic` **N** (`Espace+N` par défaut). Cette option est enregistrée dans l'EEPROM et sera gardé entre deux cycles de démarrage.

https://github.com/tmk/tmk_keyboard#boot-magic-configuration---virtual-dip-switch

## Le TrackPoint a besoin Circuit de réinitialisation (Support de souris PS/2)

Sans circuit de réinitialisation vous allez avoir des résultats inconsistants à cause de la mauvaise initialisation du matériel. Regardez le schéma du circuit du TPM754.

- http://geekhack.org/index.php?topic=50176.msg1127447#msg1127447
- http://www.mikrocontroller.net/attachment/52583/tpm754.pdf

## Impossible de lire la colonne de la matrice après 16

Utilisez `1UL<<16` à la place de `1<<16` dans `read_cols()` du fichier [matrix.h] lorsque le nombre de vos colonnes dépassent 16.

En C, `1` implique un type [int] qui est [16 bits] pour les AVR, ce qui implique que vous ne pouvez pas décaler à gauche de plus de 15. Si vous utilisez `1<<16`, vous aurez un résultat non attendu de zéro. Vous devez donc utiliser un type [unsigned long] en utilisant `1UL`.

http://deskthority.net/workshop-f7/rebuilding-and-redesigning-a-classic-thinkpad-keyboard-t6181-60.html#p146279

## Les touches spéciales ne fonctionnent pas (Touche Système, Touches de contrôle du son)

Vous devez définir `EXTRAKEY_ENABLE` dans le fichier `rules.mk` pour les utiliser dans QMK.

```
EXTRAKEY_ENABLE = yes          # Audio control and System control
```

## Réveiller du mode veille ne fonctionne pas

Sous Windows, activez l'option `Permettre au périphérique de sortir l'ordinateur de veille` dans les paramètres des **Options d'alimentations** du **Gestionnaire de périphériques**. Vérifiez aussi les paramètres du BIOS.

Appuyer sur n'importe quelle touche en mode veille devrait sortir l'ordinateur de veille.

## Vous utilisez un Arduino ?

**Faites attention au fait que le nommage des pin d'un Arduino diffère de la puce**. Par exemple, la pin `D0` n'est pas `PD0`. Vérifiez le circuit avec la fiche technique.

- http://arduino.cc/en/uploads/Main/arduino-leonardo-schematic_3b.pdf
- http://arduino.cc/en/uploads/Main/arduino-micro-schematic.pdf

Les Arduino Leonardo et micro ont des **ATMega32U4** et peuvent être utilisés avec TMK, mais le bootloader Arduino peut causer des problèmes.

## Activer JTAG

Par défaut, le débugage des interfaces JTAG est désactivé dès que le clavier démarre. Les MCUs compatible JTAG viennent d'usine avec le fusible `JTAGEN` activé, et il prend certaines pins du MCU que la board pourrait utiliser pour la matrice, les LEDs, etc.

Si vous voulez garder JTAG activé, ajoutez la ligne suivante à votre fichier `config.h` :

```c
#define NO_JTAG_DISABLE
```

## Compatibilité USB 3

Il semble que certaines personnes ont eu des problèmes avec les ports USB 3, essayez un port USB 2.

## Compatibilité Mac

### OS X 10.11 et Hub

https://geekhack.org/index.php?topic=14290.msg1884034#msg1884034

## Problème sur BIOS (UEFI) / Resume (Mise en veille et réveil) / Redémarrage

Certaines personnes ont eu des problèmes de fonctionnement de leur clavier dans le BIOS et/ou après des redémarrages.

Pour le moment, l'origine du problème n'est pas comprise, mais certaines options de compilation semble liées. Dans le Makefile, essayez de désactiver les options comme  `CONSOLE_ENABLE`, `NKRO_ENABLE`, `SLEEP_LED_ENABLE` et/ou d'autres.

https://github.com/tmk/tmk_keyboard/issues/266
https://geekhack.org/index.php?topic=41989.msg1967778#msg1967778

## FLIP ne marche pas

### `AtLibUsbDfu.dll` Not Found

Supprimez le pilote actuel et réinstallez celui donné par FLIP dans le gestionnaire de périphériques.

http://imgur.com/a/bnwzy
