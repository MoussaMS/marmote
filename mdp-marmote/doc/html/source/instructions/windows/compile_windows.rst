Using the C++ API of Marmote on MS Windows
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is recommended follow the ``cmake`` development framework.
Its steps are:

* to specify what are the project's source files, libraries etc. in a single file
* to create a "Release" directory separate from source files
* execute ``cmake`` to create adequate makefiles
* execute ``make`` to create binaries, perform tests and all other tasks.

Requirements
^^^^^^^^^^^^

For the use of C++ API (and only for it), you will need to install some elements of ``Visual C++``:

* install Visual Studio: https://visualstudio.microsoft.com/downloads/
* install ``C++ CMake tools for Windows``. 
    * This needs both ``Desktop development with C++`` and ``Linux Development with C++`` (see here https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170). 
    * This can be done with the visual studio installer.

The following steps are executed in a shell window:
open an ``anaconda prompt`` or a ``conda powershell`` in the start menu.
    
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
    $ cmake -G "Visual Studio XX 20YY" ..
    $ cmake --build . --config Release

where ``XX`` is the number of your installed version of Visual Studio and ``20YY`` the year of your installed version. It can be e.g. ``Visual Studio 16 2019``
or ``Visual Studio 17 2022``.


The executables will be found in the ``Release`` directory.
To execute it (here for *example1*):

.. code-block:: sh

    $ cd Release		
    $ .\example1 3 0.2 0.2 0.6

