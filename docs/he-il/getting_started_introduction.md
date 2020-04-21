<div dir="rtl" markdown="1">
# מבוא

עמוד זה מנסה להסביר את המידע הבסיסי אותו תדרשו לדעת כדי לעבוד עם פרוייקט QMK. הוא מניח שאתם יודעים איך לנווט בסביבת Unix Shell, אבל לא מניח שאתם מכירים את שפת C או קומפילציה באמצעות make.

## מבנה QMK בסיסי

QMK הוא פורק של הפרוייקט [tmk_keyboard](https://github.com/tmk/tmk_keyboard) של [Jun Wako](https://github.com/tmk). קוד הTMK המקורי, עם התאמות, יכול להמצא בתיקיית `tmk_core`. התוספות של QMK לפרוייקט יכולות להמצא בתיקיית `quantum`. פרוייקטי מקלדות יכולות להמצא בתיקיות `handwired` ו- `keyboard`.

### מבנה אחסון המשתמש

בתוך תיקיית `users` יש תיקייה לכל משתמש. זה המקום למשתמשים להוסיף קוד שהם רוצים להשתמש בו במקלדות שונות. מומלץ לעיין במסמך [תכונות אחסון המשתמש](feature_userspace.md) לקבלת מידע נוסף.

### מבנה פרוייקט המקלדת

בתוך תיקיית `keyboards`, תת התיקייה `handwired` ותת התיקיות של היצרן והמוכר, לדוגמה `clueboard` היא תיקייה לכל פרוייקט מקלדת - `qmk_firmware/keyboards/clueboard/2x1800` בתוך התיקייה הזאת תמצאו את המבנה הבא:


* `keymaps/`: מיפויי מקשים שונים היכולים להבנות
* `rules.mk`: קובץ המגדיר את הגדרות ברירת המחדל של `make`. נא לא לערוך את הקובץ ישירות, במקום זאת, השתמשו בקובץ מיפוי המקשים ספציפי `rules.mk`.
* `config.h`: הקובץ מכיל הגדרות לזמן הקומפילציה. נא לא לערוך את הקובץ ישירות אלא להשתמש בקובץ `config.h` לכל מיפויי מקשים.
* `info.json`: הקובץ מכיל הגדרות פריסה עבור QMK Configurator. צפו ב [תמיכת Configurator](reference_configurator_support.md) למידע נוסף.
* `readme.md`: סקירה כללית של המקלדת.
* `<keyboardName>.h`: הקובץ בו פריסת המקלדת מוגדרת אל מול מטריצת המתגים של המקלדת.
* `<keyboardName>.c`: הקובץ בו ניתן למצוא קוד מותאם למקלדת.

למידע נוסף - אנא הכנסו ל [QMK](hardware_keyboard_guidelines.md).
For more information on project structure, see [QMK מדריך למקלדת](hardware_keyboard_guidelines.md).

### מבנה מפיוי המקשים

בכל ספריית מיפוי מקשים, הקבצים הבאים עלולים להמצא. רק הקובץ `keymap.c` הוא חובה, אם השאר לא נמצאים, אפשרויות ברירת המחדל יבחרו.
In every keymap folder, the following files may be found. Only `keymap.c` is required, and if the rest of the files are not found the default options will be chosen.

* `config.h`: ההגדרות השונות עבור מיפוי המקשים.
* `keymap.c`: כל הקודים של מיפוי המקשים, קובץ חובה
* `rules.mk`: אילו יכולות של QMK מאופשרות.
* `readme.md`: הסבר על מיפוי המקשים, איך אחרים ישתמשו בו והסבר על היכולות. נא להעלות תמונות לשירותים כמו imgur.

# קובץ `config.h` 

לקובץ `config.h` יש 3 מיקומים אפשריים:

* keyboard (`/keyboards/<keyboard>/config.h`)
* userspace (`/users/<user>/config.h`)
* keymap (`/keyboards/<keyboard>/keymaps/<keymap>/config.h`)

מערכת הבילד אוטומטית בוחרת את קובץ ההגדרות לפי הסדר הנ״ל. אם רוצים לדרוס הגדרה מסויימת שהוגדרה בקובץ `config.h` קודם, ראשית תצטרכו להשתמש בקוד מוכן עבור ההגדרות שאתם רוצים לשנות.

<div dir="ltr"  markdown="1">

```
#pragma once
```

</div>

כדי לדרוס הגדרות מקובץ `config.h` קודם, אתם מוכרחים להשתמש בפקודת `#undef` ואז שוב `#define`.

דוגמה לקוד כזה נראית כך:
<div dir="ltr"  markdown="1">

```
#pragma once

// overrides go here!
#undef MY_SETTING
#define MY_SETTING 4
```

</div>
</div>
