#include <iostream>
#include "cmdline.hpp"
#include "cmd.hpp"
#include "semicolon.hpp"
#include "pound.hpp"
#include "or.hpp"


//NOTE TO SELF: MAKE SURE TO MAKE THE DISTINCTION BETWEEN EXECUTE AND ISVALID, ISVALID CURRENTLY EXECUTES A FUNCTION

int main()
{
	Cmd* A = new Cmd("ls");
	Cmd* B = new Cmd("asdf");
	Semicolon* C = new Semicolon(false,A);
	Pound* D = new Pound(false, B);
	Or* E = new Or(false, A);
	if (E->isValid)
	{
		cout << "GOOD " << endl;
	}
	else
	{
		cout << "ERROR" << endl;
	}
	return 0;
}

