#include <stdio.h>
#include <string.h>
#include "song.h"

int loadSongsFromFile(Song songs[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open %s\n", filename);
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%d|%99[^|]|%99[^|]|%d\n",
                  &songs[count].id,
                  songs[count].name,
                  songs[count].artist,
                  &songs[count].duration) == 4) {
        count++;
    }

    fclose(file);
    return count;
}
