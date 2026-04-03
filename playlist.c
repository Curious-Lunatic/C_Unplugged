#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "playlist.h"

void startPlaylist(playlist *p) {
    p->head = NULL;
    p->current = NULL;
}

void addSongToPlaylist(playlist *p, Song song) {
        playlistNode *newnode = (playlistNode*)malloc(sizeof(playlistNode));
        newnode->song = song;
        newnode->next = NULL;
        newnode->previous = NULL;

        if(p->head == NULL) {
            p->head = newnode;
            newnode->next = newnode;
            newnode->previous = newnode;
            p->current = newnode;
        }
        else {
            playlistNode *last = p->head->previous;
            last->next = newnode;
            newnode->previous = last;
            newnode->next = p->head;
            p->head->previous = newnode;
        }
        printf("%s HAS BEEN SUCUSSFULLY ADDED TO YOUR PLAYLIST! :)\n", song.name);
          printf("\n");
    printf("              SONG ADDED!                 \n");
    printf("            KEEP THE BEAT GOING!             \n");
   
}

void removeSongFromPlaylist(playlist *p, Song song) {
    if(p->head == NULL) {
        printf(" You can't remove silence, my dude. \n");
        return;
    }
   playlistNode *temp = p->head;
    do {
        if (strcmp(temp->song.name, song.name) == 0) {
            if (temp->next == temp) {
                
                p->head = NULL;
                p->current = NULL;
            } else {
                temp->previous->next = temp->next;
                temp->next->previous = temp->previous;

                if (temp == p->head)
                    p->head = temp->next;
                if (temp == p->current)
                    p->current = temp->next;
            }
            printf(" Song '%s' removed from playlist.\n", song.name);
            free(temp);
            return;
        }
        temp = temp->next;
    } while (temp != p->head);

    printf(" Song '%s' not found in playlist.\n", song.name);
}

void showplaylist(playlist*p) {
    if(p->head == NULL) {
        printf("PLAYLIST IS EMPTY!!!.... playing silence....");
        return;
    }
    playlistNode *temp = p->head; 
    do {
        printf("song: %s\nArtist: %s\n Duration: %d\n", temp->song.name, temp->song.artist, temp->song.duration);
        printf("-----------------------------------------------------------------------------------------------\n");
        temp = temp->next;
    }while(temp!= p->head);
}

void RestartPlaylist(playlist *p) {
    if(p->head == NULL) {
        printf("PLAYLIST IS EMPTY!!!");
        return;
    }
    p->current = p->head;
    printf("Restarting playlist..... Now playing:%s",p->current->song.name);
}

void playNextSong(playlist *p) {
    if(p->head == NULL) {
        printf("PLAYLIST IS EMPTY!!!");
        return;
    }
    if(p->current == NULL) {
    p->current = p->head;
    }
    else  {
        p->current = p->current->next;
    }
    printf("Now playing: %s  by %s (Duration: %d seconds)", p->current->song.name,p->current->song.artist, p->current->song.duration);
}

void playPrevSong(playlist *p) {
    if(p->head == NULL) {
        printf("PLAYLIST IS EMPTY!!!");
        return;
    }
          if  (p->current == NULL)
        p->current = p->head;  
    else {
        p->current = p->current->previous; 
    }
        printf("Now playing: %s by %s (Duration: %dseconds)",p->current->song.name,p->current->song.artist,p->current->song.duration);
}
