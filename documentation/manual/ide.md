# IDE integration

## Visual Studio Code (vscode)
Free, Open-Source, Cross-System IDE: https://code.visualstudio.com/

For IDE integration, use this project as a submodule of https://github.com/StarGate01/SWE1D

Configuration files are located in the `.vscode` directory.

Install all workspace recommended extensions.

## Environment

Linter configuration and Debug targets are available in versions both for native Linux (`Linux Native`) and the Windows Subsystem for Linux (`WSL`)

## Tasks

Build the surrounding system which integrates the submodules code:
- Build Debug
- Build Release
- Clean All
- Generate Data
- Clean Data
- Build Solver Documentation
- Run Solver Tests

## Debug targets

### Required packages:
- gdb
