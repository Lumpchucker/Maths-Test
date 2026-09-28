/*
Caleb Snashall
10496195
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Maximum size of allowed input, anything extra will be cut off
#define BUFFER_SIZE 10

// Takes given char pointer and saves user input into it, also handles cleaning up in the case of too little/many characters in the input stream
void user_input(char *response) {
    // Get input from the stdin stream and save in response, max number of bytes is BUFFER_SIZE
    // If unable to read input then tell the user and exit the program
    if (fgets(response, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading user input!\n");
        exit(1);
    }
    
    // Check if there is a \n in the array, if there is then replace it with a null terminator if found 
    // as it means the response is less than or equal to the buffer size
    if (strchr(response, '\n') != NULL) {
        response[strcspn(response, "\n")] = '\0';
    } else { // If no \n found then the input was larger than the BUFFER_SIZE so clear the buffer
        int f;
        while((f = getchar()) != '\n' && f != EOF);
    }
}

// Generate two random number within the bounds of minimum <= number <= maximum
// Then randomly pick whether to add or minus them and get the user to guess the result
// Compare the real value with the guess and if correct return 1, else return 0
int ask_question (const int minimum, const int maximum) {
    // Seed rand with the current time
    srand(time(NULL));

    // Pick a random operator and two random numbers, then calculate the answer
    char operator = (rand() % 2 == 0) ? '+' : '-'; // Generate a random number between 0 and 1, if 0 assign + else assign -
    int first_num = rand() % (maximum - minimum + 1) + minimum;
    int second_num = rand() % (maximum - minimum + 1) + minimum;
    int result = (operator == '+') ? first_num + second_num : first_num - second_num;

    // Tell the user the generated question and get them to answer it
    printf("What is %d %c %d? ", first_num, operator, second_num);

    // Create char array and save the user's response to it
    char response[BUFFER_SIZE];
    user_input(response);
    
    // endptr is used to point to the last element that was attempted to be converted
    // strtol takes a char pointer and attempts to convert it into a long, stopping at the first invalid character and saving the address in endptr
    char *endptr;
    long response_num = strtol(response, &endptr, 10);

    // strtol failed to convert the full string so the response must be invalid, thus it is an incorrect answer 
    if (*endptr != '\0') {
        printf("Invalid number entered\n");
        return 0;
    }
    // If user's converted response is equal to the calculated result then tell the user they were correct and return 1
    if (response_num == result) {
        printf("Correct!\n\n");
        return 1;
    }
    printf("Incorrect! The correct answer was %d\n\n", result);
    return 0; // response_num must not have equaled result
}

// Converts a given mark into the equivalent grade and returns it
const char* gradeConversion(const int mark) {
    // Ranges based off the given grade ranges
    if (mark <= 100 && mark >= 80) return "High Distinction";
    else if (mark >= 70) return "Distinction";
    else if (mark >= 60) return "Credit";
    else if (mark >= 50) return "Pass";
    else if (mark >= 0) return "Fail";
    else return "Invalid";
}

int main(void) {
    printf("Welcome to Maths Tester Pro.\n");
    printf("Select a difficulty:\n1) Easy\n2) Medium\n3) Hard\n");

    char difficulty[BUFFER_SIZE];
    int lives = 0, max_num = 0, questions = 0;

    // Get a user to pick a difficulty, only accepting 1, 2 or 3
    while (!lives) {
        // Get user response and only save the first character (second character is replace with \0)
        printf("> ");
        user_input(difficulty);

        // Easy difficulty
        if (strcmp("1", difficulty) == 0) {
            printf("Easy mode selected!\n\n");
            lives = 3, max_num = 10, questions = 5;
        }
        // Medium difficulty
        else if (strcmp("2", difficulty) == 0) {
            printf("Medium mode selected!\n\n");
            lives = 2, max_num = 25, questions = 10;
        }
        // Hard difficulty
        else if (strcmp("3", difficulty) == 0) {
            printf("Hard mode selected!\n\n");
            lives = 1, max_num = 50, questions = 15;
        }
        // Invalid difficulty entered
        else {
            printf("Invalid choice! Enter 1, 2 or 3.\n");
        }
    }
    // Variable used to track how well the user is doing
    int score = 0;

    // Loop for the total amount of questions, exit early if lives equal 0
    for (int i = 1; i <= questions && lives > 0; i++) {
        printf("Question %d of %d. ", i, questions);

        // If only 1 life left use the correct grammar
        (lives == 1) ? printf("1 life remaining.\n") : printf("You have %d lives remaining.\n", lives);

        // Last question so make it extra hard
        if (i == questions) {
            printf("Challenge question!\n");
            (ask_question(max_num, max_num*2)) ? score++ : lives--; // If return 1 then add score else minus lives
        }
        else {
            (ask_question(1, max_num)) ? score++ : lives--; // If return 1 then add score else minus lives
        }
    }
    // Calculate the percenatage of correct responses, rounding to the neareast decimal, along with corresponding grade
    int percentage = roundl((float)score / questions * 100);
    printf("Test complete.\nYou scored %d/%d (%d%%).\n", score, questions, percentage);
    printf("Your grade is a %s!\n", gradeConversion(percentage));
}