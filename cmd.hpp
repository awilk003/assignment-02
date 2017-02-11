#ifndef CMD_H
#define CMD_H

#include "cmdline.hpp"

class Cmd : public Cmdline
{
	public:
		Cmd() {};
		Cmd(string input1, string input2 = 0);
		bool isValid();
		bool execute();
	protected:
		string Lcmd;
		string Rcmd;
};

#endif
