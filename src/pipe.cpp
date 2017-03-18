#include "pipe.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>

Pipe::Pipe()
{}

bool Pipe::execute(const vector<string> &cmd, string &input)
{
	int pid;
	int pipes[2];

	//pass in commands to args
	char* args[512];
	for (unsigned i = 0; i < cmd.size() - 1; i++)
	{
		args[i] = (char*)cmd[i].c_str();
	}
	
	//set file descriptors
	pipes[0] = input;
	pipes[1] = STDOUT_FILENO;
	
	//set output destination
	string filename = cmd[cmd.size() - 1];
	int newOut = open(filename.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0666);

	//create pipe
	pipe(pipes);
	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		dup2(pipes[0], 0);
		close(pipes[1]);
		if (execvp(args[0], args) == -1)
		{
			perror("exec");
			exit(1);
		}
	}
	else
	{
		dup2(pipes[1], newOut);
		close(pipes[0]);
		if (execvp(args[0], args) == -1)
		{
			perror("exec");
			exit(1);
		}
	}
	
}