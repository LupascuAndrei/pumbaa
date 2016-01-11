#!/usr/bin/env python
#
# @file main.py
# @version 0.2.0
#
# @section License
# Copyright (C) 2014-2016, Erik Moqvist
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# This file is part of the Pumba project.
#

from kernel import thrd, sys
from drivers import pin
import board

sys.start()

LED = pin.Pin(board.LED, pin.OUTPUT)

while True:
    thrd.sleep(1000)
    LED.toggle()
