# Simulator of THUMB mode ARM - Architecture of Computers 

This project is intended to simulate a ARM processor core in THUMB mode.

Provided with a file with the binary codes of an arm program, it should simulate and show the final state of the processor after its execution is finished or when the `BKPT` instruction is executed.

## Run

For this program you need to use the gcc version 8.0 or early and should be able the flags `-stdc++20` or `-stdc++2a` in Makefile.

For build this project you need to run `make` in project folder and after run `./ThumbSimulator filename.ext`.