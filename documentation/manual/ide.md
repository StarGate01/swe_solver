# IDE integration

## Visual Studio Code (vscode)
Free, Open-Source, Cross-System IDE: https://code.visualstudio.com/

For IDE integration, use this project as a submodule of https://github.com/StarGate01/SWE1D

Configuration files are located in the `.vscode` directory.

Install all workspace recommended extensions.

## Environment

Linter configuration and Debug targets are available in versions both for native Linux (`Linux Native`) and the Windows Subsystem for Linux (`WSL`)

## Tasks

Build only the CLI test application of the submodule:
- Build Solver CLI Debug
- Build Solver CLI Release

Build the surrounding system which integrates the submodules code:
- Build Framework Debug
- Build Framework Release

## Debug targets

### Required packages:
- gdb

Targets:
- Framework
- Solver CLI
