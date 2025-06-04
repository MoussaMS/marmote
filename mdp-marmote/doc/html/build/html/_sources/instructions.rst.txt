Installation instructions
=========================

marmote is developped and validated on Linux (Debian/Fedora/Ubuntu), on MacOS and Windows 10.

The recommended installation is via `conda`.

Principle
^^^^^^^^^

The principle is to create a *conda environment*, in which both the C++ library and the 
python library of `Marmote` will be installed together with supporting libraries and
the consistent versions of development software (cmake, make, python etc.).

While more space-consuming than just installing the target libraries, this procedure
should remove most incompatibility issues between the current version of `Marmote` and
software already present on the machine.

Once the conda package is installed both C++ and Python development is enabled.
In order to make it easier to get started, we provide a set of examples for both languages
in the relevant sections: :doc:`for C++ <./cpp_api>` and :doc:`for Python <./python_api>`.

Installation procedure
^^^^^^^^^^^^^^^^^^^^^^

The procedure varies slightly with the operating system: 
follow the link corresponding to yours.

.. toctree::
   :maxdepth: 1

   instructions/linux/install_linux
   instructions/windows/install_windows
   instructions/macos/install_macos

Problems during installation
++++++++++++++++++++++++++++

Although we have tested the environment on many platforms, you may encounter some difficulties.
If this is the case, please take a look at the dedicated FAQ :doc:`page <./instructions/faq>` or contact us if your problem persists.

Please note that in order to make our environment as portable as possible, we have chosen not 
to overload it with numerous installed packages. Most of the time you will just need to 
(re)install a specific package to resolve the situation.
