#include <iostream>
#include "cmdline.hpp"
#include "cmd.hpp"
#include "semicolon.hpp"
int main()
{
	Cmd* A = new Cmd("ls", "asdf");
	Cmd* B = new Cmd("ls", "asdf");
	Semicolon* C = new Semicolon(A,B);
	if (C->isValid())
	{
		cout << "GOOD " << endl;
	}
	else
	{
		cout << "ERROR" << endl;
	}	
	return 0;
}

