# getsec

## Table of Contents
- [Introduction](#introduction)
- [Build and Run](#build-and-run)
- [Example Output](#example-output)
- [How does this work](#how-does-this-work)

## Introduction
`getsec` is a tool designed to extract and display information about the sections of an executable file. It provides details such as the section name, size, and memory address, helping developers analyze the structure of executables.

## Build and Run
To clone and run this project, you'll need [Git](https://git-scm.com) and [CMake](https://cmake.org/) installed on your computer. From your command line:

```bash
# Clone this repository
$ git clone https://github.com/Hayk10002/getsec

# Go into the repository
$ cd getsec

# Generate the build files
$ cmake -DCMAKE_BUILD_TYPE=Release -S . -B build

# Build the project
$ cmake --build build --config Release

# Run the executable with the path to the target file as an argument.
$ your/path/to/exe/getsec.exe {path_to_executable}
# example - .../getsec.exe ./example.exe
```

## Example Output
(for the test_target executable (the code is in test_code.cpp), and running with gcc)

```
Running command: objdump -h /some/path/test_target.exe
Section: .text          , Address: 0x0000000140001000, Size:  6312B
Section: .data          , Address: 0x0000000140003000, Size:   176B
Section: .rdata         , Address: 0x0000000140004000, Size:  2824B
Section: .pdata         , Address: 0x0000000140005000, Size:   540B
Section: .xdata         , Address: 0x0000000140006000, Size:   412B
Section: .bss           , Address: 0x0000000140007000, Size:   416B
Section: .idata         , Address: 0x0000000140008000, Size:  2296B
Section: .CRT           , Address: 0x0000000140009000, Size:    96B
Section: .tls           , Address: 0x000000014000a000, Size:    16B
Section: .rsrc          , Address: 0x000000014000b000, Size:  1256B
Section: .reloc         , Address: 0x000000014000c000, Size:   124B
Section: .debug_aranges , Address: 0x000000014000d000, Size:  1120B
Section: .debug_info    , Address: 0x000000014000e000, Size: 42715B
Section: .debug_abbrev  , Address: 0x0000000140019000, Size:  8006B
Section: .debug_line    , Address: 0x000000014001b000, Size:  7344B
Section: .debug_frame   , Address: 0x000000014001d000, Size:  2096B
Section: .debug_str     , Address: 0x000000014001e000, Size:   722B
Section: .debug_line_str, Address: 0x000000014001f000, Size:  5903B
Section: .debug_loclists, Address: 0x0000000140021000, Size:  4849B
Section: .debug_rnglists, Address: 0x0000000140023000, Size:   366B
```

## How does this work
The tool parses the headers of the provided executable file to extract section information. It reads the section table and retrieves details such as the name, size, and memory address of each section. This information is then displayed in a human-readable format. The project demonstrates how to work with executable file formats and extract meaningful data from them.
It is specified that the output is generated when compiling with gcc because this tool uses `objdump` or `dumpbin` depending on what compiler it was compiled (it is assumed that the tool `objdump` comes with gcc or clang, and the tool `dumpbin` comes with msvc) and so based on the compiler and the tool the output can differ.
