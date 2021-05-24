/*
   Copyright 2021 Thomas Weißschuh <thomas@t-8ch.de>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */

#define _POSIX_C_SOURCE 200809L

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <linux/filter.h>
#include <linux/seccomp.h>
#include <linux/audit.h>

#define _cleanup_close __attribute__((__cleanup__(close_fd)))
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#define syscall_arg(_n) (offsetof(struct seccomp_data, args[_n]))
#define syscall_nr (offsetof(struct seccomp_data, nr))
#define syscall_arch (offsetof(struct seccomp_data, arch))

#ifndef O_PATH
#    define O_PATH __O_PATH
#endif

#if __x86_64__
#    define SECCOMP_ARCH_NATIVE AUDIT_ARCH_X86_64
#elif __i386__
#    define SECCOMP_ARCH_NATIVE AUDIT_ARCH_I386
#elif __arm__
#    define SECCOMP_ARCH_NATIVE AUDIT_ARCH_ARM
#elif __aarch64__
#    define SECCOMP_ARCH_NATIVE AUDIT_ARCH_AARCH64
#elif __riscv
#    if __riscv_xlen == 32
#        define SECCOMP_ARCH_NATIVE AUDIT_ARCH_RISCV32
#    elif __riscv_xlen == 64
#        define SECCOMP_ARCH_NATIVE AUDIT_ARCH_RISCV64
#    endif
#else
#    error Unknown target architecture
#endif

static const char *const qmk_id      = "ID_QMK=1\n";
static const size_t      qmk_id_size = 9;

static void close_fd(int *fd) {
    if (fd && *fd != -1) {
        close(*fd);
        *fd = -1;
    }
}
static int parse_item(const uint8_t *report, size_t report_size, size_t *offset, uint8_t item_size, uint32_t *item) {
    if (*offset + item_size > report_size) {
        return -EIO;
    }
    uint32_t r = 0;

    for (int i = 0; i < 4; i++) {
        r <<= 8;
        if (i < item_size) {
            r |= report[*offset + i];
        }
    }
    *offset = *offset + item_size;

    *item = ntohl(r);
    return 0;
}

// including bType and bTag
enum hid_item_type {
    HID_TYPE_USAGE_PAGE = 0x01,
    HID_TYPE_USAGE      = 0x02,
    HID_TYPE_COLLECTION = 0x28,
    HID_TYPE_LONG_ITEM  = 0xFF,
};

enum hid_collection_type {
    HID_COLLECTION_APPLICATION = 0x01,
};

static int parse_type(const uint8_t *report, size_t report_size, size_t *offset, enum hid_item_type *item_type, uint8_t *item_size) {
    if (*offset >= report_size) {
        return -EIO;
    }

    uint8_t data = report[*offset];

    // long items
    if (data == 0xFE) {
        *item_type = HID_TYPE_LONG_ITEM;
        if (*offset + 2 >= report_size) {
            return -EIO;
        }
        *item_size = report[*offset + 1];
        *offset    = *offset + 2;
        return 0;
    }

    *item_type = (enum hid_item_type)((data & 0xFC) >> 2);
    *item_size = data & 0x03;
    if (*item_size == 3) {
        *item_size = 4;
    }
    *offset = *offset + 1;
    return 0;
}

static int is_collection(const uint8_t *report, size_t report_size, uint32_t usage, enum hid_collection_type collection_type) {
    uint32_t up = 0, u = 0, ct = 0;
    size_t   offset = 0;
    int      ret;

    while (1) {
        uint8_t            item_size;
        enum hid_item_type item_type;
        ret = parse_type(report, report_size, &offset, &item_type, &item_size);
        if (ret) {
            return ret;
        }
        if (item_type == HID_TYPE_LONG_ITEM) {
            offset += item_size;
            continue;
        }
        uint32_t item;
        ret = parse_item(report, report_size, &offset, item_size, &item);
        if (ret) {
            return ret;
        }
        switch (item_type) {
            case HID_TYPE_USAGE_PAGE:
                up = item;
                break;
            case HID_TYPE_USAGE:
                if (item_size <= 2) {
                    item = (up << 16) | item;
                }
                u = item;
                break;
            case HID_TYPE_COLLECTION:
                ct = item;
                break;
            case HID_TYPE_LONG_ITEM:
                // can never happen
                abort();
        }
        if (u && ct) {
            return usage == u && collection_type == ct;
        }
    }
}

static int is_teensy_style_console(const uint8_t *report, size_t report_size) { return is_collection(report, report_size, UINT32_C(0xFF310074), HID_COLLECTION_APPLICATION); }

static int apply_syscall_filter(void) {
    union {
        struct {
            uint32_t lo, hi;
        };
        uint64_t raw;
    } qmk_id_addr;

    qmk_id_addr.raw = (uintptr_t)qmk_id;

    // only allow rt_sigreturn(), exit(), exit_group() and write(STDOUT_FILENO, "QMK_ID=1", 9)
    struct sock_filter filter[] = {
        BPF_STMT(BPF_LD | BPF_W | BPF_ABS, syscall_arch),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SECCOMP_ARCH_NATIVE, 0, 14),

        BPF_STMT(BPF_LD | BPF_W | BPF_ABS, syscall_nr),

        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_rt_sigreturn, 11, 0),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_exit_group, 10, 0),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_exit, 9, 0),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_write, 0, 9),

        BPF_STMT(BPF_LD | BPF_W | BPF_ABS, syscall_arg(0)),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, STDOUT_FILENO, 0, 7),

        BPF_STMT(BPF_LD | BPF_W | BPF_ABS, syscall_arg(1)),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, qmk_id_addr.lo, 0, 5),
        BPF_STMT(BPF_LD | BPF_W | BPF_ABS, syscall_arg(1) + 4),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, qmk_id_addr.hi, 0, 3),

        BPF_STMT(BPF_LD | BPF_W | BPF_ABS, syscall_arg(2)),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, qmk_id_size, 0, 1),

        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL_PROCESS),
    };

    struct sock_fprog prog = {
        .len    = ARRAY_SIZE(filter),
        .filter = filter,
    };

    if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) {
        return 1;
    }

    if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog)) {
        return 1;
    }
    return 0;
}

static int read_report_descriptor(const char *report_dir, uint8_t *buf, size_t buf_size) {
    int _cleanup_close sysfs_fd = openat(-1, report_dir, O_PATH | O_DIRECTORY);
    if (sysfs_fd == -1) {
        return -1;
    }
    int _cleanup_close report_fd = openat(sysfs_fd, "device/report_descriptor", O_RDONLY);
    if (report_fd == -1) {
        return -1;
    }

    return read(report_fd, buf, buf_size);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return EINVAL;
    }

    uint8_t buf[100];
    ssize_t r = read_report_descriptor(argv[1], buf, sizeof(buf));
    if (r == -1) {
        return errno;
    }

    if (apply_syscall_filter()) {
        return errno;
    }

    int is_c = is_teensy_style_console(buf, r);
    if (is_c < 0) {
        return -is_c;
    }
    if (is_c > 0) {
        write(STDOUT_FILENO, qmk_id, qmk_id_size);
    }
    return 0;
}
