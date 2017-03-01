#include "and.hpp"

And::And(bool Left, Cmdline* Right)
{
	Lchild = Left;
	Rchild = Right;	
}

//calls execute on Cmdline* Right and returns a bool value indicating whether the command was executed or not
bool And::execute(vector<string> cmd)
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

