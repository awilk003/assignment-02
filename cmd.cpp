#include "cmd.hpp"

Cmd::Cmd(string input1, string input2)
{
	Rcmd = input1;
}


bool Cmd::isValid()
{
	int i = system(Rcmd.c_str());
	return i == 0;
}

bool Cmd::execute()
{
	system(Rcmd.c_str());	
	return isValid();
	
}
