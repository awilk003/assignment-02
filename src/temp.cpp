#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

int main()
 {
	
	char* leftArgs[512];
	leftArgs[0] = (char*)"echo";
	leftArgs[1] = (char*)"a";
	//	args[2] = (char*)"test.txt";
    leftArgs[2] = (char*)NULL;

	char* rightArgs[512];
	rightArgs[0] = (char*)"tee";
	rightArgs[1] = (char*)"testing.txt";
	rightArgs[1] = (char*)NULL;

	//int outback = dup(1);
	//int inback = dup(0);

	//set output destination
	//string filename = lhs[lhs.size() - 1];
	//int in = open(filename.c_str(), O_RDONLY);

	//create pipes
	int pipes[2];
	pipe(pipes);



	pid_t pid1 = fork();
	int status;

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
		close(pipes[0]);

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
	return 0;
}
