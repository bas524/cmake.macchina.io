This is a fork of [macchina.io](https://macchina.io) project.
I did it for the cmake build system support.

![macchina.io][logo]

*macchina.io Edge Device SDK is a powerful application software platform for IoT devices.*

With macchina.io you can rapidly build and deploy device applications that communicate with devices, sensors, actuators, cloud services, and humans.

macchina.io provides a web-enabled, secure, modular and extensible C++ and JavaScript IoT application environment on top of Linux, consisting of middleware, protocols and rich APIs.
macchina.io provides ready-to-use and industry proven software building blocks that enable applications to collect, process, filter, analyze and visualize sensor, machine and process data locally, directly where it originates, and where the action happens.
macchina.io enables IoT edge and fog computing.

macchina.io runs on Linux-based devices, including IoT gateways, industrial computing devices, and prototyping platforms like the Raspberry Pi, Beaglebone and MangOH.

macchina.io is based on the [POCO C++ Libraries](https://pocoproject.org) and
uses the [V8 JavaScript engine](https://developers.google.com/v8/).

For more information, including [documentation](https://macchina.io/docs), please see the
[macchina.io website](https://macchina.io). There are also a couple of useful articles and How-To's in the
[project wiki](https://github.com/macchina-io/macchina.io/wiki).


Prerequisites
-------------

  - cmake 3.5.0 or newer
  - Linux: GNU C++ (g++) 5.0 or newer; alternatively Clang++ 3.4 or newer (C++14)
  - macOS: Clang++ (Apple LLVM) 10.0 or newer
  - Windows: MSVC2017
  - OpenSSL headers and libraries (on macOS, via [Homebrew](http://brew.sh): `brew install openssl`)
  - Python 2.7 (for building V8)


Getting Started
---------------

For the impatient, using a Linux or macOS or Windows machine:

    $ git clone https://github.com/bas524/macchina.io.git
    $ cd macchina.io
    $ git checkout master
    $ mkdir cmake-build
    $ cd cmake-build
    $ cmake -DCMAKE_BUILD_TYPE=Release ..
    $ cmake --build . --config Release
    
On MacOS system set openssl cmake variable

    $ cmake -DCMAKE_BUILD_TYPE=Release -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl ..

Then, on Linux:

    $ cd bin
    $ export LD_LIBRARY_PATH=$PWD/../lib
    $ ./macchina

On macOS:

    $ cd bin
    $ export DYLD_LIBRARY_PATH=$PWD/../lib
    $ ./macchina
    
On Windows:

    $ cd bin
    $ ./macchina

Then direct your favorite web browser to <http://localhost:22080> and log in with username 'admin' and password 'admin'.

For more detailed instructions, including how to cross-compile for embedded Linux targets,
as well as an introduction to writing JavaScript code for macchina.io, see
the [documentation](http://macchina.io/docs/index.html), specifically
[Introduction and Overview](http://macchina.io/docs/00100-MacchinaIntroduction.html) and
[Getting Started with macchina.io](http://macchina.io/docs/00100-MacchinaIntroduction.html).


Contributions
-------------

We welcome contributions! Specifically we're looking for new sensor and device implementations,
as well as additional protocols.
Please see our [CONTRIBUTING](https://github.com/macchina-io/macchina.io/blob/develop/CONTRIBUTING.md)
document to get started.

[logo]: doc/images/macchina_logo_320.png "macchina.io Logo"

