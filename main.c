//
// TODO description
//
// Public domain.
//

#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <alsa/asoundlib.h>
#include <X11/Xlib.h>

#define _BSD_SOURCE

int WIDTH  = 258;
int HEIGHT = 32;

// -1 means center of the screen
int X = -1;
int Y = -1;

int main(int argc, char* argv[])
{
    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-v") == 0 ||
           strcmp(argv[i], "--version") == 0)
        {
            puts("dzvol: 1.0");
            return 0;
        }

        if(strcmp(argv[i], "-h") == 0 ||
           strcmp(argv[i], "--help") == 0)
        {
            // TODO help docs
        }
    }

    // get X and Y
    Display* xdisp = XOpenDisplay(NULL);
    Screen* screen = DefaultScreenOfDisplay(xdisp);

    if(X == -1)
        X = (screen->width/2) - (WIDTH/2);

    if(Y == -1)
        Y = (screen->height/2) - HEIGHT;

    char* command = malloc(sizeof(char) * 256);

    sprintf(command, "dzen2 -p -ta l -x %d -y %d -w %d -h %d -bg '#222222'", X, Y, WIDTH, HEIGHT);

    FILE* stream = popen(command, "w");

    free(command);

    for(int i = 0; i < 150; i++)
    {
        fprintf(stream, "^pa(+20X)♪^pa()  ^r(%dx11) ^pa(+200X;)100%%^pa()\n", i);
    }

    pclose(stream);

    return 0;
}
