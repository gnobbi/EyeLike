cd %CD%
rd /q /s build

mkdir build
cd build
cmake -G "Visual Studio 14 2015 Win64" .. 

cd ..