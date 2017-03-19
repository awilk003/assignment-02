#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string>
#include "out.hpp"

Rout::Rout()
{}

Rout::Rout(const string &filename)
{
	file = filename;
}

void Rout::truncate(const string &filename)
{
	
	out = open(filename.c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0666);
	dup2(out, 1);

}

void Rout::append(const string &filename)
{
	int out;
	out = open(filename.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0666);
	dup2(out, 1);
}


bool Rout::execute(const vector<string> &cmds, const char &flag )
{
	int outback = dup(1);
	
	if (flag == 'a')
	{
		append(file);
	}
	else
	{
		truncate(file);
	}
	char* args[512];
	unsigned i;
	for (i = 0; i < cmds.size(); i++)
	{
		args[i] = (char*)cmds[i].c_str();
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
			//exit(1);

		}
		exit(1);
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
		dup2(outback, 1);
	//	dup2(outback, out);
		close(out);
	}


	return true; 
}





