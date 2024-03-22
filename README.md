# Instructions for Compiling and Running Susan

## Preparing the Environment

1. First, ensure that your environment is clean by executing the following command:
    ```
    make clean
    ```

2. Modify the makefile to set the path for `znzlib` in `znzlib_ldflags`.

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


## Compiling

Once the dependencies are installed and the makefile is modified, you can proceed with compilation by running:
```
make
```

## Running Susan

After successfully compiling, you can run Susan by executing:
```
./susan
```

This will execute the Susan program.
