# Breaking changes

Ce document décrit le processus de QMK pour la gestion des breaking changes. Un breaking change est un changement qui modifie la manière dont QMK fonctionne introduisant des incompatibilités ou des comportements dangereux. Nous limitons ces changements afin que les utilisateurs n'aient pas peur de casser leurs keymaps en mettant à jour leur version de QMK.

La période de breaking change est quand nous allons fusionner un PR qui change QMK d'une manière dangereuse ou inattendue. Il y a une période interne de test afin de nous assurer que les problèmes résiduels sont rares ou impossible à prévoir.

## Qu'est-ce qui a été inclus dans des Breaking Changes précédents?

* [30 août 2019](ChangeLog/20190830.md)

## Quand va être le prochain Breaking Change?

Le prochain Breaking Change est planifié pour le 29 novembre.

### Dates importantes

* [x] 21 septembre 2019 - `future` est créé. Il va être rebasé de manière hebdomadaire.
* [ ] 01 novembre 2019 - `future` fermé aux nouveaux PRs.
* [ ] 01 novembre 2019 - Appel aux testeurs.
* [ ] 27 novembre 2019 - `master` est bloqué, pas de PRs fusionnés.
* [ ] 29 novembre 2019 - `future` est fusionné dans `master`.
* [ ] 30 novembre 2019 - `master` est débloqué. Les PRs peuvent à nouveau être fusionnés.

## Quels changements seront inclus?

Pour voir une liste de candidats de breaking changes, vous pouvez regarder la liste des [labels `breaking_change`](https://github.com/qmk/qmk_firmware/pulls?q=is%3Aopen+label%3Abreaking_change+is%3Apr). De nouveaux changements peuvent être ajoutés entre maintenant et lorsque `future` est fermée, et un PR avec ce label n'est pas garanti d'être fusionné.

Si vous souhaitez que votre breaking change soit inclus dans ce tour, vous devez créer un PR avec le label `breaking_change` et faire en sorte qu'il soit accepté avant que `future` ne soit fermé. Une fois `future` fermé, aucun nouveau breaking change sera accepté.

Critère d'acceptation:

* Le PR est complété et prêt à fusionner
* Le PR a un ChangeLog

# Checklists

Cette section documente plusieurs processus que nous utilisons en lançant le processus de Breaking Change.

## Rebase `future` de `master`

Ceci est lancé chaque vendredi tant que `future` est ouvert.

Processus:

```
cd qmk_firmware
git checkout master
git pull --ff-only
git checkout future
git rebase master
git push --force
```

## Créer la branche `future`

Ceci est fait immédiatement après la fusion de la branche `future` précédente.

* `qmk_firmware` git commands
    * [ ] `git checkout master`
    * [ ] `git pull --ff-only`
    * [ ] `git checkout -b future`
    * [ ] Modifie `readme.md`
        * [ ] Ajoute un message en haut qui indique que c'est une branche de test.
        * [ ] Ajoute un lien vers ce document
    * [ ] `git commit -m 'Branch point for <DATE> Breaking Change'`
    * [ ] `git tag breakpoint_<YYYY>_<MM>_<DD>`
    * [ ] `git tag <next_version>` # Evite que le label point d'arrêt soit confondu par un incrément de version
    * [ ] `git push origin future`
    * [ ] `git push --tags`

## 4 Semaines Avant la Fusion

* `future` est maintenant fermé aux nouveaux PRs, seul des correctifs pour les PRs courants peuvent être mergés
* Envoi de l'appel aux testeurs
    * [ ] Discord
    * [ ] GitHub PR
    * [ ] https://reddit.com/r/olkb

## 1 Semaine Avant la Fusion

* Annonce que master sera fermée entre <2 jours avant> à <Jour de la fusion>
    * [ ] Discord
    * [ ] GitHub PR
    * [ ] https://reddit.com/r/olkb

## 2 Jours Avant la Fusion

* Annonce que master est fermé pour 2 jours
    * [ ] Discord
    * [ ] GitHub PR
    * [ ] https://reddit.com/r/olkb

## Jour de la fusion

* `qmk_firmware` git commands
    * [ ] `git checkout future`
    * [ ] `git pull --ff-only`
    * [ ] `git rebase origin/master`
    * [ ] Modifie `readme.md`
        * [ ] Supprimer les notes à propos de `future`
    * [ ] Regroupe ChangeLog dans un fichier.
    * [ ] `git commit -m 'Merge point for <DATE> Breaking Change'`
    * [ ] `git push origin future`
* Actions sur GitHub
    * [ ] Crée un PR pour `future`
    * [ ] Fusion le PR `future`
