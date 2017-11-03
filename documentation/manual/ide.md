# IDE integration

## Visual Studio Code (vscode)
Free, Open-Source, Cross-System IDE: https://code.visualstudio.com/

For IDE integration, use this project as a submodule of https://github.com/StarGate01/SWE1D

Configuration files are located in the `.vscode` directory.

Install all workspace recommended extensions.

## Environment

Linter configuration and Debug targets are available in versions both for native Linux (`Linux Native`) and the Windows Subsystem for Linux (`WSL`)

## Tasks

The following tasks are registered in the IDE's task runner
- Build Debug Binaries
- Build Release Binaries
- Clean Binaries
- Regenerate Data
- Run Tests
- Build Documentation
- Clean Documentation
- Build Presentation
- Clean Presentation

## Debug targets

The target `build/SWE1D` is available when built with support for debug symbols
- GDB Linux Native
- GDB WSL

### Required packages:
- gdb
