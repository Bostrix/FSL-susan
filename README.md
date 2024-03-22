# Instructions for Compiling and Running Susan

## Installing Dependencies

Before compiling, make sure you have the following dependencies installed:

- Blas
- Lapack
- zlib

You can install these dependencies on Ubuntu using the following commands:

```bash
sudo apt-get install libblas-dev libblas3
sudo apt-get install liblapack-dev liblapack3
sudo apt-get install zlib1g zlib1g-dev
```
## Preparing the Environment

1. Modify the makefile to set the path for `znzlib` in `ZNZLIB_LDFLAGS`.
Open the makefile and find the ZNZLIB_LDFLAGS line. Modify it to set the path to your znzlib. 
```bash
ZNZLIB_LDFLAGS = -L/path/to/your/znzlib -lfsl-znz
```
Replace `/path/to/your/znzlib` with the actual path to your znzlib directory.

2. Before compiling, ensure that your environment is clean by executing the following command
```bash
make clean
```

## Compiling

Once the dependencies are installed and the makefile is modified, you can proceed with compilation by running:
```
make
```

## Running Susan

After successfully compiling, you can run Susan by executing:
```
./susan <input> <bt> <dt> <dim> <use_median> <n_usans> [<usan1> <bt1> [<usan2> <bt2>]] <output>
```

This will execute the Susan program.
