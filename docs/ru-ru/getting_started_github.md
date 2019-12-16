# Как использовать GitHub с QMK

GitHub может показаться несколько сложным для тех, кто никогда с ним не работал. В данном руководстве будет разобран каждый шаг создания форка, клонирования и отправки пулреквеста в QMK.

?> В этом руководстве предполагается, что вы в какой-то степени знакомы с работой в командной строке, и в вашей системе установлен git.

Откройте [страницу QMK на GitHub] (https://github.com/qmk/qmk_firmware), и в правом верхнем углу вы увидите кнопку с надписью "Fork":

![Fork on Github](http://i.imgur.com/8Toomz4.jpg)

Если вы состоите в какой-либо организации, вам нужно выбрать учетную запись, к которой будет привязан форк. В большинстве случаев это будет личной аккаунт. Как только ваш форк будет завершен (иногда это занимает немного времени), нажмите кнопку "Clone or Download":
![Download from Github](http://i.imgur.com/N1NYcSz.jpg)

И обязательно выберите "HTTPS", затем выделите ссылку и скопируйте ее:

![HTTPS link](http://i.imgur.com/eGO0ohO.jpg)

Теперь введите `git clone` в командную строку, а затем вставьте ссылку:

```
user@computer:~$ git clone https://github.com/whoeveryouare/qmk_firmware.git
Cloning into 'qmk_firmware'...
remote: Counting objects: 46625, done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 46625 (delta 0), reused 0 (delta 0), pack-reused 46623
Receiving objects: 100% (46625/46625), 84.47 MiB | 3.14 MiB/s, done.
Resolving deltas: 100% (29362/29362), done.
Checking out files: 100% (2799/2799), done.
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

![New Pull Request](http://i.imgur.com/DxMHpJ8.jpg)

Здесь вы сможете увидеть, какие именно изменения были внесены, - если все выглядит хорошо, вы можете завершить его, нажав "Create Pull Request":

![Create Pull Request](http://i.imgur.com/Ojydlaj.jpg)

После отправки мы можем расспросить вас о ваших изменениях, попросить внести корректировки и в конечном итоге принять их! Спасибо за ваш вклад в QMK :)
