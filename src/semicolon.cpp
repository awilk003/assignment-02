#include "semicolon.hpp"

Semicolon::Semicolon(bool Left, Cmdline* Right)
{
	Lchild = Left;
	Rchild = Right;
}
//calls execute on Cmdline* Right and returns a bool value indicating whether the command was executed or not
bool Semicolon::execute(string cmd)
{
	return Rchild->execute(cmd);	
}
