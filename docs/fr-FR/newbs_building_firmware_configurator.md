# Configurateur de QMK

Le [Configurateur de QMK](https://config.qmk.fm) est une interface graphique en ligne permettant de générer des fichiers "hex" du firmware de QMK.

?> **S'il vous plaît, suivez les étapes suivantes dans l'ordre.**

Regardez le [Tutoriel vidéo](https://youtu.be/tx54jkRC9ZY)

Le configurateur de QMK fonctionne mieux avec Chrome et Firefox.

!> **Les fichiers d'autres outils, tels que KLE ou kbfirmware ne seront pas compatibles avec le configurateur QMK. Ne les chargez pas, ne les importez pas. Le configurateur QMK est un outil DIFFERENT.**

## Sélectionner votre clavier

Cliquez la boîte déroulante et sélectionnez le clavier pour lequel vous voulez créer une keymap.

?> Si votre clavier a plusieurs versions, faites attention à utiliser la bonne.

Je vais le répéter, parce que c'est important

!> **FAITES ATTENTION A UTILISER LA BONNE VERSION !**

Si votre clavier est annoncé comme fonctionnant grâce à QMK mais n'est pas dans la liste, il y a des chances que le développeur ne l'ait pas encore fait, ou que nous n'avons pas encore eu le temps de le merger. Ajoutez un problème (issue) sur [qmk_firmware](https://github.com/qmk/qmk_firmware/issues) demandant le support de votre clavier, s'il n'y a pas de [Pull Request](https://github.com/qmk/qmk_firmware/pulls?q=is%3Aopen+is%3Apr+label%3Akeyboard) ouvert pour lui. Il y a aussi des clavier alimentés par QMK qui sont sur le compte GitHub du fabriquant, il est bon de le vérifier aussi.

## Sélectionner la disposition de votre clavier

Choisissez la disposition (layout) qui représente le mieux la keymap que vous voulez créer. Certains clavier n'ont pas encore assez de dispositions ou des dispositions incorrectes. Ils seront supportés dans le future.

## Nom de la Keymap

Appelez cette keymap comme vous voulez.

?> Si vous rencontrez des problèmes lors de la compilation, il peut être utile de changer ce nom, il peut déjà exister dans le dépôt du firmware QMK.

## Créer votre keymap

Entrer un keycode peut s'accomplir de 3 façons différentes.

1. Glisser déposer
2. Cliquer sur un endroit vide sur le layout et cliquer sur le keycode souhaité
3. Cliquer sur un endroit vide sur le layout et appuyer sur une touche physique de votre clavier.

Passez votre souris au dessus d'une touche et un affichage vous dira quel est le rôle du keycode. Pour une version plus verbeuse suivre:

[Référence Keycode basique](https://docs.qmk.fm/#/keycodes_basic)
[Référence Keycode avancé](https://docs.qmk.fm/#/feature_advanced_keycodes)

Dans le cas où vous ne trouvez pas une disposition qui supporte votre keymap, par exemple trois places pour une barre d'espace, ou deux places pour retour clavier, ou deux places pour shift, etc. etc. remplissez les TOUTES.

### Exemples

3 places pour la barre d'espace: Remplissez les TOUTES avec la barre d'espace

2 places pour un retour clavier: Remplissez les DEUX avec un retour clavier

2 places pour un shift droit: Remplissez les DEUX avec un shift droit

1 place pour un shift gauche et 1 place pour le support ISO: Remplissez les deux avec un shift gauche

5 places, mais seulement 4 touches: Deviner et vérifier, ou demander à quelqu'un qui l'a déjà fait.

## Sauvez votre keymap pour des éditions futures

Une fois satisfait de votre keymap, ou si vous souhaitez revenir travailler dessus plus tard, appuyez sur le bouton `Export Keymap`. Il vous permettra de sauvegarder votre keymap avec le nom choisi au dessus suivi de .json.

Vous pouvez ensuite charger ce fichier .json à nouveau en appuxant sur le bouton `Import Keymap`.

!> **ATTENTION** Ce n'est pas le même type de fichier .json utilisé pour kbfirmware.com ou n'importe quel autre outil. Si vous essayez d'utiliser ce fichier pour d'autres outil, ou le fichier .json d'autres outils avec le configurateur QMK, il y a des chances que votre clavier **explose**.

## Générer votre fichier firmware

Appuyez sur le bouton `Compile`.

Une fois la compilation terminée, vous pourrez appuyer sur le bouton vert `Download Firmware`.

## Ecrire votre firmware sur votre clavier

Merci de vous référer à [Flasher le Firmware](fr-FR/newbs_flashing.md)

## Dépannage

#### Mon fichier json ne fonctionne pas

Si le fichier .json a été généré par le configurateur QMK, bravo vous avez trouvé un bug. Merci d'ouvrir une issue sur [qmk_configurator](https://github.com/qmk/qmk_configurator/issues)

Sinon... vous avez raté mon message écris en gras qui dit de ne pas utiliser d'autres fichiers .json?

#### Il y a des espaces en trop dans mon alyout? Qu'est-ce que je fais?

Si vous voulez dire que vous avez trois places pour une barre d'espace, le mieux est de les remplir tous avec une barre d'espace. Vous pouvez faire de même avec les retour clavier et les shift.

#### C'est quoi le keycode pour .......

Merci de regarder

[Référence keycode basique](https://docs.qmk.fm/#/keycodes_basic)
[Référence keycode avancé](https://docs.qmk.fm/#/feature_advanced_keycodes)

#### Ca ne compile pas?

Merci de vérifier les autres dispositions de votre keymap afin d'être sûr qu'il n'y a pas de touches aléatoires.

## Problèmes et Bugs

Nous acceptons toujours les demandes des clients et les rapports de bugs. Merci de les remplirs sur [qmk_configurator](https://github.com/qmk/qmk_configurator/issues)
