.. s documentation master file, created by
   sphinx-quickstart on Sun Dec 20 08:56:50 2015.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

|buildstatus|_
|codecov|_

Welcome to Pumbaa's documentation!
=================================

`Pumbaa` is `Python`_ on top of `Simba`_.

The implementation is a port of `MicroPython`_, designed for embedded
devices with limited amount of RAM and code memory.

Project homepage: https://github.com/eerimoq/pumbaa

.. toctree::
   :maxdepth: 1
   :titlesonly:
   :hidden:

   user-guide
   examples
   library-reference

Features
--------

* `Python 3 language`_.

* Device drivers.

See the :doc:`library-reference` for a full list of features.

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

.. |buildstatus| image:: https://travis-ci.org/eerimoq/pumbaa.svg
.. _buildstatus: https://travis-ci.org/eerimoq/pumbaa

.. |codecov| image:: https://codecov.io/gh/eerimoq/pumbaa/branch/master/graph/badge.svg
.. _codecov: https://codecov.io/gh/eerimoq/pumbaa

.. _Python: https://www.python.org/
.. _Simba: http://simba-os.readthedocs.io/en/latest/
.. _MicroPython: http://www.micropython.org/
.. _Python 3 language: http://docs.micropython.org/en/latest/pyboard/reference/index.html
