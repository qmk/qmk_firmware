<div dir="rtl" markdown="1">
# קושחה עבור Quantum Mechanical Keyboard

[![גירסה נוכחית](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![ערוץ דיסקורד](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![מצב מסמכים](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![תומכי GitHub](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![מזלגות GitHub](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## מה היא קושחת QMK?

QMK (*Quantum Mechanical Keyboard*) היא קהילת קוד פתוח (open source) שמתחזקת את קושחת QMK, QMK Toolbox, qmk.fm, והמסמכים המתאימים. קושחת QMK היא קושחה עבור מקלדות המבוססת על [tmk\_keyboard](https://github.com/tmk/tmk_keyboard) עם כמה תוספות עבור בקרי Atmel AVR ובאופן ספציפי יותר - [מוצרי OLKB](https://olkb.com), מקלדת [ErgoDox EZ](https://www.ergodox-ez.com), וגם [מוצרי Clueboard](https://clueboard.co/). בנוסף, הקושחה עברה פורט עבור שבבי ARM באמצעות ChibiOS. ניתן להשתמש בה על מנת להפעיל את מקלדות ה PCB המקוסטמות שלך.

## איך להשיג אותה

אם אתם מתכננים לתרום מיפוי מקשים, מקלדת או יכולת ל QMK, הדבר הקל ביותר הוא  [לעשות פורק לריפו בGitHub](https://github.com/qmk/qmk_firmware#fork-destination-box), ולעשות קלון לריפו בסביבה המקומית ושם לבצע את השינויים שלכם, לדחוף אותם ולפתוח  [Pull Request](https://github.com/qmk/qmk_firmware/pulls) מהפורק שלך.

אחרת, אפשר להוריד את הקושחה באופן ישיר ([zip](https://github.com/qmk/qmk_firmware/zipball/master), [tar](https://github.com/qmk/qmk_firmware/tarball/master)), או לשכפל אותה באמצעות git (`git@github.com:qmk/qmk_firmware.git`), או https (`https://github.com/qmk/qmk_firmware.git`).

## איך לקמפל

לפני שתצליחו לקמפל, תדרשו [להתקין סביבה](he-il/getting_started_build_tools.md) עבור פיתוח AVR ו/או ARM. ברגע שהדבר בוצע, תוכלו להריץ פקודת `make` כדי לבנות מקלדת ומיפוי עם התחביר הבא: 

    make planck/rev4:default

כך תוכלו לבנות את גרסא `rev4` של ה `planck` עם מיפוי ברירת המחדל (`default`). לא כל המקלדות בעלות גרסאות (נקרא גם תת-פרוייקט או תיקייה), במקרה כזה, אפשר להריץ את הפקודה הבאה: 

    make preonic:default

## איך להתאים

לQMK יש המון [יכולות](he-il/features.md) שאפשר לנווט בהן, וכמות נכבדת של [תיעוד ודוקומנטציה](https://docs.qmk.fm) בה אפשר לנבור. רוב הפיצ׳רים באים לידי ביטוי על ידי שינוי  [מיפוי המקלדת](he-il/keymap.md) ושינוי  [קודי המקשים](he-il/keycodes.md).
</div>
