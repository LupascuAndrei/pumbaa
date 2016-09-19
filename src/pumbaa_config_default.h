/**
 * @file pumbaa_config_default.h
 *
 * @section License
 * Copyright (C) 2016, Erik Moqvist
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * This file is part of the Pumbaa project.
 */

#ifndef __PUMBAA_CONFIG_DEFAULT_H__
#define __PUMBAA_CONFIG_DEFAULT_H__

/**
 * This is the default configuration of Pumbaa.
 */

#ifndef PATH_MAX
#    define PATH_MAX                                      128
#endif

#ifndef MICROPY_ALLOC_PATH_MAX
#    define MICROPY_ALLOC_PATH_MAX                   PATH_MAX
#endif

#ifndef MICROPY_ENABLE_GC
#    define MICROPY_ENABLE_GC                             (1)
#endif

#ifndef MICROPY_DEBUG_PRINTERS
#    define MICROPY_DEBUG_PRINTERS                        (1)
#endif

#ifndef MICROPY_HELPER_REPL
#    define MICROPY_HELPER_REPL                           (1)
#endif

#ifndef MICROPY_HELPER_LEXER_UNIX
#    if defined(ARCH_LINUX)
#        define MICROPY_HELPER_LEXER_UNIX                 (1)
#    else
#        define MICROPY_HELPER_LEXER_UNIX                 (0)
#    endif
#endif

#ifndef MICROPY_ENABLE_SOURCE_LINE
#    define MICROPY_ENABLE_SOURCE_LINE                    (1)
#endif

#ifndef MICROPY_FLOAT_IMPL
#    define MICROPY_FLOAT_IMPL       MICROPY_FLOAT_IMPL_FLOAT
#endif

#ifndef MICROPY_PY_BUILTINS_FLOAT
#    define MICROPY_PY_BUILTINS_FLOAT                     (1)
#endif

#ifndef MICROPY_PY_BUILTINS_FROZENSET
#    define MICROPY_PY_BUILTINS_FROZENSET                 (1)
#endif

#ifndef MICROPY_PY_SYS_EXIT
#    define MICROPY_PY_SYS_EXIT                           (1)
#endif

#ifndef MICROPY_PY_SYS_PLATFORM
#    define MICROPY_PY_SYS_PLATFORM                   "simba"
#endif

#ifndef MICROPY_PY_SYS_STDFILES
#    define MICROPY_PY_SYS_STDFILES                       (1)
#endif

#ifndef MICROPY_PY_UJSON
#    define MICROPY_PY_UJSON                              (1)
#endif

#ifndef MICROPY_PY_URE
#    define MICROPY_PY_URE                                (1)
#endif

#ifndef MICROPY_PY_UBINASCII
#    define MICROPY_PY_UBINASCII                          (1)
#endif

#ifndef MICROPY_PY_UTIME
#    define MICROPY_PY_UTIME                              (1)
#endif

#ifndef MICROPY_MODULE_FROZEN_STR
#    define MICROPY_MODULE_FROZEN_STR                     (1)
#endif

#ifndef MICROPY_MODULE_BUILTIN_INIT
#    define MICROPY_MODULE_BUILTIN_INIT                   (1)
#endif

#ifndef CONFIG_MAIN_FRIENDLY_REPL
#    define CONFIG_MAIN_FRIENDLY_REPL                     (1)
#endif

#ifndef CONFIG_HEAP_SIZE
#    if defined(ARCH_ESP)
#        define CONFIG_HEAP_SIZE                      (11000)
#    else
#        define CONFIG_HEAP_SIZE                      (32768)
#    endif
#endif

#ifndef CONFIG_PUMBAA_CLASS_BOARD
#    define CONFIG_PUMBAA_CLASS_BOARD                       1
#endif

#ifndef CONFIG_PUMBAA_CLASS_DAC
#    if defined(FAMILY_SAM) || defined(FAMILY_LINUX)
#        define CONFIG_PUMBAA_CLASS_DAC                     1
#    else
#        define CONFIG_PUMBAA_CLASS_DAC                     0
#    endif
#endif

#ifndef CONFIG_PUMBAA_CLASS_EVENT
#    define CONFIG_PUMBAA_CLASS_EVENT                       1
#endif

#ifndef CONFIG_PUMBAA_CLASS_PIN
#    define CONFIG_PUMBAA_CLASS_PIN                         1
#endif

#ifndef CONFIG_PUMBAA_CLASS_TIMER
#    define CONFIG_PUMBAA_CLASS_TIMER                       1
#endif

#ifndef CONFIG_PUMBAA_FS_CALL
#    define CONFIG_PUMBAA_FS_CALL                           1
#endif

extern const struct _mp_obj_module_t mp_module_os;
extern const struct _mp_obj_module_t mp_module_time;
extern const struct _mp_obj_module_t module_pumbaa;

#define MICROPY_PORT_BUILTIN_MODULES                            \
    { MP_ROM_QSTR(MP_QSTR_os), MP_ROM_PTR(&mp_module_os) },     \
    { MP_ROM_QSTR(MP_QSTR_time), MP_ROM_PTR(&mp_module_time) }, \
    { MP_ROM_QSTR(MP_QSTR_pumbaa), MP_ROM_PTR(&module_pumbaa) },

/* Extra built in names to add to the global namespace. */
#define MICROPY_PORT_BUILTINS                                           \
    { MP_ROM_QSTR(MP_QSTR_help), MP_ROM_PTR(&mp_builtin_help_obj) },    \
    { MP_ROM_QSTR(MP_QSTR_input), MP_ROM_PTR(&mp_builtin_input_obj) },  \
    { MP_ROM_QSTR(MP_QSTR_open), MP_ROM_PTR(&mp_builtin_open_obj) },

#define MICROPY_PORT_ROOT_POINTERS \
    mp_obj_t keyboard_interrupt_obj; \
    const char *readline_hist[8];

//////////////////////////////////////////
// Do not change anything beyond this line
//////////////////////////////////////////

// Define to 1 to use undertested inefficient GC helper implementation
// (if more efficient arch-specific one is not available).
#ifndef MICROPY_GCREGS_SETJMP
    #ifdef __mips__
        #define MICROPY_GCREGS_SETJMP                     (1)
    #else
        #define MICROPY_GCREGS_SETJMP                     (0)
    #endif
#endif

// type definitions for the specific machine

#ifdef __LP64__
typedef long mp_int_t; // must be pointer size
typedef unsigned long mp_uint_t; // must be pointer size
#else
// These are definitions for machines where sizeof(int) == sizeof(void*),
// regardless for actual size.
typedef int mp_int_t; // must be pointer size
typedef unsigned int mp_uint_t; // must be pointer size
#endif

#define BYTES_PER_WORD sizeof(mp_int_t)

// Cannot include <sys/types.h>, as it may lead to symbol name clashes
#if _FILE_OFFSET_BITS == 64 && !defined(__LP64__)
typedef long long mp_off_t;
#else
typedef long mp_off_t;
#endif

#define mp_hal_pin_obj_t mp_obj_t

// We need to provide a declaration/definition of alloca()
#include <alloca.h>

#define MP_PLAT_PRINT_STRN(str, len) mp_hal_stdout_tx_strn_cooked(str, len)

#define MP_STATE_PORT MP_STATE_VM

#endif
