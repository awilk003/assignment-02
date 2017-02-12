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

bool Or::isValid()
{
	return Rchild->isValid();
}
