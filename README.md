# StackOverflowDetector

## Table of Contents
- [Introduction](#introduction)
- [Build and Run](#build-and-run)
- [Example Output](#example-output)
- [How does this work](#how-does-this-work)

## Introduction
This program executes a function in endless recursion and allocates memory with every call, and tracks how much memory was allocated before getting stack overflow. Then it handles the overflow someway and prints the estimated stack size.

## Build and Run
To clone and run this project, you'll need [Git](https://git-scm.com) and [CMake](https://cmake.org/) installed on your computer. From your command line:

```bash
# Clone this repository
$ git clone https://github.com/Hayk10002/StackOverflowDetector

# Go into the repository
$ cd StackOverflowDetector

# Generate the build files
# Use debug to not let compiler optimize the allocations
$ cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build

# Build the project
$ cmake --build build --config Debug

# Run the executable with the path to the target file as an argument.
$ your/path/to/exe/main.exe
# example - .../main.exe
```

## Example Output
(for linux and gcc or clang environment)

```
Caught signal 11: Stack overflow detected!
Stack size estimated: 16240KB
```

## How does this work
The estimated stack size is in fact an estimation because other things from other places can occupie a small fraction of stack to make the output not precise.