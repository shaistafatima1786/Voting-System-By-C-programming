#ifndef EXAMPLE_H
#define EXAMPLE_H

// For menu options
void mainMenu();
void adminMenu();
void adminCredentialsForm();
void adminFunctionality();

// Welcome
void welcome();

// For admin functionality
void createElectionSchedule();
void registerCandidate();
void updateCandidateDetails();
void deleteCandidate();
void listCandidateDetails();
void updateVoterDetails();
void deleteVoter();
void displayVoteResult();

void listConstitutionDetails();

// For voter functionality
void registerVoter();
void searchVoterDetails();
void castVote();

// Core functionality
int calculateAge(const char *dateOfBirth);
int generateUniqueIDFromFIle(const char *fileToRead);
bool checkEligibility(const char *dateOfBirth);

// Definting custom
struct Candidate
{
    int id;
    char name[100];
    char party[100];
    char candidancyFrom[100];
};

struct Voter
{
    int sno;
    char name[100];
    char dateOfBirth[9];
    char address[100];
    char password[20];
};

struct ElectionSchedule
{
    char constituency[100];
    char date[9];
};

struct VoteCount
{
    struct Candidate candidate;
    int count;
};

#endif