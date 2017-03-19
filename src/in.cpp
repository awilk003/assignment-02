#include "in.hpp"
#include "cmd.hpp"
#include "test.hpp"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <sys/stat.h>


Input::Input(string file)
{
	filename = file;
}

bool Input::check(vector<string> path)
{
	string flag;
	string newPath;
	struct stat buf;
	int validPath;
	bool valid = false;

	//detects flags
	if (path[0].at(0) == '-')
	{
		flag = path[0];
		newPath = path[1];
	}
	else
	{
		flag = "-e";
		newPath = path[0];
	}

	//we only accept 3 flag types at the moment (-e, -d, -f).  Sets to -e if not a valid flag
	if (flag.size() > 2)
	{
		cout << "Invalid flag type, setting flag -e" << endl;
		flag = "-e";
	}

	//checks to see if the path is valid
	validPath = stat((char*)newPath.c_str(), &buf);
	if (validPath == -1)
	{
		//perror("stat");
		return false;
	}
	else if (validPath == 0)
	{
		valid = true;
	}
	else
	{
			return false;
	}

	// if path is valid, flags are then used to decide return value
	if (flag == "-e")
	{
	}
	else if (flag == "-f")
	{
		valid = S_ISREG(buf.st_mode);
		if (valid)
		{
		}
		else
		{
		}
	}
	else if (flag == "-d")
	{
		valid = S_ISDIR(buf.st_mode);
		if (valid)
		{
		}
		else
		{
		}
	}
	else
	{
		cout << "Not a valid flag.  Setting flag to -e" << endl;
		valid = true;
	}

	return valid;
}



bool Input::execute(vector<string> cmds)
{
	char* args[512];
	unsigned i;
	for ( i = 0; i < cmds.size(); i++)
	{
		args[i] = (char*)cmds[i].c_str();
	}
	args[i] = NULL;

	bool isPath = true;
	vector<string> pathcheck;
	pathcheck.push_back(filename);	
	isPath = check(pathcheck);

//	cout << "FILENAME: " << filename << endl;	
//	cout << "ARGS" << endl;
//	for (unsigned k = 0; k < 3; k++)
//	{
//		cout << args[k] << endl;
//	}	
	if (isPath)
	{
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
			int in;
			in = open(filename.c_str(), O_RDONLY);
			dup2(in, 0);
			close(in);
//			for (unsigned i = 0; i < 10; i ++)
//			{
//				cout << "ARGS" << args[i] << endl;
//			}
			execvp(args[0], args);
			exit(0);
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
	else
	{
		cout << "No such file or directory" << endl;
		return false;
	}
}
