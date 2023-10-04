# CppND-System-Monitor

This Project is base off the [Udacity Process Monitor Project](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
Using the ncurses library, this program will get information about your Linux system and desplay it in the console.

By opening and parsing specific files in the Linux filesystem, this program provides the following information in the console:
* Linux version
* Kernel version
* CPU utiliaztion (aggregated from system boot)
* Memory usage
* Total processes
* Running processes
* System up-time
* A list of processes with the highest CPU utilization (aggregated)

![System Monitor](images/monitor.png)

## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions

1. Clone the project repository
2. Build the project: `make build`
3. Run the resulting executable: `./build/monitor`

![Starting System Monitor](images/starting_monitor.png)
