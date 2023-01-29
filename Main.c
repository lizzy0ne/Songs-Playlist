#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

int main() {

    SongInList *head, *second, *third;

    head = (SongInList*) malloc(sizeof(SongInList));   // Default songs
    second = (SongInList*) malloc(sizeof(SongInList));
    third = (SongInList*) malloc(sizeof(SongInList));

    head->songData = (song) {"Wannabe", "Spice girls", "Spice", 1996, "pop", {02, 53}};
    head->next = second;

    second->songData = (song) {"Te Amo", "Rihanna", "Rated R", 2009, "pop-music", {03, 29}};
    second->next = third;

    third->songData  = (song) {"Counting Stars", "OneRepublic", "Native", 2013, "pop-music", {04, 20}};
    third->next = NULL;

    FILE *Playlist;
    printToFile(head, Playlist, "Playlist.txt", "w");

    printf("Welcome, dear user! \nThis program was created to record your favorite songs. All the songs you recorded will be saved in a folder \"Playlist.txt\"\n"
           "Instructions are listed below:\nIf you want to add a song to the playlist, press 1.\nIf you want to see songs performed by this or that artist, select 2.\n"
           "If you want to see songs of a particular album, select 3.\nIf you want to see songs released in a certain year, select 4.\n"
           "If you want see songs of a particular genre select 5.\nIf you want to exit the program select 6.");
    printMenu();
    int option;
    while (scanf("%d", &option) == 1) {
        if (option == 6) {
            printf("\nThank you for using this program!\n");
            break;
        }

        switch(option){
            case 1:
                head = insertNewSong(head);
                break;
            case 2:
                displayByCommonArtist(head);
                break;
            case 3:
                displayByCommonAlbum(head);
                break;
            case 4:
                displayByCommonYear(head);
                break;
            case 5:
                displayByCommonGenre(head);
                break;
            default:
                printf("ERROR: No such an option!\n");
                break;
        }
        printMenu();
    }

    freeList(head);

    return 0;
}
