/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  :
Student ID#:
Email      :
Section    :

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
// ADDITIONAL FUNCTIONS ADDED BY KAROLY NEMETH
//////////////////////////////////////

// function to compare appointments
int compareAppointments(const void* a, const void* b) {
   struct Appointment* apptA = (struct Appointment*)a;
    struct Appointment* apptB = (struct Appointment*)b;

    // Compare by years
    if (apptA->date.year != apptB->date.year) {
        return apptA->date.year - apptB->date.year;
    }

    // compare by months
    if (apptA->date.month != apptB->date.month) {
        return apptA->date.month - apptB->date.month;
    }

    // compare by day
    if (apptA->date.day != apptB->date.day) {
        return apptA->date.day - apptB->date.day;
    }

    // compare by time
    return (apptA->time.hour * 60 + apptA->time.min) - 
        (apptB->time.hour * 60 + apptB->time.min);
}

// function to sort appointments array by time
void sortAppointments(struct Appointment appoints[], int max) {
   // qsort with compareAppointments as the comparison function
    qsort(appoints, max, sizeof(struct Appointment), compareAppointments);
}

// Function to get the last day of the month based on the year and month
int lastDay(int year, int month) {
    //months with 30 days
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
        // Feb month for leap year 
    } else if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return 29;
        } else {
            return 28;
        }
        // Any other month 
    } else {
        return 31;
    }
}



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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
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
            menuAppointment(data);
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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
            // Assigning patient to safe empty state so that 
            //the other function can't access it
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

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data) {
    int i;

    // Sort appointments in the data array based on time
    sortAppointments(data->appointments, data->maxAppointments);

    // Display the header of the schedule table
    displayScheduleTableHeader(NULL, 1);

    // For each appointment in the sorted data array:
    for (i = 0; i < data->maxAppointments; i++) {
        // Find the patient for the current appointment
        int patientIndex = -1;
        for (int j = 0; j < data->maxPatient; j++) {
            // Split line to stay under 80 characters
            if (data->appointments[i].patientNumber == 
            data->patients[j].patientNumber) {
                patientIndex = j;
                break;
            }
        }

        // Display patient if patient is found
        if (patientIndex != -1) {
            //split line to stay under 80 characters
            displayScheduleData(&data->patients[patientIndex], 
            &data->appointments[i], 1);
        }
    }

    // new line to seperate list
    printf("\n");
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data) {
    // Declare variables
    int day;
    int i;
    int j;
    struct Date date;

    // Get input for year with function for positive input
    printf("Year        : "); 
    date.year = inputIntPositive();

    //get input for month with range function
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);

    // get input for day using lastDay function
    day = lastDay(date.year, date.month);
    printf("Day (1-%d)  : ", day);
    date.day = inputIntRange(1, day);
    // new line for clinic appointments 
    printf("\n");

    // Sort appointment 
    sortAppointments(data->appointments, data->maxAppointments);

    // Display patient header
    displayScheduleTableHeader(&date, 0);

    // start loop to display patient appointments
    for (i = 0; i < data->maxAppointments; i++) {
        for (j = 0; j < data->maxPatient; j++) {
            // check patient number 
            if (data->appointments[i].patientNumber && 
                data->patients[j].patientNumber) {
            // Check to see if patient number match
            if (data->appointments[i].patientNumber == 
                data->patients[j].patientNumber &&
                data->appointments[i].date.year == date.year &&
                data->appointments[i].date.month == date.month &&
                data->appointments[i].date.day == date.day) {
                    //display
                    displayScheduleData(&data->patients[j], 
                        &data->appointments[i], 0);
                } 
            }
        } 
    }
    printf("\n");


}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment appoints[], int maxAppointments,
                    struct Patient patients[], int maxPatient) {
    // Declare variables
    int patientNumber;
    int patientIndex;
    struct Date date;
    struct Time time;
    int day = 31;
    int available = 1;

    // Timeslot variables
    int i;
    int timeAvailable = 0;
    int index = 0;

    // Get patient number
    printf("Patient Number: ");
    scanf("%d", &patientNumber);

    // Find patient number in patient array
    // split line to not exceed 80 characters
    patientIndex = findPatientIndexByPatientNum(patientNumber,
                                                patients, maxPatient);

    // Checking to make sure patientIndex is not -1
    if (patientIndex >= 0) {
        // Start loop if true
        while (available) {
            // Taking the year as input
            printf("Year        : ");
            date.year = inputIntPositive();

            // Taking the month as input
            printf("Month (1-12): ");
            date.month = inputIntRange(1, 12);

            // Determine the last day of the selected month and year
            day = lastDay(date.year, date.month);

            // Taking the day as input
            printf("Day (1-%d)  : ", day);
            date.day = inputIntRange(1, day);

            // input for hour
            printf("Hour (0-23)  : ");
            time.hour = inputIntRange(0, 23);

            //input for minute
            printf("Minute (0-59): ");
            time.min = inputIntRange(0, 59);

            // Check if time slot is available
            timeAvailable = 0; 
            for (i = 0; i < maxAppointments; i++) {
                if (date.year == appoints[i].date.year &&
                    date.month == appoints[i].date.month &&
                    date.day == appoints[i].date.day &&
                    time.hour == appoints[i].time.hour &&
                    time.min == appoints[i].time.min) {
                    // Unavailable slot 
                    timeAvailable = 1;
                    break;
                }
            }

            // Print error if timeslot is not available
            if (timeAvailable) {
                printf("\n");
                printf("ERROR: Appointment timeslot is not available!\n\n");
            } else {
                // Display next available timeslot
                while ((time.hour < START || time.hour > END) ||
                       (time.hour == END && time.min > 0) ||
                       (time.min % MIN != 0)) {
                    printf("ERROR: Time must be between %02d:00 and %02d:00 "
                        "in %02d minute intervals.\n\n", START, END, MIN);
                    printf("Hour (0-23)  : ");
                    scanf("%d", &time.hour);
                    printf("Minute (0-59): ");
                    scanf("%d", &time.min);
                }
                // break loop once input is valid
                break;
            }
        }
        // Find the next available slot
        while (index < maxAppointments) {
            if (appoints[index].patientNumber < 1) {
                break;
            }
            index++;
        }
        // Schedule the appointment
        if (index < maxAppointments) {
            appoints[index].date = date;
            appoints[index].time = time;
            appoints[index].patientNumber = patientNumber;
            // print scheduled message
            printf("\n*** Appointment scheduled! ***\n\n");
        }
        clearInputBuffer();
        return;
    }
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment appoints[], int maxAppointments,
                           struct Patient patients[], int maxPatient) {
    // Variables
    int patientNumber;
    int patientIndex;
    struct Date date;
    int day = 31;
    int valid = 0;
    int i;

    // get patient number input
    printf("Patient Number: ");
    patientNumber = inputIntPositive();

    // find patient
    patientIndex = findPatientIndexByPatientNum(patientNumber, 
                                                patients, maxPatient);
    // Patient not found 
    if (patientIndex < 0) {
        printf("ERROR: Patient record not found!\n\n");
        return;
    }

    // Continue if patient is found
    // Get input for year
    printf("Year        : ");
    date.year = inputIntPositive();

    // Get input for Month
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);

    // Determine the last day of the selected month and year
    day = lastDay(date.year, date.month);
    // get input for day
    printf("Day (1-%d)  : ", day);
    date.day = inputIntRange(1, day);
    printf("\n");

    // validate appointment
    for (i = 0; i < maxAppointments; i++) {
        if (appoints[i].patientNumber == patientNumber &&
            appoints[i].date.year == date.year &&
            appoints[i].date.month == date.month &&
            appoints[i].date.day == date.day) {
            // valid = 1
            valid++;
            // end iteration 
            break;
            }
    }

    // Check if a valid appointment was found
    if (valid) {
        // Display patient data
        displayPatientData(&patients[patientIndex], FMT_FORM);

        // Confirm removal
        printf("Are you sure you want to remove this appointment (y,n): ");
        char confirmation = inputCharOption("yn");
        if (confirmation == 'y') {
            // Remove the appointment by setting patient number to 0
            for (i = 0; i < maxAppointments; i++) {
                if (appoints[i].patientNumber == patientNumber &&
                    appoints[i].date.year == date.year &&
                    appoints[i].date.month == date.month &&
                    appoints[i].date.day == date.day) {
                    appoints[i].patientNumber = 0;
                    printf("\nAppointment record has been removed!\n\n");
                    break;
                }
            }
        }
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

//Import patient data from file into a Patient array(returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max) {
    //Setting ptr to file
    FILE* file;
    //open file
    file = fopen(datafile, "r");

    //error handle if file could not be read
    if (file == NULL) {
        printf("File could not be read");
    }
    
    //Declare line variable
    int line = 0;

    //begin loop to read lines and store in patient array
    while (line < max && fscanf(file, "%d|%[^|]|%[^|]|%[^\n]", 
        &patients[line].patientNumber,
        patients[line].name,
        patients[line].phone.description,
        patients[line].phone.number)
        //Continue reading until end of line
        != EOF) {
            line++;
        }

        //Close file
        fclose(file);
        //return lines read
        return line;

}

// Import appointment data from file into an 
// Appointment array (returns # of records read)
// ToDo:
// Split line to stay under 80 characters 
int importAppointments(const char* datafile, 
    struct Appointment appoints[], int max) {
    //open file
    FILE* file;
    file = fopen(datafile, "r");

    //error handle if file could not be read
    if (file == NULL) {
        printf("File could not be read");
    }

    //set line variable
    int line = 0;

    //Read file and store it into appointment array
    while (line < max && fscanf(file, "%d,%d,%d,%d,%d,%d\n",
    &appoints[line].patientNumber,
    &appoints[line].date.year,
    &appoints[line].date.month,
    &appoints[line].date.day,
    &appoints[line].time.hour,
    &appoints[line].time.min)
    != EOF) {
        line++;
    }

    //Close file
    fclose(file);
    //return lines read
    return line;

}