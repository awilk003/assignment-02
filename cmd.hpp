#ifndef CMD_H
#define CMD_H

#include "cmdline.hpp"

class Cmd : public Cmdline
{
	public:
		Cmd() {};
		Cmd(string input1);
		//bool isValid();
		bool execute(string cmd_s);	
	protected:
		string uCmd;
};

#endif
