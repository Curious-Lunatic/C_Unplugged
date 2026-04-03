#ifndef ALBUM_H
#define ALBUM_H

#include "song.h" 

typedef struct Album {
    char name[100];
    Song songs[100];  
    int songCount;
} Album;

void createAlbum(Album *album, char name[]);
void addSongToAlbum(Album *album, Song song);
void displayAlbum(Album album);
void saveAlbumToFile(Album album);
void loadAlbumFromFile(Album *album);

#endif


