dzvol
=====

dzen2 volume monitor inspired by
[bruenig's post on the Arch forums](https://bbs.archlinux.org/viewtopic.php?id=46608).

Alsa mixer volume code obtained from
[this code](https://code.google.com/p/yjl/source/browse/Miscellaneous/get-volume.c).

Screenshot
----------
![dzvol screenshot](screenshot.png)

Arguments to get this look would be:

    dzvol -bg '#222222' -fg '#FFFFFF' -fn 'Deja Vu Sans Mono 12'

Why make *another* one?
-----------------------
I use [i3wm](http://i3wm.org/) and have a 1 second refresh rate on my
status bar. Whenever I want to adjust my volume, I have to hold down my
volume keys, then wait a second or two to see what the percentage is, and
I didn't want a big interface to handle it for me, like KMix.

Searching for an existing one, I came across
[bruenig's post on the Arch Linux forums](https://bbs.archlinux.org/viewtopic.php?id=46608).
It looked good, but it didn't work how I imagined. I wanted one that can adjust in real-time
to the changing volume. I couldn't find any that existed, so I made dzvol.

Command Line Paramters
----------------------
Most command line parameters are similar to that of dzen2, and work the same way.
Some parameters are sent directly to dzen2 for interpretation.

There *are* some custom ones, which I'll go over here:

|argument|description|
|--------|-----------|
|--help  | Show the help message and exit.|
|-x X    | Adjust the X position of the window manually. If left default (-1), it will center based on your screen dimensions.|
|-y Y    | Adjust the Y position of the window manually. If left default (-1), it will center based on your screen dimensions.|
|-w WIDTH| Adjust the width of the window manually (default is 256). The progress bar and text placement should scale keeping preservation of proportions.|
|-h HEIGHT|Adjust the height of the window (default is 32). Also keeps preservation of proportions.|
|-d, --delay |Sets the time it takes to exit when the volume hasn't changed. Defaults to 2 seconds.|
|-bg COLOR | Sets the background color. This should be in the same format dzen2 would accept.|
|-fg COLOR | Sets the foreground color. This should be in the same format dzen2 would accept.|
|-fn FONT  | Sets the font. This should be in the same format dzen2 would accept.|
|-i TEXT   | Sets the icon text/character on the left. Defaults to a music note seen in the screenshot. |
|-s, --speed | Speed in microseconds to poll ALSA for volume. The higher the value, the slower the polling, the lower the value, the faster the polling. Values below 20000 begin to cause high CPU usage. Defaults to 50000.|
