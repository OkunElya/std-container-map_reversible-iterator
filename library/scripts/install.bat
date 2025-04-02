@echo off
Pushd "%~dp0"
cd .. 
cd build
make install
popd