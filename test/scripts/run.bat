@echo off
Pushd "%~dp0"
cd .. 
mkdir build
cd build
container_map_test.exe
popd