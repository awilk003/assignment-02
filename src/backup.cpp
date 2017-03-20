#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string>
#include "backup.hpp"

Backup::Backup()
{}

Backup::Backup(const string &filename)
{
}


bool Backup::execute(const vector<string> &lhs, const vector<string> &rhs)
{
	int outback = dup(1);
	string filename = "testA.txt";
	int out;
	out = open(filename.c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0666);
	dup2(out, 1);

	char* args[512];
	unsigned i;
	for (i = 0; i < lhs.size(); i++)
	{
		args[i] = (char*)lhs[i].c_str();
	}
	args[i] = NULL;

	char* rightArgs[512];
	unsigned j;
	for (j = 0; j < rhs.size(); j++)
	{
		rightArgs[j] = (char*)rhs[j].c_str();
	}
	rightArgs[i] = NULL;

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

		pid_t pid2;
		pid2 = fork();
		if (pid2 == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid2 == 0) // child process
		{
			int in;
			in = open(filename.c_str(), O_RDONLY);
			dup2(in, 0);
			close(in);
			for (unsigned i = 0; i < 3; i++)
			{
				cout << "RARGS " << rightArgs[i] << endl;
			}
			execvp(rightArgs[0], rightArgs);
			exit(0);
		}
		else // parent process
		{
			if (waitpid(pid2, &status, 0) == -1)
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





