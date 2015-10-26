#!/bin/sh
mkdir -p build
pushd build
cmake ../src && make -j &&echo "Compile Success!!!"
popd
