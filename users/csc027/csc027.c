#include "csc027.h"

static const char* git_macros[] = {
    // Make sure that the macro strings match the order they are declared
    // in the custom_keycodes enum.
    "git add ",
    "git branch ",
    "git checkout ",
    "git cherry-pick ",
    "git commit -m \"\""SS_TAP(X_LEFT),
    "git diff ",
    "git fetch ",
    "git grep ",
    "git log --decorate --oneline --graph ",
    "git init ",
    "git mv ",
    "git merge ",
    "git push ",
    "git pull ",
    "git rebase ",
    "git remote ",
    "git reset ",
    "git show ",
    "git stash ",
    "git status ",
    "git tag ",
    SS_LCTL(SS_LALT(SS_TAP(X_HOME)))"\t ",
    SS_LCTL(SS_LALT(SS_TAP(X_HOME)))"\t\t\t ",
    SS_LCTL(SS_LALT(SS_TAP(X_HOME)))SS_LALT("\t")
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case LOWER:
            if(record->event.pressed) {
                layer_on(_LW);
                update_tri_layer(_LW, _RS, _MS);
            } else {
                layer_off(_LW);
                update_tri_layer(_LW, _RS, _MS);
            }
            return false;
        case RAISE:
            if(record->event.pressed) {
                layer_on(_RS);
                update_tri_layer(_LW, _RS, _MS);
            } else {
                layer_off(_RS);
                update_tri_layer(_LW, _RS, _MS);
            }
            return false;
        case GIT_ADD...MC_ATRD:
            if(record->event.pressed) {
                // The calculation here is to make sure that the custom keycode
                // aligns with the git_macros array.
                send_string(git_macros[keycode - GIT_ADD]);
                return true;
            }
            return false;
        default:
            return true;
    }
}
