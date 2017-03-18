#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include "out.hpp"

Rout::Rout()
{}

void Rout::truncate(const string &filename)
{
	int out;
	out = open(filename.c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0666);
	dup2(out, STDOUT_FILENO);
	close(out);
}

void Rout::append(const string &filename)
{
	int out;
	out = open(filename.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0666);
	dup2(out, STDOUT_FILENO);
	close(out);
}


bool Rout::execute(const vector<string> &cmd)
{

	if (cmd[cmd.size()-1] == "a")
	{
		append(cmd[cmd.size()-2]);
	}
	else
	{
		truncate(cmd[cmd.size()-1]);
	}

	return true; 
}





