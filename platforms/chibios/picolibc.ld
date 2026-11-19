/* Copyright 2026 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Supplementary linker rules for ARM ChibiOS builds using picolibc:
 * places thread-local storage (TLS) sections and defines picolibc symbols. */

SECTIONS
{
    /* Read-only TLS initialization image in flash. */
    .tdata :
    {
        *(.tdata .tdata.* .gnu.linkonce.td.*)
    } > RODATA_FLASH AT > RODATA_FLASH_LMA

    /* NOLOAD: lays out .tbss offsets without occupying flash. */
    .tbss (NOLOAD) :
    {
        *(.tbss .tbss.* .gnu.linkonce.tb.*)
        *(.tcommon)
        __tls_end = .;
    } > RODATA_FLASH
}

__tls_start = SIZEOF(.tdata) ? ADDR(.tdata) : ADDR(.tbss);
__tls_align = MAX(ALIGNOF(.tdata), ALIGNOF(.tbss));

/* Symbols consumed by picolibc's _init_tls() and _set_tls(). */
__tdata_source = LOADADDR(.tdata);
__tdata_size = SIZEOF(.tdata);
__tbss_offset = ADDR(.tbss) - __tls_start;
__tbss_size = SIZEOF(.tbss);
__arm32_tls_tcb_offset = MAX(8, __tls_align);

/* Reserve RAM for the TLS block at the base of the heap (initialized in syscall-fallbacks.c). */
__tls_space = ALIGN(__heap_base__, __tls_align);
__heap_base__ = ALIGN(__tls_space + (__tls_end - __tls_start), 8);
ASSERT(__heap_base__ <= __heap_end__, "not enough RAM for thread-local storage");
ASSERT(__tls_end == __tls_start || DEFINED(_set_tls), "thread-local storage is used but not set up");

/* Alias ChibiOS heap bounds to the symbol names expected by picolibc's sbrk(). */
__heap_start = __heap_base__;
__heap_end = __heap_end__;
