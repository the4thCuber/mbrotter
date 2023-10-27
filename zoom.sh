#!/bin/bash

start=$EPOCHREALTIME
width=1280
height=720 #Remember to also change size in the ffmpeg command
max_loop=70000
xcenter=0.432539867562512
ycenter=0.226118675951765
num_frames=5000
zoom_i=-2.4
zoom_f=-14.3

rm -r -f images
mkdir images
make
./mbrotter $width $height $xcenter $ycenter $zoom_i $zoom_f $num_frames $max_loop
ffmpeg -f image2 -framerate 30 -i images/%04d.png -s 1280x720 fawptywgrous.mp4
#rm -r images

echo "$EPOCHREALTIME-$start" | bc -l
