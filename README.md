This repository contains simulator of computer club.

# Build and run

To build simulator use `mkdir build; cd build; cmake ..; cd ..` to run CMake configuration and then `cmake --build build` to actually build the project.
To run the project use `./build/bin/test-task <FILENAME>`, where FILENAME is the file that contains the configuration and events of the computer club

# Tests

There are test examples in `tests/integration/data`, where `.in`, `.out` and `.err` represent contents of the file, expected stdout and expected stderr after program run respectively.
To run tests use `cd build; ctest`
