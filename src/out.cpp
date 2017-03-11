#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>

Rout::Rout()
{}

void Rout::truncate(string filename)
{
	int out;
	out = open((char*)filename.c_string(), O_WRONLY | O_TRUNC | O_CREAT);
	dup2(out, 1);
	close out;  
}

void Rout::append(string filename)
{
	int out;
	out = open((char*)filename.c_string(), O_WRONLY | O_APPEND | O_CREAT);
	dup2(out, 1);
	close out;
}


bool execute(vector<string> cmd)
{
	bool valid = true;

	if (cmd[cmd.size()-1] == "a")
	{
		append(cmd[cmd.size()-2]);
	}
	else
	{
		truncate(cmd[cmd.size()-1]);
	}

	return valid; 
}






