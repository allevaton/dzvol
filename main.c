//
// TODO description
//
// Public domain.
//

#define _DEFAULT_SOURCE

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <alsa/asoundlib.h>
#include <X11/Xlib.h>

#define _BSD_SOURCE

int WIDTH  = 256;
int HEIGHT = 32;

// -1 means center of the screen
int X = -1;
int Y = -1;

const char *ATTACH = "default";
const snd_mixer_selem_channel_id_t CHANNEL = SND_MIXER_SCHN_FRONT_LEFT;
const char *SELEM_NAME = "Master";

void get_volume(float* vol, int* switch_value);

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

        // TODO more parameters!
    }

    // get X and Y
    Display* xdisp = XOpenDisplay(NULL);
    Screen* screen = DefaultScreenOfDisplay(xdisp);

    // screw division, bit shift to the right
    if(X == -1)
        X = (screen->width >> 1) - WIDTH;

    if(Y == -1)
        Y = (screen->height >> 1) - HEIGHT;

    HEIGHT = 64;
    WIDTH = 512;

    // calculate the progress bar width and height from a base percentage
    long pbar_height = lround(HEIGHT * 0.34);
    long pbar_max_width = lround(WIDTH * 0.586);
    long ltext_x = lround(WIDTH * 0.078);
    long rtext_x = lround(WIDTH * 0.78);

    char* command = malloc(sizeof(char) * 256);
    sprintf(command, "dzen2 -p -ta l -x %d -y %d -w %d -h %d -bg '#222222'", X, Y, WIDTH, HEIGHT);

    FILE* stream = popen(command, "w");

    free(command);

    float prev_vol = -1;
    int prev_switch_value;

    // TODO time sensitive delay, not infinite loop
    while(1)
    {
        float vol;
        int switch_value;

        get_volume(&vol, &switch_value);

        if(prev_vol != vol || prev_switch_value != switch_value)
        {
            char* string = malloc(sizeof(char) * 512);
            sprintf(string, "^pa(+%ldX)♪^pa()  ^r%s(%ldx%ld) ^pa(+%ldX)%3.0f%%^pa()\n",
                    ltext_x, (switch_value == 1) ? "" : "o",
                    lround(pbar_max_width * vol), pbar_height, rtext_x, vol*100);
            fprintf(stream, string);
            fflush(stream);
            free(string);

            prev_vol = vol;
            prev_switch_value = switch_value;
        }

        usleep(1000);
    }

    pclose(stream);

    return 0;
}

void error_close_exit(char *errmsg, int err, snd_mixer_t* h_mixer)
{
    if(err == 0)
        fprintf(stderr, errmsg);
    else
        fprintf(stderr, errmsg, snd_strerror(err));

    if(h_mixer != NULL)
        snd_mixer_close(h_mixer);

    exit(EXIT_FAILURE);
}

void get_volume(float* vol, int* switch_value)
{
    int err;
    long volume, vol_min, vol_max;

    snd_mixer_t* h_mixer;
    snd_mixer_selem_id_t* sid;
    snd_mixer_elem_t* elem ;

    if ((err = snd_mixer_open(&h_mixer, 1)) < 0)
        error_close_exit("Mixer open error: %s\n", err, NULL);

    if ((err = snd_mixer_attach(h_mixer, ATTACH)) < 0)
        error_close_exit("Mixer attach error: %s\n", err, h_mixer);

    if ((err = snd_mixer_selem_register(h_mixer, NULL, NULL)) < 0)
        error_close_exit("Mixer simple element register error: %s\n", err, h_mixer);

    if ((err = snd_mixer_load(h_mixer)) < 0)
        error_close_exit("Mixer load error: %s\n", err, h_mixer);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, SELEM_NAME);

    if ((elem = snd_mixer_find_selem(h_mixer, sid)) == NULL)
        error_close_exit("Cannot find simple element\n", 0, h_mixer);

    snd_mixer_selem_get_playback_volume(elem, CHANNEL, &volume);
    snd_mixer_selem_get_playback_volume_range(elem, &vol_min, &vol_max);
    snd_mixer_selem_get_playback_switch(elem, CHANNEL, switch_value);

    *vol = volume / (float)vol_max;

    snd_mixer_close(h_mixer);
    //usleep(50000);
}
