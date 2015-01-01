/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <stdint.h>

#include "py/obj.h"
#include "py/gc.h"
#include "gccollect.h"
#include MICROPY_HAL_H

mp_uint_t gc_helper_get_regs_and_sp(mp_uint_t *regs);

// obsolete
// void gc_helper_get_regs_and_clean_stack(mp_uint_t *regs, mp_uint_t heap_end);

void gc_collect(void) {
    // get current time, in case we want to time the GC
    uint32_t start = HAL_GetTick();

    // start the GC
    gc_collect_start();

    // We need to scan everything in RAM that can hold a pointer.
    // The data segment is used, but should not contain pointers, so we just scan the bss.
    gc_collect_root((void**)&_sbss, ((uint32_t)&_ebss - (uint32_t)&_sbss) / sizeof(uint32_t));

    // get the registers and the sp
    mp_uint_t regs[10];
    mp_uint_t sp = gc_helper_get_regs_and_sp(regs);

    // trace the stack, including the registers (since they live on the stack in this function)
    gc_collect_root((void**)sp, ((uint32_t)&_ram_end - sp) / sizeof(uint32_t));

    // end the GC
    gc_collect_end();

    if (0) {
        // print GC info
        uint32_t ticks = HAL_GetTick() - start; // TODO implement a function that does this properly
        gc_info_t info;
        gc_info(&info);
        printf("GC@%lu %lums\n", start, ticks);
        printf(" " UINT_FMT " total\n", info.total);
        printf(" " UINT_FMT " : " UINT_FMT "\n", info.used, info.free);
        printf(" 1=" UINT_FMT " 2=" UINT_FMT " m=" UINT_FMT "\n", info.num_1block, info.num_2block, info.max_block);
    }
}
