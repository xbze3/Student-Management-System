#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LSIZ 1280
#define RSIZ 100
#define TOTAL 4

FILE *fptr = NULL;
FILE *fptw = NULL;
FILE *fptw2 = NULL;

char line[RSIZ][LSIZ];
int i = 0;
int tot = 0;
int ret;

char filename[] = "database.txt";
char altFilename[] = "database_alt.txt";

char userCommand[50];

struct studentInfo
{
    int studentID;
    char studentName[50];
    float mathScore;
    float englishScore;
    float scienceScore;
    float socialStudiesScore;
    float averageScore;
};

void displayRecords()
{
    for(i = 0; i < tot; ++i)
    {
        if((i % 6) == 0)
        {
            printf("\nStudent ID: %s\n", line[i]);
        }

        else if((i % 6) == 1)
        {
            printf("Student Name: %s\n", line[i]);
        }

        else if((i % 6) == 2)
        {
            printf("Math Score: %s\n", line[i]);
        }

        else if((i % 6) == 3)
        {
            printf("English Score: %s\n", line[i]);
        }

        else if((i % 6) == 4)
        {
            printf("Science Score: %s\n", line[i]);
        }

        else if((i % 6) == 5)
        {
            printf("Social Studies Score: %s\n", line[i]);
        }

        else if((i % 6) == 0 && i != 0)
        {
            printf("Student ID: %s\n", line[i]);
        }
    }
}

void findStudentByName()
{
    int found = 0;
    char studentName[50];
    printf("Student Name: ");
    scanf("%s", studentName);

    for(i = 0; i < tot; ++i)
    {
        if(strcmp(studentName, line[i]) == 0)
        {
            printf("\nStudent ID: %s\n", line[i - 1]);
            printf("Student Name: %s\n", line[i]);
            printf("Math Score: %s\n", line[i + 1]);
            printf("English Score: %s\n", line[i + 2]);
            printf("Science Score: %s\n", line[i + 3]);
            printf("Social Studies Score: %s\n", line[i + 4]);
            found = 1;

            break;
        }
    }

    if(found == 0)
    {
        printf("Student Not Found\n");
    }
}

void findStudentById()
{
    int found = 0;
    int studentId;
    printf("Student ID: ");
    scanf("%d", &studentId);

    for(i = 0; i < tot; ++i)
    {
        if((atoi(line[i]) == studentId) && (i % 6) == 0)
        {
            printf("\nStudent ID: %s\n", line[i]);
            printf("Student Name: %s\n", line[i + 1]);
            printf("Math Score: %s\n", line[i + 2]);
            printf("English Score: %s\n", line[i + 3]);
            printf("Science Score: %s\n", line[i + 4]);
            printf("Social Studies Score: %s\n", line[i + 5]);
            found = 1;

            break;
        }
    }

    if(found == 0)
    {
        printf("Student Not Found\n");
    }
}

void addStudent()
{
    int found = 0;
    char studentName[50];
    printf("\nStudent Name: ");
    scanf("%s", studentName);

    for(i = 0; i < tot; ++i)
    {
        if(strcmp(line[i], studentName) == 0)
        {
            found = 1;
            printf("Student already in database\n");

            break;
        }
    }


    if(found == 0)
    {
        int idCount = 1;
        struct studentInfo newStudent;

        for(i = 0; i < tot; ++i)
        {
            if((i % 6) == 0)
            {
                idCount++;
            }
        }

        newStudent.studentID = idCount;
        strcpy(newStudent.studentName, studentName);


        printf("Student Math Score: ");
        scanf("%f", &newStudent.mathScore);

        printf("Student English Score: ");
        scanf("%f", &newStudent.englishScore);

        printf("Student Science Score: ");
        scanf("%f", &newStudent.scienceScore);

        printf("Student Social Studies Score: ");
        scanf("%f", &newStudent.socialStudiesScore);

        printf("\nNew Student ID: %d\n", newStudent.studentID);
        printf("New Student Name: %s\n", newStudent.studentName);
        printf("New Student Math Score: %.2f\n", newStudent.mathScore);
        printf("New Student English Score: %.2f\n", newStudent.englishScore);
        printf("New Student Science Score: %.2f\n", newStudent.scienceScore);
        printf("New Student Social Studies Score: %.2f\n", newStudent.socialStudiesScore);

        fprintf(fptw, "%d", newStudent.studentID);
        fprintf(fptw, "\n%s", newStudent.studentName);
        fprintf(fptw, "\n%.2f", newStudent.mathScore);
        fprintf(fptw, "\n%.2f", newStudent.englishScore);
        fprintf(fptw, "\n%.2f", newStudent.scienceScore);
        fprintf(fptw, "\n%.2f\b\n", newStudent.socialStudiesScore);

        printf("New Student added to database successfully (Reload to see changes)\n");
    }
}

void calculateAverage(int i)
{
    struct studentInfo currentStudent;

    currentStudent.studentID = atoi(line[i]);
    strcpy(currentStudent.studentName, line[i + 1]);
    currentStudent.mathScore = atof(line[i + 2]);
    currentStudent.englishScore = atof(line[i + 3]);
    currentStudent.scienceScore = atof(line[i + 4]);
    currentStudent.socialStudiesScore = atof(line[i + 5]);
    currentStudent.averageScore = (currentStudent.mathScore + currentStudent.englishScore + currentStudent.scienceScore + currentStudent.socialStudiesScore) / TOTAL;

    printf("\nStudent ID: %d\n", currentStudent.studentID);
    printf("Student Name: %s\n", currentStudent.studentName);
    printf("Student Math Score: %.2f\n", currentStudent.mathScore);
    printf("Student English Score: %.2f\n", currentStudent.englishScore);
    printf("Student Science Score: %.2f\n", currentStudent.scienceScore);
    printf("Student Social Studies Score: %.2f\n", currentStudent.socialStudiesScore);
    printf("Average Score: %.2f\n", currentStudent.averageScore);
}

void calculateAverageScoreDisplay()
{
    for(i = 0; i < tot; i = i + 6)
    {
        calculateAverage(i);
    }
}

void calculateAverageScoreSingleID()
{
    printf("\nStudent ID: ");
    scanf("%s", userCommand);

    for(i = 0; i < tot; ++i)
    {
        if(strcmp(userCommand, line[i]) == 0)
        {
            calculateAverage(i);
            break;
        }

    }
}

void calculateAverageScoreSingleName()
{
    printf("\nStudent Name: ");
    scanf("%s", userCommand);

    for(i = 0; i < tot; ++i)
    {
        if(strcmp(userCommand, line[i]) == 0)
        {
            calculateAverage(i - 1);
            break;
        }

    }
}

void updateScoreByID()
{
    struct studentInfo studentUpdate;
    float tempScore;
    int subjectChoice = 0;
    int dest = 0;
    int subjectDest = 0;

    int valid = 0;
    printf("\nStudent ID: ");
    scanf("%s", userCommand);

    for(i = 0; i < tot; ++i)
    {
        if(strcmp(line[i], userCommand) == 0)
        {
            studentUpdate.studentID = atoi(line[i]);
            strcpy(studentUpdate.studentName, line[i + 1]);
            studentUpdate.mathScore = atof(line[i + 2]);
            studentUpdate.englishScore = atof(line[i + 3]);
            studentUpdate.scienceScore = atof(line[i + 4]);
            studentUpdate.socialStudiesScore = atof(line[i + 5]);


            printf("\nStudent %s selected\n", studentUpdate.studentName);
            printf("Subject Score to be updated\n(1 - Math | 2 - English | 3 - Science | 4 - Social Studies): ");
            scanf("%d", &subjectChoice);

            dest = i;
        }
    }

    if(subjectChoice == 1)
    {
        printf("\nNew Math Score: ");
        scanf("%f", &tempScore);

        printf("\nPrevious Math Score: %.2f", studentUpdate.mathScore);
        studentUpdate.mathScore = tempScore;
        printf("\nNew Math Score: %.2f\n", studentUpdate.mathScore);

        valid = 1;
        subjectDest = dest + 2;
    }

    else if(subjectChoice == 2)
    {
        printf("\nNew English Score: ");
        scanf("%f", &tempScore);

        printf("\nPrevious English Score: %.2f", studentUpdate.englishScore);
        studentUpdate.englishScore = tempScore;
        printf("\nNew English Score: %.2f\n", studentUpdate.englishScore);

        valid = 1;
        subjectDest = dest + 3;
    }

    else if(subjectChoice == 3)
    {
        printf("\nNew Science Score: ");
        scanf("%f", &tempScore);

        printf("\nPrevious Science Score: %.2f", studentUpdate.scienceScore);
        studentUpdate.scienceScore = tempScore;
        printf("\nNew Math Score: %.2f\n", studentUpdate.scienceScore);

        valid = 1;
        subjectDest = dest + 4;
    }

    else if(subjectChoice == 4)
    {
        printf("\nNew Social Studies Score: ");
        scanf("%f", &tempScore);

        printf("\nPrevious Social Studies Score: %.2f", studentUpdate.socialStudiesScore);
        studentUpdate.socialStudiesScore = tempScore;
        printf("\nNew Social Studies Score: %.2f\n", studentUpdate.socialStudiesScore);

        valid = 1;
        subjectDest = dest + 5;
    }
    else if(subjectChoice == 0)
    {
        printf("\nInvalid Command\n");
    }

    if(valid == 1)
    {
        for(i = 0; i < tot; ++i)
        {
            if((i == subjectDest))
            {
                if(subjectChoice == 1)
                {
                    sprintf(userCommand, "%.2f", studentUpdate.mathScore);
                    fprintf(fptw2, "%s\n", userCommand);
                }

                else if(subjectChoice == 2)
                {
                    sprintf(userCommand, "%.2f", studentUpdate.englishScore);
                    fprintf(fptw2, "%s\n", userCommand);
                }

                else if(subjectChoice == 3)
                {
                    sprintf(userCommand, "%.2f", studentUpdate.scienceScore);
                    fprintf(fptw2, "%s\n", userCommand);
                }

                else if(subjectChoice == 4)
                {
                    sprintf(userCommand, "%.2f", studentUpdate.socialStudiesScore);
                    fprintf(fptw2, "%s\b\n", userCommand);
                }

            }

            else
            {
                fprintf(fptw2, "%s\n", line[i]);
            }
        }

        fclose(fptr);
        fclose(fptw);
        fclose(fptw2);

        ret = remove(filename) + rename(altFilename, filename);

        if(ret == 0)
        {
          printf("Operation Successful\n");
          printf("Restart program to see changes\n");
        }

        else
        {
          printf("Operation Error\n");
        }
    }
}

void help()
{
    printf("\n");
    printf("  *********************************************** Command List ************************************************\n");
    printf("  * help         - Show this help screen                                                                      *\n");
    printf("  * cls          - Clear terminal screen                                                                      *\n");
    printf("  * show-normal  - Show normal display screen                                                                 *\n");
    printf("  * show-avg     - Show display screen with average-score calculations                                        *\n");
    printf("  * find-name    - Find student by name in database                                                           *\n");
    printf("  * find-id      - Find student by their associated ID                                                        *\n");
    printf("  * add          - Add student to database                                                                    *\n");
    printf("  * id-avg       - Return average-score of a student with a particular ID                                     *\n");
    printf("  * name-avg     - Return average-score of a student with a particular name                                   *\n");
    printf("  * update-score - Allows for the updating of a student's score for a particular subject if their ID is known *\n");
    printf("  *                                                                                                           *\n");
    printf("  *                          Please make use of '-' character in the place of spaces                          *\n");
    printf("  *************************************************************************************************************\n");
}

int main()
{
    fptr = fopen("database.txt", "r");
    fptw = fopen("database.txt", "a");
    fptw2 = fopen("database_alt.txt", "w");

    while(fgets(line[i], LSIZ, fptr))
	{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }

    tot = i;

    help();

    while(1)
    {
        printf("\nhelp> ");
        scanf("%s", userCommand);

        if(strcmp(userCommand, "exit") == 0)
        {
            break;
        }

        else if(strcmp(userCommand, "show-normal") == 0)
        {
            system("cls");
            displayRecords();
        }

        else if(strcmp(userCommand, "show-avg") == 0)
        {
            system("cls");
            calculateAverageScoreDisplay();
        }

        else if(strcmp(userCommand, "find-name") == 0)
        {
            system("cls");
            findStudentByName();
        }

        else if(strcmp(userCommand, "find-id") == 0)
        {
            system("cls");
            findStudentById();
        }

        else if(strcmp(userCommand, "add") == 0)
        {
            system("cls");
            addStudent();
        }

        else if(strcmp(userCommand, "id-avg") == 0)
        {
            system("cls");
            calculateAverageScoreSingleID();
        }

        else if(strcmp(userCommand, "name-avg") == 0)
        {
            system("cls");
            calculateAverageScoreSingleName();
        }

        else if(strcmp(userCommand, "update-score") == 0)
        {
            system("cls");
            updateScoreByID();
        }

        else if(strcmp(userCommand, "cls") == 0)
        {
            system("cls");
        }

        else if(strcmp(userCommand, "help") == 0)
        {
            help();
        }

        else
        {
            printf("\nInvalid Command\n");
        }
    }

    printf("\n");
    fclose(fptr);
    fclose(fptw);
    fclose(fptw2);

    return 0;
}
