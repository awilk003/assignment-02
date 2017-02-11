#include "semicolon.hpp"

Semicolon::Semicolon(Cmd* Right, Cmd* Left)
{
	Lchild = Left;
	Rchild = Right;	
}

bool Semicolon::execute()
{
	Rchild->execute();	
	return Rchild->isValid();
}
