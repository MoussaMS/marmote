Using the Python API of Marmote on MS Windows
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Examples provided are in two forms: 
Python notebooks and simple Python program files.

Preparation
^^^^^^^^^^^

Prepare an installation directory, and move into it.
We assume throughout that ``MAR_DIR`` is the path to this directory.

.. code-block:: sh

    $ mkdir MAR_DIR
    $ cd MAR_DIR

The following steps are executed in a shell window:
open an ``anaconda prompt`` or a ``conda powershell`` in the start menu.

Running the notebooks
^^^^^^^^^^^^^^^^^^^^^

Download the notebooks files: :download:`as zip file <../all_nb/all_notebooks.zip>` to the directory ``MAR_DIR``.
Unpack the source files:

.. code-block:: sh

    $ unzip all_notebooks.zip

Then move in the directory and type

.. code-block:: sh

    $ jupyter-notebook name_of_notebook.ipynb

If the installation of `jupyter` is required then type

.. code-block:: sh

    $ conda install -c conda-forge jupyter

Running Python files
^^^^^^^^^^^^^^^^^^^^

Download all the Python files: :download:`as zip file <../all_pyex/all_pythons.zip>` to the directory ``MAR_DIR``.
Unpack the source files:

.. code-block:: sh

    $ unzip all_pythons.zip

Then move in the directory and type

.. code-block:: sh

    $ python name_of_script.py

Running Python files with VSCode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Once Marmote is installed on the computer it is also possible to load the Marmote python kernel in `vscode`.
All details are given by Microsoft `here <https://learn.microsoft.com/en-us/visualstudio/python/managing-python-environments-in-visual-studio?view=vs-2022>`__
or also `here <https://code.visualstudio.com/docs/python/environments>`__.


