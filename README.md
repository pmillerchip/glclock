# glclock
Simple SDL / OpenGL clock that prints times down to milliseconds.

This clock is meant for use in testing latency in video capture
systems. Display your camera's output and this clock on the same
screen, and then take a screenshot. The difference in times
displayed shows your system's latency.

The program depends on SDL 1.2 and SDL_ttf. Under Ubuntu, install
the following packages:

libsdl1.2-dev
libsdl-ttf2.0-dev

The clock prints the time in milliseconds, followed by a "frame"
value which represents the number of PAL video frames that would
have elapsed by this point. If your video capture system uses
a different video framerate, simply adjust the divider
appropriately in the code.

The clock will wrap its timers every 100 seconds because it's
not designed to time any events longer than that. For measuring
latency this is more than sufficient.

