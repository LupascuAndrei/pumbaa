/**
 * @file modos.c
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

#include "pumbaa.h"

static const qstr os_uname_info_fields[] = {
    MP_QSTR_sysname,
    MP_QSTR_nodename,
    MP_QSTR_release,
    MP_QSTR_version,
    MP_QSTR_machine
};

static const MP_DEFINE_STR_OBJ(os_uname_info_sysname_obj, MICROPY_PY_SYS_PLATFORM);
static const MP_DEFINE_STR_OBJ(os_uname_info_nodename_obj, "");
static const MP_DEFINE_STR_OBJ(os_uname_info_release_obj, STRINGIFY(VERSION));
static const MP_DEFINE_STR_OBJ(os_uname_info_version_obj, MICROPY_GIT_TAG);
static const MP_DEFINE_STR_OBJ(os_uname_info_machine_obj, "Arduino Due");

static mp_obj_tuple_t os_uname_info_obj = {
    .base = {&mp_type_attrtuple},
    .len = 5,
    .items = {
        (mp_obj_t)&os_uname_info_sysname_obj,
        (mp_obj_t)&os_uname_info_nodename_obj,
        (mp_obj_t)&os_uname_info_release_obj,
        (mp_obj_t)&os_uname_info_version_obj,
        (mp_obj_t)&os_uname_info_machine_obj,
        (void *)os_uname_info_fields,
    }
};

/**
 * Return a 5-tuple containing information identifying the current
 * operating system.
 *
 * def uname()
 */
static mp_obj_t os_uname(void)
{
    return ((mp_obj_t)&os_uname_info_obj);
}

/**
 * Change currect directory to given path.
 *
 * def chdir(path)
 */
static mp_obj_t os_chdir(mp_obj_t path_in)
{
    const char *path_p;
    int res;

    path_p = mp_obj_str_get_str(path_in);
    res = -1;

    if (res != 0) {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_OSError,
                                                "No such file or directory: '%s'",
                                                path_p));
    }

    return (mp_const_none);
}

/**
 * Get current working directory
 *
 * def getcwd()
 */
static mp_obj_t os_getcwd(void)
{
    char buf[MICROPY_ALLOC_PATH_MAX + 1];
    const char *path_p;

    buf[0] = '\0';
    path_p = thrd_get_env("CWD");

    if (path_p == NULL) {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_OSError,
                                                "No such file or directory: ''"));
    }

    if (strlen(path_p) >= membersof(buf)) {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_OSError,
                                                "No such file or directory: ''"));
    }

    strcpy(buf, path_p);

    return (mp_obj_new_str(buf, strlen(buf), false));
}

/**
 * Return a list of all files and folders in given path.
 *
 * def listdir(path)
 */
static mp_obj_t os_listdir(mp_uint_t n_args, const mp_obj_t *args_p)
{
    return (mp_const_none);
}

/**
 * Create a directory with given path.
 *
 * def mkdir(path)
 */
static mp_obj_t os_mkdir(mp_obj_t path_in)
{
    const char *path_p;
    int res;

    path_p = mp_obj_str_get_str(path_in);
    res = fs_mkdir(path_p);

    if (res != 0) {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_OSError,
                                                "Error creating directory '%s'",
                                                path_p));
    }

    return (mp_const_none);
}


/**
 * Remove given file path.
 *
 * def remove(path)
 */
static mp_obj_t os_remove(mp_obj_t path_in)
{
    const char *path_p;
    int res;

    path_p = mp_obj_str_get_str(path_in);
    res = -1;

    if (res != 0) {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_OSError,
                                                "Error removing file '%s'",
                                                path_p));
    }

    return (mp_const_none);
}

/**
 * Remove given empty directory.
 *
 * def rename(src, dst)
 */
static mp_obj_t os_rename(mp_obj_t path_src_in, mp_obj_t path_dst_in)
{
    const char *src_path_p;
    const char *dst_path_p;
    int res;

    src_path_p = mp_obj_str_get_str(path_src_in);
    dst_path_p = mp_obj_str_get_str(path_dst_in);
    res = -1;

    if (res != 0) {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_OSError,
                                                "Error renaming file '%s' to '%s'",
                                                src_path_p,
                                                dst_path_p));
    }

    return (mp_const_none);
}

/**
 * Remove given empty directory path.
 *
 * def rmdir(path)
 */
static mp_obj_t os_rmdir(mp_obj_t path_in)
{
    const char *path_p;
    int res;

    path_p = mp_obj_str_get_str(path_in);
    res = -1;

    if (res != 0) {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_OSError,
                                                "Error removing directory '%s'",
                                                path_p));
    }

    return (mp_const_none);
}

/**
 * Perform the equivalent of a stat() system call on the given path.
 *
 * def stat(path)
 */
static mp_obj_t os_stat(mp_obj_t path_in)
{
    const char *path_p;
    struct fs_stat_t stat;
    mp_obj_tuple_t *stat_p;
    int res;

    path_p = mp_obj_str_get_str(path_in);
    res = fs_stat(path_p, &stat);

    if (res != 0) {
        nlr_raise(mp_obj_new_exception_arg1(&mp_type_OSError,
                                            MP_OBJ_NEW_SMALL_INT(res)));
    }

    stat_p = mp_obj_new_tuple(10, NULL);

    stat_p->items[0] = MP_OBJ_NEW_SMALL_INT(0); /* st_mode */
    stat_p->items[1] = MP_OBJ_NEW_SMALL_INT(0); /* st_ino */
    stat_p->items[2] = MP_OBJ_NEW_SMALL_INT(0); /* st_dev */
    stat_p->items[3] = MP_OBJ_NEW_SMALL_INT(0); /* st_nlink */
    stat_p->items[4] = MP_OBJ_NEW_SMALL_INT(0); /* st_uid */
    stat_p->items[5] = MP_OBJ_NEW_SMALL_INT(0); /* st_gid */
    stat_p->items[6] = MP_OBJ_NEW_SMALL_INT(stat.size); /* st_size */
    stat_p->items[7] = MP_OBJ_NEW_SMALL_INT(0); /* st_atime */
    stat_p->items[8] = MP_OBJ_NEW_SMALL_INT(0); /* st_mtime */
    stat_p->items[9] = MP_OBJ_NEW_SMALL_INT(0); /* st_ctime */

    return (stat_p);
}

static MP_DEFINE_CONST_FUN_OBJ_0(os_uname_obj, os_uname);
static MP_DEFINE_CONST_FUN_OBJ_1(os_chdir_obj, os_chdir);
static MP_DEFINE_CONST_FUN_OBJ_0(os_getcwd_obj, os_getcwd);
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(os_listdir_obj, 0, 1, os_listdir);
static MP_DEFINE_CONST_FUN_OBJ_1(os_mkdir_obj, os_mkdir);
static MP_DEFINE_CONST_FUN_OBJ_1(os_remove_obj, os_remove);
static MP_DEFINE_CONST_FUN_OBJ_2(os_rename_obj, os_rename);
static MP_DEFINE_CONST_FUN_OBJ_1(os_rmdir_obj, os_rmdir);
static MP_DEFINE_CONST_FUN_OBJ_1(os_stat_obj, os_stat);

static const mp_rom_map_elem_t module_os_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_uos) },

    { MP_ROM_QSTR(MP_QSTR_uname), MP_ROM_PTR(&os_uname_obj) },
    { MP_ROM_QSTR(MP_QSTR_chdir), (mp_obj_t)&os_chdir_obj },
    { MP_ROM_QSTR(MP_QSTR_getcwd), (mp_obj_t)&os_getcwd_obj },
    { MP_ROM_QSTR(MP_QSTR_listdir), MP_ROM_PTR(&os_listdir_obj) },
    { MP_ROM_QSTR(MP_QSTR_mkdir), (mp_obj_t)&os_mkdir_obj },
    { MP_ROM_QSTR(MP_QSTR_remove), (mp_obj_t)&os_remove_obj },
    { MP_ROM_QSTR(MP_QSTR_rename),(mp_obj_t)&os_rename_obj},
    { MP_ROM_QSTR(MP_QSTR_rmdir), (mp_obj_t)&os_rmdir_obj },
    { MP_ROM_QSTR(MP_QSTR_stat), (mp_obj_t)&os_stat_obj },
};

static MP_DEFINE_CONST_DICT(module_os_globals, module_os_globals_table);

const mp_obj_module_t mp_module_os = {
    .base = { &mp_type_module },
    .name = MP_QSTR_os,
    .globals = (mp_obj_dict_t*)&module_os_globals,
};
