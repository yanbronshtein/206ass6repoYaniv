/*
 * Name: Joshua Friedman and Yaniv Bronshtein
 * ID's: 260738744 and 260618099
 * Date: Dec 4, 2017
 * Version: 1.0
 * Description: main.c implements the main method which creates the TURN.txt and DATA.txt files, assumes that mydata.txt
 * exists. Then it forks the producer and consumer.
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "fork.h"

int main() {

    char *turnFN = "TURN.txt"; //name of turn file
    char *sharedDataFN = "DATA.txt"; //name of text source file
    FILE *tFile;    //turn file
    FILE *sharedDataFile;    //shared DATA file


    /*create turn file */
    tFile = fopen(turnFN,"w+");
    if (tFile == NULL) {
        printf("Cannot open file %s\n ",turnFN);
        exit(EXIT_FAILURE);
    }

    fputc(PRODUCER,tFile);  //create Turn file and initialize turn to PRODUCER
    fclose(tFile);
    int status;//used for wait()

    /*create shared data file*/
    sharedDataFile = fopen(sharedDataFN,"w+");
    if (sharedDataFile == NULL) {
        printf("Cannot open file %s\n ",sharedDataFN);
        exit(EXIT_FAILURE);
    }
    fclose(sharedDataFile);

    int pid = fork();
    if(pid == -1) exit (1);
    if(pid == 0) {
        producer();
        wait(&status);  //wait for consumer to end
    }
    if(pid != 0) {
        consumer();
    }
    return 0;
}
