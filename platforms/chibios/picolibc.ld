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

/* Supplementary linker rules for ARM toolchains using Picolibc.
 *
 * Picolibc builds `errno` and other C library state as thread-local storage
 * (`.tdata`/`.tbss`), which ChibiOS's standard ARM linker scripts do not place.
 * Place the read-only TLS template in `RODATA_FLASH`, reserve the runtime TLS
 * block at the start of `HEAP_RAM`, and alias `__heap_start`/`__heap_end` for
 * Picolibc's `sbrk()`.
 */

SECTIONS
{
    .tdata :
    {
        *(.tdata .tdata.* .gnu.linkonce.td.*)
        PROVIDE(__tdata_end = .);
    } > RODATA_FLASH AT > RODATA_FLASH_LMA

    .tbss (NOLOAD) :
    {
        *(.tbss .tbss.* .gnu.linkonce.tb.*)
        *(.tcommon)
        PROVIDE(__tls_end = .);
    } > RODATA_FLASH
}

__tls_start = SIZEOF(.tdata) ? ADDR(.tdata) : ADDR(.tbss);
__tls_align = MAX(ALIGNOF(.tdata), ALIGNOF(.tbss));
__tdata_source = LOADADDR(.tdata);
__tdata_size = SIZEOF(.tdata);
__tbss_offset = ADDR(.tbss) - __tls_start;
__tbss_size = SIZEOF(.tbss);
__tls_space_size = __tls_end - __tls_start;

__tls_space = ALIGN(__heap_base__, __tls_align);
__heap_base__ = ALIGN(__tls_space + __tls_space_size, 8);
__heap_start = __heap_base__;
__heap_end = __heap_end__;

__arm32_tls_tcb_offset = MAX(8, __tls_align);
__arm32_tls_tp = __tls_space - __arm32_tls_tcb_offset;

ASSERT(__heap_base__ <= __heap_end__, "region HEAP_RAM overflowed with TLS");
