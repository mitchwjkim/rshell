##Description
  The program retrieves a user input of command line as a string and is then passed into a parse function.
The parse function sorts out the string and transfer the parsed string into a vector of char**, which can 
then be used for the execvp function. The vector of char** is then passed into our execute function, which 
then executes the respective command lines in regards to their respective connectors( ; , && , || ).

##Bugs
    - Code began glitching once we clean up our comments (??)
    - When using the parse function, if the user inputs a connector at the start of their input and its
      followed different connectors follower the inputs and the last input is same connector as the first
      the function then runs into a segmentation fault
        Ex. ( ls -a; echo hello && mkdir test || echo world; git status )
            - The first connector (;) is the same as the last (;)
