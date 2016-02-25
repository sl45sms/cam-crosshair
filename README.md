# cam-crosshair
overlay crosshair to camera stream

###combile
gcc cam-crosshair.c `pkg-config --libs --cflags opencv` -o cam-crosshair
./cam-crosshair
