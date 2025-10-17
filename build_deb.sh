#!/bin/sh
mkdir build
cd build
cmake -DE57_BUILD_SHARED:BOOL=ON ..
cmake --build . --config Release
cpack -G DEB

