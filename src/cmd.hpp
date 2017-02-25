#ifndef _CMD_H_
#define _CMD_H_

#include "cmdline.hpp"

class Cmd : public Cmdline
{
	public:
		Cmd();
		Cmd(string input1);
		//bool isValid();
		bool execute(string cmd_s);	
	protected:
		string uCmd;
};

#endif
