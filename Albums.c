#include<stdio.h>
#include<string.h>
#include "Albums.h"
void createAlbum(Album *album, char name[]) {
    strcpy(album->name, name);
    album->songCount = 0;
}
void addSongToAlbum(Album *album, Song song) {
    album->songs[album->songCount++] = song;
}
void displayAlbum(Album album) {
    printf("Album Name: %s\n",album.name);
    for(int i = 0;i<album.songCount;i++) {
           printf("%d) %s by %s(%d sec)\n", i+1,album.songs[i].name, album.songs[i].artist, album.songs[i].duration);
    }
}
void saveAlbumToFile(Album album) {
    char filename[150];
    sprintf(filename, "%s.album", album.name);
    FILE *file = fopen(filename, "w");
    if (!file) return;

    fprintf(file, "%d\n", album.songCount);
    for (int i = 0; i < album.songCount; i++) {
        fprintf(file, "%s|%s|%d\n", 
                album.songs[i].name,
                album.songs[i].artist,
                album.songs[i].duration);
    }
    fclose(file);
}

void loadAlbumFromFile(Album *album) {
    char filename[150];
    sprintf(filename, "%s.album", album->name);
    FILE *file = fopen(filename, "r");
    if (!file) return;

    fscanf(file, "%d\n", &album->songCount);
    for (int i = 0; i < album->songCount; i++) {
        fscanf(file, "%99[^|]|%99[^|]|%d\n",
               album->songs[i].name,
               album->songs[i].artist,
               &album->songs[i].duration);
    }
    fclose(file);
}
