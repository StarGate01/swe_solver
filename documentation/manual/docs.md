# Building The Documentation {#docpage}

### Required packages:
 - `doxygen`
 - `perl`
 - `graphviz`
 - `make`
 - `git`
 - `latex` 
 - Additional required packages depending on you latex installation

Compile with `doxygen ../documentation/doxygen.cfg` in directory `src` to `documentation/build/html/index.html`

Build PDF with `make` in directory `documentation/build/latex` to `documentation/build/latex/refman.pdf`
