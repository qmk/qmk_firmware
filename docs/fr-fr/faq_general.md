# Questions fréquemment posées

## Qu'est-ce que QMK ?

[QMK](https://github.com/qmk), acronyme pour Quantum Mechanical Keyboard, est un groupe de personnes qui construisent des outils pour des claviers personnalisés. Nous avons commencé par le [firmware QMK](https://github.com/qmk/qmk_firmware), un fork très modifié du firmware [TMK](https://github.com/tmk/tmk_keyboard).

## Quelles sont les différences entre QMK et TMK ?

TMK a été conçu et développé à l'origine par [Jun Wako](https://github.com/tmk). QMK a démarré comme étant le fork de [Jack Humbert](https://github.com/jackhumbert) pour le Planck. Au bout d'un moment, le fork de Jack a divergé de manière significative de TMK et, en 2015, Jack a décidé de le renommer QMK.

D'un point de vue technique, QMK se base sur TMK en lui ajoutant plusieurs nouvelles fonctionnalités.
QMK a notamment augmenté le nombre de keycodes disponibles et les a utilisé pour implémenter des fonctionnalités avancées telles que `S()`, `LCTL()` et `MO()`. Vous pouvez voir une liste complète de ces keycodes dans [Keycodes] (keycodes.md).

D'un point de vue management de projet et communauté, Hasu, sur TMK maintient tous les claviers supportés officiellement par lui-même, avec un peu de support de la communauté. Il existe ou peuvent être créées d'autres communautés maintenant des fork pour d'autres claviers. Peu de keymaps sont définies par défaut, les utilisateurs ne se partagent donc pas leurs keymaps en général. QMK encourage le partage des claviers et des keymaps à l'aide d'un dépôt géré de manière centrale, acceptant les pull requests qui suivent les standards de qualité. Ceux-ci sont surtout maitenus par la communauté, mais l'équipe de QMK aide aussi lorsque c'est nécessaire.

Les deux approches ont leurs avantages et leurs inconvénients, et le développements de fonctionnalités intéressantes sont partagées entre TMK et QMK lorsque fait sens.
