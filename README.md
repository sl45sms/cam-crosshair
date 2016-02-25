# cam-crosshair
overlay crosshair to camera stream

###compile
gcc cam-crosshair.c `pkg-config --libs --cflags opencv` -o cam-crosshair
./cam-crosshair
