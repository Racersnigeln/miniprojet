#include <ch.h>
#include <hal.h>

#include <dance.h>              // For Music type 
#include <audio/play_melody.h>  // For definition of notes
#include <music.h>

Music NO_MUSIC (void)
{
    Music song = {{0},{0}} ;
    return song ;
}

Music MARSEILLAISE (void)
{
    Music song = {{0},{0}} ;

    uint16_t tempo = 110 ;     // noire = 110

    song.rythm [0]  = DOUBLE_CROCHE ;
    song.notes [0]  = NOTE_D3;

    song.rythm [1]  = CROCHE_POINTEE ;
    song.notes [1]  = NOTE_D3;

    song.rythm [2]  = DOUBLE_CROCHE ;
    song.notes [2]  = NOTE_D3;

    song.rythm [3]  = NOIRE ;
    song.notes [3]  = NOTE_G3;

    song.rythm [4]  = NOIRE;
    song.notes [4]  = NOTE_G3;

    song.rythm [5]  = NOIRE;
    song.notes [5]  = NOTE_A3;
    
    song.rythm [6]  = NOIRE;
    song.notes [6]  = NOTE_A3;
    
    song.rythm [7]  = NOIRE_POINTEE;
    song.notes [7]  = NOTE_D4;
    
    song.rythm [8]  = CROCHE;
    song.notes [8]  = NOTE_B3;

    song.rythm [9]  = CROCHE;
    song.notes [9]  = NOTE_G3;
    
    song.rythm [10]  = DOUBLE_CROCHE ;
    song.notes [10]  = SILENCE;

    song.rythm [11]  = DOUBLE_CROCHE;
    song.notes [11]  = NOTE_G3;

    song.rythm [12]  = CROCHE_POINTEE;
    song.notes [12]  = NOTE_B3;

    song.rythm [13]  = DOUBLE_CROCHE;
    song.notes [13]  = NOTE_G3;

    song.rythm [14]  = NOIRE;
    song.notes [14]  = NOTE_E3;

    song.rythm [15]  = BLANCHE;
    song.notes [15]  = NOTE_C4;

    song.rythm [16]  = CROCHE_POINTEE;
    song.notes [16]  = NOTE_A3;

    song.rythm [17]  = DOUBLE_CROCHE;
    song.notes [17]  = NOTE_FS3;

    song.rythm [18]  = BLANCHE;
    song.notes [18]  = NOTE_G3;

    song.rythm [19]  = NOIRE;
    song.notes [19]  = SILENCE;

    song.rythm [20]  = CROCHE_POINTEE;
    song.notes [20]  = NOTE_G3;

    song.rythm [21]  = DOUBLE_CROCHE;
    song.notes [21]  = NOTE_A3;

    song.rythm [22]  = NOIRE;
    song.notes [22]  = NOTE_B3;

    song.rythm [23]  = NOIRE;
    song.notes [23]  = NOTE_B3;

    song.rythm [24]  = NOIRE;
    song.notes [24]  = NOTE_B3;

    song.rythm [25]  = CROCHE_POINTEE;
    song.notes [25]  = NOTE_C4;

    song.rythm [26]  = DOUBLE_CROCHE;
    song.notes [26]  = NOTE_B3;

    song.rythm [27]  = NOIRE;
    song.notes [27]  = NOTE_B3;

    song.rythm [28]  = NOIRE;
    song.notes [28]  = NOTE_A3;

    song.rythm [29]  = NOIRE;
    song.notes [29]  = SILENCE;

    song.rythm [30]  = CROCHE_POINTEE;
    song.notes [30]  = NOTE_A3;

    song.rythm [31]  = DOUBLE_CROCHE;
    song.notes [31]  = NOTE_B3;

    song.rythm [32]  = NOIRE;
    song.notes [32]  = NOTE_C4;

    song.rythm [33]  = NOIRE;
    song.notes [33]  = NOTE_C4;

    song.rythm [34]  = NOIRE;
    song.notes [34]  = NOTE_C4;

    song.rythm [35]  = CROCHE_POINTEE;
    song.notes [35]  = NOTE_D4;

    song.rythm [36]  = DOUBLE_CROCHE;
    song.notes [36]  = NOTE_C4;

    song.rythm [37]  = BLANCHE;
    song.notes [37]  = NOTE_B3;

    song.rythm [38]  = NOIRE;
    song.notes [38]  = SILENCE;

    song.rythm [39]  = CROCHE_POINTEE;
    song.notes [39]  = NOTE_D4;

    song.rythm [40]  = DOUBLE_CROCHE;
    song.notes [40]  = NOTE_D4;

    song.rythm [41]  = NOIRE;
    song.notes [41]  = NOTE_D4;

    song.rythm [42]  = CROCHE_POINTEE;
    song.notes [42]  = NOTE_B3;

    song.rythm [43]  = DOUBLE_CROCHE;
    song.notes [43]  = NOTE_G3;

    song.rythm [44]  = NOIRE;
    song.notes [44]  = NOTE_D4;

    song.rythm [45]  = CROCHE_POINTEE;
    song.notes [45]  = NOTE_B3;

    song.rythm [46]  = DOUBLE_CROCHE;
    song.notes [46]  = NOTE_G3;

    song.rythm [47]  = CROCHE;
    song.notes [47]  = NOTE_D3;

    song.rythm [48]  = DOUBLE_CROCHE;
    song.notes [48]  = NOTE_D3;

    song.rythm [49]  = DOUBLE_CROCHE;
    song.notes [49]  = NOTE_D3;

    song.rythm [50]  = CROCHE;
    song.notes [50]  = NOTE_DS3;

    song.rythm [51]  = CROCHE;
    song.notes [51]  = NOTE_D3;

    song.rythm [52]  = CROCHE;
    song.notes [52]  = SILENCE;

    song.rythm [53]  = CROCHE;
    song.notes [53]  = NOTE_FS3;

    song.rythm [54]  = CROCHE;
    song.notes [54]  = NOTE_G3;
    
    // convertir les notes en milliseconde
    for (uint8_t i=0; i < MUSIC_SIZE; ++i)
    {
        song.rythm [i] *= NOTE_TO_MS / tempo ;
    }
    
    return song ;
}

Music BELLA_CIAO (void) 
{
    Music song = {{0},{0}} ;

    uint16_t tempo = 136 ;      //noire = 136

    song.rythm [0]  = CROCHE ;
    song.notes [0]  = NOTE_E3;

    song.rythm [1]  = CROCHE ;
    song.notes [1]  = NOTE_A3;

    song.rythm [2]  = CROCHE ;
    song.notes [2]  = NOTE_B3;

    song.rythm [3]  = CROCHE ;
    song.notes [3]  = NOTE_C4;

    song.rythm [4]  = NOIRE;
    song.notes [4]  = NOTE_A3;

    song.rythm [5]  = NOIRE;
    song.notes [5]  = SILENCE;
    
    song.rythm [6]  = CROCHE;
    song.notes [6]  = NOTE_E3;
    
    song.rythm [7]  = CROCHE;
    song.notes [7]  = NOTE_A3;
    
    song.rythm [8]  = CROCHE;
    song.notes [8]  = NOTE_B3;

    song.rythm [9]  = CROCHE;
    song.notes [9]  = NOTE_C4;
    
    song.rythm [10]  = NOIRE ;
    song.notes [10]  = NOTE_A3;

    song.rythm [11]  = NOIRE;
    song.notes [11]  = SILENCE;

    song.rythm [12]  = CROCHE;
    song.notes [12]  = NOTE_E3;

    song.rythm [13]  = CROCHE;
    song.notes [13]  = NOTE_A3;

    song.rythm [14]  = CROCHE;
    song.notes [14]  = NOTE_B3;

    song.rythm [15]  = NOIRE;
    song.notes [15]  = NOTE_C4;

    song.rythm [16]  = CROCHE;
    song.notes [16]  = NOTE_B3;

    song.rythm [17]  = CROCHE;
    song.notes [17]  = NOTE_A3;

    song.rythm [18]  = NOIRE;
    song.notes [18]  = NOTE_C4;

    song.rythm [19]  = CROCHE;
    song.notes [19]  = NOTE_B3;

    song.rythm [20]  = CROCHE;
    song.notes [20]  = NOTE_A3;

    song.rythm [21]  = NOIRE;
    song.notes [21]  = NOTE_E4;

    song.rythm [22]  = NOIRE;
    song.notes [22]  = NOTE_E4;

    song.rythm [23]  = NOIRE;
    song.notes [23]  = NOTE_E4;

    song.rythm [24]  = CROCHE;
    song.notes [24]  = NOTE_D4;

    song.rythm [25]  = CROCHE;
    song.notes [25]  = NOTE_E4;

    song.rythm [26]  = CROCHE;
    song.notes [26]  = NOTE_F4;

    song.rythm [27]  = NOIRE;
    song.notes [27]  = NOTE_F4;

    song.rythm [28]  = NOIRE;
    song.notes [28]  = SILENCE;

    song.rythm [29]  = CROCHE;
    song.notes [29]  = NOTE_F4;

    song.rythm [30]  = CROCHE;
    song.notes [30]  = NOTE_E4;

    song.rythm [31]  = CROCHE;
    song.notes [31]  = NOTE_D4;

    song.rythm [32]  = CROCHE;
    song.notes [32]  = NOTE_F4;

    song.rythm [33]  = NOIRE;
    song.notes [33]  = NOTE_E4;

    song.rythm [34]  = NOIRE;
    song.notes [34]  = SILENCE;

    song.rythm [35]  = CROCHE;
    song.notes [35]  = NOTE_E4;

    song.rythm [36]  = CROCHE;
    song.notes [36]  = NOTE_D4;

    song.rythm [37]  = CROCHE;
    song.notes [37]  = NOTE_C4;

    song.rythm [38]  = NOIRE;
    song.notes [38]  = NOTE_B3;

    song.rythm [39]  = NOIRE;
    song.notes [39]  = NOTE_E4;

    song.rythm [40]  = NOIRE;
    song.notes [40]  = NOTE_C4;

    song.rythm [41]  = NOIRE;
    song.notes [41]  = NOTE_B3;

    song.rythm [42]  = BLANCHE;
    song.notes [42]  = NOTE_A3;
    
    // convertir les notes en milliseconde
    for (uint8_t i=0; i < MUSIC_SIZE; ++i)
    {
        song.rythm [i] *= NOTE_TO_MS / tempo ;
    }
    
    return song ;
}

Music WII_THEME (void)
{
    Music song = {{0},{0}} ;

    uint16_t tempo = 114 ;     // noire = 114

    song.rythm [0]  = CROCHE ;
    song.notes [0]  = NOTE_FS3;

    song.rythm [1]  = CROCHE ;
    song.notes [1]  = SILENCE;

    song.rythm [2]  = CROCHE ;
    song.notes [2]  = NOTE_A3;

    song.rythm [3]  = CROCHE ;
    song.notes [3]  = NOTE_CS4;

    song.rythm [4]  = CROCHE;
    song.notes [4]  = SILENCE;

    song.rythm [5]  = CROCHE;
    song.notes [5]  = NOTE_A3;

    song.rythm [6]  = CROCHE;
    song.notes [6]  = SILENCE;

    song.rythm [7]  = CROCHE;
    song.notes [7]  = NOTE_FS3;

    song.rythm [8]  = CROCHE;
    song.notes [8]  = NOTE_D3;

    song.rythm [9]  = CROCHE;
    song.notes [9]  = NOTE_D3;

    song.rythm [10]  = CROCHE ;
    song.notes [10]  = NOTE_D3;

    song.rythm [11]  = BLANCHE;
    song.notes [11]  = SILENCE;

    song.rythm [12]  = CROCHE;
    song.notes [12]  = NOTE_CS3;

    song.rythm [13]  = CROCHE;
    song.notes [13]  = NOTE_D3;

    song.rythm [14]  = CROCHE;
    song.notes [14]  = NOTE_FS3;

    song.rythm [15]  = CROCHE;
    song.notes [15]  = NOTE_A3;

    song.rythm [16]  = CROCHE;
    song.notes [16]  = NOTE_CS4;

    song.rythm [17]  = CROCHE;
    song.notes [17]  = SILENCE;

    song.rythm [18]  = CROCHE;
    song.notes [18]  = NOTE_A3;

    song.rythm [19]  = CROCHE;
    song.notes [19]  = SILENCE;

    song.rythm [20]  = CROCHE;
    song.notes [20]  = NOTE_FS3;

    song.rythm [21]  = NOIRE_POINTEE;
    song.notes [21]  = NOTE_E4;

    song.rythm [22]  = CROCHE;
    song.notes [22]  = NOTE_DS4;

    song.rythm [23]  = CROCHE;
    song.notes [23]  = NOTE_D4;

    song.rythm [24]  = NOIRE_POINTEE;
    song.notes [24]  = SILENCE;

    song.rythm [25]  = CROCHE;
    song.notes [25]  = NOTE_GS3;

    song.rythm [26]  = CROCHE;
    song.notes [26]  = SILENCE;

    song.rythm [27]  = CROCHE;
    song.notes [27]  = NOTE_CS4;

    song.rythm [28]  = CROCHE;
    song.notes [28]  = NOTE_FS3;

    song.rythm [29]  = CROCHE;
    song.notes [29]  = SILENCE;

    song.rythm [30]  = CROCHE;
    song.notes [30]  = NOTE_CS4;

    song.rythm [31]  = CROCHE;
    song.notes [31]  = SILENCE;

    song.rythm [32]  = CROCHE;
    song.notes [32]  = NOTE_GS3;

    song.rythm [33]  = CROCHE;
    song.notes [33]  = SILENCE;

    song.rythm [34]  = CROCHE;
    song.notes [34]  = NOTE_CS4;

    song.rythm [35]  = CROCHE;
    song.notes [35]  = SILENCE;

    song.rythm [36]  = CROCHE;
    song.notes [36]  = NOTE_G3;

    song.rythm [37]  = CROCHE;
    song.notes [37]  = NOTE_FS3;

    song.rythm [38]  = CROCHE;
    song.notes [38]  = SILENCE;

    song.rythm [39]  = CROCHE;
    song.notes [39]  = NOTE_E3;

    song.rythm [40]  = CROCHE;
    song.notes [40]  = SILENCE;

    song.rythm [41]  = CROCHE;
    song.notes [41]  = NOTE_C3;

    song.rythm [42]  = CROCHE;
    song.notes [42]  = NOTE_C3;

    song.rythm [43]  = CROCHE;
    song.notes [43]  = NOTE_C3;

    song.rythm [44]  = NOIRE_POINTEE;
    song.notes [44]  = SILENCE;

    song.rythm [45]  = CROCHE;
    song.notes [45]  = NOTE_C3;

    song.rythm [46]  = CROCHE;
    song.notes [46]  = NOTE_C3;

    song.rythm [47]  = CROCHE;
    song.notes [47]  = NOTE_C3;

    song.rythm [48]  = BLANCHE;
    song.notes [48]  = SILENCE;

    song.rythm [49]  = CROCHE;
    song.notes [49]  = NOTE_AS3;

    song.rythm [50]  = CROCHE;
    song.notes [50]  = NOTE_B3;

    song.rythm [51]  = CROCHE;
    song.notes [51]  = NOTE_CS4;

    song.rythm [52]  = CROCHE;
    song.notes [52]  = NOTE_D4;

    song.rythm [53]  = CROCHE;
    song.notes [53]  = NOTE_FS4;

    song.rythm [54]  = CROCHE;
    song.notes [54]  = NOTE_A4;

    // convertir les notes en milliseconde
    for (uint8_t i=0; i < MUSIC_SIZE; ++i)
    {
        song.rythm [i] *= NOTE_TO_MS / tempo ;
    }

    return song ;
}

Music LA_DANSE_DES_CANARDS (void)
{
    Music song = {{0},{0}} ;

    uint16_t tempo = 192 ;     // blanche = 96

    song.rythm [0]  = CROCHE ;
    song.notes [0]  = NOTE_D4;

    song.rythm [1]  = CROCHE ;
    song.notes [1]  = NOTE_D4;

    song.rythm [2]  = CROCHE ;
    song.notes [2]  = NOTE_E4;

    song.rythm [3]  = CROCHE ;
    song.notes [3]  = NOTE_E4;

    song.rythm [4]  = CROCHE;
    song.notes [4]  = NOTE_B3;

    song.rythm [5]  = CROCHE;
    song.notes [5]  = NOTE_B3;

    song.rythm [6]  = NOIRE;
    song.notes [6]  = NOTE_D4;

    song.rythm [7]  = CROCHE;
    song.notes [7]  = NOTE_D4;

    song.rythm [8]  = CROCHE;
    song.notes [8]  = NOTE_D4;

    song.rythm [9]  = CROCHE;
    song.notes [9]  = NOTE_E4;

    song.rythm [10]  = CROCHE ;
    song.notes [10]  = NOTE_E4;

    song.rythm [11]  = CROCHE;
    song.notes [11]  = NOTE_B3;

    song.rythm [12]  = CROCHE;
    song.notes [12]  = NOTE_B3;

    song.rythm [13]  = NOIRE;
    song.notes [13]  = NOTE_D4;

    song.rythm [14]  = CROCHE;
    song.notes [14]  = NOTE_D4;

    song.rythm [15]  = CROCHE;
    song.notes [15]  = NOTE_D4;

    song.rythm [16]  = CROCHE;
    song.notes [16]  = NOTE_E4;

    song.rythm [17]  = CROCHE;
    song.notes [17]  = NOTE_E4;

    song.rythm [18]  = CROCHE;
    song.notes [18]  = NOTE_G4;

    song.rythm [19]  = CROCHE;
    song.notes [19]  = NOTE_G4;

    song.rythm [20]  = NOIRE;
    song.notes [20]  = NOTE_FS4;

    song.rythm [21]  = NOIRE;
    song.notes [21]  = NOTE_FS4;

    song.rythm [22]  = NOIRE;
    song.notes [22]  = NOTE_E4;

    song.rythm [23]  = NOIRE;
    song.notes [23]  = NOTE_D4;

    song.rythm [24]  = NOIRE;
    song.notes [24]  = NOTE_C4;

    song.rythm [25]  = CROCHE;
    song.notes [25]  = NOTE_C4;

    song.rythm [26]  = CROCHE;
    song.notes [26]  = NOTE_C4;

    song.rythm [27]  = CROCHE;
    song.notes [27]  = NOTE_D4;

    song.rythm [28]  = CROCHE;
    song.notes [28]  = NOTE_D4;

    song.rythm [29]  = CROCHE;
    song.notes [29]  = NOTE_A3;

    song.rythm [30]  = CROCHE;
    song.notes [30]  = NOTE_A3;

    song.rythm [31]  = NOIRE;
    song.notes [31]  = NOTE_C4;

    song.rythm [32]  = CROCHE;
    song.notes [32]  = NOTE_C4;

    song.rythm [33]  = CROCHE;
    song.notes [33]  = NOTE_C4;

    song.rythm [34]  = CROCHE;
    song.notes [34]  = NOTE_D4;

    song.rythm [35]  = CROCHE;
    song.notes [35]  = NOTE_D4;

    song.rythm [36]  = CROCHE;
    song.notes [36]  = NOTE_A3;

    song.rythm [37]  = CROCHE;
    song.notes [37]  = NOTE_A3;

    song.rythm [38]  = NOIRE;
    song.notes [38]  = NOTE_C4;

    song.rythm [39]  = CROCHE;
    song.notes [39]  = NOTE_D4;

    song.rythm [40]  = CROCHE;
    song.notes [40]  = NOTE_D4;

    song.rythm [41]  = CROCHE;
    song.notes [41]  = NOTE_E4;

    song.rythm [42]  = CROCHE;
    song.notes [42]  = NOTE_E4;

    song.rythm [43]  = CROCHE;
    song.notes [43]  = NOTE_FS4;

    song.rythm [44]  = CROCHE;
    song.notes [44]  = NOTE_FS4;

    song.rythm [45]  = NOIRE;
    song.notes [45]  = NOTE_G4;

    song.rythm [46]  = NOIRE;
    song.notes [46]  = NOTE_E4;

    song.rythm [47]  = NOIRE;
    song.notes [47]  = NOTE_D4;

    song.rythm [48]  = NOIRE;
    song.notes [48]  = NOTE_B3;

    song.rythm [49]  = NOIRE;
    song.notes [49]  = NOTE_G3;

    // convertir les notes en milliseconde
    for (uint8_t i=0; i < MUSIC_SIZE; ++i)
    {
        song.rythm [i] *= NOTE_TO_MS / tempo ;
    }

    return song ;
}





