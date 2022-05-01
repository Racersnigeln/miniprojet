#ifndef MUSIC_H
#define MUSIC_H

#define MUSIC_SIZE 8  //attention a changer

typedef struct {
  uint16_t rythm [MUSIC_SIZE] ;     //en ms
  uint16_t notes [MUSIC_SIZE] ;     //en note (voir play_melody.h)
} Music; 

Music NO_MUSIC (void);

Music MARSEILLAISE (void);

Music TEST (void) ;

#endif /*   MUSIC_H */
