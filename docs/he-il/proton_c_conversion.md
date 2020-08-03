<div dir="rtl" markdown="1">
# המרה של לוח להשתמש ב-Proton C

אם לוח נתמך ב-QMK משתמש בלוח Pro Micro (או כל לוח נתמך) ואתם רוצים להשתמש ב-Proton C, ניתן לייצר את החומרה ע"י הוספה של הפקודה `CONVERT_TO_PROTON_C=yes` (או `CTPC=yes`) לפקודת make, כמו כאן:
<div dir="ltr" markdown="1">

```
    make 40percentclub/mf68:default CTPC=yes
```

</div>
ניתן להוסיף את אותו ארגומנט לקובץ `rules.mk` במיפוי המקשים שלכם, שתיצור את אותה התוצאה.

הדבר חושף את דגל `CONVERT_TO_PROTON_C` שניתן להשתמש בו בקוד שלכם באמצעות פקודת `#ifdef`, כמו כאן:
<div dir="ltr" markdown="1">

```
    #ifdef CONVERT_TO_PROTON_C
        // Proton C code
    #else
        // Pro Micro code
    #endif
```

</div>
לפני שתצליחו לקמפל, יכול להיות שתקבלו שגיאות שונות לגבי `PORTB/DDRB`, וכו' שלא הוגדרו, אם כך, תצטרכו להמיר את קודי המקלדת להשתמש ב - [בקרי GPIO](internals_gpio_control.md) שיעבדו עבור ARM וגם AVR. הדבר לא אמור להשפיע על הבילדים של AVR בכלל.

ל-Proton C יש רק מנורת LED אחת על הלוח (C13), וכברירת מחדל, TXLED (D5) ממופה אליו. אם תרצו במקום, למפות אליו את  RXLED (B0), הוסיפו את השורה הבא לקובץ `config.h`:
<div dir="ltr"  markdown="1">

```
    #define CONVERT_TO_PROTON_C_RXLED
```

</div>
</div>
