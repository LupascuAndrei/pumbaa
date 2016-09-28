/**
 * @file module_simba/class_exti.h
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

#ifndef __MODULE_SIMBA_CLASS_EXTI_H__
#define __MODULE_SIMBA_CLASS_EXTI_H__

#include "pumbaa.h"

struct class_exti_t {
    mp_obj_base_t base;
    struct exti_driver_t exti;
    struct class_event_t *event_obj_p;
    uint32_t mask;
    mp_obj_t callback;
};

extern const mp_obj_type_t module_simba_class_exti;

#endif
