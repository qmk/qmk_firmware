<div dir="rtl" markdown="1">
# איך להשתמש ב-GitHub עם QMK

GitHub עלול להיות קצת טריקי למי שלא מכיר את העבודה איתו - מדריך זה ילווה אתכם שלב אחר שלב דרך ביצוע פעולות fork, clone ו-pull request עם QMK.

?> מדריך זה מניח שאתם מרגישים בנוח עם הרצה של פקודות בסביבת command line (שורת הפקודה) ו-git מותקן במערכת שלכם.

התחילו ב- [עמוד של QMK ב-GitHub](https://github.com/qmk/qmk_firmware), ותצמאו כפתור בחלק העליון מימין עם התיכוב "Fork":

![Fork ב-GitHub](https://i.imgur.com/8Toomz4.jpg)

אם אתם חלק מארגון, תצטרכו לבחור לאיזה חשבון לבצע פעולת fork. ברוב המבקרים, תרצו לבצע fork לתוך החשבון הפרטי שלכם. ברגע שה-fork הסתיים (לפעמים זה יכול לקחת קצת זמן) הקליקו על כפתור ה-"Clone or Download":

![הורדה מ-GitHub](https://i.imgur.com/N1NYcSz.jpg)

תוודאו שאתם בוחרים באופצייה של  "HTTPS", בחרו את הקישור והעתיקו אותו:

![קישור HTTPS](https://i.imgur.com/eGO0ohO.jpg)

מכאן והלאה, הקיש `git clone --recurse-submodules ` בשורת הפקודה והדביקו את הלינק שלכם:

<div dir="ltr" markdown="1">

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
Submodule path 'lib/ugfx': checked out '3e97b74e03c93631cdd3ddb2ce43b963fdce19b2'
```

</div>

כעת, יש לכם את ה-fork של QMK על המכונה המקומית שלכם ואתם יכולים להוסיף את מיפויי המקשים שלכם, לקמפל את הפרוייקט ולצרוב אותו על הלוח שלכם. כשאתם שלמים עם השינוי שעשיתם, תוכלו להוסיף, לבצע פעולת commit ולדחוף את השינויים ל-fork שלכם באופן הבא:

<div dir="ltr" markdown="1">

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

</div>

השינויים שלכם יופיעו ב-fork שלכם ב-GitHub - אם תחזרו לשם  (`https://github.com/<whoeveryouare>/qmk_firmware`), תוכלו ליצור "Pull Request חדש" ע״י הקשה על הכפתור הבא:

![Pull Request חדש](https://i.imgur.com/DxMHpJ8.jpg)

כאן תוכלו לראות בדיוק למה עשיתם commit - אם הכל נראה תקין, תוכלו להשלים את הפעולה ע״י הקשה על  "Create Pull Request":

![צרו Pull Request](https://i.imgur.com/Ojydlaj.jpg)

אחרי שהגשתם, אנו עלולים לפנות אליכם לגבי השינויים שהצעתם, נבקש שתבצעו שינויים ובסופו של דבר נקבל את השינויים! תודה שתרמתם לפרוייקט QMK :)
</div>
