#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "song.h"

typedef struct playlistNode {
    Song song;
    struct playlistNode *next;
    struct playlistNode *previous;
}playlistNode;

typedef struct playlist {
    playlistNode *head;
    playlistNode *current;
}playlist;  
void  startPlaylist(playlist *playlist);
void addSongToPlaylist(playlist* playlist, Song song);
void removeSongFromPlaylist(playlist *playlist, Song song);
void showplaylist(playlist *playlist);
void RestartPlaylist(playlist *playlist);
void playNextSong(playlist *playlist);
void playPrevSong(playlist *playlist);

#endif
