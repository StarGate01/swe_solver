# Compilation {#compilepage}

### Required packages:
 - `g++`
 - `scons`
 - Additional compilers depending on your SWE configuration

#### SWE1D

Compile with `scons` or `scons --dbg` for debug symbol support to `build/SWE1D`. Run this command in the root directory of the framework repository.

#### SWE

Compile with `scons buildVariablesFile=build/options/SWE_gnu.py` or `scons buildVariablesFile=build/options/SWE_gnu.py compileMode=debug` for debug symbol support to `build/SWE_gnu_debug_none_fwave`.

Run this command in the root directory of the framework repository. There are several build variable files provided in `build/options`.

See [Linking The Documentation](@ref adddocpage) for additional information.