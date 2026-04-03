#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "song.h"
#include "Albums.h"
#include "playlist.h"
#define MAX_SONGS 100
#define MAX_ALBUMS 50
#define LOG_FILE "command_history.log"   
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"



void logCommand(const char *command) {
    FILE *logFile = fopen(LOG_FILE, "a");
    if (logFile) {
        fprintf(logFile, "%s\n", command);
        fclose(logFile);
    }
}

void displayCommandHistory() {
    FILE *logFile = fopen(LOG_FILE, "r");
    if (!logFile) {
        printf("No command history found.\n");
        return;
    }
    printf("         COMMAND HISTORY \n");
    char line[256];
    int count = 1;
    while (fgets(line, sizeof(line), logFile)) {
        printf("%d. %s", count++, line);
    }
    fclose(logFile);
    printf("-----------------------------------------------------------------------\n");
}

void ListAllSongs(Song songs[], int songcount) {
    printf("--------------------------------------------------------------\n\n");
    for(int i=0;i< songcount;i++) {
        printf("%d. %s by %s (%dsec)\n\n", songs[i].id,songs[i].name, songs[i].artist,songs[i].duration); 
    }
    printf("--------------------------------------------------------------\n");
}


void ListAllAlbums(Album albums[], int albumCount) {
        printf("--------------------------------------------------------------\n\n");
        if(albumCount == 0) {
            printf("No Albums found!! Create one\n");
                    printf("--------------------------------------------------------------\n\n");

        }
        else {
            for(int i=0;i<albumCount;i++) {
                printf("%d. %s (Number of songs: %d)\n\n",i+1,albums[i].name,albums[i].songCount );
            }
                    printf("--------------------------------------------------------------\n\n");

        }
}

Song* findSongByID(Song songs[], int songcount, int id)  {
    int j;
    for(int i=0;i<songcount;i++) {
        if(songs[i].id == id) {
           return &songs[i];
        }
    }
           return NULL;
}

Album* FindAlbumByName(Album albums[], int albumCount, char *name) {
    for(int i=0;i<albumCount;i++) {
        if(!strcmp(albums[i].name, name)) {
            return &albums[i];
        }
    }
    return NULL;
}
//
int loadAllAlbums(Album albums[]) {
    FILE *file = fopen("albums_list.txt", "r");
    if (!file)  {
        return 0;
    }
    int count = 0;
    char albumName[100];
    while (fscanf(file, "%99[^\n]\n", albumName) == 1) {
        createAlbum(&albums[count], albumName);
        loadAlbumFromFile(&albums[count]);
        count++;
    }
    fclose(file);
    return count;
}
//
void saveAlbumList(Album albums[], int albumCount) {
    FILE *file = fopen("albums_list.txt", "w");
    if (!file) {
        return;
    }
    for (int i = 0; i < albumCount; i++) {
        fprintf(file, "%s\n", albums[i].name);
    }
    fclose(file);
}

void displayMenu() {
printf("\n=========================================================\n");
printf("C-UNPLUGGED MUSIC PLAYER\n");
printf("welcome to 'C UNPLUGGED MUSIC PLAYER'\n");
printf("Here are some set of instrutions that will help you to guide as you explore the music player\n");
    printf("  1.  List all songs                       \n");
    printf("  2.  List all albums                      \n");
    printf("  3.  Create new album                     \n");
    printf("  4.  View album details                   \n");
    printf("  5.  Add song to album                    \n");
    printf("  6.  Delete song from album               \n");
    printf("  7.  Add album to playlist                \n");
    printf("  8.  Add song to playlist                 \n");
    printf("  9.  Remove song from playlist            \n");
    printf("  10. Show current playlist                \n");
    printf("  11. Play next song                       \n");
    printf("  12. Play previous song                   \n");
    printf("  13. Restart playlist                     \n");
    printf("  14. View command history                 \n");
    printf("  0.  Exit                                 \n");
printf("\n=========================================================\n");
printf("Please enter the corresponding code from 0 to 14 to implement the corresponding action");
printf("Enter your choice: ");
}

int main() {
    playlist mainplaylist;
    Song songLibrary[MAX_SONGS];
    Album albums[MAX_ALBUMS];

    int songCount = 0;
    int albumCount = 0;
    int choice;
    char command[100];

    startPlaylist(&mainplaylist);
    printf("\n\n");
    printf("//Loading songs from library...\n");
    songCount = loadSongsFromFile(songLibrary, "songs.txt");
    printf("Loaded %d songs.\n", songCount);

    printf("//Loading albums...\n");
    albumCount = loadAllAlbums(albums);
    printf("Loaded %d albums.\n", albumCount);

    while(1) {
        displayMenu();
        scanf("%d", &choice);
        getchar();
        sprintf(command, "Command: %d", choice);
        logCommand(command);

        switch(choice) {
            case 1: {
            ListAllSongs(songLibrary, songCount);
            break;
            }

            case 2: {
            ListAllAlbums(albums, albumCount);
            break;
            }

                        case 3: { 
                char albumName[100];
                printf("Enter album name: ");
                fgets(albumName, 100, stdin);
                albumName[strcspn(albumName, "\n")] = 0; 
                
                if (FindAlbumByName(albums, albumCount, albumName)) {
                    printf("Album already exists!\n");
                } else {
                    createAlbum(&albums[albumCount], albumName);
                    saveAlbumToFile(albums[albumCount]);
                    albumCount++;
                    saveAlbumList(albums, albumCount);
                    printf("Album '%s' created successfully!\n", albumName);
                }
                break;
            }

        case 4: {
            char albumName[100];
            printf("Enter Album Name: ");
            fgets(albumName,100,stdin);
            albumName[strcspn(albumName, "\n")] = 0;

            Album *album = FindAlbumByName(albums, albumCount, albumName);
            if(album) {
                printf("--------------------------------------------------------------------------------------------------------\n");
                displayAlbum(*album);
                printf("--------------------------------------------------------------------------------------------------------\n");
            }
            else {
                printf("Album Not Found!!");
            }
            break;
        }

        case 5: {
            char albumName[100];
            printf("Enter album name: ");
            fgets(albumName, 100, stdin);
            albumName[strcspn(albumName, "\n")] = 0;

            Album *album = FindAlbumByName(albums, albumCount, albumName);
            if(!album) {
                printf("Album not found!\n");
                break;
            }
            int songid;
            printf("Enter song ID: ");
            scanf("%d", &songid);
            getchar();

            Song *song = findSongByID(songLibrary,songCount,songid);
            if(!song) {
                printf("Song not found DUDE!!!\n");
                break;
            }
            addSongToAlbum(album, *song);
            saveAlbumToFile(*album);
            printf("song sucessfully added to album!!!\n");
            break;
        }

        case 6: {
            char albumName[100];
            printf("Enter Album name: ");
            fgets(albumName, 100, stdin);
              albumName[strcspn(albumName, "\n")] = 0;
            Album *album = FindAlbumByName(albums, albumCount, albumName);
            if(!album) {
                printf("Album not found! \n");
                break;
            }

            displayAlbum(*album);
            int songid;
            printf("Enter songID to delete: \n");
            scanf("%d", &songid);
            getchar();

            if (songid<1|| songid>album->songCount)
            {
                printf("Please enter correct songID\n");
                break;
            }
            for(int i= songid-1;i<album->songCount-1;i++) {
                 album->songs[i] = album->songs[i+1];
            }
            album->songCount--;
           saveAlbumToFile(*album);
           printf("Song with songID %d is deleted\n", songid);
           break;
            
        }
        case 7: {
            char albumName[100];
            printf("Enter album Name: ");
            fgets(albumName, 100, stdin);
            albumName[strcspn(albumName, "\n")] = 0;
            Album* album = FindAlbumByName(albums,albumCount,albumName);
            if(!(album)) {
                printf("Album NOT found!!!\n");
                break;
            }
            for(int i=0;i<album->songCount;i++) {
                addSongToPlaylist(&mainplaylist,album->songs[i]);
            }
            printf("Album successfully added to playlist\n");
            printf("------------ENJOY-------------");
            break;
            }

            case 8: {
                int songid;
                printf("Enter the song id which you want add to the playlist: ");
                scanf("%d", &songid);
                Song *song = findSongByID(songLibrary, songCount, songid);
                if(song) {
                    addSongToPlaylist(&mainplaylist, *song);
                }
                else {
                    printf("Enter valid songID\n");
                }
                break;
            }

            case 9: {
                int songid;
                printf("Enter the songid which you want to remove: ");
                scanf("%d", &songid);
                getchar();

                Song *song = findSongByID(songLibrary,songCount,songid);
                if(song) {
                    removeSongFromPlaylist(&mainplaylist,*song);
                }
                else {
                    printf("Enter valid song ID!!!\n");
                }
                break;
            }

            case 10: {
                showplaylist(&mainplaylist);
                break;
            }
            case 11: {
                playNextSong(&mainplaylist);
                break;
            }
            case 12: {
                playPrevSong(&mainplaylist);
                break;
            }
            case 13: {
                RestartPlaylist(&mainplaylist);
                break;
            }
            case 14: {
                displayCommandHistory();
                break;
            }
            case 0:{
                printf("Thankyou for using C-unplugged \n");
                return 0;
            }
           default:
           printf("Invalid choice! Enter again,\n");
        }
    }
}



