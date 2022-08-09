// Add file IO to program 4. Create a plain-text file that will store employee information from the program code. 
// The program will have the ability to load the array with the data from the file.

// When the user chooses to load from a file, ask for the name of the file, then load the data into the employee array. 
// If they choose keyboard, load the data as was done previously. Note that the application is going to want to use the 
// folder where the .exe file is located when looking for the file, unless we type in a full or relative path. 
// Using the debug folder is fine for our purposes.

// Once the data is loaded into our array, either from an already existing file, or from keyboard input, 
// we’ll then have our menu from the previous assignment. Before the program exits, you will need to ask for 
// the name of the file to save the data to. If we loaded from a file already, 
// we’ll use the same file and overwrite the contents.

// We don’t need to cover deleting employee data. 
// We can also assume that we only need to handle at most 10 employees worth of data.


#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
//required for pause while saving
#include <unistd.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX 20

typedef struct  
{
    char name[40];
    int empID;
    float hours;
    float rate;
    float gross;
    float base;
    float overtime;
    float tax;
    float net;
} Employees;

void splash();
void saveFile(Employees * employee, int *empCount, float *gross, int* fileChange);
void processMenu(int menuInput, Employees *employee, int *empCount, float *gross, int* fileChange);
float calcEmp(Employees* employee, int *empCount, float *gross, int* fileChange);
int getEmp(int *empCount, Employees* employee, float *gross, int* fileChange);

void loadMenu(Employees *employee, int *empCount, float *gross, int *fileChange)
{
    int menuInput = 0;
    puts("\n\n");
    puts("  MAIN MENU \U0001F6D1");
    puts("  ---------\n\n  Enter a selection to continue: \n");
    puts("  Press 1 to LOAD a record(s) from FILE");
    puts("  Press 2 to ADD a record");
    puts("  Press 3 to UPDATE a record");
    puts("  Press 4 to PRINT a record");
    puts("  Press 5 to PRINT ALL records");
    puts("  Press 6 to SAVE records to FILE");
    puts("  Press 7 to EXIT application\n");
    scanf(" %d", &menuInput);
    processMenu(menuInput, employee, empCount, gross, fileChange);
}

void addRecord(Employees* employee, int* empCount, float *gross, int* fileChange)
{
    int checkInput = 1;
    if (*empCount == MAX)
    {
        printf("Limit reached! You cannot create more than %d employees!\n", MAX);
        loadMenu(employee, empCount, gross, fileChange);
    }
    do{
        printf("Please enter the NAME of employee: ");
        scanf(" %s", employee[*empCount].name);
        checkInput = strcmp (employee[*empCount].name, "-1");
        if (checkInput == 0)
        {
            loadMenu(employee, empCount, gross, fileChange);
        }
        printf("Please enter the PAY RATE of employee:");
        scanf("%f", &employee[*empCount].rate);
        if (employee[*empCount].rate == -1)
        {
            loadMenu(employee, empCount, gross, fileChange);
        }
        printf("Please enter the HOURS of employee: ");
        scanf("%f", &employee[*empCount].hours);
        if (employee[*empCount].hours == -1)
        {
            loadMenu(employee, empCount, gross, fileChange);
        }
        *gross += calcEmp(employee, empCount, gross, fileChange);
        (*empCount) ++;
        printf("\n");
    } while (*empCount<MAX);
}

void updateRecord(Employees* employee, int *empCount, float *gross, int* fileChange)
{
    int selection = getEmp(empCount, employee, gross, fileChange);
    int checkInput=1;
    printf("Please enter the NAME of employee: ");
    scanf(" %s", employee[selection].name);
    checkInput = strcmp (employee[selection].name, "-1");
    if (checkInput == 0)
    {
        loadMenu(employee, empCount, gross, fileChange);
    }
    printf("Please enter the PAY RATE of employee:");
    scanf("%f", &employee[selection].rate);
    if (employee[selection].rate == -1)
    {
        loadMenu(employee, empCount, gross, fileChange);
    }
    printf("Please enter the HOURS of employee : ");
    scanf("%f", &employee[selection].hours);
    if (employee[selection].hours == -1)
    {
        loadMenu(employee, empCount, gross, fileChange);
    }
    *gross += calcEmp(employee, empCount, gross, fileChange);
    printf("\n");
}

float calcEmp(Employees* employee, int *empCount, float *gross, int* fileChange)
{
    if (employee[*empCount].hours <= 40.0f)
    {
        employee[*empCount].base = employee[*empCount].hours * employee[*empCount].rate;
        employee[*empCount].overtime = 0.0f;
        employee[*empCount].gross = employee[*empCount].base;
        
    }
    else if (employee[*empCount].hours > 40.0f)
    {
        employee[*empCount].base = (40.0f) * employee[*empCount].rate;
        employee[*empCount].overtime = (employee[*empCount].hours - 40.0f) * employee[*empCount].rate * 1.5f;
        employee[*empCount].gross = employee[*empCount].base + employee[*empCount].overtime;
    }
    employee[*empCount].tax = employee[*empCount].gross * 0.2f;
    employee[*empCount].net = employee[*empCount].gross - employee[*empCount].tax;

    return employee[*empCount].gross;
}



int getEmp(int *empCount, Employees* employee, float *gross, int* fileChange)
{
    int selection;
    int i;
    do{
        puts("Select an employee: ");
        for (int i = 0; i < *empCount; i++)
        {
            printf("Employee %d: %s\n", i+1, employee[i].name);
        }
        scanf("%d", &selection);
        if (selection == -1)
        {
            loadMenu(employee, empCount, gross, fileChange);
        }
    } while (selection > (*empCount + 1) || selection < 1);
    
    selection--;
    return selection;
}

void printRecord_single(Employees* employee, int *empCount, float *gross, int* fileChange)
{
    int selection = getEmp(empCount, employee, gross, fileChange);
    printf("\n\nEmployee #%d NAME: %s", selection+1, employee[selection].name);
    printf("\nEmployee #%d HOURS worked: %.1f",selection+1, employee[selection].hours);
    printf("\nEmployee #%d RATE hourly: $%.2f",selection+1, employee[selection].rate);
    printf("\nEmployee #%d BASE amount: $%.2f", selection+1, employee[selection].base);
    printf("\nEmployee #%d GROSS amount: $%.2f", selection+1, employee[selection].gross);
    printf("\nEmployee #%d OVERTIME amount: $%.2f", selection+1, employee[selection].overtime);
    printf("\nEmployee #%d TAXES paid: $%.2f", selection+1, employee[selection].tax);
    printf("\nEmployee #%d NET paid: $%.2f", selection+1, employee[selection].net);
    loadMenu(employee, empCount, gross, fileChange);
} 
void printRecord_all(Employees * employee, int *empCount, float *gross, int* fileChange)
{
    for (int i = 0; i < *empCount; i++)
        {
            printf("\n\nEmployee #%d NAME: %s", i+1, employee[i].name);
            printf("\nEmployee #%d HOURS worked: %.1f", i+1, employee[i].hours);
            printf("\nEmployee #%d RATE hourly: $%.2f", i+1, employee[i].rate);
            printf("\nEmployee #%d BASE amount: $%.2f", i+1, employee[i].base);
            printf("\nEmployee #%d GROSS amount: $%.2f", i+1, employee[i].gross);
            printf("\nEmployee #%d OVERTIME amount: $%.2f", i+1, employee[i].overtime);
            printf("\nEmployee #%d TAXES paid: $%.2f", i+1, employee[i].tax);
            printf("\nEmployee #%d NET paid: $%.2f", i+1, employee[i].net);
        }
    printf("\n\nTOTAL PAYROLL COST: $%.2f", *gross);
    loadMenu(employee, empCount, gross, fileChange);
}


void loadFile(Employees * employee, int *empCount, float *gross, int* fileChange)
{
    char fileName[30];
    puts("Filename to load?");
    scanf(" %s", fileName);
    puts("Loading...\n");
    sleep(1);
    FILE *inputFile;
    inputFile = fopen(fileName, "r");
    if (inputFile == NULL)
    {
        puts("Error- Can't open file! Is it available?");
        loadMenu(employee, empCount, gross, fileChange);
    }

        char ch;
        int count= 0;
        int i=0;
            
        //determine number of lines
        do{
            ch = fgetc(inputFile);
            if (ch == '\n') 
            {
                count ++;
            }
        }while(ch != EOF);
        rewind(inputFile);
        *empCount = 0;
      
        for (int i = 0; i < count; i++, (*empCount)++)
            {
                fscanf(inputFile, "%s %f %f", employee[i].name,
                                    &employee[i].hours, &employee[i].rate);
                printf("%s %f %f\n", employee[i].name,
                                    employee[i].hours, employee[i].rate);
                *gross += calcEmp(employee, empCount, gross, fileChange);
            }
        printf("\nSUCCESS!\n%d employees were loaded\n",*empCount);
}

void saveFile(Employees * employee, int *empCount, float *gross, int* fileChange)
{
    
    if (*empCount <1)
    {
        puts("Nothing to save. Add a record from the main menu\n\n");
        loadMenu(employee, empCount, gross, fileChange);
    }
    char fileName[30];
    puts("Filename to save?\n");
    scanf(" %s", fileName);
    puts("Saving...\n");
    FILE *outputFile;
    outputFile = fopen(fileName, "w");
    sleep(1);
    
    for (int i = 0; i < *empCount; i++)
        {
            printf("\n\nEmployee #%d NAME: %s", i+1, employee[i].name);
            fprintf(outputFile, " %s ", employee[i].name);
            
            printf("\nEmployee #%d HOURS worked: %.1f", i+1, employee[i].hours);
            fprintf(outputFile, " %.1f", employee[i].hours);
            
            printf("\nEmployee #%d RATE hourly: $%.2f", i+1, employee[i].rate);
            fprintf(outputFile, " %.2f \n", employee[i].rate);
        }
    printf("\n\n SAVED!\n\nYour data was saved with the filename '%s'\n\n", fileName);
    fclose(outputFile);
}

void processMenu(int menuInput, Employees *employee, 
                    int *empCount, float *gross, int* fileChange)
{
    char saveChoice;
    switch(menuInput) 
    {
        case 1:
            puts("\nYour selection: 1 - LOAD file\n");
            loadFile(employee, empCount, gross, fileChange);
            loadMenu(employee, empCount, gross, fileChange);
        case 2:
            puts("\nYour selection: 2 - ADD a record\n");
            addRecord(employee, empCount, gross, fileChange);
            *fileChange++;
            loadMenu(employee, empCount, gross, fileChange );
        case 3:
            puts("\nYour selection: 3 - UPDATE a record\n");
            updateRecord(employee, empCount, gross,fileChange);
            *fileChange++;
            loadMenu(employee, empCount, gross, fileChange);
        case 4  :
            puts("\nYour selection: 4 - PRINT SINGLE record\n");
            printRecord_single(employee, empCount, gross, fileChange);
            loadMenu(employee, empCount, gross, fileChange);
        case 5 :
            puts("\nYour selection: 5 - PRINT ALL records\n");
            printRecord_all(employee, empCount, gross, fileChange);
            loadMenu(employee, empCount, gross, fileChange);
        case 6:
            puts("\nYour selection: 6 - SAVE file\n");
            saveFile(employee, empCount, gross, fileChange);
            *fileChange = 0;
            loadMenu(employee, empCount, gross, fileChange);
        case 7:
            if (*fileChange > 0)
            {
                puts("\nYou have unsaved data - SAVE to file? \n\n Save File [Y] or [y]\n Return to Main Menu [R] or [r]\n Exit Without Saving\n");
                scanf(" %c", &saveChoice);
                if (saveChoice == 'y' || saveChoice == 'Y')
                {
                    saveFile(employee, empCount, gross, fileChange);
                }
                else (saveChoice == 'm' || saveChoice == 'Y');
                {
                    loadMenu(employee, empCount, gross, fileChange);
                }
            }
            puts("\nGoodbye! \U0001F44B\n");
            exit(0);
            
        default :
            puts("Invalid input! Try again");
            loadMenu(employee, empCount, gross, fileChange);
    } 
}

int main(void) 
{   
    splash();
    int selection;
    int empCount = 0;
    int fileChange = 0;
    float gross = 0.2f;
    Employees employee[MAX];
    loadMenu(employee, &empCount, &gross, &fileChange);
    return 0;
}


void splash()
{    
    puts("\n\n\n\n\n");
    puts("                                                                             d8b");
    puts("                                                                             88P");
    puts("                                                                            d88");
    puts("                      ?88,.d88b,     d888b8b      ?88   d8P      d8888b     888       d888b8b");
    puts("                      `?88'  ?88    d8P' ?88      d88   88      d8P' ?88    ?88      d8P' ?88");
    puts("                        88b  d8P    88b  ,88b     ?8(  d88      88b  d88     88b     88b  ,88b ");
    puts("                        888888P'    `?88P'`88b    `?88P'?8b     `?8888P'      88b    `?88P'`88b");
    puts("                       88P'                             )88");
    puts("                       d88                              ,d8P");
    puts("                       ?8P                           `?888P'");
    puts("\n\n\n\n");
    puts("                                                      \U0001F4B2\n");
    puts("                              Welcome to Payola: A Payroll Reporting Application\n");
    puts("                                               Developed by CHEYNOLDS");
    puts("                                                   Coded by CHEYNOLDS\n");
    puts("                                                      \U0001FAE0\n");
    puts("                                                     Version 0.0.5\n");
    puts("\n\n");
    puts("                                                  Press enter to begin\n");
    getchar();
    system("clear");
}
