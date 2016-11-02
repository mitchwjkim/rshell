#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

void parse(string letter, char **argv, vector<char> &con)
{
    vector<string> cmd;
    bool end_flag = false;
    bool letter_flag = false;
    
    while (letter_flag == false)
    {
        string temp;
        
        for(int i = 0; i < letter.length(); i++)
        {
            end_flag = false;                                   // If the end of the command has been reached
            
            if(letter[i] == '#')                                // If start of a comment disregard rest of line
            {
                break;
            }
            if(letter[i] == ';')                                // If the char is ';' push into the connector stack
            {
                end_flag = true;
                con.push_back(letter[i]);
            }
            else if(letter[i] == '&' || letter[i] == '|')       // If the char is '&' or '|' push into the connector stack 
            {
                end_flag = true;
                con.push_back(letter[i]);
                i++;                                            // Skip the duplicate '&' or '|'
            }
            if(end_flag == true)                                // If the current letter is a connector 
            {
                if(temp[0] == ' ')
                {
                    temp.erase(0,1);
                }
                cmd.push_back(temp);
                temp = "";
            }
            else
            {
                temp += letter[i];
            }
            
        }
        if(temp[0] == ' ')                                      // Push back the last string that does not have a connector
        {
            temp.erase(0,1);
        }
        cmd.push_back(temp);
        letter_flag = true;
    }
    
    //Print the vectors
    // for(int j = 0; j < cmd.size(); j++)
    // {
    //     cout << cmd.at(j) << endl;
    //     if(j < con.size())
    //         cout << con.at(j) << endl;
    //     else
    //     {
    //         // Nothing
    //     }
    // }
    
    // Parse the Parse ( Vector<string> cmd into Char * Array into Vector of the Char * Array )
    
    vector<char**> vec_cmd;
    bool cmd_flag = false;                      // While loop flag
    for (int k = 0; k < cmd.size(); k++)
    {
        string hold = cmd.at(k);                // Temp holder for the first command

        vector<char*> temp;                    // Vector for the single command line
        while (cmd_flag == false)
        {
            char* temp_hold = new char;
            for(int i = 0; i < hold.length(); i++)
            {
                if (hold[i] != ' ')
                {
                    temp_hold += hold[i];
                }
                else
                {
                    //temp_hold += '\0';                      // Add Null Character
                    temp.push_back(temp_hold);
                    temp_hold = '\0';
                }
            }
            //temp_hold += '\0';                              // Add Null Character on last string
            temp.push_back(temp_hold);                        // Add last string
            temp.push_back('\0');                             // Have the last index be '\0'
            //temp_hold = '\0';
            
            cmd_flag = true;
        }
        
         for (int i = 0; i < temp.size(); i++)
         {
             argv = new char * [temp.size()];
             char *holder = temp.at(i);
             int count = 0;
             while (holder[count] != '\0')
             {
                 count++;
             }
             argv[i] = new char[count];
             strcpy (argv[i], temp.at(i));
         }
         cmd_flag = false;
         vec_cmd.push_back(argv);
     }
    
     cout << endl << "vec_cmd Data:" << endl;
     for(int i = 0; i < vec_cmd.size(); i++)
     {
         cout << vec_cmd[i] << endl;
     }
}


void execute(char *argv[], vector<char> &con)
{
    int i = 0;
    while (true)
    {
        pid_t pid;
        int status;
        if ((pid = fork()) < 0)
        {
            perror("ERROR: ");
            if(con[i] == '|' || con[i] == ';')
            {
                i++;
                continue;
            }
            else
            {
                exit(1);
            }
        }
        else if (pid == 0)
        {
            if (execvp(*argv, argv) < 0)
            {
                perror("ERROR: ");
                if(con[i] == '|' || con[i] == ';')
                {
                    i++;
                    continue;
                }
                else
                {
                    exit(1);
                }
            }
        }
        else
        {
            while(wait(&status) != pid);
        }
        
        
    }
}

struct command
{
    char *c[64];
};

int main()
{
    vector<char> con;
    vector<command>cmd;
    cout << "This is our command shell." << endl;
    cout << "$ ";
    char input[1024];
    //string input;
    char *argv[64];
    cin.getline(input, 1024);
   // getline(cin, input);
    //parse(input, argv, con);
    //string test = "ls -a";
    
    //test(test);
    
    //cout << "testing github" << endl;
    //for (int i = 0; argv[i] != NULL; i++)
    //{
    //    cout << argv[i] << endl;
    //}
      int i = 0;
      char *token = strtok(input, " ");
      char *temp;
      bool vflag = false;
     while (token != NULL)
     {
         argv[i] = token;
         temp = argv[i];
         for (int j = 0; temp[j] != '\0'; j++)
         {
             if(temp[j] == ';')
             {
                 vflag = true;
                 con.push_back(temp[j]);
                 temp[j] = '\0';
             }
             if(temp[j] == '&' || temp[j] == '|')
             {
                 vflag = true;
                 con.push_back(temp[j]);
                 temp[j] = temp[j+1] = '\0';
                 j++;
             }
         }
         //cout << token << endl;
          argv[i] = temp;
          if (vflag)
          {
              
            //   command co;
            //   int ccount = 0;
            //   while(argv[i] != '\0')
            //   {
            //       co.c[ccount] = argv[i]; 
            //       ccount++;
            //   }
             
            //   cmd.push_back(co);
             
          }
          token = strtok(NULL, " ");
          i++;
        vflag = false;
     }
    return 0;
}