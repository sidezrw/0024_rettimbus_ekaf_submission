# Build instructions

## Build Requirements

- Ubuntu 20.04
- Compiler g++ 10.3.0
- Make 4 or better
- CMake 3.15 or newer
- Microsoft SEAL 3.6.6
- OpenMP 4.0 or newer

### HEBench Versions

- API Bridge v0.7.0-beta
- Frontend v0.8.0-beta (only to run the benchmark)

## How to Build

All files to build are included in the `source` directory.

1. If API Bridge and SEAL are not installed in global `/usr/local` system location, locate their installation and point the CMakeLists.txt to the appropriate install locations:
  - API Bridge:
    - Include: `set(HEBENCH_API_INCLUDE_DIR  "/usr/local/include")`
    - Library: `find_library(hebench_cpp_FOUND  NAMES  libhebench_cpp.a  HINTS  "/usr/local/lib")`
  - SEAL:
    - Include: `set(SEAL_INCLUDE_DIR  "/usr/local/include/SEAL-3.6")`
    - Library: `find_library(SEAL_FOUND  NAMES  libseal-3.6.a  HINTS  "/usr/local/lib")`
2. Inside the `source` directory, create a `build` directory and run CMake.
```bash
mkdir source/build
cd source/build
cmake -DCMAKE_INSTALL_PREFIX=$PWD/../install -DCMAKE_BUILD_TYPE=Release ..
```
3. Compile and install with `make`.
```bash
make -j
make install
```
The backend compiles into `libsubmission_0024.so`.

