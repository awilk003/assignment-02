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


/*bool Cmd::isValid()
{
	cout << "Ucd: " << uCmd << endl;
	int i = system(uCmd.c_str());
	return i == 0;
}*/



bool Cmd::execute(string cmd_s)
{
  
  pid_t pid;
  char* args[2];
  args[0] = (char*)cmd_s.c_str();
  args[1] = NULL;
  
   if ((pid = fork()) == -1) 
    {
        perror("fork");
	exit(1);
        return false;
    }
    if (pid == 0) // child process
    {
       if(execvp(args[0], args) == -1)
       {
	 perror("exec");
	 exit(1);
       }
    }
    else // parent process
    {
      if(wait(0) == -1)
      {
		perror("wait");
		exit(1);
		return false;
      }
	  
    }
    return true;
}


