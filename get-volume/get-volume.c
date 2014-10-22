// get-volume is a small utility for ALSA mixer volume, written for being used
// in Conky.
//
// This code is in Public Domain
//
// Reference:
//  http://www.alsa-project.org/alsa-doc/alsa-lib/index.html
//
// Author:
//  2009 Yu-Jie Lin
//  2014 Modified by Nick Allevato
//
// Compile using:
//  gcc -lasound -o get-volume get-volume.c

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <alsa/asoundlib.h>

const char *ATTACH = "default";
const snd_mixer_selem_channel_id_t CHANNEL = SND_MIXER_SCHN_FRONT_LEFT;
const char *SELEM_NAME = "Master";

void error_close_exit(char *errmsg, int err, snd_mixer_t *h_mixer) {
    if (err == 0)
        fprintf(stderr, errmsg);
    else
        fprintf(stderr, errmsg, snd_strerror(err));
    if (h_mixer != NULL)
        snd_mixer_close(h_mixer);
    exit(EXIT_FAILURE);
}

int print(long vol, long vol_min, long vol_max, int switch_value)
{
    return printf("%3.0f%% %s\n", 100.0 * vol / vol_max, (switch_value == 1) ? "ON" : "OFF");
}

int main(int argc, char** argv) {
    long prev_vol = 0;
    int prev_switch_value = 0;

    while(1)
    {
        int err;
        long vol;
        long vol_min, vol_max;
        int switch_value;
        snd_mixer_t *h_mixer;
        snd_mixer_selem_id_t *sid;
        snd_mixer_elem_t *elem ;

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

        snd_mixer_selem_get_playback_volume(elem, CHANNEL, &vol);
        snd_mixer_selem_get_playback_volume_range(elem, &vol_min, &vol_max);
        snd_mixer_selem_get_playback_switch(elem, CHANNEL, &switch_value);

        if(prev_vol != vol || prev_switch_value != switch_value)
            printf("%3.0f%% %s\n", 100.0 * vol / vol_max, (switch_value == 1) ? "ON" : "OFF");

        prev_vol = vol;
        prev_switch_value = switch_value;

        snd_mixer_close(h_mixer);
        usleep(50000);
    }
    return 0;
}
