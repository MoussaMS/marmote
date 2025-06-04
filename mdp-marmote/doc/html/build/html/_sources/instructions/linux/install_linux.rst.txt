Marmote install with conda on Linux
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following installation steps are executed in a shell window.

Requirements
^^^^^^^^^^^^

Before installing ``Marmote``, you will need to install ``Anaconda`` or ``miniconda``: https://conda.io/miniconda.html

Installation of conda packages
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The next step is to create the conda environment (called *marmote-use*), then to activate it and at last install the required conda packages.
In order to install the library in the conda environment it is necessary to specify the channels and the minimal packages on the command line.

.. code-block:: sh

    $ conda create -n marmote-use
    $ conda activate marmote-use
    $ conda install -c marmote -c conda-forge marmote

You're ready to program!

