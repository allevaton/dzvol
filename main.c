//
// TODO description
//
// Public domain.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <alsa/asoundlib.h>
#include <X11/Xlib.h>

#define _BSD_SOURCE

int WIDTH  = 256;
int HEIGHT = 64;

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
        X = (screen->width/2) - WIDTH;

    if(Y == -1)
        Y = (screen->height/2) - HEIGHT;

    pid_t pid;
    int mypipe[2];

    if(pipe(mypipe))
    {
        fprintf(stderr, "Could not open a pipe");
        return -1;
    }

    pid = fork();

    FILE* stream = popen("dzen2 -p -ta l -w 256 -h 32 -x 400 -y 900 -bg '#222222'", "w");

    for(int i = 0; i < 150; i++)
    {
        fprintf(stream, "   V [ ^r(%dx11) ] ^pa(+200X;)100%%^pa()\n", i);
    }

    pclose(stream);
    close(mypipe);

    return 0;
}
