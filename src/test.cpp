#include "test.hpp"
#include <sys/stat.h>
#include <string>
#include <stdio.h>

Test::Test()
{
};

Test::Test(string k)
{
	
}
//This function will return a boolean value depending on whether the path given exists and any conditions given by flags
bool Test::execute(vector<string> path)
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
		cout << "(False)" << endl;
		return false;
	}
	else if (validPath == 0)
	{
		valid = true;
	}
	else
	{
		cout << "(False)" << endl;
		return false;
	}

	// if path is valid, flags are then used to decide return value
	if (flag == "-e")
	{
		cout << "(True)" << endl;
	}
	else if (flag == "-f")
	{
		valid = S_ISREG(buf.st_mode);
		if (valid)
		{
			cout << "(True)" << endl;
		}
		else
		{
			cout << "(False)" << endl;
		}
	}
	else if (flag == "-d")
	{
		valid = S_ISDIR(buf.st_mode);
		if (valid)
		{
			cout << "(True)" << endl;
		}
		else
		{
			cout << "(False)" << endl;
		}
	}
	else
	{
		cout << "Not a valid flag.  Setting flag to -e" << endl;
		cout << "(True)" << endl;
		valid = true;
	}

	return valid;

	



}
