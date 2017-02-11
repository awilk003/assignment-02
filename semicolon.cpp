#include "semicolon.hpp"

Semicolon::Semicolon(Cmd* Left, Cmd* Right)
{
	Lchild = Left;
	Rchild = Right;	
}

bool Semicolon::execute()
{
	Rchild->execute();	
	return Rchild->isValid();
}
