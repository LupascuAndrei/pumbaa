#
# @section License
#
# The MIT License (MIT)
# 
# Copyright (c) 2016, Erik Moqvist
# 
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use, copy,
# modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# This file is part of the Pumbaa project.
#

import time
import socket
from drivers import esp_wifi

SSID = 'Qvist2'
PASSWORD = 'maxierik'
IP = '192.168.0.7'
PORT = 9000

esp_wifi.set_op_mode(esp_wifi.OP_MODE_STATION)
esp_wifi.station_init(SSID, PASSWORD)
esp_wifi.station_connect()

while esp_wifi.station_get_status() != 'got-ip':
    print('Waiting for WiFi connection...')
    time.sleep(2)

listener = socket.socket()
listener.bind((IP, PORT))
listener.listen(1)

while True:
    print('Listening for a client to connect.')
    client, address = listener.accept()
    print('Accepted client with address', address)
    
    while True:
        data = client.recv(1)
        print(data)
        if not data:
            print('Socket closed.')
            break
        client.send(data)
