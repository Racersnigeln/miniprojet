#ifndef MUSIC_H
#define MUSIC_H

#define NOTE_TO_MS 15000    // nbr_seconds_in_one_minute/NOIRE => 60000/4 

#define SILENCE 0

#define DOUBLE_CROCHE   1
#define CROCHE          2 
#define CROCHE_POINTEE  3
#define NOIRE           4
#define NOIRE_POINTEE   6
#define BLANCHE         8

#define MUSIC_SIZE 55

typedef struct {
  uint16_t rythm [MUSIC_SIZE] ;     //in ms
  uint16_t notes [MUSIC_SIZE] ;     //in frequence (see play_melody.h for the notes)
} Music; 

Music NO_MUSIC (void);

Music MARSEILLAISE (void);

Music BELLA_CIAO (void);

Music WII_THEME (void);

Music LA_DANSE_DES_CANARDS (void) ;

#endif /* MUSIC_H */
