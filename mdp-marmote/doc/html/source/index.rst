.. MARMOTE documentation master file, created by
   sphinx-quickstart on Thu Feb 13 10:21:40 2020.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Marmote's documentation
=======================

.. toctree::
   :maxdepth: 2
   :caption: Table of Contents
   :name: mastertoc

   instructions
   cpp_api
   python_api
   about


Marmote
-------

Marmote is a programming platform for building and solving Markov models with discrete state spaces. It consists in
a library of objects:

* allowing to construct custom Markov Chain models, analyze their structure and solve them
* allowing to construct custom Markov Decision Process models, solve them and analyze the solution
* representing well-known Markovian models from the literature.

This library comes with two API: one for C++ development, one for Python development.

You can learn how to

* :doc:`install <./instructions>` a consistent programming environment containing Marmote, using conda
* program your models with the :doc:`C++ API <./cpp_api>` 
* program your models with the :doc:`Python API <./python_api>`

..
   Licence

..
   You also have access to the :doc:`documentation <./documentation>` including the user/reference manual and the detailed API documentation.


Documentation creation date: |today|
