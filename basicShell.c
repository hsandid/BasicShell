#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int checkSubstring(char* sentence, char* word)
{
    int i = 0;
    int d = 0;
    if (strlen(sentence) >= strlen(word)) {
        for (i = strlen(sentence) - strlen(word); i >= 0; i--) {
            int found = 1;
            for (d = 0; d < strlen(word); d++) {
                if (sentence[i + d] != word[d]) {
                    found = 0;
                    break;
                }
            }
            if (found == 1) {
                return i;
            }
        }
        return -1;
    }
    else {
    }
}

int checkPipeSymbol(char a[])
{
    //Count amount of arguments
    int arguments;
    arguments = 0;
    int wordCheck = 1;
    char intruder;
    for (int i = 0; i < 30; i++) {
        if (a[i] == ' ' && wordCheck == 1) {
            wordCheck = 0;
            arguments++;
        }

        if (a[i] != ' ' && arguments == 1) {
            intruder = a[i];
            break;
        }
    }
    if (intruder == '|') {

        return 1;
    }
    else {

        return 0;
    }
}

int main()
{
    char filename[30];
    char command[30];
    char commandcpy[30];
    char exit[30];
    exit[0] = 'e';
    exit[1] = 'x';
    exit[2] = 'i';
    exit[3] = 't';
    exit[4] = '\0';
    char ls[30];
    ls[0] = 'l';
    ls[1] = 's';
    ls[2] = '\0';
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
    char sum[30];
    sum[0] = 's';
    sum[1] = 'u';
    sum[2] = 'm';
    sum[3] = '\0';
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
    char tee[30];
    tee[0] = 't';
    tee[1] = 'e';
    tee[2] = 'e';
    tee[3] = '\0';

    while (strcmp(exit, command)) {

        printf("basic272-shell> ");
        fgets(command, sizeof(command), stdin);

        //Initializing the command to be properly centered
        while (command[0] == ' ') {
            for (int i = 0; i < 30; i++) {
                command[i] = command[i + 1];
            }
        }

        for (int i = 0; i < 30; i++) {
            if (command[i] == '\n') {
                command[i] = '\0';
            }
        }
        strcpy(commandcpy, command);

        //Count amount of arguments
        int arguments;
        arguments = 0;
        int indexArgOne = 0;
        int indexOneSet = 0;
        int indexArgTwo = 0;
        int indexTwoSet = 0;
        int indexArgThree = 0;
        int indexThreeSet = 0;
        int newWord = 1;
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
            if (command[i] == '\0') {
                break;
            }
        }

        if (arguments == 3) {
            for (int i = indexArgThree - 1; i++; i < 30) {
                if (command[i] == ' ' || command[i] == '\0') {
                    filename[i - indexArgThree] = '\0';
                    break;
                }
                filename[i - indexArgThree] = command[i];
            }
        }

        if (arguments == 0) {
            if (strcmp(ls, commandcpy) == 0) {
                //Ls with no argument
                // printf("ls exec\n");
                pid_t pid1 = fork();
                if (pid1 == 0) {
                    //exec parent program
                    execlp("java", "java", "ls", "nopipe", NULL);
                }
                waitpid(pid1, NULL, 0);
            }
            else if (strcmp(gen, commandcpy) == 0) {
                //generate with no argument
                // printf("gen exec\n");
                pid_t pid1 = fork();
                if (pid1 == 0) {
                    //exec parent program
                    execlp("java", "java", "generate", "nopipe", NULL);
                }
                waitpid(pid1, NULL, 0);
            }
            else if (strcmp(sum, commandcpy) == 0) {
                //Sum with no argument
                // printf("Sum exec\n");
                pid_t pid1 = fork();
                if (pid1 == 0) {
                    //exec parent program
                    execlp("java", "java", "sum", "nopipe", NULL);
                }
                waitpid(pid1, NULL, 0);
            }
            else if (strcmp(subtract, commandcpy) == 0) {
                //Subtract with no argument
                // printf("Sub exec\n");
                pid_t pid1 = fork();
                if (pid1 == 0) {
                    //exec parent program
                    execlp("java", "java", "subtract", "nopipe", NULL);
                }
                waitpid(pid1, NULL, 0);
            }
            else if (strcmp(exit, commandcpy) != 0) {
                //Command not recognized && one argument

                printf("%s : Command not recognized\n", commandcpy);
            }
        }
        else if (arguments == 1) {

            printf("%s : Command not recognized\n", commandcpy);
        }
        else if (arguments == 2 || arguments == 3) {
            //ex : generate | sum or generate | tee outputx1

            //First arg check
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
                            //exec parent program
                            execlp("java", "java", "ls", "pipeout", NULL);
                        }
                        else {
                            close(pipefd[1]);
                            pid_t pid2 = fork();
                            if (pid2 == 0) {
                                close(0);
                                dup2(pipefd[0], 0);
                                close(pipefd[0]);
                                //exec child program
                                // execlp("java","java","sum","pipein",NULL);
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
                else {
                    printf("%s : Command not recognized\n", commandcpy);
                }
            }
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
                            //exec parent program
                            execlp("java", "java", "generate", "pipeout", NULL);
                        }
                        else {
                            close(pipefd[1]);
                            pid_t pid2 = fork();
                            if (pid2 == 0) {
                                close(0);
                                dup2(pipefd[0], 0);
                                close(pipefd[0]);
                                //exec child program
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
                            //exec parent program
                            execlp("java", "java", "generate", "pipeout", NULL);
                        }
                        else {
                            close(pipefd[1]);
                            pid_t pid2 = fork();
                            if (pid2 == 0) {
                                close(0);
                                dup2(pipefd[0], 0);
                                close(pipefd[0]);
                                //exec child program
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
                            //exec parent program
                            execlp("java", "java", "generate", "pipeout", NULL);
                        }
                        else {
                            close(pipefd[1]);
                            pid_t pid2 = fork();
                            if (pid2 == 0) {
                                close(0);
                                dup2(pipefd[0], 0);
                                close(pipefd[0]);
                                //exec child program
                                // execlp("java","java","sum","pipein",NULL);
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
                else {
                    printf("%s : Command not recognized\n", commandcpy);
                }
            }
            else if (checkSubstring(commandcpy, sum) == 0) {

                if (checkPipeSymbol(commandcpy) == 1) {

                    printf("%s : Command not recognized\n", commandcpy);
                }
            }
            else if (checkSubstring(commandcpy, subtract) == 0) {

                if (checkPipeSymbol(commandcpy) == 1) {

                    printf("%s : Command not recognized\n", commandcpy);
                }
            }

            else {
                printf("%s : Command not recognized\n", commandcpy);
            }

            //Check for second argument
        }
    }
    return 0;
}
