# Compilation, Testing and Building the Documentation

## Compilation of the Framework System

### Required packages:
 - g++
 - scons

Use this project as a submodule of https://github.com/StarGate01/SWE1D. Compile with `scons` or `scons --dbg` for debug symbol support to `build/SWE1D`. Run this command in the root directory of the parent repository.

## Unit Testing

### Required packages:
 - cxxtest

Compile and run tests with `scons check`.

## Building the Documentation

### Required packages:
 - doxygen
 - perl
 - graphviz
 - latex (eg. texlive)
    - pdflatex
    - bibtex
    - varwidth
    - multirow
    - adjustbox
    - collectbox
    - sectsty
    - tocloft
    - tabu

Compile with `doxygen ../documentation/doxygen.cfg` in directory `src` to `documentation/build/html/index.html`

Build PDF with `make` in directory `documentation/build/latex` to `documentation/build/latex/refman.pdf`