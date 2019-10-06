# Comment contribuer

👍🎉 Premièrement, merci de prendre le temps de lire ceci et de contribuer! 🎉👍

Les contributions de tiers nous aide à améliorer et faire grandir QMK. Nous voulons rendre les pull requests et le processus de contribution utile et simple à la fois pour les contributeurs et les mainteneurs. A cette fin, nous avons mis en places des directives pour les contibuteurs afin que votre pull request puisse être accepté sans changement majeur.

* [Aperçu du projet](#project-overview)
* [Conventions de codage](#coding-conventions)
* [Directives générales](#general-guidelines)
* [Que veut dire le code de conduite pour moi?](#what-does-the-code-of-conduct-mean-for-me)

## Je ne veux pas lire tous ce pavé! J'ai juste une question!

Si vous voulez poser une question sur QMK, vous pouvez le faire sur le [sous-reddit OLKB](https://reddit.com/r/olkb) ou sur [Discord](https://discord.gg/Uq7gcHh).

Merci de garder ceci en tête:

* Cela peut prendre plusieurs heures pour que quelqu'un réponde à votre question. Merci d'être patient!
* Tous ceux impliqués avec QMK fait don de son temps et de son énergie. Nous ne sommes pas payés pour travailler sur ou répondre aux questions concernant QMK.
* Essayez de poser vos questions de manière à ce qu'elles soient le plus simple à répondre possible. Si vous n'êtes pas sûrs de savoir comment faire, voici quelques bon guides (en anglais):
  * https://opensource.com/life/16/10/how-ask-technical-questions
  * http://www.catb.org/esr/faqs/smart-questions.html

# Aperçu du projet

QMK est majoritairement écrit en C, avec quelques fonctions et parties spécifiques écrites en C++. Il est destiné aux processeurs intégrés que l'on trouve dans des clavier, particulièrement AVR ([LUFA](http://www.fourwalledcubicle.com/LUFA.php)) et ARM ([ChibiOS](http://www.chibios.com)). Si vous maîtrisez déjà la programmation sur Arduino, vous trouverez beaucoup de concepts et de limitations familiers. Une expérience préalable avec les Arduino n'est pas nécessaire à contribuer avec succès à QMK.

<!-- FIXME: We should include a list of resources for learning C here. -->

# Où trouver de l'aide?

Si vous avez besoin d'aide, vous pouvez [ouvrir une issue](https://github.com/qmk/qmk_firmware/issues) ou [un chat sur Discord](https://discord.gg/Uq7gcHh).

# Comment contribuer?

Vous n'avez encore jamais contribué à un projet open source? Vous vous demandez comment les contributions dans QMK fonctionnent? Voici un aperçu rapide!

0. Enregistrez-vous sur [GitHub](https://github.com).
1. Définissez une keymap à contribuer, [trouvez une issue](https://github.com/qmk/qmk_firmware/issues) que vous souhaitez corriger, ou [une fonction](https://github.com/qmk/qmk_firmware/issues?q=is%3Aopen+is%3Aissue+label%3Afeature) que vous voulez ajouter.
2. Créez un fork sur le dépôt associé avec une issue sur votre compte GitHub. Cela veut dire que vous allez avoir une copie du dépôt sous `your-GitHub-username/qmk_firmware`.
3. Clonez le dépôt sur votre macine locale en utilisant `git clone https://github.com/github-username/repository-name.git`.
4. Si vous travaillez sur une nouvelle fonctionnalité, pensez à ouvrir une issue pour parler avec nous du travail que vous souhaitez démarrer.
5. Créez une nouvelle branche pour votre correctif en utilisant `git checkout -b branch-name-here`.
6. Faites les changements nécessaires pour corriger le problème ou ajouter la fonctionnalité.
7. Utilisez `git add insert-paths-of-changed-files-here` pour ajouter les contenus des fichiers modifiés au "snapshot" que git utilise pour gérer l'état du projet, appelé aussi l'index.
8. Utilisez `git commit -m "Insert a short message of the changes made here"` pour enregistrer le contenu de l'index avec un message descriptif.
9. Poussez les changements vers votre dépôt sur GitHub en utilisant `git push origin branch-name-here`.
10. Créez un pull request sur [QMK Firmware](https://github.com/qmk/qmk_firmware/pull/new/master).
11. Donnez un titre à votre pull request en utilisant une description courte des changements que vous avez fait et ajoutez le numéro de l'issue ou du bug associé avec votre changement. Les commentaires de PR devraient se faire en anglais de préférence. Par exemple, vous pouvez utiliser un titre tel que celui-là: "Added more log outputting to resolve #4352".
12. Dans la description du pull request, expliqez les changements que vous avez fait et tous les problèmes qui existent, selon vous, sur le pull request que vous avez fait. Vous pouvez aussi utiliser la description pour poser des questions au mainteneur. Il n'est pas nécessaire que votre pull request soit parfait (aucun pull request ne l'est), le reviewer sera là pour vous aider à résoudre les problèmes et l'améliorer!
13. Attendez que le pull request soit revu par un mainteneur.
14. Faites des changements au pull request si le mainteneur le recommande.
15. Célébrez votre succès une fois votre pull request fusionné!

# Conventions de codage

La grande majorité de notre style est plutôt simple à comprendre. Si vous connaissez C ou Python, vous ne devriez pas avoir trop de difficulté avec notre style.

* [Conventions de codage - C](coding_conventions_c.md)
* [Conventions de codage - Python](coding_conventions_python.md)

# Directives générales

Nous avons un certain nombre de type de changements dans QMK, chacun nécessitant un niveau de rigueur différent. Nous voulons que vous gardiez les directives suivantes en tête quel que soit le changement que vous êtes en train de faire.

* Séparez les PR dans des unités logiques. Par exemple, ne soumettez pas un PR qui couvre deux fonctionnalités spéarées, soumettez plutôt un PR pour chaque fonctionnalité.
* Vérifiez les espaces blancs non nécessaires avec `git diff --check` avant de commit.
* Assurez-vous que votre code compile.
  * Keymaps: Assurez-vous que `make keyboard:your_new_keymap` ne renvoie pas d'erreur.
  * Claviers: Assurez-vous que `make keyboard:all` ne renvoie pas d'erreur.
  * Core: Assurez-vous que `make all` ne renvoie pas d'erreur.
* Assurez-vous que le messages de commit sont compréhensible d'eux-même. Vous devriez écrire une description simple (pas plus de 70 caractères) sur la première ligne, suivi d'une ligne vide, suivi d'un détail de votre commit, si nécessaire. Exemple:

```
Adjust the fronzlebop for the kerpleplork

The kerpleplork was intermittently failing with error code 23. The root cause was the fronzlebop setting, which causes the kerpleplork to activate every N iterations.

Limited experimentation on the devices I have available shows that 7 is high enough to avoid confusing the kerpleplork, but I'd like to get some feedback from people with ARM devices to be sure.
```

## Documentation

La documentation est l'une des manière les plus simples de démarrer la contribution sur QMK. Il est simple de trouver des endroits où la documentation est fausse ou incomplète, et il est tout aussi simple de les corriger! Nous avons aussi grandement besoin de quelqu'un pour éditer notre documentation, donc si vous avez des compétences en édition mais que vous n'êtes pas sûr de savoir où aller, n'hésitez pas [demandez de l'aide](#where-can-i-go-for-help)!

Vous trouverez toute notre documentation dans le répertoire `qmk_firmware/docs`, ou si vous préférez utiliser des outils web, vous pouvez cliquer sur le bouton "Suggest An Edit" en haut de chaque page sur http://docs.qmk.fm/.

Lorsque vous donnez des exemples de code dans votre documentation, essayez de suivre les conventions de nommage utilisées ailleurs dnas la documentation. Par exemple, standardisez les enums en utilisant `my_layers` ou `my_keycodes` afin de garder une consistance:

```c
enum my_layers {
  _FIRST_LAYER,
  _SECOND_LAYER
};

enum my_keycodes {
  FIRST_LAYER = SAFE_RANGE,
  SECOND_LAYER
};
```

## Keymaps

Most first-time QMK contributors start with their personal keymaps. We try to keep keymap standards pretty casual (keymaps, after all, reflect the personality of their creators) but we do ask that you follow these guidelines to make it easier for others to discover and learn from your keymap.

* Write a `readme.md` using [the template](documentation_templates.md).
* All Keymap PR's are squashed, so if you care about how your commits are squashed you should do it yourself
* Do not lump features in with keymap PR's. Submit the feature first and then a second PR for the keymap.
* Do not include `Makefile`s in your keymap folder (they're no longer used)
* Update copyrights in file headers (look for `%YOUR_NAME%`)

## Keyboards

Keyboards are the raison d'être for QMK. Some keyboards are community maintained, while others are maintained by the people responsible for making a particular keyboard. The `readme.md` should tell you who maintains a particular keyboard. If you have questions relating to a particular keyboard you can [Open An Issue](https://github.com/qmk/qmk_firmware/issues) and tag the maintainer in your question.

We also ask that you follow these guidelines:

* Write a `readme.md` using [the template](documentation_templates.md).
* Keep the number of commits reasonable or we will squash your PR
* Do not lump core features in with new keyboards. Submit the feature first and then submit a separate PR for the keyboard.
* Name `.c`/`.h` file after the immediate parent folder, eg `/keyboards/<kb1>/<kb2>/<kb2>.[ch]`
* Do not include `Makefile`s in your keyboard folder (they're no longer used)
* Update copyrights in file headers (look for `%YOUR_NAME%`)

## Quantum/TMK Core

Before you put a lot of work into building your new feature you should make sure you are implementing it in the best way. You can get a basic understanding of QMK by reading [Understanding QMK](understanding_qmk.md), which will take you on a tour of the QMK program flow. From here you should talk to us to get a sense of the best way to implement your idea. There are two main ways to do this:

* [Chat on Discord](https://discord.gg/Uq7gcHh)
* [Open an Issue](https://github.com/qmk/qmk_firmware/issues/new)

Feature and Bug Fix PR's affect all keyboards. We are also in the process of restructuring QMK. For this reason it is especially important for significant changes to be discussed before implementation has happened. If you open a PR without talking to us first please be prepared to do some significant rework if your choices do not mesh well with our planned direction.

Here are some things to keep in mind when working on your feature or bug fix.

* **Disabled by default** - memory is a pretty limited on most chips QMK supports, and it's important that current keymaps aren't broken, so please allow your feature to be turned **on**, rather than being turned off. If you think it should be on by default, or reduces the size of the code, please talk with us about it.
* **Compile locally before submitting** - hopefully this one is obvious, but things need to compile! Our Travis system will catch any issues, but it's generally faster for you to compile a few keyboards locally instead of waiting for the results to come back.
* **Consider revisions and different chip-bases** - there are several keyboards that have revisions that allow for slightly different configurations, and even different chip-bases. Try to make a feature supported in ARM and AVR, or automatically disabled on platforms it doesn't work on.
* **Explain your feature** - Document it in `docs/`, either as a new file or as part of an existing file. If you don't document it other people won't be able to benefit from your hard work.

We also ask that you follow these guidelines:

* Keep the number of commits reasonable or we will squash your PR
* Do not lump keyboards or keymaps in with core changes. Submit your core changes first.
* Write [Unit Tests](unit_testing.md) for your feature
* Follow the style of the file you are editing. If the style is unclear or there are mixed styles you should conform to the [coding conventions](#coding-conventions) above.

## Refactoring

To maintain a clear vision of how things are laid out in QMK we try to plan out refactors in-depth and have a collaborator make the changes. If you have an idea for refactoring, or suggestions, [open an issue](https://github.com/qmk/qmk_firmware/issues), we'd love to talk about how QMK can be improved.

# What Does the Code of Conduct Mean for Me?

Our [Code of Conduct](https://github.com/qmk/qmk_firmware/blob/master/CODE_OF_CONDUCT.md) means that you are responsible for treating everyone on the project with respect and courtesy regardless of their identity. If you are the victim of any inappropriate behavior or comments as described in our Code of Conduct, we are here for you and will do the best to ensure that the abuser is reprimanded appropriately, per our code.
