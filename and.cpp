#include "and.hpp"

And::And(bool Left, Cmdline* Right)
{
	Lchild = Left;
	Rchild = Right;	
}

void And::execute(string cmd)
{
	if (Lchild)
	{
		Rchild->execute(cmd);
	}

}

bool And::isValid()
{
//	return Rchild->isValid();
}
