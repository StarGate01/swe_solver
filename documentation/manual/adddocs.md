# Linking The Documentation {#adddocpage}

The solver documentation is configured to generate a doxygen _tagfile_, which can be used to extend the frameworks' documentation.

### Required packages:
 - `doxygen`
 - `perl`
 - `graphviz`
 - `make`
 - `git`
 - `latex`
 - Additional required packages depending on you latex installation

#### SWE1D

In fact, a full doxygen documentation is available for SWE1D and a partial one is available for SWE.

Compile with `doxygen ../documentation/doxygen.cfg` in framework directory `src` to `documentation/build/html/index.html`

Build PDF with `make` in directory `documentation/build/latex` to `documentation/build/latex/refman.pdf`

This documentation is configured to link to the generated tagfile of this submodule.

#### SWE

The original documentation is available where our fork originates: https://github.com/TUM-I5/SWE/wiki.

See the SWE documentation for additional information.