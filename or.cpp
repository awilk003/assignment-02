#include "or.hpp"

Or::Or(bool Left, Cmdline* Right)
{
	Lchild = Left;
	Rchild = Right;	
}

bool Or::execute(string cmd)
{
	if (!Lchild)
	{
		cout  << "HIT IF " << endl;
		return Rchild->execute(cmd);
	}
	else
	{
		return false;
	}
}
/*
bool Or::isValid(bool valid)
{
	if (valid)
	{
		return false;
	}
	else
	{
	
	}
}
*/
