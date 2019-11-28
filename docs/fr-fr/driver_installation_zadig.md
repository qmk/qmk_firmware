# Installation du driver du bootloader avec Zadig

Vous n’aurez pas besoin de pilote particulier pour utiliser un clavier QMK. En effet, QMK  se présente à l'ordinateur hôte comme un clavier HID standard et sera reconnu sans problème. Cependant vous aurez peut-être besoin d'un pilote pour flasher votre clavier avec Windows. En effet, quand vous redémarrerez votre clavier en mode bootloader, le périphérique que détectera Windows ne sera pas un clavier mais un périphérique bootloader.

Il existe deux exceptions : le bootloader Caterina, qui se trouve en général sur les Pro Micros, et le bootloader Halfkay, livré avec les Teensy de PJRC. Ils apparaissent respectivement sous la forme d'un port série et d'un périphérique HID générique, ne nécessitant pas de pilote particulier.

Nous vous recommandons d'utiliser l'utilitaire [Zadig](https://zadig.akeo.ie/). Si vous avez configuré votre environnement de développement avec Msys2 ou WSL, le script `qmk_install.sh` vous aura proposé l'installation des pilotes durant le processus.

## Installation

Passez votre clavier en mode bootloader, soit en appuyant sur le keycode `RESET` (qui peut se trouver dans un calque différent) ou en appuyant sur le bouton reset qui se trouve en général sous la board. Si votre clavier n'a aucune de ces options, essayez de le brancher en maintenant Escape ou Espace+`B` appuyés (voir la documentation de [Bootmagic](feature_bootmagic.md) pour plus de détails). Certaines boards utilisent [Command](feature_command.md) à la place de Bootmagic. Dans ce cas, vous pouvez entrer en mode bootloader en appuyant, à n'importe quel moment lorsque le clavier est branché, sur les combinaisons de touches Shift Gauche+Shift Droit+`B` ou Shift Gauche+Shift Droit+Escape.
Certains claviers ont des instructions spécifiques pour passer en mode bootloader. Par exemple, la touche [Bootmagic Lite]](feature_bootmagic.md#bootmagic-lite) (défaut : Échap) peut être sur une touche différente telle que Contrôle Gauche. La combinaison pour la Command (défaut : Shift Gauche+Shift Droit) peut être différente, par exemple Contrôle Gauche+Contrôle Droit. Référez-vous au fichier README de votre clavier.

Pour mettre un clavier en mode bootloader avec USBaspLoader, appuyez sur le bouton `RESET` tout en maintenant le bouton `BOOT`. Vous pouvez aussi maintenir le bouton `BOOT` en branchant le câble USB.

Zadig détectera automatiquement les périphériques en mode bootloader. Il se peut toutefois que vous deviez vérifier en passant par  **Options → List All Devices**.


 - Pour les claviers avec des MCUs Atmel AVR, le bootloader aura un nom similaire à `ATm32U4DFU`, et un Vendor ID `03EB`.
 - Les bootloaders USBasp s'appelleront `USBasp`, avec un VID/PID `16C0:05DC`.
 - Les claviers AVR flashé avec le bootloader QMK-DFU s'appelleront `<nom du clavier> Bootloader` et auront aussi le VID `03EB`.
 - Pour la plupart des claviers ARM, ils s'appelleront `STM32 BOOTLOADER`, et auront un VID/PID `0483:DF11`.

!> Si Zadig affiche certains de vos périphériques avec le driver `HidUsb`, votre clavier n'est probablement pas en mode bootloader. La flèche aura une couleur orange et vous aurez un message de confirmation vous demandant de modifier un pilote système. **Ne continuez pas!**

Si la flèche apparaît en vert, sélectionnez le driver et appuyez sur le bouton **Install Driver**. Le driver `libusb-win32` devrait normalement fonctionner pour AVR, et `WinUSB` pour ARM. Si vous avez des problèmes pour flasher la board, essayez d'installer un pilote différent de la liste. Pour flasher un périphérique USBaspLoader en ligne de commande avec msys2, le driver `libusbk` est recommandé, sinon `libusb-win32` devrait fonctionner correctement si vous utilisez QMK Toolbox pour flasher.

![Zadig montrant un driver de bootloader installé correctement](https://i.imgur.com/b8VgXzx.png)

Finalement, débranchez et rebranchez le clavier afin de vous assurer que le nouveau pilote a bien été chargé. Si vous utilisez QMK Toolbox pour flasher, redémarrez-le aussi, il arrive qu'il n'arrive pas à détecter le changement de driver.

## Récupérer l'installation du mauvais périphérique

Si vous n'arrivez plus à saisir de texte avec le clavier, il est possible que vous ayez installé le driver sur le clavier au lieu du bootloader. Vous pouvez facilement vérifier ceci dans Zadig. Un clavier fonctionnel a le pilote `HidUsb` installé sur toutes ses interfaces :

![Un clavier fonctionnel vu par Zadig](https://i.imgur.com/Hx0E5kC.png)

Ouvrez le Gestionnaire de périphériques et cherchez un périphérique qui ressemble à votre clavier.

![La board avec le mauvais driver installé, dans le Gestionnaire de périphériques](https://i.imgur.com/L3wvX8f.png)

Cliquez dessus avec le bouton droit et sélectionner **Désinstaller le périphérique**. Faites bien attention à sélectionner **Supprimer le pilote pour ce périphérique** avant de valider.

![Le dialogue Suppression de périphérique, avec la boîte "suppression de pilote" cochée](https://i.imgur.com/aEs2RuA.png)

Appuyez sur **Action → Analyser les changements de hardware**. A ce stade, vous devriez pouvoir saisir à nouveau. Vérifiez dans Zadig que les périphériques utilisent bien le pilote `HidUsb`. Si c'est le cas, vous avez corrigé le problème, votre clavier devrait fonctionner à nouveau !
