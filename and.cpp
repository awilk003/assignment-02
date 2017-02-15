#include "and.hpp"

And::And(bool Left, Cmdline* Right)
{
	Lchild = Left;
	Rchild = Right;	
}

bool And::execute(string cmd)
{
	if (Lchild)
	{
		return Rchild->execute(cmd);
	}
	else
	{
		return false;
	}

}
/*
bool And::isValid()
{
//	return Rchild->isValid();
}
*/
