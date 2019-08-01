# ASF File Parsing Tool

## Overview

This repository contains a set of files that can be used to parse and display information contained in an Advanced Systems Format (ASF) file. The base unit of organization in an ASF file is called the ASF object. This code parses and displays the following ASF objects:

- Header Object
- File Properties Object
- Stream Properties Object
- Header Extension Object
- Codec List Object
- Extended Content Description Object
- Stream Bitrate Properties Object

An ASF file can contain objects which are not included in the list above. If this code encounters such an object, then it closes the file and prints an error message to the command line that it has encountered an unknown object.

The ASF Specification, which was used as a reference for implementing the parsing code, can be downloaded from the Microsoft web site [here](https://go.microsoft.com/fwlink/p/?linkid=31334).

Additional information about ASF can be found on the [Microsoft web site](https://docs.microsoft.com/en-us/windows/win32/wmformat/overview-of-the-asf-format).

## Organization

The source files are organized in the following manner:

- `main.c`: Contains the `main()` function that parses and prints information about each object in the file
- `util.c / main.h`: Contains the structures needed to store information about each object, as well as helper functions
- `parse.c / parse.h`: Contains the functions needed to parse each object
- `display.c / display.h`: Contains the functions needed to print information about each object to standard output

## Quick Start

To build the code on Linux/Mac and create an executable named `asfparse` in the current directory, run the Makefile by typing

    make

To run the executable on an example file, type

    ./asfparse example.asf

To remove the executable and objects in the current directory, type

    make clean
