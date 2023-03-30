/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <cstring>
#include <cstdarg>
#include <algorithm>
#include "boot/uf2.h"
#include "elf.h"

typedef unsigned int uint;

#define ERROR_ARGS -1
#define ERROR_FORMAT -2
#define ERROR_INCOMPATIBLE -3
#define ERROR_READ_FAILED -4
#define ERROR_WRITE_FAILED -5

#define FLASH_SECTOR_ERASE_SIZE 4096u

static char error_msg[512];
static bool verbose;

static int fail(int code, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(error_msg, sizeof(error_msg), format, args);
    va_end(args);
    return code;
}

static int fail_read_error() {
    return fail(ERROR_READ_FAILED, "Failed to read input file");
}

static int fail_write_error() {
    return fail(ERROR_WRITE_FAILED, "Failed to write output file");
}

// we require 256 (as this is the page size supported by the device)
#define LOG2_PAGE_SIZE 8u
#define PAGE_SIZE (1u << LOG2_PAGE_SIZE)

struct address_range {
    enum type {
        CONTENTS,     // may have contents
        NO_CONTENTS,  // must be uninitialized
        IGNORE        // will be ignored
    };
    address_range(uint32_t from, uint32_t to, type type) : from(from), to(to), type(type) {}
    address_range() : address_range(0, 0, IGNORE) {}
    type type;
    uint32_t to;
    uint32_t from;
};

typedef std::vector<address_range> address_ranges;

#define MAIN_RAM_START        0x20000000u // same as SRAM_BASE in addressmap.h
#define MAIN_RAM_END          0x20042000u // same as SRAM_END in addressmap.h
#define FLASH_START           0x10000000u // same as XIP_MAIN_BASE in addressmap.h
#define FLASH_END             0x15000000u
#define XIP_SRAM_START        0x15000000u // same as XIP_SRAM_BASE in addressmap.h
#define XIP_SRAM_END          0x15004000u // same as XIP_SRAM_END in addressmap.h
#define MAIN_RAM_BANKED_START 0x21000000u // same as SRAM0_BASE in addressmap.h
#define MAIN_RAM_BANKED_END   0x21040000u
#define ROM_START             0x00000000u // same as ROM_BASE in addressmap.h
#define ROM_END               0x00004000u

const address_ranges rp2040_address_ranges_flash {
    address_range(FLASH_START, FLASH_END, address_range::type::CONTENTS),
    address_range(MAIN_RAM_START, MAIN_RAM_END, address_range::type::NO_CONTENTS),
    address_range(MAIN_RAM_BANKED_START, MAIN_RAM_BANKED_END, address_range::type::NO_CONTENTS)
};

const address_ranges rp2040_address_ranges_ram {
    address_range(MAIN_RAM_START, MAIN_RAM_END, address_range::type::CONTENTS),
    address_range(XIP_SRAM_START, XIP_SRAM_END, address_range::type::CONTENTS),
    address_range(ROM_START, ROM_END, address_range::type::IGNORE) // for now we ignore the bootrom if present
};

struct page_fragment {
    page_fragment(uint32_t file_offset, uint32_t page_offset, uint32_t bytes) : file_offset(file_offset), page_offset(page_offset), bytes(bytes) {}
    uint32_t file_offset;
    uint32_t page_offset;
    uint32_t bytes;
};

static int usage() {
    fprintf(stderr, "Usage: elf2uf2 (-v) <input ELF file> <output UF2 file>\n");
    return ERROR_ARGS;
}

static int read_and_check_elf32_header(FILE *in, elf32_header& eh_out) {
    if (1 != fread(&eh_out, sizeof(eh_out), 1, in)) {
        return fail(ERROR_READ_FAILED, "Unable to read ELF header");
    }
    if (eh_out.common.magic != ELF_MAGIC) {
        return fail(ERROR_FORMAT, "Not an ELF file");
    }
    if (eh_out.common.version != 1 || eh_out.common.version2 != 1) {
        return fail(ERROR_FORMAT, "Unrecognized ELF version");
    }
    if (eh_out.common.arch_class != 1 || eh_out.common.endianness != 1) {
        return fail(ERROR_INCOMPATIBLE, "Require 32 bit little-endian ELF");
    }
    if (eh_out.eh_size != sizeof(struct elf32_header)) {
        return fail(ERROR_FORMAT, "Invalid ELF32 format");
    }
    if (eh_out.common.machine != EM_ARM) {
        return fail(ERROR_FORMAT, "Not an ARM executable");
    }
    if (eh_out.common.abi != 0) {
        return fail(ERROR_INCOMPATIBLE, "Unrecognized ABI");
    }
    if (eh_out.flags & EF_ARM_ABI_FLOAT_HARD) {
        return fail(ERROR_INCOMPATIBLE, "HARD-FLOAT not supported");
    }
    return 0;
}

int check_address_range(const address_ranges& valid_ranges, uint32_t addr, uint32_t vaddr, uint32_t size, bool uninitialized, address_range &ar) {
    for(const auto& range : valid_ranges) {
        if (range.from <= addr && range.to >= addr + size) {
            if (range.type == address_range::type::NO_CONTENTS && !uninitialized) {
                return fail(ERROR_INCOMPATIBLE, "ELF contains memory contents for uninitialized memory at 0x%p", addr);
            }
            ar = range;
            if (verbose) {
                printf("%s segment %08x->%08x (%08x->%08x)\n", uninitialized ? "Uninitialized" : "Mapped", addr,
                   addr + size, vaddr, vaddr+size);
            }
            return 0;
        }
    }
    return fail(ERROR_INCOMPATIBLE, "Memory segment %08x->%08x is outside of valid address range for device", addr, addr+size);
}

int read_elf32_ph_entries(FILE *in, const elf32_header &eh, std::vector<elf32_ph_entry>& entries) {
    if (eh.ph_entry_size != sizeof(elf32_ph_entry)) {
        return fail(ERROR_FORMAT, "Invalid ELF32 program header");
    }
    if (eh.ph_num) {
        entries.resize(eh.ph_num);
        if (fseek(in, eh.ph_offset, SEEK_SET)) {
            return fail_read_error();
        }
        if (eh.ph_num != fread(&entries[0], sizeof(struct elf32_ph_entry), eh.ph_num, in)) {
            return fail_read_error();
        }
    }
    return 0;
}

int check_elf32_ph_entries(const std::vector<elf32_ph_entry>& entries, const address_ranges& valid_ranges, std::map<uint32_t, std::vector<page_fragment>>& pages) {
    for(const auto & entry : entries) {
        if (entry.type == PT_LOAD && entry.memsz) {
            address_range ar;
            int rc;
            uint mapped_size = std::min(entry.filez, entry.memsz);
            if (mapped_size) {
                rc = check_address_range(valid_ranges, entry.paddr, entry.vaddr, mapped_size, false, ar);
                if (rc) return rc;
                // we don't download uninitialized, generally it is BSS and should be zero-ed by crt0.S, or it may be COPY areas which are undefined
                if (ar.type != address_range::type::CONTENTS) {
                    if (verbose) printf("  ignored\n");
                    continue;
                }
                uint addr = entry.paddr;
                uint remaining = mapped_size;
                uint file_offset = entry.offset;
                while (remaining) {
                    uint off = addr & (PAGE_SIZE - 1);
                    uint len = std::min(remaining, PAGE_SIZE - off);
                    auto &fragments = pages[addr - off]; // list of fragments
                    // note if filesz is zero, we want zero init which is handled because the
                    // statement above creates an empty page fragment list
                    // check overlap with any existing fragments
                    for (const auto &fragment : fragments) {
                        if ((off < fragment.page_offset + fragment.bytes) !=
                            ((off + len) <= fragment.page_offset)) {
                            fail(ERROR_FORMAT, "In memory segments overlap");
                        }
                    }
                    fragments.push_back(
                            page_fragment{file_offset,off,len});
                    addr += len;
                    file_offset += len;
                    remaining -= len;
                }
            }
            if (entry.memsz > entry.filez) {
                // we have some uninitialized data too
                rc = check_address_range(valid_ranges, entry.paddr + entry.filez, entry.vaddr + entry.filez, entry.memsz - entry.filez, true,
                                         ar);
                if (rc) return rc;
            }
        }
    }
    return 0;
}

int realize_page(FILE *in, const std::vector<page_fragment> &fragments, uint8_t *buf, uint buf_len) {
    assert(buf_len >= PAGE_SIZE);
    for(auto& frag : fragments) {
        assert(frag.page_offset >= 0 && frag.page_offset < PAGE_SIZE && frag.page_offset + frag.bytes <= PAGE_SIZE);
        if (fseek(in, frag.file_offset, SEEK_SET)) {
            return fail_read_error();
        }
        if (1 != fread(buf + frag.page_offset, frag.bytes, 1, in)) {
            return fail_read_error();
        }
    }
    return 0;
}

static bool is_address_valid(const address_ranges& valid_ranges, uint32_t addr) {
    for(const auto& range : valid_ranges) {
        if (range.from <= addr && range.to > addr) {
            return true;
        }
    }
    return false;
}

static bool is_address_initialized(const address_ranges& valid_ranges, uint32_t addr) {
    for(const auto& range : valid_ranges) {
        if (range.from <= addr && range.to > addr) {
            return address_range::type::CONTENTS == range.type;
        }
    }
    return false;
}

static bool is_address_mapped(const std::map<uint32_t, std::vector<page_fragment>>& pages, uint32_t addr) {
    uint32_t page = addr & ~(PAGE_SIZE - 1);
    if (!pages.count(page)) return false;
    // todo check actual address within page
    return true;
}

static int determine_binary_type(const elf32_header &eh, const std::vector<elf32_ph_entry>& entries, bool *ram_style) {
    for(const auto &entry : entries) {
        if (entry.type == PT_LOAD && entry.memsz) {
            uint mapped_size = std::min(entry.filez, entry.memsz);
            if (mapped_size) {
                // we back convert the entrypoint from a VADDR to a PADDR to see if it originates in flash, and if
                // so call THAT a flash binary.
                if (eh.entry >= entry.vaddr && eh.entry < entry.vaddr + mapped_size) {
                    uint32_t effective_entry = eh.entry + entry.paddr - entry.vaddr;
                    if (is_address_initialized(rp2040_address_ranges_ram, effective_entry)) {
                        *ram_style = true;
                        return 0;
                    } else if (is_address_initialized(rp2040_address_ranges_flash, effective_entry)) {
                        *ram_style = false;
                        return 0;
                    }
                }
            }
        }
    }
    return fail(ERROR_INCOMPATIBLE, "entry point is not in mapped part of file");
}

int elf2uf2(FILE *in, FILE *out) {
    elf32_header eh;
    std::map<uint32_t, std::vector<page_fragment>> pages;
    int rc = read_and_check_elf32_header(in, eh);
    bool ram_style = false;
    address_ranges valid_ranges = {};
    if (!rc) {
        std::vector<elf32_ph_entry> entries;
        rc = read_elf32_ph_entries(in, eh, entries);
        if (!rc) {
            rc = determine_binary_type(eh, entries, &ram_style);
        }
        if (!rc) {
            if (verbose) {
                if (ram_style) {
                    printf("Detected RAM binary\n");
                } else {
                    printf("Detected FLASH binary\n");
                }
            }
            valid_ranges = ram_style ? rp2040_address_ranges_ram : rp2040_address_ranges_flash;
            rc = check_elf32_ph_entries(entries, valid_ranges, pages);
        }
    }
    if (rc) return rc;
    if (pages.empty()) {
        return fail(ERROR_INCOMPATIBLE, "The input file has no memory pages");
    }
    uint page_num = 0;
    if (ram_style) {
        uint32_t expected_ep_main_ram = UINT32_MAX;
        uint32_t expected_ep_xip_sram = UINT32_MAX;
        for(auto& page_entry : pages) {
            if ( ((page_entry.first >= MAIN_RAM_START) && (page_entry.first < MAIN_RAM_END)) && (page_entry.first < expected_ep_main_ram) ) {
                expected_ep_main_ram = page_entry.first | 0x1;
            } else if ( ((page_entry.first >= XIP_SRAM_START) && (page_entry.first < XIP_SRAM_END)) && (page_entry.first < expected_ep_xip_sram) ) { 
                expected_ep_xip_sram = page_entry.first | 0x1;
            }
        }
        uint32_t expected_ep = (UINT32_MAX != expected_ep_main_ram) ? expected_ep_main_ram : expected_ep_xip_sram;
        if (eh.entry == expected_ep_xip_sram) {
            return fail(ERROR_INCOMPATIBLE, "B0/B1 Boot ROM does not support direct entry into XIP_SRAM\n");
        } else if (eh.entry != expected_ep) {
            return fail(ERROR_INCOMPATIBLE, "A RAM binary should have an entry point at the beginning: %08x (not %08x)\n", expected_ep, eh.entry);
        }
        static_assert(0 == (MAIN_RAM_START & (PAGE_SIZE - 1)), "");
        // currently don't require this as entry point is now at the start, we don't know where reset vector is
#if 0
        uint8_t buf[PAGE_SIZE];
        rc = realize_page(in, pages[MAIN_RAM_START], buf, sizeof(buf));
        if (rc) return rc;
        uint32_t sp = ((uint32_t *)buf)[0];
        uint32_t ip = ((uint32_t *)buf)[1];
        if (!is_address_mapped(pages, ip)) {
            return fail(ERROR_INCOMPATIBLE, "Vector table at %08x is invalid: reset vector %08x is not in mapped memory",
                MAIN_RAM_START, ip);
        }
        if (!is_address_valid(valid_ranges, sp - 4)) {
            return fail(ERROR_INCOMPATIBLE, "Vector table at %08x is invalid: stack pointer %08x is not in RAM",
                        MAIN_RAM_START, sp);
        }
#endif
    } else {
        // Fill in empty dummy uf2 pages to align the binary to flash sectors (except for the last sector which we don't
        // need to pad, and choose not to to avoid making all SDK UF2s bigger)
        // That workaround is required because the bootrom uses the block number for erase sector calculations:
        // https://github.com/raspberrypi/pico-bootrom/blob/c09c7f08550e8a36fc38dc74f8873b9576de99eb/bootrom/virtual_disk.c#L205

        std::set<uint32_t> touched_sectors;
        for (auto& page_entry : pages) {
            uint32_t sector = page_entry.first / FLASH_SECTOR_ERASE_SIZE;
            touched_sectors.insert(sector);
        }

        uint32_t last_page = pages.rbegin()->first;
        for (uint32_t sector : touched_sectors) {
            for (uint32_t page = sector * FLASH_SECTOR_ERASE_SIZE; page < (sector + 1) * FLASH_SECTOR_ERASE_SIZE; page += PAGE_SIZE) {
                if (page < last_page) {
                    // Create a dummy page, if it does not exist yet. note that all present pages are first
                    // zeroed before they are filled with any contents, so a dummy page will be all zeros.
                    auto &dummy = pages[page];
                }
            }
        }
    }
    uf2_block block;
    block.magic_start0 = UF2_MAGIC_START0;
    block.magic_start1 = UF2_MAGIC_START1;
    block.flags = UF2_FLAG_FAMILY_ID_PRESENT;
    block.payload_size = PAGE_SIZE;
    block.num_blocks = (uint32_t)pages.size();
    block.file_size = RP2040_FAMILY_ID;
    block.magic_end = UF2_MAGIC_END;
    for(auto& page_entry : pages) {
        block.target_addr = page_entry.first;
        block.block_no = page_num++;
        if (verbose) {
            printf("Page %d / %d %08x%s\n", block.block_no, block.num_blocks, block.target_addr,
                   page_entry.second.empty() ? " (padding)": "");
        }
        memset(block.data, 0, sizeof(block.data));
        rc = realize_page(in, page_entry.second, block.data, sizeof(block.data));
        if (rc) return rc;
        if (1 != fwrite(&block, sizeof(uf2_block), 1, out)) {
            return fail_write_error();
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    int arg = 1;
    if (arg < argc && !strcmp(argv[arg], "-v")) {
        verbose = true;
        arg++;
    }
    if (argc < arg + 2) {
        return usage();
    }
    const char *in_filename = argv[arg++];
    FILE *in = fopen(in_filename, "rb");
    if (!in) {
        fprintf(stderr, "Can't open input file '%s'\n", in_filename);
        return ERROR_ARGS;
    }
    const char *out_filename = argv[arg++];
    FILE *out = fopen(out_filename, "wb");
    if (!out) {
        fprintf(stderr, "Can't open output file '%s'\n", out_filename);
        return ERROR_ARGS;
    }

    int rc = elf2uf2(in, out);
    fclose(in);
    fclose(out);
    if (rc) {
        remove(out_filename);
        if (error_msg[0]) {
            fprintf(stderr, "ERROR: %s\n", error_msg);
        }
    }
    return rc;
}
