#include "or.hpp"

Or::Or(bool Left, Cmdline* Right)
{
	Lchild = Left;
	Rchild = Right;	
}

bool Or::execute()
{
	if (!Lchild)
	{
		cout  << "HIT IF " << endl;
		Rchild->execute();
	}
	return Rchild->isValid();
}

bool Or::isValid(bool valid)
{
	if (valid)
	{
		return false;
	}
	else
	{
		return Rchild->execute()
	}
}
