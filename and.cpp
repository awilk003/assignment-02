#include "and.hpp"

And::And(bool Left, Cmdline* Right)
{
	Lchild = Left;
	Rchild = Right;	
}

bool And::execute()
{
	if (Lchild)
	{
		Rchild->execute();
	}
	return Rchild->isValid();
}

bool And::isValid()
{
	return Rchild->isValid();
}
