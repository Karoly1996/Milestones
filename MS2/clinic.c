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
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void displayAllPatients(const struct Patient patient[], int max, int fmt) {
    // Declare variables
    int i;
    int record = 0;

    // Display table
    if (fmt == FMT_TABLE) {
        displayPatientTableHeader();
    }   

    // Begin patient array iteration 
    for (i = 0; i < max; i++) {
        // Check if patient number is not 0 
        if (patient[i].patientNumber != 0) {
            // set record to 1 if patient is not 0
            record = 1;
            // Display patient record
            displayPatientData(&patient[i], fmt);
        }
    }
    // Display message for no records found
    if (record == 0) {
        printf("*** No records found ***\n\n");
    }
    printf("\n");
}

// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max) {
    //declare viarables
    int option; 

    do {
        //print header for search options
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        //get user input
        scanf("%d", &option);
        printf("\n");

        // option 1
        if (option == 1) {
            // searching by ID
            searchPatientByPatientNumber(patient, max);
            // Clear input buffer
            clearInputBuffer();
            // Wait until user presses enter
            suspend();
        // option 2
        } else if (option == 2) {
            // searching by number
            searchPatientByPhoneNumber(patient, max);
            // clear input
            clearInputBuffer();
            // wait until user presses enter
            suspend();
        }
        
    
    } while (option != 0);

}

// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max) {
    // Declare variables 
    int i;
    int newRecord = 0;

    // Begin iteration for free element 
    for (i = 0; i < max; i++) {
        // add new record to count
        if (patient[i].patientNumber != 0) {
            // add onto new recorded count
            newRecord++;
        }
    }
    // Check to see if new record is less than max
    if (newRecord < max) {
        // add new record
        patient[newRecord].patientNumber = nextPatientNumber(patient, max);
        inputPatient(patient + newRecord);
        printf("*** New patient record added ***\n\n");
        clearInputBuffer();
    } else {
        // print listing is full 
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max) {
    int number, index;

    // get user input for patient number
    printf("Enter the patient number: ");
    scanf("%d", &number);
    printf("\n");

    // Find given number to patient number
    index = findPatientIndexByPatientNum(number, patient, max);
    // Print error if number wasnt found
    if (index == -1) {
        printf("ERROR: Patient record not found!\n\n");
    } else {
        menuPatientEdit(&patient[index]);
    }
}

// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max) {
    int number;
    int index;
    char option;
    
    // Get patient number 
    printf("Enter the patient number: ");
    scanf("%d", &number);
    printf("\n");

    // Checking if patient number exists
    if (findPatientIndexByPatientNum(number, patient, max) != -1) {
        index = findPatientIndexByPatientNum(number, patient, max);
        printf("Name  : %s\n", patient[index].name);
        printf("Number: %05d\n", patient[index].patientNumber);
        printf("Phone : ");

        // Display formatted phone
        displayFormattedPhone(patient[index].phone.number);
        printf(" (%s)", patient[index].phone.description);
        printf("\n\n");

        // Confirm removal 
        printf("Are you sure you want to remove this patient record? (y/n): ");
        scanf(" %c", &option);

        // Abort operation
        if (option == 'n' || option == 'N') {
            printf("Operation aborted.\n\n");
            clearInputBuffer();
        } else {
            // Assigning patient to safe empty state so that the other function can't access it
            patient[index].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
            clearInputBuffer();
        }
    } else {
        // Display error if patient not found
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    int number, index;

    // get user input for patient number
    printf("Search by patient number: ");
    scanf("%d", &number);
    printf("\n");

    // Find patient at index
    index = findPatientIndexByPatientNum(number, patient, max);

    if (index == -1) {
         printf("*** No records found ***\n");
    } else {
        displayPatientData(&patient[index], FMT_FORM);
    }
    printf("\n");

}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    // Declare variables
    char phoneNumber[11];
    int i, match = 0;

    // Prompt user for phone number
    clearInputBuffer();
    printf("Search by phone number: ");
    fgets(phoneNumber, 11, stdin);
    printf("\n");
    
    // Call table header
    displayPatientTableHeader();
    // begin iteration for phone numbers
    for (i = 0; i < max; i++) {
        if (strcmp(patient[i].phone.number, phoneNumber) == 0) {
            // Display patient record
            displayPatientData(&patient[i], FMT_TABLE);
            match++;
        }
    }
    printf("\n");
    // display message if no records found
    if (match == 0) {
        printf("*** No records found ***\n\n");

    }
}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max) {
    // Declare variables
    int i, nextNum = 0;

    // begin loop 
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber > nextNum) {
            nextNum = patient[i].patientNumber;
        }
    }
    // increment
    nextNum++;
    //return to function
    return nextNum;
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max) {
    // Declare variable
    int i;

    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == patientNumber) {
            return i;
        }
    }
    return -1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient) {
    // Declare variable
    int i;
    char name[NAME_LEN + 1];

    // display data input header
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    // prompt for user name 
    printf("Name  : ");
    fgets(name, sizeof(name), stdin);

    //set name into patient name
     for (i = 0; i < strlen(name) - 1; i++) {
        patient->name[i] = name[i];
    }
    
    printf("\n");
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone) {
    // Declare variables
   int option;
   int i;
   char number[PHONE_LEN + 1];

   //Display Phone Information 
   printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    //Prompt for user option
    printf("Selection: ");
    scanf("%d", &option);
    printf("\n");

    switch (option) {
        case 1:
        //Set description in phone struct
        strncpy(phone->description, "CELL", PHONE_DESC_LEN);
        //Display description 
        printf("Contact: %s\n", phone->description);

        // prompt for user input for selection 
        clearInputBuffer();
        printf("Number : ");
        fgets(number, sizeof(number), stdin);

        //loop for phone number
        for (i = 0; i < PHONE_LEN + 1; i++) {
            phone->number[i] = number[i];
        }
        printf("\n");
        break;

        case 2:
        //Set description in phone struct
        strncpy(phone->description, "HOME", PHONE_DESC_LEN);
        //Display description 
        printf("Contact: %s\n", phone->description);

        // prompt for user input for selection 
        clearInputBuffer();
        printf("Number : ");
        fgets(number, sizeof(number), stdin);

        //loop for phone number
        for (i = 0; i < PHONE_LEN + 1; i++) {
            phone->number[i] = number[i];
        }
        printf("\n");
        break;

        case 3:
        //Set description in phone struct
        strncpy(phone->description, "WORK", PHONE_DESC_LEN);
        //Display description 
        printf("Contact: %s\n", phone->description);

        // prompt for user input for selection 
        clearInputBuffer();
        printf("Number : ");
        fgets(number, sizeof(number), stdin);

        //loop for phone number
        for (i = 0; i < PHONE_LEN + 1; i++) {
            phone->number[i] = number[i];
        }
        printf("\n");
        break;

        case 4:
        //Set description in phone struct
        strncpy(phone->description, "TBD", PHONE_DESC_LEN);

        //Safe empty state
        *phone->number = 0;
        break;

        default:
        printf("Invalid\n");
        break;
    }
}
