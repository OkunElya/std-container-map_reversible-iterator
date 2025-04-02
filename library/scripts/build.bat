@echo off
Pushd "%~dp0"
cd .. 
mkdir build
cd build
:: at the moment of creating this proj i'm used to gcc as a main compiler so let it be so
cmake -G "MSYS Makefiles" -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ .. 
make 
popd