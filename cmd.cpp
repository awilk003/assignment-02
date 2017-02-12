#include "cmd.hpp"

Cmd::Cmd(string input1)
{
	uCmd = input1;
	cout << "uCmd: " << uCmd << endl;
}


bool Cmd::isValid()
{
	cout << "Ucd: " << uCmd << endl;
	int i = system(uCmd.c_str());
	return i == 0;
}

bool Cmd::execute()
{
	system(uCmd.c_str());	
	return isValid();
	
}


