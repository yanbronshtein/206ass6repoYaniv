/*
 * Name: Joshua Friedman
 * ID: 260738744
 * Date: Dec 4, 2017
 * Version: 1.0
 * Description: Consumer.c implements consumer method which reads a character from DATA.txt if the char in TURN.txt is'1'
 * and outputs the character from DATA.txt to STDOUT
 * */

#include "fork.h"
#include <stdlib.h>
#include <stdio.h>

int consumer() {
    char c;
    char turn;
    char *turnFN = "TURN.txt";
    char *sourceDataFN = "mydata.txt";
    char *sharedDataFN = "DATA.txt";
    FILE *sourceFile;    //mydata file
    FILE *tFile;    //turn file
    FILE *sharedDataFile;    //shared DATA file



    while(1) {


        tFile = fopen(turnFN, "r+");
        if (tFile == NULL) {
            printf("Cannot open file %s\n ",turnFN);
            exit(EXIT_FAILURE);
        }

        turn = (char) fgetc(tFile);  //get turn number
        fclose(tFile);

        while (turn == PRODUCER) {

            //not consumer's turn, continuously check TURN
            tFile=fopen(turnFN,"r+");
            if (tFile == NULL) {
                printf("Cannot open file %s\n ",turnFN);
                exit(EXIT_FAILURE);
            }

            turn =(char) fgetc(tFile);
            fclose(tFile);

        }

        sharedDataFile = fopen(sharedDataFN, "r");
        if (sharedDataFile == NULL) {
            printf("Cannot open file %s\n ",sharedDataFN);
            exit(EXIT_FAILURE);
        }

        c = (char) fgetc(sharedDataFile);        //get char from shared data file
        fclose(sharedDataFile);

        tFile=fopen(turnFN,"r+");
        if (tFile == NULL) {
            printf("Cannot open file %s\n ",turnFN);
            exit(EXIT_FAILURE);
        }

        fputc(PRODUCER,tFile);  //change turn
        fclose(tFile);

        if(c == EOF) break;
        printf("%c", c);
        fflush(stdout); // I put this here because the printf statements werent showing up

    }
    return 0;
}