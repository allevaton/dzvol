//
// TODO description
//
// Public domain.
//
#include <string.h>

#include <alsa/asoundlib.h>
#include <X11/Xlib.h>

int HEIGHT = 64;
int WIDTH  = 256;

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

    return 0;
}
