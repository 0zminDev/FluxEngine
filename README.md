# How to build

install ninja cmake and clang

mkdir build/bin/windows

cd build
cmake ..\..\ -G "Ninja" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
cd ..

Add rootfolder to path

FlUxBuild build to build
FluxBuild run to run
