# IDE Integration {#idepage}

### Required packages:
- `vscode`
- `gbd`

## Visual Studio Code (vscode)
Free, Open-Source, Cross-System IDE: https://code.visualstudio.com/

Configuration files are located in the `.vscode` directory.

Install all workspace recommended extensions.

## Environment

Linter configuration and debug targets are available in versions both for native Linux (`Linux Native`) and the Windows Subsystem for Linux (`WSL`)

## Tasks

The following tasks are registered in the IDE's task runner

#### SWE1D

- Build Debug Binaries
- Build Release Binaries
- Clean Binaries
- Regenerate Data
- Run Tests
- Build Solver Documentation
- Clean Solver Documentation
- Build Framework Documentation
- Clean Framework Documentation
- Build Presentation
- Clean Presentation

#### SWE

- Build Debug Binaries
- Build Release Binaries
- Clean Binaries
- Clean And Regenerate Data
- Clean And Regenerate Data And Simulate Failure
- Continue Data From Checkpoint
- Run Tsunami Script
- Build Solver Documentation
- Clean Solver Documentation
- Build All Framework Documentation
- Build Fragment Framework Documentation
- Clean Framework Documentation
- Run Solver Tests
- Run Framework Tests
- Build Presentation
- Clean Presentation

## Debug targets

The target `build/SWE1D` or `build/SWE_gnu_debug_none_fwave` is available when built with support for debug symbols
- GDB Linux Native
- GDB WSL