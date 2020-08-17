rm -Rf build
mkdir build
cd build
cmake ../src
make
make install CMAKE_INSTALL_PREFIX=$PREFIX
