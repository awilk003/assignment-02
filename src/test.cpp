#include "test.hpp"
#include <sys/stat.h>
#include <string>

Test::Test(string k)
{
	
}

bool Test::execute(string path)
{
	string flag;
	string newPath;
	struct stat buf;
	int validPath;
	bool valid = false;

	if (path.at(0) == "-")
	{
		flag = path.substr(0, 2);
		newPath = path.substr(2);
	}
	else
	{
		flag = "-e";
		newPath = path;
	}

	if (flag.size() > 2)
	{
		cout << "Invalid flag type, setting flag -e" << endl;
		flag = "-e";
	}


	validPath = stat((char*)newPath.c_str(), &buf);
	if (validPath == -1)
	{
		perror("stat");
		return false;
	}
	else if (validPath == 0)
	{
		valid = true;
	}
	else
	{
		cout << "Path does not exist" << endl;
		return false;
	}


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
