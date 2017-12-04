/*
 * Name: Yaniv Bronshtein
 * ID: 260618099
 * Date: Dec 4, 2017
 * Version: 1.0
 * Description: Producer.c implements producer method which reads from a text source file one character at a time
 * called mydata.txt, and outputs the read character into DATA.txt if the character in TURN.txt is '0'
 * */


#include "fork.h"
#include <stdlib.h>
#include <stdio.h>
int producer() {
    char c; //char to put in DATA.txt
    char turn; //char from TURN.txt
    char *turnFN = "TURN.txt"; //name of turn file
    char *sourceDataFN = "mydata.txt"; //name of source text file
    char *sharedDataFN = "DATA.txt"; //name of shared data file
    FILE *sourceFile;    //mydata file
    FILE *tFile;    //turn file
    FILE *sharedDataFile;    //shared DATA file

    sourceFile = fopen(sourceDataFN,"r+");
    if (sourceFile == NULL) {
        printf("Cannot open file %s\n ",sourceDataFN);
        exit(EXIT_FAILURE);
    }

    while(1) {



        tFile=fopen(turnFN,"r+");
        if (tFile == NULL) {
            printf("Cannot open file %s\n ",turnFN);
            exit(EXIT_FAILURE);
        }
        turn = (char) fgetc(tFile);
        fclose(tFile);

        while (turn == CONSUMER) {

            //not producer's turn, wait for consumer and continuously check TURN
            tFile = fopen(turnFN,"r+");
            if (tFile == NULL) {
                printf("Cannot open file %s\n ",turnFN);
                exit(EXIT_FAILURE);
            }
            turn =(char) fgetc(tFile);
            fclose(tFile);
        }

        c = (char) fgetc(sourceFile);    //get new char from my data

        sharedDataFile=fopen(sharedDataFN,"r+");
        if (sharedDataFile == NULL) {
            printf("Cannot open file %s\n ",sharedDataFN);
            exit(EXIT_FAILURE);
        }
        fputc(c,sharedDataFile);     //place new char in DATA.txt
        fclose(sharedDataFile);

        tFile=fopen(turnFN,"r+");
        if (tFile == NULL) {
            printf("Cannot open file %s\n ",turnFN);
            exit(EXIT_FAILURE);
        }

        fputc(CONSUMER,tFile);  //change turn
        fclose(tFile);


        if(c == EOF) break; //Reached end of mydata.txt

    }
    fclose(sourceFile);
    return 0;
}