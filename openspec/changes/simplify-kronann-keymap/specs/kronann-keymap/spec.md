# Spec Delta

## Purpose

Décrire la disposition du clavier Corne `kronann` : une base QWERTY et trois couches, qui se comportent pareil sur macOS et Linux, avec un hôte réglé en US/ABC.

## ADDED Requirements

### Requirement: Base QWERTY
La couche de base SHALL envoyer les lettres et la ponctuation d'un QWERTY US standard : Tab, Ctrl et Shift sur la colonne extérieure gauche ; Bksp, `'` et Échap sur la colonne extérieure droite. Aucune touche de la base n'a de comportement tap-hold.

#### Scenario: Lettres QWERTY
- **WHEN** on tape la rangée du haut de gauche à droite, sur un hôte en US/ABC
- **THEN** l'hôte reçoit `Tab q w e r t y u i o p Bksp`

#### Scenario: Pas de tap-hold sur la base
- **WHEN** on maintient la touche A pendant une seconde
- **THEN** l'hôte reçoit la répétition de `a` et aucun modificateur

### Requirement: Mêmes codes sur macOS et Linux
Le firmware SHALL envoyer les mêmes codes quel que soit l'OS hôte, sans détection d'OS ni échange de modificateurs.

#### Scenario: Ctrl identique sur macOS et Linux
- **WHEN** on presse la touche Ctrl (colonne extérieure gauche, rangée du milieu), clavier branché sur macOS puis sur Linux
- **THEN** l'hôte reçoit Control gauche dans les deux cas

### Requirement: Touche Hyper au pouce gauche
Le pouce gauche extérieur SHALL envoyer Super/⌘ gauche, que Hyprland utilise comme modificateur et que Karabiner transforme en Hyper sur Mac.

#### Scenario: Hyper envoie Super gauche
- **WHEN** on maintient le pouce gauche extérieur et on tape `b`
- **THEN** l'hôte reçoit Super gauche + `b`

### Requirement: Flèches sur les touches intérieures
Les quatre touches intérieures de la base SHALL envoyer les flèches : ← et → à gauche (haut, milieu), ↑ et ↓ à droite (haut, milieu).

#### Scenario: Flèches intérieures
- **WHEN** on presse la touche intérieure gauche du haut, puis la touche intérieure droite du milieu
- **THEN** l'hôte reçoit ← puis ↓

### Requirement: Shift + Bksp supprime
Shift + Bksp SHALL envoyer Suppr (Delete), sans Shift.

#### Scenario: Shift + Bksp = Suppr
- **WHEN** on maintient Shift et on tape Bksp
- **THEN** l'hôte reçoit Delete, sans modificateur Shift

### Requirement: Shift standard
En dehors de Bksp, Shift SHALL produire les caractères shiftés du QWERTY US, sans surcharge.

#### Scenario: Shift sur la ponctuation
- **WHEN** on maintient Shift et on tape `.` puis `,`
- **THEN** l'hôte reçoit `>` puis `<`

### Requirement: Couche LOWER chiffres et symboles
Tant que le pouce gauche central est maintenu, la couche LOWER SHALL être active : `` ` `` et 1–0 sur la rangée du haut ; `! @ # $ % ^ & * ( ) ~` sur la rangée du milieu ; `_ + { } |` et `- = [ ] \` sur la rangée du bas.

#### Scenario: Chiffres sur LOWER
- **WHEN** on maintient LOWER et on tape la rangée du haut, des touches Q à P
- **THEN** l'hôte reçoit `1 2 3 4 5 6 7 8 9 0`

### Requirement: Workspaces sur LOWER
Sur LOWER, les touches intérieures droites SHALL envoyer Super+PgUp (haut, workspace précédent) et Super+PgDn (milieu, workspace suivant).

#### Scenario: Workspace suivant
- **WHEN** on maintient LOWER et on presse la touche intérieure droite du milieu
- **THEN** l'hôte reçoit Super gauche + Page Down

### Requirement: Bascule IME sur LOWER
Sur LOWER, la touche Espace SHALL envoyer Ctrl+Espace, pour basculer entre ABC et le japonais.

#### Scenario: Bascule ABC / japonais
- **WHEN** on maintient LOWER et on presse Espace
- **THEN** l'hôte reçoit Control gauche + Espace

### Requirement: Souris sur RAISE
Tant que le pouce droit central est maintenu, la couche RAISE SHALL piloter la souris de la main gauche : déplacement sur E S D F, molette sur A et Z, clics gauche/droit/milieu sur V C X, clics gauche/droit aussi sur les pouces gauches (Espace, Hyper), vitesse lente sur G.

#### Scenario: Déplacer et cliquer
- **WHEN** on maintient RAISE, on maintient F, puis on tape V
- **THEN** le pointeur se déplace vers la droite, puis l'hôte reçoit un clic gauche

### Requirement: Navigation et média sur RAISE
Sur RAISE, la main droite SHALL avoir les flèches sur H J K L ; Début, PgDn, PgUp, Fin et Impr écran sur Y U I O P ; Muet, Volume −/+ et Luminosité −/+ sur N M , . /.

#### Scenario: Flèches vim
- **WHEN** on maintient RAISE et on tape `h j k l`
- **THEN** l'hôte reçoit ← ↓ ↑ →

### Requirement: Couche ADJUST
Tant que LOWER et RAISE sont maintenus ensemble, la couche ADJUST SHALL être active : F1–F12 sur la rangée du haut, réglages RGB à gauche, et Boot (passage en mode flash) sur les deux touches extérieures du bas.

#### Scenario: Touches de fonction
- **WHEN** on maintient LOWER et RAISE, puis on tape la touche Q
- **THEN** l'hôte reçoit F2

#### Scenario: Passage en mode flash
- **WHEN** on maintient LOWER et RAISE, puis on presse la touche extérieure gauche du bas
- **THEN** la moitié de clavier redémarre en mode bootloader

### Requirement: Couleur par couche
Les LED SHALL indiquer la couche active : éteintes sur BASE, une couleur distincte pour LOWER, RAISE et ADJUST, sur les deux moitiés.

#### Scenario: LED sur RAISE
- **WHEN** on maintient RAISE
- **THEN** les LED des deux moitiés prennent la couleur de RAISE, et s'éteignent au relâchement
