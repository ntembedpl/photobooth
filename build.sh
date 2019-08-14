#!/bin/bash

git reset --hard
git pull

cd build
cmake ..
make
cp ./photobooth ..
cd ..

sudo ./photobooth
