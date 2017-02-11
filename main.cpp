#include <iostream>
#include "cmdline.hpp"
#include "cmd.hpp"

int main()
{
	Cmd* A = new Cmd("ls", "asdf");
	A->execute();	
	return 0;
}

