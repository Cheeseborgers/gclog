# Gclog

A Minimal, Header only, Modern C++ Logger.

## Dependencies

### Necessary Dependencies
1. A C++ compiler that supports C++14+. 
See [cppreference.com](https://en.cppreference.com/w/cpp/compiler_support)
to see which features are supported by each compiler.
The following compilers should work:
  * [gcc 7+](https://gcc.gnu.org/)
  * [clang 6+](https://clang.llvm.org/)
  

### Optional Dependencies

None
## Build Instructions

### Make a build directory

    $ mkdir build && cd build

### Configure your build

To configure the project and write makefiles, you could use `cmake` with a
bunch of command line options. The easier option is to run cmake interactively,
with the Cmake Curses Dialog Command Line tool:  

    $ ccmake ..

Once `ccmake` has finished setting up, press 'c' to configure the project, 
press 'g' to generate, and 'q' to quit.

### Build
Once you have selected all the options you would like to use, you can build the 
project:

    $ cmake --build .   # build all targets

### Build using an alternate compiler

CMake use the environment variables CC and CXX to decide which 
compiler to use. If you don't set these variables yourself, the system 
default compiler will be used.

To build using clang, you can use these commands:

    $ CC=clang CXX=clang++ ccmake ..
    $ CC=clang CXX=clang++ cmake --build .
