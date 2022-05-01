#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include <usbcfg.h>

#include <dance.h>
#include <audio/play_melody.h>

#include <music.h>

Music NO_MUSIC (void)
{
    Music song = {{100},{0}} ;
    return song ;
}

Music MARSEILLAISE (void)
{
    Music song = {{0},{0}} ;
    
    return song ;
}

Music TEST (void)
{
    Music song = {{100},{0}} ;

    song.rythm [0] = 500;
    song.rythm [1] = 1000;
    song.rythm [2] = 1000;

    song.notes [0] = NOTE_G3;
    song.notes [1] = NOTE_A3;
    song.notes [2] = NOTE_B3;

    return song ;
}




