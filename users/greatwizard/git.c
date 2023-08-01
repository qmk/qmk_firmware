/* Copyright 2020 Guillaume Gérard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "git.h"

bool process_record_git(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GIT_ADD:
            if (record->event.pressed) {
                SEND_STRING("git add ");
            }
            return false;
        case GIT_BRANCH:
            if (record->event.pressed) {
                SEND_STRING("git branch ");
            }
            return false;
        case GIT_CHECKOUT:
            if (record->event.pressed) {
                SEND_STRING("git checkout ");
            }
            return false;
        case GIT_CHERRYPICK:
            if (record->event.pressed) {
                SEND_STRING("git cherry-pick ");
            }
            return false;
        case GIT_COMMIT:
            if (record->event.pressed) {
                SEND_STRING("git commit -m \"\""SS_TAP(X_LEFT));
            }
            return false;
        case GIT_DIFF:
            if (record->event.pressed) {
                SEND_STRING("git diff ");
            }
            return false;
        case GIT_FETCH:
            if (record->event.pressed) {
                SEND_STRING("git fetch ");
            }
            return false;
        case GIT_GREP:
            if (record->event.pressed) {
                SEND_STRING("git grep ");
            }
            return false;
        case GIT_LOG:
            if (record->event.pressed) {
                SEND_STRING("git log --decorate --oneline --graph ");
            }
            return false;
        case GIT_INIT:
            if (record->event.pressed) {
                SEND_STRING("git init ");
            }
            return false;
        case GIT_MV:
            if (record->event.pressed) {
                SEND_STRING("git mv ");
            }
            return false;
        case GIT_MERGE:
            if (record->event.pressed) {
                SEND_STRING("git merge ");
            }
            return false;
        case GIT_PUSH:
            if (record->event.pressed) {
                SEND_STRING("git push ");
            }
            return false;
        case GIT_PULL:
            if (record->event.pressed) {
                SEND_STRING("git pull ");
            }
            return false;
        case GIT_REBASE:
            if (record->event.pressed) {
                SEND_STRING("git rebase ");
            }
            return false;
        case GIT_REMOTE:
            if (record->event.pressed) {
                SEND_STRING("git remote ");
            }
            return false;
        case GIT_RESET:
            if (record->event.pressed) {
                SEND_STRING("git reset ");
            }
            return false;
        case GIT_SHOW:
            if (record->event.pressed) {
                SEND_STRING("git show ");
            }
            return false;
        case GIT_STASH:
            if (record->event.pressed) {
                SEND_STRING("git stash ");
            }
            return false;
        case GIT_STATUS:
            if (record->event.pressed) {
                SEND_STRING("git status ");
            }
            return false;
        case GIT_TAG:
            if (record->event.pressed) {
                SEND_STRING("git tag ");
            }
            return false;
    }
    return true;
}
