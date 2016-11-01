#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

void parse(char *line, char **argv)
{
    // while(*line != '\0')
    // {
    //     while (*line == ' ' || *line == '\t' || *line == '\n')
    //         *line++ = '\0';
    //     *argv++ = line;
    //     while(*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n')
    //         line++;
    // }
    // *argv = '\0';
    
}

void execute(char **argv)
{
    pid_t pid;
    int status;
    if ((pid = fork()) < 0)
    {
        perror("ERROR: ");
        exit(1);
    }
    else if (pid == 0)
    {
        if (execvp(*argv, argv) < 0)
        {
            perror("ERROR: ");
            exit(1);
        }
    }
    else
    {
        while(wait(&status) != pid);
    }
}

int main()
{
    cout << "This is our command shell." << endl;
    cout << "$ ";
    char input[1024];
    char *argv[64];
    cin.getline(input, 1024);
    //parse(input, argv);
    cout << "testing github" << endl;
    //for (int i = 0; argv[i] != NULL; i++)
    //{
    //    cout << argv[i] << endl;
    //}
     char *token = strtok(input, " ");
     while (token != NULL)
     {
         cout << token << endl;
          token = strtok(NULL, " ");
     }
    return 0;
}