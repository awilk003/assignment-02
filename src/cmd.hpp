#ifndef _CMD_H_
#define _CMD_H_

#include "cmdline.hpp"
#include <vector>

class Cmd : public Cmdline
{
	public:
		Cmd();
		Cmd(string input1);
		//bool isValid();
		bool execute(vector<string> myArgs);	
	protected:
		string uCmd;
};

#endif
