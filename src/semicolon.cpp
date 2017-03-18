#ifndef SEMI_CPP
#define SEMI_CPP
#include "semicolon.hpp"

Semicolon::Semicolon(bool Left, Cmdline* Right)
{
	Lchild = Left;
	Rchild = Right;
}

//calls execute on Cmdline* Right and returns a bool value indicating whether the command was executed or not
bool Semicolon::execute(vector<string> cmd)
{
	return Rchild->execute(cmd);	
}
#endif
