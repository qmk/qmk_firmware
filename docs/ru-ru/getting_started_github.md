# Как использовать GitHub с QMK

GitHub может показаться несколько сложным для тех, кто никогда с ним не работал. В данном руководстве будет разобран каждый шаг создания форка, клонирования и отправки пулреквеста в QMK.

?> В этом руководстве предполагается, что вы в какой-то степени знакомы с работой в командной строке, и в вашей системе установлен git.

Откройте [страницу QMK на GitHub] (https://github.com/qmk/qmk_firmware), и в правом верхнем углу вы увидите кнопку с надписью "Fork":

![Fork on GitHub](https://i.imgur.com/8Toomz4.jpg)

Если вы состоите в какой-либо организации, вам нужно выбрать учетную запись, к которой будет привязан форк. В большинстве случаев это будет личной аккаунт. Как только ваш форк будет завершен (иногда это занимает немного времени), нажмите кнопку "Clone or Download":
![Download from GitHub](https://i.imgur.com/N1NYcSz.jpg)

И обязательно выберите "HTTPS", затем выделите ссылку и скопируйте ее:

![HTTPS link](https://i.imgur.com/eGO0ohO.jpg)

Теперь введите `git clone --recurse-submodules ` в командную строку, а затем вставьте ссылку:

```
user@computer:~$ git clone --recurse-submodules https://github.com/whoeveryouare/qmk_firmware.git
Cloning into 'qmk_firmware'...
remote: Enumerating objects: 9, done.
remote: Counting objects: 100% (9/9), done.
remote: Compressing objects: 100% (5/5), done.
remote: Total 183883 (delta 5), reused 4 (delta 4), pack-reused 183874
Receiving objects: 100% (183883/183883), 132.90 MiB | 9.57 MiB/s, done.
Resolving deltas: 100% (119972/119972), done.
...
Submodule path 'lib/chibios': checked out '587968d6cbc2b0e1c7147540872f2a67e59ca18b'
Submodule path 'lib/chibios-contrib': checked out 'ede48346eee4b8d6847c19bc01420bee76a5e486'
Submodule path 'lib/googletest': checked out 'ec44c6c1675c25b9827aacd08c02433cccde7780'
Submodule path 'lib/lufa': checked out 'ce10f7642b0459e409839b23cc91498945119b4d'
```

Теперь у вас есть форк QMK на вашем локальном компьютере, и вы можете добавить свою раскладку, скомпилировать ее и прошить ей свою клавиатуру. Как только вы будете довольны своими изменениями, есть возможность добавить, зафиксировать их и сделать коммит в свой форк следующим образом:

```
user@computer:~$ git add .
user@computer:~$ git commit -m "adding my keymap"
[master cccb1608] adding my keymap
 1 file changed, 1 insertion(+)
 create mode 100644 keyboards/planck/keymaps/mine/keymap.c
user@computer:~$ git push
Counting objects: 1, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (1/1), done.
Writing objects: 100% (1/1), 1.64 KiB | 0 bytes/s, done.
Total 1 (delta 1), reused 0 (delta 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local objects.
To https://github.com/whoeveryouare/qmk_firmware.git
 + 20043e64...7da94ac5 master -> master
```

Ваши изменения теперь существуют в вашем форке на GitHub - если вернуться туда (`https://github.com/<whoeveryouare>/qmk_firmware`), вы сможете создать "New Pull Request" нажатием на кнопку:

![New Pull Request](https://i.imgur.com/DxMHpJ8.jpg)

Здесь вы сможете увидеть, какие именно изменения были внесены, - если все выглядит хорошо, вы можете завершить его, нажав "Create Pull Request":

![Create Pull Request](https://i.imgur.com/Ojydlaj.jpg)

После отправки мы можем расспросить вас о ваших изменениях, попросить внести корректировки и в конечном итоге принять их! Спасибо за ваш вклад в QMK :)
