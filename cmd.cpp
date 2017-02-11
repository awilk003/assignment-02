#include "cmd.hpp"

Cmd::Cmd(string input1, string input2)
{
	Lcmd = input1;
	Rcmd = input2;
}


bool Cmd::isValid()
{
	string input;
	cin >> input;
	int i = system(input.c_str());
	return i == 0;
}

void Cmd::execute()
{
	system(Lcmd.c_str());	
	system(Rcmd.c_str());
}
