# utils

- utilities I use in my workflow
- they are made in C++

## Deps
- [stb image](https://github.com/nothings/stb.git)

## Build
- open build.sh file and add include path to stb image folder path
- run build.sh in your shell (bash).

-----------------------------------

- [dump] prints any file [raw data] in C array with their size.
  * NOTE: you can use `xxd -i <file>` instead, but this file is useful to avoid xxd dependency.

- [idump] prints any file [raw data] into jpg 256x256 image of certain constant compile time path.
  * see OUTPUT_DIR in idump.cpp.

- [isplit] splits any image bit layers into different images.
  * constant compile time path. see OUTPUT_DIR in isplit.cpp also.

- [bezier] prints draw commands for LaTeX TikZ to draw a bezier curve.
  * you can modify this file to your needs.
