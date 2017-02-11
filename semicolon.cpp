#include "semicolon.hpp"

Semicolon::Semicolon(Cmdline* cmd)
{
	Lcmd = cmd;
}

void Semicolon::execute(string uCmd)
{
	system(uCmd.c_str());	
}
