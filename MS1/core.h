/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 1
Full Name  : Karoly Nemeth
Student ID#: 021419144
Email      : knemeth@mysenecacollege.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

//Function Prototypes

//Provided Functions 
// Clear the standard input buffer
void clearInputBuffer(void);
// Wait for user to input the "enter" key to continue
void suspend(void);

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
