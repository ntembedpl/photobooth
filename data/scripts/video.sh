#!/bin/bash
cd ./data/videos
cp ./vid$1.avi ../Screen1/$2/s1/vid.avi
cp ./vid$1.avi ../Screen2/$2/s1/vid.avi
cd ..
cd ..
cd ./data/videos
cp ./imageV_$1.png ../Screen1/$2/s3/imgVid_0.png
cd ..
cd ..
