#include "cmd.hpp"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

Cmd::Cmd ()
{}

Cmd::Cmd(string input1)
{
	uCmd = input1;
//	cout << "uCmd: " << uCmd << endl;
}



//where the magic happens
//uses fork and exec to execute commands and returns bool values to indicate a valid/invalid command
bool Cmd::execute(string cmd_s)
{
  
    pid_t pid;
    char* args[2];
    args[0] = (char*)cmd_s.c_str();
    args[1] = NULL;
    pid = fork();

	if (pid == -1)
	{
		perror("fork");
		valid = false;
		exit(1);
    }
    if (pid == 0) // child process
    {
         if(execvp(args[0], args) == -1)
         {
		     perror("exec");
			 valid = false;
		     exit(1);
			 
         }
		 valid = true;
    }
    else // parent process
    {
		if (wait(0) == -1)
		{
			perror("wait");
			valid = false;
			exit(1);
		}
		if (WEXITSTATUS(status) != 0)
		{
			return false;
		}
     }

	return true;
	  
}



