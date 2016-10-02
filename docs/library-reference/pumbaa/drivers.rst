:mod:`drivers` --- Device drivers
=================================

.. module:: drivers
   :synopsis: Device drivers.

Device drivers.

Simba documentation: `drivers`_

----------------------------------------------

.. class:: drivers.Pin(device, mode)

   Create a pin object with given `device` and `mode`. The `device` is
   selected among the pins available in the `board` module. `mode`
   must be either ``INPUT`` or ``OUTPUT``.

   Simba documentation: `drivers/pin`_

   .. method:: read()

      Read the current pin value and return it as an integer. Returns
      0 if the pin is low and 1 if the pin is high.

   .. method:: write(value)

      Write the logic level `value` to the pin. `value` must be an
      object that can be converted to an integer. The value is either
      0 or 1, where 0 is low and 1 is high.

   .. method:: toggle()

      Toggle the pin output value (high/low).

   .. method:: set_mode(mode)

      Set the pin mode to given mode `mode`. The mode must be either
      ``INPUT`` or ``OUTPUT``.

   .. data:: INPUT

      Input pin mode.

   .. data:: OUTPUT

      Output pin mode.


.. class:: drivers.Exti(device, trigger, event=None, mask=0x1, callback=None)

   Create an object handling interrupts on given `device`. `trigger`
   may be a combination of ``RISING``, ``FALLING`` or ``BOTH``. When
   an interrupt occurs given `callback` is called from interrupt
   context and `mask` is written to given event channel `event`.

   Simba documentation: `drivers/exti`_

   .. method:: start()

      Start the interrupt handler.

   .. method:: stop()

      Stop the interrupt handler.

   .. data:: RISING

      Trigger an interrupt on rising edges.

   .. data:: FALLING

      Trigger an interrupt on falling edges.

   .. data:: BOTH

      Trigger an interrupt on both rising and falling edges.


.. class:: drivers.Dac(devices, sampling_rate)

   Instansiate a Dac object. `devices` is either a list of DAC pin
   devices or a single DAC pin device. The DAC pin devices can be
   found in the ``board`` module, often named ``PIN_DAC0`` and
   ``PIN_DAC1``.

   Here is an example of how to create a DAC driver and convert
   digital samples to an analog signal.

   .. code-block:: python

      >>> dac = Dac(board.PIN_DAC0)
      >>> dac.convert(b'\x01\x02\x03\x04')

   Simba documentation: `drivers/dac`_

   .. method:: convert(samples)

      Start a synchronous convertion of digital samples to an analog
      signal. This function returns when all samples have been
      converted.

   .. method:: async_convert(samples)

      Start an asynchronous convertion of digital samples to an analog
      signal. This function only blocks if the hardware is not ready
      to convert more samples. Call ``async_wait()`` to wait for an
      asynchronous convertion to finish.

   .. method:: async_wait()

      Wait for an ongoing asynchronous convertion to finish.


.. class:: drivers.Spi(device, slave_select, mode=MODE_MASTER, speed=SPEED_1MBPS, polarity=1, phase=1)

   Create a Spi object. Select the SPI device with `device` and slave
   select pin with `slave_select`. `mode` in one of ``MODE_MASTER``
   and ``MODE_SLAVE``. `speed` is only used by the master. `polarity`
   is the bus idle logic level. `phase` controls if sampling are done
   on falling or rising clock edges..

   Here is an example of how to create a SPI driver and write 4 bytes
   to the slave.

   .. code-block:: python

      >>> spi = Spi(board.SPI_0, board.PIN_D3)
      >>> spi.start()
      >>> spi.select()
      >>> spi.write(b'\x01\x02\x03\x04')
      >>> spi.deselect()
      >>> spi.stop()

   Simba documentation: `drivers/spi`_

   .. method:: start()

      Configures the SPI hardware with the settings of this object.

   .. method:: stop()

      Deconfigures the SPI hardware if given driver currently ownes
      the bus.

   .. method:: take_bus()

      In multi master application the driver must take ownership of
      the SPI bus before performing data transfers. Will re-configure
      the SPI hardware if configured by another driver.

   .. method:: give_bus()

      In multi master application the driver must give ownership of
      the SPI bus to let other masters take it.

   .. method:: select()

      Select the slave by asserting the slave select pin.

   .. method:: deselect()

      Deselect the slave by de-asserting the slave select pin.

   .. method:: transfer(write_buffer[, size])

      Simultaniuos read/write operation over the SPI bus. Writes data
      from `write_buffer` to the bus. The `size` argument can be used to
      transfer fewer bytes than the size of `write_buffer`. Returns
      the read data as a bytes object.

      The number of read and written bytes are always equal for a
      transfer.

   .. method:: transfer_into(read_buffer, write_buffer[, size])

      Same as ``transfer()``, but the read data is written to
      `read_buffer`.

   .. method:: read(size)

      Read `size` bytes from the SPI bus. Returns the read data as a
      bytes object.

   .. method:: read_into(buffer[, size])

      Same as ``read()``, but the read data is written to `buffer`.

   .. method:: write(buffer[, size])

      Write `size` bytes from `buffer` to the SPI bus. Writes all data
      in `buffer` is `size` is not given.

   .. data:: MODE_MASTER

      SPI master mode.

   .. data:: MODE_SLAVE

      SPI slave mode.


.. _drivers: http://simba-os.readthedocs.io/en/latest/library-reference/drivers.html
.. _drivers/pin: http://simba-os.readthedocs.io/en/latest/library-reference/drivers/pin.html
.. _drivers/exti: http://simba-os.readthedocs.io/en/latest/library-reference/drivers/exti.html
.. _drivers/dac: http://simba-os.readthedocs.io/en/latest/library-reference/drivers/dac.html
.. _drivers/spi: http://simba-os.readthedocs.io/en/latest/library-reference/drivers/spi.html
