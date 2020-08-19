# headsup

[![AppVeyor](https://img.shields.io/appveyor/build/marcosbozzani/headsup)](https://ci.appveyor.com/project/marcosbozzani/headsup)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/marcosbozzani/headsup)](https://github.com/marcosbozzani/headsup/releases/latest)
[![GitHub](https://img.shields.io/github/license/marcosbozzani/headsup)](https://github.com/marcosbozzani/headsup/blob/master/LICENSE)

Generate `.c` and `.h` declarations files

# Install

- scoop: 
  1. run `scoop bucket add extras`
  2. run `scoop install https://github.com/marcosbozzani/cdecl/raw/master/cdecl.json`
  1. run `scoop install https://github.com/marcosbozzani/headsup/raw/master/headsup.json`

- manual:
  1. download the [latest release](https://github.com/marcosbozzani/headsup/releases/latest)
  2. move the `headsup.exe` to the $PATH

# Usage

- `headsup (-h|-c) <output> <input.c> [<input.h>]`
- options:
  - `-h` : generate declarations for header
  - `-c` : generate declarations for source
- arguments
  - `output`: generated file, e.g. `file.decl.c` or `file.decl.h`
  - `input.c`: source file with the definitions, e.g. `file.c`
  - `input.h`: header file with the definitions, e.g. `file.h` (optional)
- examples: 
  - `headsup -c file.decl.c file.c`
  - `headsup -h file.decl.h file.c`
  - `headsup -c file.decl.c file.c file.h`
  - `headsup -h file.decl.h file.c file.h`

# Build

1. prerequisites: `ninja`, `gcc`, `cdecl`:
   - if you use scoop: 
     - `scoop bucket add extras`
     - `scoop install gcc ninja`
     - `scoop install https://github.com/marcosbozzani/cdecl/raw/master/cdecl.json`
2. clone `git clone https://github.com/marcosbozzani/headsup.git`
3. run `./configure.ps1 release` or `./configure.ps1 debug`
4. run `ninja`

# Test

1. run `./configure.ps1 release` or `./configure.ps1 debug`
2. run `ninja test`
