Frequently Asked Questions
==========================

Installation problem with Linux
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

June 2024. Debian 12. Problem of old `libstdcxx`.
-------------------------------------------------

If you encounter the following error message during compilation:

.. code-block:: bash

    /usr/bin/ld : /miniconda3/envs/marmote-use/lib/libmarmoteMarkovChain.so.1.2.0 : undefined reference « std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_replace_cold(char*, unsigned long, char const*, unsigned long, unsigned long)@GLIBCXX_3.4.31

Then you need to install a new version of the library  `GLIBCXX`. This can be done by typing

.. code-block:: bash

    conda install -c conda-forge libstdcxx-ng
    conda install -c conda-forge gxx=13.2.0


