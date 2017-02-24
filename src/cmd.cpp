
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
bool Cmd::execute(string cmd_s)
{
	//cout << (char*)cmd_s.c_str() << endl;
	int space = 0;
	space = cmd_s.find(" ");
	char* args[256];
	if (space > 0)
	{
		string cmdx = cmd_s.substr(0, space);
		string cmdy = cmd_s.substr(space + 1);
		args = { (char*)cmdx.c_str(), (char*)cmdx.c_str(), NULL };
	}
	else
	{
		args = { (char*)cmd_s.c_str(), NULL };
	}
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

