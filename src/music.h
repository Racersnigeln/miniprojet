#ifndef MUSIC_H
#define MUSIC_H

// Not all functions are declared here, 
// only the ones that should be usable elsewhere
 
#define MUSIC_SIZE 55

typedef struct {
  uint16_t rythm [MUSIC_SIZE] ;     //in ms
  uint16_t notes [MUSIC_SIZE] ;     //in frequence (see play_melody.h for the notes)
} Music; 

Music LUT_flag_to_music (Flag country);

void init_songs(void);

#endif /* MUSIC_H */
