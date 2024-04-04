# Instructions for Compiling and Running Susan
## Introduction
Welcome to SUSAN, a powerful image processing tool renowned for its ability to reduce noise while preserving essential structures in both 2D and 3D images. This guide will walk you through compiling SUSAN, providing step-by-step instructions to effectively utilize its advanced functionalities for precise noise reduction.

For more information about susan and related tools, visit the FMRIB Software Library (FSL) website:[FSL Git Repository](https://git.fmrib.ox.ac.uk/fsl) and you can also find additional resources and documentation on susan on the FSL wiki page: [susan Documentation](https://fsl.fmrib.ox.ac.uk/fsl/fslwiki/SUSAN).
## Clone the Repository

Begin by cloning the project repository from GitHub onto your local machine. You can do this by running the following command in your terminal or command prompt:

```bash
git clone https://github.com/Bostrix/FSL-susan.git
```
This command will create a local copy of the project in a directory named "FSL-susan".

## Navigate to Project Directory
Change your current directory to the newly cloned project directory using the following command:
```bash
cd FSL-susan
```
## Installing Dependencies
To install the necessary dependencies for compiling and building the project, follow these steps:
```bash
sudo apt-get update
sudo apt install g++
sudo apt install make
sudo apt-get install libboost-all-dev
sudo apt-get install libblas-dev libblas3
sudo apt-get install liblapack-dev liblapack3
sudo apt-get install zlib1g zlib1g-dev
```

## Compilation
To compile susan, follow these steps:

- Ensure correct path in Makefile:
After installing the necessary tools, verify correct path in the makefile to include additional LDFLAGS for the required libraries. For instance, if utilizing the znzlib library, ensure that the correct path is present in the makefile.
Make sure `$(ZNZLIB_LDFLAGS)` are included in the compile step of the makefile.

- Compiling: 
Execute the appropriate compile command to build the susan tool.
```bash
make clean
make
```
- Resolving Shared Library Errors
When running an executable on Linux, you may encounter errors related to missing shared libraries.This typically manifests as messages like:
```bash
./susan: error while loading shared libraries: libexample.so: cannot open shared object file:No such file or directory
```
To resolve these errors,Pay attention to the names of the missing libraries mentioned in the error message.Locate the missing libraries on your system. If they are not present, you may need to install the corresponding packages.If the libraries are installed in custom directories, you need to specify those directories using the `LD_LIBRARY_PATH` environment variable. For example:
```bash
export LD_LIBRARY_PATH=/path/to/custom/libraries:$LD_LIBRARY_PATH
```
Replace `/path/to/custom/libraries` with the actual path to the directory containing the missing libraries.Once the `LD_LIBRARY_PATH` is set, attempt to run the executable again.If you encounter additional missing library errors, repeat steps until all dependencies are resolved.

- Resolving "The environment variable FSLOUTPUTTYPE is not defined" errors
If you encounter an error related to the FSLOUTPUTTYPE environment variable not being set.Setting it to `NIFTI_GZ` is a correct solution, as it defines the output format for FSL tools to NIFTI compressed with gzip.Here's how you can resolve:
```bash
export FSLOUTPUTTYPE=NIFTI_GZ
```
By running this command, you've set the `FSLOUTPUTTYPE` environment variable to `NIFTI_GZ`,which should resolve the error you encountered.


## Running Susan

After successfully compiling, you can run Susan by executing:
```bash
./susan <input> <bt> <dt> <dim> <use_median> <n_usans> [<usan1> <bt1> [<usan2> <bt2>]] <output>
```
This command will execute the susan tool.
