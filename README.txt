STATUS
======
Abandond experimental C/C++ project. 
The goal was 
 - to use the Haar wavelet to reconstruct images.
 - Getting more familiar with its concept of Haar wavelet and reconstruction method
 - Experimenting with evolution algorithm to find optimal parameters
 - Connecting C and C++ projects

CONTENT
=======
In this repository you can find 4 projects.
* debug_util - debug utilities
* hrir - High Resolution Image Reconstruction
* shrir - Smart High Resolution Image Resolution
* ai_evol - Evolution algorithm
* QHRIR_demo - Qt demo project

Except for the Qt demo you can read more under the doc/index.html. There are links
to the doxygen documentation.

IMPORTANT the QHRIR_demo only works in debug mode, somehow the QImage reads wrong data
in realase mode, sorry for this.

USAGE
=====

All of the libraries under the source directory uses CMake. I used Linux for the developement
therefore the scripts are Linux scripts.
Under the bin directory there are several scripts:
* build_debug.sh: builds the current project in debug mode and install it under source/libs
* build_doc.sh: creates the current project's documentation with doxygen 
* build_release.sh: builds the current project in release mode and install it under source/libs
* clean.sh: Clean up the current project.
Example:
> cd source/hrir;
> ../../bin/build_debug.sh

To make it more easier: build_all.sh [-c(clean)|-d(debug)|-D(oc)]. This script makes all the libraries.

