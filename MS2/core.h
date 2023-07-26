/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  :
Student ID#:
Email      :
Section    :

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #1 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);






//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////
//Start Milestone 1

// Function to get an int value or display error message if invalid
int inputInt(void); 

// Function to get positive int value and return, if 0 or negative entered
// Display an error message
int inputIntPositive(void);

// Function is within range, if not within range display error and prompt again
int inputIntRange(int low, int high);

// Function for single character within the list, if character is invalid
// Display an error message and prompt again
char inputCharOption(const char* vChar);

// Function for C string value in order to validate by 2nd and 3rd arguement
void inputCString(char* str, int min, int max);

// Function to display an array of 10 character
// As a formatted phone number
void displayFormattedPhone(const char* str);

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H