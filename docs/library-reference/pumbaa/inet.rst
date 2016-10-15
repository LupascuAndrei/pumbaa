:mod:`inet` --- Internet networking
===================================

.. module:: inet
   :synopsis: Internet networking.

Internet network configuration and protocol implementation.

Simba documentation: `inet`_

----------------------------------------------


.. function:: inet.ping_host_by_ip_address(address, timeout)

   Ping host by IPv4 address `address`. Send an echo request packet to
   the host and wait for the echo reply packet. Only the ICMP header
   is transmitted, no extra payload data is added to the
   packet. Returns the round trip time in milliseconds.

   .. code-block:: python

      >>> inet.ping_host_by_ip_address("192.168.0.5", 2)
      10

   Simba documentation: `inet/ping`_


.. _inet: http://simba-os.readthedocs.io/en/latest/library-reference/inet.html
.. _inet/ping: http://simba-os.readthedocs.io/en/latest/library-reference/inet/ping.html
