#include "cmd.hpp"

Cmd::Cmd(string input1, string input2)
{
	Lcmd = input1;
}


bool Cmd::isValid()
{
	int i = system(Lcmd.c_str());
	return i == 0;
}

bool Cmd::execute()
{
	system(Lcmd.c_str());	
	return isValid();
	
}
