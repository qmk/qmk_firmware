<div dir="rtl" markdown="1">
# קודי מקלדת Quantum

קודי מקלדת Quantum מאפשרים התאמה נוחה יותר של מיפוי המקשים שלך מעבר למה שהבסיסי מאפשר, ללא צורך בהגדרת של פעולות מותאמות אישית.

כל קודי המקלדת בתוך quantum הם מספרים בין `0x0000` ֿֿֿ ל-`0xFFFF`. בתוך הקובץ `keymap.c` זה עלול להראות כאילו יש לך פונקציות ומקרים יחודיים נוספים, אבל בסופו של דבר הקדם-מעבד של שפת C יתרגם אלה לתוך מספר יחיד בין 4 בתים. QMK שמרה את מרחב הכתובות בין `0x0000` עד ל- `0x00FF` עבור קודי מקשים סטנדרטיים. קודי מקשים אלה, כגון `KC_A`, `KC_1`, ו- `KC_LCTL`, אשר מתארים מקשים בסיסיים מוגדרים בתוך USB HID specification.

בעמודו זה יש לנו את קודי המקשים מתועדים בין `0x00FF` ֿֿ ל- `0xFFFF` אשר משומשים בשביל לממש יכולות מתקדמות של quantum. אם תגדירו קודי מקשים משלכם, הם יתווספו לתוך המרחב הזה גם כן.

## קודי מקשים של QMK
<div dir="ltr"  markdown="1">

```
|Key            |Aliases    |Description                                                          |
|---------------|-----------|---------------------------------------------------------------------|
|`RESET`        |           |Put the keyboard into DFU mode for flashing                          |
|`DEBUG`        |           |Toggle debug mode                                                    |
|`EEPROM_RESET` |`EEP_RST`  |Resets EEPROM state by reinitializing it                             |
|`KC_GESC`      |`GRAVE_ESC`|Escape when tapped, <code>&#96;</code> when pressed with Shift or GUI|
|`KC_LSPO`      |           |Left Shift when held, `(` when tapped                                |
|`KC_RSPC`      |           |Right Shift when held, `)` when tapped                               |
|`KC_LCPO`      |           |Left Control when held, `(` when tapped                              |
|`KC_RCPC`      |           |Right Control when held, `)` when tapped                             |
|`KC_LAPO`      |           |Left Alt when held, `(` when tapped                                  |
|`KC_RAPC`      |           |Right Alt when held, `)` when tapped                                 |
|`KC_SFTENT`    |           |Right Shift when held, Enter when tapped                             |
|`KC_LEAD`      |           |The [Leader key](feature_leader_key.md)                              |
|`KC_LOCK`      |           |The [Lock key](feature_key_lock.md)                                  |
|`FUNC(n)`      |`F(n)`     |Call `fn_action(n)` (deprecated)                                     |
|`M(n)`         |           |Call macro `n`                                                       |
|`MACROTAP(n)`  |           |Macro-tap `n` idk FIXME                                              |
```

</div>
</div>
