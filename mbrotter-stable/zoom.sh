#!/bin/bash

start=$EPOCHREALTIME
width=1280
height=720 #Remember to also change size in the ffmpeg command
max_loop=4000
xcenter=-1.96681472723463
ycenter=0.000010017592
num_frames=7500
zoom_i=-2.4
zoom_f=-14.5

rm -r -f images
mkdir images
make
./mbrotter $width $height $xcenter $ycenter $zoom_i $zoom_f $num_frames $max_loop
ffmpeg -f image2 -framerate 30 -i images/%04d.ppm -s 1280x720 pbqfsyeufr.mp4
#rm -r images

echo "$EPOCHREALTIME-$start" | bc -l
