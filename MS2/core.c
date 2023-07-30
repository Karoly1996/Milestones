/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  : Karoly Nemeth
Student ID#: 021949144
Email      : knemeth@myseneca.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//
#define _CRT_SECURE_NO_WARNINGS

// System Libraries
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
// User Libraries
#include "core.h"

// Provided function definition 
// Clear the standard input buffer
void clearInputBuffer(void)
{
 // Discard all remaining char's from the standard input buffer:
 while (getchar() != '\n')
 {
 ; // do nothing!
 }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
 printf("<ENTER> to continue...");
 clearInputBuffer();
 putchar('\n');
}

//---
//Start Milestone 1
//Function Defintion 

// Function to get an int value or display error message if invalid
int inputInt(void) {
    int inPut;
    char newLine = ' ';

    // start loop
    do {
        //get input
        scanf("%d%c", &inPut, &newLine);

        if (newLine != '\n') { 
            clearInputBuffer();
            //print error if input is not a number
            printf("Error! Input a whole number: ");
        }

    } while (newLine != '\n');

    //return
    return inPut;
}

// Function to get positive int value and return, if 0 or negative entered
// Display an error message
int inputIntPositive(void) {
    int inPut;
    char newLine = ' ';

    do {
        //get input
        scanf("%d%c", &inPut, &newLine);

        if (newLine != '\n') { 
            //clear input and prompt again
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        } if (inPut <= 0) {
            //print error message 
            printf("ERROR! Value must be > 0: ");
        }

    } while (inPut <= 0);

    return inPut;
}

// Function is within range, if not within range display error and prompt again
int inputIntRange(int low, int high) {
    int result;
    do {
        // assign result to inputInt
        result=inputInt();
        if( result<low || result>high) {
            //display error message if not within range
            printf("ERROR! Value must be between %d and %d inclusive: ",
            low,high);
        }
    } while(result<low || result>high);

    return result;
}

// Function for single character within the list, if character is invalid
// Display an error message and prompt again
char inputCharOption(const char* vChar) {
    char buffer[80];
    char* found;
    //start loop
    do {
        //get input
        fgets(buffer, 80, stdin);
        // get rid of newline character
        buffer[strlen(buffer) - 1] = '\0';
        found=strstr(vChar, buffer);
        if (found == NULL) {
            //display error message if character isnt valid
            printf("ERROR: Character must be one of [%s]: ", vChar);
        }
    } while (found == NULL);

    return buffer[0];
}

// Function for C string value in order to validate by 2nd and 3rd arguement
void inputCString(char* str, int min, int max) { 
    char buffer[80];
    int error;
    int len;
    //start loop
    do {
        //set error 
        error = 0;
        //get input
        fgets(buffer, 80, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        len=(int)strlen(buffer);

        //case 1
        if (min == max && len != min) {
            //display error
            printf("ERROR: String length must be exactly 6 chars: ");
            error = 1;
            //case2
        } else if (len < min) {
            // display error
            printf("ERROR: String length must be between 5 and 6 chars: ");
            error = 1;
            //case 3
        } else if (len > max) {
            // display error
            printf("ERROR: String length must be no more than 6 chars: ");
            error = 1;
        } else {
            error = 0;
        }
    } while (error);

    strcpy(str, buffer);
}

// Function to display an array of 10 character
// As a formatted phone number
void displayFormattedPhone(const char* str) {
    int len = 0;

    // Calculate the length of the input string 
    // until a non-digit or NULL character is encountered
    while (str != NULL && str[len] && isdigit(str[len])) {
        len++;
    }

    //display phone number
    if (len == 10) {
        // Display formatted number
        // split line to not exceed 80 characters
        printf("(%c%c%c)%c%c%c-%c%c%c%c", 
        str[0], str[1], str[2], str[3], str[4], 
        str[5], str[6], str[7], str[8], str[9]);
    } else {
        // print if invalid input
        printf("(___)___-____");
    }
}
