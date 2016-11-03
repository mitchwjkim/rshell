#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

 void parse(char input[], vector<string> &cmd, vector<char> &con)
 {
// 	vector<string> cmd;
// 	bool end_flag = false;
// 	bool letter_flag = false;

// 	while (letter_flag == false)
// 	{
// 		string temp;

// 		for (int i = 0; i < letter.length(); i++)
// 		{
// 			end_flag = false;                                   // If the end of the command has been reached

// 			if (letter[i] == '#')                                // If start of a comment disregard rest of line
// 			{
// 				break;
// 			}
// 			if (letter[i] == ';')                                // If the char is ';' push into the connector stack
// 			{
// 				end_flag = true;
// 				con.push_back(letter[i]);
// 			}
// 			else if (letter[i] == '&' || letter[i] == '|')       // If the char is '&' or '|' push into the connector stack 
// 			{
// 				end_flag = true;
// 				con.push_back(letter[i]);
// 				i++;                                            // Skip the duplicate '&' or '|'
// 			}
// 			if (end_flag == true)                                // If the current letter is a connector 
// 			{
// 				if (temp[0] == ' ')
// 				{
// 					temp.erase(0, 1);
// 				}
// 				cmd.push_back(temp);
// 				temp = "";
// 			}
// 			else
// 			{
// 				temp += letter[i];
// 			}

// 		}
// 		if (temp[0] == ' ')                                      // Push back the last string that does not have a connector
// 		{
// 			temp.erase(0, 1);
// 		}
// 		cmd.push_back(temp);
// 		letter_flag = true;
// 	}

// 	//Print the vectors
// 	// for(int j = 0; j < cmd.size(); j++)
// 	// {
// 	//     cout << cmd.at(j) << endl;
// 	//     if(j < con.size())
// 	//         cout << con.at(j) << endl;
// 	//     else
// 	//     {
// 	//         // Nothing
// 	//     }
// 	// }

// 	// Parse the Parse ( Vector<string> cmd into Char * Array into Vector of the Char * Array )

// //	vector<char**> vec_cmd;                     // Destination. Vector filled with argv
// 	bool cmd_flag = false;                      // While loop flag
	
	    
	
// 	for (int k = 0; k < cmd.size(); k++)
// 	{
// 		string hold = cmd.at(k);                // Temp holder for the first command

// 		vector<char*> temp;                     // Vector for the single command line
		        
		
// 		// LOOP - Parses the spaces in the single command line.
// 		while (cmd_flag == false)
// 		{
// 		    char *temp_hold = new char[hold.length()];   
// 			int index = 0;                                          // Index for temp_hold
			
// 			for (int i = 0; i < hold.length(); i++)
// 			{
// 				if (hold[i] != ' ')
// 				{
					
// 					temp_hold[index] = hold[i];
// 					index++;
// 				}
// 				else
// 				{
// 					temp_hold[index] = '\0';                        // Add Null Character
// 					temp.push_back(temp_hold);                      // Push the array onto the vector
// 					temp_hold = new char[hold.length()];            // Reset the array
// 					index = 0;
// 				}
// 			}
			
// 			temp_hold[index]= '\0';                              // Add Null Character on last string
// 			temp.push_back(temp_hold);                          // Add last string
// 			temp.push_back('\0');                               // Have the last index be '\0'

// 			cmd_flag = true;
// 		}
		
// 		// Then store the indexs into argv and push into a vector of argv
//   		char** argv = new char *[temp.size()];

//  		for (int i = 0; i < temp.size(); i++)
//  		{
//  		    // ------------------- ERROR HERE -------------------------------------
//  		    // Segmentation Fault when the lines below are added
//  			int count = (unsigned)strlen(temp.at(i));
//  			argv[i] = new char [count];
//  			strcpy( argv[i], temp.at(i) );
//  		}
 		
//   		vec_cmd.push_back(argv);
//   		cmd_flag = false;
//  	}

//     cout << endl << "vec_cmd Data:" << endl;
// 	for (int i = 0; i < vec_cmd.size(); i++)
// 	{
// 	    cout << vec_cmd.at(i) << endl;
// 	}
	    string s(input);
	      int i = 0;
	      char *token = strtok(input, ";|&");
	      while (token != NULL)
	      {	 
	      	cmd.push_back(token);
	          token = strtok(NULL, ";|&");
	          i++;
	          }
	          for (int i = 0; i < s.size(); i++)
	          {
	          	if (s[i] == ';')
	          	{
	          		con.push_back(s[i]);
	          	}
	          	if (s[i] == '&')
	          	{
	          		con.push_back(s[i]);
	          	}
	          	if (s[i] == '|')
	          	{
	          		con.push_back(s[i]);
	          	}
	          	if(s[i] == '#')
	          	{
	          		con.push_back(s[i]);
	          		break;
	          	}
	          }
	      	
 }


 void execute(vector<string>&cmd, vector<char>&con)
 {
// 	char *argv[cmd.size()];
// 	char *temp;
// 	char con;
// 	// cout << cmd.size() << endl;
// 	int count = 0;
// 	while(count < cmd.size() || cmd.at(count) != "#")
// 	{
// 	for(int i = 0; i < cmd.size(); i++)
// 	{
// 		if(cmd.at(i) == ";" || cmd.at(i) == "&"  || cmd.at(i) == "|" || cmd.at(i) == "#")
// 		{
// 			con = cmd.at(i)[0];
// 			break;
// 		}
// 		else
// 		{
// 			string s = cmd.at(i);
// 			strcpy(temp, s.c_str());
// 			argv[i] = temp;			
// 		}

// //		cout << argv[i] << endl;
// 	}
// 	argv[cmd.size() + 1] = '\0';
	int cmd_index = 0;
	int con_index = 0;
	char *argv[cmd.size()];
	for (cmd_index = 0; cmd_index < cmd.size(); cmd_index++)
	{
		
		string s = cmd.at(cmd_index);
		char *temp = new char[s.length() + 1];
		strcpy(temp, s.c_str());
		char *token = strtok(temp, " ");
		argv[cmd_index] = token;
		while (token != NULL)
		{
			argv[cmd_index] = token;
			cout << argv[cmd_index] << endl;
			token = strtok(NULL, " ");
		}
		delete [] temp;		
	}

        // pid_t pid;
        // int status;
        // if ((pid = fork()) < 0)
        // {
        //     perror("ERROR");
        //     if(con == '|' || con == ';')
        //     {
        //       // i++;
        //         return -1;
        //     }
        //     else
        //     {
        //         exit(1);
        //     }
        // }
        // else if (pid == 0)
        // {
        //     if (execvp(argv[0], argv) < 0)
        //     {
        //         perror("ERROR");
        //         if(con == '|' || con == ';')
        //         {
        //           //  i++;
        //             return -1;
        //         }
        //         else
        //         {
        //             exit(1);
        //         }
        //     }
        // }
        // else
        // {
        //     while(wait(&status) != pid);
        // }
       // count++;
	//}
}

int main()
{
    vector<char>con;
    vector<string>cmd;
    cout << "This is our command shell." << endl;
	    cout << "$ ";
	    char input[1024];
	    //string input;
	    char *argv[64];
	    cin.getline(input, 1024);
	    //getline(cin, input);
	    parse(input, cmd, con);
	    if (strcmp(input, "exit") == 0)
	    {
	    	exit(0);
	    }
	execute(cmd,con);    

	      //char *temp;
	      //bool vflag;         
	      //string s;

	     	// vflag = false;
	      //   argv[i] = token;
	      //   temp = argv[i];
	      //   for (int j = 0; temp[j] != '\0'; j++)
	      //   {
	      //       if(temp[j] == ';')
	      //       {
	      //           vflag = true;
	                
	      //           string r(temp);
	      //           r.pop_back();
	      //           strcpy(temp,r.c_str());
	      //            cmd.push_back(temp);
	      //       }
	      //       else if(temp[j] == '&' || temp[j] == '|')
	      //       {
	      //           vflag = true;
	               
	      //           string r(temp);
	      //          r.pop_back();
	      //          r.pop_back();
	      //          strcpy(temp,r.c_str());
	      //            cmd.push_back(temp);
	      //           j++;
	      //       }
	      //       else if(temp[j] == '#')
	      //       {
	      //       	vflag = true;
	       
	      //       	string r(temp);
	      //       	r.pop_back();
	      //       	strcpy(temp,r.c_str());
	      //       	cmd.push_back(temp);
	      //       	break;
	      //       }
	      //       else
	      //       {
	      //       	argv[i] = temp;
	      //       }
	      //   }
	      //             string s(argv[i]);
	      //                cmd.push_back(s); 
	      //        if (vflag)
	      //        {
	      //        int ex = execute(cmd);
	      //            cmd.clear();
	      //            if(ex == -1)
	      //            {
	      //            	if(con[i] == '|' || con[i] == ';')
	      //            	{
	      //            		continue;
	      //            	}
	      //            }
	      //       }
	      
      return 0;
}