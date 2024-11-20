# utils

- utilities I use in my workflow
- they are made in C++

## Deps
- [stb image](https://github.com/nothings/stb.git)

## Build
- open build.sh file and add include path to stb image folder path
- run build.sh in your shell (bash).

-----------------------------------

- [dump]   which prints any file [raw data] in C array with their size.
  * NOTE: you can use `xxd -i <file>` instead, but this file is useful to avoid xxd dependency.

- [idump]  which prints any file [raw data] into jpg 256x256 image of certain constant compile time path.
  * see OUTPUT_DIR in idump.cpp

- [isplit] which splits any image bit layers into different images
  * constant compile time path. see OUTPUT_DIR in isplit.cpp also
