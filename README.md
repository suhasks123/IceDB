# IceDB:
This is the main repository for IceDB, a Key-Value Store Database Management System built as a part of the course CS251 (DBMS), CSE Dept, NITK.

## Code:
- Written in C++.
- The application is a linux command-line application.
- The code uses the Linux kernel coding style (https://www.kernel.org/doc/html/v4.10/process/coding-style.html).

## Build Instructions:
Make sure the current working directory is the main IceDB directory before running these commands:

```
$ rm -rf ./build/*
$ cd build
$ cmake ..
$ make
```

## Repo Structure:
The Repo follows a standard C++ Project structure with:
1. **bin**: For storing binaries after compilation.
2. **build**: For storing object files generated during build.
3. **docs**: For storing documentation.
4. **include**: For storing header files.
5. **lib**: For storing dependencies as static libraries.
6. **src**: For storing source files.

The build is handled by CMake.

## Dependencies:
- CMake (>3.0.0)


## Contributors:
- Suhas K S(181CO253) - https://github.com/suhasks123
- Sai Krishna Anand (181CO244) - https://github.com/SaiKrishna1207
