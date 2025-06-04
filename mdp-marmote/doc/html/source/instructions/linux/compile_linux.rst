Using the C++ API of Marmote on Linux
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is recommended follow the ``cmake`` development framework.
Its steps are:

* to specify what are the project's source files, libraries etc. in a single file
* to create a "build" directory separate from source files
* execute ``cmake`` to create adequate makefiles
* execute ``make`` to create binaries, perform tests and all other tasks.

Preparation
^^^^^^^^^^^

Prepare an installation directory, and move into it.
We assume throughout that ``MAR_DIR`` is the path to this directory.

.. code-block:: sh

    $ mkdir MAR_DIR
    $ cd MAR_DIR

Creation of the makefile and the binaries
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  
Creating a ``cmake`` project simply requires placing there C++ source files and a
``CMakeLists.txt`` configuration file.

Compilation of all examples
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Download the source code files: :download:`as zip file <../all_ex/all_examples.zip>` to the directory ``MAR_DIR``.
Download also the :download:`configuration file <../all_ex/CMakeLists.txt>`.
Unpack the source files:

.. code-block:: sh

    $ unzip all_examples.zip

Then prepare the build directory, and "make" the project:

.. code-block:: sh
  
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

The executables will be found in the ``build`` directory.
To execute it (here for *example1*):

.. code-block:: sh

    $ cd build
    $ ./example1 3 0.2 0.2 0.6

