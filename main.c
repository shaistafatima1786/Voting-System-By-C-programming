#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "defination.h"

int main()
{
    welcome();

    bool isRunning = true;
    int choice = 0;
    mainMenu();

    do
    {
        printf("\nSelect login panel: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            adminCredentialsForm();
            adminMenu();
            adminFunctionality();
            break;
        case 2:
            registerVoter();
            break;
        case 3:
            castVote();
            break;
        case 4:
            printf("\n-------------------------------------\n");
            printf("   Successfully closed the program   \n");
            printf("-------------------------------------\n\n");
            isRunning = false;
            break;
        default:
            printf("\n-------------------------------------\n");
            printf("   Invalid choice. Please try again   \n");
            printf("-------------------------------------\n\n");
            mainMenu();
            break;
        }
    } while (isRunning != false);
}

void welcome()
{
    printf("\n");
    printf("       WELCOME  TO  VOTING  SYSTEM       \n");
    printf("------------------------------------------\n\n");
}

void mainMenu()
{
    printf("1) Admin\n");
    printf("2) Voter Register\n");
    printf("3) Cast Vote\n");
    printf("4) Exit\n");
}

void adminMenu()
{
    printf("Election Mangement System\n");
    printf("1. Election Schedule\n");
    printf("2. Candidate Registration\n");
    printf("3. Candidate Update\n");
    printf("4. Delete Candidate\n");
    printf("5. List of Candidate\n");
    printf("6. Update Voter\n");
    printf("7. Delete Voter\n");
    printf("8. Voter Serarch\n");
    printf("9. Voter Result\n");
    printf("10. Logout\n");
}

void adminCredentialsForm()
{
    char seedUsername[20] = "admin";
    char seedPassword[20] = "password";

    bool isInvalid = true;

    while (isInvalid)
    {
        char username[20];
        char password[20];

        printf("\nEnter Username: ");
        scanf("%s", username);

        printf("Enter Password: ");
        scanf("%s", password);

        if (strcmp(username, seedUsername) == 0 && strcmp(password, seedPassword) == 0)
        {
            printf("\n--------------------------------------------\n");
            printf("      Successfully login as Admin user   \n");
            printf("--------------------------------------------\n\n");
            isInvalid = false;
            break;
        }
        else
        {
            printf("\n--------------------------------------------\n");
            printf("        Invalid username or password.   \n");
            printf("--------------------------------------------\n\n");
        }
    }
}

void adminFunctionality()
{
    int choice;
    bool isRunning = true;

    do
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createElectionSchedule();
            break;
        case 2:
            registerCandidate();
            break;
        case 3:
            updateCandidateDetails();
            break;
        case 4:
            deleteCandidate();
            break;
        case 5:
            listCandidateDetails();
            break;
        case 6:
            updateVoterDetails();
            break;
        case 7:
            deleteVoter();
            break;
        case 8:
            searchVoterDetails();
        case 9:
            displayVoteResult();
            break;
        case 10:
            printf("\n--------------------------------------------------\n");
            printf("  You have successfully logout from admin panel   \n");
            printf("--------------------------------------------------\n\n");
            isRunning = false;
            break;
        default:
            printf("\n--------------------------------------------\n");
            printf("      Invalid choic please try again   \n");
            printf("--------------------------------------------\n\n");
            adminMenu();
            break;
        }
    } while (isRunning);
    mainMenu();
}

// ------------------------- Function that Admin does ------------------------------

void createElectionSchedule()
{
    int counter;
    printf("Enter the number of constituency: ");
    scanf("%d", &counter);

    struct ElectionSchedule schedule;
    FILE *file = fopen("schedule.txt", "a"); // Use "a" instead of "w" to append to the file

    if (file == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Opening a file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        return;
    }

    for (int i = 0; i < counter; i++)
    {
        printf("Enter the constituency: ");
        scanf(" %[^\n]", schedule.constituency);
        printf("Enter the date (yyyymmdd): ");
        scanf("%s", schedule.date);

        fprintf(file, "%s %s\n", schedule.constituency, schedule.date);
    }

    printf("\n-------------------------------------------------------\n");
    printf("   Election schedule created and saved successfully.   \n");
    printf("-------------------------------------------------------\n\n");
    fclose(file);

    listConstitutionDetails();

    adminMenu();
}

// Function to register a candidate
void registerCandidate()
{
    struct Candidate candidate;
    FILE *file = fopen("candidatelist.txt", "a");

    if (file == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Opening a file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        return;
    }

    printf("Enter the candidate name: ");
    scanf(" %[^\n]", candidate.name);
    printf("Enter the party name: ");
    scanf(" %[^\n]", candidate.party);
    printf("Enter the candidancy from: ");
    scanf(" %[^\n]", candidate.candidancyFrom);

    const char *fileName = "candidatelist.txt";
    int id = generateUniqueIDFromFIle(fileName);
    candidate.id = id;

    fprintf(file, "%d %s %s %s\n", candidate.id, candidate.name, candidate.party, candidate.candidancyFrom);
    fclose(file);

    printf("Candidate registered successfully.\n");

    adminMenu();
}

void updateCandidateDetails()
{
    int id;
    printf("Enter the serial number of the candidate: ");
    scanf("%d", &id);

    FILE *file = fopen("candidatelist.txt", "r");
    if (file == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Opening a file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("\n-------------------------------------------------------\n");
        printf("   Error Creating a temporary file. Please try again   \n");
        printf("-------------------------------------------------------\n\n");
        fclose(file);
        return;
    }

    struct Candidate candidate;
    bool found = false;

    while (fscanf(file, "%d %s %s %s\n", &candidate.id, candidate.name, candidate.party, candidate.candidancyFrom) != EOF)
    {
        if (candidate.id == id)
        {
            found = true;
            printf("Enter the new candidate name: ");
            scanf(" %[^\n]", candidate.name);
            printf("Enter the new candidate party: ");
            scanf("%s", candidate.party);
            printf("Enter the candidate new address: ");
            scanf(" %[^\n]", candidate.candidancyFrom);

            fprintf(tempFile, "%d %s %s %s\n", candidate.id, candidate.name, candidate.party, candidate.candidancyFrom);
        }
        else
        {
            fprintf(tempFile, "%d %s %s %s\n", candidate.id, candidate.name, candidate.party, candidate.candidancyFrom);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove("candidatelist.txt");
        rename("temp.txt", "candidatelist.txt");

        printf("\n------------------------------------------\n");
        printf("   Candidate details updated successfully   \n");
        printf("------------------------------------------\n\n");
    }
    else
    {
        remove("temp.txt");
        printf("\n---------------------------------------------\n");
        printf("   Candidate with candidate id %d not found   \n", id);
        printf("---------------------------------------------\n\n");
    }

    adminMenu();
}

void deleteCandidate()
{
    int id;
    printf("Enter the id of candidate to be deleted: ");
    scanf("%d", &id);

    FILE *file = fopen("candidatelist.txt", "r");
    if (file == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Opening a file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Creating a temporary file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        fclose(file);
        return;
    }

    struct Candidate candidate;
    bool found = false;

    while (fscanf(file, "%d %s %s %s\n", &candidate.id, candidate.name, candidate.party, candidate.candidancyFrom) != EOF)
    {
        if (candidate.id == id)
        {
            found = true;
            continue; // Skip writing this voter to the temporary file (effectively deleting it)
        }

        fprintf(tempFile, "%d %s %s %s\n", candidate.id, candidate.name, candidate.party, candidate.candidancyFrom);
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove("candidatelist.txt");
        rename("temp.txt", "candidatelist.txt");

        printf("\n------------------------------------------\n");
        printf("     Candidate deleted successfully   \n");
        printf("------------------------------------------\n\n");
    }
    else
    {
        remove("temp.txt");
        printf("\n----------------------------------------------\n");
        printf("   Candidate with candidate id %d not found   \n", id);
        printf("----------------------------------------------\n\n");
    }

    adminMenu();
}

void listCandidateDetails()
{
    FILE *file = fopen("candidatelist.txt", "r");
    if (file == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Opening the file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        return;
    }

    struct Candidate candidate;

    printf("\n------------------------------------------\n");
    printf("   Candidate Details\n");
    printf("------------------------------------------\n\n");

    while (fscanf(file, "%d %s %s %[^\n]", &candidate.id, candidate.name, candidate.party, candidate.candidancyFrom) != EOF)
    {
        printf("ID: %d\n", candidate.id);
        printf("Name: %s\n", candidate.name);
        printf("Party: %s\n", candidate.party);
        printf("Candidacy From: %s\n", candidate.candidancyFrom);
        printf("------------------------------------------\n");
    }

    printf("\n");
    fclose(file);
    adminMenu();
}

void updateVoterDetails()
{
    int sno;
    printf("Enter the serial number of the voter: ");
    scanf("%d", &sno);

    FILE *file = fopen("voterlist.txt", "r");
    if (file == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Opening a file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Creating a temporary file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        fclose(file);
        return;
    }

    struct Voter voter;
    bool found = false;

    while (fscanf(file, "%d %s %s %s %s\n", &voter.sno, voter.name, voter.dateOfBirth, voter.address, voter.password) != EOF)
    {
        if (voter.sno == sno)
        {
            found = true;
            printf("Enter the new voter name: ");
            scanf(" %[^\n]", voter.name);
            printf("Enter the new date of birth (yyyymmdd): ");
            scanf("%s", voter.dateOfBirth);
            printf("Enter the new address: ");
            scanf(" %[^\n]", voter.address);
            printf("Enter the new password: ");
            scanf("%s", voter.password);

            fprintf(tempFile, "%d %s %s %s %s\n", voter.sno, voter.name, voter.dateOfBirth, voter.address, voter.password);
        }
        else
        {
            fprintf(tempFile, "%d %s %s %s %s\n", voter.sno, voter.name, voter.dateOfBirth, voter.address, voter.password);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove("voterlist.txt");
        rename("temp.txt", "voterlist.txt");

        printf("\n------------------------------------------\n");
        printf("   Voter details updated successfully   \n");
        printf("------------------------------------------\n\n");
    }
    else
    {
        remove("temp.txt");
        printf("\n----------------------------------------\n");
        printf("   Voter with voter id %d not found   \n", sno);
        printf("----------------------------------------\n\n");
    }

    adminMenu();
}

void deleteVoter()
{
    int sno;
    printf("Enter the serial number of the voter: ");
    scanf("%d", &sno);

    FILE *file = fopen("voterlist.txt", "r");
    if (file == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Opening a file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Creating a temporary file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        fclose(file);
        return;
    }

    struct Voter voter;
    bool found = false;

    while (fscanf(file, "%d %s %s %s %s\n", &voter.sno, voter.name, voter.dateOfBirth, voter.address, voter.password) != EOF)
    {
        if (voter.sno == sno)
        {
            found = true;
            continue; // Skip writing this voter to the temporary file (effectively deleting it)
        }

        fprintf(tempFile, "%d %s %s %s %s\n", voter.sno, voter.name, voter.dateOfBirth, voter.address, voter.password);
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove("voterlist.txt");
        rename("temp.txt", "voterlist.txt");

        printf("\n------------------------------------------\n");
        printf("   Voter deleted successfully   \n");
        printf("------------------------------------------\n\n");
    }
    else
    {
        remove("temp.txt");
        printf("\n----------------------------------------\n");
        printf("   Voter with voter id %d not found   \n", sno);
        printf("----------------------------------------\n\n");
    }

    adminMenu();
}


void displayVoteResult()
{
    FILE *candidateFile = fopen("candidatelist.txt", "r");
    FILE *voteCountFile = fopen("votecount.txt", "r");

    if (candidateFile == NULL || voteCountFile == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Opening a file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        return;
    }

    struct VoteCount voteCount;
    struct VoteCount highestVoteCount;
    int highest = 0;
    bool isEmpty = true;

    printf("\n---------------------------------------------\n");
    printf("                  VOTING RESULT               \n");
    printf("---------------------------------------------\n\n");

    while (fscanf(voteCountFile, "%d %s %s %s %d\n", &voteCount.candidate.id, voteCount.candidate.name, voteCount.candidate.party, voteCount.candidate.candidancyFrom, &voteCount.count) != EOF)
    {
        isEmpty = false;
        printf("\nCandidate ID: %d\n", voteCount.candidate.id);
        printf("Candidate Name: %s\n", voteCount.candidate.name);
        printf("Candidate Party: %s\n", voteCount.candidate.party);
        printf("Candidate Address: %s\n", voteCount.candidate.candidancyFrom);
        printf("Vote Count: %d\n", voteCount.count);
        printf("--------------------\n\n");

        if (voteCount.count > highest)
        {
            highest = voteCount.count;
            highestVoteCount = voteCount;
        }
    }

    if (isEmpty)
    {
        printf("\n There is no any voting details to display \n\n");
    }

    printf("\n---------------------------------------------\n");
    printf("         CANDIDATE WITH HIGHEST VOTE          \n");
    printf("---------------------------------------------\n\n");

    if (isEmpty)
    {
        printf("There is no any voting details. So we cannot display the highest vote \n\n\n");
    }
    else
    {
        // Display the details of the candidate who has won
        printf("Candidate ID: %d\n", highestVoteCount.candidate.id);
        printf("Candidate Name: %s\n", highestVoteCount.candidate.name);
        printf("Candidate Party: %s\n", highestVoteCount.candidate.party);
        printf("Candidate Address: %s\n", highestVoteCount.candidate.candidancyFrom);
        printf("Vote Count: %d\n\n", highestVoteCount.count);
    }

    // Reset the file pointer to the beginning of the candidate file
    rewind(candidateFile);

    printf("\n---------------------------------------------\n");
    printf("           ALL CANDIDATES LIST           \n");
    printf("---------------------------------------------\n\n");

    while (fscanf(candidateFile, "%d %s %s %[^\n]", &voteCount.candidate.id, voteCount.candidate.name, voteCount.candidate.party, voteCount.candidate.candidancyFrom) != EOF)
    {
        printf("\nCandidate ID: %d\n", voteCount.candidate.id);
        printf("Candidate Name: %s\n", voteCount.candidate.name);
        printf("Candidate Party: %s\n", voteCount.candidate.party);
        printf("Candidate Address: %s\n", voteCount.candidate.candidancyFrom);
        printf("--------------------\n\n");
    }

    fclose(candidateFile);
    fclose(voteCountFile);
    adminMenu();
}

void listConstitutionDetails()
{
    FILE *file = fopen("schedule.txt", "r");
    if (file == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Opening the file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        return;
    }

    struct ElectionSchedule schedule;

    printf("\n------------------------------------------\n");
    printf("       Election Schedule Details           \n");
    printf("------------------------------------------\n\n");

    while (fscanf(file, "%s %s", schedule.constituency, schedule.date) != EOF)
    {
        printf("Name: %s\n", schedule.constituency);
        printf("Date: %s\n", schedule.date);
        printf("------------------------------------------\n");
    }

    printf("\n");
    fclose(file);
}

//---------------------For voter functionality---------------------------

// Function to register a voter
void registerVoter()
{
    struct Voter voter;
    FILE *file = fopen("voterlist.txt", "a");

    if (file == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Opening a file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        return;
    }

    printf("Enter the voter name: ");
    scanf(" %[^\n]", voter.name);
    printf("Enter the date of birth (yyyymmdd): ");
    scanf("%s", voter.dateOfBirth);
    printf("Enter the address: ");
    scanf(" %[^\n]", voter.address);
    printf("Enter the password: ");
    scanf("%s", voter.password);

    // Calculate age from date of birth
    int age = calculateAge(voter.dateOfBirth);

    // Check eligibility based on age
    if (age <= 18)
    {
        printf("\n-----------------------------------------------------------\n");
        printf("   Voter is not eligible. Minimum age requirement is 18.   \n");
        printf("------------------------------------------------------------\n\n");
        fclose(file);
        mainMenu();
        return;
    }

    const char *fileName = "voterlist.txt";

    int id = generateUniqueIDFromFIle(fileName);

    voter.sno = id;

    fprintf(file, "%d %s %s %s %s\n", voter.sno, voter.name, voter.dateOfBirth, voter.address, voter.password);
    fclose(file);

    printf("\n---------------------------------------\n");
    printf("     Voter registered successfully.   \n");
    printf("---------------------------------------\n\n");

    mainMenu();
}
void searchVoterDetails()
{
    int sno;
    printf("Enter the serial number of the voter: ");
    scanf("%d", &sno);

    FILE *file = fopen("voterlist.txt", "r");
    if (file == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Opening a file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        return;
    }

    struct Voter voter;
    bool found = false;

    while (fscanf(file, "%d %s %s %s %s", &voter.sno, voter.name, voter.dateOfBirth, voter.address, voter.password) != EOF)
    {
        if (voter.sno == sno)
        {
            found = true;
            printf("\n----------------Details of voter %d---------------------\n", sno);
            printf("Serial Number: %d\n", voter.sno);
            printf("Name: %s\n", voter.name);
            printf("Date of Birth: %s\n", voter.dateOfBirth);
            printf("Address: %s\n", voter.address);
            printf("Password: %s\n", voter.password);
            printf("----------------------------------------------------------\n\n");
            break;
        }
    }

    if (!found)
    {
        printf("\n----------------------------------------\n");
        printf("    Voter with voter id %d not found   \n", sno);
        printf("----------------------------------------\n\n");
    }

    fclose(file);
}

void castVote()
{
    int sno;
    char password[20];

    printf("Enter your serial number: ");
    scanf("%d", &sno);
    printf("Enter your password: ");
    scanf("%s", password);

    FILE *voterFile = fopen("voterlist.txt", "r");
    FILE *candidateFile = fopen("candidatelist.txt", "r");
    FILE *voteCountFile = fopen("votecount.txt", "a");

    if (voterFile == NULL || candidateFile == NULL || voteCountFile == NULL)
    {
        printf("\n--------------------------------------------\n");
        printf("   Error Opening a file. Please try again   \n");
        printf("--------------------------------------------\n\n");
        fclose(voterFile);
        fclose(candidateFile);
        fclose(voteCountFile);
        return;
    }

    struct Voter voter;
    bool voterFound = false;

    while (fscanf(voterFile, "%d %s %s %s %s\n", &voter.sno, voter.name, voter.dateOfBirth, voter.address, voter.password) != EOF)
    {
        if (voter.sno == sno && strcmp(voter.password, password) == 0)
        {
            voterFound = true;
            break;
        }
    }

    if (!voterFound)
    {
        printf("\n--------------------------------------------\n");
        printf("    Invalid Credentials. Please try again   \n");
        printf("--------------------------------------------\n\n");
        mainMenu();
        fclose(voterFile);
        fclose(candidateFile);
        fclose(voteCountFile);
        return;
    }

    printf("       List of candidates:       \n");
    printf("-----------------------------------\n\n");

    struct Candidate candidate;
    while (fscanf(candidateFile, "%d %s %s %s\n", &candidate.id, candidate.name, candidate.party, candidate.candidancyFrom) != EOF)
    {
        printf("ID: %d\n", candidate.id);
        printf("Name: %s\n", candidate.name);
        printf("Party: %s\n", candidate.party);
        printf("Candidacy From: %s\n", candidate.candidancyFrom);
        printf("--------------------\n");
    }

    int selectedCandidateId;
    printf("Enter the ID of the candidate you want to vote for: ");
    scanf("%d", &selectedCandidateId);

    struct Candidate selectedCandidate;

    FILE *candidateTempFile = fopen("candidatelist.txt", "r");
    struct Candidate tempCandidate;
    while (fscanf(candidateTempFile, "%d %s %s %s\n", &tempCandidate.id, tempCandidate.name, tempCandidate.party, tempCandidate.candidancyFrom) != EOF)
    {
        if (tempCandidate.id == selectedCandidateId)
        {
            selectedCandidate = tempCandidate;
            break;
        }
    }

    if (selectedCandidate.id != selectedCandidateId)
    {
        printf("\n---------------------------------------------------\n");
        printf("   The candidate with candidate id %d not found.\n", selectedCandidateId);
        printf("---------------------------------------------------\n\n");
        fclose(voterFile);
        fclose(candidateFile);
        fclose(voteCountFile);
        mainMenu();
        return;
    }

    struct VoteCount voteCount;
    bool found = false;

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("\n-------------------------------------------------------\n");
        printf("   Error Creating a temporary file. Please try again   \n");
        printf("-------------------------------------------------------\n\n");
        fclose(candidateFile);
        fclose(voteCountFile);
        fclose(voterFile);
        fclose(tempFile);
        return;
    }

    FILE *voteCountTempReadFile = fopen("votecount.txt", "r");
    while (fscanf(voteCountTempReadFile, "%d %s %s %s %d\n", &voteCount.candidate.id, voteCount.candidate.name,
     voteCount.candidate.party, voteCount.candidate.candidancyFrom, &voteCount.count) != EOF)
    {
        if (voteCount.candidate.id == selectedCandidate.id)
        {
            found = true;
            fprintf(tempFile, "%d %s %s %s %d\n", selectedCandidate.id, selectedCandidate.name,
             selectedCandidate.party, selectedCandidate.candidancyFrom, voteCount.count + 1);
        }
        else
        {
            fprintf(tempFile, "%d %s %s %s %d\n", voteCount.candidate.id, selectedCandidate.name,
             selectedCandidate.party, selectedCandidate.candidancyFrom, voteCount.count);
        }
    }

    if (!found)
    {
        fprintf(tempFile, "%d %s %s %s %d\n", selectedCandidate.id, selectedCandidate.name,
         selectedCandidate.party, selectedCandidate.candidancyFrom, 1);
    }

    fclose(candidateFile);
    fclose(voteCountFile);
    fclose(voterFile);
    fclose(tempFile);
    fclose(voteCountTempReadFile);

    remove("votecount.txt");
    rename("temp.txt", "votecount.txt");

    printf("\n--------------------------------------------\n");
    printf("            Vote cast successfully            \n");
    printf("--------------------------------------------\n\n");

    mainMenu();
}

// -------------------------------- For Core functionaltiy --------------------
int calculateAge(const char *dateOfBirth)
{
    // Extract year, month, and day from the date of birth
    int birthYear, birthMonth, birthDay;
    sscanf(dateOfBirth, "%4d%2d%2d", &birthYear, &birthMonth, &birthDay);

    // Get the current date
    time_t now;
    time(&now);
    struct tm *localTime = localtime(&now);
    int currentYear = localTime->tm_year + 1900;
    int currentMonth = localTime->tm_mon + 1;
    int currentDay = localTime->tm_mday;

    // Calculate age
    int age = currentYear - birthYear;
    if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay))
        age--;

    return age;
}

int generateUniqueIDFromFIle(const char *fileToRead)
{
    FILE *file = fopen(fileToRead, "r");
    int id = 1;

    if (file == NULL)
    {
        return id;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Extract the ID from the line
        int currentID;
        sscanf(line, "%d", &currentID);

        // Update the ID if it is greater than the current ID
        if (currentID >= id)
        {
            id = currentID + 1;
        }
    }

    fclose(file);

    return id;
}

bool checkEligibility(const char *dateOfBirth)
{
    int age = calculateAge(dateOfBirth);
    return age > 18;
}
