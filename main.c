#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Minimum size of 2 as the string still needs to have a null terminator to be valid
#define BUFFER_SIZE 10

int user_input(char *response) {
    //char response[BUFFER_SIZE];
    if (fgets(response, BUFFER_SIZE, stdin) == NULL) {
        printf("Error reading user input!\n");
        return -1;
    }
    // Check if there is a \n in the array, replace it with a null terminator if found as it means the response is less than or equal to the buffer size
    if (strchr(response, '\n') != NULL) {
        response[strcspn(response, "\n")] = '/0';
    } else { // If no \n found then the input was larger than the BUFFER_SIZE so clear the buffer
        int f;
        while((f = getchar()) != '\n' && f != EOF);
    }
    return 1;
}

int ask_question (int minimum, int maximum) {
    srand(time(NULL));
    char operator = (rand() % 2 == 0) ? '+' : '-';
    int first_num = rand() % (maximum - minimum + 1) + minimum;
    int second_num = rand() % (maximum - minimum + 1) + minimum;
    char results[BUFFER_SIZE];
    printf("Enter a number: ");
    if (user_input(results) == -1) {
        printf("Error reading user input!\n");
        return -1;
    }

}

int main(void) {
    printf("Welcome to Maths Tester Pro.\n");
    printf("Select a difficulty:\n1) Easy\n2) Medium\n3) Hard\n");

    char difficulty[BUFFER_SIZE];
    int lives, max_num, questions;

    // Get a user to pick a difficulty, only accepting 1, 2 or 3
    while (1) {
        // Get user response and only save the first character (second character is replace with \0)
        printf("> ");
        if (user_input(difficulty) == -1);

        // Easy difficulty
        if (strcmp("1", difficulty) == 0) {
            printf("Easy mode selected!\n");
            lives = 3, max_num = 10, questions = 5;
            break;
        }
        // Medium difficulty
        else if (strcmp("2", difficulty) == 0) {
            printf("Medium mode selected!\n");
            lives = 2, max_num = 25, questions = 10;
            break;
        }
        // Hard difficulty
        else if (strcmp("3", difficulty) == 0) {
            printf("Hard mode selected!\n");
            lives = 1, max_num = 50, questions = 15;
            break;
        }
        // Invalid difficulty entered
        else {
            printf("Invalid choice! Enter 1, 2 or 3.\n");
        }
    }

    printf("This is your response: %s\n", difficulty);
    printf("The three options are set to: lives-%d, max_num-%d, questions-%d\n", lives, max_num, questions);
    //char msg[] = {'H', 'E', 'L', 'L', 'O', '\0'};
    //printf("%s\n", msg);

    int score = 0, result = 0;

    // Loop for the total amount of questions
    for (int i = 1; i <= questions && lives > 0; i++) {
        printf("Question %d of %d. ", i, questions);

        // If only 1 life left use the correct grammar
        (lives == 1) ? printf("1 life remaining.\n") : printf("You have %d lives remaining.\n", lives);

        // Last question so make it extra hard
        if (i == questions) {
            printf("Challenge question!\n");
            result = ask_question(max_num, max_num*2);
        }
        else {
            result = ask_question(1, max_num);
        }

        (result == 0) ? lives-- : score++;
        printf("The current score is %d and the current lives are %d\n", score, lives);
    }
}