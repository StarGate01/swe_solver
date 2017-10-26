# Compilation, Testing and Building the Documentation

All commands should be unless otherwise noted run in the root directory of this repository.

## Compilation of the Framework System

### Required packages:
 - g++
 - scons

Use this project as a submodule of https://github.com/StarGate01/SWE1D. Compile with `scons` or `scons --dbg` for debug symbol support to `build/SWE1D`. Run this command in the root directory of the parent repository.

## Compilation of the CLI Application

### Required packages:
 - g++
 - scons

Compile with `scons` or `scons --dbg` for debug symbol support to `build/SWE1D_corecli`.

## Unit Testing

### Required packages:
 - cxxtest

Compile and run tests with `scons check`.

## Building the Documentation

### Required packages:
 - doxygen
 - graphviz
 - latex (eg. texlive)
    - pdflatex
    - amsmath
    - varwidth
    - multirow
    - adjustbox
    - collectbox
    - sectsty
    - tocloft
    - tabu

Compile with `doxygen documentation/doxygen.cfg` to `documentation/build/html/index.html`

Build PDF with `make` in directory `documentation/build/latex` to `documentation/build/latex/refman.pdf`