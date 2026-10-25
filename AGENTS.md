<!-- harness:begin -->
# Instructions pour les agents

## Conventions

- Prompts, specs et docs en français ; code, identifiants et commits en anglais.
- Commits au format Conventional Commits : `feat(scope): …`, `fix: …`, `docs: …`.
- **Commandes pour l'humain** : toute commande qu'il doit lancer lui-même s'annonce par la ligne « 👺 **À toi** : », suivie d'un bloc de code `bash`, une commande par ligne, sans autre texte dans le bloc.

## Commandes du projet

- **install** : _non configuré_
- **test** : `qmk compile -kb crkbd/rev4_1/standard -km kronann`
- **lint** : _non configuré_
- **typecheck** : `qmk compile -kb crkbd/rev4_1/standard -km kronann`
- **format** : _non configuré_
- **lintFiles** : _non configuré_

## Principes de code

- **Pragmatisme, KISS** : la solution la plus simple qui fonctionne.
- **DRY, règle de trois** : dupliquer deux fois, factoriser à la troisième. Pas d'abstraction pour un seul usage.
- **Code expressif** : petites fonctions nommées pour ce qu'elles font, faciles à tester.
- **Clean au sens large** : responsabilités séparées, dépendances explicites, logique métier isolée des I/O.
- **Le framework d'abord** : utiliser les routines du framework plutôt que du code natif difficile à lire.
- **Commentaires** : seulement pour un point délicat qu'on n'a pas pu rendre lisible, en une phrase. Ne jamais paraphraser le code.
- **Tests** : tester le comportement, pas l'implémentation. Mocker uniquement les frontières (I/O, réseau, horloge), jamais nos propres fonctions.

## Règles de travail

Règles apprises sur des échecs réels, valables dans tous les projets.

- **Prouve la cause avant de corriger, par un log ou une reproduction** : une hypothèse écartée sans preuve a déjà mené à une correction fausse (2026-10-20).
- **Ne tiens pas pour prouvée une correction validée par un mock de bibliothèque externe** : il ne prouve que ton hypothèse ; fais-la vérifier dans l'application, ou signale-le dans ton rapport (2026-10-20).
- **Avant de commiter, installe, compile et lance les tests dans le dossier où tu travailles** : un nouveau worktree n'a pas de dépendances, même pour un petit correctif (2026-10-19).
- **Quand une maquette existe, lis l'image elle-même** : son nom ou sa description ne suffisent pas à respecter la mise en page (2026-10-19).
<!-- harness:end -->

## Journal des échecs

Chaque échec récurrent d'un agent devient ici une règle courte et actionnable.
