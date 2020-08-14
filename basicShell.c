#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

/*
|-----------------------------------|
|------------Basic Shell------------|
|------------basicShell.c-----------|
|-----------by Hadi Sandid----------|
\-----------------------------------/
*/

// ----- Function checkSubstring -----
// Check if a word is a substring of a sentence.
// Returns -1 if false, and returns the start index of the word in the sentence if true.
int checkSubstring(char* sentence, char* word)
{
    // Declaring & initializing temporary indexes 'i' and 'd'
    int i = 0;
    int d = 0;

    // Check if the sentence has a length at least equal to the word
    // The word cannot be a substring otherwise
    if (strlen(sentence) >= strlen(word)) {
        
        // All possible start indexes for the word in the sentence are in the range [0, strlen(sentence) - strlen(word)]
        // We will iterate through each possible index and check if there is a match
        for (i = strlen(sentence) - strlen(word); i >= 0; i--) {
            int found = 1;
            for (d = 0; d < strlen(word); d++) {
                if (sentence[i + d] != word[d]) {
                    found = 0;
                    break;
                }
            }
            if (found == 1) {

                // If a match is found, return the start index of the substring/word in the sentence
                return i;
            }
        }       
    }

    // If a match isn't found, return -1
    return -1;

}

// ----- Function checkPipeSymbol -----
// Check if pipe symbol '|' is present in-between two commands
// Returns 0 if false, and returns 1 if true.
int checkPipeSymbol(char a[])
{
    // Declaring & initializing temporary variables 'arguments', 'wordCheck' and 'intruder'
    int arguments;
    arguments = 0;
    char intruder = ' ';

    // We iterate over the char array 'a' which holds the user command
    // If there is no more than one input word, the function will return 0
    // If there is more than one input word, but the first character after the first input word which isn't a space is something else than '|', we return 0
    // If there is more than one input word, and the first character after the first input word which isn't space is '|', we return 1
    for (int i = 0; i < 30; i++) {
        
        // Check for the first space after the first input word, and if found, increment variable 'arguments'
        if (a[i] == ' ' && arguments == 0) {
            arguments++;
        }

        // If an argument has been found, update the variable 'intruder' to the first non-space character after it
        if (a[i] != ' ' && arguments == 1) {
            intruder = a[i];
            break;
        }
    }
    
    // Check if the first character after the first input word corresponds to the pipe symbol '|', and return
    if (intruder == '|') {

        return 1;
    }
    else {

        return 0;
    }
}

int main()
{
    //////////////////////////////////////////////////////////
    // INITIALIZING ARRAYS                                  //
    // Declaring & initializing arrays used by the program  //
    //////////////////////////////////////////////////////////

    // 'exit' char array, which is used to identify when the user types the 'exit' command
    char exit[30];
    exit[0] = 'e';
    exit[1] = 'x';
    exit[2] = 'i';
    exit[3] = 't';
    exit[4] = '\0';

    // 'ls' char array, which is used to identify when the user types the 'ls' command
    char ls[30];
    ls[0] = 'l';
    ls[1] = 's';
    ls[2] = '\0';

    // 'gen' char array, which is used to identify when the user types the 'generate' command
    char gen[30];
    gen[0] = 'g';
    gen[1] = 'e';
    gen[2] = 'n';
    gen[3] = 'e';
    gen[4] = 'r';
    gen[5] = 'a';
    gen[6] = 't';
    gen[7] = 'e';
    gen[8] = '\0';

    // 'sum' char array, which is used to identify when the user types the 'sum' command
    char sum[30];
    sum[0] = 's';
    sum[1] = 'u';
    sum[2] = 'm';
    sum[3] = '\0';

    // 'subtract' char array, which is used to identify when the user types the 'subtract' command
    char subtract[30];
    subtract[0] = 's';
    subtract[1] = 'u';
    subtract[2] = 'b';
    subtract[3] = 't';
    subtract[4] = 'r';
    subtract[5] = 'a';
    subtract[6] = 'c';
    subtract[7] = 't';
    subtract[8] = '\0';

    // 'tee' char array, which is used to identify when the user types the 'tee' command
    char tee[30];
    tee[0] = 't';
    tee[1] = 'e';
    tee[2] = 'e';
    tee[3] = '\0';
    
    // 'filename' char array, which is used to store the user specified file-name in the tee command
    char filename[30];

    // 'command' char array, which is used to store the current command
    char command[30];

    // 'commandcpy' char array, which is used to store a second command, if the user wants to use pipes
    char commandcpy[30];

    /////////////////////////////////////////////////////////////
    // MAIN LOOP                                               //
    // Default state, which runs until the user calls 'exit'   //
    /////////////////////////////////////////////////////////////

    while (strcmp(exit, command)) {

        // Prints "basic272-shell>" and ask for user input.
        // User input is stored in the 'command' character array
        printf("basic272-shell> ");
        fgets(command, sizeof(command), stdin);

        // Checks if the user has added any spaces at the beginning of his input, and remove them
        // i.e. Check for spaces at the beginning of the 'command' char array, and shift the content of the array to the left to remove those spaces.
        while (command[0] == ' ') {
            for (int i = 0; i < 30; i++) {
                command[i] = command[i + 1];
            }
        }

        // Replace any '\n' symbol in the user input to '\0', to avoid any reading issues later on
        for (int i = 0; i < 30; i++) {
            if (command[i] == '\n') {
                command[i] = '\0';
            }
        }

        // Duplicate the command input of the user into another char array 'commandcpy', in case we have to deal with pipes
        strcpy(commandcpy, command);

        // Initialize variables used to count arguments(i.e. any additional input words in the command, ignoring the first one), 
        // variables used to identify if there is a second & third argument, and variables used to identify the start index of these arguments
        int arguments;
        arguments = 0;
        int indexArgOne = 0;
        int indexOneSet = 0;
        int indexArgTwo = 0;
        int indexTwoSet = 0;
        int indexArgThree = 0;
        int indexThreeSet = 0;
        int newWord = 1;

        // We iterate over the input command, and check how many arguments there are, and identify the start index of these arguments.
        for (int i = 0; i < 30; i++) {
            if (command[i] == ' ' && newWord == 1) {
                arguments++;
                newWord = 0;
            }

            if (command[i] != ' ') {

                if (arguments == 1 && indexOneSet == 0) {
                    indexOneSet = 1;
                    indexArgOne = i;
                }

                if (arguments == 2 && indexTwoSet == 0) {
                    indexTwoSet = 1;
                    indexArgTwo = i;
                }

                if (arguments == 3 && indexThreeSet == 0) {
                    indexThreeSet = 1;
                    indexArgThree = i;
                }

                newWord = 1;
            }

            // Break loop if the '\0' char is found
            if (command[i] == '\0') {
                break;
            }

        }

        // There is only one case where we can have three arguments
        // i.e. <command> | tee <filename>
        // Here we identify and store the filename specified by the user in the 'filename' char array
        if (arguments == 3) {
            for (int i = indexArgThree - 1; i++; i < 30) {
                if (command[i] == ' ' || command[i] == '\0') {
                    filename[i - indexArgThree] = '\0';
                    break;
                }
                filename[i - indexArgThree] = command[i];
            }
        }

        // No additional arguments
        // Possible commands : ls, generate, sum, subtract
        if (arguments == 0) {
            
            // Check if the command corresponds to 'ls'
            // If it corresponds : fork program, and load the 'ls' Java program with parameters 'nopipe'. We then wait for this program to execute fully before proceeding to the default state
            if (strcmp(ls, commandcpy) == 0) {
                pid_t pid1 = fork();
                if (pid1 == 0) {
                    execlp("java", "java", "ls", "nopipe", NULL);
                }
                waitpid(pid1, NULL, 0);
            }

            // Check if the command corresponds to 'gen'
            // If it corresponds : fork program, and load the 'generate' Java program with parameters 'nopipe'. We then wait for this program to execute fully before proceeding to the default state
            else if (strcmp(gen, commandcpy) == 0) {
                pid_t pid1 = fork();
                if (pid1 == 0) {
                    execlp("java", "java", "generate", "nopipe", NULL);
                }
                waitpid(pid1, NULL, 0);
            }

            // Check if the command corresponds to 'sum'
            // If it corresponds : fork program, and load the 'sum' Java program with parameters 'nopipe'. We then wait for this program to execute fully before proceeding to the default state
            else if (strcmp(sum, commandcpy) == 0) {
                pid_t pid1 = fork();
                if (pid1 == 0) {
                    execlp("java", "java", "sum", "nopipe", NULL);
                }
                waitpid(pid1, NULL, 0);
            }

            // Check if the command corresponds to 'subtract'
            // If it corresponds : fork program, and load the 'subtract' Java program with parameters 'nopipe'. We then wait for this program to execute fully before proceeding to the default state
            else if (strcmp(subtract, commandcpy) == 0) {
                pid_t pid1 = fork();
                if (pid1 == 0) {
                    execlp("java", "java", "subtract", "nopipe", NULL);
                }
                waitpid(pid1, NULL, 0);
            }

            // Check if the input corresponds to command 'exit'
            // If it doesn't, then this command is unrecognized and we should let the user know
            else if (strcmp(exit, commandcpy) != 0) {
                printf("%s : Command not recognized\n", commandcpy);
            }
        }

        // There is no supported command with a single argument
        // We automatically print an error message if such input is detected
        else if (arguments == 1) {

            printf("%s : Command not recognized\n", commandcpy);
        }

        // Input command holds two or three arguments
        // Commands with two arguments : generate | sum, generate | subtract,
        // Commands with three arguments : generate | tee <filename>, ls | tee <filename>
        else if (arguments == 2 || arguments == 3) {

            // Check if the full command corresponds to 'ls | tee <filename>'
            // If it corresponds : fork program, and load the 'ls' Java program with parameters 'pipeout'. 
            // We then simulate the 'tee' function, which prints the output of 'ls' to the user, and stores it in a specified text file. 
            // Upon completion, the program proceeds to the default state
            if (checkSubstring(commandcpy, ls) == 0) {

                if (checkPipeSymbol(commandcpy) == 1) {

                    if (checkSubstring(commandcpy, tee) == indexArgTwo) {

                        int pipefd[2];
                        pipe(pipefd);
                        pid_t pid1 = fork();
                        if (pid1 == 0) {
                            close(pipefd[0]);
                            close(1);
                            dup2(pipefd[1], 1);
                            close(pipefd[1]);
                            execlp("java", "java", "ls", "pipeout", NULL);
                        }
                        else {
                            close(pipefd[1]);
                            pid_t pid2 = fork();
                            if (pid2 == 0) {
                                close(0);
                                dup2(pipefd[0], 0);
                                close(pipefd[0]);
                                usleep(1000);
                                char line[3000];
                                int n = read(0, line, 3000);

                                //Save output of 'ls' to file
                                printf("%s\n", line);
                                FILE* pFile;
                                pFile = fopen(filename, "a");
                                fprintf(pFile, " %s", line);
                                fclose(pFile);
                                return 0;
                            }
                            else {
                                {
                                    close(pipefd[0]);
                                    waitpid(pid1, NULL, 0);
                                    waitpid(pid2, NULL, 0);
                                }
                            }
                        }
                    }
                }
                else {
                    printf("%s : Command not recognized\n", commandcpy);
                }
            }

            // Check if the full command corresponds to 'generate | sum' OR 'generate | subtract' OR 'generate | tee <filename>'
            // If it corresponds to 'generate | sum' : fork program, and load the 'generate' Java program with parameter 'pipeout', then fork the program again, and load the 'sum' Java program with parameter 'pipein'
            // If it corresponds to 'generate | subtract' : fork program, and load the 'generate' Java program with parameter 'pipeout', then fork the program again, and load the 'subtract' Java program with parameter 'pipein'
            // If it corresponds to 'generate | tee <filename>' : fork program, and load the 'generate' Java program with parameter 'pipeout'. We then simulate the 'tee' function, which prints the output of 'generate' to the user, and stores it in a specified text file. 
            // Upon completion, the program proceeds to the default state
            else if (checkSubstring(commandcpy, gen) == 0) {

                if (checkPipeSymbol(commandcpy) == 1) {

                    if (checkSubstring(commandcpy, sum) == indexArgTwo) {
                        int pipefd[2];
                        pipe(pipefd);
                        pid_t pid1 = fork();
                        if (pid1 == 0) {
                            close(pipefd[0]);
                            close(1);
                            dup2(pipefd[1], 1);
                            close(pipefd[1]);
                            execlp("java", "java", "generate", "pipeout", NULL);
                        }
                        else {
                            close(pipefd[1]);
                            pid_t pid2 = fork();
                            if (pid2 == 0) {
                                close(0);
                                dup2(pipefd[0], 0);
                                close(pipefd[0]);
                                execlp("java", "java", "sum", "pipein", NULL);
                            }
                            else {
                                {
                                    close(pipefd[0]);
                                    waitpid(pid1, NULL, 0);
                                    waitpid(pid2, NULL, 0);
                                }
                            }
                        }
                    }

                    else if (checkSubstring(commandcpy, subtract) == indexArgTwo) {
                        int pipefd[2];
                        pipe(pipefd);
                        pid_t pid1 = fork();
                        if (pid1 == 0) {
                            close(pipefd[0]);
                            close(1);
                            dup2(pipefd[1], 1);
                            close(pipefd[1]);
                            execlp("java", "java", "generate", "pipeout", NULL);
                        }
                        else {
                            close(pipefd[1]);
                            pid_t pid2 = fork();
                            if (pid2 == 0) {
                                close(0);
                                dup2(pipefd[0], 0);
                                close(pipefd[0]);
                                execlp("java", "java", "subtract", "pipein", NULL);
                            }
                            else {
                                {
                                    close(pipefd[0]);
                                    waitpid(pid1, NULL, 0);
                                    waitpid(pid2, NULL, 0);
                                }
                            }
                        }
                    }

                    else if (checkSubstring(commandcpy, tee) == indexArgTwo) {

                        int pipefd[2];
                        pipe(pipefd);
                        pid_t pid1 = fork();
                        if (pid1 == 0) {
                            close(pipefd[0]);
                            close(1);
                            dup2(pipefd[1], 1);
                            close(pipefd[1]);
                            execlp("java", "java", "generate", "pipeout", NULL);
                        }
                        else {
                            close(pipefd[1]);
                            pid_t pid2 = fork();
                            if (pid2 == 0) {
                                close(0);
                                dup2(pipefd[0], 0);
                                close(pipefd[0]);
                                usleep(1000);
                                char line[3000];
                                int n = read(0, line, 3000);

                                //Save to file
                                printf("%s\n", line);
                                FILE* pFile;
                                pFile = fopen(filename, "a");
                                fprintf(pFile, " %s", line);
                                fclose(pFile);
                                return 0;
                            }
                            else {
                                {
                                    close(pipefd[0]);
                                    waitpid(pid1, NULL, 0);
                                    waitpid(pid2, NULL, 0);
                                }
                            }
                        }
                    }
                }

                // If the input command does not match any of the specified cases, we let the user know his command is invalid
                else {
                    printf("%s : Command not recognized\n", commandcpy);
                }
            }

            // NON-IMPLEMENTED CASE : sum | tee <filename>
            // Prints an error for now
            else if (checkSubstring(commandcpy, sum) == 0) {

                if (checkPipeSymbol(commandcpy) == 1) {

                    printf("%s : Command not recognized\n", commandcpy);
                }
            }

            // NON-IMPLEMENTED CASE : subtract | tee <filename>
            // Prints an error for now
            else if (checkSubstring(commandcpy, subtract) == 0) {

                if (checkPipeSymbol(commandcpy) == 1) {

                    printf("%s : Command not recognized\n", commandcpy);
                }
            }

            else {
                printf("%s : Command not recognized\n", commandcpy);
            }

        }
        
        // End of Main Loop
    }


    
    return 0;
}
