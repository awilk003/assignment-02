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
	int pipes[2];
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
	//set file descriptors
	//int in = open(input.c_str(), O_RDONLY);
	
	int outback = dup(1);
	//int inback = dup(0);

	//set output destination
	string filename = lhs[lhs.size() - 1];
	int in = open(filename.c_str(), O_RDONLY);
	
	//create pipe
	pipe(pipes);
	dup2(pipes[0], in);
	dup2(pipes[1], 1);

	pid1 = fork();


	if (pid1 == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid1 == 0) // child process
	{
		cout << "1ST FORK" << endl;
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
	close(pipes[0]); 
	pid_t pid2 = fork();

	if (pid2 == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid2 == 0)
	{
		cout << "2ND FORK" << endl;
		//dup2(pipes[0], 0);
		//close(pipes[1]);
		if (execvp(rightArgs[0], rightArgs) == -1)
		{
			perror("exec");
			exit(1);
		}
	}
	else
	{
		//dup2(pipes[1], newOut);
		//close(pipes[0]);
		if (execvp(rightArgs[0], rightArgs) == -1)
		{
			perror("exec");
			exit(1);
		}
		dup2(outback, 1);
		dup2(outback, pipes[1]);
		close(pipes[1]);
	}
	return true;
}
