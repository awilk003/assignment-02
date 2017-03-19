#include "pipe.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string>
#include <stdio.h>


Pipe::Pipe()
{}

bool Pipe::execute(const vector<string> &lhs, const vector<string> &rhs)
{
	int pid1;
	int pipes[2];

	//pass in commands to args
	char* leftArgs[512];
	for (unsigned i = 0; i < lhs.size(); i++)
	{
		leftArgs[i] = (char*)cmd[i].c_str();
	}
	leftArgs[i] = NULL;

	char* rightArgs[512];
	for (unsigned j = 0; j < rhs.size() -1; j++)
	{
		rightArgs[j] = (char*)cmds[j].c_str();
	}
	rightArgs[j] = NULL;
	//set file descriptors
	//int in = open(input.c_str(), O_RDONLY);
	pipes[0] = 0;
	pipes[1] = 1;
	
	int backup = dup(1);

	//set output destination
	string filename = rhs[rhs.size() - 1];
	int newOut = open(filename.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0666);
	
	//create pipe
	pipe(pipes);
	pid1 = fork();


	if (pid1 == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid1 == 0) // child process
	{
		if (execvp(leftArgs[0], leftArgs) == -1)
		{
			perror("exec");
			//exit(1);

		}
		exit(1);
	}
	else // parent process
	{
		if (waitpid(pid1, &status, 0) == -1)
		{
			perror("wait");
			exit(1);
		}
		if (WEXITSTATUS(status) != 0)
		{
			return false;
		}
	}

	int pid2 = fork();

	if (pid2 == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid2 == 0)
	{
		dup2(pipes[0], 0);
		close(pipes[1]);
		if (execvp(rightArgs[0], rightArgs) == -1)
		{
			perror("exec");
			exit(1);
		}
	}
	else
	{
		dup2(pipes[1], newOut);
		close(pipes[0]);
		if (execvp(rightArgs[0], rightArgs) == -1)
		{
			perror("exec");
			exit(1);
		}
	}
	return true;
}