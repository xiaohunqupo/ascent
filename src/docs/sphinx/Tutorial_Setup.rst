.. ###############################################################################
.. # Copyright (c) Lawrence Livermore National Security, LLC and other Ascent
.. # Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
.. # other details. No copyright assignment is required to contribute to Ascent.
.. ###############################################################################

.. _tutorial_setup:

Tutorial Setup
=================

The tutorial examples are installed with Ascent to the subdirectory ``examples/ascent/tutorial/``.  Below are several options for using pre-built Ascent installs and links to info about building Ascent. If you have access to Docker, the easiest way to test the waters is via the ``alpinedav/ascent`` Docker image.

Tutorial Cloud Option
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For in person tutorials (at Supercomputing, the ECP Annual Meeting, etc), we provide HTTP access to several instances of our Ascent Docker image running the jupyter notebook server.
We hand out IP addresses and login info to attendees during these events.

Using Docker
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you have Docker installed you can obtain a Docker image with a ready-to-use ascent install from `Docker Hub <https://hub.docker.com/r/alpinedav/ascent/>`_. This image also includes a Jupyter install to support running Ascent's tutorial notebooks.


To directly start the Jupyter Notebook server and run the tutorial notebooks, run:

.. code::

    docker run -p 8888:8888 -t -i alpinedav/ascent-jupyter

(The ``-p`` is used to forward ports between the container and your host machine, we use these ports to allow web servers on the container to serve data to the host.)

This image automatically launches a Jupyter Notebook server on port 8888. Assuming you forwarded port 8888 from the Docker container to your host machine, you should be able to connect to the notebook server using http://localhost:8888. The current password for the notebook server is: ``learn``

.. less is more, only point folks to the docker container
.. To start the base image and explore the install and tutorial examples with bash, run:
..
.. .. code::
..
..     docker run -p 8888:8888 -t -i alpinedav/ascent
..
..
.. You will now be at a bash prompt in you container.
..
.. To add the proper paths to Python and MPI to your environment, run:
..
.. .. code::
..
..     source ascent_docker_setup_env.sh
..
.. The ascent source code is at ``/ascent/src/``, and the install is at ``/ascent/install/``.
.. The tutorial examples are at ``/ascent/install/examples/ascent/tutorial/`` and the tutorial notebooks are at ``/ascent/install/examples/ascent/tutorial/ascent_intro/notebooks/``.
..
..
.. You can also launch the a Jupyter Notebook server from this image using the following:
..
.. .. code::
..
..     ./ascent_docker_run_jupyter.sh
..
.. The url (http://localhost:8888) and password (``learn``) are the same as above.
..

.. .. _tutorial_setup_public_installs:
..
.. Using Public Installs of Ascent
.. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
..
.. This section provides info about public installs we provide on several HPC machines.
..
.. Additionally, here is a `link to the scripts used to build our public installs <https://github.com/Alpine-DAV/ascent/tree/develop/scripts/spack_install>`_ .
..
.. OLCF Summit Installs
.. +++++++++++++++++++++++
..
..
.. * Build Details: gcc 9.3.0 with OpenMP and MPI support
.. * Modules: ``gcc/9.3.0``
.. * Location: ``/sw/summit/ums/ums010/ascent/current/summit/openmp/gnu/ascent-install/``
..
.. You can copy the tutorial examples from this install and use them as follows:
..
.. .. literalinclude:: tutorial_setup_olcf_summit_openmp_test.sh
..    :language: bash
..
.. * Build Details: gcc 9.3.0 with CUDA 11.0.3 and MPI support
.. * Modules: ``gcc/9.3.0`` ``cuda/11.0.3``
.. * Location: ``/sw/summit/ums/ums010/ascent/current/summit/cuda/gnu/ascent-install/``
..
.. You can copy the tutorial examples from this install and use them as follows:
..
.. .. literalinclude:: tutorial_setup_olcf_summit_cuda_test.sh
..    :language: bash
..
..
.. NERSC Perlmuter Install
.. +++++++++++++++++++++++
..
.. * Build Details: gcc 10.3.0 with CUDA 11.4.0 and MPI support
.. * Modules: ``PrgEnv-gnu`` ``cpe-cuda/21.12``  ``cudatoolkit/21.9_11.4``
.. * Location: ``/global/cfs/cdirs/alpine/software/ascent/current/perlmutter/cuda/gnu/ascent-install/``
..
..
.. You can copy the tutorial examples from this install and use them as follows:
..
.. .. literalinclude:: tutorial_setup_nersc_perlmutter_test.sh
..    :language: bash
..
..
.. LLNL CZ TOSS 3 Install
.. +++++++++++++++++++++++
..
.. * Build Details: gcc 4.9.3 with OpenMP and MPI support
.. * Modules: (none)
.. * Location: ``/usr/gapps/conduit/software/ascent/current/toss_3_x86_64_ib/openmp/gnu/ascent-install/``
..
.. You can copy the tutorial examples from this install and use them as follows:
..
.. .. literalinclude:: tutorial_setup_llnl_pascal_openmp_test.sh
..    :language: bash


.. Register Ascent's Python as a Jupyter Kernel
.. +++++++++++++++++++++++++++++++++++++++++++++
..
.. .. warning::
..     This works the LLNL LC TOSS3 CZ OpenMP install, we are working on recipes for other HPC centers.
..
.. You can register Ascent's Python as a custom Jupyter kernel with Jupyter Hub.
..
.. LLNL CZ TOSS 3 Jupyter Kernel Register Example:
..
.. .. literalinclude:: tutorial_setup_llnl_pascal_openmp_jhub.sh
..    :language: bash
..
.. After you register you will see an option to launch an Ascent kernel in Jupyter Hub:
..
.. .. image:: images/llnl_jhub_kernel_select.png
..
.. With this kernel you can access Ascent's Python modules or run the tutorial notebooks:
..
.. .. image:: images/llnl_jhub_kernel_example.png
..
..
.. If you want to remove the registered kernel, you can use:
..
.. .. code::
..
..   # show list of registered kernels
..   jupyter kernelspec list
..   # remove our Ascent custom kernel
..   jupyter kernelspec uninstall ascent_kernel

..
.. SC19 Tutorial VM Option
.. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
..
.. Ascent is also installed on the SC19 SENSEI + Ascent Example VM Image. The install is located at ``/home/in-situ-user/ascent/current``. You can use the tutorial examples as follows:
..
.. .. code::
..
..     #
..     # source helper script with Ascent paths
..     #
..     source /home/in-situ-user/ascent/current/setup_ascent_env.sh
..
..     #
..     # build cpp examples and run the first one
..     #
..     cd /home/in-situ-user/ascent/current/ascent-install/examples/ascent/tutorial/ascent_intro/cpp
..     make
..     ./ascent_first_light_example
..
..     #
..     # run a python example
..     #
..     cd ..
..     cd python
..     python ascent_first_light_example.py
..
..
.. This install also includes jupyter, you can launch the notebook server with:
..
.. .. code::
..
..    jupyter notebook
..
..
.. The jupyter examples are at:
..
.. `/home/in-situ-user/ascent/current/ascent-install/examples/ascent/tutorial/ascent_intro/`


Build and Install
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To build and install Ascent yourself see :doc:`QuickStart`.


