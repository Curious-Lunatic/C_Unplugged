#ifndef SONG_H
#define SONG_H

typedef struct {
    int id;
    char name[100];
    char artist[100];
    int duration;
} Song;

int loadSongsFromFile(Song songs[], const char *filename);

#endif
