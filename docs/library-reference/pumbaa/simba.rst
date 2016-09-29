:mod:`simba` --- Simba wrapper
==============================

.. module:: simba
   :synopsis: Simba wrapper.

The simba module is a thin Python wrapper of the `Simba Library`_ to
make most `Simba` functionality available in `Python`.

----------------------------------------------

.. class:: simba.Timer(timeout, event=None, mask=0x1, callback=None, flags=0)

   Instantiate a timer object from given arguemts. The timer expires
   `timeout` seconds after the timer has been started. When the timer
   expires given `callback` is called from interrupt context and
   `mask` is written to given `event` channel.

   Simba documentation: `kernel/timer`_

   .. method:: start()

      Start the timer.

   .. method:: stop()

      Stop the timer. If the timer is stopped before it has expired it
      will never exipre. This function has no effect if the timer has
      already expired.

   .. data:: PERIODIC

      Pass this flag to ``simba.Timer`` for periodic timers.


.. class:: simba.Event()

   Initialize given event object.

   Simba documentation: `sync/event`_

   .. method:: read(mask)

      Wait for an event to occur and return a mask of all active
      events.

   .. method:: write(mask)

      Write given event(s) to the channel.

   .. method:: size()

      Get the number of event(s) set in the channel.


.. class:: simba.Queue()

   Initialize given queue object.

   Simba documentation: `sync/queue`_

   .. method:: read(size)

      Reads up to `size` number of bytes from the queue and returns
      them as a string. Raises an exception on error.

   .. method:: write(string)

      Write given `string` to the queue. Returns the number of bytes
      written. Raises an exception on error.

   .. method:: size()

      Get the number of bytes available to read.


.. class:: simba.Dac(devices, sampling_rate)

   Instansiate a Dac object. `devices` is either a list of DAC pin
   devices or a single DAC pin device. The DAC pin devices can be
   found in the `Board` class, often named `PIN_DAC0` and `PIN_DAC1`.

   Simba documentation: `drivers/dac`_

   .. method:: convert(samples)

      Start a synchronous convertion of digital samples to an analog
      signal. This function returns when all samples have been
      converted.

   .. method:: async_convert(samples)

      Start an asynchronous convertion of digital samples to an analog
      signal. This function only blocks if the hardware is not ready
      to convert more samples. Call `async_wait()` to wait for an
      asynchronous convertion to finish.

   .. method:: async_wait()

      Wait for an ongoing asynchronous convertion to finish.


.. class:: simba.Exti(device, trigger, event=None, mask=0x1, callback=None)

   Instantiate an object handling interrupts on given
   `device`. `trigger` may be a combination of ``RISING``, ``FALLING``
   or ``BOTH``. When an interrupt occurs given `callback` is called
   from interrupt context and `mask` is written to given event channel
   `event`.

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


.. class:: simba.Pin(device, mode)

   Initialize given pin object with given `device` and `mode`. The
   device is selected among the pins available in the `Board`
   class. Mode must be either `INPUT` or `OUTPUT`.

   Simba documentation: `drivers/pin`_

   .. method:: read()

      Read the current pin value and return it as an integer. Returns
      0 if the pin is low and 1 if the pin is high.

   .. method:: write(value)

      Write `value` to the pin. `value` must be an object that can be
      converted to an integer. The value is either 0 or 1, where 0 is
      low and 1 is high.

   .. method:: toggle()

      Toggle the pin output value (high/low).

   .. method:: set_mode(mode)

      Set the pin mode to given mode `mode`. The mode must be either
      ``INPUT`` or ``OUTPUT``.

   .. data:: INPUT

      Input pin mode.

   .. data:: OUTPUT

      Output pin mode.


.. function:: simba.fs_call(command)

   Returns the output of given file system command. Raises OSError if
   the command is missing or fails to execute.

   Simba documentation: `filesystems/fs`_


.. function:: simba.fs_format(path)

   Format file system at given path. All data in the file system will
   be lost.

   Simba documentation: `filesystems/fs`_


.. _Simba Library: http://simba-os.readthedocs.io/en/latest/library-reference.html

.. _kernel/timer: http://simba-os.readthedocs.io/en/latest/library-reference/kernel/timer.html
.. _sync/event: http://simba-os.readthedocs.io/en/latest/library-reference/sync/event.html
.. _sync/queue: http://simba-os.readthedocs.io/en/latest/library-reference/sync/queue.html
.. _drivers/dac: http://simba-os.readthedocs.io/en/latest/library-reference/drivers/dac.html
.. _drivers/exti: http://simba-os.readthedocs.io/en/latest/library-reference/drivers/exti.html
.. _drivers/pin: http://simba-os.readthedocs.io/en/latest/library-reference/drivers/pin.html
.. _filesystems/fs: http://simba-os.readthedocs.io/en/latest/library-reference/filesystems/fs.html
