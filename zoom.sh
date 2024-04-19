#!/bin/bash

start=$EPOCHREALTIME
width=1360
height=768 #Remember to also change size in the ffmpeg command
max_loop=27000
xcenter=-1.352945477964
ycenter=0.067181723195
num_frames=5900
zoom_i=-2.5
zoom_f=-14

rm -r -f images
mkdir images
make
./mbrotter $width $height $xcenter $ycenter $zoom_i $zoom_f $num_frames $max_loop
ffmpeg -f image2 -framerate 30 -i images/%04d.png -s 1360x768 nahwioroiegs.mp4
#rm -r images

make clean
