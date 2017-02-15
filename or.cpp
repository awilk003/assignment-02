#include "or.hpp"

Or::Or(bool Left, Cmdline* Right)
{
	Lchild = Left;
	Rchild = Right;	
}

void Or::execute(string cmd)
{
	if (!Lchild)
	{
		cout  << "HIT IF " << endl;
		Rchild->execute(cmd);
	}
}

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
