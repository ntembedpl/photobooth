#!/bin/bash

#git reset --hard
#git pull

cd build
cmake ..
make
cp ./operator_HMI ..
cd ..

sudo ./operator_HMI
