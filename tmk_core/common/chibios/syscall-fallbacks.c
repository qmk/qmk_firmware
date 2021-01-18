/* Copyright 2021 Nick Brassel, QMK
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

#include <sys/stat.h>
#include <sys/types.h>

#pragma GCC diagnostic ignored "-Wmissing-prototypes"

__attribute__((weak, used)) int _read_r(struct _reent *r, int file, char *ptr, int len) {
    (void)r;
    (void)file;
    (void)ptr;
    (void)len;
    return -1;
}

__attribute__((weak, used)) int _lseek_r(struct _reent *r, int file, int ptr, int dir) {
    (void)r;
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}

__attribute__((weak, used)) int _write_r(struct _reent *r, int file, char *ptr, int len) {
    (void)r;
    (void)file;
    (void)ptr;
    return len;
}

__attribute__((weak, used)) int _close_r(struct _reent *r, int file) {
    (void)r;
    (void)file;
    return 0;
}

__attribute__((weak, used)) caddr_t _sbrk_r(struct _reent *r, int incr) {
    (void)r;
    (void)incr;
    return (caddr_t)-1;
}

__attribute__((weak, used)) int _fstat_r(struct _reent *r, int file, struct stat *st) {
    (void)r;
    (void)file;
    (void)st;
    return 0;
}

__attribute__((weak, used)) int _isatty_r(struct _reent *r, int fd) {
    (void)r;
    (void)fd;
    return 1;
}

__attribute__((weak, used)) void _fini(void) { return; }

__attribute__((weak, used)) pid_t _getpid(void) { return 1; }

__attribute__((weak, noreturn)) void _exit(int i) {
    (void)i;
    while (1)
        ;
}

__attribute__((weak)) void _kill(void) {}

__attribute__((weak)) void *__dso_handle;

void __cxa_pure_virtual(void);

__attribute__((weak)) void __cxa_pure_virtual() {
    while (1)
        ;
}

#pragma GCC diagnostic pop
