
#include "cmd.hpp"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>

Cmd::Cmd()
{}

Cmd::Cmd(string input1)
{
	uCmd = input1;
	//	cout << "uCmd: " << uCmd << endl;
}


//where the magic happens
//uses fork and exec to execute commands and returns bool values to indicate a valid/invalid command
bool Cmd::execute(vector<string> myArgs)
{
	//cout << (char*)cmd_s.c_str() << endl;
	char* args[512];
	unsigned i;
	for ( i = 0; i < myArgs.size(); i++)
	{
		args[i] = (char*)myArgs[i].c_str();
	}
	args[i] = NULL;

	pid_t pid;
	pid = fork();
	int status;

	if (pid == -1)
	{ 
		perror("fork");
		exit(1);
	}
	if (pid == 0) // child process
	{
		if (execvp(args[0], args) == -1)
		{
			perror("exec");
			exit(1);

		}
	}
	else // parent process
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("wait");
			exit(1);
		}
		if (WEXITSTATUS(status) != 0)
		{
			return false;
		}
	}

	return true;

}

