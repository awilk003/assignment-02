#include "pound.hpp"

Pound::Pound(bool Left, Cmdline* Right)
{
//	Lchild = Left;
	Rchild = Right;
}

bool Pound::execute()
{
	return false;
}

bool Pound::isValid()
{
	return false;
}
