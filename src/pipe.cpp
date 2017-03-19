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
	pid_t pid1;
	int status;
	//int out;

	//pass in commands to args
	char* leftArgs[512];
	unsigned i;
	for (i = 0; i < lhs.size()-1; i++)
	{
		leftArgs[i] = (char*)lhs[i].c_str();
	}
	leftArgs[i] = NULL;

	char* rightArgs[512];
	unsigned j;
	for (j = 0; j < rhs.size(); j++)
	{
		rightArgs[j] = (char*)rhs[j].c_str();
	}
	rightArgs[j] = NULL;
	

	//int outback = dup(1);
	//int inback = dup(0);

	//set output destination
	//string filename = lhs[lhs.size() - 1];
	//int in = open(filename.c_str(), O_RDONLY);
	
	//create pipes
	int pipes[2];
	pipe(pipes);

	

	pid1 = fork();


	if (pid1 == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid1 == 0) // child process
	{

		dup2(pipes[0], 0);
		close(pipes[1]);

		if (execvp(leftArgs[0], leftArgs) == -1)
		{
			perror("exec");
			exit(1);

		}
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
	
	pid_t pid2 = fork();

	if (pid2 == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid2 == 0)
	{
		dup2(1, pipes[0]);
		close(pipes[1]);

		if (execvp(rightArgs[0], rightArgs) == -1)
		{
			perror("exec");
			exit(1);
		}
	}
	else
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
	//	dup2(outback, 1);
		//dup2(outback, pipes[1]);
		//close(pipes[1]);
	}
	return true;
}
