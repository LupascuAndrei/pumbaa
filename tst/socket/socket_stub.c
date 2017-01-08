/**
 * @section License
 *
 * The MIT License (MIT)
 * 
 * Copyright (c) 2016, Erik Moqvist
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * This file is part of the Pumbaa project.
 */

#include "simba.h"

int socket_module_init()
{
    return (0);
}

int socket_open_tcp(struct socket_t *self_p)
{
    /* Channel functions. */
    self_p->base.read = (chan_read_fn_t)socket_read;
    self_p->base.write = (chan_write_fn_t)socket_write;
    self_p->base.size = (chan_size_fn_t)socket_size;

    return (0);
}

int socket_open_udp(struct socket_t *self_p)
{
    return (0);
}

int socket_open_raw(struct socket_t *self_p)
{
    return (0);
}

int socket_close(struct socket_t *self_p)
{
    static int counter = 0;

    counter++;

    if (counter == 5) {
        return (-1);
    }
    
    return (0);
}

int socket_bind(struct socket_t *self_p,
                const struct inet_addr_t *local_addr_p)
{
    static int counter = 0;

    counter++;

    if (counter == 3) {
        return (-1);
    }
    
    return (0);
}

int socket_listen(struct socket_t *self_p, int backlog)
{
    static int counter = 0;

    counter++;

    if (counter == 3) {
        return (-1);
    } else {
        if (backlog != 5) {
            return (-1);
        }
    }
    
    return (0);
}

int socket_connect(struct socket_t *self_p,
                   const struct inet_addr_t *addr_p)
{
    char ip[16];
    static int counter = 0;

    counter++;

    if (counter == 1) {
        if (strcmp("192.168.1.101", inet_ntoa(&addr_p->ip, &ip[0])) != 0) {
            return (-1);
        }
        
        if (addr_p->port != 80) {
            return (-1);
        }
    } else if (counter == 2) {
        return (-1);
    }
    
    return (0);
}

int socket_accept(struct socket_t *self_p,
                  struct socket_t *accepted_p,
                  struct inet_addr_t *addr_p)
{
    static int counter = 0;

    counter++;

    if (counter == 2) {
        return (-1);
    }
    
    return (0);
}

ssize_t socket_sendto(struct socket_t *self_p,
                      const void *buf_p,
                      size_t size,
                      int flags,
                      const struct inet_addr_t *remote_addr_p)
{
    static int counter = 0;

    counter++;

    if (counter == 1) {
        if (memcmp(buf_p, "bar", 3) != 0) {
            return (-1);
        }

        return (3);
    } else if (counter == 2) {
        return (-1);
    }
    
    return (0);
}

ssize_t socket_recvfrom(struct socket_t *self_p,
                        void *buf_p,
                        size_t size,
                        int flags,
                        struct inet_addr_t *remote_addr)
{
    static int counter = 0;

    counter++;

    if (counter == 1) {
        memcpy(buf_p, "foo", size);
        inet_aton("1.2.3.4", &remote_addr->ip);
        remote_addr->port = 30;
        
        return (3);
    }

    return (-1);
}

ssize_t socket_write(struct socket_t *self_p,
                     const void *buf_p,
                     size_t size)
{
    static int counter = 0;

    counter++;

    if (counter == 3) {
        return (0);
    } else if (counter == 4) {
        return (-1);
    } else {
        if (memcmp(buf_p, "foo", size) != 0) {
            return (-1);
        }
        
        return (3);
    }
}

ssize_t socket_read(struct socket_t *self_p,
                    void *buf_p,
                    size_t size)
{
    static int counter = 0;

    counter++;

    if (counter == 1) {
        memcpy(buf_p, "bar", size);
        
        return (3);
    } else if (counter == 2) {
        return (0);
    }

    return (-1);
}

ssize_t socket_size(struct socket_t *self_p)
{
    return (0);
}
