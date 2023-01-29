#ifndef HEADER_FILE
#define HEADER_FILE

typedef struct length {
    int minutes;
    int seconds;
} length;

typedef struct song {
    char title[50];
    char singer[50];
    char album[50];
    int year;
    char genre[50];
    length length;
} song;

typedef struct SongInList {    // Elements of Linked List
    song songData;
    struct SongInList *next;
} SongInList;

void printMenu() {
    printf("\n---------------------------------------------------------------------\n"
           "Choose option:\n"
           "1. Add and save a new song in database\n"
           "2. Display all songs of selected artist\n"
           "3. Display all details of the songs of selected album\n"
           "4. List all songs that were released in selected year\n"
           "5. List all songs of selected genre\n"
           "6. Stop the program\n\n");
}

void displayByCommonArtist(SongInList* n) {
    printf("\nCommon Singer/Group.....\n");
    if (n == NULL)  // check if the list is empty
        printf("The playlist is empty now.\n\n");
    else {
        printf("Enter searching Singer/Group:  ");
        bool conditionForError = false;  // to check is there such an artist
        char commonArtist[100];
        scanf("%s", commonArtist);
        while (n != NULL) {
            if (strcmp(n->songData.singer, commonArtist) == 0) {
                conditionForError = true;
                printf("The title of the song is %s\n", n->songData.title);
            }

            n = n->next;   // check the next element(Song)
        }

        if (!conditionForError)      // Add error if there is no such Artist in playlist
            printf("ERROR: No such artist in the playlist!\n");
    }
}

void displayByCommonAlbum(SongInList* n) {
    printf("\nFrom the same Album.....\n");
    if (n == NULL)
        printf("The playlist is empty now.\n\n");
    else {
        printf("Enter searching Singer/Group:  ");
        bool conditionForError = false;
        char commonArtist[100], commonAlbum[100];
        scanf("%s", commonArtist);
        printf("Enter searching Album:  ");
        scanf("%s", commonAlbum);
        while (n != NULL) {
            if (strcmp(n->songData.singer, commonArtist) == 0 && strcmp(n->songData.album, commonAlbum) == 0) {
                conditionForError = true;
                printf("The title of the song is  %s\n"
                   "The singer/group is       %s\n"
                   "The album is              %s\n"
                   "The year of release is    %d\n"
                   "The genre is              %s\n"
                   "And the length is         %d:%d\n\n",
                   n->songData.title, n->songData.singer, n->songData.album, n->songData.year, n->songData.genre, n->songData.length.minutes, n->songData.length.seconds);
            }

            n = n->next;
        }

        if (!conditionForError)
            printf("ERROR: No such a singer/group or album in the playlist!\n"); // Add error if there is no such Album in playlist
    }
}

void displayByCommonYear(SongInList* n) {
    printf("\nThe Same year of release.....\n");
    if (n == NULL)
        printf("The playlist is empty now.\n\n");
    else {
        printf("Enter year:  \n");
        bool conditionForError = false;
        int commonYear;
        scanf("%d", &commonYear);

        while (n != NULL) {
            if (n->songData.year == commonYear) {
                conditionForError = true;
                printf("The title of the song is %s\n"
                       "The singer/group is      %s\n"
                       "The album is             %s\n"
                       "The year of release is   %d\n"
                       "The genre is             %s\n"
                       "And the length is        %d:%d\n\n",
                       n->songData.title, n->songData.singer, n->songData.album, n->songData.year,
                       n->songData.genre, n->songData.length.minutes, n->songData.length.seconds);
            }

            n = n->next;
        }

        if (!conditionForError)
            printf("ERROR: No such a year of release in the playlist!\n"); // Add error if there is no such year in playlist
    }
}

void displayByCommonGenre(SongInList* n) {
    printf("\nThe Same Genre.....\n");
    if (n == NULL)
        printf("The playlist is empty now.\n\n");
    else {
        printf("Enter type of genre:  \n");
        bool conditionForError = false;
        char commonGenre[100];
        scanf("%s", commonGenre);
        while (n != NULL) {
            if (strcmp(n->songData.genre, commonGenre) == 0) {
                conditionForError = true;
                printf("The title of the song is  %s\n"
                       "The singer/group is       %s\n"
                       "The album is              %s\n"
                       "The year of release is    %d\n\n",
                       n->songData.title, n->songData.singer, n->songData.album, n->songData.year);
            }

            n = n->next;
        }

        if (!conditionForError)
            printf("ERROR: No such Genre in the playlist!\n"); // Add error if there is no such Genre in playlist
    }
}

void printToFile(SongInList* n, FILE* fp, char fileName[25], char mode[3]) {
    if (strcmp(mode, "w") != 0) printf("\nPrint to File. Open File....\n");
    fp = fopen(fileName, mode);
    while (n != NULL) {
        fprintf(fp, "The title of the song is  %s\n", n->songData.title);
        fprintf(fp, "The singer/group is       %s\n", n->songData.singer);
        fprintf(fp, "The album is              %s\n", n->songData.album);
        fprintf(fp, "The year of release is    %d\n", n->songData.year);
        fprintf(fp, "The genre is              %s\n", n->songData.genre);
        fprintf(fp, "The length is             %d:%d\n\n", n->songData.length.minutes, n->songData.length.seconds);

        n = n->next;
    }
    if (strcmp(mode, "w") != 0) printf("Successfully saved. Closing file....\n");
    fclose(fp);
}

SongInList* insertNewSong (SongInList* n) {
    printf("\nNew Song....\n");
    char newTitle[50], newSinger[50], newAlbum[50], newGenre[50];
    int newYear, newMinutes, newSeconds;

    printf("\nEnter a new song information\n"
           "Song's title:    ");
    scanf("%s", newTitle);
    printf("Singer/group:    ");
    scanf("%s", newSinger);
    printf("Album:           ");
    scanf("%s", newAlbum);
    printf("Year of release: ");
    scanf("%d", &newYear);
    printf("Song's genre:    ");
    scanf("%s", newGenre);
    printf("length:          ");
    scanf("%d:%d", &newMinutes, &newSeconds);

    if (newMinutes > 59 || newSeconds > 59) {
        printf("ERROR: Invalid length!\n");
        return 0;
    }

    SongInList* newSong = (SongInList*) malloc(sizeof(SongInList));  //create a new Element of Linked List

    strcpy(newSong->songData.title, newTitle);   // copy data
    strcpy(newSong->songData.singer, newSinger);
    strcpy(newSong->songData.album, newAlbum);
    strcpy(newSong->songData.genre, newGenre);
    newSong->songData.year = newYear;
    newSong->songData.length.minutes = newMinutes;
    newSong->songData.length.seconds = newSeconds;
    newSong->next = NULL;

    FILE *Playlist;  //directly write to file
    printToFile(newSong, Playlist, "Playlist.txt", "a");

    if (n == NULL)
        return newSong;
    else {
        SongInList *iter;
        for (iter = n; iter->next != NULL; iter = iter->next);
        iter->next = newSong;
        return n;
    }
}

void freeList(SongInList* n) {   //to free memory allocated space
   SongInList* tmp;

   while (n != NULL){  // delete every element in List
        tmp = n;
        n = n->next;
        free(tmp);
   }
}

#endif
