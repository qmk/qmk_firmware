---
name: qa-local
description: Recette locale d'un changement. Lance la version feature des applications impactées à côté de la stack du développeur (autres ports, copie de la base), fait cocher les scénarios WHEN/THEN, écrit le rapport puis nettoie. À lancer par l'humain avec /qa-local.
argument-hint: <nom-du-changement> [--clean]
disable-model-invocation: true
---
<!-- généré par harness : ne pas éditer -->
# /qa-local : recette locale d'un changement

Changement : $ARGUMENTS (si vide : `npx -y @fission-ai/openspec@1.14.2 list --json`, propose le changement et attends la confirmation). Avec `--clean`, tu ne lances rien : tu fais l'étape 0, tu nettoies sans demander (étapes 7.1 à 7.4), puis tu t'arrêtes. S'il n'y a rien à nettoyer, dis-le et arrête-toi.

Dès que le changement est connu, affiche : 💡 Nomme la session : `/rename qa-<nom>`, pour la retrouver dans `claude --resume`.

Tu prépares une recette **à côté** de la stack du développeur. Tu ne touches jamais à sa stack ni à sa base. Ces commandes te sont interdites, quoi qu'il arrive :
- `make down`, `make restart`, `make clean`, `make reset-db`, `make dump-db`, `make refresh-db` ;
- `docker compose down`, `docker compose restart`, `docker stop`, `docker rm` sur un conteneur de la stack ;
- `kill` d'un processus que tu n'as pas lancé, sauf un reste de recette identifié à l'étape 0.

Ton shell garde son dossier courant d'une commande à l'autre : utilise toujours des chemins absolus.

## Placeholders

La même substitution s'applique dans `start`, `env`, `config`, `copy`, `run`, `drop` et `migrate` :
- `{port}` : le port de recette du service ; `{port:<service>}` : celui d'un autre service ;
- `{name}` : `local.database.name`, la base d'origine (jamais modifiée) ;
- `{copy}` = `{database}` = `{name}_qa` : la copie de recette ;
- `{file}` : le chemin absolu d'un script SQL (pour `migrate`, celui à produire).

Note :
- `<racine>`, la racine du projet ;
- pour chaque repo touché : `<chemin>`, tiré de `repos` et résolu depuis `<racine>` ;
- les worktrees de recette : `<racine>/.claude/worktrees/<nom>-qa` et `<chemin>/.claude/worktrees/<nom>-qa` ;
- `<rapports>` = `<racine>/.claude/qa-reports/` : rapport et scripts générés (ignoré par git).

## 0. Restes d'une recette précédente

Cherche ce qui reste d'une recette de `<nom>` :
- les worktrees `<nom>-qa` (`git worktree list`, dans le projet et dans chaque repo de `repos`) ;
- pour chaque port de recette, les processus en écoute (`lsof -nP -iTCP:{port} -sTCP:LISTEN -t`) et leur dossier courant (`lsof -a -p <pid> -d cwd -Fn`). Ne retiens que ceux dont le dossier courant est dans un worktree `<nom>-qa` ;
- la copie `{copy}`.

En mode `--clean`, fais d'abord le contrôle 1.1 (section `local`), puis nettoie sans demander (étapes 7.1 à 7.4) et arrête-toi.

Sinon, s'il y en a, montre-les et demande : « Je les nettoie avant de lancer la recette ? ». Si l'humain accepte, fais les étapes 7.1 à 7.4. Si l'humain refuse, arrête-toi : la recette ne peut pas tourner sur ces restes. Un processus dont le dossier courant n'est pas dans un worktree `<nom>-qa` n'est jamais un reste : tu n'y touches pas.

## 1. Contrôles ⛔

Si l'un échoue, arrête-toi et explique.

1. **Config** : `harness.config.json` a une section `local`, avec un service `projet` et un service pour chaque repo touché par le changement (groupes `[<repo>]` de `tasks.md`). Sinon, montre cet exemple et arrête-toi :

   ```json
   "local": {
     "envFile": "../dev-env/.env",
     "services": {
       "projet": {
         "start": "npx ng serve --port {port}",
         "port": 4300,
         "patch": ".claude/qa-local.patch",
         "config": { "file": "src/assets/config.json", "set": { "api.anomaly": "http://localhost:{port:backend}" } }
       },
       "backend": {
         "dir": "Anomaly-Service",
         "start": "dotnet run --no-launch-profile --project src/RestApi",
         "port": 51000,
         "env": { "ASPNETCORE_ENVIRONMENT": "Development", "ASPNETCORE_URLS": "http://localhost:{port}", "MYSQL_CONNECTSTRING": "Server=localhost;Port=3306;Database={database};Uid=root;Pwd=${MYSQL_ROOT_PASSWORD}" },
         "migrate": "dotnet ef migrations script --idempotent --project src/Infrastructure --startup-project src/RestApi -o {file}"
       }
     },
     "database": {
       "name": "anomaly",
       "copy": "docker exec mysql-db bash -c 'set -o pipefail; mysql -uroot -p\"$MYSQL_ROOT_PASSWORD\" -e \"CREATE DATABASE {copy}\" && mysqldump --single-transaction --routines --triggers -uroot -p\"$MYSQL_ROOT_PASSWORD\" {name} | mysql -uroot -p\"$MYSQL_ROOT_PASSWORD\" {copy}'",
       "run": "docker exec -i mysql-db bash -c 'mysql -uroot -p\"$MYSQL_ROOT_PASSWORD\" {copy}' < {file}",
       "drop": "docker exec mysql-db bash -c 'mysql -uroot -p\"$MYSQL_ROOT_PASSWORD\" -e \"DROP DATABASE IF EXISTS {copy}\"'"
     },
     "url": "http://localhost:4300"
   }
   ```
2. **Branches** : `git ls-remote --exit-code --heads origin feat/<nom>` réussit dans ce projet et dans chaque repo touché. Sinon, nomme le repo dont la branche manque.
3. **Ports** : pour chaque service lancé, `lsof -nP -iTCP:{port} -sTCP:LISTEN` ne renvoie rien. Si un port est pris, ne tue rien : donne le PID et la commande qui l'occupent.
4. **Environnement** : le chemin absolu de `envFile`, résolu depuis `<racine>`, existe.
5. **Base** : la commande `drop` résolue contient `{copy}` remplacé par `<name>_qa`, et jamais le nom d'origine seul. Sinon, arrête-toi : elle pourrait supprimer la vraie base.
6. **Patch** : pour chaque service lancé qui a une clé `patch`, le fichier existe (pour une liste, au moins un). Chaque `patch` est relatif à `<racine>`, même pour un repo lié : `.claude/` y est ignoré par git, et les réglages locaux ne finissent jamais dans un commit. Sinon, arrête-toi et explique comment le créer, depuis la racine du repo du service, sur une branche qui porte les réglages locaux : `git diff <base> -- <fichiers> > .claude/qa-local.patch` (pour un repo lié, écris-le dans `<racine>/.claude/`, avec un autre nom). Puis annonce, avant toute autre étape : « ⚠️ Recette avec les réglages locaux de `<patch>` », suivi de la liste des fichiers qu'il modifie (`git apply --stat <chemin absolu du patch>`).

On ne lance que le service `projet` et ceux des repos touchés seulement.

## 2. Worktrees

- Pour chaque repo : `cd <racine ou chemin> && git fetch origin`, puis `git worktree add --detach <worktree> origin/feat/<nom>`. Avec `localOnly` dans son `harness.config.json`, la branche locale `feat/<nom>` doit exister (sinon, arrête-toi et dis-le) : `git worktree add --detach <worktree> feat/<nom>`, puis, dans le worktree, `git merge --no-edit origin/feat/<nom>` pour récupérer les commits des collègues (conflit : montre-le et passe au nettoyage). La recette ne commite rien sur une branche.
- Dans chaque worktree, lance la commande `install` de son `harness.config.json` si elle est configurée.
- **Patch** : pour chaque service qui a une clé `patch`, lance `git apply <chemin absolu du patch>` à la racine de son worktree. `patch` peut être une liste : applique le premier qui passe `git apply --check`, et dis lequel. Si aucun ne passe, montre l'erreur et passe au nettoyage.

## 3. Données

Si `local.database` est configuré :
1. **Copie** : lance toujours `drop` (contrôlé à l'étape 1.5 ; elle cible la copie, avec `IF EXISTS`), puis `copy`. Si `copy` échoue, arrête-toi : une copie vide fausserait la recette.
2. Lis la section « Base de données » de `design.md`, dans le dossier du changement du worktree du projet : `openspec/changes/<nom>/`, ou `openspec/changes/archive/<date>-<nom>/` s'il est archivé. Si elle manque, ou n'a pas ses rubriques, alors que le changement touche la base, demande à l'humain quoi jouer.
3. **Schéma** : si la rubrique « Schéma » annonce une migration, lance `migrate` sans charger `envFile` : générer le script ne demande aucun secret. Exporte seulement les variables d'`env` du service, puis `cd <worktree>/<dir>`, avec `{file}` = `<rapports>/<nom>-<service>-migration.sql`. Ce fichier devient le premier script de l'étape 5. Si le service n'a pas de `migrate`, demande à l'humain comment créer le schéma.
4. **Variables** : pour chaque script de la rubrique « Scripts », copie-le dans `<rapports>/<nom>-<fichier>`, en remplaçant chaque placeholder de la rubrique « Variables » par sa valeur locale. L'original n'est jamais modifié. S'il reste un placeholder `#{…}#` sans valeur, demande-la à l'humain : ne joue jamais un script qui en contient encore un.
5. **Scripts** : pour chaque script à jouer, dans l'ordre (la migration d'abord, puis les copies de l'étape 3.4) :
   - si le script contient `USE `, ou le nom d'origine suivi d'un point (`{name}.` ou `` `{name}`. ``), arrête-toi et demande : il écrirait dans la vraie base ;
   - sinon, lance `run`, avec `{file}` = le chemin absolu de la migration générée, puis de chaque copie de l'étape 3.4, jamais d'un script d'origine. Juste avant, vérifie que la copie ne contient plus `#{`.
   - Si un script échoue (une chaîne de migrations différente, par exemple), montre l'erreur et passe au nettoyage : ne réaligne jamais la copie à la main. Indique que la base du développeur est sans doute trop ancienne, et qu'il peut la rafraîchir lui-même.

## 4. Services

1. **Config du front** : si un service a une clé `config`, modifie ce fichier dans son worktree seulement. Les clés de `set` sont des chemins pointés (`api.anomaly` désigne `api` → `anomaly`) ; une valeur qui n'est pas une chaîne (tableau, nombre, booléen) s'écrit telle quelle, en JSON. Ne commite rien.
2. **Lancement** : chaque `start` en arrière-plan (outil Bash, `run_in_background`), avec cette forme exacte :

   ```
   set -a; . <chemin absolu de envFile>; set +a; export CLE="valeur" …; cd <worktree>/<dir> && <start>
   ```

   - Chaque variable d'`env` est exportée entre guillemets doubles, après le chargement d'`envFile` : elle prime sur lui, et le `;` d'une chaîne de connexion ne coupe pas la commande.
   - Pour un projet .NET, `dotnet run --no-launch-profile` : sinon `launchSettings.json` impose son port et sa chaîne de connexion, celle de la vraie base.
   - Limite : `envFile` est chargé comme un script shell. Une valeur avec `$`, espace, `&`, `(` ou `!` doit y être entre guillemets.
   - Note l'identifiant de chaque tâche.
3. **Attente** : pour chaque service, `curl --retry 270 --retry-max-time 540 --retry-connrefused --retry-delay 2 -s -o /dev/null http://localhost:{port}`, avec un `timeout` Bash de 600000 ms. Une réponse HTTP, même 404, veut dire que le service tourne. Si sa tâche s'est arrêtée entre-temps (erreur de compilation), montre la fin de sa sortie et passe au nettoyage.

## 5. Recette

1. Donne l'URL `local.url`. Rappelle que le port de recette du front doit être autorisé dans Keycloak : URI de redirection et Web Origins du client.
2. Liste les scénarios du changement, numérotés : chaque `#### Scenario` des specs delta (même dossier qu'à l'étape 3.2), avec ses WHEN/THEN. Ajoute un scénario par image de `mockups/` (même dossier) : « Mise en page conforme à `<image>` », avec le chemin absolu de l'image pour que l'humain la compare à l'écran.
3. Fais cocher le résultat, OK ou KO, avec `AskUserQuestion` et `multiSelect: true` : 4 scénarios par question, 4 questions par appel, autant d'appels que nécessaire. Chaque option est un scénario (`<n>. <titre court>`). L'humain coche les scénarios **OK** ; un scénario non coché est KO. Un dernier groupe d'un seul scénario devient une question à deux options, « OK » et « KO ».
4. En un seul message, demande un commentaire pour chaque KO.
5. Pour un KO, propose de regarder les logs du service concerné (sortie de sa tâche) avant de conclure.

## 6. Résultat

1. Écris le rapport dans `<rapports>/<nom>.md`, soit `.claude/qa-reports/<nom>.md` (il remplace le précédent) : date, SHA testé de chaque repo, patchs appliqués, tableau des scénarios (OK ou KO, commentaire), scripts joués.
2. Affiche-le, puis donne, pour la PR de `feat/<nom>` de chaque repo touché, la commande à copier : `gh pr comment <url> --body-file <chemin absolu du rapport>`. Ne publie jamais le rapport toi-même.
3. Tout OK : dis que la recette locale est validée. Un KO ou plus : résume-les, propose `/fix <nom>` pour les corriger, puis une nouvelle recette avec `/qa-local <nom>`.

## 7. Nettoyage

Demande : « Je nettoie l'environnement de recette, ou je le garde (pour tester un correctif) ? ». Sans réponse claire, nettoie. Si l'humain le garde, rappelle qu'il le nettoiera avec `/qa-local <nom> --clean`.

Sinon, toujours, même si l'humain abandonne ou si un service ne démarre pas :
1. Arrête chaque service que tu as lancé (TaskStop sur ses identifiants), et les restes repérés à l'étape 0 (`kill <pid>`), eux seulement.
2. Avant chaque `drop`, refais le contrôle de l'étape 1.5, dans tous les modes. Lance `drop` : il supprime la copie, seulement si son nom finit par `_qa`.
3. Pour chaque worktree de recette, lance `git status --porcelain` dans le worktree. S'il y a des modifications autres que les fichiers du patch et de `config` (un correctif fait pendant la recette, par exemple), montre-les et demande avant de supprimer : elles seraient perdues. Puis `cd <racine ou chemin> && git worktree remove --force <worktree>` (le garde-fou bloque la restauration de tout le worktree et le nettoyage forcé). Ne supprime qu'un chemin qui finit par `/<nom>-qa`, avec `<nom>` non vide.
4. Refais la recherche de processus de l'étape 0 sur chaque port de recette. `TaskStop` peut laisser un processus enfant (le binaire lancé par `dotnet run`, le `node` lancé par `npx`) : arrête ceux dont le dossier courant est dans un worktree `<nom>-qa`, puis vérifie que les ports de recette sont libres. Sinon, donne le PID et la commande qui occupent encore le port.
5. Rappelle que la stack du développeur n'a pas été touchée.
