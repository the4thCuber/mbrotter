# Mbrotter v0.1.2 (27 Oct 2023)
---
This program generates a series of images of fractals that are then converted to video.  
[Description of the Mandelbrot Set](https://en.wikipedia.org/wiki/Mandelbrot_set)     
To see an example of this program, watch [this playlist](https://www.youtube.com/playlist?list=PL5jVFBHrC0F-W4pdNcpXEOrn2nLp5iJCm).

## Dependencies:
* a C compiler to compile from source (gcc is specified in the makefile)
* ffmpeg (you could potentially edit some parts of the code to not use
	ffmpeg if it is not available on your machine)
* make
---
## Editing configurations:
In _config.h_, all the computation-specific options are #defined. Edit _config.h_
to change these options. The options for rendering are in the file _zoom.sh_.
* Rshift/gshift/bshift: Control the increments for the R, G, and B components
of the palette. They should be around 1-10, depending on the number of iterations
and how far of a zoom you are doing, and should be coprime and unequal unless
repetitive coloring is desired (e.g. 3.7, 4.1, and 4.3)      
Some of the below terms might require explanations for users not entirely familiar
with the Mandelbrot Set and fractal rendering. Go [here](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set)
for explanations.
* Bailout: How far to compute the pixel before "giving up" on it. Mathematically,
4 is the optimal setting, but in practice a higher number is needed to improve and
smooth the coloring. Default value is 400.
* Maxperiod: Periodicity checking. Set to maxloop to turn off periodicity checking.
Default value is 25, turn off if there aren't many large black areas in the picture
* Iterscaling: Scale palette to this power of log(iter), controls width of "color bands".
Value of 1 provides least overhead, 0 corresponds to a uniform coloring. Values above 
1 provide more visible bands and transitions between the colors, especially with large 
values for rgbshifts. Default value is 3/4.
  ### _zoom.sh_ settings:
* Max_loop: How far to iterate points. For very short zooms, it shouldn't need to go
above 500-5k, but for farther zooms, it could be necessary to go as high as 5m-50m.
Decrease this value to shorten computing time, increase it to get more detail in the
black areas. Default value is 4000.
* Width/height of generated images.
* Xcenter/ycenter: Center the program will zoom into. Use an online explorer to find a
good value, should stay in the range ([-2,.5],[-1,1]).
* Num_frames: Number of frames. 3000-9000 gives a video length of 1:40-5:00 at 30fps.
* Zoom_i/zoom_f: intial and final zoom levels, in log base 10 form.      
Note: You must carefully pick the framerate, number of frames, and initial/final zoom so that
the zooming action in the video is not too slow or too fast.
---
# Changelog:
* 0.1.1 - 17 Sep 2023: Initialize
* 0.1.2 - 27 Oct 2023: Check everything over, add progress bar

> Released under the GPL3 license by the4thCuber
