#ifndef CMD_H
#define CMD_H

#include "cmdline.hpp"

class Cmd : public Cmdline
{
	public:
		Cmd(string input1, string input2 = 0);
		bool isValid();
		void execute();
	protected:
		string Lcmd;
		string Rcmd;
};

#endif
