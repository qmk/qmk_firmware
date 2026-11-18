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

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

/* To compile the ChibiOS syscall stubs with picolibc
 * the _reent struct has to be defined. */
#if defined(USE_PICOLIBC)
#    include <stdint.h>
#    if __has_include(<picotls.h>)
#        include <picotls.h>
#    endif
struct _reent;
struct timeval;
#    if defined(__arm__) && defined(__THREAD_LOCAL_STORAGE)
/* ChibiOS links with -nostartfiles and does not invoke picocrt's TLS setup.
 * Point `__tls` at the TLS block reserved by `platforms/chibios/picolibc.ld`
 * and initialize it before `main()`. */
extern char __tls_space[];
extern char __tls_space_size[];
extern char __arm32_tls_tp[];

__attribute__((used)) void *__tls = __arm32_tls_tp;

__attribute__((constructor, used)) static void init_picolibc_tls(void) {
    if ((uintptr_t)__tls_space_size != 0) {
        _init_tls(__tls_space);
    }
}
#    endif
#endif

#pragma GCC diagnostic ignored "-Wmissing-prototypes"

__attribute__((weak, used)) int _open_r(struct _reent *r, const char *path, int flag, int m) {
    __errno_r(r) = ENOENT;
    return -1;
}

__attribute__((weak, used)) int _lseek_r(struct _reent *r, int file, int ptr, int dir) {
    __errno_r(r) = EBADF;
    return -1;
}

__attribute__((weak, used)) int _read_r(struct _reent *r, int file, char *ptr, int len) {
    __errno_r(r) = EBADF;
    return -1;
}

__attribute__((weak, used)) int _write_r(struct _reent *r, int file, char *ptr, int len) {
    __errno_r(r) = EBADF;
    return -1;
}

__attribute__((weak, used)) int _close_r(struct _reent *r, int file) {
    __errno_r(r) = EBADF;
    return -1;
}

__attribute__((weak, used)) int _link_r(struct _reent *r, const char *oldpath, const char *newpath) {
    __errno_r(r) = EPERM;
    return -1;
}

__attribute__((weak, used)) int _unlink_r(struct _reent *r, const char *path) {
    __errno_r(r) = EPERM;
    return -1;
}

__attribute__((weak, used)) clock_t _times_r(struct _reent *r, void *t) {
    __errno_r(r) = EFAULT;
    return -1;
}

__attribute__((weak, used)) int _fstat_r(struct _reent *r, int file, struct stat *st) {
    __errno_r(r) = EBADF;
    return -1;
}

__attribute__((weak, used)) int _isatty_r(struct _reent *r, int fd) {
    __errno_r(r) = EBADF;
    return 0;
}

__attribute__((weak, used)) caddr_t _sbrk_r(struct _reent *r, int incr) {
    __errno_r(r) = ENOMEM;
    return (caddr_t)-1;
}

__attribute__((weak, used)) int _kill(int pid, int sig) {
    errno = EPERM;
    return -1;
}

__attribute__((weak, used)) pid_t _getpid(void) {
    return 1;
}

__attribute__((weak, used)) void _fini(void) {
    return;
}

__attribute__((weak, used, noreturn)) void _exit(int i) {
    while (1)
        ;
}

__attribute__((weak, used)) int _gettimeofday_r(struct _reent *r, struct timeval *t, void *tzp) {
    __errno_r(r) = EPERM;
    return -1;
}

__attribute__((weak, used)) void *__dso_handle;

__attribute__((weak, used)) void __cxa_pure_virtual(void) {
    while (1)
        ;
}

#pragma GCC diagnostic pop
