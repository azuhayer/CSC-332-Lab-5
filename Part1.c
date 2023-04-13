#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

int main() 
{
    char command[MAX_COMMAND_LENGTH];
    while (1) 
    {
        printf("command: ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        // Remove the newline character from the end of the command string
        size_t command_length = strlen(command);
        if (command[command_length - 1] == '\n') 
        {
            command[command_length - 1] = '\0';
        }

        if (strcmp(command, "exit") == 0) 
        {
            break;
        }

        // Fork a child process to execute the command
        pid_t pid = fork();
        if (pid < 0) 
        {
            perror("fork() failed");
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0) 
        {
            // Child process
            char* args[] = {"/bin/sh", "-c", command, NULL};
            execv(args[0], args);
            perror("execv() failed");
            exit(EXIT_FAILURE);
        } 
        else 
        {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}
