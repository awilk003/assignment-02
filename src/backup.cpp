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

string Backup::checkSymbol(vector<string> cmds, string& path)
{
	string listofsymbols = "<>>";
	string symbol;
	for (unsigned k = 0; k < cmds.size(); k++)
	{
		if (listofsymbols.find(cmds.at(k)) != string::npos)
		{
			symbol = cmds.at(k);
			path = cmds.at(k+1);
			break;
		}
	}
	return symbol;

}

bool Backup::execute(const vector<string> &lhs, const vector<string> &rhs, int (& currFD)[2])
{
	string path;
	string symbol = checkSymbol(lhs, path);
//	cout << "SYMBOL" << symbol << endl;
//	cout << "PATH" << path << endl;

	//int outback = dup(1);
	string filename = "testA.txt";
	int out;
	out = open(filename.c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0666);

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
	rightArgs[j] = NULL;

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
		unsigned i = 0;
		dup2(out, 1);
		if (!symbol.empty())
		{
			while (args[i] != (char*)symbol.c_str())
			{
				i++;	
			}
			args[i] = NULL;

			if (symbol == "<")
			{
				int in = open(path.c_str(),  O_RDONLY);
				dup2(in, 0);
			}
			else
			{
				if (symbol == ">")
				{
					out = open(path.c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0666);
					dup2(out, 1);
				}
				else	
				{
					out = open(path.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0666);
					dup2(out, 1);
				}
			}		
		}

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
	//	dup2(currFD[1], 1);													//HERE IS THE OUTPUT DUP
	//	dup2(outback, out);
		close(out);
	}

		symbol = checkSymbol(rhs, path);
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

			if (!symbol.empty())
			{
				i = 0;
				while (rightArgs[i] != (char*)symbol.c_str())
				{
					i++;	
				}
				rightArgs[i] = NULL;
				
				cout << "ARGS" << rightArgs[0] << endl;

				if (symbol == "<")
				{
					int in = open(path.c_str(),  O_RDONLY);
					dup2(in, 0);
				}
				else
				{
					if (symbol == ">")
					{
						out = open(path.c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0666);
						dup2(out, 1);
					}
					else	
					{
						out = open(path.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0666);
						dup2(out, 1);
					}
				}		
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

		string cmd = "rm";
		char* lastArgs[512];
		lastArgs[0] = (char *)cmd.c_str();
		lastArgs[1] = (char *)filename.c_str();
		lastArgs[2] = NULL;

		pid_t pid3;
		pid3 = fork();
		if (pid3 == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid3 == 0) // child process
		{
			int in;
			in = open(filename.c_str(), O_RDONLY);
			dup2(in, 0);
			close(in);
			execvp(lastArgs[0], lastArgs);
			exit(0);
		}
		else // parent process
		{
			if (waitpid(pid3, &status, 0) == -1)
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


mPipe::mPipe()
{}

bool mPipe::execute(const vector<string> &lhs, const vector<string> &rhs, int (& currFD)[2])
{
	string path;
	string symbol = checkSymbol(lhs, path);
//	cout << "SYMBOL" << symbol << endl;
//	cout << "PATH" << path << endl;

	//int outback = dup(1);
	string filename = "testA.txt";
	int out;
	out = open(filename.c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0666);

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
	rightArgs[j] = NULL;

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
		unsigned i = 0;
		dup2(out, 1);

		if (!symbol.empty())
		{
			while (args[i] != (char*)symbol.c_str())
			{
				i++;	
			}
			args[i] = NULL;

			if (symbol == "<")
			{
				int in = open(path.c_str(),  O_RDONLY);
				dup2(in, 0);
			}
			else
			{
				if (symbol == ">")
				{
					out = open(path.c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0666);
					dup2(out, 1);
				}
				else	
				{
					out = open(path.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0666);
					dup2(out, 1);
				}
			}		
		}

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
		dup2(currFD[1], 1);													//HERE IS THE OUTPUT DUP
	//	dup2(outback, out);
		close(out);
	}

		symbol = checkSymbol(rhs, path);
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

			if (!symbol.empty())
			{
				i = 0;
				while (rightArgs[i] != (char*)symbol.c_str())
				{
					i++;	
				}
				rightArgs[i] = NULL;
				
				cout << "ARGS" << rightArgs[0] << endl;

				if (symbol == "<")
				{
					int in = open(path.c_str(),  O_RDONLY);
					dup2(in, 0);
				}
				else
				{
					if (symbol == ">")
					{
						out = open(path.c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0666);
						dup2(out, 1);
					}
					else	
					{
						out = open(path.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0666);
						dup2(out, 1);
					}
				}		
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

		string cmd = "rm";
		char* lastArgs[512];
		lastArgs[0] = (char *)cmd.c_str();
		lastArgs[1] = (char *)filename.c_str();
		lastArgs[2] = NULL;

		pid_t pid3;
		pid3 = fork();
		if (pid3 == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid3 == 0) // child process
		{
			int in;
			in = open(filename.c_str(), O_RDONLY);
			dup2(in, 0);
			close(in);
			execvp(lastArgs[0], lastArgs);
			exit(0);
		}
		else // parent process
		{
			if (waitpid(pid3, &status, 0) == -1)
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



