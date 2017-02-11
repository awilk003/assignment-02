#include "semicolon.hpp"

Semicolon::Semicolon(Cmdline* cmd)
{
	Lcmd = cmd;
}

void Semicolon::execute()
{
	system(Rcmd.c_str());	
}
